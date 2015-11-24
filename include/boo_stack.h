#ifndef BOO_STACK_H
#define BOO_STACK_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_allocator.h>
#include <boo_mem.h>
#include <boo_if.h>
namespace booldog
{
	namespace allocators
	{
		namespace stack
		{
			template< size_t s >
			class simple : public ::booldog::allocator
			{
				::booldog::byte _data[ s + sizeof( ::booldog::mem::info4 ) ];
				size_t _avail;
				::booldog::byte* _begin;
			public:
				simple( void )
				{
					_avail = s + sizeof( ::booldog::mem::info4 );
					_begin = _data;
					if( ::booldog::compile::If< s < 0xff >::test() )
					{
						::booldog::mem::info1* info = (::booldog::mem::info1*)_begin;
						info->_flags = 0;
						::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO1 );
						info->_size = (::booldog::byte)( _avail - sizeof( ::booldog::mem::info1 ) );
						info->_eflags = info->_flags;
					}
					else if( ::booldog::compile::If< s < 0xffff >::test() )
					{
						::booldog::mem::info2* info = (::booldog::mem::info2*)_begin;
						info->_flags = 0;
						::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO2 );
						info->_size = (::booldog::ushort)( _avail - sizeof( ::booldog::mem::info2 ) );
						info->_eflags = info->_flags;
					}
					else if( ::booldog::compile::If< s < 0xffffffff >::test() )
					{
						::booldog::mem::info3* info = (::booldog::mem::info3*)_begin;
						info->_flags = 0;
						::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO3 );
						info->_size = (::booldog::uint32)( _avail - sizeof( ::booldog::mem::info3 ) );
						info->_eflags = info->_flags;
					}
					else if( ::booldog::compile::If< s < 0xffffffffffffffff >::test() )
					{
						::booldog::mem::info4* info = (::booldog::mem::info4*)_begin;
						info->_flags = 0;
						::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO4 );
						info->_size = _avail - sizeof( ::booldog::mem::info4 );
						info->_eflags = info->_flags;
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
						info->_flags = 0;
						::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO1 );
						info->_size = (::booldog::byte)begin_size;
						info->_eflags = info->_flags;
					}
					else if( size < 0xffff )
					{
						begin_size = size - sizeof( ::booldog::mem::info2 );
						::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
						info->_flags = 0;
						::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO2 );
						info->_size = (::booldog::ushort)begin_size;
						info->_eflags = info->_flags;
					}
					else if( size < 0xffffffff )
					{
						begin_size = size - sizeof( ::booldog::mem::info3 );
						::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
						info->_flags = 0;
						::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO3 );
						info->_size = (::booldog::uint32)begin_size;
						info->_eflags = info->_flags;
					}
					else if( size < 0xffffffffffffffff )
					{
						begin_size = size - sizeof( ::booldog::mem::info4 );
						::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
						info->_flags = 0;
						::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO4 );
						info->_size = begin_size;
						info->_eflags = info->_flags;
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
							info->_flags = 0;
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO1 );
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
							info->_eflags = info->_flags;
						}
						else if( begin_size == sizeof( ::booldog::mem::info2 ) )
						{
							::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
							info->_flags = 0;
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO2 );
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
							info->_eflags = info->_flags;
						}
						else if( begin_size == sizeof( ::booldog::mem::info3 ) )
						{
							::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
							info->_flags = 0;
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO3 );
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
							info->_eflags = info->_flags;
						}
						else if( begin_size == sizeof( ::booldog::mem::info4 ) )
						{
							::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
							info->_flags = 0;
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO4 );
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
							info->_eflags = info->_flags;
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
								info->_flags = 0;
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO1 );
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
								info->_eflags = info->_flags;
							}
							else if( begin_size == sizeof( ::booldog::mem::info2 ) )
							{
								::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
								info->_flags = 0;
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO2 );
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
								info->_eflags = info->_flags;
							}
							else if( begin_size == sizeof( ::booldog::mem::info3 ) )
							{
								::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
								info->_flags = 0;
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO3 );
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
								info->_eflags = info->_flags;
							}
							else if( begin_size == sizeof( ::booldog::mem::info4 ) )
							{
								::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
								info->_flags = 0;
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO4 );
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
								info->_eflags = info->_flags;
							}
							return begin;
						}
						_avail -= total;
						diff = total - size;
						if( diff == sizeof( ::booldog::mem::info1 ) )
						{
							::booldog::mem::info1* info = (::booldog::mem::info1*)begin;
							info->_flags = 0;
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO1 );
							info->_size = (::booldog::byte)size;
							info->_eflags = info->_flags;
						}
						else if( diff == sizeof( ::booldog::mem::info2 ) )
						{
							::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
							info->_flags = 0;
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO2 );
							info->_size = (::booldog::ushort)size;
							info->_eflags = info->_flags;
						}
						else if( diff == sizeof( ::booldog::mem::info3 ) )
						{
							::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
							info->_flags = 0;
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO3 );
							info->_size = (::booldog::uint32)size;
							info->_eflags = info->_flags;
						}
						else if( diff == sizeof( ::booldog::mem::info4 ) )
						{
							::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
							info->_flags = 0;
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO4 );
							info->_size = size;
							info->_eflags = info->_flags;
						}
						return begin;
					}
					else
						return 0;
				};				
				booinline ::booldog::byte* from_pointer( void* pointer , size_t& offsize , size_t& begin_size )
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
					return &_data[ s + sizeof( ::booldog::mem::info4 ) ];
				};
				virtual void* alloc( size_t size , ::booldog::debug::info* debuginfo = 0 )
				{
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
				virtual void free( void* pointer )
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
						throw int();
				};
				virtual void* realloc( void* pointer , size_t size , ::booldog::debug::info* debuginfo = 0 )
				{
					if( size == 0 )
					{
						if( pointer )
							free( pointer );
						return 0;
					}
					if( pointer == 0 )
						return alloc( size , debuginfo );
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
							info->_flags = 0;
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO1 );
							info->_size = (::booldog::byte)size;
							info->_eflags = info->_flags;
						}
						else if( new_offset == sizeof( ::booldog::mem::info2 ) )
						{
							::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
							info->_flags = 0;
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO2 );
							info->_size = (::booldog::ushort)size;
							info->_eflags = info->_flags;
						}
						else if( new_offset == sizeof( ::booldog::mem::info3 ) )
						{
							::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
							info->_flags = 0;
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO3 );
							info->_size = (::booldog::uint32)size;
							info->_eflags = info->_flags;
						}
						else if( new_offset == sizeof( ::booldog::mem::info4 ) )
						{
							::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
							info->_flags = 0;
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
							::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO4 );
							info->_size = size;
							info->_eflags = info->_flags;
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
								info->_flags = 0;
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO1 );
								info->_size = (::booldog::byte)info_begin_size;
								info->_eflags = info->_flags;
							}
							else if( new_offset == sizeof( ::booldog::mem::info2 ) )
							{
								::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
								info->_flags = 0;
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO2 );
								info->_size = (::booldog::ushort)info_begin_size;
								info->_eflags = info->_flags;
							}
							else if( new_offset == sizeof( ::booldog::mem::info3 ) )
							{
								::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
								info->_flags = 0;
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO3 );
								info->_size = (::booldog::uint32)info_begin_size;
								info->_eflags = info->_flags;
							}
							else if( new_offset == sizeof( ::booldog::mem::info4 ) )
							{
								::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
								info->_flags = 0;
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_BUSY );
								::booldog::utils::set_bit( info->_flags , BOOLDOG_MEM_INFO_USE_INFO4 );
								info->_size = info_begin_size;
								info->_eflags = info->_flags;
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
							return this->realloc( begin + new_offset , size , debuginfo );
						}
					}
				};
			};
		};
	};
};
#endif
