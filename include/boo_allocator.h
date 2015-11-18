#ifndef BOO_ALLOCATOR_H
#define BOO_ALLOCATOR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stddef.h>
#include <boo_debug_info.h>
namespace booldog
{
	class allocator
	{
	public:
		virtual void* realloc( void* pointer , size_t size , ::booldog::debug::info* debuginfo = 0 ) = 0;
		virtual void* alloc( size_t size , ::booldog::debug::info* debuginfo = 0 ) = 0;
		virtual void free( void* pointer ) = 0;
		template< class booclass >
		booclass* realloc_array( booclass* pointer , size_t size , ::booldog::debug::info* debuginfo = 0 )
		{
			return (booclass*)realloc( pointer , size * sizeof( booclass ) , debuginfo );
		}; 
	};
	booldog::allocator* _allocator = 0;
};
#endif