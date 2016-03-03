#ifndef BOO_STACK_ALLOCATOR_H
#define BOO_STACK_ALLOCATOR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_mem_cluster.h)
#include BOOLDOG_HEADER(boo_threading_utils.h)
#ifndef BOOLDOG_STACK_ALLOCATOR_NOT_USE_RDWRLOCK
#include BOOLDOG_HEADER(boo_rdwrlock.h)
#endif
namespace booldog
{
	namespace allocators
	{
		template< size_t s >
		class stack : public ::booldog::stack_allocator
		{
			::booldog::pid_t _owner_thread_id;
			::booldog::byte _data[ s + sizeof( ::booldog::mem::info4 ) ];
			::booldog::mem::cluster _cluster;
#ifndef BOOLDOG_STACK_ALLOCATOR_NOT_USE_RDWRLOCK
			::booldog::threading::rdwrlock _lock;
#endif
		public:
			stack( ::booldog::pid_t owner_thread_id = 0 )
				: _owner_thread_id( owner_thread_id ) , _cluster( _data , s + sizeof( ::booldog::mem::info4 ) )
			{
			};
			booinline void print( void )
			{
				_cluster.print();
			};
		public:
			size_t available( void )
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
#ifndef BOOLDOG_STACK_ALLOCATOR_NOT_USE_RDWRLOCK
				void* ptr = 0;
				if( _owner_thread_id == 0 || _owner_thread_id == ::booldog::threading::threadid() )
				{
					_lock.rlock( debuginfo );
					ptr = _cluster.alloc( size , debuginfo );
					_lock.runlock( debuginfo );
				}
				else
				{
					_lock.wlock( debuginfo );
					ptr = _cluster.alloc( size , debuginfo );
					_lock.wunlock( debuginfo );
				}
				return ptr;
#else
				if( _owner_thread_id == 0 || _owner_thread_id == ::booldog::threading::threadid() )
					return _cluster.alloc( size , debuginfo );
				else
					return 0;
#endif
			};
			virtual void free( void* pointer )
			{
#ifndef BOOLDOG_STACK_ALLOCATOR_NOT_USE_RDWRLOCK
				if( _owner_thread_id == 0 || _owner_thread_id == ::booldog::threading::threadid() )
				{
					_lock.rlock( debuginfo_macros );
					_cluster.free( pointer );
					_lock.runlock( debuginfo_macros );
				}
				else
				{
					_lock.wlock( debuginfo_macros );
					_cluster.free( pointer );
					_lock.wunlock( debuginfo_macros );
				}
#else
				_cluster.free( pointer );
#endif
			};
			virtual size_t getsize( void* pointer )
			{
#ifndef BOOLDOG_STACK_ALLOCATOR_NOT_USE_RDWRLOCK
				size_t size = 0;
				if( _owner_thread_id == 0 || _owner_thread_id == ::booldog::threading::threadid() )
				{
					_lock.rlock( debuginfo_macros );
					size = _cluster.getsize( pointer );
					_lock.runlock( debuginfo_macros );
				}
				else
				{
					_lock.wlock( debuginfo_macros );
					size = _cluster.getsize( pointer );
					_lock.wunlock( debuginfo_macros );
				}
				return size;
#else
				return _cluster.getsize( pointer );
#endif
			};
			virtual void* tryrealloc( void* pointer , size_t size , bool free_if_cannot_alloc , void*& oldpointer
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
#ifndef BOOLDOG_STACK_ALLOCATOR_NOT_USE_RDWRLOCK
				void* ptr = 0;
				if( _owner_thread_id == 0 || _owner_thread_id == ::booldog::threading::threadid() )
				{
					_lock.rlock( debuginfo );
					ptr = _cluster.tryrealloc( pointer , size , free_if_cannot_alloc , oldpointer , debuginfo );
					_lock.runlock( debuginfo );
				}
				else
				{
					_lock.wlock( debuginfo );
					ptr = _cluster.tryrealloc( pointer , size , free_if_cannot_alloc , oldpointer , debuginfo );
					_lock.wunlock( debuginfo );
				}
				return ptr;
#else
				if( _owner_thread_id == 0 || _owner_thread_id == ::booldog::threading::threadid() )
					return _cluster.tryrealloc( pointer , size , free_if_cannot_alloc , oldpointer , debuginfo );
				else
				{
					oldpointer = pointer;
					return 0;
				}
#endif
			};
			virtual void* realloc( void* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
#ifndef BOOLDOG_STACK_ALLOCATOR_NOT_USE_RDWRLOCK
				void* ptr = 0;
				if( _owner_thread_id == 0 || _owner_thread_id == ::booldog::threading::threadid() )
				{
					_lock.rlock( debuginfo );
					ptr = _cluster.realloc( pointer , size , debuginfo );
					_lock.runlock( debuginfo );
				}
				else
				{
					_lock.wlock( debuginfo );
					ptr = _cluster.realloc( pointer , size , debuginfo );
					_lock.wunlock( debuginfo );
				}
				return ptr;
#else
				if( _owner_thread_id == 0 || _owner_thread_id == ::booldog::threading::threadid() )
					return _cluster.realloc( pointer , size , debuginfo );
				else
					return 0;
#endif
			};
		};
	};
};
#endif
