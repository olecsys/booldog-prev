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
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#ifdef __WINDOWS__
#if (_MSC_VER >= 1600 )
#include <stdint.h>
#endif
#else
#include <stdint.h>
#endif
#ifndef SIZE_MAX
#ifdef __SIZE_MAX__
#define SIZE_MAX __SIZE_MAX__
#else
#define SIZE_MAX ((size_t) - 1)
#endif
#endif

#ifndef BOOLDOG_MEM_ALIGN_SIZE
#ifdef __ARM_ALIGN_MAX_STACK_PWR
#define BOOLDOG_MEM_ALIGN_SIZE __ARM_ALIGN_MAX_STACK_PWR
#else
#ifdef __ELBRUS__
#define BOOLDOG_MEM_ALIGN_SIZE 8 
#else 
#define BOOLDOG_MEM_ALIGN_SIZE 4
#endif
#endif
#endif
namespace booldog
{
	namespace mem
	{
#ifdef __WINDOWS__
#pragma warning( push )
#pragma warning( disable: 4324 )
#endif
#define BOOLDOG_MEM_INFO_HEAP 2
#define BOOLDOG_MEM_INFO_BUSY 3
#define BOOLDOG_MEM_INFO_USE_INFO1 4
#define BOOLDOG_MEM_INFO_USE_INFO2 5
#define BOOLDOG_MEM_INFO_USE_INFO3 6
#define BOOLDOG_MEM_INFO_USE_INFO4 7
		boobegin_struct_pack(BOOLDOG_MEM_ALIGN_SIZE)
		struct info1
		{
			::booldog::byte _check;
			::booldog::byte _flags;
			::booldog::byte _size;
			::booldog::byte _eflags;
		}
		booend_struct_pack(BOOLDOG_MEM_ALIGN_SIZE);
		boobegin_struct_pack(BOOLDOG_MEM_ALIGN_SIZE)
		struct info2
		{
			::booldog::byte _check;
			::booldog::byte _flags;
			::booldog::ushort _size;
			::booldog::byte _eflags;
		}
		booend_struct_pack(BOOLDOG_MEM_ALIGN_SIZE);
		boobegin_struct_pack(BOOLDOG_MEM_ALIGN_SIZE)
		struct info3
		{
			::booldog::byte _check;
			::booldog::byte _flags;
			::booldog::uint32 _size;
			::booldog::byte _eflags;
		}
		booend_struct_pack(BOOLDOG_MEM_ALIGN_SIZE);
		boobegin_struct_pack(BOOLDOG_MEM_ALIGN_SIZE)
		struct info4
		{
			::booldog::byte _check;
			::booldog::byte _flags;
			::booldog::uint64 _size;
			::booldog::byte _eflags;
		}
		booend_struct_pack(BOOLDOG_MEM_ALIGN_SIZE);
#ifdef __WINDOWS__
#pragma warning( pop )
#endif
		namespace info
		{
			booinline size_t memory_size_with_info( size_t size )
			{
				if( size % BOOLDOG_MEM_ALIGN_SIZE)
					size = BOOLDOG_MEM_ALIGN_SIZE * ( size / BOOLDOG_MEM_ALIGN_SIZE ) + BOOLDOG_MEM_ALIGN_SIZE;

				if( size < UINT8_MAX )
					size += sizeof( ::booldog::mem::info1 );
				else if( size < UINT16_MAX )
					size += sizeof( ::booldog::mem::info2 );
				else if( size < UINT32_MAX )
					size += sizeof( ::booldog::mem::info3 );
				else
					size += sizeof( ::booldog::mem::info4 );
				return size;
			};
			booinline size_t memory_info_size( size_t size )
			{
				if( size < UINT8_MAX )
					return sizeof( ::booldog::mem::info1 );
				else if( size < UINT16_MAX )
					return sizeof( ::booldog::mem::info2 );
				else if( size < UINT32_MAX )
					return sizeof( ::booldog::mem::info3 );
				else
					return sizeof( ::booldog::mem::info4 );
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
