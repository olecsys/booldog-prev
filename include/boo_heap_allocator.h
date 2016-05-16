#ifndef BOO_HEAP_ALLOCATOR_H
#define BOO_HEAP_ALLOCATOR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_mem_cluster.h)
#include BOOLDOG_HEADER(boo_interlocked.h)
#include BOOLDOG_HEADER(boo_bits_utils.h)
#include <stdlib.h>
namespace booldog
{
	namespace allocators
	{
		namespace easy
		{
			class heap : public ::booldog::heap_allocator
			{
				::booldog::interlocked::atomic _size_of_allocated_memory;
			private:
				booinline static ::booldog::byte* from_pointer( void* pointer , size_t& offsize , size_t& begin_size )
				{
					::booldog::byte* ptr = (::booldog::byte*)pointer;
					ptr--;
					if( ::booldog::utils::get_bit( *ptr , BOOLDOG_MEM_INFO_BUSY ) )
					{
						offsize = 0 , begin_size = 0;
						if( ::booldog::utils::get_bit( *ptr , BOOLDOG_MEM_INFO_USE_INFO1 ) )
						{
							offsize = sizeof( ::booldog::mem::info1 );
							ptr = ptr + 1 - offsize;
							::booldog::mem::info1* info = (::booldog::mem::info1*)( ptr );
							offsize += info->_size;
							begin_size = info->_size;
						}
						else if( ::booldog::utils::get_bit( *ptr , BOOLDOG_MEM_INFO_USE_INFO2 ) )
						{
							offsize = sizeof( ::booldog::mem::info2 );
							ptr = ptr + 1 - offsize;
							::booldog::mem::info2* info = (::booldog::mem::info2*)( ptr );
							offsize += info->_size;
							begin_size = info->_size;
						}
						else if( ::booldog::utils::get_bit( *ptr , BOOLDOG_MEM_INFO_USE_INFO3 ) )
						{
							offsize = sizeof( ::booldog::mem::info3 );
							ptr = ptr + 1 - offsize;
							::booldog::mem::info3* info = (::booldog::mem::info3*)( ptr );
							offsize += info->_size;
							begin_size = info->_size;
						}
						else if( ::booldog::utils::get_bit( *ptr , BOOLDOG_MEM_INFO_USE_INFO4 ) )
						{
							offsize = sizeof( ::booldog::mem::info4 );
							ptr = ptr + 1 - offsize;
							::booldog::mem::info4* info = (::booldog::mem::info4*)( ptr );
							offsize += (size_t)info->_size;
							begin_size = (size_t)info->_size;
						}
						return ptr;
					}
					return 0;
				};
			public:
				heap( void )
					: _size_of_allocated_memory( 0 )
				{
				};
				~heap( void )
				{
					if( ::booldog::interlocked::compare_exchange( &_size_of_allocated_memory , 0 , 0 ) > 0 )
					{
						int u = 5; u-- ; printf( "%d" , 120 / ( u - 4 ) );
					}
				};
				virtual size_t size_of_allocated_memory( void )
				{
					return ::booldog::interlocked::compare_exchange( &_size_of_allocated_memory , 0 , 0 );
				};
			private:
				void* palloc( void* pointer , size_t pointertotal , size_t pointersize , size_t size
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					if( size % 4 )
						size = 4 * ( size / 4 ) + 4;

					debuginfo = debuginfo;
					size_t pointerinfosize = pointertotal - pointersize;
					size_t total = size , oldsize = size;
					if( size < UINT8_MAX )
						total += sizeof( ::booldog::mem::info1 );
					else if( size < UINT16_MAX )
						total += sizeof( ::booldog::mem::info2 );
					else if( size < UINT32_MAX )
						total += sizeof( ::booldog::mem::info3 );
					else
						total += sizeof( ::booldog::mem::info4 );
					size_t begin_size = total - size;
					if( pointerinfosize > begin_size )
					{
						size += pointerinfosize - begin_size;
						total = size;
						if( size < UINT8_MAX )
							total += sizeof( ::booldog::mem::info1 );
						else if( size < UINT16_MAX )
							total += sizeof( ::booldog::mem::info2 );
						else if( size < UINT32_MAX )
							total += sizeof( ::booldog::mem::info3 );
						else
							total += sizeof( ::booldog::mem::info4 );
						begin_size = total - size;
					}

					::booldog::byte* begin = (::booldog::byte*)::realloc( pointer , total );
					if( begin )
					{
						if( total > pointertotal )
							::booldog::interlocked::exchange_add( &_size_of_allocated_memory 
							, (::booldog::interlocked::atomic_return)( total - pointertotal ) );
						else
							::booldog::interlocked::exchange_subtract( &_size_of_allocated_memory 
							, (::booldog::interlocked::atomic_return)( pointertotal - total ) );
						if( pointerinfosize != begin_size )
							memmove( &begin[ begin_size ] , &begin[ pointerinfosize ] , pointertotal > total 
							? oldsize : pointersize );

						if( size < UINT8_MAX )
						{
							::booldog::mem::info1* info = (::booldog::mem::info1*)begin;
							info->_size = (::booldog::byte)size;
							info->_check = 86;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_HEAP , BOOLDOG_MEM_INFO_USE_INFO1 , BOOLDOG_MEM_INFO_BUSY >::value;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						else if( size < UINT16_MAX )
						{
							::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
							info->_check = 86;
							info->_size = (::booldog::ushort)size;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_HEAP , BOOLDOG_MEM_INFO_USE_INFO2 , BOOLDOG_MEM_INFO_BUSY >::value;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						else if( size < UINT32_MAX )
						{
							::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
							info->_check = 86;
							info->_size = (::booldog::uint32)size;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_HEAP , BOOLDOG_MEM_INFO_USE_INFO3 , BOOLDOG_MEM_INFO_BUSY >::value;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						else
						{
							::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
							info->_check = 86;
							info->_size = size;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_HEAP , BOOLDOG_MEM_INFO_USE_INFO4 , BOOLDOG_MEM_INFO_BUSY >::value;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						return begin + begin_size;
					}
					::booldog::interlocked::exchange_subtract( &_size_of_allocated_memory 
						, (::booldog::interlocked::atomic_return)pointertotal );
					return 0;
				};
			public:
				virtual void* alloc( size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					return palloc( 0 , 0 , 0 , size , debuginfo );
				};
				virtual void free( void* pointer )
				{
					size_t offsize = 0 , begin_size = 0;
					::booldog::byte* ptr = from_pointer( pointer , offsize , begin_size );
					if( ptr )
					{
						::free( ptr );
						::booldog::interlocked::exchange_subtract( &_size_of_allocated_memory 
							, (booldog::interlocked::atomic_return)offsize );
					}
					else
					{
						int u = 5; u-- ; printf( "%d" , 120 / ( u - 4 ) );
					}
				};
				virtual size_t getsize( void* pointer )
				{
					if( pointer == 0 )
						return 0;
					size_t offsize = 0 , size = 0;
					from_pointer( pointer , offsize , size );
					return size;
				};
				virtual size_t gettotalsize( void* pointer )
				{
					if( pointer == 0 )
						return 0;
					size_t offsize = 0 , size = 0;
					from_pointer( pointer , offsize , size );
					return offsize;
				};
				virtual void* realloc( void* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					if( size == 0 )
					{
						if( pointer )
							free( pointer );
						return 0;
					}
					if( pointer == 0 )
						return palloc( 0 , 0 , 0 , size , debuginfo );

					if( size % 4 )
						size = 4 * ( size / 4 ) + 4;

					size_t offsize = 0 , begin_size = 0;
					from_pointer( pointer , offsize , begin_size );
					if( begin_size == size )
						return pointer;
					return palloc( ((::booldog::byte*)pointer) - ( offsize - begin_size ) , offsize , begin_size , size , debuginfo );
				};
			};
		};
	};
};
#endif
