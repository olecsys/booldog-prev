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
#include BOOLDOG_HEADER(boo_rdwrlock.h)
namespace booldog
{
	namespace allocators
	{
		template< size_t s >
		class stack : public ::booldog::stack_allocator
		{
			::booldog::byte _data[ s + sizeof( ::booldog::mem::info4 ) ];
			::booldog::mem::cluster _cluster;
			::booldog::threading::rdwrlock _lock;
		public:
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
				_lock.wlock( debuginfo );
				void* ptr = _cluster.alloc( size , debuginfo );
				_lock.wunlock( debuginfo );
				return ptr;
			};
			virtual void free( void* pointer )
			{
				_lock.wlock( debuginfo_macros );
				_cluster.free( pointer );
				_lock.wunlock( debuginfo_macros );
			};
			virtual size_t getsize( void* pointer )
			{
				_lock.wlock( debuginfo_macros );
				size_t size = _cluster.getsize( pointer );
				_lock.wunlock( debuginfo_macros );
				return size;
			};
			virtual size_t gettotalsize( void* pointer )
			{
				_lock.wlock( debuginfo_macros );
				size_t size = _cluster.gettotalsize( pointer );
				_lock.wunlock( debuginfo_macros );
				return size;
			};
			virtual void* tryrealloc( void* pointer , size_t size , bool free_if_cannot_alloc , void*& oldpointer
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				_lock.wlock( debuginfo );
				void* ptr = _cluster.tryrealloc( pointer , size , free_if_cannot_alloc , oldpointer , debuginfo );
				_lock.wunlock( debuginfo );
				return ptr;
			};
			virtual void* realloc( void* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				_lock.wlock( debuginfo );
				void* ptr = _cluster.realloc( pointer , size , debuginfo );
				_lock.wunlock( debuginfo );
				return ptr;
			};
			virtual bool check_consistency(void)
			{
				return _cluster.check_consistency();
			};
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
				};
			};
		};
	};
};
#endif
