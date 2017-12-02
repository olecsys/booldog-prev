#ifndef BOO_HASH_TIMES33_H
#define BOO_HASH_TIMES33_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_types.h"

#include <stdarg.h>
#include <string.h>
namespace booldog
{
	namespace hash
	{
		namespace compile
		{
#ifdef __WINDOWS__
#pragma warning( push )
#pragma warning( disable: 4307 )
#endif
			template<const char n0 = 0, const char n1 = 0, const char n2 = 0, const char n3 = 0, const char n4 = 0
				, const char n5 = 0, const char n6 = 0, const char n7 = 0, const char n8 = 0, const char n9 = 0 
				, const char n10 = 0, const char n11 = 0, const char n12 = 0, const char n13 = 0 , const char n14 = 0 
				, const char n15 = 0 , const char n16 = 0 , const char n17 = 0 , const char n18 = 0 , const char n19 = 0
				, const char n20 = 0, const char n21 = 0, const char n22 = 0, const char n23 = 0, const char n24 = 0
				, const char n25 = 0, const char n26 = 0, const char n27 = 0, const char n28 = 0, const char n29 = 0
				, const char n30 = 0, const char n31 = 0, const char n32 = 0, const char n33 = 0, const char n34 = 0
				, const char n35 = 0, const char n36 = 0, const char n37 = 0, const char n38 = 0, const char n39 = 0>
			struct times33
			{
				template<const char k, ::booldog::uint64 hash = 0>
				struct hash_calc
				{
					static const ::booldog::uint64 value = (k == 0) ? hash : (::booldog::uint64)(hash * 33ULL)
						+ (::booldog::uint64)k;
				};
				static const ::booldog::uint64 value = hash_calc<n39, hash_calc<n38, hash_calc<n37, hash_calc<n36, hash_calc<n35
					, hash_calc<n34, hash_calc<n33, hash_calc<n32, hash_calc<n31, hash_calc<n30, hash_calc<n29
					, hash_calc<n28, hash_calc<n27, hash_calc<n26, hash_calc<n25, hash_calc<n24, hash_calc<n23
					, hash_calc<n22, hash_calc<n21, hash_calc<n20, hash_calc<n19, hash_calc<n18, hash_calc<n17
					, hash_calc<n16, hash_calc<n15, hash_calc<n14, hash_calc<n13, hash_calc<n12, hash_calc<n11
					, hash_calc<n10, hash_calc<n9, hash_calc<n8, hash_calc<n7, hash_calc<n6, hash_calc<n5, hash_calc<n4
					, hash_calc<n3, hash_calc<n2, hash_calc<n1, hash_calc<n0>::value>::value>::value>::value>::value>::value
					>::value>::value>::value>::value>::value>::value>::value>::value>::value>::value>::value>::value>::value>::value
					>::value>::value>::value>::value>::value>::value>::value>::value>::value>::value>::value>::value>::value>::value
					>::value>::value>::value>::value>::value>::value;
			};
		}
#ifdef __WINDOWS__
#pragma warning( pop )
#endif
		namespace times33
		{
			booinline ::booldog::uint64 calculate(const char* data, size_t data_len)
			{
				::booldog::uint64 hash = 0;
				const ::booldog::byte* begin = (const ::booldog::byte*)data;
				if(data_len == SIZE_MAX)
				{
					const ::booldog::byte* ptr = begin;
					for(;*ptr;++ptr)
						hash = hash * 33 + *ptr;
				}
				else
				{
					const ::booldog::byte* ptr = begin;
					for(size_t index0 = data_len;index0;--index0, ++ptr)
						hash = hash * 33 + *ptr;
				}
				return hash;
			}
			booinline ::booldog::uint64 calculate(size_t count, va_list ap)
			{
				::booldog::uint64 hash = 0;
				const ::booldog::byte* ptr = 0;
				for(size_t index0 = 0;index0 < count;++index0)
				{
					ptr = (const ::booldog::uint8*)va_arg(ap, char*);
					for(;*ptr;++ptr)
						hash = hash * 33 + *ptr;
				}
				return hash;
			}
			booinline ::booldog::uint64 calculate(size_t count, ...)
			{
				va_list ap;
				va_start(ap, count);
				::booldog::uint64 hash = calculate(count, ap);
				va_end(ap);
				return hash;
			}
		}
	}
}
#endif
