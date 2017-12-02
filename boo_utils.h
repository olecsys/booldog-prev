#ifndef BOO_UTILS_H
#define BOO_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_types.h"

#include <math.h>
namespace booldog
{
	namespace utils
	{
		template< class T >
		booinline T decimal_string_to_number( const ::booldog::byte*& ptr )
		{
			T value = 0;
			for( ; ; )
			{
				if( *ptr >= 0x30 && *ptr <= 0x39 )
				{
					value *= 10;
					value += *ptr++ - 0x30;
				}
				else
					break;
			}
			return value;
		};

		booinline double round( double number , int precision )
		{	
			number *= pow( 10.0 , precision );
			number = floor( number + 0.5 );
			number /= pow( 10.0 , precision );
			return number;
		};
		booinline float round( float number , int precision )
		{	
			number *= (float)pow( 10.0f , precision );
			number = (float)floor( number + 0.5f );
			number /= (float)pow( 10.0f , precision );
			return number;
		};
		booinline double round( double number )
		{
		  return floor( number + 0.5 );
		};
		booinline float round( float d )
		{
		  return (float)floor( d + 0.5f );
		};
		template< class T >
		booinline bool odd( T val )
		{
			return ( val & 1 );
		};
		booinline ::booldog::byte get_bit( const ::booldog::byte& byte , ::booldog::uchar bit_index )
		{
			if( ( ( byte ) & ( 1 << ( bit_index ) ) ) )
				return 1;
			else
				return 0;
		};
		booinline void unset_bit( const ::booldog::byte& byte , ::booldog::uchar bit_index )
		{
			*const_cast< ::booldog::byte* >( &byte ) &= ~( 1 << bit_index );
		};
		booinline void set_bit( ::booldog::byte& byte , ::booldog::uchar bit_index )
		{
			byte |= 1 << bit_index;
		};
		booinline ::booldog::byte get_bit( ::booldog::uint8* bytes , size_t bit_index )
		{
			size_t byte_index = bit_index / 8;
			bit_index -= byte_index * 8;
			return ::booldog::utils::get_bit( bytes[ byte_index ] , (::booldog::byte)bit_index );
		};
		booinline void unset_bit( ::booldog::uint8* bytes , size_t bit_index )
		{
			size_t byte_index = bit_index / 8;
			bit_index -= byte_index * 8; 
			::booldog::utils::unset_bit( bytes[ byte_index ] , (::booldog::byte)bit_index );
		};
		booinline void set_bit( ::booldog::uint8* bytes , size_t bit_index )
		{
			size_t byte_index = bit_index / 8;
			bit_index -= byte_index * 8;
			::booldog::utils::set_bit( bytes[ byte_index ] , (::booldog::byte)bit_index );
		};
	};
};
#endif
