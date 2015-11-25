#include <gtest/gtest.h>

#ifdef __WINDOWS__
#ifdef __x86__
#include <yajl/yajl_parse.h>
#include <yajl/yajl_gen.h>
#define USE_YAJL 1
static int reformat_null(void * ctx)  
{  
    yajl_gen g = (yajl_gen) ctx;  
    return yajl_gen_status_ok == yajl_gen_null(g);  
}  
  
static int reformat_boolean(void * ctx, int boolean)  
{  
    yajl_gen g = (yajl_gen) ctx;  
    return yajl_gen_status_ok == yajl_gen_bool(g, boolean);  
}  
  
static int reformat_number(void * ctx, const char * s, size_t l)  
{  
    yajl_gen g = (yajl_gen) ctx;  
    return yajl_gen_status_ok == yajl_gen_number(g, s, l);  
}  
  
static int reformat_string(void * ctx, const unsigned char * stringVal,  
                           size_t stringLen)  
{  
    yajl_gen g = (yajl_gen) ctx;  
    return yajl_gen_status_ok == yajl_gen_string(g, stringVal, stringLen);  
}  
  
static int reformat_map_key(void * ctx, const unsigned char * stringVal,  
                            size_t stringLen)  
{  
    yajl_gen g = (yajl_gen) ctx;  
    return yajl_gen_status_ok == yajl_gen_string(g, stringVal, stringLen);  
}  
  
static int reformat_start_map(void * ctx)  
{  
    yajl_gen g = (yajl_gen) ctx;  
    return yajl_gen_status_ok == yajl_gen_map_open(g);  
}  
  
  
static int reformat_end_map(void * ctx)  
{  
    yajl_gen g = (yajl_gen) ctx;  
    return yajl_gen_status_ok == yajl_gen_map_close(g);  
}  
  
static int reformat_start_array(void * ctx)  
{  
    yajl_gen g = (yajl_gen) ctx;  
    return yajl_gen_status_ok == yajl_gen_array_open(g);  
}  
  
static int reformat_end_array(void * ctx)  
{  
    yajl_gen g = (yajl_gen) ctx;  
    return yajl_gen_status_ok == yajl_gen_array_close(g);  
}  
  
static yajl_callbacks callbacks = {  
    reformat_null,  
    reformat_boolean,  
    NULL,  
    NULL,  
    reformat_number,  
    reformat_string,  
    reformat_start_map,  
    reformat_map_key,  
    reformat_end_map,  
    reformat_start_array,  
    reformat_end_array  
};  
#endif
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
#include <boo_object.h>
#include <boo_if.h>
#include <boo_check.h>
#include <boo_string.h>
#include <boo_list.h>
#include <boo_stack.h>
#include <boo_mem.h>
#include <boo_base_loader.h>
#include <boo_module_utils.h>
#include <boo_io_utils.h>
#include <boo_array.h>
#include <boo_param.h>
#include <boo_string_utils.h>
#include <boo_error_format.h>
class boo_paramTest : public ::testing::Test 
{
};
TEST_F( boo_paramTest , test )
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

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_int32 );

	ASSERT_EQ( p0[ index ].int32value , -32 );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_bool );

	ASSERT_EQ( p0[ index ].boolvalue , false );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_char );

	ASSERT_EQ( p0[ index ].charvalue , -127 );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_uchar );

	ASSERT_EQ( p0[ index ].ucharvalue , 128 );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_short );

	ASSERT_EQ( p0[ index ].shortvalue , -1986 );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_ushort );

	ASSERT_EQ( p0[ index ].ushortvalue , 1986 );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_int64 );

	ASSERT_EQ( p0[ index ].int64value , -123456789 );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_uint64 );

	ASSERT_EQ( p0[ index ].uint64value , 123456789 );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_wchar );

	ASSERT_EQ( p0[ index ].wcharvalue , L'W' );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_pchar );

	ASSERT_EQ( strcmp( p0[ index ].pcharvalue , "hello" ) , 0 );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_pwchar );

	ASSERT_EQ( wcscmp( p0[ index ].pwcharvalue , L"hello" ) , 0 );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_pvoid );

	ASSERT_EQ( p0[ index ].pvoidvalue , &p0 );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_pparam );

	ASSERT_EQ( p0[ index ].pparamvalue , p0 );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_pint32 );

	ASSERT_EQ( p0[ index ].pint32value , &int32value );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_puint32 );

	ASSERT_EQ( p0[ index ].puint32value , &uint32value );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_pbool );

	ASSERT_EQ( p0[ index ].pboolvalue , &boolvalue );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_puchar );

	ASSERT_EQ( p0[ index ].pucharvalue , &ucharvalue );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_pshort );

	ASSERT_EQ( p0[ index ].pshortvalue , &shortvalue );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_pushort );

	ASSERT_EQ( p0[ index ].pushortvalue , &ushortvalue );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_pint64 );

	ASSERT_EQ( p0[ index ].pint64value , &int64value );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_puint64 );

	ASSERT_EQ( p0[ index ].puint64value , &uint64value );

	index++;

	ASSERT_EQ( p0[ index ].type , ::booldog::enums::param::type_none );


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

	ASSERT_EQ( strcmp( p1[ index ].name , "test0" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_int32 );

	ASSERT_EQ( p1[ index ].param.int32value , -32 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test1" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_bool );

	ASSERT_EQ( p1[ index ].param.boolvalue , false );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test2" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_char );

	ASSERT_EQ( p1[ index ].param.charvalue , -127 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test3" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_uchar );

	ASSERT_EQ( p1[ index ].param.ucharvalue , 128 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test4" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_short );

	ASSERT_EQ( p1[ index ].param.shortvalue , -1986 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test5" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_ushort );

	ASSERT_EQ( p1[ index ].param.ushortvalue , 1986 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test6" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_int64 );

	ASSERT_EQ( p1[ index ].param.int64value , -123456789 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test7" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_uint64 );

	ASSERT_EQ( p1[ index ].param.uint64value , 123456789 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test8" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_wchar );

	ASSERT_EQ( p1[ index ].param.wcharvalue , L'W' );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test9" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_pchar );

	ASSERT_EQ( strcmp( p1[ index ].param.pcharvalue , "hello" ) , 0 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test10" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_pwchar );

	ASSERT_EQ( wcscmp( p1[ index ].param.pwcharvalue , L"hello" ) , 0 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test11" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_pvoid );

	ASSERT_EQ( p1[ index ].param.pvoidvalue , &p0 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test12" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_pnamed_param );

	ASSERT_EQ( p1[ index ].param.pnamed_paramvalue , p1 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test13" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_pparam );

	ASSERT_EQ( p1[ index ].param.pparamvalue , p0 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test14" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_pint32 );

	ASSERT_EQ( p1[ index ].param.pint32value , &int32value );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test15" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_puint32 );

	ASSERT_EQ( p1[ index ].param.puint32value , &uint32value );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test16" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_pbool );

	ASSERT_EQ( p1[ index ].param.pboolvalue , &boolvalue );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test17" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_puchar );

	ASSERT_EQ( p1[ index ].param.pucharvalue , &ucharvalue );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test18" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_pshort );

	ASSERT_EQ( p1[ index ].param.pshortvalue , &shortvalue );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test19" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_pushort );

	ASSERT_EQ( p1[ index ].param.pushortvalue , &ushortvalue );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test20" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_pint64 );

	ASSERT_EQ( p1[ index ].param.pint64value , &int64value );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test21" ) , 0 );

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_puint64 );

	ASSERT_EQ( p1[ index ].param.puint64value , &uint64value );

	index++;

	ASSERT_EQ( p1[ index ].param.type , ::booldog::enums::param::type_none );


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

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_not_found );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test0" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_int32 );

	ASSERT_EQ( p2[ index ].param.int32value , -32 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test1" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_bool );

	ASSERT_EQ( p2[ index ].param.boolvalue , false );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test2" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_char );

	ASSERT_EQ( p2[ index ].param.charvalue , -127 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test3" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_uchar );

	ASSERT_EQ( p2[ index ].param.ucharvalue , 128 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test4" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_short );

	ASSERT_EQ( p2[ index ].param.shortvalue , -1986 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test5" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_ushort );

	ASSERT_EQ( p2[ index ].param.ushortvalue , 1986 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test6" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_int64 );

	ASSERT_EQ( p2[ index ].param.int64value , -123456789 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test7" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_uint64 );

	ASSERT_EQ( p2[ index ].param.uint64value , 123456789 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test8" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_wchar );

	ASSERT_EQ( p2[ index ].param.wcharvalue , L'W' );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test9" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_pchar );

	ASSERT_EQ( strcmp( p2[ index ].param.pcharvalue , "hello" ) , 0 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test10" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_pwchar );

	ASSERT_EQ( wcscmp( p2[ index ].param.pwcharvalue , L"hello" ) , 0 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test11" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_pvoid );

	ASSERT_EQ( p2[ index ].param.pvoidvalue , &p0 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test12" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_pnamed_param );

	ASSERT_EQ( p2[ index ].param.pnamed_paramvalue , p1 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test13" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_pparam );

	ASSERT_EQ( p2[ index ].param.pparamvalue , p0 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test14" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_pint32 );

	ASSERT_EQ( p2[ index ].param.pint32value , &int32value );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test15" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_puint32 );

	ASSERT_EQ( p2[ index ].param.puint32value , &uint32value );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test16" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_pbool );

	ASSERT_EQ( p2[ index ].param.pboolvalue , &boolvalue );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test17" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_puchar );

	ASSERT_EQ( p2[ index ].param.pucharvalue , &ucharvalue );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test18" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_pshort );

	ASSERT_EQ( p2[ index ].param.pshortvalue , &shortvalue );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test19" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_pushort );

	ASSERT_EQ( p2[ index ].param.pushortvalue , &ushortvalue );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test20" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_pint64 );

	ASSERT_EQ( p2[ index ].param.pint64value , &int64value );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test21" ) , 0 );

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_puint64 );

	ASSERT_EQ( p2[ index ].param.puint64value , &uint64value );

	index++;

	ASSERT_EQ( p2[ index ].param.type , ::booldog::enums::param::type_none );

};

#define boo_stackTestAllocatorSize 64
class boo_stackTest : public ::testing::Test 
{
};
TEST_F( boo_stackTest , test )
{
	::booldog::allocators::stack::simple< boo_stackTestAllocatorSize > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	void* ptr0 = allocator.alloc( boo_stackTestAllocatorSize );

	size_t ptr0_mswi = ::booldog::mem::info::memory_size_with_info( boo_stackTestAllocatorSize );
	size_t ptr0_mis = ::booldog::mem::info::memory_info_size( boo_stackTestAllocatorSize );

	ASSERT_TRUE( allocator.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr0 == ( begin + ptr0_mis ) );

	ASSERT_EQ( allocator.available() , total - ptr0_mswi );

	size_t ptr1_mswi = ::booldog::mem::info::memory_size_with_info( 17 );
	size_t ptr1_mis = ::booldog::mem::info::memory_info_size( 17 );

	void* ptr1 = allocator.alloc( 17 );

	ASSERT_TRUE( allocator.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr1 == 0 );

	ASSERT_EQ( allocator.available() , total - ptr0_mswi );

	allocator.free( ptr0 );

	ASSERT_TRUE( allocator.begin() == begin );

	ASSERT_EQ( allocator.available() , total );

	ptr0 = allocator.alloc( 23 );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 23 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 23 );

	ASSERT_TRUE( allocator.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr0 == begin + ptr0_mis );

	ASSERT_EQ( allocator.available() , total - ptr0_mswi );

	ptr1 = allocator.alloc( 17 );

	ptr1_mswi = ::booldog::mem::info::memory_size_with_info( 17 );
	ptr1_mis = ::booldog::mem::info::memory_info_size( 17 );

	ASSERT_TRUE( allocator.begin() == begin + ptr0_mswi + ptr1_mswi );

	ASSERT_TRUE( ptr1 == begin + ptr0_mswi + ptr1_mis );

	ASSERT_EQ( allocator.available() , total - ptr0_mswi - ptr1_mswi );

	allocator.free( ptr0 );

	ASSERT_TRUE( allocator.begin() == begin );

	ASSERT_EQ( allocator.available() , total - ptr1_mswi );

	allocator.free( ptr1 );

	ptr1 = 0;

	ASSERT_TRUE( allocator.begin() == begin );

	ASSERT_EQ( allocator.available() , total );

	ptr0 = allocator.alloc( 45 );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 45 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 45 );

	ASSERT_TRUE( allocator.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr0 == begin + ptr0_mis );

	ASSERT_EQ( allocator.available() , total - ptr0_mswi );

	allocator.free( ptr0 );

	ASSERT_TRUE( allocator.begin() == begin );

	ASSERT_EQ( allocator.available() , total );


	ptr0 = 0;

	ptr0 = allocator.realloc( ptr0 , 45 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 45 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 45 );

	ASSERT_TRUE( allocator.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr0 == begin + ptr0_mis );

	ASSERT_EQ( allocator.available() , total - ptr0_mswi );

	ptr0 = allocator.realloc( ptr0 , 45 );

	ASSERT_TRUE( allocator.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr0 == begin + ptr0_mis );

	ASSERT_EQ( allocator.available() , total - ptr0_mswi );

	ptr0 = allocator.realloc( ptr0 , 50 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 50 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 50 );

	ASSERT_TRUE( allocator.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr0 == begin + ptr0_mis );

	ASSERT_EQ( allocator.available() , total - ptr0_mswi );

	ptr0 = allocator.realloc( ptr0 , 45 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 45 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 45 );

	ASSERT_TRUE( allocator.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr0 == ( begin + ptr0_mis ) );

	ASSERT_EQ( allocator.available() , total - ptr0_mswi );

	allocator.free( ptr0 );

	ptr0 = 0;

	ASSERT_TRUE( allocator.begin() == begin );

	ASSERT_EQ( allocator.available() , total );


	ptr0 = allocator.realloc_array< wchar_t >( (wchar_t*)ptr0 , 11 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 11 * sizeof( wchar_t ) );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 11 * sizeof( wchar_t ) );

	ASSERT_TRUE( allocator.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr0 == ( begin + ptr0_mis ) );

	ASSERT_EQ( allocator.available() , total - ptr0_mswi );

	allocator.free( ptr0 );

	ptr0 = 0;

	ASSERT_TRUE( allocator.begin() == begin );

	ASSERT_EQ( allocator.available() , total );





	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 6 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 8 * 4 );

		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
	}


	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 6 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 8 );

		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
	}


	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 7 * 4 );
		
		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
	}

	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 * 4 );
		
		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
	}

	{
		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 3 * 4 );		

		allocator.free( ptr1 );

		ptr1 = 0;

		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
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

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
	}



	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 7 );

		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
	}

	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 );

		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
	}

	{
		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 3 );

		allocator.free( ptr1 );

		ptr1 = 0;

		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
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

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
	}

	ASSERT_TRUE( allocator.begin() == begin );
		
	ASSERT_EQ( allocator.available() , total );
};

class boo_memTest : public ::testing::Test 
{
};
TEST_F( boo_memTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	booldog::_allocator = &allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	size_t dstsize = 0;
	size_t dst_allocsize = 8;
	char* dst = (char*)allocator.alloc( dst_allocsize );

	ASSERT_TRUE( ::booldog::mem::insert< char >( 0 , dst , dstsize , dst_allocsize , 0 , "Test" , 5 ) );

	dstsize = 4;

	ASSERT_TRUE( ::memcmp( "Test" , dst , dstsize ) == 0 );

	ASSERT_TRUE( ::booldog::mem::insert< char >( 1 , dst , dstsize , dst_allocsize , 0 , "r" , 1 ) );

	dstsize = 5;

	ASSERT_TRUE( ::memcmp( "Trest" , dst , dstsize ) == 0 );

	ASSERT_TRUE( ::booldog::mem::insert< char >( 8 , dst , dstsize , dst_allocsize , 0 , "#7" , 2 ) );

	dstsize = 7;

	ASSERT_TRUE( ::memcmp( "Trest#7" , dst , dstsize ) == 0 );

	ASSERT_TRUE( ::booldog::mem::insert< char >( 2 , dst , dstsize , dst_allocsize , 2 , "om" , 2 ) );

	dstsize = 7;

	ASSERT_TRUE( ::memcmp( "Tromt#7" , dst , dstsize ) == 0 );

	ASSERT_TRUE( ::booldog::mem::insert< char >( 2 , dst , dstsize , dst_allocsize , 2 , "usd" , 3 ) );

	dstsize = 8;

	ASSERT_TRUE( ::memcmp( "Trusdt#7" , dst , dstsize ) == 0 );

	ASSERT_TRUE( ::booldog::mem::insert< char >( 2 , dst , dstsize , dst_allocsize , 3 , "es" , 2 ) );

	dstsize = 7;

	ASSERT_TRUE( ::memcmp( "Trest#7" , dst , dstsize ) == 0 );

	ASSERT_TRUE( ::booldog::mem::insert< char >( 5 , dst , dstsize , dst_allocsize , 4 , "e" , 1 ) );

	dstsize = 6;

	ASSERT_TRUE( ::memcmp( "Treste" , dst , dstsize ) == 0 );

	ASSERT_FALSE( ::booldog::mem::insert< char >( 5 , dst , dstsize , dst_allocsize , 2 , "TEST00000" , 9 ) );

	dstsize = 6;

	ASSERT_TRUE( ::memcmp( "Treste" , dst , dstsize ) == 0 );

	::booldog::mem::remove< char >( 1 , dst , dstsize , 2 );

	dstsize = 4;

	ASSERT_TRUE( ::memcmp( "Tste" , dst , dstsize ) == 0 );

	::booldog::mem::remove< char >( 2 , dst , dstsize , 2 );

	dstsize = 2;

	ASSERT_TRUE( ::memcmp( "Ts" , dst , dstsize ) == 0 );


	::booldog::mem::remove< char >( 1 , dst , dstsize , 3 );

	dstsize = 1;

	ASSERT_TRUE( ::memcmp( "T" , dst , dstsize ) == 0 );


	ASSERT_TRUE( ::booldog::mem::insert< char >( 1 , dst , dstsize , dst_allocsize , 0 , "est0" , 4 ) );

	dstsize = 5;

	ASSERT_TRUE( ::memcmp( "Test0" , dst , dstsize ) == 0 );


	ASSERT_TRUE( ::booldog::mem::expand< char >( 1 , dst , dstsize , dst_allocsize , 2 ) );

	dstsize = 7;

	ASSERT_TRUE( ::memcmp( "Tesest0" , dst , dstsize ) == 0 );

	ASSERT_FALSE( ::booldog::mem::expand< char >( 1 , dst , dstsize , dst_allocsize , 2 ) );

	dstsize = 7;

	ASSERT_TRUE( ::memcmp( "Tesest0" , dst , dstsize ) == 0 );


	allocator.free( dst );

	ASSERT_TRUE( allocator.begin() == begin );
		
	ASSERT_EQ( allocator.available() , total );
};

class boo_stringTest : public ::testing::Test 
{
};
TEST_F( boo_stringTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	::booldog::_allocator = &allocator;
#ifdef BOOLDOG_STRING_TEST
	for( ::booldog::string_step = 1 ; ::booldog::string_step < 25 ; ::booldog::string_step++ )
	{

#endif
		{
			::booldog::string string( (const char*)0 );

			ASSERT_TRUE( strcmp( string.str() , "" ) == 0 );

			ASSERT_EQ( string.length() , 0 );

			ASSERT_EQ( string.bytes() , 1 );
		}

		{
			::booldog::string string( "" );

			ASSERT_TRUE( strcmp( string.str() , "" ) == 0 );

			ASSERT_EQ( string.length() , 0 );

			ASSERT_EQ( string.bytes() , 1 );
		}

		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );
		}

		{
			::booldog::string string( "TEST" , 0 , 4 );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );
		}

		{
			::booldog::string string( "Hello, TEST" , 7 );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );
		}

		{
			::booldog::string string( "Hello, TEST, it's our first meeting" , 7 , 4 );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );
		}

		{
			::booldog::string string( cp1251_April_var , 3 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_il_var ) == 0 );

			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , 6 , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , 3 , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_Apr_var ) == 0 );

			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );
		}


		{
			::booldog::string string( utf16_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF16 );
		
			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );		
		}

		{
			::booldog::string string( utf16_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF16 );
		
			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );

			ASSERT_TRUE( strcmp( string.str() , utf8_il_var ) == 0 );		
		}

		{
			::booldog::string string( utf16_April_var , 0 , 12 , ::booldog::enums::string::UTF16 );
		
			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );		
		}

		{
			::booldog::string string( utf16_April_var , 0 , 6 , ::booldog::enums::string::UTF16 );
		
			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Apr_var ) == 0 );
		}


		{
			::booldog::string string( utf32_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF32 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );
		}

		{
			::booldog::string string( utf32_April_var , 12 , SIZE_MAX , ::booldog::enums::string::UTF32 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_il_var ) == 0 );

			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );
		}

		{
			::booldog::string string( utf32_April_var , 0 , 24 , ::booldog::enums::string::UTF32 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );
		}

		{
			::booldog::string string( utf32_April_var , 0 , 12 , ::booldog::enums::string::UTF32 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_Apr_var ) == 0 );

			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );
		}

		const wchar_t* wchar_test = 0;
		if( ::booldog::compile::If< sizeof( wchar_t ) == 2 >::test() )
			wchar_test = (wchar_t*)utf16_April_var;
		else if( ::booldog::compile::If< sizeof( wchar_t ) == 4 >::test() )
			wchar_test = (wchar_t*)utf32_April_var;
		{
			::booldog::string string( wchar_test , 0 , SIZE_MAX );
		
			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );		
		}

		{
			::booldog::string string( wchar_test , 3 , SIZE_MAX );
		
			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );

			ASSERT_TRUE( strcmp( string.str() , utf8_il_var ) == 0 );		
		}

		{
			::booldog::string string( wchar_test , 0 , 6 );
		
			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );		
		}

		{
			::booldog::string string( wchar_test , 0 , 3 );
		
			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Apr_var ) == 0 );
		}



		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApril_var ) == 0 );

			ASSERT_EQ( string.length() , 10 );

			ASSERT_EQ( string.bytes() , 17 );
		}

		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf8_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApril_var ) == 0 );

			ASSERT_EQ( string.length() , 10 );

			ASSERT_EQ( string.bytes() , 17 );
		}

		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf16_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF16 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApril_var ) == 0 );

			ASSERT_EQ( string.length() , 10 );

			ASSERT_EQ( string.bytes() , 17 );
		}

		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf32_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF32 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApril_var ) == 0 );

			ASSERT_EQ( string.length() , 10 );

			ASSERT_EQ( string.bytes() , 17 );
		}


		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( cp1251_April_var , 3 , SIZE_MAX , ::booldog::enums::string::CP1251 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTil_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}

		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf8_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF8 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTil_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}

		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf16_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF16 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTil_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}

		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf32_April_var , 12 , SIZE_MAX , ::booldog::enums::string::UTF32 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTil_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}


		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( cp1251_April_var , 0 , 3 , ::booldog::enums::string::CP1251 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApr_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}

		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf8_April_var , 0 , 6 , ::booldog::enums::string::UTF8 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApr_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}

		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf16_April_var , 0 , 6 , ::booldog::enums::string::UTF16 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApr_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}

		{
			::booldog::string string( "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf32_April_var , 0 , 12 , ::booldog::enums::string::UTF32 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApr_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}



		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , cp1251_il_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf16_il_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF16 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf32_il_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF32 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf8_il_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}


		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , cp1251_April_var , 3 , SIZE_MAX , ::booldog::enums::string::CP1251 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf16_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF16 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf32_April_var , 12 , SIZE_MAX , ::booldog::enums::string::UTF32 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf8_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF8 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}


		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , cp1251_April_var , 3 , 3 , ::booldog::enums::string::CP1251 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf16_April_var , 6 , 6 , ::booldog::enums::string::UTF16 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf32_April_var , 12 , 12 , ::booldog::enums::string::UTF32 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf8_April_var , 6 , 6 , ::booldog::enums::string::UTF8 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}



		if( ::booldog::compile::If< sizeof( wchar_t ) == 2 >::test() )
			wchar_test = (wchar_t*)utf16_il_var;
		else if( ::booldog::compile::If< sizeof( wchar_t ) == 4 >::test() )
			wchar_test = (wchar_t*)utf32_il_var;
		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , wchar_test , 0 , SIZE_MAX );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		if( ::booldog::compile::If< sizeof( wchar_t ) == 2 >::test() )
			wchar_test = (wchar_t*)utf16_April_var;
		else if( ::booldog::compile::If< sizeof( wchar_t ) == 4 >::test() )
			wchar_test = (wchar_t*)utf32_April_var;
		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , wchar_test , 3 , SIZE_MAX );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , wchar_test , 3 , 3 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}



		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_il_var , cp1251_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_il_var , utf16_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_il_var , utf32_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_il_var , utf8_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_il_var , cp1251_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_il_var , utf16_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_il_var , utf32_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_il_var , utf8_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_il_var , cp1251_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_il_var , utf16_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_il_var , utf32_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_il_var , utf8_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_il_var , cp1251_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_il_var , utf16_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_il_var , utf32_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_il_var , utf8_April_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}


		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_April_var , cp1251_April_var , SIZE_MAX , 3 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_April_var , utf16_April_var , SIZE_MAX , 3 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_April_var , utf32_April_var , SIZE_MAX , 3 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_April_var , utf8_April_var , SIZE_MAX , 3 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_April_var , cp1251_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_April_var , utf16_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_April_var , utf32_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_April_var , utf8_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_April_var , cp1251_April_var , SIZE_MAX , 12 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_April_var , utf16_April_var , SIZE_MAX , 12 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_April_var , utf32_April_var , SIZE_MAX , 12 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_April_var , utf8_April_var , SIZE_MAX , 12 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_April_var , cp1251_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_April_var , utf16_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_April_var , utf32_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_April_var , utf8_April_var , SIZE_MAX , 6 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}


		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_April_var , cp1251_April_var , SIZE_MAX , 3 , 3 , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_April_var , utf16_April_var , SIZE_MAX , 3 , 3 , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_April_var , utf32_April_var , SIZE_MAX , 3 , 3 , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_April_var , utf8_April_var , SIZE_MAX , 3 , 3 , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_April_var , cp1251_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_April_var , utf16_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_April_var , utf32_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_April_var , utf8_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_April_var , cp1251_April_var , SIZE_MAX , 12 , 12 , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_April_var , utf16_April_var , SIZE_MAX , 12 , 12 , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_April_var , utf32_April_var , SIZE_MAX , 12 , 12 , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_April_var , utf8_April_var , SIZE_MAX , 12 , 12 , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_April_var , cp1251_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_April_var , utf16_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_April_var , utf32_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_April_var , utf8_April_var , SIZE_MAX , 6 , 6 , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprAprilAprAprilAprApril_var ) == 0 );

			ASSERT_EQ( string.length() , 27 );

			ASSERT_EQ( string.bytes() , 55 );
		}


		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_April_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_April_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_April_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_April_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_April_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_April_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_April_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_April_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_April_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_April_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_April_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_April_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_April_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_April_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_April_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_April_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ililil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}


		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_Apr_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_Apr_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_Apr_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , cp1251_Apr_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_Apr_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_Apr_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_Apr_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf8_Apr_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_Apr_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_Apr_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_Apr_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf16_Apr_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_Apr_var , cp1251_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_Apr_var , utf8_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_Apr_var , utf16_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 0 , utf32_Apr_var , utf32_il_var , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_ilililililil_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );
		}


		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 3 , utf32_April_var , 0 , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 3 , utf16_April_var , 0 , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 3 , utf8_April_var , 0 , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 3 , cp1251_April_var , 0 , SIZE_MAX , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 3 , utf32_April_var , 0 , 1 , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 12 );

			ASSERT_EQ( string.bytes() , 25 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 3 , utf16_April_var , 0 , 1 , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF16
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 12 );

			ASSERT_EQ( string.bytes() , 25 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 3 , utf8_April_var , 0 , 1 , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF8
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 12 );

			ASSERT_EQ( string.bytes() , 25 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			string.replace( 3 , cp1251_April_var , 0 , 1 , 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::CP1251
				, 0 , SIZE_MAX , SIZE_MAX , ::booldog::enums::string::UTF32 , true , true );

			ASSERT_TRUE( strcmp( string.str() , utf8_AprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 12 );

			ASSERT_EQ( string.bytes() , 25 );
		}

		{
			::booldog::string string( utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			::booldog::string res;
			res = string.substring( 12 );

			ASSERT_TRUE( strcmp( res.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( res.length() , 6 );

			ASSERT_EQ( res.bytes() , 13 );
		}

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
	}

	ASSERT_TRUE( allocator.begin() == begin );
		
	ASSERT_EQ( allocator.available() , total );
};

class boo_string_utilsTest : public ::testing::Test 
{
};
TEST_F( boo_string_utilsTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	booldog::_allocator = &allocator;

	{
		::booldog::result_bool resbool;

		wchar_t* wcsdst = 0;
		size_t wcsdstlen = 0;
		size_t wcsdstsize = 0;

		::booldog::utils::string::wcs::insert( &resbool , SIZE_MAX , wcsdst , wcsdstlen , wcsdstsize , 0 );

		ASSERT_FALSE( resbool.succeeded() );

		ASSERT_EQ( resbool.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resbool.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::wcs::insert( &resbool , SIZE_MAX , wcsdst , wcsdstlen , wcsdstsize , L"" );

		ASSERT_FALSE( resbool.succeeded() );

		ASSERT_EQ( resbool.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resbool.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::wcs::insert( &resbool , SIZE_MAX , wcsdst , wcsdstlen , wcsdstsize , L"lib" , 3 );

		ASSERT_FALSE( resbool.succeeded() );

		ASSERT_EQ( resbool.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resbool.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::wcs::insert( &resbool , SIZE_MAX , wcsdst , wcsdstlen , wcsdstsize , L"lib" );

		ASSERT_TRUE( resbool.succeeded() );

		ASSERT_EQ( wcsdstlen , 3 );

		ASSERT_EQ( wcsdstsize , 4 * sizeof( wchar_t ) );

		ASSERT_TRUE( wcscmp( wcsdst , L"lib" ) == 0 );


		::booldog::utils::string::wcs::insert( &resbool , 3 , wcsdst , wcsdstlen , wcsdstsize , L"re" );

		ASSERT_TRUE( resbool.succeeded() );

		ASSERT_EQ( wcsdstlen , 5 );

		ASSERT_EQ( wcsdstsize , 6 * sizeof( wchar_t ) );

		ASSERT_TRUE( wcscmp( wcsdst , L"libre" ) == 0 );


		::booldog::utils::string::wcs::insert( &resbool , 3 , wcsdst , wcsdstlen , wcsdstsize , L"libcore.so" , 3 , 2 );

		ASSERT_TRUE( resbool.succeeded() );

		ASSERT_EQ( wcsdstlen , 7 );

		ASSERT_EQ( wcsdstsize , 8 * sizeof( wchar_t ) );

		ASSERT_TRUE( wcscmp( wcsdst , L"libcore" ) == 0 );

		allocator.free( wcsdst );

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
	}


	{
		::booldog::result res;

		char* mbsdst = 0;
		size_t mbsdstlen = 0;
		size_t mbsdstsize = 0;

		::booldog::utils::string::mbs::insert( &res , SIZE_MAX , mbsdst , mbsdstlen , mbsdstsize , 0 );

		ASSERT_FALSE( res.succeeded() );

		ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::mbs::insert( &res , SIZE_MAX , mbsdst , mbsdstlen , mbsdstsize , "" );

		ASSERT_FALSE( res.succeeded() );

		ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::mbs::insert( &res , SIZE_MAX , mbsdst , mbsdstlen , mbsdstsize , "lib" , 3 );

		ASSERT_FALSE( res.succeeded() );

		ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::mbs::insert( &res , SIZE_MAX , mbsdst , mbsdstlen , mbsdstsize , "lib" );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( mbsdstlen , 3 );

		ASSERT_EQ( mbsdstsize , 4 );

		ASSERT_TRUE( strcmp( mbsdst , "lib" ) == 0 );


		::booldog::utils::string::mbs::insert( &res , 3 , mbsdst , mbsdstlen , mbsdstsize , "re" );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( mbsdstlen , 5 );

		ASSERT_EQ( mbsdstsize , 6 );

		ASSERT_TRUE( strcmp( mbsdst , "libre" ) == 0 );


		::booldog::utils::string::mbs::insert( &res , 3 , mbsdst , mbsdstlen , mbsdstsize , "libcore.so" , 3 , 2 );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( mbsdstlen , 7 );

		ASSERT_EQ( mbsdstsize , 8 );

		ASSERT_TRUE( strcmp( mbsdst , "libcore" ) == 0 );

		allocator.free( mbsdst );

		ASSERT_TRUE( allocator.begin() == begin );
		
		ASSERT_EQ( allocator.available() , total );
	}


	{
		::booldog::result_wchar reswchar( &allocator );

		::booldog::utils::string::mbs::towcs( &reswchar , "locale" , 0 , SIZE_MAX );
		
		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 7 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 6 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"locale" ) == 0 );
	}

	{
		::booldog::result_wchar reswchar( &allocator );

		::booldog::utils::string::mbs::towcs( &reswchar , "locale" , 3 , SIZE_MAX );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 4 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 3 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"ale" ) == 0 );
	}

	{
		::booldog::result_wchar reswchar( &allocator );

		::booldog::utils::string::mbs::towcs( &reswchar , "locale" , 3 , 2 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 3 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 2 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"al" ) == 0 );
	}

	{
		::booldog::result_wchar reswchar( &allocator );

		::booldog::utils::string::mbs::towcs( &reswchar , "locale" , 3 , 2 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 3 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 2 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"al" ) == 0 );

		::booldog::result res;

		::booldog::utils::string::mbs::insert( &res , 2 , reswchar.wchar , reswchar.wlen , reswchar.wsize , "e" , 0 , SIZE_MAX );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( reswchar.wsize , 4 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 3 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"ale" ) == 0 );


		::booldog::utils::string::mbs::insert( &res , 0 , reswchar.wchar , reswchar.wlen , reswchar.wsize , "locale" , 0 , 2 );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( reswchar.wsize , 6 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 5 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"loale" ) == 0 );


		::booldog::utils::string::mbs::insert( &res , 2 , reswchar.wchar , reswchar.wlen , reswchar.wsize , "locale" , 2 , 1 );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( reswchar.wsize , 7 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 6 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"locale" ) == 0 );
	}



	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::tombs( &resmbchar , L"locale" , 0 , SIZE_MAX );
		
		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 7 );

		ASSERT_EQ( resmbchar.mblen , 6 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "locale" ) == 0 );
	}

	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::tombs( &resmbchar , L"locale" , 3 , SIZE_MAX );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 4 );

		ASSERT_EQ( resmbchar.mblen , 3 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "ale" ) == 0 );
	}

	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::tombs( &resmbchar , L"locale" , 3 , 2 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 3 );

		ASSERT_EQ( resmbchar.mblen , 2 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "al" ) == 0 );
	}

	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::tombs( &resmbchar , L"locale" , 3 , 2 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 3 );

		ASSERT_EQ( resmbchar.mblen , 2 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "al" ) == 0 );

		::booldog::result res;

		::booldog::utils::string::wcs::insert( &res , 2 , resmbchar.mbchar , resmbchar.mblen , resmbchar.mbsize , L"e" , 0 , SIZE_MAX );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 4 );

		ASSERT_EQ( resmbchar.mblen , 3 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "ale" ) == 0 );


		::booldog::utils::string::wcs::insert( &res , 0 , resmbchar.mbchar , resmbchar.mblen , resmbchar.mbsize , L"locale" , 0 , 2 );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 6 );

		ASSERT_EQ( resmbchar.mblen , 5 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "loale" ) == 0 );


		::booldog::utils::string::wcs::insert( &res , 2 , resmbchar.mbchar , resmbchar.mblen , resmbchar.mbsize , L"locale" , 2 , 1 );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 7 );

		ASSERT_EQ( resmbchar.mblen , 6 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "locale" ) == 0 );
	}

	ASSERT_TRUE( allocator.begin() == begin );
		
	ASSERT_EQ( allocator.available() , total );
};

class boo_arrayTest : public ::testing::Test 
{
};
TEST_F( boo_arrayTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	booldog::_allocator = &allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{
		::booldog::array< const wchar_t* > wcs_array;

		ASSERT_EQ( wcs_array.insert( 3 , L"TEST2" ) , 0 );

		ASSERT_EQ( wcs_array.count() , 1 );

		ASSERT_TRUE( wcscmp( wcs_array[ 0 ] , L"TEST2" ) == 0 );

		ASSERT_EQ( wcs_array.insert( 0 , L"TEST0" ) , 0 );

		ASSERT_EQ( wcs_array.count() , 2 );

		ASSERT_TRUE( wcscmp( wcs_array[ 0 ] , L"TEST0" ) == 0 );

		ASSERT_TRUE( wcscmp( wcs_array[ 1 ] , L"TEST2" ) == 0 );

		ASSERT_EQ( wcs_array.insert( 1 , L"TEST1" ) , 1 );

		ASSERT_EQ( wcs_array.count() , 3 );

		ASSERT_TRUE( wcscmp( wcs_array[ 0 ] , L"TEST0" ) == 0 );

		ASSERT_TRUE( wcscmp( wcs_array[ 1 ] , L"TEST1" ) == 0 );

		ASSERT_TRUE( wcscmp( wcs_array[ 2 ] , L"TEST2" ) == 0 );

		wcs_array.clear();

		ASSERT_EQ( wcs_array.count() , 0 );


		ASSERT_EQ( wcs_array.add( L"TEST2" ) , 0 );

		ASSERT_EQ( wcs_array.count() , 1 );

		ASSERT_TRUE( wcscmp( wcs_array[ 0 ] , L"TEST2" ) == 0 );

		ASSERT_EQ( wcs_array.add( L"TEST0" ) , 1 );

		ASSERT_EQ( wcs_array.count() , 2 );

		ASSERT_TRUE( wcscmp( wcs_array[ 0 ] , L"TEST2" ) == 0 );

		ASSERT_TRUE( wcscmp( wcs_array[ 1 ] , L"TEST0" ) == 0 );

		ASSERT_EQ( wcs_array.add( L"TEST1" ) , 2 );

		ASSERT_EQ( wcs_array.count() , 3 );

		ASSERT_TRUE( wcscmp( wcs_array[ 0 ] , L"TEST2" ) == 0 );

		ASSERT_TRUE( wcscmp( wcs_array[ 1 ] , L"TEST0" ) == 0 );

		ASSERT_TRUE( wcscmp( wcs_array[ 2 ] , L"TEST1" ) == 0 );


		wcs_array.remove( 1 , 4 );

		ASSERT_EQ( wcs_array.count() , 1 );

		ASSERT_TRUE( wcscmp( wcs_array[ 0 ] , L"TEST2" ) == 0 );


		ASSERT_EQ( wcs_array.add( L"TEST1" ) , 1 );

		ASSERT_EQ( wcs_array.count() , 2 );

		ASSERT_TRUE( wcscmp( wcs_array[ 0 ] , L"TEST2" ) == 0 );

		ASSERT_TRUE( wcscmp( wcs_array[ 1 ] , L"TEST1" ) == 0 );


		wcs_array.remove( 0 , 1 );

		ASSERT_EQ( wcs_array.count() , 1 );

		ASSERT_TRUE( wcscmp( wcs_array[ 0 ] , L"TEST1" ) == 0 );
	}

	ASSERT_TRUE( allocator.begin() == begin );
		
	ASSERT_EQ( allocator.available() , total );
};

class boo_listTest : public ::testing::Test 
{
};
TEST_F( boo_listTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	booldog::_allocator = &allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{
		::booldog::string item0( "TEST0" );

		::booldog::string item1( "TEST1" );

		::booldog::string item2( "TEST2" );

		::booldog::list< ::booldog::string > string_array;

		::booldog::list< ::booldog::object > object_array;


		ASSERT_EQ( string_array.insert( 3 , item2 ) , 0 );

		ASSERT_EQ( string_array.count() , 1 );

		ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

		ASSERT_EQ( string_array.insert( 0 , item0 ) , 0 );

		ASSERT_EQ( string_array.count() , 2 );

		ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST0" ) == 0 );

		ASSERT_TRUE( strcmp( string_array[ 1 ].str() , "TEST2" ) == 0 );

		ASSERT_EQ( string_array.insert( 1 , item1 ) , 1 );

		ASSERT_EQ( string_array.count() , 3 );

		ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST0" ) == 0 );

		ASSERT_TRUE( strcmp( string_array[ 1 ].str() , "TEST1" ) == 0 );

		ASSERT_TRUE( strcmp( string_array[ 2 ].str() , "TEST2" ) == 0 );

		string_array.clear();

		ASSERT_EQ( string_array.count() , 0 );


		ASSERT_EQ( string_array.add( item2 ) , 0 );

		ASSERT_EQ( string_array.count() , 1 );

		ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

		ASSERT_EQ( string_array.add( item0 ) , 1 );

		ASSERT_EQ( string_array.count() , 2 );

		ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

		ASSERT_TRUE( strcmp( string_array[ 1 ].str() , "TEST0" ) == 0 );

		ASSERT_EQ( string_array.add( item1 ) , 2 );

		ASSERT_EQ( string_array.count() , 3 );

		ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

		ASSERT_TRUE( strcmp( string_array[ 1 ].str() , "TEST0" ) == 0 );

		ASSERT_TRUE( strcmp( string_array[ 2 ].str() , "TEST1" ) == 0 );


		string_array.remove( 1 , 4 );

		ASSERT_EQ( string_array.count() , 1 );

		ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );


		ASSERT_EQ( string_array.add( item1 ) , 1 );

		ASSERT_EQ( string_array.count() , 2 );

		ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

		ASSERT_TRUE( strcmp( string_array[ 1 ].str() , "TEST1" ) == 0 );


		string_array.remove( 0 , 1 );

		ASSERT_EQ( string_array.count() , 1 );

		ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST1" ) == 0 );


		string_array.insert( 1 , object_array );

	}

	ASSERT_TRUE( allocator.begin() == begin );
		
	ASSERT_EQ( allocator.available() , total );
};


class boo_assignmentTest : public ::testing::Test 
{
};
TEST_F( boo_assignmentTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	booldog::_allocator = &allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();


	::booldog::object obj;

	::booldog::string str;

	::booldog::list< ::booldog::string > str_array;

	::booldog::list< ::booldog::object > obj_array;

	::booldog::list< ::booldog::list< ::booldog::object > > obj_array_array;

	::booldog::list< ::booldog::list< ::booldog::string > > str_array_array;


	ASSERT_TRUE( allocator.begin() == begin );
		
	ASSERT_EQ( allocator.available() , total );
};


class boo_checkTest : public ::testing::Test 
{
};
TEST_F( boo_checkTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	booldog::_allocator = &allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{
		::booldog::object obj( &allocator );

		::booldog::string str( &allocator );

		::booldog::list< ::booldog::string > str_array( &allocator );

		::booldog::list< ::booldog::object > obj_array( &allocator );

		::booldog::list< ::booldog::list< ::booldog::object > > obj_array_array( &allocator );

		::booldog::list< ::booldog::list< ::booldog::string > > str_array_array( &allocator );


		ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( str ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::string >( str ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( str ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( str ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( str ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( str ) );


		ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( str_array ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( str_array ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( str_array ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( str_array ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( str_array ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( str_array ) );


		ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj_array ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj_array ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj_array ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj_array ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj_array ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj_array ) );


		ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj_array_array ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj_array_array ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj_array_array ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj_array_array ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj_array_array ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj_array_array ) );


		ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( str_array_array ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( str_array_array ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( str_array_array ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( str_array_array ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( str_array_array ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( str_array_array ) );


		ASSERT_TRUE( ::booldog::isclass< ::booldog::object >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( str ) );

		ASSERT_TRUE( ::booldog::isclass< ::booldog::string >( str ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( str ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( str ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( str ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( str ) );


		ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( str_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( str_array ) );

		ASSERT_TRUE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( str_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( str_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( str_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( str_array ) );


		ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj_array ) );

		ASSERT_TRUE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj_array ) );


		ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj_array_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj_array_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj_array_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj_array_array ) );

		ASSERT_TRUE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj_array_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj_array_array ) );


		ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( str_array_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( str_array_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( str_array_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( str_array_array ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( str_array_array ) );

		ASSERT_TRUE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( str_array_array ) );


		obj = str;

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::string >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

		ASSERT_TRUE( ::booldog::isclass< ::booldog::string >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		obj = str_array;

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

		ASSERT_TRUE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		obj = obj_array;

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj ) );

		ASSERT_TRUE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		obj = obj_array_array;

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj ) );

		ASSERT_TRUE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		obj = str_array_array;

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

		ASSERT_FALSE( ::booldog::can_assign< ::booldog::list< ::booldog::string > >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::object > >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		ASSERT_TRUE( ::booldog::can_assign< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );


		ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::string > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::object > >( obj ) );

		ASSERT_FALSE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::object > > >( obj ) );

		ASSERT_TRUE( ::booldog::isclass< ::booldog::list< ::booldog::list< ::booldog::string > > >( obj ) );
	}

	ASSERT_TRUE( allocator.begin() == begin );
		
	ASSERT_EQ( allocator.available() , total );
};
class boo_io_utilsTest : public ::testing::Test 
{
};
TEST_F( boo_io_utilsTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	booldog::_allocator = &allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{

		const wchar_t* wtest = L"C:/privet\\../gui.exe\\./..\\ui.exe";
		const char* mbtest = "C:/privet\\../gui.exe\\./..\\ui.exe";

		const wchar_t* wtest2 = L"C:/privet\\../gui.exe\\./..\\ui";
		const char* mbtest2 = "C:/privet\\../gui.exe\\./..\\ui";

		::booldog::result_wchar reswchar( ::booldog::_allocator );
	
		::booldog::utils::io::path::wcs::filename( &reswchar , wtest );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 7 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 6 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"ui.exe" ) == 0 );

		::booldog::utils::io::path::wcs::filename( &reswchar , wtest , 3 , 17 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 8 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 7 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"gui.exe" ) == 0 );


		::booldog::utils::io::path::wcs::directory( &reswchar , wtest );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 26 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 25 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"C:/privet\\../gui.exe\\./.." ) == 0 );

		::booldog::utils::io::path::wcs::directory( &reswchar , wtest , 3 , 17 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 10 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 9 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"privet\\.." ) == 0 );


		::booldog::utils::io::path::wcs::extension( &reswchar , wtest );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 4 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 3 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"exe" ) == 0 );

		::booldog::utils::io::path::wcs::extension( &reswchar , wtest , 3 , 16 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 3 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 2 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"ex" ) == 0 );

		::booldog::utils::io::path::wcs::extension( &reswchar , wtest2 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 1 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 0 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::result_mbchar resmbchar( ::booldog::_allocator );
	
		::booldog::utils::io::path::mbs::filename( &resmbchar , mbtest );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 7 );

		ASSERT_EQ( resmbchar.mblen , 6 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "ui.exe" ) == 0 );

		::booldog::utils::io::path::mbs::filename( &resmbchar , mbtest , 3 , 17 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 8 );

		ASSERT_EQ( resmbchar.mblen , 7 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "gui.exe" ) == 0 );


		::booldog::utils::io::path::mbs::directory( &resmbchar , mbtest );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 26 );

		ASSERT_EQ( resmbchar.mblen , 25 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "C:/privet\\../gui.exe\\./.." ) == 0 );

		::booldog::utils::io::path::mbs::directory( &resmbchar , mbtest , 3 , 17 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 10 );

		ASSERT_EQ( resmbchar.mblen , 9 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "privet\\.." ) == 0 );


		::booldog::utils::io::path::mbs::extension( &resmbchar , mbtest );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 4 );

		ASSERT_EQ( resmbchar.mblen , 3 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "exe" ) == 0 );

		::booldog::utils::io::path::mbs::extension( &resmbchar , mbtest , 3 , 16 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 3 );

		ASSERT_EQ( resmbchar.mblen , 2 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "ex" ) == 0 );

		::booldog::utils::io::path::mbs::extension( &resmbchar , mbtest2 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 1 );

		ASSERT_EQ( resmbchar.mblen , 0 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , L"home\\kill/." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 12 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 9 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , L"home\\./.\\kill/." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 16 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 9 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , L"./home\\./.\\kill/." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 18 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 9 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , L"./home/try\\explain\\./.\\../..\\kill/." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 36 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 9 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , L"./home/try\\explain\\./.\\../..\\kill/joke\\.." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 42 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 9 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , L"/home/.." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 9 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 0 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , L".\\" );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 3 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 0 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , L"." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 2 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 0 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , L"home\\./\\.\\kill/." );

		ASSERT_FALSE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( reswchar.booerror , ::booldog::enums::result::booerr_type_path_has_incorrect_format );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , L"./.\\../kill/." );

		ASSERT_FALSE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( reswchar.booerror , ::booldog::enums::result::booerr_type_not_enough_top_level_folders );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , L"../local" );

		ASSERT_FALSE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( reswchar.booerror , ::booldog::enums::result::booerr_type_not_enough_top_level_folders );



		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , "home\\kill/." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 12 );

		ASSERT_EQ( resmbchar.mblen , 9 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , "home\\./.\\kill/." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 16 );

		ASSERT_EQ( resmbchar.mblen , 9 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , "./home\\./.\\kill/." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 18 );

		ASSERT_EQ( resmbchar.mblen , 9 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , "./home/try\\explain\\./.\\../..\\kill/." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 36 );

		ASSERT_EQ( resmbchar.mblen , 9 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , "./home/try\\explain\\./.\\../..\\kill/joke\\.." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 42 );

		ASSERT_EQ( resmbchar.mblen , 9 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , "/home/.." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 9 );

		ASSERT_EQ( resmbchar.mblen , 0 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , ".\\" );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 3 );

		ASSERT_EQ( resmbchar.mblen , 0 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , "." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 2 );

		ASSERT_EQ( resmbchar.mblen , 0 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , "home\\./\\.\\kill/." );

		ASSERT_FALSE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resmbchar.booerror , ::booldog::enums::result::booerr_type_path_has_incorrect_format );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , "./.\\../kill/." );

		ASSERT_FALSE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resmbchar.booerror , ::booldog::enums::result::booerr_type_not_enough_top_level_folders );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , "../local" );

		ASSERT_FALSE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resmbchar.booerror , ::booldog::enums::result::booerr_type_not_enough_top_level_folders );


		::booldog::result_bool resbool;

		::booldog::utils::io::path::wcs::has_levels( &resbool , 0 );

		ASSERT_FALSE( resbool.succeeded() );

		ASSERT_EQ( resbool.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resbool.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::io::path::wcs::has_levels( &resbool , L"" );

		ASSERT_FALSE( resbool.succeeded() );

		ASSERT_EQ( resbool.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resbool.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::io::path::wcs::has_levels( &resbool , L"../local/" , 9 );

		ASSERT_FALSE( resbool.succeeded() );

		ASSERT_EQ( resbool.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resbool.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::io::path::wcs::has_levels( &resbool , L"../local" );

		ASSERT_TRUE( resbool.succeeded() );

		ASSERT_TRUE( resbool.bres );


		::booldog::utils::io::path::wcs::has_levels( &resbool , L"../local" , 2 );

		ASSERT_TRUE( resbool.succeeded() );

		ASSERT_TRUE( resbool.bres );


		::booldog::utils::io::path::wcs::has_levels( &resbool , L"../local" , 3 );

		ASSERT_TRUE( resbool.succeeded() );

		ASSERT_FALSE( resbool.bres );



		::booldog::utils::io::path::mbs::has_levels( &resbool , 0 );

		ASSERT_FALSE( resbool.succeeded() );

		ASSERT_EQ( resbool.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resbool.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::io::path::mbs::has_levels( &resbool , "" );

		ASSERT_FALSE( resbool.succeeded() );

		ASSERT_EQ( resbool.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resbool.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::io::path::mbs::has_levels( &resbool , "../local/" , 9 );

		ASSERT_FALSE( resbool.succeeded() );

		ASSERT_EQ( resbool.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resbool.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::io::path::mbs::has_levels( &resbool , "../local" );

		ASSERT_TRUE( resbool.succeeded() );

		ASSERT_TRUE( resbool.bres );


		::booldog::utils::io::path::mbs::has_levels( &resbool , "../local" , 2 );

		ASSERT_TRUE( resbool.succeeded() );

		ASSERT_TRUE( resbool.bres );


		::booldog::utils::io::path::mbs::has_levels( &resbool , "../local" , 3 );

		ASSERT_TRUE( resbool.succeeded() );

		ASSERT_FALSE( resbool.bres );


	
		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , L"" );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 1 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 0 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , L"core" );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 4 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , L"\\home/core" );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 4 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , L"\\home/core.dll.exe" );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 9 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 8 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"core.dll" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , L"\\home/.core" );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 1 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 0 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , L"\\home/.core" , 7 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 4 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , L"\\home/.core.dll.exe" , 7 , 8 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 4 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , L"\\home/.core.dll.exe" , 7 , 9 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 9 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 8 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"core.dll" ) == 0 );



		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , "" );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 1 );

		ASSERT_EQ( resmbchar.mblen , 0 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , "core" );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 5 );

		ASSERT_EQ( resmbchar.mblen , 4 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , "\\home/core" );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 5 );

		ASSERT_EQ( resmbchar.mblen , 4 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , "\\home/core.dll.exe" );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 9 );

		ASSERT_EQ( resmbchar.mblen , 8 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "core.dll" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , "\\home/.core" );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 1 );

		ASSERT_EQ( resmbchar.mblen , 0 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , "\\home/.core" , 7 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 5 );

		ASSERT_EQ( resmbchar.mblen , 4 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , "\\home/.core.dll.exe" , 7 , 8 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 5 );

		ASSERT_EQ( resmbchar.mblen , 4 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , "\\home/.core.dll.exe" , 7 , 9 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 9 );

		ASSERT_EQ( resmbchar.mblen , 8 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "core.dll" ) == 0 );



		{
			::booldog::result res;

			size_t pathnamelen = 0;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , 0 , pathnamelen );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = 0;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , pathname , pathnamelen );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 4 );

			ASSERT_TRUE( wcscmp( pathname , L"core" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e','.','d','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 4 );

			ASSERT_TRUE( wcscmp( pathname , L"core" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e','.','d','/','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 9 );

			ASSERT_TRUE( wcscmp( pathname , L"core.d/ll" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e','.','d','l','l','.', 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 8 );

			ASSERT_TRUE( wcscmp( pathname , L"core.dll" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { '.','c','o','r','e', 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::pathname_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 0 );

			ASSERT_TRUE( wcscmp( pathname , L"" ) == 0 );
		}


		{
			::booldog::result res;

			size_t pathnamelen = 0;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , 0 , pathnamelen );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = 0;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , pathname , pathnamelen );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 4 );

			ASSERT_TRUE( strcmp( pathname , "core" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e','.','d','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 4 );

			ASSERT_TRUE( strcmp( pathname , "core" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e','.','d','/','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 9 );

			ASSERT_TRUE( strcmp( pathname , "core.d/ll" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e','.','d','l','l','.', 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 8 );

			ASSERT_TRUE( strcmp( pathname , "core.dll" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { '.','c','o','r','e', 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::pathname_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 0 );

			ASSERT_TRUE( strcmp( pathname , "" ) == 0 );
		}


		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , "" , 0 , SIZE_MAX );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 1 );

			ASSERT_EQ( resmbchar.mblen , 0 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , "core" , 0 , SIZE_MAX );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 5 );

			ASSERT_EQ( resmbchar.mblen , 4 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , "core.dll.exe" , 0 , SIZE_MAX );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 9 );

			ASSERT_EQ( resmbchar.mblen , 8 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "core.dll" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , ".core" , 0 , SIZE_MAX );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 1 );

			ASSERT_EQ( resmbchar.mblen , 0 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , "core." , 0 , SIZE_MAX );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 5 );

			ASSERT_EQ( resmbchar.mblen , 4 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , "/home.exe\\core" , 0 , SIZE_MAX );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 15 );

			ASSERT_EQ( resmbchar.mblen , 14 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "/home.exe\\core" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , "/home.exe\\core.dll" , 9 , 4 );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 5 );

			ASSERT_EQ( resmbchar.mblen , 4 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "\\cor" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , "/home.exe\\core.dll" , 1 , 6 );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 5 );

			ASSERT_EQ( resmbchar.mblen , 4 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "home" ) == 0 );
		}


		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , L"" , 0 , SIZE_MAX );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 1 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 0 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , L"core" , 0 , SIZE_MAX );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 4 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , L"core.dll.exe" , 0 , SIZE_MAX );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 9 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 8 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"core.dll" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , L".core" , 0 , SIZE_MAX );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 1 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 0 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , L"core." , 0 , SIZE_MAX );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 4 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , L"/home.exe\\core" , 0 , SIZE_MAX );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 15 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 14 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"/home.exe\\core" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , L"/home.exe\\core.dll" , 9 , 4 );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 4 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"\\cor" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , L"/home.exe\\core.dll" , 1 , 6 );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 4 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"home" ) == 0 );
		}


		{
			::booldog::result res;

			size_t pathnamelen = 0;
			::booldog::utils::io::path::wcs::directory( &res , 0 , pathnamelen );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = 0;
			::booldog::utils::io::path::wcs::directory( &res , pathname , pathnamelen );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::directory( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 4 );

			ASSERT_TRUE( wcscmp( pathname , L"core" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e','\\','d','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::directory( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 4 );

			ASSERT_TRUE( wcscmp( pathname , L"core" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'c','o','r','e','.','d','/','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::directory( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 6 );

			ASSERT_TRUE( wcscmp( pathname , L"core.d" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { '/','c','o','r','e','.','d','l','l','.', 0 };
			size_t pathnamelen = sizeof( pathname ) / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::directory( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 0 );

			ASSERT_TRUE( wcscmp( pathname , L"" ) == 0 );
		}


		{
			::booldog::result res;

			size_t pathnamelen = 0;
			::booldog::utils::io::path::mbs::directory( &res , 0 , pathnamelen );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = 0;
			::booldog::utils::io::path::mbs::directory( &res , pathname , pathnamelen );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e', 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::directory( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 4 );

			ASSERT_TRUE( strcmp( pathname , "core" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e','\\','d','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::directory( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 4 );

			ASSERT_TRUE( strcmp( pathname , "core" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { 'c','o','r','e','.','d','/','l','l' , 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::directory( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 6 );

			ASSERT_TRUE( strcmp( pathname , "core.d" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { '/','c','o','r','e','.','d','l','l','.', 0 };
			size_t pathnamelen = sizeof( pathname ) - 1;
			::booldog::utils::io::path::mbs::directory( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 0 );

			ASSERT_TRUE( strcmp( pathname , "" ) == 0 );
		}



		{
			::booldog::result res;

			wchar_t pathname[] = { 'h','o','m','e','/','.','.','\\','t','e','s','t','/','.','\\','c','o','r','e','\\', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::normalize( &res , pathname , pathnamelen , pathnamesize );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 10 );
	#ifdef __WINDOWS__
			ASSERT_TRUE( wcscmp( pathname , L"\\test\\core" ) == 0 );
	#else
			ASSERT_TRUE( wcscmp( pathname , L"/test/core" ) == 0 );
	#endif
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'h','o','m','e','\\','.','/','\\','.','\\','k','i','l','l','/','.', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::normalize( &res , pathname , pathnamelen , pathnamesize );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_path_has_incorrect_format );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { '.','/','.','\\','.','.','/','k','i','l','l','/','.', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::normalize( &res , pathname , pathnamelen , pathnamesize );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { '.','.','/','l','o','c','a','l', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::normalize( &res , pathname , pathnamelen , pathnamesize );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
		}


		{
			::booldog::result res;

			char pathname[] = { 'h','o','m','e','/','.','.','\\','t','e','s','t','/','.','\\','c','o','r','e','\\', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::normalize( &res , pathname , pathnamelen , pathnamesize );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 10 );
	#ifdef __WINDOWS__
			ASSERT_TRUE( strcmp( pathname , "\\test\\core" ) == 0 );
	#else
			ASSERT_TRUE( strcmp( pathname , "/test/core" ) == 0 );
	#endif
		}

		{
			::booldog::result res;

			char pathname[] = { 'h','o','m','e','\\','.','/','\\','.','\\','k','i','l','l','/','.', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::normalize( &res , pathname , pathnamelen , pathnamesize );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_path_has_incorrect_format );
		}

		{
			::booldog::result res;

			char pathname[] = { '.','/','.','\\','.','.','/','k','i','l','l','/','.', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::normalize( &res , pathname , pathnamelen , pathnamesize );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
		}

		{
			::booldog::result res;

			char pathname[] = { '.','.','/','l','o','c','a','l', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::normalize( &res , pathname , pathnamelen , pathnamesize );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
		}



		{
			::booldog::result res;

			size_t pathnamelen = 0;
			::booldog::utils::io::path::mbs::filename_without_extension( &res , 0 , pathnamelen );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			char pathname[] = { 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::filename_without_extension( &res , pathname , pathnamelen );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			char pathname[] = { '.','.','/','l','o','c','a','l', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::filename_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 5 );

			ASSERT_TRUE( strcmp( pathname , "local" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { '.','.','/','b','.','l','o','c','a','l','.','e', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::filename_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 7 );

			ASSERT_TRUE( strcmp( pathname , "b.local" ) == 0 );
		}

		{
			::booldog::result res;

			char pathname[] = { 'l','o','c','a','l', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize - 1;
			::booldog::utils::io::path::mbs::filename_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 5 );

			ASSERT_TRUE( strcmp( pathname , "local" ) == 0 );
		}


		{
			::booldog::result res;

			size_t pathnamelen = 0;
			::booldog::utils::io::path::wcs::filename_without_extension( &res , 0 , pathnamelen );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::filename_without_extension( &res , pathname , pathnamelen );

			ASSERT_FALSE( res.succeeded() );

			ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

			ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { '.','.','/','l','o','c','a','l', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::filename_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 5 );

			ASSERT_TRUE( wcscmp( pathname , L"local" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { '.','.','/','b','.','l','o','c','a','l','.','e', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::filename_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 7 );

			ASSERT_TRUE( wcscmp( pathname , L"b.local" ) == 0 );
		}

		{
			::booldog::result res;

			wchar_t pathname[] = { 'l','o','c','a','l', 0 };
			size_t pathnamesize = sizeof( pathname );
			size_t pathnamelen = pathnamesize / sizeof( wchar_t ) - 1;
			::booldog::utils::io::path::wcs::filename_without_extension( &res , pathname , pathnamelen );

			ASSERT_TRUE( res.succeeded() );

			ASSERT_EQ( pathnamelen , 5 );

			ASSERT_TRUE( wcscmp( pathname , L"local" ) == 0 );
		}
	}

	ASSERT_TRUE( allocator.begin() == begin );
		
	ASSERT_EQ( allocator.available() , total );
};
class boo_base_loaderTest : public ::testing::Test 
{
};
TEST_F( boo_base_loaderTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	booldog::_allocator = &allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();
	{
		{
			::booldog::result_mbchar resmbchar( booldog::_allocator );
			::booldog::utils::executable::mbs::filename< 4 >( &resmbchar );
			{
				::booldog::result res;

				::booldog::utils::io::path::mbs::filename_without_extension( &res , resmbchar.mbchar , resmbchar.mblen );

				ASSERT_TRUE( res.succeeded() );

				ASSERT_EQ( resmbchar.mblen , 12 );

				ASSERT_TRUE( strcmp( resmbchar.mbchar , "booldog.test" ) == 0 );
			}
		}
		{
			::booldog::result_wchar reswchar( booldog::_allocator );
			::booldog::utils::executable::wcs::filename< 4 >( &reswchar );
			{
				::booldog::result res;

				::booldog::utils::io::path::wcs::filename_without_extension( &res , reswchar.wchar , reswchar.wlen );

				ASSERT_TRUE( res.succeeded() );

				ASSERT_EQ( reswchar.wlen , 12 );

				ASSERT_TRUE( wcscmp( reswchar.wchar , L"booldog.test" ) == 0 );
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

		loader.wcsload( &res , L"core1" , load_params );

		ASSERT_FALSE( res.succeeded() );

		loader.wcsload( &res , L"core" , load_params );
		
		ASSERT_TRUE( res.succeeded() );

		::booldog::base::module* module0 = res.module;

		loader.wcsload( &res , L"core" , 0 );

		ASSERT_TRUE( res.succeeded() );

		::booldog::base::module* module1 = res.module;

		::booldog::result resres;
		loader.unload( &resres , module0 );

		ASSERT_TRUE( res.succeeded() );

		loader.unload( &resres , module1 );

		ASSERT_TRUE( res.succeeded() );

#ifdef __WINDOWS__
		loader.wcsload( &res , L"kernel32" , 0 );
#else
		loader.wcsload( &res , L"rt" , 0 );
#endif

		ASSERT_TRUE( res.succeeded() );

		::booldog::base::module* module2 = res.module;

		loader.unload( &resres , module2 );

		ASSERT_TRUE( res.succeeded() );



		loader.mbsload( &res , "core1" , load_params );

		ASSERT_FALSE( res.succeeded() );

		loader.mbsload( &res , "core" , load_params );

		ASSERT_TRUE( res.succeeded() );

		module0 = res.module;

		char p[ PATH_MAX ] = {0};
		if( dlinfo( module0->handle() , RTLD_DI_ORIGIN , p ) != -1 )
			printf( "RTLD_DI_ORIGIN=%s\n" , p );
		struct link_map *map = 0;
		if( dlinfo( module0->handle() , RTLD_DI_LINKMAP , &map ) != -1 )
			printf( "RTLD_DI_LINKMAP=%s\n" , map->l_name );

		loader.mbsload( &res , "core" , 0 );

		ASSERT_TRUE( res.succeeded() );	

		module1 = res.module;

		if( dlinfo( module1->handle() , RTLD_DI_ORIGIN , p ) != -1 )
			printf( "RTLD_DI_ORIGIN=%s\n" , p );
		if( dlinfo( module1->handle() , RTLD_DI_LINKMAP , &map ) != -1 )
			printf( "RTLD_DI_LINKMAP=%s\n" , map->l_name );

		loader.unload( &resres , module0 );

		ASSERT_TRUE( res.succeeded() );

		loader.unload( &resres , module1 );

		ASSERT_TRUE( res.succeeded() );
#ifdef __WINDOWS__
		loader.mbsload( &res , "kernel32" , 0 );
#else
		loader.mbsload( &res , "rt" , 0 );
#endif

		ASSERT_TRUE( res.succeeded() );

		module2 = res.module;

				
		if( dlinfo( module2->handle() , RTLD_DI_ORIGIN , p ) != -1 )
			printf( "RTLD_DI_ORIGIN=%s\n" , p );
		if( dlinfo( module2->handle() , RTLD_DI_LINKMAP , &map ) != -1 )
			printf( "RTLD_DI_LINKMAP=%s\n" , map->l_name );


		loader.unload( &resres , module2 );

		ASSERT_TRUE( res.succeeded() );




#ifdef __WINDOWS__
		loader.mbsload( &res , "kernel32" , 0 );
#else
		loader.mbsload( &res , "./libcore.so" , 0 );
#endif

		ASSERT_TRUE( res.succeeded() );

		module2 = res.module;

				
		if( dlinfo( module2->handle() , RTLD_DI_ORIGIN , p ) != -1 )
			printf( "RTLD_DI_ORIGIN=%s\n" , p );
		if( dlinfo( module2->handle() , RTLD_DI_LINKMAP , &map ) != -1 )
			printf( "RTLD_DI_LINKMAP=%s\n" , map->l_name );


		loader.unload( &resres , module2 );

		ASSERT_TRUE( res.succeeded() );
	}

	ASSERT_TRUE( allocator.begin() == begin );

	ASSERT_EQ( allocator.available() , total );
};
#ifdef __LINUX__
#include <locale.h>
#include <langinfo.h>
#endif
int main( int argc , char **argv )
{
#ifdef __LINUX__
	/*char* encoding = nl_langinfo(CODESET);
    printf("Encoding is %s\n", encoding);

	setlocale(LC_ALL, "");
    char* locstr = setlocale(LC_CTYPE, NULL);
    encoding = nl_langinfo(CODESET);
    printf("Locale is %s\n", locstr);
    printf("Encoding is %s\n", encoding);*/
#endif
    ::testing::InitGoogleTest( &argc , argv );
    return RUN_ALL_TESTS();
};