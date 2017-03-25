#ifndef BOO_MIXED_ALLOCATOR_H
#define BOO_MIXED_ALLOCATOR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_stack_allocator.h"
#include "boo_holder_allocator.h"
namespace booldog
{
	namespace allocators
	{
		template< size_t s, size_t cluster_count = 32 >
		class mixed : public ::booldog::allocator
		{
		public:
			::booldog::allocators::stack< s, cluster_count > stack;
			::booldog::allocators::holder holder;
		public:
			mixed(::booldog::heap_allocator* pheap)
				: holder(&stack, pheap)
			{
			}
		public:
			virtual void* alloc( size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				return holder.alloc( size , debuginfo );
			};
			virtual void free( void* pointer )
			{
				holder.free( pointer );
			};
			virtual size_t getsize( void* pointer )
			{
				return holder.getsize( pointer );
			};
			virtual size_t gettotalsize( void* pointer )
			{
				return holder.gettotalsize( pointer );
			};
			virtual void* realloc( void* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				return holder.realloc( pointer , size , debuginfo );
			};
			virtual bool check_consistency(void)
			{
				return &stack == holder.stack && stack.check_consistency();
			};
		};
		namespace single_threaded
		{
			template< size_t s >
			class mixed : public ::booldog::allocator
			{
			public:
				::booldog::allocators::single_threaded::stack< s > stack;
				::booldog::allocators::holder holder;
			public:
				mixed( ::booldog::heap_allocator* pheap )
					: holder( &stack , pheap )
				{
				};
			public:
				virtual void* alloc( size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					return holder.alloc( size , debuginfo );
				};
				virtual void free( void* pointer )
				{
					holder.free( pointer );
				};
				virtual size_t getsize( void* pointer )
				{
					return holder.getsize( pointer );
				};
				virtual size_t gettotalsize( void* pointer )
				{
					return holder.gettotalsize( pointer );
				};
				virtual void* realloc( void* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					return holder.realloc( pointer , size , debuginfo );
				};
				virtual bool check_consistency(void)
				{
					return &stack == holder.stack && stack.check_consistency();
				};
			};
		};
	};
};
#endif
