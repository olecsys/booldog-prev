#ifndef BOO_STACK_ALLOCATOR_H
#define BOO_STACK_ALLOCATOR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_mem_cluster.h"
#include "boo_threading_utils.h"
namespace booldog
{
	namespace allocators
	{
		template< size_t s, size_t cluster_count = 1 >
		class stack : public ::booldog::stack_allocator
		{
			::booldog::byte _data[s + sizeof(::booldog::mem::info4)];
			::booldog::mem::cluster _clusters[cluster_count];
			size_t _count;
			::booldog::interlocked::atomic _index;
		public:
			stack()
				: _index(0)
			{
				_count = cluster_count;
				size_t cluster_size = (s + sizeof(::booldog::mem::info4)) / _count;				
				while(cluster_size < sizeof(::booldog::mem::info4))
				{
					--_count;
					if(_count == 0)
						break;
					cluster_size = (s + sizeof(::booldog::mem::info4)) / _count;
					if(cluster_size % BOOLDOG_MEM_ALIGN_SIZE)
						cluster_size = BOOLDOG_MEM_ALIGN_SIZE * (cluster_size /BOOLDOG_MEM_ALIGN_SIZE) + BOOLDOG_MEM_ALIGN_SIZE;
				}
				_count = (s + sizeof(::booldog::mem::info4)) / cluster_size;
				::booldog::byte* ptr = _data;
				for(size_t cluster_index = 0;cluster_index < _count;++cluster_index)
				{
					_clusters[cluster_index].initialize(ptr, cluster_size);
					ptr += cluster_size;
				}
			}
			booinline void print()
			{
				_clusters[0].print();
			}
		public:
			virtual size_t available()
			{
				return _clusters[0].available();
			}
			void* begin()
			{
				return _clusters[0].begin();
			};
			void* end()
			{
				return _clusters[0].end();
			};
		private:
			::booldog::mem::cluster* get_free_cluster(void* pointer)
			{
				::booldog::mem::cluster* cluster = 0;
				if(pointer)
				{
					for(size_t index = 0;index < _count;++index)
					{
						cluster = &_clusters[index];
						if(cluster->contains(pointer))
							break;
						cluster = 0;
					}
					::booldog::byte tries = 0;
					while(::booldog::interlocked::compare_exchange(&cluster->_locked, 1, 0) != 0)
					{
						if(tries++ == 5)
							::booldog::threading::sleep(1);
					}
				}
				else
				{
					size_t index = (size_t)::booldog::interlocked::increment(&_index) - 1;
					if(index >= _count)
					{
						::booldog::interlocked::exchange(&_index, 0);
						index = 0;
					}
					for(;index < _count;++index)
					{
						cluster = &_clusters[index];
						if(::booldog::interlocked::compare_exchange(&cluster->_locked, 1, 0) == 0)
							break;
						cluster = 0;
					}
					if(cluster == 0)
					{
						for(index = 0;index < _count;++index)
						{
							cluster = &_clusters[index];
							if(::booldog::interlocked::compare_exchange(&cluster->_locked, 1, 0) == 0)
								break;
							cluster = 0;
						}
					}
				}
				return cluster;
			}
		public:
			virtual void* alloc(size_t size, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				::booldog::mem::cluster* cluster = get_free_cluster(0);
				if(cluster)
				{
					void* ptr = cluster->alloc(size, debuginfo);
					::booldog::interlocked::exchange(&cluster->_locked, 0);
					return ptr;
				}
				return 0;
			};
			virtual void free(void* pointer)
			{
				::booldog::mem::cluster* cluster = get_free_cluster(pointer);
				cluster->free(pointer);
				::booldog::interlocked::exchange(&cluster->_locked, 0);
			}
			virtual size_t getsize( void* pointer )
			{
				::booldog::mem::cluster* cluster = get_free_cluster(pointer);
				size_t size = cluster->getsize(pointer);
				::booldog::interlocked::exchange(&cluster->_locked, 0);
				return size;
			};
			virtual size_t gettotalsize( void* pointer )
			{
				::booldog::mem::cluster* cluster = get_free_cluster(pointer);
				size_t size = cluster->gettotalsize(pointer);
				::booldog::interlocked::exchange(&cluster->_locked, 0);
				return size;
			};
			virtual void* tryrealloc( void* pointer , size_t size , bool free_if_cannot_alloc , void*& oldpointer
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::mem::cluster* cluster = get_free_cluster(pointer);
				if(cluster)
				{
					void* ptr = cluster->tryrealloc(pointer, size, free_if_cannot_alloc, oldpointer, debuginfo);
					::booldog::interlocked::exchange(&cluster->_locked, 0);
					return ptr;
				}
				return 0;
			};
			virtual void* realloc(void* pointer, size_t size, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				::booldog::mem::cluster* cluster = get_free_cluster(pointer);
				if(cluster)
				{
					void* ptr = cluster->realloc(pointer, size, debuginfo);
					::booldog::interlocked::exchange(&cluster->_locked, 0);
					return ptr;
				}
				return 0;
			}
			virtual bool check_consistency()
			{
				return _clusters[0].check_consistency();
			}
		};
		namespace single_threaded
		{
			template< size_t s >
			class stack : public ::booldog::stack_allocator
			{	
				::booldog::byte _data[ s + sizeof( ::booldog::mem::info4 ) ];
			public:				
				::booldog::mem::cluster _cluster;
				stack( void )
					: _cluster( _data , s + sizeof( ::booldog::mem::info4 ) )
				{
				};
				booinline void print( void )
				{
					_cluster.print();
				};
			public:
				virtual size_t available( void )
				{
					return _cluster.available();
				};
				void* begin( void )
				{
					return _cluster.begin();
				};
				void* end( void )
				{
					return _cluster.end();
				};
				virtual void* alloc( size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					return _cluster.alloc( size , debuginfo );
				};
				virtual void free( void* pointer )
				{
					_cluster.free( pointer );
				};
				virtual size_t getsize( void* pointer )
				{
					return _cluster.getsize( pointer );
				};
				virtual size_t gettotalsize( void* pointer )
				{
					return _cluster.gettotalsize( pointer );
				};
				virtual void* tryrealloc( void* pointer , size_t size , bool free_if_cannot_alloc , void*& oldpointer
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					return _cluster.tryrealloc( pointer , size , free_if_cannot_alloc , oldpointer , debuginfo );
				};
				virtual void* realloc( void* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					return _cluster.realloc( pointer , size , debuginfo );
				};
				virtual bool check_consistency(void)
				{
					return _cluster.check_consistency();
				}
			};
		}
	}
}
#endif
