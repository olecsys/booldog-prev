#ifndef BOO_MIXED_ALLOCATOR_H
#define BOO_MIXED_ALLOCATOR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_stack_allocator.h>
namespace booldog
{
	namespace allocators
	{
		template< size_t s >
		class mixed : public ::booldog::allocator
		{
		public:
			::booldog::allocators::stack< s > stack;
			::booldog::heap_allocator* heap;
		public:
			mixed( ::booldog::heap_allocator* pheap , ::booldog::pid_t owner_thread_id = 0 )
				: heap( pheap ) , stack( owner_thread_id )
			{
			};
		public:
			virtual void* alloc( size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				void* pointer = stack.alloc( size , debuginfo );
				if( pointer == 0 )
					pointer = heap->alloc( size , debuginfo );
				return pointer;
			};
			virtual void free( void* pointer )
			{
				::booldog::byte* ptr = (::booldog::byte*)pointer;
				ptr--;
				if( ::booldog::utils::get_bit( *ptr , BOOLDOG_MEM_INFO_HEAP ) )
					heap->free( pointer );
				else
					stack.free( pointer );
			};
			virtual void* realloc( void* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				if( pointer == 0 )
					return alloc( size , debuginfo );
				::booldog::byte* ptr = (::booldog::byte*)pointer;
				ptr--;
				if( ::booldog::utils::get_bit( *ptr , BOOLDOG_MEM_INFO_HEAP ) )
					return heap->realloc( pointer , size , debuginfo );
				else
					return stack.realloc( pointer , size , debuginfo );
			};
		};
	};
};
#endif
