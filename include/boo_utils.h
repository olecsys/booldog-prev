#ifndef BOO_UTILS_H
#define BOO_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_types.h>
namespace booldog
{
	namespace utils
	{
		template< class T >
		booinline bool odd( T val )
		{
			return ( val & 1 );
		};
		booinline ::booldog::byte get_bit( ::booldog::byte& byte , ::booldog::uchar bit_index )
		{
			if( ( ( byte ) & ( 1 << ( bit_index ) ) ) )
				return 1;
			else
				return 0;
		};
		booinline void unset_bit( ::booldog::byte& byte , ::booldog::uchar bit_index )
		{
			byte &= ~( 1 << bit_index );
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
