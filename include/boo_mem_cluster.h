#ifndef BOO_MEM_CLUSTER_H
#define BOO_MEM_CLUSTER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_allocator.h)
#include BOOLDOG_HEADER(boo_mem.h)
#include BOOLDOG_HEADER(boo_if.h)
#include BOOLDOG_HEADER(boo_utils.h)
#include BOOLDOG_HEADER(boo_bits_utils.h)

#include <stdio.h>
namespace booldog
{
	namespace mem
	{
		class cluster
		{
			::booldog::byte* _data;
			size_t _data_size;
			size_t _avail;
			::booldog::byte* _begin;
		public:
			cluster( ::booldog::byte* data , size_t data_size )
			{
				_data = data;
				_data_size = data_size;
				_avail = data_size;
				size_t s = data_size - sizeof( ::booldog::mem::info4 );
				_begin = _data;
				if( s < 0xff )
				{
					::booldog::mem::info1* info = (::booldog::mem::info1*)_begin;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO1 >::value;
					info->_size = (::booldog::byte)( _avail - sizeof( ::booldog::mem::info1 ) );
					_begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else if( s < 0xffff )
				{
					::booldog::mem::info2* info = (::booldog::mem::info2*)_begin;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO2 >::value;
					info->_size = (::booldog::ushort)( _avail - sizeof( ::booldog::mem::info2 ) );
					_begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else if( s < 0xffffffff )
				{
					::booldog::mem::info3* info = (::booldog::mem::info3*)_begin;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO3 >::value;
					info->_size = (::booldog::uint32)( _avail - sizeof( ::booldog::mem::info3 ) );
					_begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else if( s < 0xffffffffffffffff )
				{
					::booldog::mem::info4* info = (::booldog::mem::info4*)_begin;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO4 >::value;
					info->_size = _avail - sizeof( ::booldog::mem::info4 );
					_begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
			};
			booinline void print( void )
			{
				void* endptr = end();
				::booldog::byte* info = _data;
				size_t offsize = 0 , begin_size = 0;
				from_info( info , offsize , begin_size );
				for( ; ; )
				{
					info = info + offsize;
					if( info >= endptr )
					{
						_begin = info;
						break;
					}
					from_info( info , offsize , begin_size );
					if( ::booldog::utils::get_bit( info[ 1 ] , BOOLDOG_MEM_INFO_BUSY ) )
						printf( "size=%u, total=%u\n" , (::booldog::uint32)begin_size , (::booldog::uint32)offsize );
				}
			};
		private:
			booinline void from_info( ::booldog::byte* pointer , size_t& offsize , size_t& begin_size )
			{
				if( ::booldog::utils::get_bit( pointer[ 1 ] , BOOLDOG_MEM_INFO_USE_INFO1 ) )
				{
					offsize = sizeof( ::booldog::mem::info1 );
					::booldog::mem::info1* info = (::booldog::mem::info1*)pointer;
					offsize += info->_size;
					begin_size = info->_size;
				}
				else if( ::booldog::utils::get_bit( pointer[ 1 ] , BOOLDOG_MEM_INFO_USE_INFO2 ) )
				{
					offsize = sizeof( ::booldog::mem::info2 );
					::booldog::mem::info2* info = (::booldog::mem::info2*)pointer;
					offsize += info->_size;
					begin_size = info->_size;
				}
				else if( ::booldog::utils::get_bit( pointer[ 1 ] , BOOLDOG_MEM_INFO_USE_INFO3 ) )
				{
					offsize = sizeof( ::booldog::mem::info3 );
					::booldog::mem::info3* info = (::booldog::mem::info3*)pointer;
					offsize += info->_size;
					begin_size = info->_size;
				}
				else if( ::booldog::utils::get_bit( pointer[ 1 ] , BOOLDOG_MEM_INFO_USE_INFO4 ) )
				{
					offsize = sizeof( ::booldog::mem::info4 );
					::booldog::mem::info4* info = (::booldog::mem::info4*)pointer;
					offsize += (size_t)info->_size;
					begin_size = (size_t)info->_size;
				}
			};
			booinline void concat_unbusy_slices( ::booldog::byte* begin , size_t& size , size_t& begin_size  )
			{
				::booldog::byte* ptr = begin;
				void* endptr = end();
				for( ; ; )
				{
					ptr += size;
					if( ptr >= endptr || ::booldog::utils::get_bit( ptr[ 1 ] , BOOLDOG_MEM_INFO_BUSY ) )
					{
						size = ptr - begin;
						break;
					}
					if( ::booldog::utils::get_bit( ptr[ 1 ] , BOOLDOG_MEM_INFO_USE_INFO1 ) )
					{
						size = sizeof( ::booldog::mem::info1 );
						::booldog::mem::info1* info = (::booldog::mem::info1*)( ptr );
						size += info->_size;
					}
					else if( ::booldog::utils::get_bit( ptr[ 1 ] , BOOLDOG_MEM_INFO_USE_INFO2 ) )
					{
						size = sizeof( ::booldog::mem::info2 );
						::booldog::mem::info2* info = (::booldog::mem::info2*)( ptr );
						size += info->_size;
					}
					else if( ::booldog::utils::get_bit( ptr[ 1 ] , BOOLDOG_MEM_INFO_USE_INFO3 ) )
					{
						size = sizeof( ::booldog::mem::info3 );
						::booldog::mem::info3* info = (::booldog::mem::info3*)( ptr );
						size += info->_size;
					}
					else if( ::booldog::utils::get_bit( ptr[ 1 ] , BOOLDOG_MEM_INFO_USE_INFO4 ) )
					{
						size = sizeof( ::booldog::mem::info4 );
						::booldog::mem::info4* info = (::booldog::mem::info4*)( ptr );
						size += (size_t)info->_size;
					}
				}

				if( size < 0xff )
				{
					begin_size = size - sizeof( ::booldog::mem::info1 );
					::booldog::mem::info1* info = (::booldog::mem::info1*)begin;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO1 >::value;
					info->_size = (::booldog::byte)begin_size;
					begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else if( size < 0xffff )
				{
					begin_size = size - sizeof( ::booldog::mem::info2 );
					::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO2 >::value;
					info->_size = (::booldog::ushort)begin_size;
					begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else if( size < 0xffffffff )
				{
					begin_size = size - sizeof( ::booldog::mem::info3 );
					::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO3 >::value;
					info->_size = (::booldog::uint32)begin_size;
					begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else if( size < 0xffffffffffffffff )
				{
					begin_size = size - sizeof( ::booldog::mem::info4 );
					::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO4 >::value;
					info->_size = begin_size;
					begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
			};
			booinline ::booldog::byte* check_alloc( ::booldog::byte* begin , size_t& size , size_t& total )
			{
				size_t offsize = 0 , begin_size = 0;
				from_info( begin , offsize , begin_size );
				if( begin_size == size )
				{
					_avail -= total;
					begin_size = total - size;
					if( begin_size == sizeof( ::booldog::mem::info1 ) )
					{
						::booldog::mem::info1* info = (::booldog::mem::info1*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_USE_INFO1 , BOOLDOG_MEM_INFO_BUSY >::value;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					else if( begin_size == sizeof( ::booldog::mem::info2 ) )
					{
						::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_USE_INFO2 , BOOLDOG_MEM_INFO_BUSY >::value;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					else if( begin_size == sizeof( ::booldog::mem::info3 ) )
					{
						::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_USE_INFO3 , BOOLDOG_MEM_INFO_BUSY >::value;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					else if( begin_size == sizeof( ::booldog::mem::info4 ) )
					{
						::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_USE_INFO4 , BOOLDOG_MEM_INFO_BUSY >::value;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					return begin;
				}
				else if( offsize > total )
				{
					size_t diff = offsize - total;
						
					if( diff > sizeof( ::booldog::mem::info1 ) && diff - sizeof( ::booldog::mem::info1 ) < 0xff )
					{
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info1 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else if( diff > sizeof( ::booldog::mem::info2 ) && diff - sizeof( ::booldog::mem::info2 ) < 0xffff )
					{
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info2 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else if( diff > sizeof( ::booldog::mem::info3 ) && diff - sizeof( ::booldog::mem::info3 ) < 0xffffffff )
					{
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info3 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else if( diff > sizeof( ::booldog::mem::info4 ) && diff - sizeof( ::booldog::mem::info4 ) < 0xffffffffffffffff )
					{
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info4 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else
					{
						total = offsize;
						_avail -= total;

						size = begin_size;
						begin_size = offsize - size;
						if( begin_size == sizeof( ::booldog::mem::info1 ) )
						{
							::booldog::mem::info1* info = (::booldog::mem::info1*)begin;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_USE_INFO1 , BOOLDOG_MEM_INFO_BUSY >::value;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						else if( begin_size == sizeof( ::booldog::mem::info2 ) )
						{
							::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_USE_INFO2 , BOOLDOG_MEM_INFO_BUSY >::value;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						else if( begin_size == sizeof( ::booldog::mem::info3 ) )
						{
							::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_USE_INFO3 , BOOLDOG_MEM_INFO_BUSY >::value;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						else if( begin_size == sizeof( ::booldog::mem::info4 ) )
						{
							::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_USE_INFO4 , BOOLDOG_MEM_INFO_BUSY >::value;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						return begin;
					}
					_avail -= total;
					diff = total - size;
					if( diff == sizeof( ::booldog::mem::info1 ) )
					{
						::booldog::mem::info1* info = (::booldog::mem::info1*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO1 >::value;
						info->_size = (::booldog::byte)size;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					else if( diff == sizeof( ::booldog::mem::info2 ) )
					{
						::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO2 >::value;
						info->_size = (::booldog::ushort)size;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					else if( diff == sizeof( ::booldog::mem::info3 ) )
					{
						::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO3 >::value;
						info->_size = (::booldog::uint32)size;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					else if( diff == sizeof( ::booldog::mem::info4 ) )
					{
						::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO4 >::value;
						info->_size = size;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					return begin;
				}
				else
					return 0;
			};				
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
			size_t available( void )
			{
				return _avail;
			};
			void* begin( void )
			{
				return _begin;
			};
			void* end( void )
			{
				return &_data[ _data_size ];
			};
			void* alloc( size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				if( size % 4 )
					size = 4 * ( size / 4 ) + 4;

				debuginfo = debuginfo;
				if( _avail > 0 )
				{
					size_t offsize = 0 , begin_size = 0;
					from_info( _begin , offsize , begin_size );
					concat_unbusy_slices( _begin , offsize , begin_size );

					size_t total = size;
					if( size < 0xff )
						total += sizeof( ::booldog::mem::info1 );
					else if( size < 0xffff )
						total += sizeof( ::booldog::mem::info2 );
					else if( size < 0xffffffff )
						total += sizeof( ::booldog::mem::info3 );
					else if( size < 0xffffffffffffffff )
						total += sizeof( ::booldog::mem::info4 );
					::booldog::byte* begin = check_alloc( _begin , size , total );
					if( begin )
					{
						void* endptr = end();

						offsize = total;
						::booldog::byte* info = begin;
						for( ; ; )
						{
							info = info + offsize;
							if( info >= endptr || ::booldog::utils::get_bit( info[ 1 ] , BOOLDOG_MEM_INFO_BUSY ) == 0 )
							{
								_begin = info;
								break;
							}
							from_info( info , offsize , begin_size );
						}
					}
					else
					{
						void* endptr = end();
						::booldog::byte* info = _begin;
						from_info( info , offsize , begin_size );
						for( ; ; )
						{
							info = info + offsize;
							if( info >= endptr )
								break;
							from_info( info , offsize , begin_size );
							if( ::booldog::utils::get_bit( info[ 1 ] , BOOLDOG_MEM_INFO_BUSY ) == 0 )
							{
								concat_unbusy_slices( info , offsize , begin_size );
								begin = check_alloc( info , size , total );
							}
							if( begin )
								break;
						}
					}
					if( begin )
						return begin + total - size;
				}
				return 0;
			};
			void free( void* pointer )
			{
				size_t offsize = 0 , begin_size = 0;
				::booldog::byte* ptr = from_pointer( pointer , offsize , begin_size );
				if( ptr )
				{
					_avail += offsize;
					concat_unbusy_slices( ptr , offsize , begin_size );
					if( _begin > ptr )
						_begin = ptr;
				}
				else
				{
					int u = 5; u-- ; printf( "%d" , 120 / ( u - 4 ) );
				}
			};
			size_t getsize( void* pointer )
			{
				if( pointer == 0 )
					return 0;
				size_t offsize = 0 , size = 0;
				from_pointer( pointer , offsize , size );
				return size;
			};
			void* tryrealloc( void* pointer , size_t size , bool free_if_cannot_alloc , void*& oldpointer
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				if( size == 0 )
				{
					if( pointer )
						free( pointer );
					return 0;
				}
				if( pointer == 0 )
					return alloc( size , debuginfo );

				if( size % 4 )
					size = 4 * ( size / 4 ) + 4;

				size_t offsize = 0 , begin_size = 0;
				::booldog::byte* begin = from_pointer( pointer , offsize , begin_size );
				if( begin_size == size )
					return pointer;
				else if( begin_size > size )
				{
					size_t total = size;
					if( size < 0xff )
						total += sizeof( ::booldog::mem::info1 );
					else if( size < 0xffff )
						total += sizeof( ::booldog::mem::info2 );
					else if( size < 0xffffffff )
						total += sizeof( ::booldog::mem::info3 );
					else if( size < 0xffffffffffffffff )
						total += sizeof( ::booldog::mem::info4 );
						
					size_t old_offset = offsize - begin_size;
					size_t new_offset = total - size;
						
					size_t diff = offsize - total;
						
					if( diff > sizeof( ::booldog::mem::info1 ) && diff - sizeof( ::booldog::mem::info1 ) < 0xff )
					{
						if( old_offset != new_offset )
							::memmove( &begin[ new_offset ] , &begin[ old_offset ] , begin_size );
						_avail += diff;
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info1 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else if( diff > sizeof( ::booldog::mem::info2 ) && diff - sizeof( ::booldog::mem::info2 ) < 0xffff )
					{
						if( old_offset != new_offset )
							::memmove( &begin[ new_offset ] , &begin[ old_offset ] , size );
						_avail += diff;
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info2 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else if( diff > sizeof( ::booldog::mem::info3 ) && diff - sizeof( ::booldog::mem::info3 ) < 0xffffffff )
					{
						if( old_offset != new_offset )
							::memmove( &begin[ new_offset ] , &begin[ old_offset ] , size );
						_avail += diff;
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info3 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else if( diff > sizeof( ::booldog::mem::info4 ) && diff - sizeof( ::booldog::mem::info4 ) < 0xffffffffffffffff )
					{
						if( old_offset != new_offset )
							::memmove( &begin[ new_offset ] , &begin[ old_offset ] , size );
						_avail += diff;
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info4 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else
						return pointer;
					if( _begin > &begin[ total ] )
						_begin = &begin[ total ];
					if( new_offset == sizeof( ::booldog::mem::info1 ) )
					{
						::booldog::mem::info1* info = (::booldog::mem::info1*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO1 >::value;
						info->_size = (::booldog::byte)size;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					else if( new_offset == sizeof( ::booldog::mem::info2 ) )
					{
						::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO2 >::value;
						info->_size = (::booldog::ushort)size;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					else if( new_offset == sizeof( ::booldog::mem::info3 ) )
					{
						::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO3 >::value;
						info->_size = (::booldog::uint32)size;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					else if( new_offset == sizeof( ::booldog::mem::info4 ) )
					{
						::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO4 >::value;
						info->_size = size;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					return begin + new_offset;
				}
				else
				{
					void* endptr = end();
					::booldog::byte* info = begin + offsize;
					if( info >= endptr || ::booldog::utils::get_bit( info[ 1 ] , BOOLDOG_MEM_INFO_BUSY ) )
					{
						void* new_pointer = this->alloc( size , debuginfo );
						if( new_pointer )
							::memcpy( new_pointer , pointer , begin_size );
						if( new_pointer == 0 )
						{
							oldpointer = pointer;
							if( free_if_cannot_alloc )
								this->free( pointer );
						}
						else
							this->free( pointer );
						return new_pointer;
					}
					else
					{
						size_t info_offsize = 0 , info_begin_size = 0;
						from_info( info , info_offsize , info_begin_size );
						concat_unbusy_slices( info , info_offsize , info_begin_size );
							
						_avail -= info_offsize;
						size_t diff = offsize + info_offsize;
						if( diff > sizeof( ::booldog::mem::info1 ) && diff - sizeof( ::booldog::mem::info1 ) < 0xff )
						{
							info_offsize = diff;
							info_begin_size = diff - sizeof( ::booldog::mem::info1 );
						}
						else if( diff > sizeof( ::booldog::mem::info2 ) && diff - sizeof( ::booldog::mem::info2 ) < 0xffff )
						{
							info_offsize = diff;
							info_begin_size = diff - sizeof( ::booldog::mem::info2 );
						}
						else if( diff > sizeof( ::booldog::mem::info3 ) && diff - sizeof( ::booldog::mem::info3 ) < 0xffffffff )
						{
							info_offsize = diff;
							info_begin_size = diff - sizeof( ::booldog::mem::info3 );
						}
						else if( diff > sizeof( ::booldog::mem::info4 ) && diff - sizeof( ::booldog::mem::info4 ) < 0xffffffffffffffff )
						{
							info_offsize = diff;
							info_begin_size = diff - sizeof( ::booldog::mem::info4 );
						}							
						size_t old_offset = offsize - begin_size;
						size_t new_offset = info_offsize - info_begin_size;
						if( old_offset != new_offset )
							::memmove( &begin[ new_offset ] , &begin[ old_offset ] , begin_size );
						if( new_offset == sizeof( ::booldog::mem::info1 ) )
						{
							::booldog::mem::info1* info = (::booldog::mem::info1*)begin;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO1 >::value;
							info->_size = (::booldog::byte)info_begin_size;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						else if( new_offset == sizeof( ::booldog::mem::info2 ) )
						{
							::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO2 >::value;
							info->_size = (::booldog::ushort)info_begin_size;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						else if( new_offset == sizeof( ::booldog::mem::info3 ) )
						{
							::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO3 >::value;
							info->_size = (::booldog::uint32)info_begin_size;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						else if( new_offset == sizeof( ::booldog::mem::info4 ) )
						{
							::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO4 >::value;
							info->_size = info_begin_size;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						if( _begin > begin && _begin < &begin[ info_offsize ] )
						{
							::booldog::byte* info = begin;
							for( ; ; )
							{
								info = info + info_offsize;
								if( info >= endptr || ::booldog::utils::get_bit( info[ 1 ] , BOOLDOG_MEM_INFO_BUSY ) == 0 )
								{
									_begin = info;
									break;
								}
								from_info( info , info_offsize , info_begin_size );
							}
						}
						return this->tryrealloc( begin + new_offset , size , free_if_cannot_alloc , oldpointer , debuginfo );
					}
				}
			};
			void* realloc( void* pointer , size_t size , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				void* oldpointer = 0;
				return tryrealloc( pointer , size , true , oldpointer , debuginfo );
			};
		};
	};
};
#endif
