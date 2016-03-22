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
//#ifdef __WINDOWS__
//#pragma warning( push )
//#pragma warning( disable: 4293 )
//#endif
				template< class booclass , const ::booldog::byte n0 = 8 * sizeof( booclass ) , const ::booldog::byte n1 = 8 * sizeof( booclass ) 
					, const ::booldog::byte n2 = 8 * sizeof( booclass ) , const ::booldog::byte n3 = 8 * sizeof( booclass ) , const ::booldog::byte n4 = 8 * sizeof( booclass ) 
					, const ::booldog::byte n5 = 8 * sizeof( booclass ) , const ::booldog::byte n6 = 8 * sizeof( booclass ) , const ::booldog::byte n7 = 8 * sizeof( booclass ) 
					, const ::booldog::byte n8 = 8 * sizeof( booclass ) , const ::booldog::byte n9 = 8 * sizeof( booclass ) , const ::booldog::byte n10 = 8 * sizeof( booclass ) 
					, const ::booldog::byte n11 = 8 * sizeof( booclass ) , const ::booldog::byte n12 = 8 * sizeof( booclass ) , const ::booldog::byte n13 = 8 * sizeof( booclass ) 
					, const ::booldog::byte n14 = 8 * sizeof( booclass ) , const ::booldog::byte n15 = 8 * sizeof( booclass ) , const ::booldog::byte n16 = 8 * sizeof( booclass ) 
					, const ::booldog::byte n17 = 8 * sizeof( booclass ) , const ::booldog::byte n18 = 8 * sizeof( booclass ) , const ::booldog::byte n19 = 8 * sizeof( booclass ) >
				struct number_from_bit_index
				{
					template< const ::booldog::byte k , booclass prev = 0 >
					struct calc
					{
						static const booclass value = ( k == 8 * sizeof( booclass ) ) ? prev : prev | ( 1 << k );
					};
					static const booclass value = calc< n19 , calc< n18 , calc< n17 , calc< n16 , calc< n15 , calc< n14 , calc< n13 
						, calc< n12 , calc< n11 , calc< n10 , calc< n9 , calc< n8 , calc< n7 , calc< n6 , calc< n5 , calc< n4 , calc< n3 
						, calc< n2 , calc< n1 , calc< n0 >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value >::value;
				};
//#ifdef __WINDOWS__
//#pragma warning( pop )
//#endif
			};
		};
	};
};
#endif