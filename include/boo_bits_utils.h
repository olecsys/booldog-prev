#ifndef BOO_BITS_UTILS_H
#define BOO_BITS_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_types.h)
namespace booldog
{	
	namespace utils
	{
		namespace bits
		{
			namespace compile
			{
				template< class booclass , const ::booldog::byte n0 = 0 , const ::booldog::byte n1 = 0 
					, const ::booldog::byte n2 = 0 , const ::booldog::byte n3 = 0 , const ::booldog::byte n4 = 0 
					, const ::booldog::byte n5 = 0 , const ::booldog::byte n6 = 0 , const ::booldog::byte n7 = 0 
					, const ::booldog::byte n8 = 0 , const ::booldog::byte n9 = 0 , const ::booldog::byte n10 = 0 
					, const ::booldog::byte n11 = 0 , const ::booldog::byte n12 = 0 , const ::booldog::byte n13 = 0 
					, const ::booldog::byte n14 = 0 , const ::booldog::byte n15 = 0 , const ::booldog::byte n16 = 0 
					, const ::booldog::byte n17 = 0 , const ::booldog::byte n18 = 0 , const ::booldog::byte n19 = 0 >
				struct number_from_bit_index
				{
					template< const ::booldog::byte k , booclass prev = 0 >
					struct calc
					{
						static const booclass value = ( k == 0 ) ? prev : prev | ( 1 << k );
					};
					static const booclass value = calc< n19 , calc< n18 , calc< n17 , calc< n16 , calc< n15 , calc< n14 , calc< n13 
						, calc< n12 , calc< n11 , calc< n10 , calc< n9 , calc< n8 , calc< n7 , calc< n6 , calc< n5 , calc< n4 , calc< n3 
						, calc< n2 , calc< n1 , calc< n0 >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value;
				};
			};
		};
	};
};
#endif