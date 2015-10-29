#ifndef BOO_NEW_H
#define BOO_NEW_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_allocator.h>
#include <boo_types.h>
namespace booldog
{
	template< class T >
	booinline T* create( const char* file , int line , ::booldog::allocator* allocator )
	{	
		return new ( allocator->alloc( sizeof( T ) , file , line ) )T;
	};
	template< class T >
	booinline void destroy( T* object , ::booldog::allocator* allocator )
	{
		object->~T();
		allocator->free( object );
	};
};
#endif
