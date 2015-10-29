#ifndef BOO_HASH_TIMES33_H
#define BOO_HASH_TIMES33_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_types.h>

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
			template< const char n0 = 0 , const char n1 = 0 , const char n2 = 0 , const char n3 = 0 , const char n4 = 0 , const char n5 = 0 , const char n6 = 0 , const char n7 = 0 , const char n8 = 0 , const char n9 = 0 , const char n10 = 0 , const char n11 = 0 , const char n12 = 0 , const char n13 = 0 , const char n14 = 0 , const char n15 = 0 , const char n16 = 0 , const char n17 = 0 , const char n18 = 0 , const char n19 = 0 >
			struct times33
			{
				template< const char k , ::booldog::uint64 hash = 0 >
				struct hash_calc
				{
					static const ::booldog::uint64 value = ( k == 0 ) ? hash : (::booldog::uint64)( hash * 33ULL ) + (::booldog::uint64)k;
				};
				static const ::booldog::uint64 value = hash_calc< n19 , hash_calc< n18 , hash_calc< n17 , hash_calc< n16 , hash_calc< n15 , hash_calc< n14 , hash_calc< n13 , hash_calc< n12 , hash_calc< n11 , hash_calc< n10 , hash_calc< n9 , hash_calc< n8 , hash_calc< n7 , hash_calc< n6 , hash_calc< n5 , hash_calc< n4 , hash_calc< n3 , hash_calc< n2 , hash_calc< n1 , hash_calc< n0 >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value;
			};
		};
#ifdef __WINDOWS__
#pragma warning( pop )
#endif
	};
};

#endif
