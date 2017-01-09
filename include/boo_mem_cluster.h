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
	namespace enums
	{
		namespace log
		{
			enum level
			{
				level_error = 40000 ,
				level_warn = 30000 ,
				level_debug = 10000 ,
				level_trace = 5000 , 
				level_verbose = 0
			};
		};
	};
	namespace typedefs
	{
		typedef void (*write_log_t)(::booldog::enums::log::level level, const char* format, va_list ap);
	};
	namespace empties
	{
		namespace log
		{
			booinline void write_log(::booldog::enums::log::level, const char* , va_list){};
		};
	};
	namespace mem
	{		
		class cluster
		{
			::booldog::byte* _data;
			size_t _data_size;			
		public:
			size_t _avail;
			::booldog::byte* _begin;
#ifdef BOOLDOG_MEM_CLUSTER_LOG
			::booldog::typedefs::write_log_t _write_log;
			booinline void write_log(const char* format, ...)
			{
				va_list ap;
				va_start(ap, format);
				_write_log(::booldog::enums::log::level_error, format, ap);
				va_end( ap );
			};
#endif
			cluster( ::booldog::byte* data , size_t data_size )
			{
#ifdef BOOLDOG_MEM_CLUSTER_LOG
				_write_log = ::booldog::empties::log::write_log;
#endif
				_data = data;
				_data_size = data_size;
				_avail = data_size;
				_begin = _data;
				if(_avail - sizeof( ::booldog::mem::info1 ) < UINT8_MAX )
				{
					::booldog::mem::info1* info = (::booldog::mem::info1*)_begin;
					info->_check = 86;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO1 >::value;
					info->_size = (::booldog::byte)( _avail - sizeof( ::booldog::mem::info1 ) );
					_begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else if(_avail - sizeof( ::booldog::mem::info2 ) < UINT16_MAX)
				{
					::booldog::mem::info2* info = (::booldog::mem::info2*)_begin;
					info->_check = 86;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO2 >::value;
					info->_size = (::booldog::ushort)( _avail - sizeof( ::booldog::mem::info2 ) );
					_begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else if(_avail - sizeof( ::booldog::mem::info3 ) < UINT32_MAX)
				{
					::booldog::mem::info3* info = (::booldog::mem::info3*)_begin;
					info->_check = 86;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO3 >::value;
					info->_size = (::booldog::uint32)( _avail - sizeof( ::booldog::mem::info3 ) );
					_begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else
				{
					::booldog::mem::info4* info = (::booldog::mem::info4*)_begin;
					info->_check = 86;
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
				from_info(info, offsize, begin_size);
				printf("Available size=%u(%u), begin(%p), end(%p)\n", (::booldog::uint32)_avail
					, (::booldog::uint32)_data_size, _begin, endptr);
				for( ; ; )
				{
					if( ::booldog::utils::get_bit( info[ 1 ] , BOOLDOG_MEM_INFO_BUSY ) )
						printf("Busy slice, size=%u(%u)\n", (::booldog::uint32)begin_size, (::booldog::uint32)offsize);
					else
						printf("Available slice, size=%u(%u)\n", (::booldog::uint32)begin_size, (::booldog::uint32)offsize);
					info = info + offsize;
					if( info >= endptr )
						break;
					from_info( info , offsize , begin_size );
				}
			};
			booinline bool check_consistency(void)
			{
				void* endptr = end();
				::booldog::byte* info = _data, * prev = 0;
				size_t offsize = 0 , begin_size = 0, prev_offsize = 0;
				from_info(info, offsize, begin_size);
				for(;;)
				{
					if(prev)
					{					
						size_t diff = (size_t)(info - prev);
						if(diff <= sizeof(::booldog::mem::info1)
							|| prev_offsize != diff)
							return false;
					}
					prev = info;
					info = info + offsize;
					if(info >= endptr)
					{
						size_t diff = (size_t)((::booldog::byte*)endptr - prev);
						if(diff <= sizeof(::booldog::mem::info1))
							return false;
						break;
					}
					prev_offsize = offsize;
					from_info(info, offsize, begin_size);
				}
				return true;
			};
			booinline void check( void )
			{
				void* endptr = end();
				::booldog::byte* info = _data;
				size_t offsize = 0 , begin_size = 0;
				from_info( info , offsize , begin_size );
				for( ; ; )
				{
					if( info[ 0 ] != 86 )
					{
						int u = 5; u-- ; printf( "%d" , 120 / ( u - 4 ) );
					}
					info = info + offsize;
					if( info >= endptr )
						break;
					from_info( info , offsize , begin_size );
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

				if(size - sizeof( ::booldog::mem::info1 ) < UINT8_MAX)
				{
					begin_size = size - sizeof( ::booldog::mem::info1 );
					::booldog::mem::info1* info = (::booldog::mem::info1*)begin;
					info->_check = 86;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO1 >::value;
					info->_size = (::booldog::byte)begin_size;
					begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else if(size - sizeof( ::booldog::mem::info2 ) < UINT16_MAX)
				{
					begin_size = size - sizeof( ::booldog::mem::info2 );
					::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
					info->_check = 86;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO2 >::value;
					info->_size = (::booldog::ushort)begin_size;
					begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else if(size - sizeof( ::booldog::mem::info1 ) < UINT32_MAX)
				{
					begin_size = size - sizeof( ::booldog::mem::info3 );
					::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
					info->_check = 86;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO3 >::value;
					info->_size = (::booldog::uint32)begin_size;
					begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else
				{
					begin_size = size - sizeof( ::booldog::mem::info4 );
					::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
					info->_check = 86;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO4 >::value;
					info->_size = begin_size;
					begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
			};
			booinline ::booldog::byte* check_alloc( ::booldog::byte* begin , size_t& size , size_t& total )
			{
				size_t offsize = 0 , begin_size = 0;
				from_info(begin, offsize, begin_size);
				if(begin_size == size && total == offsize)
					_avail -= total;
				else if(offsize <= total)
					return 0;
				else
				{
					size_t diff = offsize - total;		
					if( diff <= sizeof( ::booldog::mem::info1 ) )
					{
						total = offsize;
						size = begin_size;
					}
					else if( diff - sizeof( ::booldog::mem::info1 ) < UINT8_MAX )
					{
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info1 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else if( diff - sizeof( ::booldog::mem::info2 ) < UINT16_MAX )
					{
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info2 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else if( diff - sizeof( ::booldog::mem::info3 ) < UINT32_MAX )
					{
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info3 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else
					{
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info4 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					_avail -= total;
				}
				if( size < UINT8_MAX )
				{
					::booldog::mem::info1* info = (::booldog::mem::info1*)begin;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO1 , BOOLDOG_MEM_INFO_BUSY >::value;
					info->_size = (::booldog::byte)size;
					begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else if( size < UINT16_MAX )
				{
					::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO2 , BOOLDOG_MEM_INFO_BUSY >::value;
					info->_size = (::booldog::ushort)size;
					begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else if( size < UINT32_MAX )
				{
					::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO3 , BOOLDOG_MEM_INFO_BUSY >::value;
					info->_size = (::booldog::uint32)size;
					begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				else
				{
					::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
					info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
						BOOLDOG_MEM_INFO_USE_INFO4 , BOOLDOG_MEM_INFO_BUSY >::value;
					info->_size = (::booldog::uint64)size;
					begin[ sizeof( *info ) - 1 ] = info->_flags;
				}
				return begin;
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
#ifdef BOOLDOG_MEM_CLUSTER_CHECK
				check();
#endif
#ifdef BOOLDOG_MEM_CLUSTER_LOG
				size_t requested_size = size;
#endif
				if(size % BOOLDOG_MEM_ALIGN_SIZE)
					size = BOOLDOG_MEM_ALIGN_SIZE * (size /BOOLDOG_MEM_ALIGN_SIZE) + BOOLDOG_MEM_ALIGN_SIZE;

				debuginfo = debuginfo;
				if( _avail > 0 )
				{
					size_t offsize = 0 , begin_size = 0;
					from_info( _begin , offsize , begin_size );
					concat_unbusy_slices( _begin , offsize , begin_size );

					size_t total = size;
					if( size < UINT8_MAX )
						total += sizeof( ::booldog::mem::info1 );
					else if( size < UINT16_MAX )
						total += sizeof( ::booldog::mem::info2 );
					else if( size < UINT32_MAX )
						total += sizeof( ::booldog::mem::info3 );
					else
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
#ifdef BOOLDOG_MEM_CLUSTER_LOG
						write_log("mem_cluster::alloc, %pp(%u)", begin + total - size, (::booldog::uint32)requested_size);
#endif
						return begin + total - size;
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
							{
#ifdef BOOLDOG_MEM_CLUSTER_LOG
								write_log("mem_cluster::alloc, %pp(%u)", begin + total - size
									, (::booldog::uint32)requested_size);
#endif
								return begin + total - size;
							}
						}
					}	
				}
				return 0;
			};
			void free( void* pointer )
			{
#ifdef BOOLDOG_MEM_CLUSTER_LOG
				write_log("mem_cluster::free, %pp", pointer);
#endif
#ifdef BOOLDOG_MEM_CLUSTER_CHECK
				check();
#endif
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
			size_t gettotalsize( void* pointer )
			{
				if( pointer == 0 )
					return 0;
				size_t offsize = 0 , size = 0;
				from_pointer( pointer , offsize , size );
				return offsize;
			};
			void* tryrealloc(void* pointer, size_t size, bool free_if_cannot_alloc, void*& oldpointer
				, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
#ifdef BOOLDOG_MEM_CLUSTER_CHECK
				check();
#endif
				if(size == 0)
				{
					if(pointer)
						free(pointer);
					return 0;
				}
				if(pointer == 0)
					return alloc(size, debuginfo);
#ifdef BOOLDOG_MEM_CLUSTER_LOG
				size_t requested_size = size;
#endif
				if(size % BOOLDOG_MEM_ALIGN_SIZE)
					size = BOOLDOG_MEM_ALIGN_SIZE * (size / BOOLDOG_MEM_ALIGN_SIZE) + BOOLDOG_MEM_ALIGN_SIZE;

				size_t offsize = 0 , begin_size = 0;
				::booldog::byte* begin = from_pointer( pointer , offsize , begin_size );
				if( begin_size == size )
				{
#ifdef BOOLDOG_MEM_CLUSTER_LOG
					write_log("mem_cluster::tryrealloc, %pp(%u, %pp)", pointer, (::booldog::uint32)requested_size, pointer);
#endif
					return pointer;
				}
				else if( begin_size > size )
				{
					size_t total = size;
					if( size < UINT8_MAX )
						total += sizeof( ::booldog::mem::info1 );
					else if( size < UINT16_MAX )
						total += sizeof( ::booldog::mem::info2 );
					else if( size < UINT32_MAX )
						total += sizeof( ::booldog::mem::info3 );
					else
						total += sizeof( ::booldog::mem::info4 );

					size_t new_offset = total - size;
						
					size_t diff = offsize - total;
					if( diff <= sizeof( ::booldog::mem::info1 ) )
					{
#ifdef BOOLDOG_MEM_CLUSTER_LOG
						write_log("mem_cluster::tryrealloc, %pp(%u, %pp)", pointer, (::booldog::uint32)requested_size
							, pointer);
#endif
						return pointer;
					}
					else if( diff - sizeof( ::booldog::mem::info1 ) < UINT8_MAX )
					{
						size_t old_offset = offsize - begin_size;
						if( old_offset != new_offset )
							::memmove( &begin[ new_offset ] , &begin[ old_offset ] , begin_size );
						_avail += diff;
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info1 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else if( diff - sizeof( ::booldog::mem::info2 ) < UINT16_MAX )
					{
						size_t old_offset = offsize - begin_size;
						if( old_offset != new_offset )
							::memmove( &begin[ new_offset ] , &begin[ old_offset ] , begin_size );
						_avail += diff;
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info2 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else if( diff - sizeof( ::booldog::mem::info3 ) < UINT32_MAX )
					{
						size_t old_offset = offsize - begin_size;
						if( old_offset != new_offset )
							::memmove( &begin[ new_offset ] , &begin[ old_offset ] , begin_size );
						_avail += diff;
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info3 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					else
					{
						size_t old_offset = offsize - begin_size;
						if( old_offset != new_offset )
							::memmove( &begin[ new_offset ] , &begin[ old_offset ] , begin_size );
						_avail += diff;
						size_t new_offsize = diff;
						diff -= sizeof( ::booldog::mem::info4 );
						concat_unbusy_slices( &begin[ total ] , new_offsize , diff );
					}
					if( _begin > &begin[ total ] )
						_begin = &begin[ total ];
					if( size < UINT8_MAX )
					{
						::booldog::mem::info1* info = (::booldog::mem::info1*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO1 >::value;
						info->_size = (::booldog::byte)size;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					else if( size < UINT16_MAX )
					{
						::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO2 >::value;
						info->_size = (::booldog::ushort)size;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					else if( size < UINT32_MAX )
					{
						::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO3 >::value;
						info->_size = (::booldog::uint32)size;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
					else
					{
						::booldog::mem::info4* info = (::booldog::mem::info4*)begin;
						info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
							BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO4 >::value;
						info->_size = size;
						begin[ sizeof( *info ) - 1 ] = info->_flags;
					}
#ifdef BOOLDOG_MEM_CLUSTER_LOG
					write_log("mem_cluster::tryrealloc, %pp(%u, %pp)", begin + new_offset
						, (::booldog::uint32)requested_size, pointer);
#endif
					return begin + new_offset;
				}
				else
				{
					void* endptr = end();
					::booldog::byte* info = begin + offsize;
					if( info >= endptr || ::booldog::utils::get_bit( info[ 1 ] , BOOLDOG_MEM_INFO_BUSY ) )
					{
						void* new_pointer = this->alloc( size , debuginfo );
						if( new_pointer == 0 )
						{
							oldpointer = pointer;
							if( free_if_cannot_alloc )
								this->free( pointer );
						}
						else
						{
							::memcpy( new_pointer , pointer , begin_size );
							this->free( pointer );
						}
#ifdef BOOLDOG_MEM_CLUSTER_LOG
						write_log("mem_cluster::tryrealloc, %pp(%u, %pp)", new_pointer, (::booldog::uint32)requested_size
							, pointer);
#endif
						return new_pointer;
					}
					else
					{
						size_t info_offsize = 0 , info_begin_size = 0;
						from_info( info , info_offsize , info_begin_size );
						concat_unbusy_slices( info , info_offsize , info_begin_size );
							
						_avail -= info_offsize;
						size_t diff = offsize + info_offsize , new_offset = 0;
						if( diff - sizeof( ::booldog::mem::info1 ) < UINT8_MAX )
						{
							info_offsize = diff;
							info_begin_size = diff - sizeof( ::booldog::mem::info1 );

							size_t old_offset = offsize - begin_size;
							new_offset = info_offsize - info_begin_size;
							if( old_offset != new_offset )
								::memmove( &begin[ new_offset ] , &begin[ old_offset ] , begin_size );

							::booldog::mem::info1* info = (::booldog::mem::info1*)begin;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO1 >::value;
							info->_size = (::booldog::byte)info_begin_size;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						else if( diff - sizeof( ::booldog::mem::info2 ) < UINT16_MAX )
						{
							info_offsize = diff;
							info_begin_size = diff - sizeof( ::booldog::mem::info2 );

							size_t old_offset = offsize - begin_size;
							new_offset = info_offsize - info_begin_size;
							if( old_offset != new_offset )
								::memmove( &begin[ new_offset ] , &begin[ old_offset ] , begin_size );

							::booldog::mem::info2* info = (::booldog::mem::info2*)begin;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO2 >::value;
							info->_size = (::booldog::ushort)info_begin_size;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						else if( diff - sizeof( ::booldog::mem::info3 ) < UINT32_MAX )
						{
							info_offsize = diff;
							info_begin_size = diff - sizeof( ::booldog::mem::info3 );

							size_t old_offset = offsize - begin_size;
							new_offset = info_offsize - info_begin_size;
							if( old_offset != new_offset )
								::memmove( &begin[ new_offset ] , &begin[ old_offset ] , begin_size );

							::booldog::mem::info3* info = (::booldog::mem::info3*)begin;
							info->_flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , 
								BOOLDOG_MEM_INFO_BUSY , BOOLDOG_MEM_INFO_USE_INFO3 >::value;
							info->_size = (::booldog::uint32)info_begin_size;
							begin[ sizeof( *info ) - 1 ] = info->_flags;
						}
						else
						{
							info_offsize = diff;
							info_begin_size = diff - sizeof( ::booldog::mem::info4 );

							size_t old_offset = offsize - begin_size;
							new_offset = info_offsize - info_begin_size;
							if( old_offset != new_offset )
								::memmove( &begin[ new_offset ] , &begin[ old_offset ] , begin_size );

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
#ifdef BOOLDOG_MEM_CLUSTER_LOG
						write_log("mem_cluster::tryrealloc, again tryrealloc, %pp(%u)", pointer
							, (::booldog::uint32)requested_size);
#endif
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
