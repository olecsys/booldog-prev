#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define test_rpr_cp1251 -16 , -17 , -16
#define test_Apr_cp1251 -64 , -17 , -16
#define test_0Apr_cp1251 48 , -64 , -17 , -16
#define test_rpr_utf8 -47 , -128 , -48 , -65 , -47 , -128
#define test_Apr_utf8 -48 , -112 , -48 , -65 , -47 , -128
#define test_0Apr_utf8 48 , -48 , -112 , -48 , -65 , -47 , -128
#define test_rpr_utf16 64 , 4 , 63 , 4 , 64 , 4
#define test_Apr_utf16 16 , 4 , 63 , 4 , 64 , 4
#define test_Apr_utf32 16 , 4 , 0 , 0 , 63 , 4 , 0 , 0 , 64 , 4 , 0 , 0

#define test_0Apr_utf16 48 , 0 , 16 , 4 , 63 , 4 , 64 , 4
#define test_il_cp1251 -27 , -21 , -4
#define test_0il_cp1251 48 , -27 , -21 , -4
#define test_il0_cp1251 -27 , -21 , -4 , 48
#define test_il_utf8 -48 , -75 , -48 , -69 , -47 , -116
#define test_0il_utf8 48 , -48 , -75 , -48 , -69 , -47 , -116
#define test_il0_utf8 -48 , -75 , -48 , -69 , -47 , -116 , 48
#define test_il_utf16 53 , 4 , 59 , 4 , 76 , 4
#define test_il_utf32 53 , 4 , 0 , 0 , 59 , 4 , 0 , 0 , 76 , 4 , 0 , 0

#define test_0il_utf16 48 , 0 , 53 , 4 , 59 , 4 , 76 , 4
#define test_il0_utf16 53 , 4 , 59 , 4 , 76 , 4 , 48 , 0
char utf8_AprilApril_var[] =
{
	test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , 0
};

char cp1251_April_var[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , 0 
};
char utf8_April_var[] = 
{
	test_Apr_utf8 , test_il_utf8 , 0
};
char utf16_April_var[] = 
{
	test_Apr_utf16 , test_il_utf16 , 0 , 0
};
char utf32_April_var[] = 
{
	test_Apr_utf32 , test_il_utf32 , 0 , 0 , 0 , 0
};

char cp1251_Aprilil_var[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_il_cp1251 , 0 
};
char utf8_Aprilil_var[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_il_utf8 , 0
};
char utf16_Aprilil_var[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_il_utf16 , 0 , 0
};
char utf32_Aprilil_var[] = 
{
	test_Apr_utf32 , test_il_utf32 , test_il_utf32 , 0 , 0 , 0 , 0
};


char utf8_AprilAprilApril_var[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , 0 
};

char utf8_ililil_var[] = 
{
	test_il_utf8 , test_il_utf8 , test_il_utf8 , 0 
};

char utf8_ilililililil_var[] = 
{
	test_il_utf8 , test_il_utf8 , test_il_utf8 , test_il_utf8 , test_il_utf8 , test_il_utf8 , 0 
};

char utf8_AprAprilAprAprilAprApril_var[] = 
{
	test_Apr_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_Apr_utf8 , test_il_utf8 , 0 
};

char cp1251_il_var[] = 
{
	test_il_cp1251 , 0 
};
char utf8_il_var[] = 
{
	test_il_utf8 , 0
};
char utf16_il_var[] = 
{
	test_il_utf16 , 0 , 0
};
char utf32_il_var[] = 
{
	test_il_utf32 , 0 , 0 , 0 , 0
};

char cp1251_Apr_var[] = 
{
	test_Apr_cp1251 , 0 
};
char utf8_Apr_var[] = 
{
	test_Apr_utf8 , 0
};
char utf16_Apr_var[] = 
{
	test_Apr_utf16 , 0 , 0
};
char utf32_Apr_var[] = 
{
	test_Apr_utf32 , 0 , 0 , 0 , 0
};

char utf8_TESTApril_var[] = 
{
	'T' , 'E' , 'S' , 'T' , test_Apr_utf8 , test_il_utf8 , 0
};

char utf8_TESTApr_var[] = 
{
	'T' , 'E' , 'S' , 'T' , test_Apr_utf8 , 0
};

char utf8_TESTil_var[] = 
{
	'T' , 'E' , 'S' , 'T' , test_il_utf8 , 0
};

#define BOOLDOG_STRING_TEST

#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_object.h)
#include BOOLDOG_HEADER(boo_thread.h)
#include BOOLDOG_HEADER(boo_if.h)
#include BOOLDOG_HEADER(boo_check.h)
#include BOOLDOG_HEADER(boo_string.h)
#include BOOLDOG_HEADER(boo_list.h)
#include BOOLDOG_HEADER(boo_stack_allocator.h)
#include BOOLDOG_HEADER(boo_heap_allocator.h)
#include BOOLDOG_HEADER(boo_mixed_allocator.h)
#include BOOLDOG_HEADER(boo_mem.h)
#include BOOLDOG_HEADER(boo_base_loader.h)
#include BOOLDOG_HEADER(boo_module_utils.h)
#include BOOLDOG_HEADER(boo_executable_utils.h)
#include BOOLDOG_HEADER(boo_io_utils.h)
#include BOOLDOG_HEADER(boo_array.h)
#include BOOLDOG_HEADER(boo_param.h)
#include BOOLDOG_HEADER(boo_string_utils.h)
#include BOOLDOG_HEADER(boo_error_format.h)
#include BOOLDOG_HEADER(boo_json.h)
#include BOOLDOG_HEADER(boo_io_file.h)
#include BOOLDOG_HEADER(boo_bits_utils.h)
#include BOOLDOG_HEADER(boo_time_utils.h)
#include BOOLDOG_HEADER(boo_doubly_linked_list.h)
#include BOOLDOG_HEADER(boo_threading_event.h)
#include BOOLDOG_HEADER(boo_network_utils.h)
#include BOOLDOG_HEADER(boo_hash_md5.h)
TEST_CASE("boo_bits_utilsTest", "test")
{
	::booldog::byte eq = 0;

	::booldog::byte res = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , BOOLDOG_MEM_INFO_HEAP 
		, BOOLDOG_MEM_INFO_USE_INFO1 , BOOLDOG_MEM_INFO_BUSY >::value;

	eq = 0;
	::booldog::utils::set_bit( eq , BOOLDOG_MEM_INFO_HEAP );
	::booldog::utils::set_bit( eq , BOOLDOG_MEM_INFO_USE_INFO1 );
	::booldog::utils::set_bit( eq , BOOLDOG_MEM_INFO_BUSY );

	REQUIRE( res == eq );

	res = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
		, 8 * sizeof( ::booldog::byte ) >::value;

	eq = 0;
	::booldog::utils::set_bit( eq , 8 * sizeof( ::booldog::byte ) );

	REQUIRE( res == eq );


	res = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , BOOLDOG_MEM_INFO_HEAP 
		, BOOLDOG_MEM_INFO_USE_INFO3 , BOOLDOG_MEM_INFO_BUSY >::value;
	
	eq = 0;
	::booldog::utils::set_bit( eq , BOOLDOG_MEM_INFO_HEAP );
	::booldog::utils::set_bit( eq , BOOLDOG_MEM_INFO_USE_INFO3 );
	::booldog::utils::set_bit( eq , BOOLDOG_MEM_INFO_BUSY );

	REQUIRE( res == eq );
		
	res = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , BOOLDOG_MEM_INFO_USE_INFO1 >::value;
	

	eq = 0;
	::booldog::utils::set_bit( eq , BOOLDOG_MEM_INFO_USE_INFO1 );

	REQUIRE( res == eq );

		
	res = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte , BOOLDOG_MEM_INFO_USE_INFO2 >::value;
	
	eq = 0;
	::booldog::utils::set_bit( eq , BOOLDOG_MEM_INFO_USE_INFO2 );

	REQUIRE( res == eq );


	res = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
		, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED 
		, BOOLDOG_DATA_JSON_ROOT >::value;

	eq = 0;

	::booldog::utils::set_bit( eq , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
	::booldog::utils::set_bit( eq , BOOLDOG_DATA_JSON_NAME_SERIALIZED );
	::booldog::utils::set_bit( eq , BOOLDOG_DATA_JSON_ROOT );

	REQUIRE( res == eq );
};
TEST_CASE("boo_paramTest", "test")
{
	booldog::int32 int32value = 0;
	booldog::uint32 uint32value = 0;
	bool boolvalue = 0;
	booldog::uchar ucharvalue = 0;
	short shortvalue = 0;
	booldog::ushort ushortvalue = 0;
	booldog::int64 int64value = 0;
	booldog::uint64 uint64value = 0;
	booldog::param p0[] =
	{
		BOOPARAM_INT32( -32 ) , 
		BOOPARAM_BOOL( false ) ,
		BOOPARAM_CHAR( -127 ) ,
		BOOPARAM_UCHAR( 128 ) , 
		BOOPARAM_SHORT( -1986 ) ,
		BOOPARAM_USHORT( 1986 ) ,
		BOOPARAM_INT64( -123456789 ) ,
		BOOPARAM_UINT64( 123456789 ) ,
		BOOPARAM_WCHAR( L'W' ) ,
		BOOPARAM_PCHAR( "hello" ) ,
		BOOPARAM_PWCHAR( L"hello" ) ,
		BOOPARAM_PVOID( &p0 ) ,
		//BOOPARAM_PNAMED_PARAM( val ) ,
		BOOPARAM_PPARAM( p0 ) ,
		BOOPARAM_PINT32( &int32value ) ,
		BOOPARAM_PUINT32( &uint32value ) ,
		BOOPARAM_PBOOL( &boolvalue ) ,
		BOOPARAM_PUCHAR( &ucharvalue ) ,
		BOOPARAM_PSHORT( &shortvalue ) ,
		BOOPARAM_PUSHORT( &ushortvalue ) ,
		BOOPARAM_PINT64( &int64value ) ,
		BOOPARAM_PUINT64( &uint64value ) ,
		BOOPARAM_NONE
	};

	size_t index = 0;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_int32 );

	REQUIRE( p0[ index ].int32value == -32 );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_bool );

	REQUIRE( p0[ index ].boolvalue == false );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_char );

	REQUIRE( p0[ index ].charvalue == -127 );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_uchar );

	REQUIRE( p0[ index ].ucharvalue == 128 );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_short );

	REQUIRE( p0[ index ].shortvalue == -1986 );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_ushort );

	REQUIRE( p0[ index ].ushortvalue == 1986 );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_int64 );

	REQUIRE( p0[ index ].int64value == -123456789 );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_uint64 );

	REQUIRE( p0[ index ].uint64value == 123456789 );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_wchar );

	REQUIRE( p0[ index ].wcharvalue == L'W' );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_pchar );

	REQUIRE( strcmp( p0[ index ].pcharvalue , "hello" ) == 0 );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_pwchar );

	REQUIRE( wcscmp( p0[ index ].pwcharvalue , L"hello" ) == 0 );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_pvoid );

	REQUIRE( p0[ index ].pvoidvalue == &p0 );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_pparam );

	REQUIRE( p0[ index ].pparamvalue == p0 );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_pint32 );

	REQUIRE( p0[ index ].pint32value == &int32value );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_puint32 );

	REQUIRE( p0[ index ].puint32value == &uint32value );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_pbool );

	REQUIRE( p0[ index ].pboolvalue == &boolvalue );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_puchar );

	REQUIRE( p0[ index ].pucharvalue == &ucharvalue );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_pshort );

	REQUIRE( p0[ index ].pshortvalue == &shortvalue );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_pushort );

	REQUIRE( p0[ index ].pushortvalue == &ushortvalue );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_pint64 );

	REQUIRE( p0[ index ].pint64value == &int64value );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_puint64 );

	REQUIRE( p0[ index ].puint64value == &uint64value );

	index++;

	REQUIRE( p0[ index ].type == ::booldog::enums::param::type_none );


	booldog::named_param p1[] =
	{
		BOONAMED_PARAM_INT32( "test0" , -32 ) , 
		BOONAMED_PARAM_BOOL( "test1" , false ) ,
		BOONAMED_PARAM_CHAR( "test2" , -127 ) ,
		BOONAMED_PARAM_UCHAR( "test3" , 128 ) , 
		BOONAMED_PARAM_SHORT( "test4" , -1986 ) ,
		BOONAMED_PARAM_USHORT( "test5" , 1986 ) ,
		BOONAMED_PARAM_INT64( "test6" , -123456789 ) ,
		BOONAMED_PARAM_UINT64( "test7" , 123456789 ) ,
		BOONAMED_PARAM_WCHAR( "test8" , L'W' ) ,
		BOONAMED_PARAM_PCHAR( "test9" , "hello" ) ,
		BOONAMED_PARAM_PWCHAR( "test10" , L"hello" ) ,
		BOONAMED_PARAM_PVOID( "test11" , &p0 ) ,
		BOONAMED_PARAM_PNAMED_PARAM( "test12" , &p1 ) ,
		BOONAMED_PARAM_PPARAM( "test13" , p0 ) ,
		BOONAMED_PARAM_PINT32( "test14" , &int32value ) ,
		BOONAMED_PARAM_PUINT32( "test15" , &uint32value ) ,
		BOONAMED_PARAM_PBOOL( "test16" , &boolvalue ) ,
		BOONAMED_PARAM_PUCHAR( "test17" , &ucharvalue ) ,
		BOONAMED_PARAM_PSHORT( "test18" , &shortvalue ) ,
		BOONAMED_PARAM_PUSHORT( "test19" , &ushortvalue ) ,
		BOONAMED_PARAM_PINT64( "test20" , &int64value ) ,
		BOONAMED_PARAM_PUINT64( "test21" , &uint64value ) ,
		BOONAMED_PARAM_NONE
	};

	index = 0;

	REQUIRE( strcmp( p1[ index ].name , "test0" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_int32 );

	REQUIRE( p1[ index ].int32value == -32 );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test1" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_bool );

	REQUIRE( p1[ index ].boolvalue == false );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test2" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_char );

	REQUIRE( p1[ index ].charvalue == -127 );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test3" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_uchar );

	REQUIRE( p1[ index ].ucharvalue == 128 );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test4" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_short );

	REQUIRE( p1[ index ].shortvalue == -1986 );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test5" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_ushort );

	REQUIRE( p1[ index ].ushortvalue == 1986 );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test6" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_int64 );

	REQUIRE( p1[ index ].int64value == -123456789 );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test7" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_uint64 );

	REQUIRE( p1[ index ].uint64value == 123456789 );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test8" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_wchar );

	REQUIRE( p1[ index ].wcharvalue == L'W' );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test9" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_pchar );

	REQUIRE( strcmp( p1[ index ].pcharvalue , "hello" ) == 0 );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test10" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_pwchar );

	REQUIRE( wcscmp( p1[ index ].pwcharvalue , L"hello" ) == 0 );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test11" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_pvoid );

	REQUIRE( p1[ index ].pvoidvalue == &p0 );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test12" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_pnamed_param );

	REQUIRE( p1[ index ].pnamed_paramvalue == p1 );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test13" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_pparam );

	REQUIRE( p1[ index ].pparamvalue == p0 );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test14" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_pint32 );

	REQUIRE( p1[ index ].pint32value == &int32value );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test15" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_puint32 );

	REQUIRE( p1[ index ].puint32value == &uint32value );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test16" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_pbool );

	REQUIRE( p1[ index ].pboolvalue == &boolvalue );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test17" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_puchar );

	REQUIRE( p1[ index ].pucharvalue == &ucharvalue );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test18" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_pshort );

	REQUIRE( p1[ index ].pshortvalue == &shortvalue );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test19" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_pushort );

	REQUIRE( p1[ index ].pushortvalue == &ushortvalue );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test20" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_pint64 );

	REQUIRE( p1[ index ].pint64value == &int64value );

	index++;

	REQUIRE( strcmp( p1[ index ].name , "test21" ) == 0 );

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_puint64 );

	REQUIRE( p1[ index ].puint64value == &uint64value );

	index++;

	REQUIRE( p1[ index ].type == ::booldog::enums::param::type_none );


	booldog::named_param p2[] =
	{
		BOO_SEARCH_NAMED_PARAM_BOOL( "not found test1" ) ,
		BOO_SEARCH_NAMED_PARAM_INT32( "test0" ) , 
		BOO_SEARCH_NAMED_PARAM_BOOL( "test1" ) ,
		BOO_SEARCH_NAMED_PARAM_CHAR( "test2" ) ,
		BOO_SEARCH_NAMED_PARAM_UCHAR( "test3" ) , 
		BOO_SEARCH_NAMED_PARAM_SHORT( "test4" ) ,
		BOO_SEARCH_NAMED_PARAM_USHORT( "test5" ) ,
		BOO_SEARCH_NAMED_PARAM_INT64( "test6" ) ,
		BOO_SEARCH_NAMED_PARAM_UINT64( "test7" ) ,
		BOO_SEARCH_NAMED_PARAM_WCHAR( "test8" ) ,
		BOO_SEARCH_NAMED_PARAM_PCHAR( "test9" ) ,
		BOO_SEARCH_NAMED_PARAM_PWCHAR( "test10" ) ,
		BOO_SEARCH_NAMED_PARAM_PVOID( "test11" ) ,
		BOO_SEARCH_NAMED_PARAM_PNAMED_PARAM( "test12" ) ,
		BOO_SEARCH_NAMED_PARAM_PPARAM( "test13" ) ,
		BOO_SEARCH_NAMED_PARAM_PINT32( "test14" ) ,
		BOO_SEARCH_NAMED_PARAM_PUINT32( "test15" ) ,
		BOO_SEARCH_NAMED_PARAM_PBOOL( "test16" ) ,
		BOO_SEARCH_NAMED_PARAM_PUCHAR( "test17" ) ,
		BOO_SEARCH_NAMED_PARAM_PSHORT( "test18" ) ,
		BOO_SEARCH_NAMED_PARAM_PUSHORT( "test19" ) ,
		BOO_SEARCH_NAMED_PARAM_PINT64( "test20" ) ,
		BOO_SEARCH_NAMED_PARAM_PUINT64( "test21" ) ,
		BOO_SEARCH_NAMED_PARAM_NONE
	};

	::booldog::utils::param::search( p1 , p2 );

	index = 0;

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_not_found );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test0" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_int32 );

	REQUIRE( p2[ index ].int32value == -32 );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test1" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_bool );

	REQUIRE( p2[ index ].boolvalue == false );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test2" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_char );

	REQUIRE( p2[ index ].charvalue == -127 );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test3" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_uchar );

	REQUIRE( p2[ index ].ucharvalue == 128 );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test4" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_short );

	REQUIRE( p2[ index ].shortvalue == -1986 );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test5" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_ushort );

	REQUIRE( p2[ index ].ushortvalue == 1986 );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test6" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_int64 );

	REQUIRE( p2[ index ].int64value == -123456789 );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test7" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_uint64 );

	REQUIRE( p2[ index ].uint64value == 123456789 );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test8" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_wchar );

	REQUIRE( p2[ index ].wcharvalue == L'W' );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test9" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_pchar );

	REQUIRE( strcmp( p2[ index ].pcharvalue , "hello" ) == 0 );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test10" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_pwchar );

	REQUIRE( wcscmp( p2[ index ].pwcharvalue , L"hello" ) == 0 );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test11" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_pvoid );

	REQUIRE( p2[ index ].pvoidvalue == &p0 );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test12" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_pnamed_param );

	REQUIRE( p2[ index ].pnamed_paramvalue == p1 );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test13" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_pparam );

	REQUIRE( p2[ index ].pparamvalue == p0 );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test14" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_pint32 );

	REQUIRE( p2[ index ].pint32value == &int32value );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test15" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_puint32 );

	REQUIRE( p2[ index ].puint32value == &uint32value );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test16" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_pbool );

	REQUIRE( p2[ index ].pboolvalue == &boolvalue );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test17" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_puchar );

	REQUIRE( p2[ index ].pucharvalue == &ucharvalue );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test18" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_pshort );

	REQUIRE( p2[ index ].pshortvalue == &shortvalue );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test19" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_pushort );

	REQUIRE( p2[ index ].pushortvalue == &ushortvalue );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test20" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_pint64 );

	REQUIRE( p2[ index ].pint64value == &int64value );

	index++;

	REQUIRE( strcmp( p2[ index ].name , "test21" ) == 0 );

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_puint64 );

	REQUIRE( p2[ index ].puint64value == &uint64value );

	index++;

	REQUIRE( p2[ index ].type == ::booldog::enums::param::type_none );

};

#define boo_stackTestAllocatorSize 64

TEST_CASE("boo_threading_eventTest", "test")
{
	{
		::booldog::threading::event evt( 0 , debuginfo_macros );

		::booldog::uint64 time = ::booldog::utils::time::posix::now_as_utc();

		REQUIRE( evt.sleep( 0 , 5000 , debuginfo_macros ) );

		REQUIRE( ::booldog::utils::time::posix::now_as_utc() - time > 4999999 );
	}
};

TEST_CASE("boo_stackTest", "test")
{
	::booldog::allocators::stack< boo_stackTestAllocatorSize > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	void* ptr0 = allocator.alloc( boo_stackTestAllocatorSize );

	size_t ptr0_mswi = ::booldog::mem::info::memory_size_with_info( boo_stackTestAllocatorSize );
	size_t ptr0_mis = ::booldog::mem::info::memory_info_size( boo_stackTestAllocatorSize );

	REQUIRE( allocator.begin() == begin + ptr0_mswi );

	REQUIRE( ptr0 == ( begin + ptr0_mis ) );

	REQUIRE( allocator.available() == total - ptr0_mswi );

	size_t ptr1_mswi = ::booldog::mem::info::memory_size_with_info( 17 );
	size_t ptr1_mis = ::booldog::mem::info::memory_info_size( 17 );

	void* ptr1 = allocator.alloc( 17 );

	REQUIRE( allocator.begin() == begin + ptr0_mswi );

	REQUIRE( ptr1 == 0 );

	REQUIRE( allocator.available() == total - ptr0_mswi );

	allocator.free( ptr0 );

	REQUIRE( allocator.begin() == begin );

	REQUIRE( allocator.available() == total );

	ptr0 = allocator.alloc( 23 );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 23 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 23 );

	REQUIRE( allocator.begin() == begin + ptr0_mswi );

	REQUIRE( ptr0 == begin + ptr0_mis );

	REQUIRE( allocator.available() == total - ptr0_mswi );

	ptr1 = allocator.alloc( 17 );

	ptr1_mswi = ::booldog::mem::info::memory_size_with_info( 17 );
	ptr1_mis = ::booldog::mem::info::memory_info_size( 17 );

	REQUIRE( allocator.begin() == begin + ptr0_mswi + ptr1_mswi );

	REQUIRE( ptr1 == begin + ptr0_mswi + ptr1_mis );

	REQUIRE( allocator.available() == total - ptr0_mswi - ptr1_mswi );

	allocator.free( ptr0 );

	REQUIRE( allocator.begin() == begin );

	REQUIRE( allocator.available() == total - ptr1_mswi );

	allocator.free( ptr1 );

	ptr1 = 0;

	REQUIRE( allocator.begin() == begin );

	REQUIRE( allocator.available() == total );

	ptr0 = allocator.alloc( 45 );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 45 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 45 );

	REQUIRE( allocator.begin() == begin + ptr0_mswi );

	REQUIRE( ptr0 == begin + ptr0_mis );

	REQUIRE( allocator.available() == total - ptr0_mswi );

	allocator.free( ptr0 );

	REQUIRE( allocator.begin() == begin );

	REQUIRE( allocator.available() == total );


	ptr0 = 0;

	ptr0 = allocator.realloc( ptr0 , 45 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 45 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 45 );

	REQUIRE( allocator.begin() == begin + ptr0_mswi );

	REQUIRE( ptr0 == begin + ptr0_mis );

	REQUIRE( allocator.available() == total - ptr0_mswi );

	ptr0 = allocator.realloc( ptr0 , 45 );

	REQUIRE( allocator.begin() == begin + ptr0_mswi );

	REQUIRE( ptr0 == begin + ptr0_mis );

	REQUIRE( allocator.available() == total - ptr0_mswi );

	ptr0 = allocator.realloc( ptr0 , 50 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 50 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 50 );

	REQUIRE( allocator.begin() == begin + ptr0_mswi );

	REQUIRE( ptr0 == begin + ptr0_mis );

	REQUIRE( allocator.available() == total - ptr0_mswi );

	ptr0 = allocator.realloc( ptr0 , 45 );
	//ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 45 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 45 );

	REQUIRE( allocator.begin() == begin + ptr0_mswi );

	REQUIRE( ptr0 == ( begin + ptr0_mis ) );

	REQUIRE( allocator.available() == total - ptr0_mswi );

	allocator.free( ptr0 );

	ptr0 = 0;

	REQUIRE( allocator.begin() == begin );

	REQUIRE( allocator.available() == total );


	ptr0 = allocator.realloc_array< wchar_t >( (wchar_t*)ptr0 , 11 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 11 * sizeof( wchar_t ) );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 11 * sizeof( wchar_t ) );

	REQUIRE( allocator.begin() == begin + ptr0_mswi );

	REQUIRE( ptr0 == ( begin + ptr0_mis ) );

	REQUIRE( allocator.available() == total - ptr0_mswi );

	allocator.free( ptr0 );

	ptr0 = 0;

	REQUIRE( allocator.begin() == begin );

	REQUIRE( allocator.available() == total );





	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 6 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 8 * 4 );

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE( allocator.available() == total );
	}


	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 6 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 8 );

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE( allocator.available() == total );
	}


	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 7 * 4 );
		
		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE( allocator.available() == total );
	}

	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 * 4 );
		
		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE( allocator.available() == total );
	}

	{
		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 3 * 4 );		

		allocator.free( ptr1 );

		ptr1 = 0;

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE( allocator.available() == total );
	}

	{
		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 3 * 4 );		

		allocator.free( ptr1 );

		ptr1 = 0;


		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 * 4 );

		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 6 * 4 );

		allocator.free( ptr1 );

		ptr1 = 0;


		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 2 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 7 * 4 );

		allocator.free( ptr1 );

		ptr1 = 0;

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE( allocator.available() == total );
	}



	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 7 );

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE( allocator.available() == total );
	}

	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 );

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE( allocator.available() == total );
	}

	{
		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 3 );

		allocator.free( ptr1 );

		ptr1 = 0;

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE( allocator.available() == total );
	}

	{
		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 3 );

		allocator.free( ptr1 );

		ptr1 = 0;


		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 );


		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 6 );

		allocator.free( ptr1 );

		ptr1 = 0;


		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 2 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 7 );

		allocator.free( ptr1 );

		ptr1 = 0;


		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE( allocator.available() == total );
	}

	REQUIRE( allocator.begin() == begin );
		
	REQUIRE( allocator.available() == total );
};
TEST_CASE("boo_network_utilsTest", "test")
{
	::booldog::result resres;

	size_t ipstrlen = 0;
	char ipstr[ 16 ] = {0};

	REQUIRE( ::booldog::utils::network::ip( &resres , ipstr , ipstrlen , sizeof( ipstr ) , 2130706433 , debuginfo_macros ) );

	REQUIRE( ipstrlen == 9 );

	REQUIRE( strcmp( ipstr , "127.0.0.1" ) == 0 );
};
TEST_CASE("boo_allocators_heapTest", "test")
{
	::booldog::allocators::easy::heap allocator;

	void* ptr0 = allocator.alloc( boo_stackTestAllocatorSize );

	size_t ptr0_mswi = ::booldog::mem::info::memory_size_with_info( boo_stackTestAllocatorSize );
	size_t ptr0_mis = ::booldog::mem::info::memory_info_size( boo_stackTestAllocatorSize );
	
	REQUIRE_FALSE( ptr0 == 0 );

	REQUIRE( allocator.size_of_allocated_memory() == ptr0_mswi );

	size_t ptr1_mswi = ::booldog::mem::info::memory_size_with_info( 17 );
	size_t ptr1_mis = ::booldog::mem::info::memory_info_size( 17 );

	void* ptr1 = allocator.alloc( 17 );

	REQUIRE_FALSE( ptr1 == 0 );

	REQUIRE( allocator.size_of_allocated_memory() == ptr0_mswi + ptr1_mswi );

	allocator.free( ptr0 );

	REQUIRE( allocator.size_of_allocated_memory() == ptr1_mswi );

	allocator.free( ptr1 );

	REQUIRE( allocator.size_of_allocated_memory() == 0 );


	ptr0 = allocator.alloc( 23 );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 23 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 23 );

	REQUIRE_FALSE( ptr0 == 0 );

	REQUIRE( allocator.size_of_allocated_memory() == ptr0_mswi );


	ptr1 = allocator.alloc( 17 );

	ptr1_mswi = ::booldog::mem::info::memory_size_with_info( 17 );
	ptr1_mis = ::booldog::mem::info::memory_info_size( 17 );

	REQUIRE_FALSE( ptr1 == 0 );

	REQUIRE( allocator.size_of_allocated_memory() == ptr0_mswi + ptr1_mswi );


	allocator.free( ptr0 );

	REQUIRE( allocator.size_of_allocated_memory() == ptr1_mswi );

	allocator.free( ptr1 );

	ptr1 = 0;

	REQUIRE( allocator.size_of_allocated_memory() == 0 );


	ptr0 = allocator.alloc( 45 );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 45 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 45 );

	REQUIRE_FALSE( ptr0 == 0 );

	REQUIRE( allocator.size_of_allocated_memory() == ptr0_mswi );

	allocator.free( ptr0 );

	REQUIRE( allocator.size_of_allocated_memory() == 0 );


	ptr0 = 0;

	ptr0 = allocator.realloc( ptr0 , 45 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 45 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 45 );

	REQUIRE_FALSE( ptr0 == 0 );

	REQUIRE( allocator.size_of_allocated_memory() == ptr0_mswi );

	ptr0 = allocator.realloc( ptr0 , 45 );

	REQUIRE_FALSE( ptr0 == 0 );

	REQUIRE( allocator.size_of_allocated_memory() == ptr0_mswi );


	ptr0 = allocator.realloc( ptr0 , 50 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 50 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 50 );

	REQUIRE_FALSE( ptr0 == 0 );

	REQUIRE( allocator.size_of_allocated_memory() == ptr0_mswi );


	ptr0 = allocator.realloc( ptr0 , 45 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 45 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 45 );

	REQUIRE_FALSE( ptr0 == 0 );

	REQUIRE( allocator.size_of_allocated_memory() == ptr0_mswi );

	allocator.free( ptr0 );

	ptr0 = 0;

	REQUIRE( allocator.size_of_allocated_memory() == 0 );


	ptr0 = allocator.realloc_array< wchar_t >( (wchar_t*)ptr0 , 11 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 11 * sizeof( wchar_t ) );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 11 * sizeof( wchar_t ) );

	REQUIRE_FALSE( ptr0 == 0 );

	REQUIRE( allocator.size_of_allocated_memory() == ptr0_mswi );

	allocator.free( ptr0 );

	ptr0 = 0;

	REQUIRE( allocator.size_of_allocated_memory() == 0 );





	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 6 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 8 * 4 );

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.size_of_allocated_memory() == 0 );
	}


	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 6 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 8 );

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.size_of_allocated_memory() == 0 );
	}


	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 7 * 4 );
		
		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.size_of_allocated_memory() == 0 );
	}

	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 * 4 );
		
		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.size_of_allocated_memory() == 0 );
	}

	{
		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 3 * 4 );		

		allocator.free( ptr1 );

		ptr1 = 0;

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.size_of_allocated_memory() == 0 );
	}

	{
		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 3 * 4 );		

		allocator.free( ptr1 );

		ptr1 = 0;


		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 * 4 );

		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 6 * 4 );

		allocator.free( ptr1 );

		ptr1 = 0;


		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 2 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 7 * 4 );

		allocator.free( ptr1 );

		ptr1 = 0;

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.size_of_allocated_memory() == 0 );
	}



	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 7 );

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.size_of_allocated_memory() == 0 );
	}

	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 );

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.size_of_allocated_memory() == 0 );
	}

	{
		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 3 );

		allocator.free( ptr1 );

		ptr1 = 0;

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.size_of_allocated_memory() == 0 );
	}

	{
		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 3 );

		allocator.free( ptr1 );

		ptr1 = 0;


		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 );


		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 6 );

		allocator.free( ptr1 );

		ptr1 = 0;


		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 2 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 7 );

		allocator.free( ptr1 );

		ptr1 = 0;


		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.size_of_allocated_memory() == 0 );
	}

	{
		printf( "sizeof(info1)=%d\n" , sizeof( ::booldog::mem::info1 ) );

		printf( "sizeof(info2)=%d\n" , sizeof( ::booldog::mem::info2 ) );

		printf( "sizeof(info3)=%d\n" , sizeof( ::booldog::mem::info3 ) );

		printf( "sizeof(info4)=%d\n" , sizeof( ::booldog::mem::info4 ) );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 83076 - sizeof( ::booldog::mem::info3 ) );

		REQUIRE( allocator.gettotalsize( ptr0 ) == 83076 );

		allocator.free( ptr0 );

		ptr0 = 0;
	}

	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 563 );

		int checker = 1986;
		::memcpy( &((char*)ptr0)[ 233 - sizeof( int ) ] , &checker , sizeof( int ) ); 

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 233 );

		REQUIRE( ::memcmp( &((char*)ptr0)[ 233 - sizeof( int ) ] , &checker , sizeof( int ) ) == 0 );

		allocator.free( ptr0 );

		ptr0 = 0;


		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 563 );

		::memcpy( &((char*)ptr0)[ 254 - sizeof( int ) ] , &checker , sizeof( int ) ); 

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 254 );

		REQUIRE( ::memcmp( &((char*)ptr0)[ 254 - sizeof( int ) ] , &checker , sizeof( int ) ) == 0 );

		allocator.free( ptr0 );

		ptr0 = 0;


		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 70000 );

		::memcpy( &((char*)ptr0)[ 233 - sizeof( int ) ] , &checker , sizeof( int ) ); 

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 233 );

		REQUIRE( ::memcmp( &((char*)ptr0)[ 233 - sizeof( int ) ] , &checker , sizeof( int ) ) == 0 );

		allocator.free( ptr0 );

		ptr0 = 0;


		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 70000 );

		::memcpy( &((char*)ptr0)[ 254 - sizeof( int ) ] , &checker , sizeof( int ) ); 

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 254 );

		REQUIRE( ::memcmp( &((char*)ptr0)[ 254 - sizeof( int ) ] , &checker , sizeof( int ) ) == 0 );

		allocator.free( ptr0 );

		ptr0 = 0;

		REQUIRE( allocator.size_of_allocated_memory() == 0 );
	}

	REQUIRE( allocator.size_of_allocated_memory() == 0 );
};
TEST_CASE("boo_allocators_mixedTest", "test")
{
	::booldog::allocators::easy::heap heap;
	::booldog::allocators::mixed< 32 > mixed( &heap );

	size_t total = mixed.stack.available();

	char* begin = (char*)mixed.stack.begin();

	size_t size = 17;

	void* ptr0 = mixed.alloc( size );

	size_t ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	size_t ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == 0 );

	REQUIRE( mixed.stack.begin() == begin + ptr0_mswi );

	REQUIRE( ptr0 == ( begin + ptr0_mis ) );

	REQUIRE( mixed.stack.available() == total - ptr0_mswi );


	size = 1475;

	void* ptr2 = mixed.alloc( size );

	size_t ptr2_mswi = ::booldog::mem::info::memory_size_with_info( size );

	REQUIRE_FALSE( ptr2 == 0 );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == ptr2_mswi );


	size = 4;

	void* ptr1 = mixed.alloc( size );

	size_t ptr1_mswi = ::booldog::mem::info::memory_size_with_info( size );
	size_t ptr1_mis = ::booldog::mem::info::memory_info_size( size );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == ptr2_mswi );

	REQUIRE( mixed.stack.begin() == begin + ptr0_mswi + ptr1_mswi );

	REQUIRE( ptr1 == ( begin + ptr1_mis + ptr0_mswi ) );

	REQUIRE( mixed.stack.available() == total - ptr0_mswi - ptr1_mswi );
	

	mixed.free( ptr1 );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == ptr2_mswi );

	REQUIRE( mixed.stack.begin() == begin + ptr0_mswi );

	REQUIRE( mixed.stack.available() == total - ptr0_mswi );


	mixed.free( ptr0 );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == ptr2_mswi );

	REQUIRE( mixed.stack.begin() == begin );

	REQUIRE( mixed.stack.available() == total );


	mixed.free( ptr2 );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == 0 );

	REQUIRE( mixed.stack.begin() == begin );

	REQUIRE( mixed.stack.available() == total );
	

	ptr0 = 0;

	size = 17;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == 0 );

	REQUIRE( mixed.stack.begin() == begin + ptr0_mswi );

	REQUIRE( ptr0 == ( begin + ptr0_mis ) );

	REQUIRE( mixed.stack.available() == total - ptr0_mswi );


	size = 11;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == 0 );

	REQUIRE( mixed.stack.begin() == begin + ptr0_mswi );

	REQUIRE( ptr0 == ( begin + ptr0_mis ) );

	REQUIRE( mixed.stack.available() == total - ptr0_mswi );


	size = 26;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == 0 );

	REQUIRE( mixed.stack.begin() == begin + ptr0_mswi );

	REQUIRE( ptr0 == ( begin + ptr0_mis ) );

	REQUIRE( mixed.stack.available() == total - ptr0_mswi );


	size = 0;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == 0 );

	REQUIRE( mixed.stack.begin() == begin );

	REQUIRE( ptr0 == 0 );

	REQUIRE( mixed.stack.available() == total );


	size = 176;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == ptr0_mswi );

	REQUIRE( mixed.stack.begin() == begin );

	REQUIRE_FALSE( ptr0 == 0 );

	REQUIRE( mixed.stack.available() == total );


	size = 17;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == ptr0_mswi );

	REQUIRE( mixed.stack.begin() == begin );

	REQUIRE_FALSE( ptr0 == 0 );

	REQUIRE( mixed.stack.available() == total );


	size = 298;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == ptr0_mswi );

	REQUIRE( mixed.stack.begin() == begin );

	REQUIRE_FALSE( ptr0 == 0 );

	REQUIRE( mixed.stack.available() == total );


	size = 0;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == 0 );

	REQUIRE( mixed.stack.begin() == begin );

	REQUIRE( ptr0 == 0 );

	REQUIRE( mixed.stack.available() == total );




	REQUIRE( mixed.holder.heap->size_of_allocated_memory() == 0 );

	REQUIRE( mixed.stack.begin() == begin );

	REQUIRE( mixed.stack.available() == total );

	{
		::booldog::allocators::single_threaded::mixed< 512 > mixed(&heap);

		void* ptr0 = mixed.realloc(0, 67);//mem_cluster::alloc, 7fffd4f92ac4(67)

		REQUIRE(mixed.check_consistency());

		ptr0 = mixed.realloc(ptr0, 318);//mem_cluster::tryrealloc, again tryrealloc, 7fffd4f92ac4(318)

		REQUIRE(mixed.check_consistency());

		ptr0 = mixed.realloc(ptr0, 843);//mem_cluster::tryrealloc, again tryrealloc, 7fffd4f92ac8(843) go to heap

		REQUIRE(mixed.check_consistency());

		void* ptr1 = mixed.realloc(0, 448);//mem_cluster::alloc, 7fffd4f92ac8(448)

		REQUIRE(mixed.check_consistency());

		ptr1 = mixed.realloc(ptr1, 896);//mem_cluster::tryrealloc, again tryrealloc, 7fffd4f92ac8(896) go to heap

		REQUIRE(mixed.check_consistency());

		void* ptr2 = mixed.realloc(0, 14);//mem_cluster::alloc, 7fffd4f92ac4(14)

		REQUIRE(mixed.check_consistency());

		void* ptr3 = mixed.realloc(0, 25);//mem_cluster::alloc, 7fffd4f92ad8(25)

		REQUIRE(mixed.check_consistency());

		void* ptr4 = mixed.realloc(0, 109);//mem_cluster::alloc, 7fffd4f92af8(109)

		REQUIRE(mixed.check_consistency());

		void* ptr5 = mixed.realloc(0, 93);//mem_cluster::alloc, 7fffd4f92b6c(93)

		REQUIRE(mixed.check_consistency());

		void* ptr6 = mixed.realloc(0, 248);//mem_cluster::alloc, 7fffd4f92bd0(248)

		REQUIRE(mixed.check_consistency());

		/*mem_cluster::free, 7fffd4f92af8
		mem_cluster::tryrealloc, 7fffd4f92bd0(246, 7fffd4f92af8)
		*/
		ptr4 = mixed.realloc(ptr4, 246);

		REQUIRE(mixed.check_consistency());

		void* ptr7 = mixed.realloc(0, 232);//mem_cluster::alloc, 7fffd4f92ccc(232)

		REQUIRE(mixed.check_consistency());

		mixed.free(ptr0);
		mixed.free(ptr1);
		mixed.free(ptr2);
		mixed.free(ptr3);
		mixed.free(ptr4);
		mixed.free(ptr5);
		mixed.free(ptr6);
		mixed.free(ptr7);
	}
};
TEST_CASE("boo_memTest", "test")
{
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	size_t dstsize = 0;
	size_t dst_allocsize = 8;
	char* dst = (char*)allocator.alloc( dst_allocsize );

	REQUIRE( ::booldog::mem::insert< char >( 0 , dst , dstsize , dst_allocsize , 0 , "Test" , 5 ) );

	dstsize = 4;

	REQUIRE( ::memcmp( "Test" , dst , dstsize ) == 0 );

	REQUIRE( ::booldog::mem::insert< char >( 1 , dst , dstsize , dst_allocsize , 0 , "r" , 1 ) );

	dstsize = 5;

	REQUIRE( ::memcmp( "Trest" , dst , dstsize ) == 0 );

	REQUIRE( ::booldog::mem::insert< char >( 8 , dst , dstsize , dst_allocsize , 0 , "#7" , 2 ) );

	dstsize = 7;

	REQUIRE( ::memcmp( "Trest#7" , dst , dstsize ) == 0 );

	REQUIRE( ::booldog::mem::insert< char >( 2 , dst , dstsize , dst_allocsize , 2 , "om" , 2 ) );

	dstsize = 7;

	REQUIRE( ::memcmp( "Tromt#7" , dst , dstsize ) == 0 );

	REQUIRE( ::booldog::mem::insert< char >( 2 , dst , dstsize , dst_allocsize , 2 , "usd" , 3 ) );

	dstsize = 8;

	REQUIRE( ::memcmp( "Trusdt#7" , dst , dstsize ) == 0 );

	REQUIRE( ::booldog::mem::insert< char >( 2 , dst , dstsize , dst_allocsize , 3 , "es" , 2 ) );

	dstsize = 7;

	REQUIRE( ::memcmp( "Trest#7" , dst , dstsize ) == 0 );

	REQUIRE( ::booldog::mem::insert< char >( 5 , dst , dstsize , dst_allocsize , 4 , "e" , 1 ) );

	dstsize = 6;

	REQUIRE( ::memcmp( "Treste" , dst , dstsize ) == 0 );

	REQUIRE_FALSE( ::booldog::mem::insert< char >( 5 , dst , dstsize , dst_allocsize , 2 , "TEST00000" , 9 ) );

	dstsize = 6;

	REQUIRE( ::memcmp( "Treste" , dst , dstsize ) == 0 );

	::booldog::mem::remove< char >( 1 , dst , dstsize , 2 );

	dstsize = 4;

	REQUIRE( ::memcmp( "Tste" , dst , dstsize ) == 0 );

	::booldog::mem::remove< char >( 2 , dst , dstsize , 2 );

	dstsize = 2;

	REQUIRE( ::memcmp( "Ts" , dst , dstsize ) == 0 );


	::booldog::mem::remove< char >( 1 , dst , dstsize , 3 );

	dstsize = 1;

	REQUIRE( ::memcmp( "T" , dst , dstsize ) == 0 );


	REQUIRE( ::booldog::mem::insert< char >( 1 , dst , dstsize , dst_allocsize , 0 , "est0" , 4 ) );

	dstsize = 5;

	REQUIRE( ::memcmp( "Test0" , dst , dstsize ) == 0 );


	REQUIRE( ::booldog::mem::expand< char >( 1 , dst , dstsize , dst_allocsize , 2 ) );

	dstsize = 7;

	REQUIRE( ::memcmp( "Tesest0" , dst , dstsize ) == 0 );

	REQUIRE_FALSE( ::booldog::mem::expand< char >( 1 , dst , dstsize , dst_allocsize , 2 ) );

	dstsize = 7;

	REQUIRE( ::memcmp( "Tesest0" , dst , dstsize ) == 0 );


	allocator.free( dst );

	REQUIRE( allocator.begin() == begin );
		
	REQUIRE( allocator.available() == total );
};
TEST_CASE("boo_jsonTest", "test")
{
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();
		
	{
		::booldog::data::json::serializator serializator( &allocator );

		::booldog::data::json::result res( &serializator );

		::booldog::data::json::parse< 64 >( &res , &allocator , "{\r\n"
			"	\"databases\":\r\n"
			"	[\r\n"
			"		{\"key\":\"conf\",\"connection\":{\"hostname\":\"localhost\",\"filename\":\"configuration.db\",\"upgrade\":\"server_upgrade.sql\"}},\r\n"
			"		{\"key\":\"events\",\"connection\":{\"hostname\":\"localhost\",\"filename\":\"events.db\",\"upgrade\":\"events_upgrade.sql\"}},\r\n"
			"		{\"key\":\"ptzusers\",\"connection\":{\"hostname\":\"localhost\",\"filename\":\"ptzusers.db\",\"upgrade\":\"ptzusers_upgrade.sql\"}}\r\n"
			"	]\r\n"
			"}\r\n"
			"\r\n" );

		REQUIRE( res.succeeded() );

		::booldog::data::json::object root = (*res.serializator);

		REQUIRE( root.isobject() );

		

		::booldog::data::json::parse< 64 >( &res , &allocator , "{\"test0\":{\"test0\":-1986}}" );

		REQUIRE( res.succeeded() );

		root = (*res.serializator);

		root( "test0" )( "test0" ).name( 0 , "te" , debuginfo_macros );

		REQUIRE( strcmp( root.json , "{\"test0\":{\"te\":-1986}}" ) == 0 );

		REQUIRE( root( "test0" ).value.node->name_or_valuebegin == &res.serializator->slow.json[ 2 ] );

		REQUIRE( root( "test0" ).value.node->valueend == &res.serializator->slow.json[ 20 ] );

		REQUIRE( root( "test0" )( "te" ).value.node->name_or_valuebegin == &res.serializator->slow.json[ 11 ] );

		REQUIRE( root( "test0" )( "te" ).value.node->valueend == &res.serializator->slow.json[ 19 ] );

		REQUIRE( strcmp( root( "test0" ).json , "{\"te\":-1986}" ) == 0 );
	}

	{
		::booldog::data::json::serializator copy_serializator( &allocator );

		::booldog::data::json::serializator serializator( &allocator );

		::booldog::data::json::result res( &serializator );

		::booldog::data::json::parse< 1 >( &res , &allocator , "0" );

		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		::booldog::data::json::object root = (*res.serializator);

		const char* json = root.json;

		REQUIRE( strcmp( json , "0" ) == 0 );
		
		REQUIRE( root.isnumber() );

		::booldog::uint64 valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		::booldog::uint32 valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		::booldog::int64 valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		::booldog::int32 valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		float valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		const char* valuestring = root.value;

		REQUIRE( valuestring == 0 );

		bool valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "0" ) == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( strcmp( json , "0" ) == 0 );
		
		REQUIRE( root.isnumber() );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "0" ) == 0 );




		::booldog::data::json::parse< 1 >( &res , &allocator , "00" );

		REQUIRE_FALSE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( json == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "-0" );

		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( strcmp( json , "-0" ) == 0 );

		REQUIRE( root.isnumber() );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "-0" ) == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( strcmp( json , "-0" ) == 0 );

		REQUIRE( root.isnumber() );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "-0" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "  0.E  " );

		REQUIRE_FALSE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( json == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "-0.02" );

		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( strcmp( json , "-0.02" ) == 0 );

		REQUIRE( root.isnumber() );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == -0.02f );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "-0.02" ) == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( strcmp( json , "-0.02" ) == 0 );

		REQUIRE( root.isnumber() );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == -0.02f );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "-0.02" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "-0.02E" );

		REQUIRE_FALSE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( json == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "-0.02e0" );

		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( strcmp( json , "-0.02e0" ) == 0 );

		REQUIRE( root.isnumber() );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == -0.02f );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "-0.02e0" ) == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( strcmp( json , "-0.02e0" ) == 0 );

		REQUIRE( root.isnumber() );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == -0.02f );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "-0.02e0" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "-0.02E-3" );

		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( strcmp( json , "-0.02E-3" ) == 0 );

		REQUIRE( root.isnumber() );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( ::booldog::utils::round( valuefloat , 5 ) == -0.00002f );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "-0.02E-3" ) == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( strcmp( json , "-0.02E-3" ) == 0 );

		REQUIRE( root.isnumber() );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( ::booldog::utils::round( valuefloat , 5 ) == -0.00002f );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "-0.02E-3" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , " 1986E" );

		REQUIRE_FALSE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( json == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , " 1986E." );

		REQUIRE_FALSE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( json == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , " 1986E+" );

		REQUIRE_FALSE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( json == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , " 1986E-" );

		REQUIRE_FALSE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( json == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , " 19.86E+3" );

		REQUIRE( res.succeeded() );

		copy_serializator = serializator;
				
		root = (*res.serializator);

		json = root.json;

		REQUIRE( strcmp( json , "19.86E+3" ) == 0 );

		REQUIRE( root.isnumber() );
		
		valueuint64 = root.value;

		REQUIRE( valueuint64 == 19860 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 19860 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 19860 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 19860 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 19860.f );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "19.86E+3" ) == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( strcmp( json , "19.86E+3" ) == 0 );

		REQUIRE( root.isnumber() );
		
		valueuint64 = root.value;

		REQUIRE( valueuint64 == 19860 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 19860 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 19860 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 19860 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 19860.f );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "19.86E+3" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   [     ]   " );

		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( strcmp( json , "[]" ) == 0 );

		REQUIRE( root.isarray() );

		REQUIRE( root.count() == 0 );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "[]" ) == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( strcmp( json , "[]" ) == 0 );

		REQUIRE( root.isarray() );

		REQUIRE( root.count() == 0 );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "[]" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   {\"test0\":true,     }   " );

		REQUIRE_FALSE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( json == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   {\"test0\":[    " );

		REQUIRE_FALSE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( json == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   {\"test0\": \ttRue }    " );

		REQUIRE_FALSE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( json == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   [\"test0\",    ]    " );

		REQUIRE_FALSE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( json == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   [\"test0\",1986 ,\t  25.56   , true   , null ,  {\"1\": true  \t} , [1 , 1 , 2    ] , -21E5 , 2e-1 , 6e+4   ]    " );

		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( strcmp( json , "[\"test0\",1986,25.56,true,null,{\"1\":true},[1,1,2],-21E5,2e-1,6e+4]" ) == 0 );

		REQUIRE( root.isarray() );

		REQUIRE( root.count() == 10 );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );
		

		::booldog::data::json::object node = root[ 0 ];

		json = node.json;

		REQUIRE( strcmp( json , "\"test0\"" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isstring() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( strcmp( valuestring , "test0" ) == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 1 ];

		json = node.json;

		REQUIRE( strcmp( json , "1986" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 1986 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 1986 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 1986 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 1986 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 1986.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 2 ];

		json = node.json;
		
		REQUIRE( strcmp( json , "25.56" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 25 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 25 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 25 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 25 );

		valuefloat = node.value;

		REQUIRE( ::booldog::utils::round( valuefloat , 2 ) == 25.56f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 3 ];

		json = node.json;
		
		REQUIRE( strcmp( json , "true" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isboolean() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE( valuebool );


		node = root[ 4 ];

		json = node.json;
		
		REQUIRE( strcmp( json , "null" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnull() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 5 ];

		json = node.json;
		
		REQUIRE( strcmp( json , "{\"1\":true}" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isobject() );

		REQUIRE( node.count() == 1 );
		
		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = node( "1" );

		json = node.json;

		REQUIRE( strcmp( json , "true" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isboolean() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "1" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE( valuebool );


		node = root[ 6 ];

		json = node.json;

		REQUIRE( strcmp( json , "[1,1,2]" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isarray() );

		REQUIRE( node.count() == 3 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );
		

		node = root[ 6 ][ 0 ];

		json = node.json;

		REQUIRE( strcmp( json , "1" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 1 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 1 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 1 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 1 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 1.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 6 ][ 1 ];

		json = node.json;

		REQUIRE( strcmp( json , "1" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 1 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 1 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 1 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 1 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 1.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 6 ][ 2 ];

		json = node.json;

		REQUIRE( strcmp( json , "2" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 2 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 2 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 2 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 2 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 2.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 7 ];

		json = node.json;
		
		REQUIRE( strcmp( json , "-21E5" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == -2100000 );

		valueint32 = node.value;

		REQUIRE( valueint32 == -2100000 );

		valuefloat = node.value;

		REQUIRE( valuefloat == -2100000.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 8 ];

		json = node.json;

		REQUIRE( strcmp( json , "2e-1" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );
		
		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0.2f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 9 ];

		json = node.json;

		REQUIRE( strcmp( json , "6e+4" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 60000 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 60000 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 60000 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 60000 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 60000.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 10 ];

		json = node.json;

		REQUIRE( json == 0 );

		REQUIRE_FALSE( node.exists() );


		json = root.json;

		REQUIRE( strcmp( json , "[\"test0\",1986,25.56,true,null,{\"1\":true},[1,1,2],-21E5,2e-1,6e+4]" ) == 0 );



		root = copy_serializator;

		json = root.json;

		REQUIRE( strcmp( json , "[\"test0\",1986,25.56,true,null,{\"1\":true},[1,1,2],-21E5,2e-1,6e+4]" ) == 0 );

		REQUIRE( root.isarray() );

		REQUIRE( root.count() == 10 );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );
		

		node = root[ 0 ];

		json = node.json;

		REQUIRE( strcmp( json , "\"test0\"" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isstring() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( strcmp( valuestring , "test0" ) == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 1 ];

		json = node.json;

		REQUIRE( strcmp( json , "1986" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 1986 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 1986 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 1986 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 1986 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 1986.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 2 ];

		json = node.json;
		
		REQUIRE( strcmp( json , "25.56" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 25 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 25 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 25 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 25 );

		valuefloat = node.value;

		REQUIRE( ::booldog::utils::round( valuefloat , 2 ) == 25.56f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 3 ];

		json = node.json;
		
		REQUIRE( strcmp( json , "true" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isboolean() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE( valuebool );


		node = root[ 4 ];

		json = node.json;
		
		REQUIRE( strcmp( json , "null" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnull() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 5 ];

		json = node.json;
		
		REQUIRE( strcmp( json , "{\"1\":true}" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isobject() );

		REQUIRE( node.count() == 1 );
		
		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = node( "1" );

		json = node.json;

		REQUIRE( strcmp( json , "true" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isboolean() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "1" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE( valuebool );


		node = root[ 6 ];

		json = node.json;

		REQUIRE( strcmp( json , "[1,1,2]" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isarray() );

		REQUIRE( node.count() == 3 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );
		

		node = root[ 6 ][ 0 ];

		json = node.json;

		REQUIRE( strcmp( json , "1" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 1 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 1 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 1 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 1 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 1.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 6 ][ 1 ];

		json = node.json;

		REQUIRE( strcmp( json , "1" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 1 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 1 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 1 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 1 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 1.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 6 ][ 2 ];

		json = node.json;

		REQUIRE( strcmp( json , "2" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 2 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 2 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 2 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 2 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 2.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 7 ];

		json = node.json;
		
		REQUIRE( strcmp( json , "-21E5" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == -2100000 );

		valueint32 = node.value;

		REQUIRE( valueint32 == -2100000 );

		valuefloat = node.value;

		REQUIRE( valuefloat == -2100000.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 8 ];

		json = node.json;

		REQUIRE( strcmp( json , "2e-1" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );
		
		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0.2f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 9 ];

		json = node.json;

		REQUIRE( strcmp( json , "6e+4" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 60000 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 60000 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 60000 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 60000 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 60000.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root[ 10 ];

		json = node.json;

		REQUIRE( json == 0 );

		REQUIRE_FALSE( node.exists() );


		json = root.json;

		REQUIRE( strcmp( json , "[\"test0\",1986,25.56,true,null,{\"1\":true},[1,1,2],-21E5,2e-1,6e+4]" ) == 0 );




		::booldog::data::json::parse< 1 >( &res , &allocator , "    \"test0 \\t\\n \\u0074\\u0065\\u0073\\u0074\\u0036\\uD834\\uDD1E \\\" \\b \\n\"    " );

		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( strcmp( json , "\"test0 \\t\\n test6\xf0\x9d\x84\x9e \\\" \\b \\n\"" ) == 0 );

		REQUIRE( root.isstring() );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( strcmp( valuestring , "test0 \t\n test6\xf0\x9d\x84\x9e \" \b \n" ) == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "\"test0 \\t\\n test6\xf0\x9d\x84\x9e \\\" \\b \\n\"" ) == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( strcmp( json , "\"test0 \\t\\n test6\xf0\x9d\x84\x9e \\\" \\b \\n\"" ) == 0 );

		REQUIRE( root.isstring() );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( strcmp( valuestring , "test0 \t\n test6\xf0\x9d\x84\x9e \" \b \n" ) == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );

		json = root.json;

		REQUIRE( strcmp( json , "\"test0 \\t\\n test6\xf0\x9d\x84\x9e \\\" \\b \\n\"" ) == 0 );
		
		
		::booldog::data::json::parse< 1 >( &res , &allocator , "{\"test0\":{},\"test1\":{},\"test2\":{},\"test3\":null,\"test4\":true,\"test5\":false,\"\\u0074\\u0065\\u0073\\u0074\\u0036\\n\\b\\f\":\"example \\u0065 \\b \\n \\f\\n \\\"\",\"\\u0074\\u0065\\u0073\\u0074\\u0036\\uD834\\uDD1E\":25167.678e+4}" );

		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( strcmp( json , "{\"test0\":{},\"test1\":{},\"test2\":{},\"test3\":null,\"test4\":true,\"test5\":false,\"test6\\n\\b\\f\":\"example \x65 \\b \\n \\f\\n \\\"\",\"test6\xf0\x9d\x84\x9e\":25167.678e+4}" ) == 0 );

		REQUIRE( root.isobject() );

		REQUIRE( root.count() == 8 );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test0" );

		json = node.json;

		REQUIRE( strcmp( json , "{}" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isobject() );

		REQUIRE( node.count() == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test0" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test1" );

		json = node.json;

		REQUIRE( strcmp( json , "{}" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isobject() );

		REQUIRE( node.count() == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test1" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test2" );

		json = node.json;

		REQUIRE( strcmp( json , "{}" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isobject() );

		REQUIRE( node.count() == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test2" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test3" );

		json = node.json;

		REQUIRE( strcmp( json , "null" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnull() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test3" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test4" );

		json = node.json;

		REQUIRE( strcmp( json , "true" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isboolean() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test4" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE( valuebool );


		node = root( "test5" );

		json = node.json;

		REQUIRE( strcmp( json , "false" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isboolean() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test5" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test6\n\b\f" );

		json = node.json;

		REQUIRE( strcmp( json , "\"example \x65 \\b \\n \\f\\n \\\"\"" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isstring() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test6\n\b\f" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( strcmp( valuestring , "example \x65 \b \n \f\n \"" ) == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );
		

		node = root( "test6\xf0\x9d\x84\x9e" );

		json = node.json;

		REQUIRE( strcmp( json , "25167.678e+4" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 251676780 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 251676780 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 251676780 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 251676780 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 251676780.f );

		REQUIRE( strcmp( node.name() , "test6\xf0\x9d\x84\x9e" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 251676780 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 251676780 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 251676780 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 251676780 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 251676780.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test6\n \f" );

		json = node.json;

		REQUIRE( json == 0 );

		REQUIRE_FALSE( node.exists() );

		node = root( "test6777" );

		json = node.json;

		REQUIRE( json == 0 );

		REQUIRE_FALSE( node.exists() );

		node = root( "test" );

		json = node.json;

		REQUIRE( json == 0 );

		REQUIRE_FALSE( node.exists() );


		json = root.json;

		REQUIRE( strcmp( json , "{\"test0\":{},\"test1\":{},\"test2\":{},\"test3\":null,\"test4\":true,\"test5\":false,\"test6\\n\\b\\f\":\"example \x65 \\b \\n \\f\\n \\\"\",\"test6\xf0\x9d\x84\x9e\":25167.678e+4}" ) == 0 );


		root = copy_serializator;

		json = root.json;

		REQUIRE( strcmp( json , "{\"test0\":{},\"test1\":{},\"test2\":{},\"test3\":null,\"test4\":true,\"test5\":false,\"test6\\n\\b\\f\":\"example \x65 \\b \\n \\f\\n \\\"\",\"test6\xf0\x9d\x84\x9e\":25167.678e+4}" ) == 0 );

		REQUIRE( root.isobject() );

		REQUIRE( root.count() == 8 );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test0" );

		json = node.json;

		REQUIRE( strcmp( json , "{}" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isobject() );

		REQUIRE( node.count() == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test0" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test1" );

		json = node.json;

		REQUIRE( strcmp( json , "{}" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isobject() );

		REQUIRE( node.count() == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test1" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test2" );

		json = node.json;

		REQUIRE( strcmp( json , "{}" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isobject() );

		REQUIRE( node.count() == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test2" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test3" );

		json = node.json;

		REQUIRE( strcmp( json , "null" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnull() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test3" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test4" );

		json = node.json;

		REQUIRE( strcmp( json , "true" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isboolean() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test4" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE( valuebool );


		node = root( "test5" );

		json = node.json;

		REQUIRE( strcmp( json , "false" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isboolean() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test5" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test6\n\b\f" );

		json = node.json;

		REQUIRE( strcmp( json , "\"example \x65 \\b \\n \\f\\n \\\"\"" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isstring() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test6\n\b\f" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( strcmp( valuestring , "example \x65 \b \n \f\n \"" ) == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );
		

		node = root( "test6\xf0\x9d\x84\x9e" );

		json = node.json;

		REQUIRE( strcmp( json , "25167.678e+4" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isnumber() );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 251676780 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 251676780 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 251676780 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 251676780 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 251676780.f );

		REQUIRE( strcmp( node.name() , "test6\xf0\x9d\x84\x9e" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 251676780 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 251676780 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 251676780 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 251676780 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 251676780.f );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test6\n \f" );

		json = node.json;

		REQUIRE( json == 0 );

		REQUIRE_FALSE( node.exists() );

		node = root( "test6777" );

		json = node.json;

		REQUIRE( json == 0 );

		REQUIRE_FALSE( node.exists() );

		node = root( "test" );

		json = node.json;

		REQUIRE( json == 0 );

		REQUIRE_FALSE( node.exists() );


		json = root.json;

		REQUIRE( strcmp( json , "{\"test0\":{},\"test1\":{},\"test2\":{},\"test3\":null,\"test4\":true,\"test5\":false,\"test6\\n\\b\\f\":\"example \x65 \\b \\n \\f\\n \\\"\",\"test6\xf0\x9d\x84\x9e\":25167.678e+4}" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   \n{       \"test0\" : { \t\n\r }      \r}   \n\t" );

		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = (*res.serializator);

		json = root.json;

		REQUIRE( strcmp( json , "{\"test0\":{}}" ) == 0 );

		REQUIRE( root.isobject() );

		REQUIRE( root.count() == 1 );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test0" );

		json = node.json;

		REQUIRE( strcmp( json , "{}" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isobject() );

		REQUIRE( node.count() == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test0" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );



		root = copy_serializator;

		json = root.json;

		REQUIRE( strcmp( json , "{\"test0\":{}}" ) == 0 );

		REQUIRE( root.isobject() );

		REQUIRE( root.count() == 1 );

		valueuint64 = root.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = root.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = root.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = root.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = root.value;

		REQUIRE( valuefloat == 0 );

		valuestring = root.value;

		REQUIRE( valuestring == 0 );

		valuebool = root.value;

		REQUIRE_FALSE( valuebool );


		node = root( "test0" );

		json = node.json;

		REQUIRE( strcmp( json , "{}" ) == 0 );

		REQUIRE( node.exists() );

		REQUIRE( node.isobject() );

		REQUIRE( node.count() == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		REQUIRE( strcmp( node.name() , "test0" ) == 0 );

		valueuint64 = node.value;

		REQUIRE( valueuint64 == 0 );

		valueuint32 = node.value;

		REQUIRE( valueuint32 == 0 );

		valueint64 = node.value;

		REQUIRE( valueint64 == 0 );

		valueint32 = node.value;

		REQUIRE( valueint32 == 0 );

		valuefloat = node.value;

		REQUIRE( valuefloat == 0 );

		valuestring = node.value;

		REQUIRE( valuestring == 0 );

		valuebool = node.value;

		REQUIRE_FALSE( valuebool );
	}

	{
		::booldog::result resres;

		::booldog::data::json::serializator serializator( &allocator );

		serializator.fast.begin_object< 1 >( &resres , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 1 );

		REQUIRE( strcmp( serializator.fast.json , "{" ) == 0 );


		serializator.fast.end_object< 1 >( &resres , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 2 );

		REQUIRE( strcmp( serializator.fast.json , "{}" ) == 0 );

		serializator.clear();


		serializator.fast.add< 1 >( &resres , 0LL , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 1 );

		REQUIRE( strcmp( serializator.fast.json , "0" ) == 0 );


		serializator.clear();

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 0 );

		REQUIRE( strcmp( serializator.fast.json , "" ) == 0 );


		serializator.fast.begin_array< 1 >( &resres , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 1 );

		REQUIRE( strcmp( serializator.fast.json , "[" ) == 0 );


		serializator.fast.end_array< 1 >( &resres , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 2 );

		REQUIRE( strcmp( serializator.fast.json , "[]" ) == 0 );


		serializator.clear();

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 0 );

		REQUIRE( strcmp( serializator.fast.json , "" ) == 0 );



		serializator.fast.begin_object< 1 >( &resres , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 1 );

		REQUIRE( strcmp( serializator.fast.json , "{" ) == 0 );
		

		serializator.fast.begin_object< 1 >( &resres , "test\n \b \\" , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 17 );

		REQUIRE( strcmp( serializator.fast.json , "{\"test\\n \\b \\\\\":{" ) == 0 );


		serializator.fast.add< 1 >( &resres , "test\n \b \\\\" , "\f" , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 38 );

		REQUIRE( strcmp( serializator.fast.json , "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"" ) == 0 );


		serializator.fast.end_object< 1 >( &resres , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 39 );

		REQUIRE( strcmp( serializator.fast.json , "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"}" ) == 0 );
		

		serializator.fast.begin_array< 1 >( &resres , "test\n \\b \\" , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 57 );

		REQUIRE( strcmp( serializator.fast.json 
			, "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[" ) == 0 );


		serializator.fast.add< 1 >( &resres , true , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 61 );

		REQUIRE( strcmp( serializator.fast.json 
			, "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[true" ) == 0 );


		serializator.fast.add< 1 >( &resres , false , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 67 );

		REQUIRE( strcmp( serializator.fast.json 
			, "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[true,false" ) == 0 );


		serializator.fast.add< 1 >( &resres , -23 , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 71 );

		REQUIRE( strcmp( serializator.fast.json 
			, "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[true,false,-23" ) == 0 );


		serializator.fast.add< 1 >( &resres , "primer" , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 80 );

		REQUIRE( strcmp( serializator.fast.json 
			, "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[true,false,-23,\"primer\"" ) == 0 );


		serializator.fast.end_array< 1 >( &resres , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 81 );

		REQUIRE( strcmp( serializator.fast.json 
			, "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[true,false,-23,\"primer\"]" ) == 0 );


		serializator.fast.add< 1 >( &resres , "" , true , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 89 );

		REQUIRE( strcmp( serializator.fast.json 
			, "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[true,false,-23,\"primer\"],\"\":true" ) 
			== 0 );


		serializator.fast.add< 1 >( &resres , "test \" \n \f" , false , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 111 );

		REQUIRE( strcmp( serializator.fast.json , "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[true,false,-23,\"primer\"],\"\":true"
			",\"test \\\" \\n \\f\":false" ) 
			== 0 );


		serializator.fast.add< 1 >( &resres , "1" , -128 , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 120 );

		REQUIRE( strcmp( serializator.fast.json , "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[true,false,-23,\"primer\"],\"\":true"
			",\"test \\\" \\n \\f\":false,\"1\":-128" ) 
			== 0 );


		serializator.fast.add< 1 >( &resres , "2" , -128128128128128LL , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 141 );

		REQUIRE( strcmp( serializator.fast.json , "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[true,false,-23,\"primer\"],\"\":true"
			",\"test \\\" \\n \\f\":false,\"1\":-128,\"2\":-128128128128128" ) 
			== 0 );


		serializator.fast.add< 1 >( &resres , "3" , 256256256256256ULL , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 161 );

		REQUIRE( strcmp( serializator.fast.json , "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[true,false,-23,\"primer\"],\"\":true"
			",\"test \\\" \\n \\f\":false,\"1\":-128,\"2\":-128128128128128,\"3\":256256256256256" ) 
			== 0 );


		serializator.fast.add< 1 >( &resres , "4" , 0 , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 167 );

		REQUIRE( strcmp( serializator.fast.json 
			, "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[true,false,-23,\"primer\"],\"\":true"
			",\"test \\\" \\n \\f\":false,\"1\":-128,\"2\":-128128128128128,\"3\":256256256256256,\"4\":0" ) 
			== 0 );


		serializator.fast.end_object< 1 >( &resres , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 168 );

		REQUIRE( strcmp( serializator.fast.json 
			, "{\"test\\n \\b \\\\\":{\"test\\n \\b \\\\\\\\\":\"\\f\"},\"test\\n \\\\b \\\\\":[true,false,-23,\"primer\"],\"\":true"
			",\"test \\\" \\n \\f\":false,\"1\":-128,\"2\":-128128128128128,\"3\":256256256256256,\"4\":0}" )
			== 0 );

		serializator.clear();

		serializator.fast.object< 1 >( &resres , "test0\n" , "value01'f  \f \"" , "test1\f" , true , "test2\b" , 1986 , "test3\r" , -999 
			,"test4\"" , false , true , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 91 );

		REQUIRE( strcmp( serializator.fast.json 
			, "{\"test0\\n\":\"value01'f  \\f \\\"\",\"test1\\f\":true,\"test2\\b\":1986,\"test3\\r\":-999,\"test4\\\"\":false}" )
			== 0 );


		serializator.clear();

		REQUIRE( serializator.fast.nodesindex == 0 );

		REQUIRE( serializator.fast.jsonlen == 0 );

		REQUIRE( strcmp( serializator.fast.json , "" ) == 0 );
	}

	{
		::booldog::result resres;

		::booldog::data::json::serializator serializator( &allocator );

		::booldog::data::json::result res( &serializator );

		::booldog::data::json::parse< 1 >( &res , &allocator , "{\"test0 \\\" \":1,\"1\":{\"2\":1986}}" );

		REQUIRE( res.succeeded() );
		
		::booldog::data::json::object root = (*res.serializator);

		::booldog::data::json::object field = root( "test0 \" " );

		::booldog::data::json::object field1 = root( "1" );

		::booldog::data::json::object field2 = field1( "2" );

		const char* json = root.json;

		REQUIRE( strcmp( json , "{\"test0 \\\" \":1,\"1\":{\"2\":1986}}" ) == 0 );

		REQUIRE( root.isobject() );

		REQUIRE( field.isnumber() );

		REQUIRE( field1.isobject() );

		REQUIRE( field2.isnumber() );

		REQUIRE( (int)field2.value == 1986 );


		field.name( &resres , "test1 \" " , debuginfo_macros );

		field = root( "test1 \" " );

		field1 = root( "1" );

		field2 = field1( "2" );

		json = root.json;

		REQUIRE( strcmp( json , "{\"test1 \\\" \":1,\"1\":{\"2\":1986}}" ) == 0 );

		REQUIRE( root.isobject() );

		REQUIRE( field.isnumber() );

		REQUIRE( field1.isobject() );

		REQUIRE( field2.isnumber() );

		REQUIRE( (int)field2.value == 1986 );


		REQUIRE( strcmp( field.name() , "test1 \" " ) == 0 );

		field.name( &resres , "test0 \" " , debuginfo_macros );

		field = root( "test0 \" " );

		field1 = root( "1" );

		field2 = field1( "2" );

		json = root.json;

		REQUIRE( strcmp( json , "{\"test0 \\\" \":1,\"1\":{\"2\":1986}}" ) == 0 );

		REQUIRE( root.isobject() );

		REQUIRE( field.isnumber() );

		REQUIRE( field1.isobject() );

		REQUIRE( field2.isnumber() );

		REQUIRE( (int)field2.value == 1986 );


		
		field.name( &resres , "test10000 \" " , debuginfo_macros );

		field = root( "test10000 \" " );

		field1 = root( "1" );

		field2 = field1( "2" );

		json = root.json;

		REQUIRE( strcmp( json , "{\"test10000 \\\" \":1,\"1\":{\"2\":1986}}" ) == 0 );

		REQUIRE( root.isobject() );

		REQUIRE( field.isnumber() );

		REQUIRE( field1.isobject() );

		REQUIRE( field2.isnumber() );

		REQUIRE( (int)field2.value == 1986 );
	}

	{
		::booldog::result resres;

		::booldog::data::json::serializator copy_serializator( &allocator );

		::booldog::data::json::serializator serializator( &allocator );

		::booldog::data::json::result res( &serializator );

		::booldog::data::json::parse< 1 >( &res , &allocator , "{}" );
		
		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		::booldog::data::json::object root = copy_serializator;

		::booldog::data::json::object field = root.add< 1 >( &resres , "1" , true , debuginfo_macros );

		REQUIRE( field.isboolean() );

		REQUIRE( strcmp( field.json , "true" ) == 0 );

		REQUIRE( (bool)field.value );

		REQUIRE( strcmp( root.json , "{\"1\":true}" ) == 0 );

		REQUIRE( copy_serializator.slow.jsonlen == 10 );

		field = root( "1" );

		REQUIRE( field.isboolean() );

		REQUIRE( strcmp( field.json , "true" ) == 0 );

		REQUIRE( (bool)field.value );


		field = root.add< 1 >( &resres , "2" , false , debuginfo_macros );

		REQUIRE( field.isboolean() );

		REQUIRE( strcmp( field.json , "false" ) == 0 );

		REQUIRE_FALSE( (bool)field.value );

		REQUIRE( strcmp( root.json , "{\"1\":true,\"2\":false}" ) == 0 );

		REQUIRE( copy_serializator.slow.jsonlen == 20 );

		field = root( "1" );

		REQUIRE( field.isboolean() );

		REQUIRE( strcmp( field.json , "true" ) == 0 );

		REQUIRE( (bool)field.value );

		field = root( "2" );

		REQUIRE( field.isboolean() );

		REQUIRE( strcmp( field.json , "false" ) == 0 );

		REQUIRE_FALSE( (bool)field.value );


		::booldog::data::json::parse< 1 >( &res , &allocator , "{\"internal\":{\"internal\":{}}}" );
		
		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = copy_serializator;

		::booldog::data::json::object internalroot = root( "internal" )( "internal" );

		field = internalroot.add< 1 >( &resres , "1" , true , debuginfo_macros );

		REQUIRE( field.isboolean() );

		REQUIRE( strcmp( field.json , "true" ) == 0 );

		REQUIRE( (bool)field.value );

		REQUIRE( strcmp( root.json , "{\"internal\":{\"internal\":{\"1\":true}}}" ) == 0 );

		REQUIRE( copy_serializator.slow.jsonlen == 36 );

		field = internalroot( "1" );

		REQUIRE( field.isboolean() );

		REQUIRE( strcmp( field.json , "true" ) == 0 );

		REQUIRE( (bool)field.value );


		field = internalroot.add< 1 >( &resres , "2" , false , debuginfo_macros );

		REQUIRE( field.isboolean() );

		REQUIRE( strcmp( field.json , "false" ) == 0 );

		REQUIRE_FALSE( (bool)field.value );

		REQUIRE( strcmp( root.json , "{\"internal\":{\"internal\":{\"1\":true,\"2\":false}}}" ) == 0 );

		REQUIRE( copy_serializator.slow.jsonlen == 46 );

		field = internalroot( "1" );

		REQUIRE( field.isboolean() );

		REQUIRE( strcmp( field.json , "true" ) == 0 );

		REQUIRE( (bool)field.value );

		field = internalroot( "2" );

		REQUIRE( field.isboolean() );

		REQUIRE( strcmp( field.json , "false" ) == 0 );

		REQUIRE_FALSE( (bool)field.value );
	}

	{
		::booldog::data::json::serializator copy_serializator( &allocator );

		::booldog::data::json::serializator serializator( &allocator );

		::booldog::data::json::result res( &serializator );

		::booldog::data::json::parse< 1 >( &res , &allocator , "{}" );

		/*::booldog::data::json::parse< 64 >( &res , &allocator , "{\r\n"
			"	\"databases\":\r\n"
			"	[\r\n"
			"		{\"key\":\"conf\",\"connection\":{\"hostname\":\"localhost\",\"filename\":\"configuration.db\",\"upgrade\":\"server_upgrade.sql\"}},\r\n"
			"		{\"key\":\"events\",\"connection\":{\"hostname\":\"localhost\",\"filename\":\"events.db\",\"upgrade\":\"events_upgrade.sql\"}},\r\n"
			"		{\"key\":\"ptzusers\",\"connection\":{\"hostname\":\"localhost\",\"filename\":\"ptzusers.db\",\"upgrade\":\"ptzusers_upgrade.sql\"}}\r\n"
			"	]\r\n"
			"}\r\n"
			"\r\n" );*/

		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		::booldog::data::json::object root = copy_serializator;

		root.value = (int)-1986;

		REQUIRE( root.isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 5 );

		REQUIRE( strcmp( (const char*)root.json , "-1986" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root.value = 0LL;

		REQUIRE( root.isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 1 );

		REQUIRE( strcmp( (const char*)root.json , "0" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root.value = -1;

		REQUIRE( root.isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 2 );

		REQUIRE( strcmp( (const char*)root.json , "-1" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root.value = 1;

		REQUIRE( root.isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 1 );

		REQUIRE( strcmp( (const char*)root.json , "1" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root.value = (::booldog::uint32)1986;

		REQUIRE( root.isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 4 );

		REQUIRE( strcmp( (const char*)root.json , "1986" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root.value = (::booldog::uint64)1986198619861986;

		REQUIRE( root.isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 16 );

		REQUIRE( strcmp( (const char*)root.json , "1986198619861986" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root.value = (::booldog::int64)-1986198619861986;

		REQUIRE( root.isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 17 );

		REQUIRE( strcmp( (const char*)root.json , "-1986198619861986" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root.value = true;

		REQUIRE( root.isboolean() );

		REQUIRE( copy_serializator.slow.jsonlen == 4 );

		REQUIRE( strcmp( (const char*)root.json , "true" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root.value = false;

		REQUIRE( root.isboolean() );

		REQUIRE( copy_serializator.slow.jsonlen == 5 );

		REQUIRE( strcmp( (const char*)root.json , "false" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root.value = "test1986 \"";

		REQUIRE( root.isstring() );

		REQUIRE( copy_serializator.slow.jsonlen == 12 );

		REQUIRE( strcmp( (const char*)root.json , "\"test1986 \\\"\"" ) == 0 );

		REQUIRE( strcmp( (const char*)root.value , "test1986 \"" ) == 0 );



		::booldog::data::json::parse< 1 >( &res , &allocator , "{\"test0\":{\"test0\":121212121212}}" );
		
		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = (int)-1986;
		
		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":-1986}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 25 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":-1986}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = -1;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":-1}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 22 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":-1}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = 1;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":1}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 21 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":1}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = (::booldog::uint32)1986;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":1986}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 24 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":1986}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = (::booldog::uint64)1986198619861986;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":1986198619861986}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 36 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":1986198619861986}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = (::booldog::int64)-1986198619861986;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":-1986198619861986}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 37 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":-1986198619861986}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = true;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":true}" ) == 0 );

		REQUIRE( root("test0")("test0").isboolean() );

		REQUIRE( copy_serializator.slow.jsonlen == 24 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":true}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = false;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":false}" ) == 0 );

		REQUIRE( root("test0")("test0").isboolean() );

		REQUIRE( copy_serializator.slow.jsonlen == 25 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":false}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = "test1986 \"";

		REQUIRE( copy_serializator.slow.jsonlen == 32 );

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":\"test1986 \\\"\"}" ) == 0 );

		REQUIRE( root("test0")("test0").isstring() );

		REQUIRE( copy_serializator.slow.jsonlen == 33 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":\"test1986 \\\"\"}}" ) == 0 );



		::booldog::data::json::parse< 1 >( &res , &allocator , "{\"test0\":{\"test0\":12}}" );
		
		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = (int)-1986;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":-1986}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 25 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":-1986}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = -1;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":-1}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 22 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":-1}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = 1;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":1}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 21 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":1}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = (::booldog::uint32)1986;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":1986}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 24 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":1986}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = (::booldog::uint64)1986198619861986;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":1986198619861986}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 36 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":1986198619861986}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = (::booldog::int64)-1986198619861986;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":-1986198619861986}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 37 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":-1986198619861986}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = true;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":true}" ) == 0 );

		REQUIRE( root("test0")("test0").isboolean() );

		REQUIRE( copy_serializator.slow.jsonlen == 24 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":true}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = false;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":false}" ) == 0 );

		REQUIRE( root("test0")("test0").isboolean() );

		REQUIRE( copy_serializator.slow.jsonlen == 25 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":false}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = "test1986 \"";

		REQUIRE( copy_serializator.slow.jsonlen == 32 );

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":\"test1986 \\\"\"}" ) == 0 );

		REQUIRE( root("test0")("test0").isstring() );

		REQUIRE( copy_serializator.slow.jsonlen == 33 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":\"test1986 \\\"\"}}" ) == 0 );



		::booldog::data::json::parse< 1 >( &res , &allocator , "{\"test0\":{\"test0\":121212121212121212}}" );
		
		REQUIRE( res.succeeded() );

		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = (int)-1986;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":-1986}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 25 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":-1986}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = -1;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":-1}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 22 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":-1}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = 1;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":1}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 21 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":1}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = (::booldog::uint32)1986;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":1986}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 24 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":1986}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = (::booldog::uint64)1986198619861986;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":1986198619861986}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 36 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":1986198619861986}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = (::booldog::int64)-1986198619861986;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":-1986198619861986}" ) == 0 );

		REQUIRE( root("test0")("test0").isnumber() );

		REQUIRE( copy_serializator.slow.jsonlen == 37 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":-1986198619861986}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = true;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":true}" ) == 0 );

		REQUIRE( root("test0")("test0").isboolean() );

		REQUIRE( copy_serializator.slow.jsonlen == 24 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":true}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = false;

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":false}" ) == 0 );

		REQUIRE( root("test0")("test0").isboolean() );

		REQUIRE( copy_serializator.slow.jsonlen == 25 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":false}}" ) == 0 );


		copy_serializator = serializator;

		root = copy_serializator;

		root("test0")("test0").value = "test1986 \"";

		REQUIRE( copy_serializator.slow.jsonlen == 32 );

		REQUIRE( root.isobject() );

		REQUIRE( root( "test0" ).isobject() );

		REQUIRE( strcmp( root( "test0" ).json , "{\"test0\":\"test1986 \\\"\"}" ) == 0 );

		REQUIRE( root("test0")("test0").isstring() );

		REQUIRE( copy_serializator.slow.jsonlen == 33 );

		REQUIRE( strcmp( (const char*)root.json , "{\"test0\":{\"test0\":\"test1986 \\\"\"}}" ) == 0 );
	}

	REQUIRE( allocator.begin() == begin );     
		
	REQUIRE( allocator.available() == total );
};

struct boo_doubly_linked_listTest_struct
{
	const char* value;
	boo_doubly_linked_listTest_struct* _doubly_linked_list_prev;
	boo_doubly_linked_listTest_struct* _doubly_linked_list_next;
	boo_doubly_linked_listTest_struct( const char* pvalue )
	{
		value = pvalue;
	};
};
//class boo_doubly_linked_listTest : public ::testing::Test 
//{
//};
TEST_CASE("boo_doubly_linked_listTest", "test")
{
	boo_doubly_linked_listTest_struct item0( "item0" );
	boo_doubly_linked_listTest_struct item1( "item1" );
	boo_doubly_linked_listTest_struct item2( "item2" );
	boo_doubly_linked_listTest_struct item3( "item3" );

	::booldog::data::doubly_linked_list< boo_doubly_linked_listTest_struct > doubly_linked_list;

	REQUIRE( doubly_linked_list.add( item0 ) == 0 );

	REQUIRE( doubly_linked_list.count() == 1 );

	REQUIRE( doubly_linked_list[ 0 ] == &item0 );

	REQUIRE( doubly_linked_list[ 1 ] == 0 );

	REQUIRE( doubly_linked_list[ 2 ] == 0 );

	REQUIRE( doubly_linked_list[ 3 ] == 0 );

	REQUIRE( doubly_linked_list[ 4 ] == 0 );


	REQUIRE( doubly_linked_list.add( item1 ) == 1 );

	REQUIRE( doubly_linked_list.count() == 2 );

	REQUIRE( doubly_linked_list[ 0 ] == &item0 );

	REQUIRE( doubly_linked_list[ 1 ] == &item1 );

	REQUIRE( doubly_linked_list[ 2 ] == 0 );

	REQUIRE( doubly_linked_list[ 3 ] == 0 );

	REQUIRE( doubly_linked_list[ 4 ] == 0 );


	REQUIRE( doubly_linked_list.add( item2 ) == 2 );

	REQUIRE( doubly_linked_list.count() == 3 );

	REQUIRE( doubly_linked_list[ 0 ] == &item0 );

	REQUIRE( doubly_linked_list[ 1 ] == &item1 );

	REQUIRE( doubly_linked_list[ 2 ] == &item2 );

	REQUIRE( doubly_linked_list[ 3 ] == 0 );

	REQUIRE( doubly_linked_list[ 4 ] == 0 );


	REQUIRE( doubly_linked_list.add( item3 ) == 3 );

	REQUIRE( doubly_linked_list.count() == 4 );

	REQUIRE( doubly_linked_list[ 0 ] == &item0 );

	REQUIRE( doubly_linked_list[ 1 ] == &item1 );

	REQUIRE( doubly_linked_list[ 2 ] == &item2 );

	REQUIRE( doubly_linked_list[ 3 ] == &item3 );

	REQUIRE( doubly_linked_list[ 4 ] == 0 );


	doubly_linked_list.remove( item3 );

	REQUIRE( doubly_linked_list.count() == 3 );

	REQUIRE( doubly_linked_list[ 0 ] == &item0 );

	REQUIRE( doubly_linked_list[ 1 ] == &item1 );

	REQUIRE( doubly_linked_list[ 2 ] == &item2 );

	REQUIRE( doubly_linked_list[ 3 ] == 0 );

	REQUIRE( doubly_linked_list[ 4 ] == 0 );


	doubly_linked_list.remove( item1 );

	REQUIRE( doubly_linked_list.count() == 2 );

	REQUIRE( doubly_linked_list[ 0 ] == &item0 );

	REQUIRE( doubly_linked_list[ 1 ] == &item2 );

	REQUIRE( doubly_linked_list[ 2 ] == 0 );

	REQUIRE( doubly_linked_list[ 3 ] == 0 );

	REQUIRE( doubly_linked_list[ 4 ] == 0 );


	doubly_linked_list.remove( item0 );

	REQUIRE( doubly_linked_list.count() == 1 );

	REQUIRE( doubly_linked_list[ 0 ] == &item2 );

	REQUIRE( doubly_linked_list[ 1 ] == 0 );

	REQUIRE( doubly_linked_list[ 2 ] == 0 );

	REQUIRE( doubly_linked_list[ 3 ] == 0 );

	REQUIRE( doubly_linked_list[ 4 ] == 0 );


	doubly_linked_list.clear();

	REQUIRE( doubly_linked_list.count() == 0 );

	REQUIRE( doubly_linked_list[ 0 ] == 0 );

	REQUIRE( doubly_linked_list[ 1 ] == 0 );

	REQUIRE( doubly_linked_list[ 2 ] == 0 );

	REQUIRE( doubly_linked_list[ 3 ] == 0 );

	REQUIRE( doubly_linked_list[ 4 ] == 0 );
};
//class boo_stringTest : public ::testing::Test 
//{
//};
TEST_CASE("boo_stringTest", "test")
{
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

#ifdef BOOLDOG_STRING_TEST
	for( ::booldog::string_step = 1 ; ::booldog::string_step < 25 ; ::booldog::string_step++ )
	{

#endif
		{
			::booldog::string string( &allocator , (const char*)0 );

			REQUIRE( strcmp( string.str() , "" ) == 0 );

			REQUIRE( string.length() == 0 );

			REQUIRE( string.bytes() == 1 );
		}

		{
			::booldog::string string( &allocator , "" );

			REQUIRE( strcmp( string.str() , "" ) == 0 );

			REQUIRE( string.length() == 0 );

			REQUIRE( string.bytes() == 1 );
		}

		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE( string.bytes() == 5 );
		}

		{
			::booldog::string string( &allocator , "TEST" , 0 , 4 );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE( string.bytes() == 5 );
		}

		{
			::booldog::string string( &allocator , "Hello, TEST" , 7 );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE( string.bytes() == 5 );
		}

		{
			::booldog::string string( &allocator , "Hello, TEST, it's our first meeting" , 7 , 4 );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE( string.bytes() == 5 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE( string.bytes() == 13 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 3 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_il_var ) == 0 );

			REQUIRE( string.length() == 3 );

			REQUIRE( string.bytes() == 7 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , 6 , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE( string.bytes() == 13 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , 3 , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_Apr_var ) == 0 );

			REQUIRE( string.length() == 3 );

			REQUIRE( string.bytes() == 7 );
		}


		{
			::booldog::string string( &allocator , utf16_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF16 );
		
			REQUIRE( string.length() == 6 );

			REQUIRE( string.bytes() == 13 );

			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );		
		}

		{
			::booldog::string string( &allocator , utf16_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF16 );
		
			REQUIRE( string.length() == 3 );

			REQUIRE( string.bytes() == 7 );

			REQUIRE( strcmp( string.str() , utf8_il_var ) == 0 );		
		}

		{
			::booldog::string string( &allocator , utf16_April_var , 0 , 12 , ::booldog::enums::string::UTF16 );
		
			REQUIRE( string.length() == 6 );

			REQUIRE( string.bytes() == 13 );

			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );		
		}

		{
			::booldog::string string( &allocator , utf16_April_var , 0 , 6 , ::booldog::enums::string::UTF16 );
		
			REQUIRE( string.length() == 3 );

			REQUIRE( string.bytes() == 7 );

			REQUIRE( strcmp( string.str() , utf8_Apr_var ) == 0 );
		}


		{
			::booldog::string string( &allocator , utf32_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF32 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE( string.bytes() == 13 );
		}

		{
			::booldog::string string( &allocator , utf32_April_var , 12 , SIZE_MAX , ::booldog::enums::string::UTF32 );
		
			REQUIRE( strcmp( string.str() , utf8_il_var ) == 0 );

			REQUIRE( string.length() == 3 );

			REQUIRE( string.bytes() == 7 );
		}

		{
			::booldog::string string( &allocator , utf32_April_var , 0 , 24 , ::booldog::enums::string::UTF32 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE( string.bytes() == 13 );
		}

		{
			::booldog::string string( &allocator , utf32_April_var , 0 , 12 , ::booldog::enums::string::UTF32 );
		
			REQUIRE( strcmp( string.str() , utf8_Apr_var ) == 0 );

			REQUIRE( string.length() == 3 );

			REQUIRE( string.bytes() == 7 );
		}

		const wchar_t* wchar_test = 0;
		if( ::booldog::compile::If< sizeof( wchar_t ) == 2 >::test() )
			wchar_test = (wchar_t*)utf16_April_var;
		else if( ::booldog::compile::If< sizeof( wchar_t ) == 4 >::test() )
			wchar_test = (wchar_t*)utf32_April_var;
		{
			::booldog::string string( &allocator , wchar_test , 0 , SIZE_MAX );
		
			REQUIRE( string.length() == 6 );

			REQUIRE( string.bytes() == 13 );

			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );		
		}

		{
			::booldog::string string( &allocator , wchar_test , 3 , SIZE_MAX );
		
			REQUIRE( string.length() == 3 );

			REQUIRE( string.bytes() == 7 );

			REQUIRE( strcmp( string.str() , utf8_il_var ) == 0 );		
		}

		{
			::booldog::string string( &allocator , wchar_test , 0 , 6 );
		
			REQUIRE( string.length() == 6 );

			REQUIRE( string.bytes() == 13 );

			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );		
		}

		{
			::booldog::string string( &allocator , wchar_test , 0 , 3 );
		
			REQUIRE( string.length() == 3 );

			REQUIRE(string.bytes() == 7);

			REQUIRE( strcmp( string.str() , utf8_Apr_var ) == 0 );
		}



		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE(string.bytes() == 5);

			string.append( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );

			REQUIRE( strcmp( string.str() , utf8_TESTApril_var ) == 0 );

			REQUIRE(string.length() == 10);

			REQUIRE(string.bytes() == 17);
		}

		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE(string.length() == 4);

			REQUIRE(string.bytes() == 5);

			string.append( utf8_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );

			REQUIRE( strcmp( string.str() , utf8_TESTApril_var ) == 0 );

			REQUIRE(string.length() == 10);

			REQUIRE(string.bytes() == 17);
		}

		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE(string.bytes() == 5);

			string.append( utf16_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF16 );

			REQUIRE( strcmp( string.str() , utf8_TESTApril_var ) == 0 );

			REQUIRE(string.length() == 10);

			REQUIRE(string.bytes() == 17);
		}

		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE(string.bytes() == 5);

			string.append( utf32_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF32 );

			REQUIRE( strcmp( string.str() , utf8_TESTApril_var ) == 0 );

			REQUIRE(string.length() == 10);

			REQUIRE(string.bytes() == 17);
		}


		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE(string.bytes() == 5);

			string.append( cp1251_April_var , 3 , SIZE_MAX , ::booldog::enums::string::CP1251 );

			REQUIRE( strcmp( string.str() , utf8_TESTil_var ) == 0 );

			REQUIRE(string.length() == 7);

			REQUIRE(string.bytes() == 11);
		}

		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE(string.bytes() == 5);

			string.append( utf8_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF8 );

			REQUIRE( strcmp( string.str() , utf8_TESTil_var ) == 0 );

			REQUIRE(string.length() == 7);

			REQUIRE(string.bytes() == 11);
		}

		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE(string.bytes() == 5);

			string.append( utf16_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF16 );

			REQUIRE( strcmp( string.str() , utf8_TESTil_var ) == 0 );

			REQUIRE(string.length() == 7);

			REQUIRE(string.bytes() == 11);
		}

		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE(string.bytes() == 5);

			string.append( utf32_April_var , 12 , SIZE_MAX , ::booldog::enums::string::UTF32 );

			REQUIRE( strcmp( string.str() , utf8_TESTil_var ) == 0 );

			REQUIRE(string.length() == 7);

			REQUIRE(string.bytes() == 11);
		}


		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE(string.bytes() == 5);

			string.append( cp1251_April_var , 0 , 3 , ::booldog::enums::string::CP1251 );

			REQUIRE( strcmp( string.str() , utf8_TESTApr_var ) == 0 );

			REQUIRE(string.length() == 7);

			REQUIRE(string.bytes() == 11);
		}

		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE(string.bytes() == 5);

			string.append( utf8_April_var , 0 , 6 , ::booldog::enums::string::UTF8 );

			REQUIRE( strcmp( string.str() , utf8_TESTApr_var ) == 0 );

			REQUIRE(string.length() == 7);

			REQUIRE(string.bytes() == 11);
		}

		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE(string.bytes() == 5);

			string.append( utf16_April_var , 0 , 6 , ::booldog::enums::string::UTF16 );

			REQUIRE( strcmp( string.str() , utf8_TESTApr_var ) == 0 );

			REQUIRE(string.length() == 7);

			REQUIRE(string.bytes() == 11);
		}

		{
			::booldog::string string( &allocator , "TEST" );

			REQUIRE( strcmp( string.str() , "TEST" ) == 0 );

			REQUIRE( string.length() == 4 );

			REQUIRE(string.bytes() == 5);

			string.append( utf32_April_var , 0 , 12 , ::booldog::enums::string::UTF32 );

			REQUIRE( strcmp( string.str() , utf8_TESTApr_var ) == 0 );

			REQUIRE(string.length() == 7);

			REQUIRE(string.bytes() == 11);
		}



		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , cp1251_il_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , utf16_il_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF16 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , utf32_il_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF32 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , utf8_il_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}


		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , cp1251_April_var , 3 , SIZE_MAX , ::booldog::enums::string::CP1251 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , utf16_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF16 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , utf32_April_var , 12 , SIZE_MAX , ::booldog::enums::string::UTF32 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , utf8_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF8 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}


		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , cp1251_April_var , 3 , 3 , ::booldog::enums::string::CP1251 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , utf16_April_var , 6 , 6 , ::booldog::enums::string::UTF16 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , utf32_April_var , 12 , 12 , ::booldog::enums::string::UTF32 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , utf8_April_var , 6 , 6 , ::booldog::enums::string::UTF8 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}



		if( ::booldog::compile::If< sizeof( wchar_t ) == 2 >::test() )
			wchar_test = (wchar_t*)utf16_il_var;
		else if( ::booldog::compile::If< sizeof( wchar_t ) == 4 >::test() )
			wchar_test = (wchar_t*)utf32_il_var;
		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , wchar_test , 0 , SIZE_MAX );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		if( ::booldog::compile::If< sizeof( wchar_t ) == 2 >::test() )
			wchar_test = (wchar_t*)utf16_April_var;
		else if( ::booldog::compile::If< sizeof( wchar_t ) == 4 >::test() )
			wchar_test = (wchar_t*)utf32_April_var;
		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , wchar_test , 3 , SIZE_MAX );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE( string.length() == 6 );

			REQUIRE(string.bytes() == 13);

			string.insert( 3 , wchar_test , 3 , 3 );

			REQUIRE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}



		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_il_var , cp1251_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_il_var , utf16_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_il_var , utf32_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_il_var , utf8_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_il_var , cp1251_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_il_var , utf16_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_il_var , utf32_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_il_var , utf8_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_il_var , cp1251_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_il_var , utf16_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_il_var , utf32_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_il_var , utf8_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_il_var , cp1251_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_il_var , utf16_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_il_var , utf32_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_il_var , utf8_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}


		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_April_var , cp1251_April_var , SIZE_MAX , 3 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_April_var , utf16_April_var , SIZE_MAX , 3 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_April_var , utf32_April_var , SIZE_MAX , 3 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_April_var , utf8_April_var , SIZE_MAX , 3 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_April_var , cp1251_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_April_var , utf16_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_April_var , utf32_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_April_var , utf8_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_April_var , cp1251_April_var , SIZE_MAX , 12 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_April_var , utf16_April_var , SIZE_MAX , 12 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_April_var , utf32_April_var , SIZE_MAX , 12 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_April_var , utf8_April_var , SIZE_MAX , 12 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_April_var , cp1251_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_April_var , utf16_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_April_var , utf32_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_April_var , utf8_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}


		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_April_var , cp1251_April_var , SIZE_MAX , 3 , 3 , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_April_var , utf16_April_var , SIZE_MAX , 3 , 3 , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_April_var , utf32_April_var , SIZE_MAX , 3 , 3 , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_April_var , utf8_April_var , SIZE_MAX , 3 , 3 , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_April_var , cp1251_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_April_var , utf16_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_April_var , utf32_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_April_var , utf8_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_April_var , cp1251_April_var , SIZE_MAX , 12 , 12 , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_April_var , utf16_April_var , SIZE_MAX , 12 , 12 , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_April_var , utf32_April_var , SIZE_MAX , 12 , 12 , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_April_var , utf8_April_var , SIZE_MAX , 12 , 12 , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_April_var , cp1251_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_April_var , utf16_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_April_var , utf32_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_April_var , utf8_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			REQUIRE(string.length() == 27);

			REQUIRE(string.bytes() == 55);
		}


		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_April_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_April_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_April_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_April_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE( string.length() == 18 );

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_April_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_April_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_April_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_April_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_April_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_April_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_April_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_April_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_April_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_April_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_April_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_April_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			REQUIRE(string.length() == 9);

			REQUIRE(string.bytes() == 19);
		}


		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_Apr_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_Apr_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_Apr_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , cp1251_Apr_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_Apr_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_Apr_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_Apr_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf8_Apr_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_Apr_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_Apr_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_Apr_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf16_Apr_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_Apr_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_Apr_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_Apr_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 0 , utf32_Apr_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);
		}


		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 3 , utf32_April_var , 0 , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE(string.length() == 6);

			REQUIRE(string.bytes() == 13);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 3 , utf16_April_var , 0 , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE(string.length() == 6);

			REQUIRE(string.bytes() == 13);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 3 , utf8_April_var , 0 , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE(string.length() == 6);

			REQUIRE(string.bytes() == 13);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 3 , cp1251_April_var , 0 , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_April_var ) == 0 );

			REQUIRE(string.length() == 6);

			REQUIRE(string.bytes() == 13);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 3 , utf32_April_var , 0 , 1 , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprilApril_var ) == 0 );

			REQUIRE(string.length() == 12);

			REQUIRE(string.bytes() == 25);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 3 , utf16_April_var , 0 , 1 , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprilApril_var ) == 0 );

			REQUIRE(string.length() == 12);

			REQUIRE(string.bytes() == 25);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 3 , utf8_April_var , 0 , 1 , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprilApril_var ) == 0 );

			REQUIRE(string.length() == 12);

			REQUIRE(string.bytes() == 25);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			string.replace( 3 , cp1251_April_var , 0 , 1 , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			REQUIRE( strcmp( string.str() , utf8_AprilApril_var ) == 0 );

			REQUIRE(string.length() == 12);

			REQUIRE(string.bytes() == 25);
		}

		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			REQUIRE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			REQUIRE(string.length() == 18);

			REQUIRE(string.bytes() == 37);

			::booldog::string res( &allocator );
			res = string.substring( &allocator , 12 );

			REQUIRE( strcmp( res.str() , utf8_April_var ) == 0 );

			REQUIRE(res.length() == 6);

			REQUIRE(res.bytes() == 13);
		}

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE(allocator.available() == total);
	}

	REQUIRE( allocator.begin() == begin );
		
	REQUIRE(allocator.available() == total);
};

//class boo_rdwrlockTest : public ::testing::Test 
//{
//};
TEST_CASE("boo_rdwrlockTest", "test")
{
	::booldog::threading::rdwrlock lock;

	lock.wlock( debuginfo_macros );

	REQUIRE(lock._writer_recursion == 1);

	REQUIRE(lock._writer_readers == (1L << (sizeof(::booldog::int32) * 8 - 2)));


	lock.rlock( debuginfo_macros );

	REQUIRE(lock._writer_recursion == 1);

	REQUIRE(lock._writer_readers == (1L << (sizeof(::booldog::int32) * 8 - 2)) + 1);


	lock.wlock( debuginfo_macros );

	REQUIRE(lock._writer_recursion == 2);

	REQUIRE(lock._writer_readers == (1L << (sizeof(::booldog::int32) * 8 - 2)) + 1);


	lock.wunlock( debuginfo_macros );

	REQUIRE(lock._writer_recursion == 1);

	REQUIRE(lock._writer_readers == (1L << (sizeof(::booldog::int32) * 8 - 2)) + 1);



	lock.runlock( debuginfo_macros );

	REQUIRE(lock._writer_recursion == 1);

	REQUIRE(lock._writer_readers == (1L << (sizeof(::booldog::int32) * 8 - 2)));


	lock.wunlock( debuginfo_macros );

	REQUIRE(lock._writer_recursion == 0);

	REQUIRE(lock._writer_readers == 0);
};

//class boo_time_utilsTest : public ::testing::Test 
//{
//};
TEST_CASE("boo_time_utilsTest", "test")
{
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();
	{
		REQUIRE( ::booldog::utils::time::posix::mbs::parse( "2016.03.16 11:46:17:336" ,  "%Y.%m.%d %H:%M:%S:%MS" ) 
			== 1458128777336000ULL );

		REQUIRE( ::booldog::utils::time::posix::mbs::parse( "  2016.03.16 11:46:17:336" ,  "  %Y.%m.%d %H:%M:%S:%MS" ) 
			== 1458128777336000ULL );
		
		::booldog::uint32 year = 0 , month = 0 , day_of_month = 0;

		::booldog::utils::time::posix::date( ::booldog::utils::time::posix::mbs::parse( "  1971.02.01 11:46:17:336" 
			,  "  %Y.%m.%d %H:%M:%S:%MS" ) , year , month , day_of_month );

		REQUIRE( year == 1971 );

		REQUIRE( month == 2 );

		REQUIRE( day_of_month == 1 );


		::booldog::utils::time::posix::date( ::booldog::utils::time::posix::mbs::parse( "  1971.01.01 11:46:17:336" 
			,  "  %Y.%m.%d %H:%M:%S:%MS" ) , year , month , day_of_month );

		REQUIRE( year == 1971 );

		REQUIRE( month == 1 );

		REQUIRE( day_of_month == 1 );


		::booldog::utils::time::posix::date( ::booldog::utils::time::posix::mbs::parse( "  1970.01.01 11:46:17:336" 
			,  "  %Y.%m.%d %H:%M:%S:%MS" ) , year , month , day_of_month );

		REQUIRE( year == 1970 );

		REQUIRE( month == 1 );

		REQUIRE( day_of_month == 1 );


		::booldog::utils::time::posix::date( ::booldog::utils::time::posix::mbs::parse( "  1970.03.08 11:46:17:336" 
			,  "  %Y.%m.%d %H:%M:%S:%MS" ) , year , month , day_of_month );

		REQUIRE( year == 1970 );

		REQUIRE( month == 3 );

		REQUIRE( day_of_month == 8 );


		::booldog::utils::time::posix::date( ::booldog::utils::time::posix::mbs::parse( "  1970.01.05 11:46:17:336" 
			,  "  %Y.%m.%d %H:%M:%S:%MS" ) , year , month , day_of_month );

		REQUIRE( year == 1970 );

		REQUIRE( month == 1 );

		REQUIRE( day_of_month == 5 );


		::booldog::utils::time::posix::date( ::booldog::utils::time::posix::mbs::parse( "  2016.01.01 11:46:17:336" 
			,  "  %Y.%m.%d %H:%M:%S:%MS" ) , year , month , day_of_month );

		REQUIRE( year == 2016 );

		REQUIRE( month == 1 );

		REQUIRE( day_of_month == 1 );


		::booldog::utils::time::posix::date( ::booldog::utils::time::posix::mbs::parse( "  3395.01.01 11:46:17:336" 
			,  "  %Y.%m.%d %H:%M:%S:%MS" ) , year , month , day_of_month );	

		REQUIRE( year == 3395 );

		REQUIRE( month == 1 );

		REQUIRE( day_of_month == 1 );

		



		REQUIRE( ::booldog::utils::time::posix::day_of_month( 1458128777336000 ) == 16 );

		REQUIRE( ::booldog::utils::time::posix::month( 1458128777336000 ) == 3 );

		REQUIRE( ::booldog::utils::time::posix::year( 1458128777336000 ) == 2016 );

		REQUIRE( ::booldog::utils::time::posix::hour( 1458128777336000 ) == 11 );

		REQUIRE( ::booldog::utils::time::posix::minute( 1458128777336000 ) == 46 );

		REQUIRE( ::booldog::utils::time::posix::second( 1458128777336000 ) == 17 );

		REQUIRE( ::booldog::utils::time::posix::millisecond( 1458128777336000 ) == 336 );

		REQUIRE( ::booldog::utils::time::posix::day_of_week( 1458128777336000 ) == 3 );

		::booldog::uint64 local = ::booldog::utils::time::posix::tolocal( 1458128777336000 );

		REQUIRE( ::booldog::utils::time::posix::toutc( local ) == 1458128777336000 );

		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::time::posix::mbs::tostring< 16 >( &resmbchar , &allocator , 0 , 1458128777336000 , debuginfo_macros );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mblen == 19 );

		REQUIRE( strcmp( resmbchar.mbchar , "11:46:17 16.03.2016" ) == 0 );


		::booldog::utils::time::posix::mbs::tostring< 16 >( &resmbchar , &allocator , "Gt%y %Y%" , 1458128777336000
			, debuginfo_macros );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mblen == 10 );

		REQUIRE( strcmp( resmbchar.mbchar , "Gt%y 2016%" ) == 0 );


		::booldog::utils::time::posix::mbs::tostring< 16 >( &resmbchar , &allocator , "Gt%y %MS%" , 1458128777336000
			, debuginfo_macros );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mblen == 9 );

		REQUIRE( strcmp( resmbchar.mbchar , "Gt%y 336%" ) == 0 );
	//1458128777336000 16.03.2016/11:46:17

		REQUIRE( ::booldog::utils::time::posix::generate( 336 , 17 , 46 , 11 , 16 , 3 , 2016 ) == 1458128777336000ULL );

		

		::booldog::utils::time::posix::mbs::tostring< 16 >( &resmbchar , &allocator , 0 
			, ::booldog::utils::time::posix::add_months( 1458128777336000ULL , 27 ) , debuginfo_macros );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mblen == 19 );

		REQUIRE( strcmp( resmbchar.mbchar , "11:46:17 16.06.2018" ) == 0 );


		::booldog::utils::time::posix::mbs::tostring< 16 >( &resmbchar , &allocator , 0 
			, ::booldog::utils::time::posix::sub_months( 1458128777336000ULL , 27 ) , debuginfo_macros );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mblen == 19 );

		REQUIRE( strcmp( resmbchar.mbchar , "11:46:17 16.12.2013" ) == 0 );	


		::booldog::utils::time::posix::mbs::tostring< 16 >( &resmbchar , &allocator , 0 
			, ::booldog::utils::time::posix::add_years( 1458128777336000ULL , 5 ) , debuginfo_macros );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mblen == 19 );

		REQUIRE( strcmp( resmbchar.mbchar , "11:46:17 16.03.2021" ) == 0 );	


		::booldog::utils::time::posix::mbs::tostring< 16 >( &resmbchar , &allocator , 0 
			, ::booldog::utils::time::posix::sub_years( 1458128777336000ULL , 7 ) , debuginfo_macros );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mblen == 19 );

		REQUIRE( strcmp( resmbchar.mbchar , "11:46:17 16.03.2009" ) == 0 );
	}

	REQUIRE( allocator.begin() == begin );
		
	REQUIRE(allocator.available() == total);
};

//class boo_string_utilsTest : public ::testing::Test 
//{
//};
TEST_CASE("boo_string_utilsTest", "test")
{
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{
		::booldog::result_mbchar mbchar( &allocator );

		const ::booldog::byte md5_hash0[] = { 0xe2 , 0xfc , 0x71 , 0x4c , 0x47 , 0x27 , 0xee , 0x93 , 0x95 , 0xf3 , 0x24 , 0xcd , 0x2e , 0x7f 
			, 0x33 , 0x1f };

		::booldog::utils::string::mbs::toreversehexstring( &mbchar , mbchar.mballocator , md5_hash0 , 16 , debuginfo_macros );

		REQUIRE( mbchar.succeeded() );

		REQUIRE( mbchar.mblen == 32 );

		REQUIRE( strcmp( mbchar.mbchar , "e2fc714c4727ee9395f324cd2e7f331f" ) == 0 );
	}

	{
		::booldog::result resres;
		::booldog::result_mbchar mbchar( &allocator );

		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 0 );

		REQUIRE( strcmp( mbchar.mbchar , "" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 0 );

		REQUIRE( strcmp( mbchar.mbchar , "" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$dev" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 4 );

		REQUIRE( strcmp( mbchar.mbchar , "$dev" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 4 );

		REQUIRE( strcmp( mbchar.mbchar , "$dev" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devnam" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 7 );

		REQUIRE( strcmp( mbchar.mbchar , "$devnam" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 7 );

		REQUIRE( strcmp( mbchar.mbchar , "$devnam" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devnam " , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 8 );

		REQUIRE( strcmp( mbchar.mbchar , "$devnam " ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 8 );

		REQUIRE( strcmp( mbchar.mbchar , "$devnam " ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devname" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 8 );

		REQUIRE( strcmp( mbchar.mbchar , "$devname" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 8 );

		REQUIRE( strcmp( mbchar.mbchar , "camera16" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devname$devname" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 16 );

		REQUIRE( strcmp( mbchar.mbchar , "$devname$devname" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 16 );

		REQUIRE( strcmp( mbchar.mbchar , "camera16camera16" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devname hi $devname" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 20 );

		REQUIRE( strcmp( mbchar.mbchar , "$devname hi $devname" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 20 );

		REQUIRE( strcmp( mbchar.mbchar , "camera16 hi camera16" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devname hi $devname  " , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 22 );

		REQUIRE( strcmp( mbchar.mbchar , "$devname hi $devname  " ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 22 );

		REQUIRE( strcmp( mbchar.mbchar , "camera16 hi camera16  " ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "  $devname hi $devname  " , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 24);

		REQUIRE( strcmp( mbchar.mbchar , "  $devname hi $devname  " ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 24);

		REQUIRE( strcmp( mbchar.mbchar , "  camera16 hi camera16  " ) == 0 );




		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 0);

		REQUIRE(strcmp(mbchar.mbchar, "") == 0);

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "cam16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 0);

		REQUIRE(strcmp(mbchar.mbchar, "") == 0);


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$dev" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 4);

		REQUIRE( strcmp( mbchar.mbchar , "$dev" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "cam16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 4);

		REQUIRE( strcmp( mbchar.mbchar , "$dev" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devnam" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 7 );

		REQUIRE( strcmp( mbchar.mbchar , "$devnam" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "cam16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 7 );

		REQUIRE( strcmp( mbchar.mbchar , "$devnam" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devnam " , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 8 );

		REQUIRE( strcmp( mbchar.mbchar , "$devnam " ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "cam16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 8 );

		REQUIRE( strcmp( mbchar.mbchar , "$devnam " ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devname" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 8 );

		REQUIRE( strcmp( mbchar.mbchar , "$devname" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "cam16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 5 );

		REQUIRE( strcmp( mbchar.mbchar , "cam16" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devname$devname" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 16 );

		REQUIRE( strcmp( mbchar.mbchar , "$devname$devname" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "cam16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 10 );

		REQUIRE( strcmp( mbchar.mbchar , "cam16cam16" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devname hi $devname" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 20 );

		REQUIRE( strcmp( mbchar.mbchar , "$devname hi $devname" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "cam16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 14 );

		REQUIRE( strcmp( mbchar.mbchar , "cam16 hi cam16" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devname hi $devname  " , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 22 );

		REQUIRE( strcmp( mbchar.mbchar , "$devname hi $devname  " ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "cam16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 16 );

		REQUIRE( strcmp( mbchar.mbchar , "cam16 hi cam16  " ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "  $devname hi $devname  " , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 24);

		REQUIRE( strcmp( mbchar.mbchar , "  $devname hi $devname  " ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "cam16" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 18 );

		REQUIRE( strcmp( mbchar.mbchar , "  cam16 hi cam16  " ) == 0 );




		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 0);

		REQUIRE(strcmp(mbchar.mbchar, "") == 0);

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera2216" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 0);

		REQUIRE(strcmp(mbchar.mbchar, "") == 0);


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$dev" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 4);

		REQUIRE( strcmp( mbchar.mbchar , "$dev" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera2216" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 4);

		REQUIRE( strcmp( mbchar.mbchar , "$dev" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devnam" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 7 );

		REQUIRE( strcmp( mbchar.mbchar , "$devnam" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera2216" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 7 );

		REQUIRE( strcmp( mbchar.mbchar , "$devnam" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devnam   " , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 10 );

		REQUIRE( strcmp( mbchar.mbchar , "$devnam   " ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera2216" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 10 );

		REQUIRE( strcmp( mbchar.mbchar , "$devnam   " ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devname" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 8 );

		REQUIRE( strcmp( mbchar.mbchar , "$devname" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera2216" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 10 );

		REQUIRE( strcmp( mbchar.mbchar , "camera2216" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devname$devname" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 16 );

		REQUIRE( strcmp( mbchar.mbchar , "$devname$devname" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera2216" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 20 );

		REQUIRE( strcmp( mbchar.mbchar , "camera2216camera2216" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devname hi $devname" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 20 );

		REQUIRE( strcmp( mbchar.mbchar , "$devname hi $devname" ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera2216" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 24);

		REQUIRE( strcmp( mbchar.mbchar , "camera2216 hi camera2216" ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "$devname hi $devname  " , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 22 );

		REQUIRE( strcmp( mbchar.mbchar , "$devname hi $devname  " ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera2216" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 26 );

		REQUIRE( strcmp( mbchar.mbchar , "camera2216 hi camera2216  " ) == 0 );


		::booldog::utils::string::mbs::assign< 0 >( &resres , mbchar.mballocator , false , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize	, "  $devname hi $devname  " , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE(mbchar.mblen == 24);

		REQUIRE( strcmp( mbchar.mbchar , "  $devname hi $devname  " ) == 0 );

		::booldog::utils::string::mbs::replaceall< 0 >( &resres , mbchar.mballocator , 0 , mbchar.mbchar , mbchar.mblen 
			, mbchar.mbsize , "$devname" , 0 , SIZE_MAX , "camera2216" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( mbchar.mblen == 28 );

		REQUIRE( strcmp( mbchar.mbchar , "  camera2216 hi camera2216  " ) == 0 );
	}

	{
		::booldog::result_bool resbool;

		wchar_t* wcsdst = 0;
		size_t wcsdstlen = 0;
		size_t wcsdstsize = 0;

		::booldog::utils::string::wcs::insert( &resbool , &allocator , true , SIZE_MAX , wcsdst , wcsdstlen , wcsdstsize , 0 );

		REQUIRE_FALSE( resbool.succeeded() );

		REQUIRE( resbool.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( resbool.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::wcs::insert( &resbool , &allocator , true , SIZE_MAX , wcsdst , wcsdstlen , wcsdstsize , L"" );

		REQUIRE_FALSE( resbool.succeeded() );

		REQUIRE( resbool.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( resbool.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::wcs::insert( &resbool , &allocator , true , SIZE_MAX , wcsdst , wcsdstlen , wcsdstsize , L"lib" , 3 );

		REQUIRE_FALSE( resbool.succeeded() );

		REQUIRE( resbool.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( resbool.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::wcs::insert( &resbool , &allocator , true , SIZE_MAX , wcsdst , wcsdstlen , wcsdstsize , L"lib" );

		REQUIRE( resbool.succeeded() );

		REQUIRE( wcsdstlen == 3 );

		REQUIRE( wcsdstsize == 4 * sizeof( wchar_t ) );

		REQUIRE( wcscmp( wcsdst , L"lib" ) == 0 );


		::booldog::utils::string::wcs::insert( &resbool , &allocator , true , 3 , wcsdst , wcsdstlen , wcsdstsize , L"re" );

		REQUIRE( resbool.succeeded() );

		REQUIRE( wcsdstlen == 5 );

		REQUIRE( wcsdstsize == 6 * sizeof( wchar_t ) );

		REQUIRE( wcscmp( wcsdst , L"libre" ) == 0 );


		::booldog::utils::string::wcs::insert( &resbool , &allocator , true , 3 , wcsdst , wcsdstlen , wcsdstsize , L"libcore.so" , 3 , 2 );

		REQUIRE( resbool.succeeded() );

		REQUIRE( wcsdstlen == 7 );

		REQUIRE( wcsdstsize == 8 * sizeof( wchar_t ) );

		REQUIRE( wcscmp( wcsdst , L"libcore" ) == 0 );

		allocator.free( wcsdst );

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE(allocator.available() == total);
	}


	{
		::booldog::result res;

		char* mbsdst = 0;
		size_t mbsdstlen = 0;
		size_t mbsdstsize = 0;

		::booldog::utils::string::mbs::insert< 0 >( &res , &allocator , true , SIZE_MAX , mbsdst , mbsdstlen , mbsdstsize , 0 );

		REQUIRE_FALSE( res.succeeded() );

		REQUIRE( res.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::mbs::insert< 0 >( &res , &allocator , true , SIZE_MAX , mbsdst , mbsdstlen , mbsdstsize , "" );

		REQUIRE_FALSE( res.succeeded() );

		REQUIRE( res.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::mbs::insert< 0 >( &res , &allocator , true , SIZE_MAX , mbsdst , mbsdstlen , mbsdstsize , "lib" , 3 );

		REQUIRE_FALSE( res.succeeded() );

		REQUIRE( res.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::mbs::insert< 0 >( &res , &allocator , true , SIZE_MAX , mbsdst , mbsdstlen , mbsdstsize , "lib" );

		REQUIRE( res.succeeded() );

		REQUIRE( mbsdstlen == 3 );

		REQUIRE( mbsdstsize == 4 );

		REQUIRE( strcmp( mbsdst , "lib" ) == 0 );


		::booldog::utils::string::mbs::insert< 0 >( &res , &allocator , true , 3 , mbsdst , mbsdstlen , mbsdstsize , "re" );

		REQUIRE( res.succeeded() );

		REQUIRE( mbsdstlen == 5 );

		REQUIRE( mbsdstsize == 6 );

		REQUIRE( strcmp( mbsdst , "libre" ) == 0 );


		::booldog::utils::string::mbs::insert< 0 >( &res , &allocator , true , 3 , mbsdst , mbsdstlen , mbsdstsize , "libcore.so" , 3 , 2 );

		REQUIRE( res.succeeded() );

		REQUIRE( mbsdstlen == 7 );

		REQUIRE( mbsdstsize == 8 );

		REQUIRE( strcmp( mbsdst , "libcore" ) == 0 );

		allocator.free( mbsdst );

		REQUIRE( allocator.begin() == begin );
		
		REQUIRE(allocator.available() == total);
	}


	{
		::booldog::result_wchar reswchar( &allocator );

		::booldog::utils::string::mbs::towcs( &reswchar , &allocator , "locale" , 0 , SIZE_MAX );
		
		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 7 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 6 );

		REQUIRE( wcscmp( reswchar.wchar , L"locale" ) == 0 );
	}

	{
		::booldog::result_wchar reswchar( &allocator );

		::booldog::utils::string::mbs::towcs( &reswchar , &allocator , "locale" , 3 , SIZE_MAX );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 4 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 3 );

		REQUIRE( wcscmp( reswchar.wchar , L"ale" ) == 0 );
	}

	{
		::booldog::result_wchar reswchar( &allocator );

		::booldog::utils::string::mbs::towcs( &reswchar , &allocator , "locale" , 3 , 2 );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 3 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 2 );

		REQUIRE( wcscmp( reswchar.wchar , L"al" ) == 0 );
	}

	{
		::booldog::result_wchar reswchar( &allocator );

		::booldog::utils::string::mbs::towcs( &reswchar , &allocator , "locale" , 3 , 2 );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 3 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 2 );

		REQUIRE( wcscmp( reswchar.wchar , L"al" ) == 0 );

		::booldog::result res;

		::booldog::utils::string::mbs::insert( &res , &allocator , true , 2 , reswchar.wchar , reswchar.wlen , reswchar.wsize , "e" , 0 , SIZE_MAX );

		REQUIRE( res.succeeded() );

		REQUIRE( reswchar.wsize == 4 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 3 );

		REQUIRE( wcscmp( reswchar.wchar , L"ale" ) == 0 );


		::booldog::utils::string::mbs::insert( &res , &allocator , true , 0 , reswchar.wchar , reswchar.wlen , reswchar.wsize , "locale" , 0 , 2 );

		REQUIRE( res.succeeded() );

		REQUIRE( reswchar.wsize == 6 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 5 );

		REQUIRE( wcscmp( reswchar.wchar , L"loale" ) == 0 );


		::booldog::utils::string::mbs::insert( &res , &allocator , true , 2 , reswchar.wchar , reswchar.wlen , reswchar.wsize , "locale" , 2 , 1 );

		REQUIRE( res.succeeded() );

		REQUIRE( reswchar.wsize == 7 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 6 );

		REQUIRE( wcscmp( reswchar.wchar , L"locale" ) == 0 );
	}



	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::tombs( &resmbchar , &allocator , L"locale" , 0 , SIZE_MAX );
		
		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 7 );

		REQUIRE( resmbchar.mblen == 6 );

		REQUIRE( strcmp( resmbchar.mbchar , "locale" ) == 0 );
	}

	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::toutf8< 1 >( &resmbchar , &allocator , L"locale" , 0 , SIZE_MAX );
		
		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 7 );

		REQUIRE( resmbchar.mblen == 6 );

		REQUIRE( strcmp( resmbchar.mbchar , "locale" ) == 0 );
	}

	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::tombs( &resmbchar , &allocator , L"locale" , 3 , SIZE_MAX );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 4 );

		REQUIRE( resmbchar.mblen == 3 );

		REQUIRE( strcmp( resmbchar.mbchar , "ale" ) == 0 );
	}

	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::toutf8< 1 >( &resmbchar , &allocator , L"locale" , 3 , SIZE_MAX );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE(resmbchar.mbsize == 4);

		REQUIRE(resmbchar.mblen == 3);

		REQUIRE( strcmp( resmbchar.mbchar , "ale" ) == 0 );
	}

	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::tombs( &resmbchar , &allocator , L"locale" , 3 , 2 );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE(resmbchar.mbsize == 3);

		REQUIRE(resmbchar.mblen == 2);

		REQUIRE( strcmp( resmbchar.mbchar , "al" ) == 0 );
	}

	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::toutf8< 1 >( &resmbchar , &allocator , L"locale" , 3 , 2 );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE(resmbchar.mbsize == 3);

		REQUIRE(resmbchar.mblen == 2);

		REQUIRE( strcmp( resmbchar.mbchar , "al" ) == 0 );
	}

	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::tombs( &resmbchar , &allocator , L"locale" , 3 , 2 );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE(resmbchar.mbsize == 3);

		REQUIRE(resmbchar.mblen == 2);

		REQUIRE( strcmp( resmbchar.mbchar , "al" ) == 0 );

		::booldog::result res;

		::booldog::utils::string::wcs::insert( &res , &allocator , true , 2 , resmbchar.mbchar , resmbchar.mblen , resmbchar.mbsize , L"e" , 0 , SIZE_MAX );

		REQUIRE( res.succeeded() );

		REQUIRE(resmbchar.mbsize == 4);

		REQUIRE(resmbchar.mblen == 3);

		REQUIRE( strcmp( resmbchar.mbchar , "ale" ) == 0 );


		::booldog::utils::string::wcs::insert( &res , &allocator , true , 0 , resmbchar.mbchar , resmbchar.mblen , resmbchar.mbsize , L"locale" , 0 , 2 );

		REQUIRE( res.succeeded() );

		REQUIRE(resmbchar.mbsize == 6);

		REQUIRE(resmbchar.mblen == 5);

		REQUIRE( strcmp( resmbchar.mbchar , "loale" ) == 0 );


		::booldog::utils::string::wcs::insert( &res , &allocator , true , 2 , resmbchar.mbchar , resmbchar.mblen , resmbchar.mbsize , L"locale" , 2 , 1 );

		REQUIRE( res.succeeded() );

		REQUIRE(resmbchar.mbsize == 7);

		REQUIRE(resmbchar.mblen == 6);

		REQUIRE( strcmp( resmbchar.mbchar , "locale" ) == 0 );
	}

	{
		::booldog::result_size ressize;

		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "lib" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE(ressize.sres == 89);


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "lib898" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE(ressize.sres == SIZE_MAX);


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "7f6" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE(ressize.sres == 0);


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , ".so" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 105 );


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 1 , SIZE_MAX , "7f6" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 12 );


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 1 , 15 , "7f6" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 12 );

		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 1 , 14 , "7f6" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == SIZE_MAX );


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "rtmp.so" , 1 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == SIZE_MAX );


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "rtmp.so" , 4 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 105 );


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "rtmp.so" , 5 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 106 );


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "rtmp.so" , 4 , 3 , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 105 );


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "rtmp.so" , 4 , 2 , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 105 );


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "rtmp.so" , 4 , 1 , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 86 );


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "rtmphome.so" , 4 , 4 , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 61 );


		::booldog::utils::string::mbs::indexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "video-se" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 72 );


		::booldog::utils::string::mbs::lastindexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "/lib" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 97 );


		::booldog::utils::string::mbs::lastindexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "7f6" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 13 );


		::booldog::utils::string::mbs::lastindexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , ".so" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 105 );


		::booldog::utils::string::mbs::lastindexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 13 , SIZE_MAX , "7f6" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 0 );


		::booldog::utils::string::mbs::lastindexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , 13 , "7f6" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 0 );


		::booldog::utils::string::mbs::lastindexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , 16 , "7f6" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 13 );
		

		::booldog::utils::string::mbs::lastindexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 13 , 3 , "7f6" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 0 );


		::booldog::utils::string::mbs::lastindexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 13 , 2 , "7f6" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == SIZE_MAX );


		::booldog::utils::string::mbs::lastindexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "7f6" , 1 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 14 );


		::booldog::utils::string::mbs::lastindexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "7f600" , 1 , 2 , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 14 );


		::booldog::utils::string::mbs::lastindexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "7f600" , 1 , 1 , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 14 );


		::booldog::utils::string::mbs::lastindexof( &ressize , false , "7f6e0c400000-7f6e0c432000 r-xp 00000000 08:06 22283772"
			"      /home/test1/video-server-7.0/lib/IP3S/libIP3S.so" , 0 , SIZE_MAX , "video-se" , 0 , SIZE_MAX , debuginfo_macros );

		REQUIRE( ressize.succeeded() );

		REQUIRE( ressize.sres == 72 );
	}

	{
		::booldog::result_mbchar numbermbchar( &allocator );

		::booldog::utils::string::mbs::tostring( &numbermbchar , &allocator , 0L , debuginfo_macros );

		REQUIRE( numbermbchar.succeeded() );

		REQUIRE( numbermbchar.mblen == 1 );

		REQUIRE( strcmp( numbermbchar.mbchar , "0" ) == 0 );


		::booldog::utils::string::mbs::tostring( &numbermbchar , &allocator , 2L , debuginfo_macros );

		REQUIRE( numbermbchar.succeeded() );

		REQUIRE( numbermbchar.mblen == 1 );

		REQUIRE( strcmp( numbermbchar.mbchar , "2" ) == 0 );


		::booldog::utils::string::mbs::tostring( &numbermbchar , &allocator , 2908980L , debuginfo_macros );

		REQUIRE( numbermbchar.succeeded() );

		REQUIRE( numbermbchar.mblen == 7 );

		REQUIRE( strcmp( numbermbchar.mbchar , "2908980" ) == 0 );


		::booldog::utils::string::mbs::tostring( &numbermbchar , &allocator , 290898000L , debuginfo_macros );

		REQUIRE( numbermbchar.succeeded() );

		REQUIRE( numbermbchar.mblen == 9 );

		REQUIRE( strcmp( numbermbchar.mbchar , "290898000" ) == 0 );


		::booldog::utils::string::mbs::tostring( &numbermbchar , &allocator , -290898000L , debuginfo_macros );

		REQUIRE( numbermbchar.succeeded() );

		REQUIRE(numbermbchar.mblen == 10);

		REQUIRE( strcmp( numbermbchar.mbchar , "-290898000" ) == 0 );
	}

	REQUIRE( allocator.begin() == begin );
		
	REQUIRE(allocator.available() == total);
};

//class boo_arrayTest : public ::testing::Test 
//{
//};
TEST_CASE("boo_arrayTest", "test")
{
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{
		::booldog::array< const wchar_t* > wcs_array( &allocator );

		REQUIRE(wcs_array.insert( 3 , L"TEST2" ) == 0);

		REQUIRE( wcs_array.count() == 1 );

		REQUIRE( wcscmp( wcs_array[ 0 ] , L"TEST2" ) == 0 );

		REQUIRE( wcs_array.insert( 0 , L"TEST0" ) == 0 );

		REQUIRE( wcs_array.count() == 2 );

		REQUIRE( wcscmp( wcs_array[ 0 ] , L"TEST0" ) == 0 );

		REQUIRE( wcscmp( wcs_array[ 1 ] , L"TEST2" ) == 0 );

		REQUIRE( wcs_array.insert( 1 , L"TEST1" ) == 1 );

		REQUIRE( wcs_array.count() == 3 );

		REQUIRE( wcscmp( wcs_array[ 0 ] , L"TEST0" ) == 0 );

		REQUIRE( wcscmp( wcs_array[ 1 ] , L"TEST1" ) == 0 );

		REQUIRE( wcscmp( wcs_array[ 2 ] , L"TEST2" ) == 0 );

		wcs_array.clear();

		REQUIRE( wcs_array.count() == 0 );


		REQUIRE( wcs_array.add( L"TEST2" ) == 0 );

		REQUIRE( wcs_array.count() == 1 );

		REQUIRE( wcscmp( wcs_array[ 0 ] , L"TEST2" ) == 0 );

		REQUIRE( wcs_array.add( L"TEST0" ) == 1 );

		REQUIRE( wcs_array.count() == 2 );

		REQUIRE( wcscmp( wcs_array[ 0 ] , L"TEST2" ) == 0 );

		REQUIRE( wcscmp( wcs_array[ 1 ] , L"TEST0" ) == 0 );

		REQUIRE( wcs_array.add( L"TEST1" ) == 2 );

		REQUIRE( wcs_array.count() == 3 );

		REQUIRE( wcscmp( wcs_array[ 0 ] , L"TEST2" ) == 0 );

		REQUIRE( wcscmp( wcs_array[ 1 ] , L"TEST0" ) == 0 );

		REQUIRE( wcscmp( wcs_array[ 2 ] , L"TEST1" ) == 0 );


		wcs_array.remove( 1 , 4 );

		REQUIRE( wcs_array.count() == 1 );

		REQUIRE( wcscmp( wcs_array[ 0 ] , L"TEST2" ) == 0 );


		REQUIRE( wcs_array.add( L"TEST1" ) == 1 );

		REQUIRE( wcs_array.count() == 2 );

		REQUIRE( wcscmp( wcs_array[ 0 ] , L"TEST2" ) == 0 );

		REQUIRE( wcscmp( wcs_array[ 1 ] , L"TEST1" ) == 0 );


		wcs_array.remove( 0 , 1 );

		REQUIRE( wcs_array.count() == 1 );

		REQUIRE( wcscmp( wcs_array[ 0 ] , L"TEST1" ) == 0 );
	}

	REQUIRE( allocator.begin() == begin );
		
	REQUIRE(allocator.available() == total);
};

//class boo_listTest : public ::testing::Test 
//{
//};
TEST_CASE("boo_listTest", "test")
{
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{
		::booldog::string item0( &allocator , "TEST0" );

		::booldog::string item1( &allocator , "TEST1" );

		::booldog::string item2( &allocator , "TEST2" );

		::booldog::list< ::booldog::string > string_array( &allocator );

		::booldog::list< ::booldog::object > object_array( &allocator );


		REQUIRE( string_array.insert( 3 , item2 ) == 0 );

		REQUIRE( string_array.count() == 1 );

		REQUIRE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

		REQUIRE( string_array.insert( 0 , item0 ) == 0 );

		REQUIRE( string_array.count() == 2 );

		REQUIRE( strcmp( string_array[ 0 ].str() , "TEST0" ) == 0 );

		REQUIRE( strcmp( string_array[ 1 ].str() , "TEST2" ) == 0 );

		REQUIRE( string_array.insert( 1 , item1 ) == 1 );

		REQUIRE( string_array.count() == 3 );

		REQUIRE( strcmp( string_array[ 0 ].str() , "TEST0" ) == 0 );

		REQUIRE( strcmp( string_array[ 1 ].str() , "TEST1" ) == 0 );

		REQUIRE( strcmp( string_array[ 2 ].str() , "TEST2" ) == 0 );

		string_array.clear();

		REQUIRE( string_array.count() == 0 );


		REQUIRE( string_array.add( item2 ) == 0 );

		REQUIRE( string_array.count() == 1 );

		REQUIRE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

		REQUIRE( string_array.add( item0 ) == 1 );

		REQUIRE( string_array.count() == 2 );

		REQUIRE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

		REQUIRE( strcmp( string_array[ 1 ].str() , "TEST0" ) == 0 );

		REQUIRE( string_array.add( item1 ) == 2 );

		REQUIRE( string_array.count() == 3 );

		REQUIRE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

		REQUIRE( strcmp( string_array[ 1 ].str() , "TEST0" ) == 0 );

		REQUIRE( strcmp( string_array[ 2 ].str() , "TEST1" ) == 0 );


		string_array.remove( 1 , 4 );

		REQUIRE( string_array.count() == 1 );

		REQUIRE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );


		REQUIRE( string_array.add( item1 ) == 1 );

		REQUIRE( string_array.count() == 2 );

		REQUIRE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

		REQUIRE( strcmp( string_array[ 1 ].str() , "TEST1" ) == 0 );


		string_array.remove( 0 , 1 );

		REQUIRE( string_array.count() == 1 );

		REQUIRE( strcmp( string_array[ 0 ].str() , "TEST1" ) == 0 );


		string_array.insert( 1 , object_array );

	}

	REQUIRE( allocator.begin() == begin );
		
	REQUIRE(allocator.available() == total);
};


//class boo_assignmentTest : public ::testing::Test 
//{
//};
TEST_CASE("boo_assignmentTest", "test")
{
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();


	::booldog::object obj( &allocator );

	::booldog::string str( &allocator );

	::booldog::list< ::booldog::string > str_array( &allocator );

	::booldog::list< ::booldog::object > obj_array( &allocator );

	::booldog::list< ::booldog::list< ::booldog::object > > obj_array_array( &allocator );

	::booldog::list< ::booldog::list< ::booldog::string > > str_array_array( &allocator );


	REQUIRE( allocator.begin() == begin );
		
	REQUIRE(allocator.available() == total);
};


//class boo_checkTest : public ::testing::Test 
//{
//};
TEST_CASE("boo_checkTest", "test")
{
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{
		::booldog::object obj( &allocator );

		::booldog::string str( &allocator );

		::booldog::list< ::booldog::string > str_array( &allocator );

		::booldog::list< ::booldog::object > obj_array( &allocator );

		::booldog::list< ::booldog::list< ::booldog::object > > obj_array_array( &allocator );

		::booldog::list< ::booldog::list< ::booldog::string > > str_array_array( &allocator );


		REQUIRE( ::booldog::can_assign< ::booldog::object >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		REQUIRE( ::booldog::can_assign< ::booldog::object >( str ) );

		REQUIRE( ::booldog::can_assign< ::booldog::string >( str ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( str ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( str ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( str ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( str ) );


		REQUIRE( ::booldog::can_assign< ::booldog::object >( str_array ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::string >( str_array ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( str_array ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( str_array ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( str_array ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( str_array ) );


		REQUIRE( ::booldog::can_assign< ::booldog::object >( obj_array ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::string >( obj_array ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj_array ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj_array ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj_array ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj_array ) );


		REQUIRE( ::booldog::can_assign< ::booldog::object >( obj_array_array ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::string >( obj_array_array ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj_array_array ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj_array_array ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj_array_array ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj_array_array ) );


		REQUIRE( ::booldog::can_assign< ::booldog::object >( str_array_array ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::string >( str_array_array ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( str_array_array ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( str_array_array ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( str_array_array ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( str_array_array ) );


		REQUIRE( ::booldog::isclass< ::booldog::object >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		REQUIRE_FALSE( ::booldog::isclass< ::booldog::object >( str ) );

		REQUIRE( ::booldog::isclass< ::booldog::string >( str ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( str ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( str ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( str ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( str ) );


		REQUIRE_FALSE( ::booldog::isclass< ::booldog::object >( str_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::string >( str_array ) );

		REQUIRE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( str_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( str_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( str_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( str_array ) );


		REQUIRE_FALSE( ::booldog::isclass< ::booldog::object >( obj_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::string >( obj_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj_array ) );

		REQUIRE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj_array ) );


		REQUIRE_FALSE( ::booldog::isclass< ::booldog::object >( obj_array_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::string >( obj_array_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj_array_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj_array_array ) );

		REQUIRE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj_array_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj_array_array ) );


		REQUIRE_FALSE( ::booldog::isclass< ::booldog::object >( str_array_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::string >( str_array_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( str_array_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( str_array_array ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( str_array_array ) );

		REQUIRE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( str_array_array ) );


		obj = str;

		REQUIRE( ::booldog::can_assign< ::booldog::object >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::string >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		REQUIRE_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

		REQUIRE( ::booldog::isclass< ::booldog::string >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		obj = str_array;

		REQUIRE( ::booldog::can_assign< ::booldog::object >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		REQUIRE_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

		REQUIRE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		obj = obj_array;

		REQUIRE( ::booldog::can_assign< ::booldog::object >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		REQUIRE_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj ) );

		REQUIRE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		obj = obj_array_array;

		REQUIRE( ::booldog::can_assign< ::booldog::object >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		REQUIRE_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj ) );

		REQUIRE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		obj = str_array_array;

		REQUIRE( ::booldog::can_assign< ::booldog::object >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

		REQUIRE_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		REQUIRE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		REQUIRE_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj ) );

		REQUIRE_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		REQUIRE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );
	}

	REQUIRE( allocator.begin() == begin );
		
	REQUIRE(allocator.available() == total);
};

//class boo_hash_md5Test : public ::testing::Test 
//{
//};
TEST_CASE("boo_hash_md5Test", "test")
{
	::booldog::allocators::easy::heap heap;
	::booldog::allocators::mixed< 16 * 1024 > allocator( &heap );
	
	size_t total = allocator.stack.available();

	char* begin = (char*)allocator.stack.begin();
	{
		::booldog::result_buffer resbuf( &allocator );
		::booldog::hash::md5::calculate( &resbuf , resbuf.allocator , (::booldog::byte*)"abcd" , 4 , debuginfo_macros );

		const ::booldog::byte md5_hash0[] = { 0xe2 , 0xfc , 0x71 , 0x4c , 0x47 , 0x27 , 0xee , 0x93 , 0x95 , 0xf3 , 0x24 , 0xcd , 0x2e , 0x7f 
			, 0x33 , 0x1f };
		
		REQUIRE( resbuf.bufdatasize == 16 );

		REQUIRE( memcmp( resbuf.buf , md5_hash0 , 16 ) == 0 );
	}

	REQUIRE( allocator.stack.begin() == begin );

	REQUIRE( allocator.stack.available() == total );

	REQUIRE( allocator.holder.heap->size_of_allocated_memory() == 0 );
};

//class boo_io_utilsTest : public ::testing::Test 
//{
//};
TEST_CASE("boo_io_utilsTest", "test")
{
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{
		::booldog::result_bool res;

		booldog::param search_paths_params[] =
		{
			BOOPARAM_PCHAR( "../../test_data\\modules0/x86" ) ,
			BOOPARAM_PWCHAR( L"..\\../test_data\\modules1\\x86" ) ,
			BOOPARAM_PCHAR( "../../test_data\\json" ) ,
			BOOPARAM_PCHAR( "../../test_data" ) ,
			BOOPARAM_NONE
		};
		booldog::named_param load_params[] =
		{
			BOONAMED_PARAM_PPARAM( "search_paths" , search_paths_params ) ,
			BOONAMED_PARAM_BOOL( "exedir_as_root_path" , true ) ,
			BOONAMED_PARAM_NONE
		};
		::booldog::utils::io::file::mbs::exists( &res , &allocator , "core1" , load_params );

		REQUIRE( res.succeeded() );

		REQUIRE_FALSE( res.bres );

		::booldog::utils::io::file::mbs::exists( &res , &allocator , "core.dll" , load_params );
		
		REQUIRE( res.succeeded() );

		REQUIRE( res.bres );


		::booldog::utils::io::file::mbs::exists( &res , &allocator , "json_test2.txt" , load_params );
		
		REQUIRE( res.succeeded() );

		REQUIRE( res.bres );


		::booldog::utils::io::file::mbs::exists( &res , &allocator , "maps" , load_params );
		
		REQUIRE( res.succeeded() );

		REQUIRE( res.bres );


		::booldog::utils::io::file::wcs::exists( &res , &allocator , L"core1" , load_params );

		REQUIRE( res.succeeded() );

		REQUIRE_FALSE( res.bres );

		::booldog::utils::io::file::wcs::exists( &res , &allocator , L"core.dll" , load_params );
		
		REQUIRE( res.succeeded() );

		REQUIRE( res.bres );


		::booldog::utils::io::file::wcs::exists( &res , &allocator , L"json_test2.txt" , load_params );
		
		REQUIRE( res.succeeded() );

		REQUIRE( res.bres );


		::booldog::utils::io::file::wcs::exists( &res , &allocator , L"maps" , load_params );
		
		REQUIRE( res.succeeded() );

		REQUIRE( res.bres );
	}

	{

		const wchar_t* wtest = L"C:/privet\\../gui.exe\\./..\\ui.exe";
		const char* mbtest = "C:/privet\\../gui.exe\\./..\\ui.exe";

		const wchar_t* wtest2 = L"C:/privet\\../gui.exe\\./..\\ui";
		const char* mbtest2 = "C:/privet\\../gui.exe\\./..\\ui";

		::booldog::result_wchar reswchar( &allocator );
	
		::booldog::utils::io::path::wcs::filename( &reswchar , &allocator , wtest );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 7 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 6 );

		REQUIRE( wcscmp( reswchar.wchar , L"ui.exe" ) == 0 );

		::booldog::utils::io::path::wcs::filename( &reswchar , &allocator , wtest , 3 , 17 );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 8 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 7 );

		REQUIRE( wcscmp( reswchar.wchar , L"gui.exe" ) == 0 );


		::booldog::utils::io::path::wcs::directory( &reswchar , &allocator , wtest );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 26 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 25 );

		REQUIRE( wcscmp( reswchar.wchar , L"C:/privet\\../gui.exe\\./.." ) == 0 );

		::booldog::utils::io::path::wcs::directory( &reswchar , &allocator , wtest , 3 , 17 );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 10 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 9 );

		REQUIRE( wcscmp( reswchar.wchar , L"privet\\.." ) == 0 );


		::booldog::utils::io::path::wcs::extension( &reswchar , &allocator , wtest );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 4 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 3 );

		REQUIRE( wcscmp( reswchar.wchar , L"exe" ) == 0 );

		::booldog::utils::io::path::wcs::extension( &reswchar , &allocator , wtest , 3 , 16 );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 3 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 2 );

		REQUIRE( wcscmp( reswchar.wchar , L"ex" ) == 0 );

		::booldog::utils::io::path::wcs::extension( &reswchar , &allocator , wtest2 );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 1 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 0 );

		REQUIRE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::result_mbchar resmbchar( &allocator );
	
		::booldog::utils::io::path::mbs::filename( &resmbchar , &allocator , mbtest );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE(resmbchar.mbsize == 7);

		REQUIRE(resmbchar.mblen == 6);

		REQUIRE( strcmp( resmbchar.mbchar , "ui.exe" ) == 0 );

		::booldog::utils::io::path::mbs::filename( &resmbchar , &allocator , mbtest , 3 , 17 );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 8 );

		REQUIRE( resmbchar.mblen == 7 );

		REQUIRE( strcmp( resmbchar.mbchar , "gui.exe" ) == 0 );


		::booldog::utils::io::path::mbs::directory( &resmbchar , &allocator , mbtest );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 26 );

		REQUIRE( resmbchar.mblen == 25 );

		REQUIRE( strcmp( resmbchar.mbchar , "C:/privet\\../gui.exe\\./.." ) == 0 );

		::booldog::utils::io::path::mbs::directory( &resmbchar , &allocator , mbtest , 3 , 17 );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 10 );

		REQUIRE( resmbchar.mblen == 9 );

		REQUIRE( strcmp( resmbchar.mbchar , "privet\\.." ) == 0 );


		::booldog::utils::io::path::mbs::extension( &resmbchar , &allocator , mbtest );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE(resmbchar.mbsize == 4);

		REQUIRE(resmbchar.mblen == 3);

		REQUIRE( strcmp( resmbchar.mbchar , "exe" ) == 0 );

		::booldog::utils::io::path::mbs::extension( &resmbchar , &allocator , mbtest , 3 , 16 );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE(resmbchar.mbsize == 3);

		REQUIRE(resmbchar.mblen == 2);

		REQUIRE( strcmp( resmbchar.mbchar , "ex" ) == 0 );

		::booldog::utils::io::path::mbs::extension( &resmbchar , &allocator , mbtest2 );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 1 );

		REQUIRE( resmbchar.mblen == 0 );

		REQUIRE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"home\\kill/." );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 12 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 9 );

		REQUIRE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"home\\./.\\kill/." );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 16 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 9 );

		REQUIRE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"./home\\./.\\kill/." );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 18 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 9 );

		REQUIRE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"./home/try\\explain\\./.\\../..\\kill/." );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 36 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 9 );

		REQUIRE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"./home/try\\explain\\./.\\../..\\kill/joke\\.." );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 42 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 9 );

		REQUIRE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"/home/.." );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 9 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 0 );

		REQUIRE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L".\\" );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 3 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 0 );

		REQUIRE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"." );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 2 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 0 );

		REQUIRE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"home\\./\\.\\kill/." );

		REQUIRE_FALSE( reswchar.succeeded() );

		REQUIRE( reswchar.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( reswchar.booerror == ::booldog::enums::result::booerr_type_path_has_incorrect_format );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"./.\\../kill/." );

		REQUIRE_FALSE( reswchar.succeeded() );

		REQUIRE( reswchar.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( reswchar.booerror == ::booldog::enums::result::booerr_type_not_enough_top_level_folders );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"../local" );

		REQUIRE_FALSE( reswchar.succeeded() );

		REQUIRE(reswchar.get_error_type() == ::booldog::enums::result::error_type_booerr);

		REQUIRE( reswchar.booerror == ::booldog::enums::result::booerr_type_not_enough_top_level_folders );



		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "home\\kill/." );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 12 );

		REQUIRE( resmbchar.mblen == 9 );

		REQUIRE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "home\\./.\\kill/." );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 16 );

		REQUIRE( resmbchar.mblen == 9 );

		REQUIRE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "./home\\./.\\kill/." );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 18 );

		REQUIRE( resmbchar.mblen == 9 );

		REQUIRE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "./home/try\\explain\\./.\\../..\\kill/." );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 36 );

		REQUIRE( resmbchar.mblen == 9 );

		REQUIRE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "./home/try\\explain\\./.\\../..\\kill/joke\\.." );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 42 );

		REQUIRE( resmbchar.mblen == 9 );

		REQUIRE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "/home/.." );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 9 );

		REQUIRE( resmbchar.mblen == 0 );

		REQUIRE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , ".\\" );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE(resmbchar.mbsize == 3);

		REQUIRE( resmbchar.mblen == 0 );

		REQUIRE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "." );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 2 );

		REQUIRE( resmbchar.mblen == 0 );

		REQUIRE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "home\\./\\.\\kill/." );

		REQUIRE_FALSE( resmbchar.succeeded() );

		REQUIRE( resmbchar.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( resmbchar.booerror == ::booldog::enums::result::booerr_type_path_has_incorrect_format );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "./.\\../kill/." );

		REQUIRE_FALSE( resmbchar.succeeded() );

		REQUIRE( resmbchar.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( resmbchar.booerror == ::booldog::enums::result::booerr_type_not_enough_top_level_folders );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "../local" );

		REQUIRE_FALSE( resmbchar.succeeded() );

		REQUIRE( resmbchar.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( resmbchar.booerror == ::booldog::enums::result::booerr_type_not_enough_top_level_folders );


		::booldog::result_bool resbool;

		::booldog::utils::io::path::wcs::has_levels( &resbool , 0 );

		REQUIRE_FALSE( resbool.succeeded() );

		REQUIRE( resbool.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( resbool.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::io::path::wcs::has_levels( &resbool , L"" );

		REQUIRE_FALSE( resbool.succeeded() );

		REQUIRE( resbool.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( resbool.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::io::path::wcs::has_levels( &resbool , L"../local/" , 9 );

		REQUIRE_FALSE( resbool.succeeded() );

		REQUIRE( resbool.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( resbool.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::io::path::wcs::has_levels( &resbool , L"../local" );

		REQUIRE( resbool.succeeded() );

		REQUIRE( resbool.bres );


		::booldog::utils::io::path::wcs::has_levels( &resbool , L"../local" , 2 );

		REQUIRE( resbool.succeeded() );

		REQUIRE( resbool.bres );


		::booldog::utils::io::path::wcs::has_levels( &resbool , L"../local" , 3 );

		REQUIRE( resbool.succeeded() );

		REQUIRE_FALSE( resbool.bres );



		::booldog::utils::io::path::mbs::has_levels( &resbool , 0 );

		REQUIRE_FALSE( resbool.succeeded() );

		REQUIRE( resbool.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( resbool.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::io::path::mbs::has_levels( &resbool , "" );

		REQUIRE_FALSE( resbool.succeeded() );

		REQUIRE( resbool.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( resbool.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::io::path::mbs::has_levels( &resbool , "../local/" , 9 );

		REQUIRE_FALSE( resbool.succeeded() );

		REQUIRE( resbool.get_error_type() == ::booldog::enums::result::error_type_booerr );

		REQUIRE( resbool.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::io::path::mbs::has_levels( &resbool , "../local" );

		REQUIRE( resbool.succeeded() );

		REQUIRE( resbool.bres );


		::booldog::utils::io::path::mbs::has_levels( &resbool , "../local" , 2 );

		REQUIRE( resbool.succeeded() );

		REQUIRE( resbool.bres );


		::booldog::utils::io::path::mbs::has_levels( &resbool , "../local" , 3 );

		REQUIRE( resbool.succeeded() );

		REQUIRE_FALSE( resbool.bres );


	
		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"" );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 1 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 0 );

		REQUIRE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"core" );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 5 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 4 );

		REQUIRE( wcscmp( reswchar.wchar , L"core" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"\\home/core" );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 5 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 4 );

		REQUIRE( wcscmp( reswchar.wchar , L"core" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"\\home/core.dll.exe" );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 9 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 8 );

		REQUIRE( wcscmp( reswchar.wchar , L"core.dll" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"\\home/.core" );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 1 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 0 );

		REQUIRE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"\\home/.core" , 7 );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 5 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 4 );

		REQUIRE( wcscmp( reswchar.wchar , L"core" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"\\home/.core.dll.exe" , 7 , 8 );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 5 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 4 );

		REQUIRE( wcscmp( reswchar.wchar , L"core" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"\\home/.core.dll.exe" , 7 , 9 );

		REQUIRE( reswchar.succeeded() );

		REQUIRE( reswchar.wsize == 9 * sizeof( wchar_t ) );

		REQUIRE( reswchar.wlen == 8 );

		REQUIRE( wcscmp( reswchar.wchar , L"core.dll" ) == 0 );



		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "" );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 1 );

		REQUIRE( resmbchar.mblen == 0 );

		REQUIRE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "core" );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 5 );

		REQUIRE( resmbchar.mblen == 4 );

		REQUIRE( strcmp( resmbchar.mbchar , "core" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "\\home/core" );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 5 );

		REQUIRE( resmbchar.mblen == 4 );

		REQUIRE( strcmp( resmbchar.mbchar , "core" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "\\home/core.dll.exe" );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 9 );

		REQUIRE( resmbchar.mblen == 8 );

		REQUIRE( strcmp( resmbchar.mbchar , "core.dll" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "\\home/.core" );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 1 );

		REQUIRE( resmbchar.mblen == 0 );

		REQUIRE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "\\home/.core" , 7 );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 5 );

		REQUIRE( resmbchar.mblen == 4 );

		REQUIRE( strcmp( resmbchar.mbchar , "core" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "\\home/.core.dll.exe" , 7 , 8 );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 5 );

		REQUIRE( resmbchar.mblen == 4 );

		REQUIRE( strcmp( resmbchar.mbchar , "core" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "\\home/.core.dll.exe" , 7 , 9 );

		REQUIRE( resmbchar.succeeded() );

		REQUIRE( resmbchar.mbsize == 9 );

		REQUIRE( resmbchar.mblen == 8 );

		REQUIRE( strcmp( resmbchar.mbchar , "core.dll" ) == 0 );



		{
			::booldog::result res;

			size_t pathnamelen = 0;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , 0 , pathnamelen );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE( res.get_error_type() == ::booldog::enums::result::error_type_booerr );

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = 0;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , pathname , pathnamelen );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE( res.get_error_type() == ::booldog::enums::result::error_type_booerr );

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 4 );

			REQUIRE( wcscmp( pathname , L"core" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e','.','d','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 4 );

			REQUIRE( wcscmp( pathname , L"core" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e','.','d','/','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 9 );

			REQUIRE( wcscmp( pathname , L"core.d/ll" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e','.','d','l','l','.', 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 8 );

			REQUIRE( wcscmp( pathname , L"core.dll" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { '.','c','o','r','e', 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 0 );

			REQUIRE( wcscmp( pathname , L"" ) == 0 );
		}


		{
			::booldog::result res;

			size_t pathnamelen = 0;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , 0 , pathnamelen );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE( res.get_error_type() == ::booldog::enums::result::error_type_booerr );

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = 0;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , pathname , pathnamelen );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE( res.get_error_type() == ::booldog::enums::result::error_type_booerr );

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 4 );

			REQUIRE( strcmp( pathname , "core" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e','.','d','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 4 );

			REQUIRE( strcmp( pathname , "core" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e','.','d','/','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 9 );

			REQUIRE( strcmp( pathname , "core.d/ll" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e','.','d','l','l','.', 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 8 );

			REQUIRE( strcmp( pathname , "core.dll" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { '.','c','o','r','e', 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 0 );

			REQUIRE( strcmp( pathname , "" ) == 0 );
		}


		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "" , 0 , SIZE_MAX );

			REQUIRE( resmbchar.succeeded() );

			REQUIRE( resmbchar.mbsize == 1 );

			REQUIRE( resmbchar.mblen == 0 );

			REQUIRE( strcmp( resmbchar.mbchar , "" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "core" , 0 , SIZE_MAX );

			REQUIRE( resmbchar.succeeded() );

			REQUIRE( resmbchar.mbsize == 5 );

			REQUIRE( resmbchar.mblen == 4 );

			REQUIRE( strcmp( resmbchar.mbchar , "core" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "core.dll.exe" , 0 , SIZE_MAX );

			REQUIRE( resmbchar.succeeded() );

			REQUIRE( resmbchar.mbsize == 9 );

			REQUIRE( resmbchar.mblen == 8 );

			REQUIRE( strcmp( resmbchar.mbchar , "core.dll" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , ".core" , 0 , SIZE_MAX );

			REQUIRE( resmbchar.succeeded() );

			REQUIRE( resmbchar.mbsize == 1 );

			REQUIRE( resmbchar.mblen == 0 );

			REQUIRE( strcmp( resmbchar.mbchar , "" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "core." , 0 , SIZE_MAX );

			REQUIRE( resmbchar.succeeded() );

			REQUIRE( resmbchar.mbsize == 5 );

			REQUIRE( resmbchar.mblen == 4 );

			REQUIRE( strcmp( resmbchar.mbchar , "core" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "/home.exe\\core" , 0 , SIZE_MAX );

			REQUIRE( resmbchar.succeeded() );

			REQUIRE( resmbchar.mbsize == 15 );

			REQUIRE( resmbchar.mblen == 14 );

			REQUIRE( strcmp( resmbchar.mbchar , "/home.exe\\core" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "/home.exe\\core.dll" , 9 , 4 );

			REQUIRE( resmbchar.succeeded() );

			REQUIRE( resmbchar.mbsize == 5 );

			REQUIRE( resmbchar.mblen == 4 );

			REQUIRE( strcmp( resmbchar.mbchar , "\\cor" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "/home.exe\\core.dll" , 1 , 6 );

			REQUIRE( resmbchar.succeeded() );

			REQUIRE( resmbchar.mbsize == 5 );

			REQUIRE( resmbchar.mblen == 4 );

			REQUIRE( strcmp( resmbchar.mbchar , "home" ) == 0 );
		}


		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"" , 0 , SIZE_MAX );

			REQUIRE( reswchar.succeeded() );

			REQUIRE( reswchar.wsize == 1 * sizeof( wchar_t ) );

			REQUIRE( reswchar.wlen == 0 );

			REQUIRE( wcscmp( reswchar.wchar , L"" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"core" , 0 , SIZE_MAX );

			REQUIRE( reswchar.succeeded() );

			REQUIRE( reswchar.wsize == 5 * sizeof( wchar_t ) );

			REQUIRE( reswchar.wlen == 4 );

			REQUIRE( wcscmp( reswchar.wchar , L"core" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"core.dll.exe" , 0 , SIZE_MAX );

			REQUIRE( reswchar.succeeded() );

			REQUIRE( reswchar.wsize == 9 * sizeof( wchar_t ) );

			REQUIRE( reswchar.wlen == 8 );

			REQUIRE( wcscmp( reswchar.wchar , L"core.dll" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L".core" , 0 , SIZE_MAX );

			REQUIRE( reswchar.succeeded() );

			REQUIRE( reswchar.wsize == 1 * sizeof( wchar_t ) );

			REQUIRE( reswchar.wlen == 0 );

			REQUIRE( wcscmp( reswchar.wchar , L"" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"core." , 0 , SIZE_MAX );

			REQUIRE( reswchar.succeeded() );

			REQUIRE( reswchar.wsize == 5 * sizeof( wchar_t ) );

			REQUIRE( reswchar.wlen == 4 );

			REQUIRE( wcscmp( reswchar.wchar , L"core" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"/home.exe\\core" , 0 , SIZE_MAX );

			REQUIRE( reswchar.succeeded() );

			REQUIRE( reswchar.wsize == 15 * sizeof( wchar_t ) );

			REQUIRE( reswchar.wlen == 14 );

			REQUIRE( wcscmp( reswchar.wchar , L"/home.exe\\core" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"/home.exe\\core.dll" , 9 , 4 );

			REQUIRE( reswchar.succeeded() );

			REQUIRE( reswchar.wsize == 5 * sizeof( wchar_t ) );

			REQUIRE( reswchar.wlen == 4 );

			REQUIRE( wcscmp( reswchar.wchar , L"\\cor" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"/home.exe\\core.dll" , 1 , 6 );

			REQUIRE( reswchar.succeeded() );

			REQUIRE( reswchar.wsize == 5 * sizeof( wchar_t ) );

			REQUIRE( reswchar.wlen == 4 );

			REQUIRE( wcscmp( reswchar.wchar , L"home" ) == 0 );
		}


		{
			::booldog::result res;

			size_t pathnamelen = 0;
			::booldog::utils::io::path::wcs::directory( &res , 0 , pathnamelen );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE( res.get_error_type() == ::booldog::enums::result::error_type_booerr );

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = 0;
			::booldog::utils::io::path::wcs::directory( &res , pathname , pathnamelen );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::directory( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 4 );

			REQUIRE( wcscmp( pathname , L"core" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e','\\','d','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::directory( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 4 );

			REQUIRE( wcscmp( pathname , L"core" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e','.','d','/','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::directory( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 6 );

			REQUIRE( wcscmp( pathname , L"core.d" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { '/','c','o','r','e','.','d','l','l','.', 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::directory( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 0 );

			REQUIRE( wcscmp( pathname , L"" ) == 0 );
		}


		{
			::booldog::result res;

			size_t pathnamelen = 0;
			::booldog::utils::io::path::mbs::directory( &res , 0 , pathnamelen );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = 0;
			::booldog::utils::io::path::mbs::directory( &res , pathname , pathnamelen );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::directory( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 4 );

			REQUIRE( strcmp( pathname , "core" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e','\\','d','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::directory( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 4 );

			REQUIRE( strcmp( pathname , "core" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e','.','d','/','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::directory( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 6 );

			REQUIRE( strcmp( pathname , "core.d" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { '/','c','o','r','e','.','d','l','l','.', 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::directory( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 0 );

			REQUIRE( strcmp( pathname , "" ) == 0 );
		}



		{
			::booldog::result res;

			wchar_t pathname[] = { 'h','o','m','e','/','.','.','\\','t','e','s','t','/','.','\\','c','o','r','e','\\', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::normalize( &res , pathname , pathnamelen , pathnamesize );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 10 );
	#ifdef __WINDOWS__
			REQUIRE( wcscmp( pathname , L"\\test\\core" ) == 0 );
	#else
			REQUIRE( wcscmp( pathname , L"/test/core" ) == 0 );
	#endif
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'h','o','m','e','\\','.','/','\\','.','\\','k','i','l','l','/','.', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::normalize( &res , pathname , pathnamelen , pathnamesize );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_path_has_incorrect_format );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { '.','/','.','\\','.','.','/','k','i','l','l','/','.', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::normalize( &res , pathname , pathnamelen , pathnamesize );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { '.','.','/','l','o','c','a','l', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::normalize( &res , pathname , pathnamelen , pathnamesize );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
		}


		{
			::booldog::result res;

			char pathname[] = { 'h','o','m','e','/','.','.','\\','t','e','s','t','/','.','\\','c','o','r','e','\\', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::normalize( &res , pathname , pathnamelen , pathnamesize );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 10 );
	#ifdef __WINDOWS__
			REQUIRE( strcmp( pathname , "\\test\\core" ) == 0 );
	#else
			REQUIRE( strcmp( pathname , "/test/core" ) == 0 );
	#endif
		}

		{
			::booldog::result res;

			char pathname[] = { 'h','o','m','e','\\','.','/','\\','.','\\','k','i','l','l','/','.', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::normalize( &res , pathname , pathnamelen , pathnamesize );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_path_has_incorrect_format );
		}

		{
			::booldog::result res;

			char pathname[] = { '.','/','.','\\','.','.','/','k','i','l','l','/','.', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::normalize( &res , pathname , pathnamelen , pathnamesize );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
		}

		{
			::booldog::result res;

			char pathname[] = { '.','.','/','l','o','c','a','l', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::normalize( &res , pathname , pathnamelen , pathnamesize );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
		}



		{
			::booldog::result res;

			size_t pathnamelen = 0;
			::booldog::utils::io::path::mbs::filename_without_extension( &res , 0 , pathnamelen );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			char pathname[] = { 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::filename_without_extension( &res , pathname , pathnamelen );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			char pathname[] = { '.','.','/','l','o','c','a','l', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::filename_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 5 );

			REQUIRE( strcmp( pathname , "local" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { '.','.','/','b','.','l','o','c','a','l','.','e', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::filename_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 7 );

			REQUIRE( strcmp( pathname , "b.local" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { 'l','o','c','a','l', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::filename_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 5 );

			REQUIRE( strcmp( pathname , "local" ) == 0 );
		}


		{
			::booldog::result res;

			size_t pathnamelen = 0;
			::booldog::utils::io::path::wcs::filename_without_extension( &res , 0 , pathnamelen );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::filename_without_extension( &res , pathname , pathnamelen );

			REQUIRE_FALSE( res.succeeded() );

			REQUIRE(res.get_error_type() == ::booldog::enums::result::error_type_booerr);

			REQUIRE( res.booerror == ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { '.','.','/','l','o','c','a','l', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::filename_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 5 );

			REQUIRE( wcscmp( pathname , L"local" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { '.','.','/','b','.','l','o','c','a','l','.','e', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::filename_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 7 );

			REQUIRE( wcscmp( pathname , L"b.local" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'l','o','c','a','l', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::filename_without_extension( &res , pathname , pathnamelen );

			REQUIRE( res.succeeded() );

			REQUIRE( pathnamelen == 5 );

			REQUIRE( wcscmp( pathname , L"local" ) == 0 );
		}
	}

	REQUIRE( allocator.begin() == begin );
		
	REQUIRE(allocator.available() == total);
};
//class boo_base_loaderTest : public ::testing::Test 
//{
//};
TEST_CASE("boo_base_loaderTest", "test")
{
	::booldog::allocators::stack< 4096 > allocator;
	
	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();
	{
		{
			::booldog::result_mbchar resmbchar( &allocator );
			::booldog::utils::executable::mbs::pathname< 4 >( &resmbchar , &allocator );
			{
				::booldog::result res;

				::booldog::utils::io::path::mbs::filename_without_extension( &res , resmbchar.mbchar , resmbchar.mblen );

				REQUIRE( res.succeeded() );

				REQUIRE( resmbchar.mblen == 12 );

				REQUIRE( strcmp( resmbchar.mbchar , "booldog.test" ) == 0 );
			}
		}
		{
			::booldog::result_wchar reswchar( &allocator );
			::booldog::utils::executable::wcs::pathname< 4 >( &reswchar , &allocator );
			{
				::booldog::result res;

				::booldog::utils::io::path::wcs::filename_without_extension( &res , reswchar.wchar , reswchar.wlen );

				REQUIRE( res.succeeded() );

				REQUIRE( reswchar.wlen == 12 );

				REQUIRE( wcscmp( reswchar.wchar , L"booldog.test" ) == 0 );
			}
		}
		::booldog::loader loader( &allocator );

		::booldog::result_module res;
	#ifdef __x64__
		booldog::param search_paths_params[] =
		{
			BOOPARAM_PCHAR( "../../test_data\\modules0/x64" ) ,
			BOOPARAM_PWCHAR( L"..\\../test_data\\modules1\\x64" ) ,
			BOOPARAM_NONE
		};
	#elif defined( __x86__ )
		booldog::param search_paths_params[] =
		{
			BOOPARAM_PCHAR( "../../test_data\\modules0/x86" ) ,
			BOOPARAM_PWCHAR( L"..\\../test_data\\modules1\\x86" ) ,
			BOOPARAM_NONE
		};
	#endif
		booldog::named_param load_params[] =
		{
			BOONAMED_PARAM_PPARAM( "search_paths" , search_paths_params ) ,
			BOONAMED_PARAM_BOOL( "exedir_as_root_path" , true ) ,
			BOONAMED_PARAM_NONE
		};

		loader.wcsload( &res , &allocator , L"core1" , load_params );

		REQUIRE_FALSE( res.succeeded() );

		loader.wcsload( &res , &allocator , L"core" , load_params );
		
		REQUIRE( res.succeeded() );

		::booldog::base::module* module0 = res.module;

		loader.wcsload( &res , &allocator , L"core" , 0 );

		REQUIRE( res.succeeded() );

		::booldog::base::module* module1 = res.module;

		{
			::booldog::result_mbchar resmbchar( &allocator );
			::booldog::utils::module::mbs::pathname< 4 >( &resmbchar , &allocator , module1->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::mbs::filename_without_extension( &res , resmbchar.mbchar , resmbchar.mblen );

				REQUIRE( res.succeeded() );
#ifdef __WINDOWS__
				REQUIRE( resmbchar.mblen == 4 );

				REQUIRE( strcmp( resmbchar.mbchar , "core" ) == 0 );
#else
				REQUIRE( resmbchar.mblen == 7 );

				REQUIRE( strcmp( resmbchar.mbchar , "libcore" ) == 0 );
#endif
			}
		}
		{
			::booldog::result_wchar reswchar( &allocator );
			::booldog::utils::module::wcs::pathname< 4 >( &reswchar , &allocator , module1->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::wcs::filename_without_extension( &res , reswchar.wchar , reswchar.wlen );

				REQUIRE( res.succeeded() );
#ifdef __WINDOWS__
				REQUIRE( reswchar.wlen == 4 );

				REQUIRE( wcscmp( reswchar.wchar , L"core" ) == 0 );
#else
				REQUIRE( reswchar.wlen == 7 );

				REQUIRE( wcscmp( reswchar.wchar , L"libcore" ) == 0 );
#endif
			}
		}


		::booldog::result resres;
		loader.unload( &resres , module0 , 0 , 0 );

		REQUIRE( res.succeeded() );

		loader.unload( &resres , module1 , 0 , 0 );

		REQUIRE( res.succeeded() );

#ifdef __WINDOWS__
		loader.wcsload( &res , &allocator , L"kernel32" , 0 );
#else
		loader.wcsload( &res , &allocator , L"rt" , 0 );
#endif

		REQUIRE( res.succeeded() );

		::booldog::base::module* module2 = res.module;

		{
			::booldog::result_mbchar resmbchar( &allocator );
			::booldog::utils::module::mbs::pathname< 4 >( &resmbchar , &allocator , module2->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::mbs::filename_without_extension( &res , resmbchar.mbchar , resmbchar.mblen );

				REQUIRE( res.succeeded() );
#ifdef __WINDOWS__
				REQUIRE( resmbchar.mblen == 8 );

				REQUIRE( strcmp( resmbchar.mbchar , "kernel32" ) == 0 );
#else
				REQUIRE(resmbchar.mblen == 8);

				REQUIRE( strcmp( resmbchar.mbchar , "librt.so" ) == 0 );
#endif
			}
		}
		{
			::booldog::result_wchar reswchar( &allocator );
			::booldog::utils::module::wcs::pathname< 4 >( &reswchar , &allocator , module2->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::wcs::filename_without_extension( &res , reswchar.wchar , reswchar.wlen );

				REQUIRE( res.succeeded() );
#ifdef __WINDOWS__
				REQUIRE( reswchar.wlen == 8 );

				REQUIRE( wcscmp( reswchar.wchar , L"kernel32" ) == 0 );
#else
				REQUIRE(reswchar.wlen == 8);

				REQUIRE( wcscmp( reswchar.wchar , L"librt.so" ) == 0 );
#endif
			}
		}

		loader.unload( &resres , module2 , 0 , 0 );

		REQUIRE( res.succeeded() );



		loader.mbsload( &res , &allocator , "core1" , load_params );

		REQUIRE_FALSE( res.succeeded() );

		loader.mbsload( &res , &allocator , "core" , load_params );

		REQUIRE( res.succeeded() );

		module0 = res.module;

		loader.mbsload( &res , &allocator , "core" , 0 );

		REQUIRE( res.succeeded() );	

		module1 = res.module;

		{
			::booldog::result_mbchar resmbchar( &allocator );
			::booldog::utils::module::mbs::pathname< 4 >( &resmbchar , &allocator , module1->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::mbs::filename_without_extension( &res , resmbchar.mbchar , resmbchar.mblen );

				REQUIRE( res.succeeded() );
#ifdef __WINDOWS__
				REQUIRE( resmbchar.mblen == 4 );

				REQUIRE( strcmp( resmbchar.mbchar , "core" ) == 0 );
#else
				REQUIRE( resmbchar.mblen == 7 );

				REQUIRE( strcmp( resmbchar.mbchar , "libcore" ) == 0 );
#endif
			}
		}
		{
			::booldog::result_wchar reswchar( &allocator );
			::booldog::utils::module::wcs::pathname< 4 >( &reswchar , &allocator , module1->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::wcs::filename_without_extension( &res , reswchar.wchar , reswchar.wlen );

				REQUIRE( res.succeeded() );
#ifdef __WINDOWS__
				REQUIRE( reswchar.wlen == 4 );

				REQUIRE( wcscmp( reswchar.wchar , L"core" ) == 0 );
#else
				REQUIRE(reswchar.wlen == 7);

				REQUIRE( wcscmp( reswchar.wchar , L"libcore" ) == 0 );
#endif
			}
		}

		loader.unload( &resres , module0 , 0 , 0 );

		REQUIRE( res.succeeded() );

		loader.unload( &resres , module1 , 0 , 0 );

		REQUIRE( res.succeeded() );
#ifdef __WINDOWS__
		loader.mbsload( &res , &allocator , "kernel32" , 0 );
#else
		loader.mbsload( &res , &allocator , "rt" , 0 );
#endif

		REQUIRE( res.succeeded() );

		module2 = res.module;
		{
			::booldog::result_mbchar resmbchar( &allocator );
			::booldog::utils::module::mbs::pathname< 4 >( &resmbchar , &allocator , module2->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::mbs::filename_without_extension( &res , resmbchar.mbchar , resmbchar.mblen );

				REQUIRE( res.succeeded() );
#ifdef __WINDOWS__
				REQUIRE(resmbchar.mblen == 8);

				REQUIRE( strcmp( resmbchar.mbchar , "kernel32" ) == 0 );
#else
				REQUIRE(resmbchar.mblen == 8);

				REQUIRE( strcmp( resmbchar.mbchar , "librt.so" ) == 0 );
#endif
			}
		}
		{
			::booldog::result_wchar reswchar( &allocator );
			::booldog::utils::module::wcs::pathname< 4 >( &reswchar , &allocator , module2->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::wcs::filename_without_extension( &res , reswchar.wchar , reswchar.wlen );

				REQUIRE( res.succeeded() );
#ifdef __WINDOWS__
				REQUIRE(reswchar.wlen == 8);

				REQUIRE( wcscmp( reswchar.wchar , L"kernel32" ) == 0 );
#else
				REQUIRE(reswchar.wlen == 8);

				REQUIRE( wcscmp( reswchar.wchar , L"librt.so" ) == 0 );
#endif
			}
		}		
		loader.unload( &resres , module2 , 0 , 0 );

		REQUIRE( res.succeeded() );
		

		loader.mbsload( &res , &allocator , "core" , load_params );

		REQUIRE( res.succeeded() );

		module0 = res.module;


		loader.mbsload( &res , &allocator , "language" , load_params );

		/*char* errorstr = 0;
		size_t errorstrlen = 0 , errorstrsize = 0;
		::booldog::error::format( &res , errorstr , errorstrlen , errorstrsize );
		printf( "error %s\n" , errorstr );*/

		REQUIRE( res.succeeded() );

		module2 = res.module;

		::booldog::result_pointer respointer;
		::booldog::utils::module::mbs::method( &respointer , &allocator , module2->handle() , "core_init" );

		REQUIRE_FALSE( respointer.succeeded() );

		::booldog::utils::module::mbs::method( &respointer , &allocator , module2->handle() , "dll_init" );

		REQUIRE( respointer.succeeded() );

		
		::booldog::module_handle modhandle = ::booldog::utils::module::handle( &resres , &allocator , respointer.pres , 
			debuginfo_macros );

		REQUIRE( resres.succeeded() );

		REQUIRE( modhandle != 0 );

		REQUIRE( modhandle == module2->handle() );

		::booldog::utils::module::free( &resres , &allocator , modhandle , debuginfo_macros );

		REQUIRE( resres.succeeded() );

		{
			::booldog::result_mbchar resmbchar( &allocator );
			::booldog::utils::module::mbs::pathname_from_address< 4 >( &resmbchar , &allocator , respointer.pres , debuginfo_macros );

			REQUIRE( resmbchar.succeeded() );

			{
				::booldog::result res;

				::booldog::utils::io::path::mbs::filename_without_extension( &res , resmbchar.mbchar , resmbchar.mblen );

				REQUIRE( res.succeeded() );
#ifdef __WINDOWS__
				REQUIRE(resmbchar.mblen == 8);

				REQUIRE( strcmp( resmbchar.mbchar , "language" ) == 0 );
#else
				REQUIRE( resmbchar.mblen == 11 );

				REQUIRE( strcmp( resmbchar.mbchar , "liblanguage" ) == 0 );
#endif
			}
		}

		{
			::booldog::result_wchar reswchar( &allocator );
			::booldog::utils::module::wcs::pathname_from_address< 4 >( &reswchar , &allocator , respointer.pres , debuginfo_macros );

			REQUIRE( reswchar.succeeded() );

			{
				::booldog::result res;

				::booldog::utils::io::path::wcs::filename_without_extension( &res , reswchar.wchar , reswchar.wlen );

				REQUIRE( res.succeeded() );
#ifdef __WINDOWS__
				REQUIRE(reswchar.wlen == 8);

				REQUIRE( wcscmp( reswchar.wchar , L"language" ) == 0 );
#else
				REQUIRE( reswchar.wlen == 11 );

				REQUIRE( wcscmp( reswchar.wchar , L"liblanguage" ) == 0 );
#endif
			}
		}
		

		loader.unload( &resres , module2 , 0 , 0 );

		REQUIRE( resres.succeeded() );


		loader.unload( &resres , module0 , 0 , 0 );

		REQUIRE( resres.succeeded() );
	}

	REQUIRE( allocator.begin() == begin );

	REQUIRE(allocator.available() == total);
};
//class boo_io_fileTest : public ::testing::Test 
//{
//};
TEST_CASE("boo_io_fileTest", "test")
{
	::booldog::allocators::easy::heap heap;
	::booldog::allocators::mixed< 16 * 1024 > allocator( &heap );
	
	size_t total = allocator.stack.available();

	char* begin = (char*)allocator.stack.begin();
	{
		::booldog::result_buffer resbuf00( &allocator );
		::booldog::result_file res;

		booldog::param search_paths_params[] =
		{
			BOOPARAM_PCHAR( "../../test_data\\modules0/x86" ) ,
			BOOPARAM_PWCHAR( L"..\\../test_data\\modules1\\x86" ) ,
			BOOPARAM_PCHAR( "../../test_data\\json" ) ,
			BOOPARAM_PCHAR( "../../test_data" ) ,
			BOOPARAM_NONE
		};
		booldog::named_param load_params[] =
		{
			BOONAMED_PARAM_PPARAM( "search_paths" , search_paths_params ) ,
			BOONAMED_PARAM_BOOL( "exedir_as_root_path" , true ) ,
			BOONAMED_PARAM_PCHAR("root_path", 0),
			BOONAMED_PARAM_PWCHAR("root_path", 0),
			BOONAMED_PARAM_NONE
		};
		::booldog::io::file::mbsopen( &res , &allocator , "core1" , ::booldog::enums::io::file_mode_read , load_params );

		REQUIRE_FALSE( res.succeeded() );

		::booldog::io::file::mbsopen( &res , &allocator , "core.dll" , ::booldog::enums::io::file_mode_read , load_params );
		
		REQUIRE( res.succeeded() );

		res.file->close( &res );

		REQUIRE( res.succeeded() );


		::booldog::io::file::mbsopen( &res , &allocator , "json_test2.txt" , ::booldog::enums::io::file_mode_read , load_params );
		
		REQUIRE( res.succeeded() );

		res.file->readall< 16 * 1024 >( &resbuf00 , &allocator , debuginfo_macros );

		REQUIRE( resbuf00.succeeded() );

		REQUIRE( resbuf00.buf[ 0 ] == '[' );

		res.file->close( &res );

		REQUIRE( res.succeeded() );


		::booldog::io::file::mbsopen( &res , &allocator , "maps" , ::booldog::enums::io::file_mode_read , load_params );
		
		REQUIRE( res.succeeded() );

		res.file->readline< 64 >( &resbuf00 , resbuf00.allocator , debuginfo_macros );

		REQUIRE( resbuf00.succeeded() );

		REQUIRE( strcmp( (char*)resbuf00.buf , "00400000-004c1000 r-xp 00000000 08:06 22283081                           "
			"/home/test1/video-server-7.0/video-server-7.0" ) == 0 );

		res.file->readline< 64 >( &resbuf00 , resbuf00.allocator , debuginfo_macros );

		REQUIRE( resbuf00.succeeded() );

		REQUIRE( strcmp( (char*)resbuf00.buf , "006c0000-006c6000 rw-p 000c0000 08:06 22283081                           "
			"/home/test1/video-server-7.0/video-server-7.0" ) == 0 );

		res.file->readline< 64 >( &resbuf00 , resbuf00.allocator , debuginfo_macros );

		REQUIRE( resbuf00.succeeded() );

		REQUIRE( strcmp( (char*)resbuf00.buf , "014a9000-1a803000 rw-p 00000000 00:00 0                                  "
			"[heap]" ) == 0 );

		res.file->readline< 64 >( &resbuf00 , resbuf00.allocator , debuginfo_macros );

		REQUIRE( resbuf00.succeeded() );

		REQUIRE( strcmp( (char*)resbuf00.buf , "7f6dcc000000-7f6dcdea8000 rw-p 00000000 00:00 0 " ) == 0 );
				
		res.file->close( &res );

		REQUIRE( res.succeeded() );

		{
			::booldog::result_buffer resbuf1( &allocator );

			::booldog::io::file::mbsopen( &res , &allocator , "maps" , ::booldog::enums::io::file_mode_read , load_params );
		
			REQUIRE( res.succeeded() );

			res.file->readline< 64 >( &resbuf1 , resbuf1.allocator , debuginfo_macros );

			REQUIRE( resbuf1.succeeded() );

			REQUIRE( strcmp( (char*)resbuf1.buf , "00400000-004c1000 r-xp 00000000 08:06 22283081                           "
				"/home/test1/video-server-7.0/video-server-7.0" ) == 0 );

			res.file->readline< 64 >( &resbuf1 , resbuf1.allocator , debuginfo_macros );

			REQUIRE( resbuf1.succeeded() );

			REQUIRE( strcmp( (char*)resbuf1.buf , "006c0000-006c6000 rw-p 000c0000 08:06 22283081                           "
				"/home/test1/video-server-7.0/video-server-7.0" ) == 0 );

			res.file->readline< 64 >( &resbuf1 , resbuf1.allocator , debuginfo_macros );

			REQUIRE( resbuf1.succeeded() );

			REQUIRE( strcmp( (char*)resbuf1.buf , "014a9000-1a803000 rw-p 00000000 00:00 0                                  "
				"[heap]" ) == 0 );

			res.file->readline< 64 >( &resbuf1 , resbuf1.allocator , debuginfo_macros );

			REQUIRE( resbuf1.succeeded() );

			REQUIRE( strcmp( (char*)resbuf1.buf , "7f6dcc000000-7f6dcdea8000 rw-p 00000000 00:00 0 " ) == 0 );
				
			res.file->close( &res );

			REQUIRE( res.succeeded() );
		}
	}

	REQUIRE( allocator.stack.begin() == begin );

	REQUIRE( allocator.stack.available() == total );

	REQUIRE( allocator.holder.heap->size_of_allocated_memory() == 0 );
};
//#ifdef __LINUX__
//#include <locale.h>
//#include <langinfo.h>
//#endif
//int main( int argc , char **argv )
//{
//#ifdef __LINUX__
//	/*char* encoding = nl_langinfo(CODESET);
//    printf("Encoding is %s\n", encoding);
//
//	setlocale(LC_ALL, "");
//    char* locstr = setlocale(LC_CTYPE, NULL);
//    encoding = nl_langinfo(CODESET);
//    printf("Locale is %s\n", locstr);
//    printf("Encoding is %s\n", encoding);*/
//#endif
//    ::testing::InitGoogleTest( &argc , argv );
//    return RUN_ALL_TESTS();
//};