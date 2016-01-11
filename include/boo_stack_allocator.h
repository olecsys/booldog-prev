#ifndef BOO_STACK_ALLOCATOR_H
#define BOO_STACK_ALLOCATOR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_mem_cluster.h>
namespace booldog
{
	namespace allocators
	{
		template< size_t s >
		class stack : public ::booldog::allocator
		{
			::booldog::byte _data[ s + sizeof( ::booldog::mem::info4 ) ];
			::booldog::mem::cluster _cluster;
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
				return _cluster.alloc( size , debuginfo );
			};
			virtual void free( void* pointer )
			{
				_cluster.free( pointer );
			};
			virtual void* realloc( void* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				return _cluster.realloc( pointer , size , debuginfo );
			};
		};
	};
};
#endif
