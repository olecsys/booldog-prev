#ifndef BOO_ALLOCATOR_H
#define BOO_ALLOCATOR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <new>
#include <stddef.h>
#include "boo_debug_info.h"
namespace booldog
{
	class allocator
	{
	public:
		virtual size_t getsize( void* pointer ) = 0;
		virtual void* realloc( void* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros ) = 0;
		virtual void* alloc( size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros ) = 0;
		virtual void free( void* pointer ) = 0;
		template< class booclass >
		booclass* realloc_array( booclass* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			return (booclass*)realloc( pointer , size * sizeof( booclass ) , debuginfo );
		};
		template< class booclass >
		booclass* create( const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			void* pointer = this->alloc( sizeof( booclass ) , debuginfo );
			if( pointer )
				return new ( pointer )booclass;
			return 0;
		};
		template< class booclass , class P0 >
		booclass* create( P0 param0 , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{	
			void* pointer = this->alloc( sizeof( booclass ) , debuginfo );
			if( pointer )
				return new ( pointer )booclass( param0 );
			return 0;
		};
		template< class booclass , class P0 , class P1 >
		booclass* create( P0 param0 , P1 param1 , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{	
			void* pointer = this->alloc( sizeof( booclass ) , debuginfo );
			if( pointer )
				return new ( pointer )booclass( param0 , param1 );
			return 0;
		};
		template< class booclass , class P0 , class P1 , class P2 >
		booclass* create( P0 param0 , P1 param1 , P2 param2 , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{	
			void* pointer = this->alloc( sizeof( booclass ) , debuginfo );
			if( pointer )
				return new ( pointer )booclass( param0 , param1 , param2 );
			return 0;
		};
		template< class booclass , class P0 , class P1 , class P2 , class P3>
		booclass* create( P0 param0 , P1 param1 , P2 param2 , P3 param3 , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{	
			void* pointer = this->alloc( sizeof( booclass ) , debuginfo );
			if( pointer )
				return new ( pointer )booclass( param0 , param1 , param2 , param3 );
			return 0;
		};
		template< class booclass , class P0 , class P1 , class P2 , class P3 , class P4 >
		booclass* create( P0 param0 , P1 param1 , P2 param2 , P3 param3 , P4 param4 
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{	
			void* pointer = this->alloc( sizeof( booclass ) , debuginfo );
			if( pointer )
				return new ( pointer )booclass( param0 , param1 , param2 , param3 , param4 );
			return 0;
		};
		template< class booclass , class P0 , class P1 , class P2 , class P3 , class P4 , class P5 >
		booclass* create( P0 param0 , P1 param1 , P2 param2 , P3 param3 , P4 param4 , P5 param5
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{	
			void* pointer = this->alloc( sizeof( booclass ) , debuginfo );
			if( pointer )
				return new ( pointer )booclass( param0 , param1 , param2 , param3 , param4 , param5 );
			return 0;
		};
		template< class booclass , class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 >
		booclass* create( P0 param0 , P1 param1 , P2 param2 , P3 param3 , P4 param4 , P5 param5 , P6 param6 
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{	
			void* pointer = this->alloc( sizeof( booclass ) , debuginfo );
			if( pointer )
				return new ( pointer )booclass( param0 , param1 , param2 , param3 , param4 , param5 , param6 );
			return 0;
		};
		template< class booclass , class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 >
		booclass* create( P0 param0 , P1 param1 , P2 param2 , P3 param3 , P4 param4 , P5 param5 , P6 param6 , P7 param7 
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{	
			void* pointer = this->alloc( sizeof( booclass ) , debuginfo );
			if( pointer )
				return new ( pointer )booclass( param0 , param1 , param2 , param3 , param4 , param5 , param6 , param7 );
			return 0;
		};
		template< class booclass , class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 >
		booclass* create( P0 param0 , P1 param1 , P2 param2 , P3 param3 , P4 param4 , P5 param5 , P6 param6 , P7 param7 , P8 param8
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{	
			void* pointer = this->alloc( sizeof( booclass ) , debuginfo );
			if( pointer )
				return new ( pointer )booclass( param0 , param1 , param2 , param3 , param4 , param5 , param6 , param7 , param8 );
			return 0;
		};
		template< class booclass >
		void destroy( booclass* object )
		{
			object->~booclass();
			this->free( object );
		};
		virtual size_t gettotalsize( void* pointer ) = 0;
		virtual bool check_consistency(void){return true;};
	};
	class heap_allocator : public ::booldog::allocator
	{
	public:
		virtual size_t size_of_allocated_memory( void ) = 0;
	};
	class stack_allocator : public ::booldog::allocator
	{
	public:
		virtual void* tryrealloc( void* pointer , size_t size , bool free_if_cannot_alloc , void*& oldpointer
			, const ::booldog::debug::info& debuginfo = debuginfo_macros ) = 0;
		virtual size_t available( void ) = 0;
	};
};
#endif