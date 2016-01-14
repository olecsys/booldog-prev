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
#include <boo_stack_allocator.h>
#include <boo_heap_allocator.h>
#include <boo_mixed_allocator.h>
#include <boo_mem.h>
#include <boo_base_loader.h>
#include <boo_module_utils.h>
#include <boo_io_utils.h>
#include <boo_array.h>
#include <boo_param.h>
#include <boo_string_utils.h>
#include <boo_error_format.h>
#include <boo_json.h>
#include <boo_io_file.h>
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

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_int32 );

	ASSERT_EQ( p1[ index ].int32value , -32 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test1" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_bool );

	ASSERT_EQ( p1[ index ].boolvalue , false );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test2" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_char );

	ASSERT_EQ( p1[ index ].charvalue , -127 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test3" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_uchar );

	ASSERT_EQ( p1[ index ].ucharvalue , 128 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test4" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_short );

	ASSERT_EQ( p1[ index ].shortvalue , -1986 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test5" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_ushort );

	ASSERT_EQ( p1[ index ].ushortvalue , 1986 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test6" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_int64 );

	ASSERT_EQ( p1[ index ].int64value , -123456789 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test7" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_uint64 );

	ASSERT_EQ( p1[ index ].uint64value , 123456789 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test8" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_wchar );

	ASSERT_EQ( p1[ index ].wcharvalue , L'W' );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test9" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_pchar );

	ASSERT_EQ( strcmp( p1[ index ].pcharvalue , "hello" ) , 0 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test10" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_pwchar );

	ASSERT_EQ( wcscmp( p1[ index ].pwcharvalue , L"hello" ) , 0 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test11" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_pvoid );

	ASSERT_EQ( p1[ index ].pvoidvalue , &p0 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test12" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_pnamed_param );

	ASSERT_EQ( p1[ index ].pnamed_paramvalue , p1 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test13" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_pparam );

	ASSERT_EQ( p1[ index ].pparamvalue , p0 );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test14" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_pint32 );

	ASSERT_EQ( p1[ index ].pint32value , &int32value );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test15" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_puint32 );

	ASSERT_EQ( p1[ index ].puint32value , &uint32value );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test16" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_pbool );

	ASSERT_EQ( p1[ index ].pboolvalue , &boolvalue );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test17" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_puchar );

	ASSERT_EQ( p1[ index ].pucharvalue , &ucharvalue );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test18" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_pshort );

	ASSERT_EQ( p1[ index ].pshortvalue , &shortvalue );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test19" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_pushort );

	ASSERT_EQ( p1[ index ].pushortvalue , &ushortvalue );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test20" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_pint64 );

	ASSERT_EQ( p1[ index ].pint64value , &int64value );

	index++;

	ASSERT_EQ( strcmp( p1[ index ].name , "test21" ) , 0 );

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_puint64 );

	ASSERT_EQ( p1[ index ].puint64value , &uint64value );

	index++;

	ASSERT_EQ( p1[ index ].type , ::booldog::enums::param::type_none );


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

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_not_found );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test0" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_int32 );

	ASSERT_EQ( p2[ index ].int32value , -32 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test1" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_bool );

	ASSERT_EQ( p2[ index ].boolvalue , false );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test2" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_char );

	ASSERT_EQ( p2[ index ].charvalue , -127 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test3" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_uchar );

	ASSERT_EQ( p2[ index ].ucharvalue , 128 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test4" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_short );

	ASSERT_EQ( p2[ index ].shortvalue , -1986 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test5" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_ushort );

	ASSERT_EQ( p2[ index ].ushortvalue , 1986 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test6" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_int64 );

	ASSERT_EQ( p2[ index ].int64value , -123456789 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test7" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_uint64 );

	ASSERT_EQ( p2[ index ].uint64value , 123456789 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test8" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_wchar );

	ASSERT_EQ( p2[ index ].wcharvalue , L'W' );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test9" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_pchar );

	ASSERT_EQ( strcmp( p2[ index ].pcharvalue , "hello" ) , 0 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test10" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_pwchar );

	ASSERT_EQ( wcscmp( p2[ index ].pwcharvalue , L"hello" ) , 0 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test11" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_pvoid );

	ASSERT_EQ( p2[ index ].pvoidvalue , &p0 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test12" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_pnamed_param );

	ASSERT_EQ( p2[ index ].pnamed_paramvalue , p1 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test13" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_pparam );

	ASSERT_EQ( p2[ index ].pparamvalue , p0 );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test14" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_pint32 );

	ASSERT_EQ( p2[ index ].pint32value , &int32value );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test15" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_puint32 );

	ASSERT_EQ( p2[ index ].puint32value , &uint32value );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test16" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_pbool );

	ASSERT_EQ( p2[ index ].pboolvalue , &boolvalue );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test17" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_puchar );

	ASSERT_EQ( p2[ index ].pucharvalue , &ucharvalue );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test18" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_pshort );

	ASSERT_EQ( p2[ index ].pshortvalue , &shortvalue );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test19" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_pushort );

	ASSERT_EQ( p2[ index ].pushortvalue , &ushortvalue );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test20" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_pint64 );

	ASSERT_EQ( p2[ index ].pint64value , &int64value );

	index++;

	ASSERT_EQ( strcmp( p2[ index ].name , "test21" ) , 0 );

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_puint64 );

	ASSERT_EQ( p2[ index ].puint64value , &uint64value );

	index++;

	ASSERT_EQ( p2[ index ].type , ::booldog::enums::param::type_none );

};

#define boo_stackTestAllocatorSize 64
class boo_stackTest : public ::testing::Test 
{
};
TEST_F( boo_stackTest , test )
{
	::booldog::allocators::stack< boo_stackTestAllocatorSize > allocator;

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


class boo_allocators_heapTest : public ::testing::Test 
{
};
TEST_F( boo_allocators_heapTest , test )
{
	::booldog::allocators::easy::heap allocator;

	void* ptr0 = allocator.alloc( boo_stackTestAllocatorSize );

	size_t ptr0_mswi = ::booldog::mem::info::memory_size_with_info( boo_stackTestAllocatorSize );
	size_t ptr0_mis = ::booldog::mem::info::memory_info_size( boo_stackTestAllocatorSize );
	
	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , ptr0_mswi );

	size_t ptr1_mswi = ::booldog::mem::info::memory_size_with_info( 17 );
	size_t ptr1_mis = ::booldog::mem::info::memory_info_size( 17 );

	void* ptr1 = allocator.alloc( 17 );

	ASSERT_FALSE( ptr1 == 0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , ptr0_mswi + ptr1_mswi );

	allocator.free( ptr0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , ptr1_mswi );

	allocator.free( ptr1 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );


	ptr0 = allocator.alloc( 23 );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 23 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 23 );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , ptr0_mswi );


	ptr1 = allocator.alloc( 17 );

	ptr1_mswi = ::booldog::mem::info::memory_size_with_info( 17 );
	ptr1_mis = ::booldog::mem::info::memory_info_size( 17 );

	ASSERT_FALSE( ptr1 == 0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , ptr0_mswi + ptr1_mswi );


	allocator.free( ptr0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , ptr1_mswi );

	allocator.free( ptr1 );

	ptr1 = 0;

	ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );


	ptr0 = allocator.alloc( 45 );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 45 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 45 );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , ptr0_mswi );

	allocator.free( ptr0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );


	ptr0 = 0;

	ptr0 = allocator.realloc( ptr0 , 45 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 45 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 45 );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , ptr0_mswi );

	ptr0 = allocator.realloc( ptr0 , 45 );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , ptr0_mswi );


	ptr0 = allocator.realloc( ptr0 , 50 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 50 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 50 );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , ptr0_mswi );


	ptr0 = allocator.realloc( ptr0 , 45 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 45 );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 45 );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , ptr0_mswi );

	allocator.free( ptr0 );

	ptr0 = 0;

	ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );


	ptr0 = allocator.realloc_array< wchar_t >( (wchar_t*)ptr0 , 11 );
	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( 11 * sizeof( wchar_t ) );
	ptr0_mis = ::booldog::mem::info::memory_info_size( 11 * sizeof( wchar_t ) );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( allocator.size_of_allocated_memory() , ptr0_mswi );

	allocator.free( ptr0 );

	ptr0 = 0;

	ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );





	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 6 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 8 * 4 );

		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );
	}


	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 6 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 8 );

		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );
	}


	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 7 * 4 );
		
		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );
	}

	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 * 4 );
		
		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );
	}

	{
		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 3 * 4 );		

		allocator.free( ptr1 );

		ptr1 = 0;

		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );
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

		ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );
	}



	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 7 );

		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );
	}

	{
		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 4 );

		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );
	}

	{
		ptr1 = allocator.realloc_array< char >( (char*)ptr1 , 3 * 4 );

		ptr0 = allocator.realloc_array< char >( (char*)ptr0 , 3 );

		allocator.free( ptr1 );

		ptr1 = 0;

		allocator.free( ptr0 );

		ptr0 = 0;

		ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );
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

		ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );
	}
			
	ASSERT_EQ( allocator.size_of_allocated_memory() , 0 );
};


class boo_allocators_mixedTest : public ::testing::Test 
{
};
TEST_F( boo_allocators_mixedTest , test )
{
	::booldog::allocators::easy::heap heap;
	::booldog::allocators::mixed< 32 > mixed( &heap , ::booldog::threading::thread_id() );

	size_t total = mixed.stack.available();

	char* begin = (char*)mixed.stack.begin();

	size_t size = 17;

	void* ptr0 = mixed.alloc( size );

	size_t ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	size_t ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , 0 );

	ASSERT_TRUE( mixed.stack.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr0 == ( begin + ptr0_mis ) );

	ASSERT_EQ( mixed.stack.available() , total - ptr0_mswi );


	size = 1475;

	void* ptr2 = mixed.alloc( size );

	size_t ptr2_mswi = ::booldog::mem::info::memory_size_with_info( size );

	ASSERT_FALSE( ptr2 == 0 );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , ptr2_mswi );


	size = 4;

	void* ptr1 = mixed.alloc( size );

	size_t ptr1_mswi = ::booldog::mem::info::memory_size_with_info( size );
	size_t ptr1_mis = ::booldog::mem::info::memory_info_size( size );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , ptr2_mswi );

	ASSERT_TRUE( mixed.stack.begin() == begin + ptr0_mswi + ptr1_mswi );

	ASSERT_TRUE( ptr1 == ( begin + ptr1_mis + ptr0_mswi ) );

	ASSERT_EQ( mixed.stack.available() , total - ptr0_mswi - ptr1_mswi );
	

	mixed.free( ptr1 );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , ptr2_mswi );

	ASSERT_TRUE( mixed.stack.begin() == begin + ptr0_mswi );

	ASSERT_EQ( mixed.stack.available() , total - ptr0_mswi );


	mixed.free( ptr0 );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , ptr2_mswi );

	ASSERT_TRUE( mixed.stack.begin() == begin );

	ASSERT_EQ( mixed.stack.available() , total );


	mixed.free( ptr2 );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , 0 );

	ASSERT_TRUE( mixed.stack.begin() == begin );

	ASSERT_EQ( mixed.stack.available() , total );
	

	ptr0 = 0;

	size = 17;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , 0 );

	ASSERT_TRUE( mixed.stack.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr0 == ( begin + ptr0_mis ) );

	ASSERT_EQ( mixed.stack.available() , total - ptr0_mswi );


	size = 11;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , 0 );

	ASSERT_TRUE( mixed.stack.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr0 == ( begin + ptr0_mis ) );

	ASSERT_EQ( mixed.stack.available() , total - ptr0_mswi );


	size = 26;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , 0 );

	ASSERT_TRUE( mixed.stack.begin() == begin + ptr0_mswi );

	ASSERT_TRUE( ptr0 == ( begin + ptr0_mis ) );

	ASSERT_EQ( mixed.stack.available() , total - ptr0_mswi );


	size = 0;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , 0 );

	ASSERT_TRUE( mixed.stack.begin() == begin );

	ASSERT_TRUE( ptr0 == 0 );

	ASSERT_EQ( mixed.stack.available() , total );


	size = 176;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , ptr0_mswi );

	ASSERT_TRUE( mixed.stack.begin() == begin );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( mixed.stack.available() , total );


	size = 17;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , ptr0_mswi );

	ASSERT_TRUE( mixed.stack.begin() == begin );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( mixed.stack.available() , total );


	size = 298;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , ptr0_mswi );

	ASSERT_TRUE( mixed.stack.begin() == begin );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( mixed.stack.available() , total );


	size = 0;

	ptr0 = mixed.realloc( ptr0 , size );

	ptr0_mswi = ::booldog::mem::info::memory_size_with_info( size );
	ptr0_mis = ::booldog::mem::info::memory_info_size( size );

	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , 0 );

	ASSERT_TRUE( mixed.stack.begin() == begin );

	ASSERT_TRUE( ptr0 == 0 );

	ASSERT_EQ( mixed.stack.available() , total );




	ASSERT_EQ( mixed.heap->size_of_allocated_memory() , 0 );

	ASSERT_TRUE( mixed.stack.begin() == begin );

	ASSERT_EQ( mixed.stack.available() , total );
};


class boo_memTest : public ::testing::Test 
{
};
TEST_F( boo_memTest , test )
{
	::booldog::allocators::stack< 4096 > allocator;

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

class boo_jsonTest : public ::testing::Test 
{
};
TEST_F( boo_jsonTest , test )
{
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();
	{
		::booldog::data::json::serializator serializator( &allocator );

		::booldog::data::json::result res( &serializator );

		::booldog::data::json::parse< 1 >( &res , &allocator , "0" );

		ASSERT_TRUE( res.succeeded() );

		::booldog::data::json::object root = (*res.serializator);

		const char* json = root.json;

		ASSERT_TRUE( strcmp( json , "0" ) == 0 );
		
		ASSERT_TRUE( root.isnumber() );

		::booldog::uint64 valueuint64 = root.value;

		ASSERT_EQ( valueuint64 , 0 );

		::booldog::uint32 valueuint32 = root.value;

		ASSERT_EQ( valueuint32 , 0 );

		::booldog::int64 valueint64 = root.value;

		ASSERT_EQ( valueint64 , 0 );

		::booldog::int32 valueint32 = root.value;

		ASSERT_EQ( valueint32 , 0 );

		float valuefloat = root.value;

		ASSERT_EQ( valuefloat , 0 );

		const char* valuestring = root.value;

		ASSERT_TRUE( valuestring == 0 );

		bool valuebool = root.value;

		ASSERT_FALSE( valuebool );

		json = root.json;

		ASSERT_TRUE( strcmp( json , "0" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "00" );

		ASSERT_FALSE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "-0" );

		ASSERT_TRUE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( strcmp( json , "-0" ) == 0 );

		ASSERT_TRUE( root.isnumber() );

		valueuint64 = root.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = root.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = root.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = root.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = root.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = root.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = root.value;

		ASSERT_FALSE( valuebool );

		json = root.json;

		ASSERT_TRUE( strcmp( json , "-0" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "  0.E  " );

		ASSERT_FALSE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "-0.02" );

		ASSERT_TRUE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( strcmp( json , "-0.02" ) == 0 );

		ASSERT_TRUE( root.isnumber() );

		valueuint64 = root.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = root.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = root.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = root.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = root.value;

		ASSERT_EQ( valuefloat , -0.02f );

		valuestring = root.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = root.value;

		ASSERT_FALSE( valuebool );

		json = root.json;

		ASSERT_TRUE( strcmp( json , "-0.02" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "-0.02E" );

		ASSERT_FALSE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "-0.02e0" );

		ASSERT_TRUE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( strcmp( json , "-0.02e0" ) == 0 );

		ASSERT_TRUE( root.isnumber() );

		valueuint64 = root.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = root.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = root.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = root.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = root.value;

		ASSERT_EQ( valuefloat , -0.02f );

		valuestring = root.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = root.value;

		ASSERT_FALSE( valuebool );

		json = root.json;

		ASSERT_TRUE( strcmp( json , "-0.02e0" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "-0.02E-3" );

		ASSERT_TRUE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( strcmp( json , "-0.02E-3" ) == 0 );

		ASSERT_TRUE( root.isnumber() );

		valueuint64 = root.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = root.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = root.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = root.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = root.value;

		ASSERT_EQ( ::booldog::utils::round( valuefloat , 5 ) , -0.00002f );

		valuestring = root.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = root.value;

		ASSERT_FALSE( valuebool );

		json = root.json;

		ASSERT_TRUE( strcmp( json , "-0.02E-3" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , " 1986E" );

		ASSERT_FALSE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , " 1986E." );

		ASSERT_FALSE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , " 1986E+" );

		ASSERT_FALSE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , " 1986E-" );

		ASSERT_FALSE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , " 19.86E+3" );

		ASSERT_TRUE( res.succeeded() );
				
		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( strcmp( json , "19.86E+3" ) == 0 );

		ASSERT_TRUE( root.isnumber() );
		
		valueuint64 = root.value;

		ASSERT_EQ( valueuint64 , 19860 );

		valueuint32 = root.value;

		ASSERT_EQ( valueuint32 , 19860 );

		valueint64 = root.value;

		ASSERT_EQ( valueint64 , 19860 );

		valueint32 = root.value;

		ASSERT_EQ( valueint32 , 19860 );

		valuefloat = root.value;

		ASSERT_EQ( valuefloat , 19860.f );

		valuestring = root.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = root.value;

		ASSERT_FALSE( valuebool );

		json = root.json;

		ASSERT_TRUE( strcmp( json , "19.86E+3" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   [     ]   " );

		ASSERT_TRUE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( strcmp( json , "[]" ) == 0 );

		ASSERT_TRUE( root.isarray() );

		ASSERT_EQ( root.count() , 0 );

		valueuint64 = root.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = root.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = root.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = root.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = root.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = root.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = root.value;

		ASSERT_FALSE( valuebool );

		json = root.json;

		ASSERT_TRUE( strcmp( json , "[]" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   {\"test0\":true,     }   " );

		ASSERT_FALSE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   {\"test0\":[    " );

		ASSERT_FALSE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   {\"test0\": \ttRue }    " );

		ASSERT_FALSE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   [\"test0\",    ]    " );

		ASSERT_FALSE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( json == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   [\"test0\",1986 ,\t  25.56   , true   , null ,  {\"1\": true  \t} , [1 , 1 , 2    ] , -21E5 , 2e-1 , 6e+4   ]    " );

		ASSERT_TRUE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( strcmp( json , "[\"test0\",1986,25.56,true,null,{\"1\":true},[1,1,2],-21E5,2e-1,6e+4]" ) == 0 );

		ASSERT_TRUE( root.isarray() );

		ASSERT_EQ( root.count() , 10 );

		valueuint64 = root.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = root.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = root.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = root.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = root.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = root.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = root.value;

		ASSERT_FALSE( valuebool );
		

		::booldog::data::json::object node = root[ 0 ];

		json = node.json;

		ASSERT_TRUE( strcmp( json , "\"test0\"" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isstring() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( strcmp( valuestring , "test0" ) == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root[ 1 ];

		json = node.json;

		ASSERT_TRUE( strcmp( json , "1986" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isnumber() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 1986 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 1986 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 1986 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 1986 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 1986.f );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root[ 2 ];

		json = node.json;
		
		ASSERT_TRUE( strcmp( json , "25.56" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isnumber() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 25 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 25 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 25 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 25 );

		valuefloat = node.value;

		ASSERT_EQ( ::booldog::utils::round( valuefloat , 2 ) , 25.56f );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root[ 3 ];

		json = node.json;
		
		ASSERT_TRUE( strcmp( json , "true" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isboolean() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_TRUE( valuebool );


		node = root[ 4 ];

		json = node.json;
		
		ASSERT_TRUE( strcmp( json , "null" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isnull() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root[ 5 ];

		json = node.json;
		
		ASSERT_TRUE( strcmp( json , "{\"1\":true}" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isobject() );

		ASSERT_EQ( node.count() , 1 );
		
		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = node( "1" );

		json = node.json;

		ASSERT_TRUE( strcmp( json , "true" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isboolean() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		ASSERT_TRUE( strcmp( node.name() , "1" ) == 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_TRUE( valuebool );


		node = root[ 6 ];

		json = node.json;

		ASSERT_TRUE( strcmp( json , "[1,1,2]" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isarray() );

		ASSERT_EQ( node.count() , 3 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );
		

		node = root[ 6 ][ 0 ];

		json = node.json;

		ASSERT_TRUE( strcmp( json , "1" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isnumber() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 1 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 1 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 1 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 1 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 1.f );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root[ 6 ][ 1 ];

		json = node.json;

		ASSERT_TRUE( strcmp( json , "1" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isnumber() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 1 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 1 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 1 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 1 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 1.f );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root[ 6 ][ 2 ];

		json = node.json;

		ASSERT_TRUE( strcmp( json , "2" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isnumber() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 2 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 2 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 2 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 2 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 2.f );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root[ 7 ];

		json = node.json;
		
		ASSERT_TRUE( strcmp( json , "-21E5" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isnumber() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , -2100000 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , -2100000 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , -2100000.f );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root[ 8 ];

		json = node.json;

		ASSERT_TRUE( strcmp( json , "2e-1" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isnumber() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );
		
		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0.2f );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root[ 9 ];

		json = node.json;

		ASSERT_TRUE( strcmp( json , "6e+4" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isnumber() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 60000 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 60000 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 60000 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 60000 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 60000.f );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root[ 10 ];

		json = node.json;

		ASSERT_TRUE( json == 0 );

		ASSERT_FALSE( node.exists() );


		json = root.json;

		ASSERT_TRUE( strcmp( json , "[\"test0\",1986,25.56,true,null,{\"1\":true},[1,1,2],-21E5,2e-1,6e+4]" ) == 0 );



		::booldog::data::json::parse< 1 >( &res , &allocator , "    \"test0 \\t\\n \\u0074\\u0065\\u0073\\u0074\\u0036\\uD834\\uDD1E \\\" \\b \\n\"    " );

		ASSERT_TRUE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( strcmp( json , "\"test0 \\t\\n test6\xf0\x9d\x84\x9e \\\" \\b \\n\"" ) == 0 );

		ASSERT_TRUE( root.isstring() );

		valueuint64 = root.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = root.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = root.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = root.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = root.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = root.value;

		ASSERT_TRUE( strcmp( valuestring , "test0 \t\n test6\xf0\x9d\x84\x9e \" \b \n" ) == 0 );

		valuebool = root.value;

		ASSERT_FALSE( valuebool );

		json = root.json;

		ASSERT_TRUE( strcmp( json , "\"test0 \\t\\n test6\xf0\x9d\x84\x9e \\\" \\b \\n\"" ) == 0 );
		
		
		::booldog::data::json::parse< 1 >( &res , &allocator , "{\"test0\":{},\"test1\":{},\"test2\":{},\"test3\":null,\"test4\":true,\"test5\":false,\"\\u0074\\u0065\\u0073\\u0074\\u0036\\n\\b\\f\":\"example \\u0065 \\b \\n \\f\\n \\\"\",\"\\u0074\\u0065\\u0073\\u0074\\u0036\\uD834\\uDD1E\":25167.678e+4}" );

		ASSERT_TRUE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( strcmp( json , "{\"test0\":{},\"test1\":{},\"test2\":{},\"test3\":null,\"test4\":true,\"test5\":false,\"test6\\n\\b\\f\":\"example \x65 \\b \\n \\f\\n \\\"\",\"test6\xf0\x9d\x84\x9e\":25167.678e+4}" ) == 0 );

		ASSERT_TRUE( root.isobject() );

		ASSERT_EQ( root.count() , 8 );

		valueuint64 = root.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = root.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = root.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = root.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = root.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = root.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = root.value;

		ASSERT_FALSE( valuebool );


		node = root( "test0" );

		json = node.json;

		ASSERT_TRUE( strcmp( json , "{}" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isobject() );

		ASSERT_EQ( node.count() , 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		ASSERT_TRUE( strcmp( node.name() , "test0" ) == 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root( "test1" );

		json = node.json;

		ASSERT_TRUE( strcmp( json , "{}" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isobject() );

		ASSERT_EQ( node.count() , 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		ASSERT_TRUE( strcmp( node.name() , "test1" ) == 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root( "test2" );

		json = node.json;

		ASSERT_TRUE( strcmp( json , "{}" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isobject() );

		ASSERT_EQ( node.count() , 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		ASSERT_TRUE( strcmp( node.name() , "test2" ) == 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root( "test3" );

		json = node.json;

		ASSERT_TRUE( strcmp( json , "null" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isnull() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		ASSERT_TRUE( strcmp( node.name() , "test3" ) == 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root( "test4" );

		json = node.json;

		ASSERT_TRUE( strcmp( json , "true" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isboolean() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		ASSERT_TRUE( strcmp( node.name() , "test4" ) == 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_TRUE( valuebool );


		node = root( "test5" );

		json = node.json;

		ASSERT_TRUE( strcmp( json , "false" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isboolean() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		ASSERT_TRUE( strcmp( node.name() , "test5" ) == 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root( "test6\n\b\f" );

		json = node.json;

		ASSERT_TRUE( strcmp( json , "\"example \x65 \\b \\n \\f\\n \\\"\"" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isstring() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		ASSERT_TRUE( strcmp( node.name() , "test6\n\b\f" ) == 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( strcmp( valuestring , "example \x65 \b \n \f\n \"" ) == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );
		

		node = root( "test6\xf0\x9d\x84\x9e" );

		json = node.json;

		ASSERT_TRUE( strcmp( json , "25167.678e+4" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isnumber() );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 251676780 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 251676780 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 251676780 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 251676780 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 251676780.f );

		ASSERT_TRUE( strcmp( node.name() , "test6\xf0\x9d\x84\x9e" ) == 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 251676780 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 251676780 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 251676780 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 251676780 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 251676780.f );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );


		node = root( "test6\n \f" );

		json = node.json;

		ASSERT_TRUE( json == 0 );

		ASSERT_FALSE( node.exists() );

		node = root( "test6777" );

		json = node.json;

		ASSERT_TRUE( json == 0 );

		ASSERT_FALSE( node.exists() );

		node = root( "test" );

		json = node.json;

		ASSERT_TRUE( json == 0 );

		ASSERT_FALSE( node.exists() );


		json = root.json;

		ASSERT_TRUE( strcmp( json , "{\"test0\":{},\"test1\":{},\"test2\":{},\"test3\":null,\"test4\":true,\"test5\":false,\"test6\\n\\b\\f\":\"example \x65 \\b \\n \\f\\n \\\"\",\"test6\xf0\x9d\x84\x9e\":25167.678e+4}" ) == 0 );


		::booldog::data::json::parse< 1 >( &res , &allocator , "   \n{       \"test0\" : { \t\n\r }      \r}   \n\t" );

		ASSERT_TRUE( res.succeeded() );

		root = (*res.serializator);

		json = root.json;

		ASSERT_TRUE( strcmp( json , "{\"test0\":{}}" ) == 0 );

		ASSERT_TRUE( root.isobject() );

		ASSERT_EQ( root.count() , 1 );

		valueuint64 = root.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = root.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = root.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = root.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = root.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = root.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = root.value;

		ASSERT_FALSE( valuebool );


		node = root( "test0" );

		json = node.json;

		ASSERT_TRUE( strcmp( json , "{}" ) == 0 );

		ASSERT_TRUE( node.exists() );

		ASSERT_TRUE( node.isobject() );

		ASSERT_EQ( node.count() , 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		ASSERT_TRUE( strcmp( node.name() , "test0" ) == 0 );

		valueuint64 = node.value;

		ASSERT_EQ( valueuint64 , 0 );

		valueuint32 = node.value;

		ASSERT_EQ( valueuint32 , 0 );

		valueint64 = node.value;

		ASSERT_EQ( valueint64 , 0 );

		valueint32 = node.value;

		ASSERT_EQ( valueint32 , 0 );

		valuefloat = node.value;

		ASSERT_EQ( valuefloat , 0 );

		valuestring = node.value;

		ASSERT_TRUE( valuestring == 0 );

		valuebool = node.value;

		ASSERT_FALSE( valuebool );
	}

	ASSERT_TRUE( allocator.begin() == begin );
		
	ASSERT_EQ( allocator.available() , total );
};

class boo_stringTest : public ::testing::Test 
{
};
TEST_F( boo_stringTest , test )
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

			ASSERT_TRUE( strcmp( string.str() , "" ) == 0 );

			ASSERT_EQ( string.length() , 0 );

			ASSERT_EQ( string.bytes() , 1 );
		}

		{
			::booldog::string string( &allocator , "" );

			ASSERT_TRUE( strcmp( string.str() , "" ) == 0 );

			ASSERT_EQ( string.length() , 0 );

			ASSERT_EQ( string.bytes() , 1 );
		}

		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );
		}

		{
			::booldog::string string( &allocator , "TEST" , 0 , 4 );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );
		}

		{
			::booldog::string string( &allocator , "Hello, TEST" , 7 );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );
		}

		{
			::booldog::string string( &allocator , "Hello, TEST, it's our first meeting" , 7 , 4 );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 3 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_il_var ) == 0 );

			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , 6 , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , 3 , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_Apr_var ) == 0 );

			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );
		}


		{
			::booldog::string string( &allocator , utf16_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF16 );
		
			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );		
		}

		{
			::booldog::string string( &allocator , utf16_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF16 );
		
			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );

			ASSERT_TRUE( strcmp( string.str() , utf8_il_var ) == 0 );		
		}

		{
			::booldog::string string( &allocator , utf16_April_var , 0 , 12 , ::booldog::enums::string::UTF16 );
		
			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );		
		}

		{
			::booldog::string string( &allocator , utf16_April_var , 0 , 6 , ::booldog::enums::string::UTF16 );
		
			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Apr_var ) == 0 );
		}


		{
			::booldog::string string( &allocator , utf32_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF32 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );
		}

		{
			::booldog::string string( &allocator , utf32_April_var , 12 , SIZE_MAX , ::booldog::enums::string::UTF32 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_il_var ) == 0 );

			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );
		}

		{
			::booldog::string string( &allocator , utf32_April_var , 0 , 24 , ::booldog::enums::string::UTF32 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );
		}

		{
			::booldog::string string( &allocator , utf32_April_var , 0 , 12 , ::booldog::enums::string::UTF32 );
		
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
			::booldog::string string( &allocator , wchar_test , 0 , SIZE_MAX );
		
			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );		
		}

		{
			::booldog::string string( &allocator , wchar_test , 3 , SIZE_MAX );
		
			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );

			ASSERT_TRUE( strcmp( string.str() , utf8_il_var ) == 0 );		
		}

		{
			::booldog::string string( &allocator , wchar_test , 0 , 6 );
		
			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );		
		}

		{
			::booldog::string string( &allocator , wchar_test , 0 , 3 );
		
			ASSERT_EQ( string.length() , 3 );

			ASSERT_EQ( string.bytes() , 7 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Apr_var ) == 0 );
		}



		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApril_var ) == 0 );

			ASSERT_EQ( string.length() , 10 );

			ASSERT_EQ( string.bytes() , 17 );
		}

		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf8_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApril_var ) == 0 );

			ASSERT_EQ( string.length() , 10 );

			ASSERT_EQ( string.bytes() , 17 );
		}

		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf16_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF16 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApril_var ) == 0 );

			ASSERT_EQ( string.length() , 10 );

			ASSERT_EQ( string.bytes() , 17 );
		}

		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf32_April_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF32 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApril_var ) == 0 );

			ASSERT_EQ( string.length() , 10 );

			ASSERT_EQ( string.bytes() , 17 );
		}


		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( cp1251_April_var , 3 , SIZE_MAX , ::booldog::enums::string::CP1251 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTil_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}

		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf8_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF8 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTil_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}

		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf16_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF16 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTil_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}

		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf32_April_var , 12 , SIZE_MAX , ::booldog::enums::string::UTF32 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTil_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}


		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( cp1251_April_var , 0 , 3 , ::booldog::enums::string::CP1251 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApr_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}

		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf8_April_var , 0 , 6 , ::booldog::enums::string::UTF8 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApr_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}

		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf16_April_var , 0 , 6 , ::booldog::enums::string::UTF16 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApr_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}

		{
			::booldog::string string( &allocator , "TEST" );

			ASSERT_TRUE( strcmp( string.str() , "TEST" ) == 0 );

			ASSERT_EQ( string.length() , 4 );

			ASSERT_EQ( string.bytes() , 5 );

			string.append( utf32_April_var , 0 , 12 , ::booldog::enums::string::UTF32 );

			ASSERT_TRUE( strcmp( string.str() , utf8_TESTApr_var ) == 0 );

			ASSERT_EQ( string.length() , 7 );

			ASSERT_EQ( string.bytes() , 11 );
		}



		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , cp1251_il_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf16_il_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF16 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf32_il_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF32 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf8_il_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}


		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , cp1251_April_var , 3 , SIZE_MAX , ::booldog::enums::string::CP1251 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf16_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF16 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf32_April_var , 12 , SIZE_MAX , ::booldog::enums::string::UTF32 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf8_April_var , 6 , SIZE_MAX , ::booldog::enums::string::UTF8 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}


		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , cp1251_April_var , 3 , 3 , ::booldog::enums::string::CP1251 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf16_April_var , 6 , 6 , ::booldog::enums::string::UTF16 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , utf32_April_var , 12 , 12 , ::booldog::enums::string::UTF32 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
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
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
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
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , wchar_test , 3 , SIZE_MAX );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}

		{
			::booldog::string string( &allocator , cp1251_April_var , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_April_var ) == 0 );

			ASSERT_EQ( string.length() , 6 );

			ASSERT_EQ( string.bytes() , 13 );

			string.insert( 3 , wchar_test , 3 , 3 );

			ASSERT_TRUE( strcmp( string.str() , utf8_Aprilil_var ) == 0 );

			ASSERT_EQ( string.length() , 9 );

			ASSERT_EQ( string.bytes() , 19 );
		}



		{
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
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
			::booldog::string string( &allocator , utf8_AprilAprilApril_var , 0 , SIZE_MAX , ::booldog::enums::string::UTF8 );
		
			ASSERT_TRUE( strcmp( string.str() , utf8_AprilAprilApril_var ) == 0 );

			ASSERT_EQ( string.length() , 18 );

			ASSERT_EQ( string.bytes() , 37 );

			::booldog::string res( &allocator );
			res = string.substring( &allocator , 12 );

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
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{
		::booldog::result_bool resbool;

		wchar_t* wcsdst = 0;
		size_t wcsdstlen = 0;
		size_t wcsdstsize = 0;

		::booldog::utils::string::wcs::insert( &resbool , &allocator , true , SIZE_MAX , wcsdst , wcsdstlen , wcsdstsize , 0 );

		ASSERT_FALSE( resbool.succeeded() );

		ASSERT_EQ( resbool.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resbool.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::wcs::insert( &resbool , &allocator , true , SIZE_MAX , wcsdst , wcsdstlen , wcsdstsize , L"" );

		ASSERT_FALSE( resbool.succeeded() );

		ASSERT_EQ( resbool.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resbool.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::wcs::insert( &resbool , &allocator , true , SIZE_MAX , wcsdst , wcsdstlen , wcsdstsize , L"lib" , 3 );

		ASSERT_FALSE( resbool.succeeded() );

		ASSERT_EQ( resbool.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resbool.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::wcs::insert( &resbool , &allocator , true , SIZE_MAX , wcsdst , wcsdstlen , wcsdstsize , L"lib" );

		ASSERT_TRUE( resbool.succeeded() );

		ASSERT_EQ( wcsdstlen , 3 );

		ASSERT_EQ( wcsdstsize , 4 * sizeof( wchar_t ) );

		ASSERT_TRUE( wcscmp( wcsdst , L"lib" ) == 0 );


		::booldog::utils::string::wcs::insert( &resbool , &allocator , true , 3 , wcsdst , wcsdstlen , wcsdstsize , L"re" );

		ASSERT_TRUE( resbool.succeeded() );

		ASSERT_EQ( wcsdstlen , 5 );

		ASSERT_EQ( wcsdstsize , 6 * sizeof( wchar_t ) );

		ASSERT_TRUE( wcscmp( wcsdst , L"libre" ) == 0 );


		::booldog::utils::string::wcs::insert( &resbool , &allocator , true , 3 , wcsdst , wcsdstlen , wcsdstsize , L"libcore.so" , 3 , 2 );

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

		::booldog::utils::string::mbs::insert( &res , &allocator , true , SIZE_MAX , mbsdst , mbsdstlen , mbsdstsize , 0 );

		ASSERT_FALSE( res.succeeded() );

		ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::mbs::insert( &res , &allocator , true , SIZE_MAX , mbsdst , mbsdstlen , mbsdstsize , "" );

		ASSERT_FALSE( res.succeeded() );

		ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::mbs::insert( &res , &allocator , true , SIZE_MAX , mbsdst , mbsdstlen , mbsdstsize , "lib" , 3 );

		ASSERT_FALSE( res.succeeded() );

		ASSERT_EQ( res.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( res.booerror , ::booldog::enums::result::booerr_type_string_parameter_is_empty );


		::booldog::utils::string::mbs::insert( &res , &allocator , true , SIZE_MAX , mbsdst , mbsdstlen , mbsdstsize , "lib" );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( mbsdstlen , 3 );

		ASSERT_EQ( mbsdstsize , 4 );

		ASSERT_TRUE( strcmp( mbsdst , "lib" ) == 0 );


		::booldog::utils::string::mbs::insert( &res , &allocator , true , 3 , mbsdst , mbsdstlen , mbsdstsize , "re" );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( mbsdstlen , 5 );

		ASSERT_EQ( mbsdstsize , 6 );

		ASSERT_TRUE( strcmp( mbsdst , "libre" ) == 0 );


		::booldog::utils::string::mbs::insert( &res , &allocator , true , 3 , mbsdst , mbsdstlen , mbsdstsize , "libcore.so" , 3 , 2 );

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

		::booldog::utils::string::mbs::towcs( &reswchar , &allocator , "locale" , 0 , SIZE_MAX );
		
		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 7 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 6 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"locale" ) == 0 );
	}

	{
		::booldog::result_wchar reswchar( &allocator );

		::booldog::utils::string::mbs::towcs( &reswchar , &allocator , "locale" , 3 , SIZE_MAX );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 4 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 3 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"ale" ) == 0 );
	}

	{
		::booldog::result_wchar reswchar( &allocator );

		::booldog::utils::string::mbs::towcs( &reswchar , &allocator , "locale" , 3 , 2 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 3 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 2 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"al" ) == 0 );
	}

	{
		::booldog::result_wchar reswchar( &allocator );

		::booldog::utils::string::mbs::towcs( &reswchar , &allocator , "locale" , 3 , 2 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 3 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 2 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"al" ) == 0 );

		::booldog::result res;

		::booldog::utils::string::mbs::insert( &res , &allocator , true , 2 , reswchar.wchar , reswchar.wlen , reswchar.wsize , "e" , 0 , SIZE_MAX );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( reswchar.wsize , 4 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 3 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"ale" ) == 0 );


		::booldog::utils::string::mbs::insert( &res , &allocator , true , 0 , reswchar.wchar , reswchar.wlen , reswchar.wsize , "locale" , 0 , 2 );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( reswchar.wsize , 6 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 5 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"loale" ) == 0 );


		::booldog::utils::string::mbs::insert( &res , &allocator , true , 2 , reswchar.wchar , reswchar.wlen , reswchar.wsize , "locale" , 2 , 1 );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( reswchar.wsize , 7 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 6 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"locale" ) == 0 );
	}



	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::tombs( &resmbchar , &allocator , L"locale" , 0 , SIZE_MAX );
		
		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 7 );

		ASSERT_EQ( resmbchar.mblen , 6 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "locale" ) == 0 );
	}

	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::tombs( &resmbchar , &allocator , L"locale" , 3 , SIZE_MAX );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 4 );

		ASSERT_EQ( resmbchar.mblen , 3 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "ale" ) == 0 );
	}

	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::tombs( &resmbchar , &allocator , L"locale" , 3 , 2 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 3 );

		ASSERT_EQ( resmbchar.mblen , 2 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "al" ) == 0 );
	}

	{
		::booldog::result_mbchar resmbchar( &allocator );

		::booldog::utils::string::wcs::tombs( &resmbchar , &allocator , L"locale" , 3 , 2 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 3 );

		ASSERT_EQ( resmbchar.mblen , 2 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "al" ) == 0 );

		::booldog::result res;

		::booldog::utils::string::wcs::insert( &res , &allocator , true , 2 , resmbchar.mbchar , resmbchar.mblen , resmbchar.mbsize , L"e" , 0 , SIZE_MAX );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 4 );

		ASSERT_EQ( resmbchar.mblen , 3 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "ale" ) == 0 );


		::booldog::utils::string::wcs::insert( &res , &allocator , true , 0 , resmbchar.mbchar , resmbchar.mblen , resmbchar.mbsize , L"locale" , 0 , 2 );

		ASSERT_TRUE( res.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 6 );

		ASSERT_EQ( resmbchar.mblen , 5 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "loale" ) == 0 );


		::booldog::utils::string::wcs::insert( &res , &allocator , true , 2 , resmbchar.mbchar , resmbchar.mblen , resmbchar.mbsize , L"locale" , 2 , 1 );

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
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{
		::booldog::array< const wchar_t* > wcs_array( &allocator );

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
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{
		::booldog::string item0( &allocator , "TEST0" );

		::booldog::string item1( &allocator , "TEST1" );

		::booldog::string item2( &allocator , "TEST2" );

		::booldog::list< ::booldog::string > string_array( &allocator );

		::booldog::list< ::booldog::object > object_array( &allocator );


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
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();


	::booldog::object obj( &allocator );

	::booldog::string str( &allocator );

	::booldog::list< ::booldog::string > str_array( &allocator );

	::booldog::list< ::booldog::object > obj_array( &allocator );

	::booldog::list< ::booldog::list< ::booldog::object > > obj_array_array( &allocator );

	::booldog::list< ::booldog::list< ::booldog::string > > str_array_array( &allocator );


	ASSERT_TRUE( allocator.begin() == begin );
		
	ASSERT_EQ( allocator.available() , total );
};


class boo_checkTest : public ::testing::Test 
{
};
TEST_F( boo_checkTest , test )
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
	::booldog::allocators::stack< 4096 > allocator;

	size_t total = allocator.available();

	char* begin = (char*)allocator.begin();

	{

		const wchar_t* wtest = L"C:/privet\\../gui.exe\\./..\\ui.exe";
		const char* mbtest = "C:/privet\\../gui.exe\\./..\\ui.exe";

		const wchar_t* wtest2 = L"C:/privet\\../gui.exe\\./..\\ui";
		const char* mbtest2 = "C:/privet\\../gui.exe\\./..\\ui";

		::booldog::result_wchar reswchar( &allocator );
	
		::booldog::utils::io::path::wcs::filename( &reswchar , &allocator , wtest );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 7 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 6 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"ui.exe" ) == 0 );

		::booldog::utils::io::path::wcs::filename( &reswchar , &allocator , wtest , 3 , 17 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 8 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 7 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"gui.exe" ) == 0 );


		::booldog::utils::io::path::wcs::directory( &reswchar , &allocator , wtest );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 26 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 25 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"C:/privet\\../gui.exe\\./.." ) == 0 );

		::booldog::utils::io::path::wcs::directory( &reswchar , &allocator , wtest , 3 , 17 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 10 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 9 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"privet\\.." ) == 0 );


		::booldog::utils::io::path::wcs::extension( &reswchar , &allocator , wtest );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 4 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 3 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"exe" ) == 0 );

		::booldog::utils::io::path::wcs::extension( &reswchar , &allocator , wtest , 3 , 16 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 3 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 2 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"ex" ) == 0 );

		::booldog::utils::io::path::wcs::extension( &reswchar , &allocator , wtest2 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 1 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 0 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::result_mbchar resmbchar( &allocator );
	
		::booldog::utils::io::path::mbs::filename( &resmbchar , &allocator , mbtest );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 7 );

		ASSERT_EQ( resmbchar.mblen , 6 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "ui.exe" ) == 0 );

		::booldog::utils::io::path::mbs::filename( &resmbchar , &allocator , mbtest , 3 , 17 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 8 );

		ASSERT_EQ( resmbchar.mblen , 7 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "gui.exe" ) == 0 );


		::booldog::utils::io::path::mbs::directory( &resmbchar , &allocator , mbtest );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 26 );

		ASSERT_EQ( resmbchar.mblen , 25 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "C:/privet\\../gui.exe\\./.." ) == 0 );

		::booldog::utils::io::path::mbs::directory( &resmbchar , &allocator , mbtest , 3 , 17 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 10 );

		ASSERT_EQ( resmbchar.mblen , 9 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "privet\\.." ) == 0 );


		::booldog::utils::io::path::mbs::extension( &resmbchar , &allocator , mbtest );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 4 );

		ASSERT_EQ( resmbchar.mblen , 3 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "exe" ) == 0 );

		::booldog::utils::io::path::mbs::extension( &resmbchar , &allocator , mbtest , 3 , 16 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 3 );

		ASSERT_EQ( resmbchar.mblen , 2 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "ex" ) == 0 );

		::booldog::utils::io::path::mbs::extension( &resmbchar , &allocator , mbtest2 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 1 );

		ASSERT_EQ( resmbchar.mblen , 0 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"home\\kill/." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 12 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 9 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"home\\./.\\kill/." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 16 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 9 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"./home\\./.\\kill/." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 18 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 9 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"./home/try\\explain\\./.\\../..\\kill/." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 36 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 9 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"./home/try\\explain\\./.\\../..\\kill/joke\\.." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 42 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 9 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"home\\kill" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"/home/.." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 9 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 0 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L".\\" );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 3 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 0 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"." );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 2 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 0 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"home\\./\\.\\kill/." );

		ASSERT_FALSE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( reswchar.booerror , ::booldog::enums::result::booerr_type_path_has_incorrect_format );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"./.\\../kill/." );

		ASSERT_FALSE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( reswchar.booerror , ::booldog::enums::result::booerr_type_not_enough_top_level_folders );


		::booldog::utils::io::path::wcs::toabsolute( &reswchar , &allocator , L"../local" );

		ASSERT_FALSE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( reswchar.booerror , ::booldog::enums::result::booerr_type_not_enough_top_level_folders );



		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "home\\kill/." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 12 );

		ASSERT_EQ( resmbchar.mblen , 9 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "home\\./.\\kill/." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 16 );

		ASSERT_EQ( resmbchar.mblen , 9 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "./home\\./.\\kill/." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 18 );

		ASSERT_EQ( resmbchar.mblen , 9 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "./home/try\\explain\\./.\\../..\\kill/." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 36 );

		ASSERT_EQ( resmbchar.mblen , 9 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "./home/try\\explain\\./.\\../..\\kill/joke\\.." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 42 );

		ASSERT_EQ( resmbchar.mblen , 9 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "home\\kill" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "/home/.." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 9 );

		ASSERT_EQ( resmbchar.mblen , 0 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , ".\\" );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 3 );

		ASSERT_EQ( resmbchar.mblen , 0 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "." );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 2 );

		ASSERT_EQ( resmbchar.mblen , 0 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "home\\./\\.\\kill/." );

		ASSERT_FALSE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resmbchar.booerror , ::booldog::enums::result::booerr_type_path_has_incorrect_format );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "./.\\../kill/." );

		ASSERT_FALSE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.get_error_type() , ::booldog::enums::result::error_type_booerr );

		ASSERT_EQ( resmbchar.booerror , ::booldog::enums::result::booerr_type_not_enough_top_level_folders );


		::booldog::utils::io::path::mbs::toabsolute( &resmbchar , &allocator , "../local" );

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


	
		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"" );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 1 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 0 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"core" );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 4 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"\\home/core" );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 4 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"\\home/core.dll.exe" );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 9 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 8 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"core.dll" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"\\home/.core" );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 1 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 0 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"\\home/.core" , 7 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 4 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"\\home/.core.dll.exe" , 7 , 8 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 4 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );


		::booldog::utils::io::path::wcs::filename_without_extension( &reswchar , &allocator , L"\\home/.core.dll.exe" , 7 , 9 );

		ASSERT_TRUE( reswchar.succeeded() );

		ASSERT_EQ( reswchar.wsize , 9 * sizeof( wchar_t ) );

		ASSERT_EQ( reswchar.wlen , 8 );

		ASSERT_TRUE( wcscmp( reswchar.wchar , L"core.dll" ) == 0 );



		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "" );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 1 );

		ASSERT_EQ( resmbchar.mblen , 0 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "core" );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 5 );

		ASSERT_EQ( resmbchar.mblen , 4 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "\\home/core" );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 5 );

		ASSERT_EQ( resmbchar.mblen , 4 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "\\home/core.dll.exe" );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 9 );

		ASSERT_EQ( resmbchar.mblen , 8 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "core.dll" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "\\home/.core" );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 1 );

		ASSERT_EQ( resmbchar.mblen , 0 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "\\home/.core" , 7 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 5 );

		ASSERT_EQ( resmbchar.mblen , 4 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "\\home/.core.dll.exe" , 7 , 8 );

		ASSERT_TRUE( resmbchar.succeeded() );

		ASSERT_EQ( resmbchar.mbsize , 5 );

		ASSERT_EQ( resmbchar.mblen , 4 );

		ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );


		::booldog::utils::io::path::mbs::filename_without_extension( &resmbchar , &allocator , "\\home/.core.dll.exe" , 7 , 9 );

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

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "" , 0 , SIZE_MAX );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 1 );

			ASSERT_EQ( resmbchar.mblen , 0 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "core" , 0 , SIZE_MAX );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 5 );

			ASSERT_EQ( resmbchar.mblen , 4 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "core.dll.exe" , 0 , SIZE_MAX );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 9 );

			ASSERT_EQ( resmbchar.mblen , 8 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "core.dll" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , ".core" , 0 , SIZE_MAX );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 1 );

			ASSERT_EQ( resmbchar.mblen , 0 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "core." , 0 , SIZE_MAX );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 5 );

			ASSERT_EQ( resmbchar.mblen , 4 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "/home.exe\\core" , 0 , SIZE_MAX );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 15 );

			ASSERT_EQ( resmbchar.mblen , 14 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "/home.exe\\core" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "/home.exe\\core.dll" , 9 , 4 );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 5 );

			ASSERT_EQ( resmbchar.mblen , 4 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "\\cor" ) == 0 );
		}

		{

			::booldog::utils::io::path::mbs::pathname_without_extension( &resmbchar , &allocator , "/home.exe\\core.dll" , 1 , 6 );

			ASSERT_TRUE( resmbchar.succeeded() );

			ASSERT_EQ( resmbchar.mbsize , 5 );

			ASSERT_EQ( resmbchar.mblen , 4 );

			ASSERT_TRUE( strcmp( resmbchar.mbchar , "home" ) == 0 );
		}


		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"" , 0 , SIZE_MAX );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 1 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 0 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"core" , 0 , SIZE_MAX );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 4 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"core.dll.exe" , 0 , SIZE_MAX );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 9 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 8 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"core.dll" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L".core" , 0 , SIZE_MAX );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 1 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 0 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"core." , 0 , SIZE_MAX );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 4 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"/home.exe\\core" , 0 , SIZE_MAX );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 15 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 14 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"/home.exe\\core" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"/home.exe\\core.dll" , 9 , 4 );

			ASSERT_TRUE( reswchar.succeeded() );

			ASSERT_EQ( reswchar.wsize , 5 * sizeof( wchar_t ) );

			ASSERT_EQ( reswchar.wlen , 4 );

			ASSERT_TRUE( wcscmp( reswchar.wchar , L"\\cor" ) == 0 );
		}

		{

			::booldog::utils::io::path::wcs::pathname_without_extension( &reswchar , &allocator , L"/home.exe\\core.dll" , 1 , 6 );

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

				ASSERT_TRUE( res.succeeded() );

				ASSERT_EQ( resmbchar.mblen , 12 );

				ASSERT_TRUE( strcmp( resmbchar.mbchar , "booldog.test" ) == 0 );
			}
		}
		{
			::booldog::result_wchar reswchar( &allocator );
			::booldog::utils::executable::wcs::pathname< 4 >( &reswchar , &allocator );
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

		loader.wcsload( &res , &allocator , L"core1" , load_params );

		ASSERT_FALSE( res.succeeded() );

		loader.wcsload( &res , &allocator , L"core" , load_params );
		
		ASSERT_TRUE( res.succeeded() );

		::booldog::base::module* module0 = res.module;

		loader.wcsload( &res , &allocator , L"core" , 0 );

		ASSERT_TRUE( res.succeeded() );

		::booldog::base::module* module1 = res.module;

		{
			::booldog::result_mbchar resmbchar( &allocator );
			::booldog::utils::module::mbs::pathname< 4 >( &resmbchar , &allocator , module1->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::mbs::filename_without_extension( &res , resmbchar.mbchar , resmbchar.mblen );

				ASSERT_TRUE( res.succeeded() );
#ifdef __WINDOWS__
				ASSERT_EQ( resmbchar.mblen , 4 );

				ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );
#else
				ASSERT_EQ( resmbchar.mblen , 7 );

				ASSERT_TRUE( strcmp( resmbchar.mbchar , "libcore" ) == 0 );
#endif
			}
		}
		{
			::booldog::result_wchar reswchar( &allocator );
			::booldog::utils::module::wcs::pathname< 4 >( &reswchar , &allocator , module1->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::wcs::filename_without_extension( &res , reswchar.wchar , reswchar.wlen );

				ASSERT_TRUE( res.succeeded() );
#ifdef __WINDOWS__
				ASSERT_EQ( reswchar.wlen , 4 );

				ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );
#else
				ASSERT_EQ( reswchar.wlen , 7 );

				ASSERT_TRUE( wcscmp( reswchar.wchar , L"libcore" ) == 0 );
#endif
			}
		}


		::booldog::result resres;
		loader.unload( &resres , module0 );

		ASSERT_TRUE( res.succeeded() );

		loader.unload( &resres , module1 );

		ASSERT_TRUE( res.succeeded() );

#ifdef __WINDOWS__
		loader.wcsload( &res , &allocator , L"kernel32" , 0 );
#else
		loader.wcsload( &res , &allocator , L"rt" , 0 );
#endif

		ASSERT_TRUE( res.succeeded() );

		::booldog::base::module* module2 = res.module;

		{
			::booldog::result_mbchar resmbchar( &allocator );
			::booldog::utils::module::mbs::pathname< 4 >( &resmbchar , &allocator , module2->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::mbs::filename_without_extension( &res , resmbchar.mbchar , resmbchar.mblen );

				ASSERT_TRUE( res.succeeded() );
#ifdef __WINDOWS__
				ASSERT_EQ( resmbchar.mblen , 8 );

				ASSERT_TRUE( strcmp( resmbchar.mbchar , "kernel32" ) == 0 );
#else
				ASSERT_EQ( resmbchar.mblen , 8 );

				ASSERT_TRUE( strcmp( resmbchar.mbchar , "librt.so" ) == 0 );
#endif
			}
		}
		{
			::booldog::result_wchar reswchar( &allocator );
			::booldog::utils::module::wcs::pathname< 4 >( &reswchar , &allocator , module2->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::wcs::filename_without_extension( &res , reswchar.wchar , reswchar.wlen );

				ASSERT_TRUE( res.succeeded() );
#ifdef __WINDOWS__
				ASSERT_EQ( reswchar.wlen , 8 );

				ASSERT_TRUE( wcscmp( reswchar.wchar , L"kernel32" ) == 0 );
#else
				ASSERT_EQ( reswchar.wlen , 8 );

				ASSERT_TRUE( wcscmp( reswchar.wchar , L"librt.so" ) == 0 );
#endif
			}
		}

		loader.unload( &resres , module2 );

		ASSERT_TRUE( res.succeeded() );



		loader.mbsload( &res , &allocator , "core1" , load_params );

		ASSERT_FALSE( res.succeeded() );

		loader.mbsload( &res , &allocator , "core" , load_params );

		ASSERT_TRUE( res.succeeded() );

		module0 = res.module;

		loader.mbsload( &res , &allocator , "core" , 0 );

		ASSERT_TRUE( res.succeeded() );	

		module1 = res.module;

		{
			::booldog::result_mbchar resmbchar( &allocator );
			::booldog::utils::module::mbs::pathname< 4 >( &resmbchar , &allocator , module1->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::mbs::filename_without_extension( &res , resmbchar.mbchar , resmbchar.mblen );

				ASSERT_TRUE( res.succeeded() );
#ifdef __WINDOWS__
				ASSERT_EQ( resmbchar.mblen , 4 );

				ASSERT_TRUE( strcmp( resmbchar.mbchar , "core" ) == 0 );
#else
				ASSERT_EQ( resmbchar.mblen , 7 );

				ASSERT_TRUE( strcmp( resmbchar.mbchar , "libcore" ) == 0 );
#endif
			}
		}
		{
			::booldog::result_wchar reswchar( &allocator );
			::booldog::utils::module::wcs::pathname< 4 >( &reswchar , &allocator , module1->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::wcs::filename_without_extension( &res , reswchar.wchar , reswchar.wlen );

				ASSERT_TRUE( res.succeeded() );
#ifdef __WINDOWS__
				ASSERT_EQ( reswchar.wlen , 4 );

				ASSERT_TRUE( wcscmp( reswchar.wchar , L"core" ) == 0 );
#else
				ASSERT_EQ( reswchar.wlen , 7 );

				ASSERT_TRUE( wcscmp( reswchar.wchar , L"libcore" ) == 0 );
#endif
			}
		}

		loader.unload( &resres , module0 );

		ASSERT_TRUE( res.succeeded() );

		loader.unload( &resres , module1 );

		ASSERT_TRUE( res.succeeded() );
#ifdef __WINDOWS__
		loader.mbsload( &res , &allocator , "kernel32" , 0 );
#else
		loader.mbsload( &res , &allocator , "rt" , 0 );
#endif

		ASSERT_TRUE( res.succeeded() );

		module2 = res.module;
		{
			::booldog::result_mbchar resmbchar( &allocator );
			::booldog::utils::module::mbs::pathname< 4 >( &resmbchar , &allocator , module2->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::mbs::filename_without_extension( &res , resmbchar.mbchar , resmbchar.mblen );

				ASSERT_TRUE( res.succeeded() );
#ifdef __WINDOWS__
				ASSERT_EQ( resmbchar.mblen , 8 );

				ASSERT_TRUE( strcmp( resmbchar.mbchar , "kernel32" ) == 0 );
#else
				ASSERT_EQ( resmbchar.mblen , 8 );

				ASSERT_TRUE( strcmp( resmbchar.mbchar , "librt.so" ) == 0 );
#endif
			}
		}
		{
			::booldog::result_wchar reswchar( &allocator );
			::booldog::utils::module::wcs::pathname< 4 >( &reswchar , &allocator , module2->handle() );
			{
				::booldog::result res;

				::booldog::utils::io::path::wcs::filename_without_extension( &res , reswchar.wchar , reswchar.wlen );

				ASSERT_TRUE( res.succeeded() );
#ifdef __WINDOWS__
				ASSERT_EQ( reswchar.wlen , 8 );

				ASSERT_TRUE( wcscmp( reswchar.wchar , L"kernel32" ) == 0 );
#else
				ASSERT_EQ( reswchar.wlen , 8 );

				ASSERT_TRUE( wcscmp( reswchar.wchar , L"librt.so" ) == 0 );
#endif
			}
		}		
		loader.unload( &resres , module2 );

		ASSERT_TRUE( res.succeeded() );
		

		loader.mbsload( &res , &allocator , "core" , load_params );

		ASSERT_TRUE( res.succeeded() );

		module0 = res.module;


		loader.mbsload( &res , &allocator , "language" , load_params );

		/*char* errorstr = 0;
		size_t errorstrlen = 0 , errorstrsize = 0;
		::booldog::error::format( &res , errorstr , errorstrlen , errorstrsize );
		printf( "error %s\n" , errorstr );*/

		ASSERT_TRUE( res.succeeded() );

		module2 = res.module;

		::booldog::result_pointer respointer;
		::booldog::utils::module::mbs::method( &respointer , &allocator , module2->handle() , "core_init" );

		ASSERT_FALSE( respointer.succeeded() );

		::booldog::utils::module::mbs::method( &respointer , &allocator , module2->handle() , "dll_init" );

		ASSERT_TRUE( respointer.succeeded() );

		
		::booldog::module_handle modhandle = ::booldog::utils::module::handle( &resres , &allocator , respointer.pres , 
			debuginfo_macros );

		ASSERT_TRUE( resres.succeeded() );

		ASSERT_TRUE( modhandle != 0 );

		ASSERT_TRUE( modhandle == module2->handle() );

		::booldog::utils::module::free( &resres , &allocator , modhandle , debuginfo_macros );

		ASSERT_TRUE( resres.succeeded() );

		{
			::booldog::result_mbchar resmbchar( &allocator );
			::booldog::utils::module::mbs::pathname< 4 >( &resmbchar , &allocator , respointer.pres , debuginfo_macros );

			ASSERT_TRUE( resmbchar.succeeded() );

			{
				::booldog::result res;

				::booldog::utils::io::path::mbs::filename_without_extension( &res , resmbchar.mbchar , resmbchar.mblen );

				ASSERT_TRUE( res.succeeded() );
#ifdef __WINDOWS__
				ASSERT_EQ( resmbchar.mblen , 8 );

				ASSERT_TRUE( strcmp( resmbchar.mbchar , "language" ) == 0 );
#else
				ASSERT_EQ( resmbchar.mblen , 11 );

				ASSERT_TRUE( strcmp( resmbchar.mbchar , "liblanguage" ) == 0 );
#endif
			}
		}

		{
			::booldog::result_wchar reswchar( &allocator );
			::booldog::utils::module::wcs::pathname< 4 >( &reswchar , &allocator , respointer.pres , debuginfo_macros );

			ASSERT_TRUE( reswchar.succeeded() );

			{
				::booldog::result res;

				::booldog::utils::io::path::wcs::filename_without_extension( &res , reswchar.wchar , reswchar.wlen );

				ASSERT_TRUE( res.succeeded() );
#ifdef __WINDOWS__
				ASSERT_EQ( reswchar.wlen , 8 );

				ASSERT_TRUE( wcscmp( reswchar.wchar , L"language" ) == 0 );
#else
				ASSERT_EQ( reswchar.wlen , 11 );

				ASSERT_TRUE( wcscmp( reswchar.wchar , L"liblanguage" ) == 0 );
#endif
			}
		}
		

		loader.unload( &resres , module2 );

		ASSERT_TRUE( resres.succeeded() );


		loader.unload( &resres , module0 );

		ASSERT_TRUE( resres.succeeded() );
	}

	ASSERT_TRUE( allocator.begin() == begin );

	ASSERT_EQ( allocator.available() , total );
};
class boo_io_fileTest : public ::testing::Test 
{
};
TEST_F( boo_io_fileTest , test )
{
	::booldog::allocators::easy::heap heap;
	::booldog::allocators::mixed< 16 * 1024 > allocator( &heap , ::booldog::threading::thread_id() );
	
	size_t total = allocator.stack.available();

	char* begin = (char*)allocator.stack.begin();
	{
		::booldog::result_buffer resbuf( &allocator );
		::booldog::result_file res;

		booldog::param search_paths_params[] =
		{
			BOOPARAM_PCHAR( "../../test_data\\modules0/x86" ) ,
			BOOPARAM_PWCHAR( L"..\\../test_data\\modules1\\x86" ) ,
			BOOPARAM_PCHAR( "../../test_data\\json" ) ,
			BOOPARAM_NONE
		};
		booldog::named_param load_params[] =
		{
			BOONAMED_PARAM_PPARAM( "search_paths" , search_paths_params ) ,
			BOONAMED_PARAM_BOOL( "exedir_as_root_path" , true ) ,
			BOONAMED_PARAM_NONE
		};
		::booldog::io::file::mbsopen( &res , &allocator , "core1" , ::booldog::enums::io::file_mode_read , load_params );

		ASSERT_FALSE( res.succeeded() );

		::booldog::io::file::mbsopen( &res , &allocator , "core.dll" , ::booldog::enums::io::file_mode_read , load_params );
		
		ASSERT_TRUE( res.succeeded() );

		res.file->close( &res );

		ASSERT_TRUE( res.succeeded() );


		::booldog::io::file::mbsopen( &res , &allocator , "json_test2.txt" , ::booldog::enums::io::file_mode_read , load_params );
		
		ASSERT_TRUE( res.succeeded() );

		res.file->readall< 16 * 1024 >( &resbuf , &allocator , debuginfo_macros );

		ASSERT_TRUE( resbuf.succeeded() );

		ASSERT_TRUE( resbuf.buf[ 0 ] == '[' );

		res.file->close( &res );

		ASSERT_TRUE( res.succeeded() );
	}

	ASSERT_TRUE( allocator.stack.begin() == begin );

	ASSERT_EQ( allocator.stack.available() , total );

	ASSERT_EQ( allocator.heap->size_of_allocated_memory() , 0 );
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