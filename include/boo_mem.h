#ifndef BOO_MEM_H
#define BOO_MEM_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_types.h>
namespace booldog
{
	namespace mem
	{
		struct info
		{
			bool _busy;
			size_t _size;
		};
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
					::memmove( &dstptr[ index + srcsize ] , &dstptr[ index ] , dstsize - index );
			}
			return true;
		};
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
					::memmove( &dstptr[ index + srcsize ] , &dstptr[ index + dstremovesize ] , dstsize - index - dstremovesize );
				::memmove( &dstptr[ index ] , src , srcsize );
			}
			return true;
		};
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
						::memmove( &dstptr[ index ] , &dstptr[ index + removesize ] , dstsize - index - removesize );
				}
			}
		};
	};
};
#endif