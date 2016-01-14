#ifndef BOO_STACK_ALLOCATOR_H
#define BOO_STACK_ALLOCATOR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_mem_cluster.h>
#include <boo_threading_utils.h>
namespace booldog
{
	namespace allocators
	{
		template< size_t s >
		class stack : public ::booldog::allocator
		{
			::booldog::pid_t _owner_thread_id;
			::booldog::byte _data[ s + sizeof( ::booldog::mem::info4 ) ];
			::booldog::mem::cluster _cluster;
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
				if( _owner_thread_id == 0 || _owner_thread_id == ::booldog::threading::thread_id() )
					return _cluster.alloc( size , debuginfo );
				else
					return 0;
			};
			virtual void free( void* pointer )
			{
				_cluster.free( pointer );
			};
			virtual void* realloc( void* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				if( _owner_thread_id == 0 || _owner_thread_id == ::booldog::threading::thread_id() )
					return _cluster.realloc( pointer , size , debuginfo );
				else
					return 0;
			};
		};
	};
};
#endif
