#ifndef BOO_MEM_H
#define BOO_MEM_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_types.h)
#include <string.h>
namespace booldog
{
	namespace mem
	{
#define BOOLDOG_MEM_INFO_HEAP 2
#define BOOLDOG_MEM_INFO_BUSY 3
#define BOOLDOG_MEM_INFO_USE_INFO1 4
#define BOOLDOG_MEM_INFO_USE_INFO2 5
#define BOOLDOG_MEM_INFO_USE_INFO3 6
#define BOOLDOG_MEM_INFO_USE_INFO4 7
		boobegin_struct_pack( 1 )
		struct info1
		{
			::booldog::byte _check;
			::booldog::byte _flags;
			::booldog::byte _size;
			::booldog::byte _eflags;
		}
		booend_struct_pack( 1 )
		boobegin_struct_pack( 1 )
		struct info2
		{
			::booldog::byte _check;
			::booldog::byte _flags;
			::booldog::ushort _size;
			::booldog::byte _eflags;
		}
		booend_struct_pack( 1 )
		boobegin_struct_pack( 1 )
		struct info3
		{
			::booldog::byte _check;
			::booldog::byte _flags;
			::booldog::uint32 _size;
			::booldog::byte _eflags;
		}
		booend_struct_pack( 1 )
		boobegin_struct_pack( 1 )
		struct info4
		{
			::booldog::byte _check;
			::booldog::byte _flags;
			::booldog::uint64 _size;
			::booldog::byte _eflags;
		}
		booend_struct_pack( 1 )
		namespace info
		{
			booinline size_t memory_size_with_info( size_t size )
			{
				if( size < 0xff )
					size += sizeof( ::booldog::mem::info1 );
				else if( size < 0xffff )
					size += sizeof( ::booldog::mem::info2 );
				else if( size < 0xffffffff )
					size += sizeof( ::booldog::mem::info3 );
				else if( size < 0xffffffffffffffff )
					size += sizeof( ::booldog::mem::info4 );
				return size;
			};
			booinline size_t memory_info_size( size_t size )
			{
				if( size < 0xff )
					return sizeof( ::booldog::mem::info1 );
				else if( size < 0xffff )
					return sizeof( ::booldog::mem::info2 );
				else if( size < 0xffffffff )
					return sizeof( ::booldog::mem::info3 );
				else if( size < 0xffffffffffffffff )
					return sizeof( ::booldog::mem::info4 );
				return 0;
			};
		};
		template< class booclass >
		booinline bool expand( size_t index , const void* dst , size_t dstsize , size_t dst_allocsize , size_t srcsize )
		{
			if( srcsize )
			{
				if( index > dstsize )
					index = dstsize;
				if( srcsize + dstsize > dst_allocsize )
					return false;

				::booldog::byte* dstptr = (::booldog::byte*)dst;
				if( dstsize > index )
					::memmove( &dstptr[ ( index + srcsize ) * sizeof( booclass ) ] , &dstptr[ index * sizeof( booclass ) ] , ( dstsize - index ) * sizeof( booclass ) );
			}
			return true;
		};
		template< class booclass >
		booinline bool insert( size_t index , const void* dst , size_t dstsize , size_t dst_allocsize , size_t dstremovesize , const void* src , size_t srcsize )
		{
			if( srcsize )
			{
				if( index > dstsize )
				{
					index = dstsize;
					dstremovesize = 0;
				}
				else if( index + dstremovesize > dstsize )
					dstremovesize = dstsize - index;
				if( srcsize + dstsize - dstremovesize > dst_allocsize )
					return false;

				::booldog::byte* dstptr = (::booldog::byte*)dst;
				if( dstsize > index + dstremovesize )
					::memmove( &dstptr[ ( index + srcsize ) * sizeof( booclass ) ] , &dstptr[ ( index + dstremovesize ) * sizeof( booclass ) ] , ( dstsize - index - dstremovesize ) * sizeof( booclass ) );
				::memmove( &dstptr[ index * sizeof( booclass ) ] , src , srcsize * sizeof( booclass ) );
			}
			return true;
		};
		template< class booclass >
		booinline void remove( size_t index , const void* dst , size_t dstsize , size_t removesize )
		{
			if( removesize )
			{
				if( index < dstsize )
				{
					if( index + removesize > dstsize )
						removesize = dstsize - index;
					::booldog::byte* dstptr = (::booldog::byte*)dst;
					if( dstsize > index + removesize )
						::memmove( &dstptr[ index * sizeof( booclass ) ] , &dstptr[ ( index + removesize ) * sizeof( booclass ) ] , ( dstsize - index - removesize ) * sizeof( booclass ) );
				}
			}
		};
	};
};
#endif