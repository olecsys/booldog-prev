#ifndef BOO_ALLOCATOR_H
#define BOO_ALLOCATOR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stddef.h>
namespace booldog
{
	class allocator
	{
	public:
		virtual void* realloc( void* pointer , size_t size , const char* file , int line ) = 0;
		virtual void* alloc( size_t size , const char* file , int line ) = 0;
		virtual void free( void* pointer ) = 0;
	};
	booldog::allocator* _allocator = 0;
};
#endif
