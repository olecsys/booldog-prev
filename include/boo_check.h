#ifndef BOO_CHECK_H
#define BOO_CHECK_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_object.h)
namespace booldog
{
	template< class booclass >
	booinline bool isclass( ::booldog::object& object )
	{
		if( booclass::use_item_type != object.get_use_item_type( 0 ) )
			return false;
		if( booclass::type_hash != object.get_type_hash( 0 , false ) )
			return false;
		if( ::booldog::compile::If< booclass::use_item_type == false >::test() )
			return true;

		if( booclass::item_type::use_item_type != object.get_use_item_type( 1 ) )
			return false;
		if( booclass::item_type::type_hash != object.get_type_hash( 1 , false ) )
			return false;
		if( ::booldog::compile::If< booclass::item_type::use_item_type == false >::test() )
			return true;

		if( booclass::item_type::item_type::use_item_type != object.get_use_item_type( 2 ) )
			return false;
		if( booclass::item_type::item_type::type_hash != object.get_type_hash( 2 , false ) )
			return false;
		if( ::booldog::compile::If< booclass::item_type::item_type::use_item_type == false >::test() )
			return true;

		if( booclass::item_type::item_type::item_type::use_item_type != object.get_use_item_type( 3 ) )
			return false;
		if( booclass::item_type::item_type::item_type::type_hash != object.get_type_hash( 3 , false ) )
			return false;
		if( ::booldog::compile::If< booclass::item_type::item_type::item_type::use_item_type == false >::test() )
			return true;

		if( booclass::item_type::item_type::item_type::item_type::use_item_type != object.get_use_item_type( 4 ) )
			return false;
		if( booclass::item_type::item_type::item_type::item_type::type_hash != object.get_type_hash( 4 , false ) )
			return false;
		if( ::booldog::compile::If< booclass::item_type::item_type::item_type::item_type::use_item_type == false >::test() )
			return true;

		if( booclass::item_type::item_type::item_type::item_type::item_type::use_item_type != object.get_use_item_type( 5 ) )
			return false;
		if( booclass::item_type::item_type::item_type::item_type::item_type::type_hash != object.get_type_hash( 5 , false ) )
			return false;
		if( ::booldog::compile::If< booclass::item_type::item_type::item_type::item_type::item_type::use_item_type == false >::test() )
			return true;
		return false;
	};
	template< class booclass >
	booinline bool can_assign( ::booldog::object& object )
	{
		if( ::booldog::compile::If< booclass::type_hash == ::booldog::object::type_hash >::test() )
			return true;
		::booldog::uint64 src_type_hash = object.get_type_hash( 0 , false );
		if( booclass::type_hash != src_type_hash )
			return false;
		if( booclass::use_item_type != object.get_use_item_type( 0 ) )
			return false;
		if( ::booldog::compile::If< booclass::use_item_type == false >::test() )
			return true;

		if( ::booldog::compile::If< booclass::item_type::type_hash == ::booldog::object::type_hash >::test() )
			return true;
		src_type_hash = object.get_type_hash( 1 , false );
		if( booclass::item_type::type_hash != src_type_hash )
		{
			if( src_type_hash == ::booldog::object::type_hash )
				return true;
			return false;
		}
		if( booclass::item_type::use_item_type != object.get_use_item_type( 1 ) )
			return false;
		if( ::booldog::compile::If< booclass::item_type::use_item_type == false >::test() )
			return true;

		if( ::booldog::compile::If< booclass::item_type::item_type::type_hash == ::booldog::object::type_hash >::test() )
			return true;
		src_type_hash = object.get_type_hash( 2 , false );
		if( booclass::item_type::item_type::type_hash != src_type_hash )
		{
			if( src_type_hash == ::booldog::object::type_hash )
				return true;
			return false;
		}
		if( booclass::item_type::item_type::use_item_type != object.get_use_item_type( 2 ) )
			return false;
		if( ::booldog::compile::If< booclass::item_type::item_type::use_item_type == false >::test() )
			return true;

		if( ::booldog::compile::If< booclass::item_type::item_type::item_type::type_hash == ::booldog::object::type_hash >::test() )
			return true;
		src_type_hash = object.get_type_hash( 3 , false );
		if( booclass::item_type::item_type::item_type::type_hash != src_type_hash )
		{
			if( src_type_hash == ::booldog::object::type_hash )
				return true;
			return false;
		}
		if( booclass::item_type::item_type::item_type::use_item_type != object.get_use_item_type( 3 ) )
			return false;
		if( ::booldog::compile::If< booclass::item_type::item_type::item_type::use_item_type == false >::test() )
			return true;

		if( ::booldog::compile::If< booclass::item_type::item_type::item_type::item_type::type_hash == ::booldog::object::type_hash >::test() )
			return true;
		src_type_hash = object.get_type_hash( 4 , false );
		if( booclass::item_type::item_type::item_type::item_type::type_hash != src_type_hash )
		{
			if( src_type_hash == ::booldog::object::type_hash )
				return true;
			return false;
		}
		if( booclass::item_type::item_type::item_type::item_type::use_item_type != object.get_use_item_type( 4 ) )
			return false;
		if( ::booldog::compile::If< booclass::item_type::item_type::item_type::item_type::use_item_type == false >::test() )
			return true;

		if( ::booldog::compile::If< booclass::item_type::item_type::item_type::item_type::item_type::type_hash == ::booldog::object::type_hash >::test() )
			return true;
		src_type_hash = object.get_type_hash( 5 , false );
		if( booclass::item_type::item_type::item_type::item_type::item_type::type_hash != src_type_hash )
		{
			if( src_type_hash == ::booldog::object::type_hash )
				return true;
			return false;
		}
		if( booclass::item_type::item_type::item_type::item_type::item_type::use_item_type != object.get_use_item_type( 5 ) )
			return false;
		if( ::booldog::compile::If< booclass::item_type::item_type::item_type::item_type::item_type::use_item_type == false >::test() )
			return true;
		return false;
	};
};
#endif
