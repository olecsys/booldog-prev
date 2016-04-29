#ifndef BOO_HOLDER_ALLOCATOR_H
#define BOO_HOLDER_ALLOCATOR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_allocator.h)
#include BOOLDOG_HEADER(boo_types.h)
#include BOOLDOG_HEADER(boo_utils.h)
#include BOOLDOG_HEADER(boo_mem.h)
namespace booldog
{
	namespace allocators
	{
		class holder : public ::booldog::allocator
		{
		public:
			::booldog::stack_allocator* stack;
			::booldog::heap_allocator* heap;
		public:
			holder( ::booldog::stack_allocator* pstack , ::booldog::heap_allocator* pheap )
				: heap( pheap ) , stack( pstack )
			{
			};
		public:
			virtual void* alloc( size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				void* pointer = stack->alloc( size , debuginfo );
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
					stack->free( pointer );
			};
			virtual size_t getsize( void* pointer )
			{
				if( pointer == 0 )
					return 0;
				::booldog::byte* ptr = (::booldog::byte*)pointer;
				ptr--;
				if( ::booldog::utils::get_bit( *ptr , BOOLDOG_MEM_INFO_HEAP ) )
					return heap->getsize( pointer );
				else
					return stack->getsize( pointer );
			};
			virtual size_t gettotalsize( void* pointer )
			{
				if( pointer == 0 )
					return 0;
				::booldog::byte* ptr = (::booldog::byte*)pointer;
				ptr--;
				if( ::booldog::utils::get_bit( *ptr , BOOLDOG_MEM_INFO_HEAP ) )
					return heap->gettotalsize( pointer );
				else
					return stack->gettotalsize( pointer );
			};
			virtual void* realloc( void* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				if( pointer == 0 )
					return alloc( size , debuginfo );
				else if( size == 0 )
				{
					free( pointer );
					return 0;
				}
				::booldog::byte* ptr = (::booldog::byte*)pointer;
				ptr--;
				if( ::booldog::utils::get_bit( *ptr , BOOLDOG_MEM_INFO_HEAP ) )
					return heap->realloc( pointer , size , debuginfo );
				else
				{
					void* oldpointer = 0;
					void* newpointer = stack->tryrealloc( pointer , size , false , oldpointer , debuginfo );
					if( newpointer == 0 )
					{
						newpointer = heap->realloc( newpointer , size , debuginfo );
						if( newpointer )
						{
							size_t oldsize = stack->getsize( oldpointer );
							::memcpy( newpointer , oldpointer , oldsize > size ? size : oldsize );
						}
						stack->free( oldpointer );
					}
					return newpointer;
				}
			};
		};
	};
};
#endif
