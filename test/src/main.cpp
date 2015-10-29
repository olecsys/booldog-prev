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
char cp1251_test0[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , 0 
};
char utf8_test0[] = 
{
	test_Apr_utf8 , test_il_utf8 , 0
};
char utf16_test0[] = 
{
	test_Apr_utf16 , test_il_utf16 , 0 , 0
};
char utf32_test0[] = 
{
	test_Apr_utf32 , test_il_utf32 , 0 , 0 , 0 , 0
};


char cp1251_test1[] = 
{
	test_Apr_cp1251 , 0 
};
char utf8_test1[] = 
{
	test_Apr_utf8 , 0
};
char utf16_test1[] = 
{
	test_Apr_utf16 , 0 , 0
};

char cp1251_test2[] = 
{
	test_il_cp1251 , 0 
};
char utf8_test2[] = 
{
	test_il_utf8 , 0
};
char utf16_test2[] = 
{
	test_il_utf16 , 0 , 0
};

char cp1251_test3[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_il_cp1251 , 0 
};
char utf8_test3[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_il_utf8 , 0
};
char utf16_test3[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_il_utf16 , 0 , 0
};

char cp1251_test4[] = 
{
	test_il_cp1251 , test_il_cp1251 , 0 
};
char utf8_test4[] = 
{
	test_il_utf8 , test_il_utf8 , 0
};
char utf16_test4[] = 
{
	test_il_utf16 , test_il_utf16 , 0 , 0
};

char cp1251_test5[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_il_cp1251 , test_il_cp1251 , 0 
};
char utf8_test5[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_il_utf8 , test_il_utf8 , 0
};
char utf16_test5[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_il_utf16 , test_il_utf16 , 0 , 0
};

char cp1251_test6[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , 0 
};
char utf8_test6[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , 0
};
char utf16_test6[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , 0 , 0
};

char cp1251_test7[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , 0 
};
char utf8_test7[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , 0 
};
char utf16_test7[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , 0 
};

char cp1251_test8[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , 0 
};
char utf8_test8[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , 0
};
char utf16_test8[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , 0 , 0
};

char cp1251_test9[] = 
{
	test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , 0 
};
char utf8_test9[] = 
{
	test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , 0
};
char utf16_test9[] = 
{
	test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , 0 , 0
};

char cp1251_test10[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , 0 
};
char utf8_test10[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , 0
};
char utf16_test10[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , 0 , 0
};

char cp1251_test11[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_il_cp1251 , test_Apr_cp1251 , 0 
};
char utf8_test11[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_il_utf8 , test_Apr_utf8 , 0
};
char utf16_test11[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_il_utf16 , test_Apr_utf16 , 0 , 0
};

char cp1251_test12[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_il_cp1251 , test_Apr_cp1251 , 0 
};
char utf8_test12[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_il_utf8 , test_Apr_utf8 , 0
};
char utf16_test12[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_il_utf16 , test_Apr_utf16 , 0 , 0
};

char cp1251_test13[] = 
{
	test_rpr_cp1251 , test_il_cp1251 , test_rpr_cp1251 , test_il_cp1251 , test_rpr_cp1251 , 0 
};
char utf8_test13[] = 
{
	test_rpr_utf8 , test_il_utf8 , test_rpr_utf8 , test_il_utf8 , test_rpr_utf8 , 0
};
char utf16_test13[] = 
{
	test_rpr_utf16 , test_il_utf16 , test_rpr_utf16 , test_il_utf16 , test_rpr_utf16 , 0 , 0
};

char cp1251_test14[] = 
{
	test_rpr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , 0 
};
char utf8_test14[] = 
{
	test_rpr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , 0
};
char utf16_test14[] = 
{
	test_rpr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , 0 , 0
};

char cp1251_test15[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_rpr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , 0 
};
char utf8_test15[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_rpr_utf8 , test_il_utf8 , test_Apr_utf8 , 0
};
char utf16_test15[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_rpr_utf16 , test_il_utf16 , test_Apr_utf16 , 0 , 0
};

char cp1251_test16[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_rpr_cp1251 , test_il_cp1251 , test_rpr_cp1251 , 0 
};
char utf8_test16[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_rpr_utf8 , test_il_utf8 , test_rpr_utf8 , 0
};
char utf16_test16[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_rpr_utf16 , test_il_utf16 , test_rpr_utf16 , 0 , 0
};

char cp1251_test17[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_rpr_cp1251 , 0 
};
char utf8_test17[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_rpr_utf8 , 0
};
char utf16_test17[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_rpr_utf16 , 0 , 0
};

char cp1251_test18[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , 0 
};
char utf8_test18[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , 0
};
char utf16_test18[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , 0 , 0
};

char cp1251_test19[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , 0 
};
char utf8_test19[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , 0
};
char utf16_test19[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , 0 , 0
};

char cp1251_test20[] = 
{
	test_rpr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , 0 
};
char utf8_test20[] = 
{
	test_rpr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , 0
};
char utf16_test20[] = 
{
	test_rpr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , 0 , 0
};

char cp1251_test21[] = 
{
	test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , 0 
};
char utf8_test21[] = 
{
	test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , 0
};
char utf16_test21[] = 
{
	test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , 0 , 0
};

char cp1251_test22[] = 
{
	test_Apr_cp1251 , test_il_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , 0 
};
char utf8_test22[] = 
{
	test_Apr_utf8 , test_il_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , 0
};
char utf16_test22[] = 
{
	test_Apr_utf16 , test_il_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , 0 , 0
};

char cp1251_test23[] = 
{
	test_0Apr_cp1251 , test_il_cp1251 , 0 
};
char utf8_test23[] = 
{
	test_0Apr_utf8 , test_il_utf8 , 0
};
char utf16_test23[] = 
{
	test_0Apr_utf16 , test_il_utf16 , 0 , 0
};

char cp1251_test24[] = 
{
	test_Apr_cp1251 , test_0il_cp1251 , 0 
};
char utf8_test24[] = 
{
	test_Apr_utf8 , test_0il_utf8 , 0
};
char utf16_test24[] = 
{
	test_Apr_utf16 , test_0il_utf16 , 0 , 0
};

char cp1251_test25[] = 
{
	test_Apr_cp1251 , test_il0_cp1251 , 0 
};
char utf8_test25[] = 
{
	test_Apr_utf8 , test_il0_utf8 , 0
};
char utf16_test25[] = 
{
	test_Apr_utf16 , test_il0_utf16 , 0 , 0
};

char cp1251_test26[] = 
{
	test_0Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , 0 
};
char utf8_test26[] = 
{
	test_0Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , 0
};
char utf16_test26[] = 
{
	test_0Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , 0 , 0
};

char cp1251_test27[] = 
{
	test_0Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , test_Apr_cp1251 , test_il_cp1251 , 0 
};
char utf8_test27[] = 
{
	test_0Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , test_Apr_utf8 , test_il_utf8 , 0
};
char utf16_test27[] = 
{
	test_0Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , test_Apr_utf16 , test_il_utf16 , 0 , 0
};
/*
class StringTest : public ::testing::Test 
{
};
TEST_F( StringTest , Convert ) 
{
	{
		{
			::booldog::XString res_str;
			{
				::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );
			
				res_str.set_ByRef( str0.ConvertToAnsi() );
				if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
				{
					ASSERT_TRUE( memcmp( res_str.str() , cp1251_test0 , sizeof( cp1251_test0 ) ) == 0 );

					ASSERT_TRUE( res_str.Length() == 6 );
				}
				else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
				{
					ASSERT_TRUE( memcmp( res_str.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );

					ASSERT_TRUE( res_str.Length() == 6 );
				}				
			
				res_str.set_ByRef( str0.ConvertToUTF8() );

				ASSERT_TRUE( memcmp( res_str.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );

				ASSERT_TRUE( res_str.Length() == 6 );

				res_str.set_ByRef( str0.ConvertToUTF16() );

				ASSERT_TRUE( memcmp( res_str.str() , utf16_test0 , sizeof( utf16_test0 ) ) == 0 );

				ASSERT_TRUE( res_str.Length() == 6 );
			}

			{
				::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
			
				res_str.set_ByRef( str0.ConvertToAnsi() );
				if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
				{
					ASSERT_TRUE( memcmp( res_str.str() , cp1251_test0 , sizeof( cp1251_test0 ) ) == 0 );

					ASSERT_TRUE( res_str.Length() == 6 );
				}
				else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
				{
					ASSERT_TRUE( memcmp( res_str.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );

					ASSERT_TRUE( res_str.Length() == 6 );
				}				
			
				res_str.set_ByRef( str0.ConvertToUTF8() );

				ASSERT_TRUE( memcmp( res_str.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );

				ASSERT_TRUE( res_str.Length() == 6 );

				res_str.set_ByRef( str0.ConvertToUTF16() );

				ASSERT_TRUE( memcmp( res_str.str() , utf16_test0 , sizeof( utf16_test0 ) ) == 0 );

				ASSERT_TRUE( res_str.Length() == 6 );
			}

			{
				::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
			
				res_str.set_ByRef( str0.ConvertToAnsi() );
				if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
				{
					ASSERT_TRUE( memcmp( res_str.str() , cp1251_test0 , sizeof( cp1251_test0 ) ) == 0 );

					ASSERT_TRUE( res_str.Length() == 6 );
				}
				else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
				{
					ASSERT_TRUE( memcmp( res_str.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );

					ASSERT_TRUE( res_str.Length() == 6 );
				}				
			
				res_str.set_ByRef( str0.ConvertToUTF8() );

				ASSERT_TRUE( memcmp( res_str.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );

				ASSERT_TRUE( res_str.Length() == 6 );

				res_str.set_ByRef( str0.ConvertToUTF16() );

				ASSERT_TRUE( memcmp( res_str.str() , utf16_test0 , sizeof( utf16_test0 ) ) == 0 );

				ASSERT_TRUE( res_str.Length() == 6 );
			}
		}
	}
};

TEST_F( StringTest , Substring ) 
{
	{
		{
			::booldog::XString res_str;
			{
				::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );
			
				res_str.set_ByRef( str0.Substring( 3 ) );
				
				ASSERT_TRUE( memcmp( res_str.str() , cp1251_test2 , sizeof( cp1251_test2 ) ) == 0 );
				
				ASSERT_TRUE( res_str.Length() == 3 );

				res_str.set_ByRef( str0.Substring( 0 , 3 ) );
				
				ASSERT_TRUE( memcmp( res_str.str() , cp1251_test1 , sizeof( cp1251_test1 ) ) == 0 );
				
				ASSERT_TRUE( res_str.Length() == 3 );			
			}

			{
				::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
			
				res_str.set_ByRef( str0.Substring( 3 ) );
				
				ASSERT_TRUE( memcmp( res_str.str() , utf8_test2 , sizeof( utf8_test2 ) ) == 0 );
				
				ASSERT_TRUE( res_str.Length() == 3 );

				res_str.set_ByRef( str0.Substring( 0 , 3 ) );
				
				ASSERT_TRUE( memcmp( res_str.str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
				
				ASSERT_TRUE( res_str.Length() == 3 );
			}

			{
				::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
			
				res_str.set_ByRef( str0.Substring( 3 ) );
				
				ASSERT_TRUE( memcmp( res_str.str() , utf16_test2 , sizeof( utf16_test2 ) ) == 0 );
				
				ASSERT_TRUE( res_str.Length() == 3 );

				res_str.set_ByRef( str0.Substring( 0 , 3 ) );
				
				ASSERT_TRUE( memcmp( res_str.str() , utf16_test1 , sizeof( utf16_test1 ) ) == 0 );
				
				ASSERT_TRUE( res_str.Length() == 3 );
			}
		}
	}
};

TEST_F( StringTest , ReplaceAll ) 
{
	{
		{
			::booldog::XString res_str;
			{
				::booldog::XString str0( cp1251_test6 , 0 , XEnumCodePage_CP1251 );
				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceAll( (char)-64 , (char)-16 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , cp1251_test13 , sizeof( cp1251_test13 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , cp1251_test4 , sizeof( cp1251_test4 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 6 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , cp1251_test7 , sizeof( cp1251_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test7 , sizeof( utf16_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test4 , sizeof( utf8_test4 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 6 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test4 , sizeof( utf16_test4 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 6 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test7 , sizeof( utf16_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test7 , sizeof( utf16_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}
				}
			}

			{
				::booldog::XString str0( utf16_test6 , 0 , XEnumCodePage_UTF16 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceAll( (char)-64 , (char)-16 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , utf16_test13 , sizeof( utf16_test13 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test4 , sizeof( utf16_test4 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 6 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test7 , sizeof( utf16_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test7 , sizeof( utf16_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test4 , sizeof( utf8_test4 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 6 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test4 , sizeof( utf16_test4 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 6 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test7 , sizeof( utf16_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test7 , sizeof( utf16_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}
				}
			}

			{
				::booldog::XString str0( utf8_test6 , 0 , XEnumCodePage_UTF8 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceAll( (char)-64 , (char)-16 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , utf8_test13 , sizeof( utf8_test13 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test4 , sizeof( utf8_test4 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 6 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test4 , sizeof( utf8_test4 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 6 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test4 , sizeof( utf8_test4 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 6 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test7 , sizeof( utf8_test7 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 24 );
					}
				}
			}	



			{
				::booldog::XString str0( cp1251_test6 , 0 , XEnumCodePage_CP1251 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceAll( (char)-64 , (char)-16 , 4 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , cp1251_test16 , sizeof( cp1251_test16 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , cp1251_test3 , sizeof( cp1251_test3 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 9 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , cp1251_test8 , sizeof( cp1251_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test8 , sizeof( utf16_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 9 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test3 , sizeof( utf16_test3 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 9 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test8 , sizeof( utf16_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test8 , sizeof( utf16_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}
				}
			}

			{
				::booldog::XString str0( utf16_test6 , 0 , XEnumCodePage_UTF16 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceAll( (char)-64 , (char)-16 , 4 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , utf16_test16 , sizeof( utf16_test16 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test3 , sizeof( utf16_test3 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 9 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test8 , sizeof( utf16_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test8 , sizeof( utf16_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 9 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test3 , sizeof( utf16_test3 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 9 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test8 , sizeof( utf16_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test8 , sizeof( utf16_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}
				}
			}

			{
				::booldog::XString str0( utf8_test6 , 0 , XEnumCodePage_UTF8 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceAll( (char)-64 , (char)-16 , 4 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , utf8_test16 , sizeof( utf8_test16 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 9 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 9 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceAll( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 9 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceAll( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test8 , sizeof( utf8_test8 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 21 );
					}
				}
			}	
		}
	}
};

TEST_F( StringTest , ReplaceFirst ) 
{
	{
		{
			::booldog::XString res_str;
			{
				::booldog::XString str0( cp1251_test6 , 0 , XEnumCodePage_CP1251 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceFirst( (char)-64 , (char)-16 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , cp1251_test14 , sizeof( cp1251_test14 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , cp1251_test9 , sizeof( cp1251_test9 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , cp1251_test10 , sizeof( cp1251_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test10 , sizeof( utf16_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test9 , sizeof( utf8_test9 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test9 , sizeof( utf16_test9 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test10 , sizeof( utf16_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test10 , sizeof( utf16_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}
			}

			{
				::booldog::XString str0( utf16_test6 , 0 , XEnumCodePage_UTF16 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceFirst( (char)-64 , (char)-16 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , utf16_test14 , sizeof( utf16_test14 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test9 , sizeof( utf16_test9 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test10 , sizeof( utf16_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test10 , sizeof( utf16_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test9 , sizeof( utf8_test9 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test9 , sizeof( utf16_test9 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test10 , sizeof( utf16_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test10 , sizeof( utf16_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}
			}

			{
				::booldog::XString str0( utf8_test6 , 0 , XEnumCodePage_UTF8 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceFirst( (char)-64 , (char)-16 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , utf8_test14 , sizeof( utf8_test14 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test9 , sizeof( utf8_test9 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test9 , sizeof( utf8_test9 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test9 , sizeof( utf8_test9 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test10 , sizeof( utf8_test10 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}
			}	



			{
				::booldog::XString str0( cp1251_test6 , 0 , XEnumCodePage_CP1251 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceFirst( (char)-64 , (char)-16 , 4 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , cp1251_test15 , sizeof( cp1251_test15 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , cp1251_test11 , sizeof( cp1251_test11 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , cp1251_test12 , sizeof( cp1251_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test12 , sizeof( utf16_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test11 , sizeof( utf8_test11 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test11 , sizeof( utf16_test11 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test12 , sizeof( utf16_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test12 , sizeof( utf16_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}
			}

			{
				::booldog::XString str0( utf16_test6 , 0 , XEnumCodePage_UTF16 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceFirst( (char)-64 , (char)-16 , 4 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , utf16_test15 , sizeof( utf16_test15 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test11 , sizeof( utf16_test11 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test12 , sizeof( utf16_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test12 , sizeof( utf16_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test11 , sizeof( utf8_test11 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test11 , sizeof( utf16_test11 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test12 , sizeof( utf16_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test12 , sizeof( utf16_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}
			}

			{
				::booldog::XString str0( utf8_test6 , 0 , XEnumCodePage_UTF8 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceFirst( (char)-64 , (char)-16 , 4 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , utf8_test15 , sizeof( utf8_test15 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test11 , sizeof( utf8_test11 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test11 , sizeof( utf8_test11 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceFirst( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test11 , sizeof( utf8_test11 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceFirst( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test12 , sizeof( utf8_test12 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}
			}	
		}
	}
};

TEST_F( StringTest , ReplaceLast ) 
{
	{
		{
			::booldog::XString res_str;
			{
				::booldog::XString str0( cp1251_test6 , 0 , XEnumCodePage_CP1251 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceLast( (char)-64 , (char)-16 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , cp1251_test17 , sizeof( cp1251_test17 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , cp1251_test18 , sizeof( cp1251_test18 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , cp1251_test19 , sizeof( cp1251_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test19 , sizeof( utf16_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test18 , sizeof( utf8_test18 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test18 , sizeof( utf16_test18 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test19 , sizeof( utf16_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test19 , sizeof( utf16_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}
			}

			{
				::booldog::XString str0( utf16_test6 , 0 , XEnumCodePage_UTF16 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceLast( (char)-64 , (char)-16 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , utf16_test17 , sizeof( utf16_test17 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test18 , sizeof( utf16_test18 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test19 , sizeof( utf16_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test19 , sizeof( utf16_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test18 , sizeof( utf8_test18 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test18 , sizeof( utf16_test18 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test19 , sizeof( utf16_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test19 , sizeof( utf16_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}
			}

			{
				::booldog::XString str0( utf8_test6 , 0 , XEnumCodePage_UTF8 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceLast( (char)-64 , (char)-16 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , utf8_test17 , sizeof( utf8_test17 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test18 , sizeof( utf8_test18 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test18 , sizeof( utf8_test18 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test18 , sizeof( utf8_test18 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test19 , sizeof( utf8_test19 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}
			}	



			{
				::booldog::XString str0( cp1251_test6 , 0 , XEnumCodePage_CP1251 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceLast( (char)-64 , (char)-16 , 4 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , cp1251_test20 , sizeof( cp1251_test20 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , cp1251_test21 , sizeof( cp1251_test21 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , cp1251_test22 , sizeof( cp1251_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test22 , sizeof( utf16_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test21 , sizeof( utf8_test21 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test21 , sizeof( utf16_test21 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test22 , sizeof( utf16_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test22 , sizeof( utf16_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}
			}

			{
				::booldog::XString str0( utf16_test6 , 0 , XEnumCodePage_UTF16 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceLast( (char)-64 , (char)-16 , 4 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , utf16_test20 , sizeof( utf16_test20 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test21 , sizeof( utf16_test21 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test22 , sizeof( utf16_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test22 , sizeof( utf16_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test21 , sizeof( utf8_test21 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test21 , sizeof( utf16_test21 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test22 , sizeof( utf16_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf16_test22 , sizeof( utf16_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}
			}

			{
				::booldog::XString str0( utf8_test6 , 0 , XEnumCodePage_UTF8 );

				{
#ifdef __WINDOWS__
					res_str.set_ByRef( str0.ReplaceLast( (char)-64 , (char)-16 , 4 ) );
				
					ASSERT_TRUE( memcmp( res_str.str() , utf8_test20 , sizeof( utf8_test20 ) ) == 0 );
				
					ASSERT_TRUE( res_str.Length() == 15 );
#endif
				}

				{
					::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test21 , sizeof( utf8_test21 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test21 , sizeof( utf8_test21 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}

				{
					::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );
					
					{
						res_str.set_ByRef( str0.ReplaceLast( str1 , "" , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test21 , sizeof( utf8_test21 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 12 );
					}

					{
						::booldog::XString str2( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf8_test0 , 0 , XEnumCodePage_UTF8 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}

					{
						::booldog::XString str2( utf16_test0 , 0 , XEnumCodePage_UTF16 );

						res_str.set_ByRef( str0.ReplaceLast( str1 , str2 , 4 ) );
				
						ASSERT_TRUE( memcmp( res_str.str() , utf8_test22 , sizeof( utf8_test22 ) ) == 0 );
				
						ASSERT_TRUE( res_str.Length() == 18 );
					}
				}
			}	
		}
	}
};

TEST_F( StringTest , IndexOf ) 
{
	{
		{
			::booldog::XString str0( cp1251_test6 , 0 , XEnumCodePage_CP1251 );

			{
				if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
					ASSERT_TRUE( str0.IndexOf( cp1251_test2 ) == 3 );
				else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
					ASSERT_TRUE( str0.IndexOf( utf8_test2 ) == 3 );
			}

			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0.IndexOf( str1 ) == 3 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0.IndexOf( str1 ) == 3 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0.IndexOf( str1 ) == 3 );
			}

			{
				::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0.IndexOf( str1 , 2 ) == 6 );
			}

			{
				::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0.IndexOf( str1 , 2 ) == 6 );
			}

			{
				::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0.IndexOf( str1 , 2 ) == 6 );
			}
		}

		{
			::booldog::XString str0( utf16_test6 , 0 , XEnumCodePage_UTF16 );

			{
				if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
					ASSERT_TRUE( str0.IndexOf( cp1251_test2 ) == 3 );
				else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
					ASSERT_TRUE( str0.IndexOf( utf8_test2 ) == 3 );
			}

			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0.IndexOf( str1 ) == 3 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0.IndexOf( str1 ) == 3 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0.IndexOf( str1 ) == 3 );
			}

			{
				::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0.IndexOf( str1 , 2 ) == 6 );
			}

			{
				::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0.IndexOf( str1 , 2 ) == 6 );
			}

			{
				::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0.IndexOf( str1 , 2 ) == 6 );
			}
		}

		{
			::booldog::XString str0( utf8_test6 , 0 , XEnumCodePage_UTF8 );

			{
				if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
					ASSERT_TRUE( str0.IndexOf( cp1251_test2 ) == 3 );
				else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
					ASSERT_TRUE( str0.IndexOf( utf8_test2 ) == 3 );
			}

			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0.IndexOf( str1 ) == 3 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0.IndexOf( str1 ) == 3 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0.IndexOf( str1 ) == 3 );
			}

			{
				::booldog::XString str1( cp1251_test1 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0.IndexOf( str1 , 2 ) == 6 );
			}

			{
				::booldog::XString str1( utf16_test1 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0.IndexOf( str1 , 2 ) == 6 );
			}

			{
				::booldog::XString str1( utf8_test1 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0.IndexOf( str1 , 2 ) == 6 );
			}
		}
	}
};

TEST_F( StringTest , LastIndexOf ) 
{
	{
		{
			::booldog::XString str0( cp1251_test6 , 0 , XEnumCodePage_CP1251 );
			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0.LastIndexOf( str1 ) == 9 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0.LastIndexOf( str1 ) == 9 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0.LastIndexOf( str1 ) == 9 );
			}

			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0.LastIndexOf( str1 , 7 ) == 3 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0.LastIndexOf( str1 , 7 ) == 3 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0.LastIndexOf( str1 , 7 ) == 3 );
			}
		}

		{
			::booldog::XString str0( utf16_test6 , 0 , XEnumCodePage_UTF16 );
			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0.LastIndexOf( str1 ) == 9 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0.LastIndexOf( str1 ) == 9 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0.LastIndexOf( str1 ) == 9 );
			}

			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0.LastIndexOf( str1 , 7 ) == 3 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0.LastIndexOf( str1 , 7 ) == 3 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0.LastIndexOf( str1 , 7 ) == 3 );
			}
		}

		{
			::booldog::XString str0( utf8_test6 , 0 , XEnumCodePage_UTF8 );
			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0.LastIndexOf( str1 ) == 9 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0.LastIndexOf( str1 ) == 9 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0.LastIndexOf( str1 ) == 9 );
			}

			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0.LastIndexOf( str1 , 7 ) == 3 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0.LastIndexOf( str1 , 7 ) == 3 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0.LastIndexOf( str1 , 7 ) == 3 );
			}
		}
	}
};

TEST_F( StringTest , Equals ) 
{
	{
		{
			::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );
			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_FALSE( str0 == str1 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_FALSE( str0 == str1 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_FALSE( str0 == str1 );
			}

			{
				::booldog::XString str1( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0 == str1 );
			}

			{
				::booldog::XString str1( utf16_test0 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0 == str1 );
			}

			{
				::booldog::XString str1( utf8_test0 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0 == str1 );
			}
		}

		{
			::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_FALSE( str0 == str1 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_FALSE( str0 == str1 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_FALSE( str0 == str1 );
			}

			{
				::booldog::XString str1( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0 == str1 );
			}

			{
				::booldog::XString str1( utf16_test0 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0 == str1 );
			}

			{
				::booldog::XString str1( utf8_test0 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0 == str1 );
			}
		}

		{
			::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_FALSE( str0 == str1 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_FALSE( str0 == str1 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_FALSE( str0 == str1 );
			}

			{
				::booldog::XString str1( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0 == str1 );
			}

			{
				::booldog::XString str1( utf16_test0 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0 == str1 );
			}

			{
				::booldog::XString str1( utf8_test0 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0 == str1 );
			}
		}
	}

	{
		{
			::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );
			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0 != str1 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0 != str1 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0 != str1 );
			}

			{
				::booldog::XString str1( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

				ASSERT_FALSE( str0 != str1 );
			}

			{
				::booldog::XString str1( utf16_test0 , 0 , XEnumCodePage_UTF16 );

				ASSERT_FALSE( str0 != str1 );
			}

			{
				::booldog::XString str1( utf8_test0 , 0 , XEnumCodePage_UTF8 );

				ASSERT_FALSE( str0 != str1 );
			}
		}

		{
			::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0 != str1 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0 != str1 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0 != str1 );
			}

			{
				::booldog::XString str1( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

				ASSERT_FALSE( str0 != str1 );
			}

			{
				::booldog::XString str1( utf16_test0 , 0 , XEnumCodePage_UTF16 );

				ASSERT_FALSE( str0 != str1 );
			}

			{
				::booldog::XString str1( utf8_test0 , 0 , XEnumCodePage_UTF8 );

				ASSERT_FALSE( str0 != str1 );
			}
		}

		{
			::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
			{
				::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				ASSERT_TRUE( str0 != str1 );
			}

			{
				::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				ASSERT_TRUE( str0 != str1 );
			}

			{
				::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				ASSERT_TRUE( str0 != str1 );
			}

			{
				::booldog::XString str1( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

				ASSERT_FALSE( str0 != str1 );
			}

			{
				::booldog::XString str1( utf16_test0 , 0 , XEnumCodePage_UTF16 );

				ASSERT_FALSE( str0 != str1 );
			}

			{
				::booldog::XString str1( utf8_test0 , 0 , XEnumCodePage_UTF8 );

				ASSERT_FALSE( str0 != str1 );
			}
		}
	}
}


TEST_F( StringTest , InsertRange ) 
{
	{
		{
			::booldog::XString str0;
					
			::booldog::XString str1;
				
			str0.InsertRange( 0 , str1 );

			ASSERT_TRUE( str0.Length() == 0 );
		}

		{
			::booldog::XString str0;
					
			::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );
				
			str0.InsertRange( SIZE_MAX , str1 );

			ASSERT_TRUE( memcmp( str0.str() , cp1251_test2 , sizeof( cp1251_test2 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 3 );
		}

		{
			::booldog::XString str0;
					
			::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );
				
			str0.InsertRange( SIZE_MAX , str1 );

			ASSERT_TRUE( memcmp( str0.str() , utf8_test2 , sizeof( utf8_test2 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 3 );
		}

		{
			::booldog::XString str0;
					
			::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );
				
			str0.InsertRange( SIZE_MAX , str1 );

			ASSERT_TRUE( memcmp( str0.str() , utf16_test2 , sizeof( utf16_test2 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 3 );
		}

		{
			::booldog::XString str0;
					
			::booldog::XString str1( cp1251_test27 , 0 , XEnumCodePage_CP1251 );
				
			str0.InsertRange( SIZE_MAX , str1 );

			ASSERT_TRUE( memcmp( str0.str() , cp1251_test27 , sizeof( cp1251_test27 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 43 );
		}

		{
			::booldog::XString str0;
					
			::booldog::XString str1( utf8_test27 , 0 , XEnumCodePage_UTF8 );
				
			str0.InsertRange( SIZE_MAX , str1 );

			ASSERT_TRUE( memcmp( str0.str() , utf8_test27 , sizeof( utf8_test27 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 43 );
		}

		{
			::booldog::XString str0;
					
			::booldog::XString str1( utf16_test27 , 0 , XEnumCodePage_UTF16 );
				
			str0.InsertRange( SIZE_MAX , str1 );

			ASSERT_TRUE( memcmp( str0.str() , utf16_test27 , sizeof( utf16_test27 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 43 );
		}

		{
			::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );
					
			::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );
				
			str0.InsertRange( 3 , str1 );

			ASSERT_TRUE( memcmp( str0.str() , cp1251_test3 , sizeof( cp1251_test3 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 9 );
		}

		{
			::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );
					
			::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );
				
			str0.InsertRange( 3 , str1 );

			ASSERT_TRUE( memcmp( str0.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 9 );
		}

		{
			::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );
					
			::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );
				
			str0.InsertRange( 3 , str1 );

			ASSERT_TRUE( memcmp( str0.str() , utf16_test3 , sizeof( utf16_test3 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 9 );
		}

		{
			::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
					
			::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );
				
			str0.InsertRange( 3 , str1 );

			ASSERT_TRUE( memcmp( str0.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 9 );
		}

		{
			::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
					
			::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );
				
			str0.InsertRange( 3 , str1 );

			ASSERT_TRUE( memcmp( str0.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 9 );
		}

		{
			::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
					
			::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );
				
			str0.InsertRange( 3 , str1 );

			ASSERT_TRUE( memcmp( str0.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 9 );
		}

		{
			::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
					
			::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );
				
			str0.InsertRange( 3 , str1 );

			ASSERT_TRUE( memcmp( str0.str() , utf16_test3 , sizeof( utf16_test3 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 9 );
		}

		{
			::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
					
			::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );
				
			str0.InsertRange( 3 , str1 );

			ASSERT_TRUE( memcmp( str0.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 9 );
		}

		{
			::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
					
			::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );
				
			str0.InsertRange( 3 , str1 );

			ASSERT_TRUE( memcmp( str0.str() , utf16_test3 , sizeof( utf16_test3 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 9 );
		}
				
		{
			::booldog::XString str0;

			if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
			{
				str0.InsertRange( 3 , cp1251_test4 , 3 );

				ASSERT_TRUE( memcmp( str0.str() , cp1251_test2 , sizeof( cp1251_test2 ) ) == 0 );
			}
			else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			{
				str0.InsertRange( 3 , utf8_test4 , 3 );

				ASSERT_TRUE( memcmp( str0.str() , utf8_test2 , sizeof( utf8_test2 ) ) == 0 );
			}
			ASSERT_TRUE( str0.Length() == 3 );
		}

		{
			::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

			if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
			{
				str0.InsertRange( 3 , cp1251_test4 , SIZE_MAX );

				ASSERT_TRUE( memcmp( str0.str() , cp1251_test5 , sizeof( cp1251_test5 ) ) == 0 );
			}
			else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			{
				str0.InsertRange( 3 , utf8_test4 , SIZE_MAX );

				ASSERT_TRUE( memcmp( str0.str() , utf8_test5 , sizeof( utf8_test5 ) ) == 0 );
			}

			ASSERT_TRUE( str0.Length() == 12 );
		}

		{
			::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
					
			if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
				str0.InsertRange( 3 , cp1251_test4 , SIZE_MAX );
			else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
				str0.InsertRange( 3 , utf8_test4 , SIZE_MAX );

			ASSERT_TRUE( memcmp( str0.str() , utf8_test5 , sizeof( utf8_test5 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 12 );
		}

		{
			::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
					
			if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
			{
				str0.InsertRange( 3 , cp1251_test4 , SIZE_MAX );

				ASSERT_TRUE( memcmp( str0.str() , utf16_test5 , sizeof( utf16_test5 ) ) == 0 );
			}
			else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			{
				str0.InsertRange( 3 , utf8_test4 , SIZE_MAX );

				ASSERT_TRUE( memcmp( str0.str() , utf8_test5 , sizeof( utf8_test5 ) ) == 0 );
			}

			ASSERT_TRUE( str0.Length() == 12 );
		}


		{
			::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

			if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
			{
				str0.InsertRange( 3 , cp1251_test4 , 3 );

				ASSERT_TRUE( memcmp( str0.str() , cp1251_test3 , sizeof( cp1251_test3 ) ) == 0 );
			}
			else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			{
				str0.InsertRange( 3 , utf8_test4 , 3 );

				ASSERT_TRUE( memcmp( str0.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );
			}

			ASSERT_TRUE( str0.Length() == 9 );
		}

		{
			::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
					
			if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
				str0.InsertRange( 3 , cp1251_test4 , 3 );
			else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
				str0.InsertRange( 3 , utf8_test4 , 3 );

			ASSERT_TRUE( memcmp( str0.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 9 );
		}

		{
			::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
					
			if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
			{
				str0.InsertRange( 3 , cp1251_test4 , 3 );

				ASSERT_TRUE( memcmp( str0.str() , utf16_test3 , sizeof( utf16_test3 ) ) == 0 );
			}
			else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			{
				str0.InsertRange( 3 , utf8_test4 , 3 );

				ASSERT_TRUE( memcmp( str0.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );
			}

			ASSERT_TRUE( str0.Length() == 9 );
		}
		if( sizeof( wchar_t ) == 2 )
		{
			{
				::booldog::XString str0;
				
				str0.InsertRange( 3 , (wchar_t*)utf16_test4 , 3 );

				if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
					ASSERT_TRUE( memcmp( str0.str() , utf16_test2 , sizeof( utf16_test2 ) ) == 0 );
				else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
					ASSERT_TRUE( memcmp( str0.str() , utf8_test2 , sizeof( utf8_test2 ) ) == 0 );

				ASSERT_TRUE( str0.Length() == 3 );
			}

			{
				::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );
				
				str0.InsertRange( 3 , (wchar_t*)utf16_test4 , 3 );

				ASSERT_TRUE( memcmp( str0.str() , utf16_test3 , sizeof( utf16_test3 ) ) == 0 );

				ASSERT_TRUE( str0.Length() == 9 );
			}

			{
				::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
					
				str0.InsertRange( 3 , (wchar_t*)utf16_test4 , 3 );

				ASSERT_TRUE( memcmp( str0.str() , utf8_test3 , sizeof( utf8_test3 ) ) == 0 );

				ASSERT_TRUE( str0.Length() == 9 );
			}

			{
				::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
					
				str0.InsertRange( 3 , (wchar_t*)utf16_test4 , 3 );

				ASSERT_TRUE( memcmp( str0.str() , utf16_test3 , sizeof( utf16_test3 ) ) == 0 );

				ASSERT_TRUE( str0.Length() == 9 );
			}

			{
				::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

				str0.InsertRange( 3 , (wchar_t*)utf16_test4 , SIZE_MAX );
				
				ASSERT_TRUE( memcmp( str0.str() , utf16_test5 , sizeof( utf16_test5 ) ) == 0 );

				ASSERT_TRUE( str0.Length() == 12 );
			}

			{
				::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
					
				str0.InsertRange( 3 , (wchar_t*)utf16_test4 , SIZE_MAX );

				ASSERT_TRUE( memcmp( str0.str() , utf8_test5 , sizeof( utf8_test5 ) ) == 0 );

				ASSERT_TRUE( str0.Length() == 12 );
			}

			{
				::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
					
				str0.InsertRange( 3 , (wchar_t*)utf16_test4 , SIZE_MAX );
				
				ASSERT_TRUE( memcmp( str0.str() , utf16_test5 , sizeof( utf16_test5 ) ) == 0 );

				ASSERT_TRUE( str0.Length() == 12 );
			}
		}
	}
};

TEST_F( StringTest , RemoveRange ) 
{
	{
		{
			::booldog::XString str0;
				
			str0.RemoveRange( 0 , 3 );

			ASSERT_TRUE( str0.Length() == 0 );
		}

		{
			::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );
				
			str0.RemoveRange( 3 , 3 );

			ASSERT_TRUE( memcmp( str0.str() , cp1251_test1 , sizeof( cp1251_test1 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 3 );
		}

		{
			::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
				
			str0.RemoveRange( 3 , 3 );

			ASSERT_TRUE( memcmp( str0.str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 3 );
		}

		{
			::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
				
			str0.RemoveRange( 3 , 3 );

			ASSERT_TRUE( memcmp( str0.str() , utf16_test1 , sizeof( utf16_test1 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 3 );
		}

		{
			::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );
				
			str0.RemoveRange( 3 , SIZE_MAX );

			ASSERT_TRUE( memcmp( str0.str() , cp1251_test1 , sizeof( cp1251_test1 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 3 );
		}

		{
			::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
				
			str0.RemoveRange( 3 , SIZE_MAX );

			ASSERT_TRUE( memcmp( str0.str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 3 );
		}

		{
			::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
				
			str0.RemoveRange( 3 , SIZE_MAX );

			ASSERT_TRUE( memcmp( str0.str() , utf16_test1 , sizeof( utf16_test1 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 3 );
		}

		{
			::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );
				
			str0.RemoveRange( 0 , 3 );

			ASSERT_TRUE( memcmp( str0.str() , cp1251_test2 , sizeof( cp1251_test2 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 3 );
		}

		{
			::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );
				
			str0.RemoveRange( 0 , 3 );

			ASSERT_TRUE( memcmp( str0.str() , utf8_test2 , sizeof( utf8_test2 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 3 );
		}

		{
			::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );
				
			str0.RemoveRange( 0 , 3 );

			ASSERT_TRUE( memcmp( str0.str() , utf16_test2 , sizeof( utf16_test2 ) ) == 0 );

			ASSERT_TRUE( str0.Length() == 3 );
		}
	}
};

TEST_F( StringTest , Plus ) 
{
	::booldog::XString res_string;
	{
		::booldog::XString str0( cp1251_test1 , 0 , XEnumCodePage_CP1251 );

		{
			if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
				res_string.set_ByRef( str0 + utf8_test2 );
			else
				res_string.set_ByRef( str0 + cp1251_test2 );
			
			ASSERT_TRUE( res_string.Length() == 6 );
			if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
				ASSERT_TRUE( memcmp( res_string.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );
			else
				ASSERT_TRUE( memcmp( res_string.str() , cp1251_test0 , sizeof( cp1251_test0 ) ) == 0 );
		}

		{
			::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

			res_string.set_ByRef( str0 + str1 );
			
			ASSERT_TRUE( res_string.Length() == 6 );
			
			ASSERT_TRUE( memcmp( res_string.str() , cp1251_test0 , sizeof( cp1251_test0 ) ) == 0 );
		}

		{
			::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

			res_string.set_ByRef( str0 + str1 );
			
			ASSERT_TRUE( res_string.Length() == 6 );
			
			ASSERT_TRUE( memcmp( res_string.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );
		}

		{
			::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

			res_string.set_ByRef( str0 + str1 );
			
			ASSERT_TRUE( res_string.Length() == 6 );
			
			ASSERT_TRUE( memcmp( res_string.str() , utf16_test0 , sizeof( utf16_test0 ) ) == 0 );
		}
	}

	{
		::booldog::XString str0( utf16_test1 , 0 , XEnumCodePage_UTF16 );

		{
			if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
				res_string.set_ByRef( str0 + utf8_test2 );
			else
				res_string.set_ByRef( str0 + cp1251_test2 );
			
			ASSERT_TRUE( res_string.Length() == 6 );
			if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
				ASSERT_TRUE( memcmp( res_string.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );
			else
				ASSERT_TRUE( memcmp( res_string.str() , utf16_test0 , sizeof( utf16_test0 ) ) == 0 );
		}

		{
			::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

			res_string.set_ByRef( str0 + str1 );
			
			ASSERT_TRUE( res_string.Length() == 6 );
			
			ASSERT_TRUE( memcmp( res_string.str() , utf16_test0 , sizeof( utf16_test0 ) ) == 0 );
		}

		{
			::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

			res_string.set_ByRef( str0 + str1 );
			
			ASSERT_TRUE( res_string.Length() == 6 );
			
			ASSERT_TRUE( memcmp( res_string.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );
		}

		{
			::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

			res_string.set_ByRef( str0 + str1 );
			
			ASSERT_TRUE( memcmp( res_string.str() , utf16_test0 , sizeof( utf16_test0 ) ) == 0 );
		}
	}

	{
		::booldog::XString str0( utf8_test1 , 0 , XEnumCodePage_UTF8 );

		{
			if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
				res_string.set_ByRef( str0 + utf8_test2 );
			else
				res_string.set_ByRef( str0 + cp1251_test2 );
			
			ASSERT_TRUE( res_string.Length() == 6 );
			
			ASSERT_TRUE( memcmp( res_string.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );
		}

		{
			::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

			res_string.set_ByRef( str0 + str1 );
			
			ASSERT_TRUE( res_string.Length() == 6 );
			
			ASSERT_TRUE( memcmp( res_string.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );
		}

		{
			::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

			res_string.set_ByRef( str0 + str1 );
			
			ASSERT_TRUE( res_string.Length() == 6 );
			
			ASSERT_TRUE( memcmp( res_string.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );
		}

		{
			::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

			res_string.set_ByRef( str0 + str1 );
			
			ASSERT_TRUE( res_string.Length() == 6 );
			
			ASSERT_TRUE( memcmp( res_string.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );
		}
	}

	{
		::booldog::XString str1( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

		if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			res_string.set_ByRef( utf8_test1 + str1 );
		else
			res_string.set_ByRef( cp1251_test1 + str1 );
			
		ASSERT_TRUE( res_string.Length() == 6 );
		if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )			
			ASSERT_TRUE( memcmp( res_string.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );
		else
			ASSERT_TRUE( memcmp( res_string.str() , cp1251_test0 , sizeof( cp1251_test0 ) ) == 0 );
	}

	{
		::booldog::XString str1( utf16_test2 , 0 , XEnumCodePage_UTF16 );

		if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			res_string.set_ByRef( utf8_test1 + str1 );
		else
			res_string.set_ByRef( cp1251_test1 + str1 );
			
		ASSERT_TRUE( res_string.Length() == 6 );
			
		if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )			
			ASSERT_TRUE( memcmp( res_string.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );
		else
			ASSERT_TRUE( memcmp( res_string.str() , utf16_test0 , sizeof( utf16_test0 ) ) == 0 );
	}

	{
		::booldog::XString str1( utf8_test2 , 0 , XEnumCodePage_UTF8 );

		if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			res_string.set_ByRef( utf8_test1 + str1 );
		else
			res_string.set_ByRef( cp1251_test1 + str1 );
			
		ASSERT_TRUE( res_string.Length() == 6 );
			
		ASSERT_TRUE( memcmp( res_string.str() , utf8_test0 , sizeof( utf8_test0 ) ) == 0 );
	}
};

TEST_F( StringTest , Split ) 
{
	{
		::booldog::XString str0( cp1251_test6 , 0 , XEnumCodePage_CP1251 );
		{
			::booldog::XString str1( cp1251_test23 , 0 , XEnumCodePage_CP1251 );
			{
				::booldog::XString str2( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				splits.set_ByRef( str0.Split( splits ) );

				ASSERT_TRUE( splits.Count() == 3 );

				ASSERT_TRUE( memcmp( splits[ 0 ].str() , cp1251_test1 , sizeof( cp1251_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 0 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 1 ].str() , cp1251_test1 , sizeof( cp1251_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 1 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 2 ].str() , cp1251_test1 , sizeof( cp1251_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 2 ].Length() == 3 );
			}

			{
				::booldog::XString str2( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				splits.set_ByRef( str0.Split( splits ) );

				ASSERT_TRUE( splits.Count() == 3 );

				ASSERT_TRUE( memcmp( splits[ 0 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 0 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 1 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 1 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 2 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 2 ].Length() == 3 );
			}

			{
				::booldog::XString str2( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				splits.set_ByRef( str0.Split( splits ) );

				ASSERT_TRUE( splits.Count() == 3 );

				ASSERT_TRUE( memcmp( splits[ 0 ].str() , utf16_test1 , sizeof( utf16_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 0 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 1 ].str() , utf16_test1 , sizeof( utf16_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 1 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 2 ].str() , utf16_test1 , sizeof( utf16_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 2 ].Length() == 3 );
			}
		}

		{
			::booldog::XString str1( utf8_test23 , 0 , XEnumCodePage_UTF8 );
			{
				::booldog::XString str2( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				splits.set_ByRef( str0.Split( splits ) );

				ASSERT_TRUE( splits.Count() == 3 );

				ASSERT_TRUE( memcmp( splits[ 0 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 0 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 1 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 1 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 2 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 2 ].Length() == 3 );
			}

			{
				::booldog::XString str2( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				splits.set_ByRef( str0.Split( splits ) );

				ASSERT_TRUE( splits.Count() == 3 );

				ASSERT_TRUE( memcmp( splits[ 0 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 0 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 1 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 1 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 2 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 2 ].Length() == 3 );
			}

			{
				::booldog::XString str2( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				splits.set_ByRef( str0.Split( splits ) );

				ASSERT_TRUE( splits.Count() == 3 );

				ASSERT_TRUE( memcmp( splits[ 0 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 0 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 1 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 1 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 2 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 2 ].Length() == 3 );
			}
		}

		{
			::booldog::XString str1( utf16_test23 , 0 , XEnumCodePage_UTF16 );
			{
				::booldog::XString str2( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				splits.set_ByRef( str0.Split( splits ) );

				ASSERT_TRUE( splits.Count() == 3 );

				ASSERT_TRUE( memcmp( splits[ 0 ].str() , utf16_test1 , sizeof( utf16_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 0 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 1 ].str() , utf16_test1 , sizeof( utf16_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 1 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 2 ].str() , utf16_test1 , sizeof( utf16_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 2 ].Length() == 3 );
			}

			{
				::booldog::XString str2( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				splits.set_ByRef( str0.Split( splits ) );

				ASSERT_TRUE( splits.Count() == 3 );

				ASSERT_TRUE( memcmp( splits[ 0 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 0 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 1 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 1 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 2 ].str() , utf8_test1 , sizeof( utf8_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 2 ].Length() == 3 );
			}

			{
				::booldog::XString str2( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				splits.set_ByRef( str0.Split( splits ) );

				ASSERT_TRUE( splits.Count() == 3 );

				ASSERT_TRUE( memcmp( splits[ 0 ].str() , utf16_test1 , sizeof( utf16_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 0 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 1 ].str() , utf16_test1 , sizeof( utf16_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 1 ].Length() == 3 );

				ASSERT_TRUE( memcmp( splits[ 2 ].str() , utf16_test1 , sizeof( utf16_test1 ) ) == 0 );
		
				ASSERT_TRUE( splits[ 2 ].Length() == 3 );
			}
		}
	}
};

TEST_F( StringTest , Join ) 
{
	::booldog::XString res_string;
	{
		::booldog::XString str0( cp1251_test6 , 0 , XEnumCodePage_CP1251 );
		{
			::booldog::XString str1( cp1251_test23 , 0 , XEnumCodePage_CP1251 );
			{
				::booldog::XString str2( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );
				
				ASSERT_TRUE( memcmp( res_string.str() , cp1251_test26 , sizeof( cp1251_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}

			{
				::booldog::XString str2( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );
				
				ASSERT_TRUE( memcmp( res_string.str() , utf16_test26 , sizeof( utf16_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	

			{
				::booldog::XString str2( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	
		}

		{
			::booldog::XString str1( utf16_test23 , 0 , XEnumCodePage_UTF16 );
			{
				::booldog::XString str2( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );
				
				ASSERT_TRUE( memcmp( res_string.str() , utf16_test26 , sizeof( utf16_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}

			{
				::booldog::XString str2( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );
				
				ASSERT_TRUE( memcmp( res_string.str() , utf16_test26 , sizeof( utf16_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	

			{
				::booldog::XString str2( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	
		}

		{
			::booldog::XString str1( utf8_test23 , 0 , XEnumCodePage_UTF8 );
			{
				::booldog::XString str2( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}

			{
				::booldog::XString str2( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	

			{
				::booldog::XString str2( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	
		}		
	}

	{
		::booldog::XString str0( utf16_test6 , 0 , XEnumCodePage_UTF16 );
		{
			::booldog::XString str1( cp1251_test23 , 0 , XEnumCodePage_CP1251 );
			{
				::booldog::XString str2( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );
				
				ASSERT_TRUE( memcmp( res_string.str() , utf16_test26 , sizeof( utf16_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}

			{
				::booldog::XString str2( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );
				
				ASSERT_TRUE( memcmp( res_string.str() , utf16_test26 , sizeof( utf16_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	

			{
				::booldog::XString str2( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );
				
				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	
		}

		{
			::booldog::XString str1( utf16_test23 , 0 , XEnumCodePage_UTF16 );
			{
				::booldog::XString str2( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );
				
				ASSERT_TRUE( memcmp( res_string.str() , utf16_test26 , sizeof( utf16_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}

			{
				::booldog::XString str2( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );
				
				ASSERT_TRUE( memcmp( res_string.str() , utf16_test26 , sizeof( utf16_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	

			{
				::booldog::XString str2( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	
		}

		{
			::booldog::XString str1( utf8_test23 , 0 , XEnumCodePage_UTF8 );
			{
				::booldog::XString str2( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}

			{
				::booldog::XString str2( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	

			{
				::booldog::XString str2( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	
		}		
	}

	{
		::booldog::XString str0( utf8_test6 , 0 , XEnumCodePage_UTF8 );
		{
			::booldog::XString str1( cp1251_test23 , 0 , XEnumCodePage_CP1251 );
			{
				::booldog::XString str2( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}

			{
				::booldog::XString str2( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	

			{
				::booldog::XString str2( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	
		}

		{
			::booldog::XString str1( utf16_test23 , 0 , XEnumCodePage_UTF16 );
			{
				::booldog::XString str2( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}

			{
				::booldog::XString str2( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	

			{
				::booldog::XString str2( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	
		}

		{
			::booldog::XString str1( utf8_test23 , 0 , XEnumCodePage_UTF8 );
			{
				::booldog::XString str2( cp1251_test2 , 0 , XEnumCodePage_CP1251 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}

			{
				::booldog::XString str2( utf16_test2 , 0 , XEnumCodePage_UTF16 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	

			{
				::booldog::XString str2( utf8_test2 , 0 , XEnumCodePage_UTF8 );

				::booldog::XArray< ::booldog::XString > splits;
				splits.AddByRef( str1 );
				splits.AddByRef( str2 );		

				res_string.set_ByRef( ::booldog::XString::Join( str0 , splits ) );

				ASSERT_TRUE( memcmp( res_string.str() , utf8_test26 , sizeof( utf8_test26 ) ) == 0 );
		
				ASSERT_TRUE( res_string.Length() == 25 );
			}	
		}		
	}
};


TEST_F( StringTest , Insert ) 
{
	{
		::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

		str0.Insert( 0 , '0' );
		if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			ASSERT_TRUE( memcmp( str0.str() , utf8_test23 , sizeof( utf8_test23 ) ) == 0 );
		else if( ::booldog::XString::get_global_code_page() == XEnumCodePage_CP1251 )
			ASSERT_TRUE( memcmp( str0.str() , cp1251_test23 , sizeof( cp1251_test23 ) ) == 0 );
		
		ASSERT_TRUE( str0.Length() == 7 );
	}

	{
		::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );

		str0.Insert( 0 , '0' );

		ASSERT_TRUE( memcmp( str0.str() , utf8_test23 , sizeof( utf8_test23 ) ) == 0 );
		
		ASSERT_TRUE( str0.Length() == 7 );
	}

	{
		::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );

		str0.Insert( 0 , '0' );
		if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			ASSERT_TRUE( memcmp( str0.str() , utf8_test23 , sizeof( utf8_test23 ) ) == 0 );
		else
			ASSERT_TRUE( memcmp( str0.str() , utf16_test23 , sizeof( utf16_test23 ) ) == 0 );
		
		ASSERT_TRUE( str0.Length() == 7 );
	}

	{
		::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

		str0.Insert( 3 , '0' );
		if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			ASSERT_TRUE( memcmp( str0.str() , utf8_test24 , sizeof( utf8_test24 ) ) == 0 );
		else
			ASSERT_TRUE( memcmp( str0.str() , cp1251_test24 , sizeof( cp1251_test24 ) ) == 0 );
		
		ASSERT_TRUE( str0.Length() == 7 );
	}

	{
		::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );

		str0.Insert( 3 , '0' );

		ASSERT_TRUE( memcmp( str0.str() , utf8_test24 , sizeof( utf8_test24 ) ) == 0 );
		
		ASSERT_TRUE( str0.Length() == 7 );
	}

	{
		::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );

		str0.Insert( 3 , '0' );
		if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			ASSERT_TRUE( memcmp( str0.str() , utf8_test24 , sizeof( utf8_test24 ) ) == 0 );
		else
			ASSERT_TRUE( memcmp( str0.str() , utf16_test24 , sizeof( utf16_test24 ) ) == 0 );
		
		ASSERT_TRUE( str0.Length() == 7 );
	}

	{
		::booldog::XString str0( cp1251_test0 , 0 , XEnumCodePage_CP1251 );

		str0.Insert( SIZE_MAX , '0' );

		if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			ASSERT_TRUE( memcmp( str0.str() , utf8_test25 , sizeof( utf8_test25 ) ) == 0 );
		else
			ASSERT_TRUE( memcmp( str0.str() , cp1251_test25 , sizeof( cp1251_test25 ) ) == 0 );
		
		ASSERT_TRUE( str0.Length() == 7 );
	}

	{
		::booldog::XString str0( utf8_test0 , 0 , XEnumCodePage_UTF8 );

		str0.Insert( SIZE_MAX , '0' );

		ASSERT_TRUE( memcmp( str0.str() , utf8_test25 , sizeof( utf8_test25 ) ) == 0 );
		
		ASSERT_TRUE( str0.Length() == 7 );
	}

	{
		::booldog::XString str0( utf16_test0 , 0 , XEnumCodePage_UTF16 );

		str0.Insert( SIZE_MAX , '0' );
		if( ::booldog::XString::get_global_code_page() == XEnumCodePage_UTF8 )
			ASSERT_TRUE( memcmp( str0.str() , utf8_test25 , sizeof( utf8_test25 ) ) == 0 );
		else
			ASSERT_TRUE( memcmp( str0.str() , utf16_test25 , sizeof( utf16_test25 ) ) == 0 );
		
		ASSERT_TRUE( str0.Length() == 7 );
	}
};
*/
/*
class JsonTest : public ::testing::Test 
{
};

TEST_F( JsonTest , DesrializeSpeed ) 
{
	::booldog::XConsole::Print( stdout , XColors::XWhite , "%s" , "Enter to start json test:" );
	//::booldog::XConsole::WaitForEnter();

	declare_variable( ::booldog::XString , error );
	declare_variable( ::booldog::XString , js );
	::booldog::XString dir( ::booldog::engine::_globals->_executable_directory );
	dir += "/json_test_files";
	::booldog::XArray< ::booldog::io::XFile > files;
	::booldog::io::XDirectory::GetFiles( dir , XAllDirectories , files );
	for( size_t index0 = 0 ; index0 < files.Count() ; index0++ )
	{
		js.set_ByRef( files[ index0 ].ReadTextAll( error ) );
		if( error.Length() == 0 )
		{
			if( js.Length() > 0 )
			{
				::booldog::uint32 hash = 0;
				::booldog::XConsole::Print( stdout , XColors::XWhite , files[ index0 ].get_FileName() + "\n" );

				::booldog::XConsole::Print( stdout , XColors::XWhite , "%s" , "======================\n" );
				for( size_t index2 = 0 ; index2 < 10 ; index2++ )
				{
					size_t number_of_tests = 1000;
					::booldog::XConsole::Print( stdout , XColors::XWhite , "%s" , "-------------------\n" );
					::booldog::uint64 test_begin = ::booldog::XTime::get_NowAsUnixTime();
					for( size_t index1 = 0 ; index1 < number_of_tests ; index1++ )
					{
#if USE_YAJL
						yajl_handle hand;
						yajl_gen g;
						yajl_status stat;
						size_t rd;
						int retval = 0;
						int a = 1;  
  
						g = yajl_gen_alloc( NULL );  
						yajl_gen_config( g , yajl_gen_beautify , 1 );  
						yajl_gen_config( g , yajl_gen_validate_utf8 , 1 );  
  
						// ok.  open file.  let's read and parse
						hand = yajl_alloc(&callbacks, NULL, (void *) g);  
						// and let's allow comments by default
						yajl_config( hand , yajl_allow_comments , 1 );  
						stat = yajl_parse( hand , (::booldog::byte*)js.str() , js.Size() - 1 );  
  
						stat = yajl_complete_parse(hand);
  
						yajl_gen_free(g);  
						yajl_free(hand);  
#else
						//XObject obj( ::booldog::data::XJsonSerializer::Deserialize( js , error , __FILE__ , __LINE__ , 0 ) );

						//::booldog::data::XJsonSerializer::IsValidJSON( js.str() , 1 , error , __FILE__ , __LINE__ , 0);//&hash );

						//size_t length = strlen( js.str() );
						//char* ptr = js.str();
						//while( *ptr++ != 0 )
						//	length++;						
#endif
					}
					::booldog::uint64 test_end = ::booldog::XTime::get_NowAsUnixTime();
					::booldog::uint64 delta = test_end - test_begin;
					::booldog::XConsole::Print( stdout , XColors::XWhite , ::booldog::XUInt64( delta ).ToString() + " microseconds, avg " + ::booldog::XUInt64( delta / number_of_tests ).ToString() + " microseconds\n" );
					::booldog::XConsole::Print( stdout , XColors::XWhite , "%s" , "-------------------\n" );
				}
				::booldog::XConsole::Print( stdout , XColors::XWhite , "%s" , "======================\n" );
			}
		}
	}
};

TEST_F( JsonTest , Desrialize ) 
{


	TestString string0;
	TestString string1;



	declare_stack_variable( char , filename , 1024 );
	::booldog::safe_strncpy( filename , ::booldog::engine::_globals->_executable_directory , 1024 );
	rux_concatenation( filename , "/../../rux.framework/test/test.ruxprj" );

	::booldog::XString error;
	//rux::generator::XRUXProject::load( filename , error );

	::booldog::io::file file( filename );
	if( file.opened() )
	{
		size_t size = file.size() + 1 , readen = 0;
		char* json = alloc_array_macros( char , size );
		if( file.read_text( json , size , readen ) )
		{
			char* ptr = json;
			if( memcmp( json , _rux_utf8_header , 3 ) == 0 )
				ptr = &json[ 3 ];
			
			{
				LAZY_PERFORMANCE;
				XObject obj( ::booldog::data::XJsonSerializer::Deserialize( ptr , 1 , error , __FILE__ , __LINE__ ) );

				ASSERT_TRUE( error.Length() == 0 );

				ASSERT_TRUE( rux_is_object( obj , ::booldog::data::XDataObject ) );
			}
		}
		::booldog::engine::free_mem( json );
	}

	
	{
		XObject obj;
		obj.set_ByRef( ::booldog::data::XJsonSerializer::Deserialize( "[{\"name\":\"Joe\"},{\"name\":\"Matthew\"},{\"name\":\"Bill\"}]" , 1 , error , __FILE__ , __LINE__ ) );

		ASSERT_TRUE( error.Length() == 0 );

		ASSERT_TRUE( rux_is_object( obj , ::booldog::XArray< ::booldog::data::XDataObject > ) );
	}

	{
		::booldog::XTime time( 1970 , 1 , 1 , 0 , 0 , 0 , 0 );
	}
};

TEST_F( JsonTest , Merge ) 
{
	declare_stack_variable( char , filename , 1024 );
	::booldog::safe_strncpy( filename , ::booldog::engine::_globals->_executable_directory , 1024 );
	::booldog::safe_strncat( filename , "/../../addons/tests/json/config.txt" , 1024 );

	declare_variable( ::booldog::data::XDataObject , config );

	::booldog::XString error;
	::booldog::io::file file( filename );
	if( file.opened() )
	{
		size_t size = file.size() + 1 , readen = 0;
		char* json = alloc_array_macros( char , size );
		if( file.read_text( json , size , readen ) )
		{
			char* ptr = json;
			if( memcmp( json , _rux_utf8_header , 3 ) == 0 )
				ptr = &json[ 3 ];
			
			{
				LAZY_PERFORMANCE;
				XObject object( ::booldog::data::XJsonSerializer::Deserialize( ptr , 1 , error , __FILE__ , __LINE__ ) );

				ASSERT_TRUE( error.Length() == 0 );

				ASSERT_TRUE( rux_is_object( object , ::booldog::data::XDataObject ) );

				config.set_ByRef( object );
			}
		}
		::booldog::engine::free_mem( json );
	}
	::booldog::safe_strncpy( filename , ::booldog::engine::_globals->_executable_directory , 1024 );
	::booldog::safe_strncat( filename , "/../../addons/tests/json/obj.txt" , 1024 );

	declare_variable( ::booldog::data::XDataObject , obj );

	file.open( filename );
	if( file.opened() )
	{
		size_t size = file.size() + 1 , readen = 0;
		char* json = alloc_array_macros( char , size );
		if( file.read_text( json , size , readen ) )
		{
			char* ptr = json;
			if( memcmp( json , _rux_utf8_header , 3 ) == 0 )
				ptr = &json[ 3 ];
			
			{
				LAZY_PERFORMANCE;
				XObject object( ::booldog::data::XJsonSerializer::Deserialize( ptr , 1 , error , __FILE__ , __LINE__ ) );

				ASSERT_TRUE( error.Length() == 0 );

				ASSERT_TRUE( rux_is_object( object , ::booldog::data::XDataObject ) );

				obj.set_ByRef( object );
			}
		}
		::booldog::engine::free_mem( json );
	}

	::booldog::byte changed = 0;
	config.Merge( obj , changed );
};*/
#define BOOLDOG_STRING_STEP 6
#include <boo_object.h>
#include <boo_if.h>
#include <boo_check.h>
#include <boo_string.h>
#include <boo_array.h>
#include <boo_stack.h>
#include <boo_mem.h>
namespace booldog
{
	/*class string
	{
	private:
		char* _str;
	public:
		string( const char* str )
		{
			if( str )
			{
				size_t len = 0;
				while( str[ len++ ] != 0 ){};
				_str = (char*)_allocator->alloc( len + 1 , __FILE__ , _LINE_ );
				memcpy( _str , str , len );
				_str[ len ] = 0;
			}
			else
				_str = 0;
		};
		string( string& str )
		{
			if( str._str )
			{
				size_t len = 0;
				while( str._str[ len++ ] != 0 ){};
				_str = (char*)_allocator->malloc( len + 1 );
				memcpy( _str , str._str , len );
				_str[ len ] = 0;
			}
			else
				_str = 0;
		};
		~string( void )
		{
			if( _str )
				_allocator->free( _str );
		};
	};*/
};

booldog::string get_string( void )
{
	booldog::string g;
	return g;
};
#define boo_stackTestAllocatorSize 64
class boo_stackTest : public ::testing::Test 
{
};
TEST_F( boo_stackTest , test )
{
	::booldog::allocators::stack::simple< boo_stackTestAllocatorSize > allocator;

	size_t total = boo_stackTestAllocatorSize + sizeof( ::booldog::mem::info );

	char* begin = (char*)allocator.begin();

	void* ptr0 = allocator.alloc( boo_stackTestAllocatorSize , __FILE__ , __LINE__ );

	ASSERT_TRUE( allocator.begin() == allocator.end() );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( allocator.available() , 0 );

	void* ptr1 = allocator.alloc( 17 , __FILE__ , __LINE__ );

	ASSERT_TRUE( allocator.begin() == allocator.end() );

	ASSERT_TRUE( ptr1 == 0 );

	ASSERT_EQ( allocator.available() , 0 );

	allocator.free( ptr0 );

	ASSERT_TRUE( allocator.begin() == begin );

	ASSERT_EQ( allocator.available() , total );

	ptr0 = allocator.alloc( 23 , __FILE__ , __LINE__ );

	ASSERT_TRUE( allocator.begin() == &begin[ 23 + sizeof( ::booldog::mem::info ) ] );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( allocator.available() , total - 23 - sizeof( ::booldog::mem::info ) );

	ptr1 = allocator.alloc( 17 , __FILE__ , __LINE__ );

	ASSERT_TRUE( allocator.begin() == &begin[ 40 + 2 * sizeof( ::booldog::mem::info ) ] );

	ASSERT_FALSE( ptr1 == 0 );

	ASSERT_EQ( allocator.available() , total - 40 - 2 * sizeof( ::booldog::mem::info ) );

	allocator.free( ptr0 );

	ASSERT_TRUE( allocator.begin() == begin );

	ASSERT_EQ( allocator.available() , total - 17 - sizeof( ::booldog::mem::info ) );

	allocator.free( ptr1 );

	ASSERT_TRUE( allocator.begin() == begin );

	ASSERT_EQ( allocator.available() , total );

	ptr0 = allocator.alloc( 45 , __FILE__ , __LINE__ );

	ASSERT_TRUE( allocator.begin() == &begin[ 45 + sizeof( ::booldog::mem::info ) ] );

	ASSERT_FALSE( ptr0 == 0 );

	ASSERT_EQ( allocator.available() , total - 45 - sizeof( ::booldog::mem::info ) );

	allocator.free( ptr0 );

	ASSERT_TRUE( allocator.begin() == begin );

	ASSERT_EQ( allocator.available() , total );


	ptr0 = 0;

	ptr0 = allocator.realloc( ptr0 , 45 , __FILE__ , __LINE__ );

	ASSERT_TRUE( allocator.begin() == &begin[ 45 + sizeof( ::booldog::mem::info ) ] );

	ASSERT_TRUE( ptr0 == ( begin + sizeof( ::booldog::mem::info ) ) );

	ASSERT_EQ( allocator.available() , total - 45 - sizeof( ::booldog::mem::info ) );

	ptr0 = allocator.realloc( ptr0 , 45 , __FILE__ , __LINE__ );

	ASSERT_TRUE( allocator.begin() == &begin[ 45 + sizeof( ::booldog::mem::info ) ] );

	ASSERT_TRUE( ptr0 == ( begin + sizeof( ::booldog::mem::info ) ) );

	ASSERT_EQ( allocator.available() , total - 45 - sizeof( ::booldog::mem::info ) );

	ptr0 = allocator.realloc( ptr0 , 50 , __FILE__ , __LINE__ );

	ASSERT_TRUE( allocator.begin() == &begin[ 50 + sizeof( ::booldog::mem::info ) ] );

	ASSERT_TRUE( ptr0 == ( begin + sizeof( ::booldog::mem::info ) ) );

	ASSERT_EQ( allocator.available() , total - 50 - sizeof( ::booldog::mem::info ) );

	ptr0 = allocator.realloc( ptr0 , 45 , __FILE__ , __LINE__ );

	ASSERT_TRUE( allocator.begin() == &begin[ 45 + sizeof( ::booldog::mem::info ) ] );

	ASSERT_TRUE( ptr0 == ( begin + sizeof( ::booldog::mem::info ) ) );

	ASSERT_EQ( allocator.available() , total - 45 - sizeof( ::booldog::mem::info ) );
};

class boo_memTest : public ::testing::Test 
{
};
TEST_F( boo_memTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	booldog::_allocator = &allocator;

	size_t dstsize = 0;
	size_t dst_allocsize = 8;
	char* dst = (char*)allocator.alloc( dst_allocsize , __FILE__ , __LINE__ );

	ASSERT_TRUE( ::booldog::mem::insert( 0 , dst , dstsize , dst_allocsize , 0 , "Test" , 5 ) );

	dstsize = 4;

	ASSERT_TRUE( ::memcmp( "Test" , dst , dstsize ) == 0 );

	ASSERT_TRUE( ::booldog::mem::insert( 1 , dst , dstsize , dst_allocsize , 0 , "r" , 1 ) );

	dstsize = 5;

	ASSERT_TRUE( ::memcmp( "Trest" , dst , dstsize ) == 0 );

	ASSERT_TRUE( ::booldog::mem::insert( 8 , dst , dstsize , dst_allocsize , 0 , "#7" , 2 ) );

	dstsize = 7;

	ASSERT_TRUE( ::memcmp( "Trest#7" , dst , dstsize ) == 0 );

	ASSERT_TRUE( ::booldog::mem::insert( 2 , dst , dstsize , dst_allocsize , 2 , "om" , 2 ) );

	dstsize = 7;

	ASSERT_TRUE( ::memcmp( "Tromt#7" , dst , dstsize ) == 0 );

	ASSERT_TRUE( ::booldog::mem::insert( 2 , dst , dstsize , dst_allocsize , 2 , "usd" , 3 ) );

	dstsize = 8;

	ASSERT_TRUE( ::memcmp( "Trusdt#7" , dst , dstsize ) == 0 );

	ASSERT_TRUE( ::booldog::mem::insert( 2 , dst , dstsize , dst_allocsize , 3 , "es" , 2 ) );

	dstsize = 7;

	ASSERT_TRUE( ::memcmp( "Trest#7" , dst , dstsize ) == 0 );

	ASSERT_TRUE( ::booldog::mem::insert( 5 , dst , dstsize , dst_allocsize , 4 , "e" , 1 ) );

	dstsize = 6;

	ASSERT_TRUE( ::memcmp( "Treste" , dst , dstsize ) == 0 );

	ASSERT_FALSE( ::booldog::mem::insert( 5 , dst , dstsize , dst_allocsize , 2 , "TEST00000" , 9 ) );

	dstsize = 6;

	ASSERT_TRUE( ::memcmp( "Treste" , dst , dstsize ) == 0 );

	::booldog::mem::remove( 1 , dst , dstsize , 2 );

	dstsize = 4;

	ASSERT_TRUE( ::memcmp( "Tste" , dst , dstsize ) == 0 );

	::booldog::mem::remove( 2 , dst , dstsize , 2 );

	dstsize = 2;

	ASSERT_TRUE( ::memcmp( "Ts" , dst , dstsize ) == 0 );


	::booldog::mem::remove( 1 , dst , dstsize , 3 );

	dstsize = 1;

	ASSERT_TRUE( ::memcmp( "T" , dst , dstsize ) == 0 );


	ASSERT_TRUE( ::booldog::mem::insert( 1 , dst , dstsize , dst_allocsize , 0 , "est0" , 4 ) );

	dstsize = 5;

	ASSERT_TRUE( ::memcmp( "Test0" , dst , dstsize ) == 0 );


	ASSERT_TRUE( ::booldog::mem::expand( 1 , dst , dstsize , dst_allocsize , 2 ) );

	dstsize = 7;

	ASSERT_TRUE( ::memcmp( "Tesest0" , dst , dstsize ) == 0 );

	ASSERT_FALSE( ::booldog::mem::expand( 1 , dst , dstsize , dst_allocsize , 2 ) );

	dstsize = 7;

	ASSERT_TRUE( ::memcmp( "Tesest0" , dst , dstsize ) == 0 );
};

class boo_stringTest : public ::testing::Test 
{
};
TEST_F( boo_stringTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	::booldog::_allocator = &allocator;

	{
		::booldog::string string( (const char*)0 );

		ASSERT_TRUE( strcmp( string.str() , "" ) == 0 );

		ASSERT_EQ( string.length() , 0 );

		ASSERT_EQ( string.bytes() , 0 );
	}

	{
		::booldog::string string( "" );

		ASSERT_TRUE( strcmp( string.str() , "" ) == 0 );

		ASSERT_EQ( string.length() , 0 );

		ASSERT_EQ( string.bytes() , 0 );
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
		::booldog::string string( cp1251_test0 , 0 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
		ASSERT_TRUE( strcmp( string.str() , utf8_test0 ) == 0 );

		ASSERT_EQ( string.length() , 6 );

		ASSERT_EQ( string.bytes() , 13 );
	}

	{
		::booldog::string string( cp1251_test0 , 3 , SIZE_MAX , ::booldog::enums::string::CP1251 );
		
		ASSERT_TRUE( strcmp( string.str() , utf8_test2 ) == 0 );

		ASSERT_EQ( string.length() , 3 );

		ASSERT_EQ( string.bytes() , 7 );
	}

	{
		::booldog::string string( cp1251_test0 , 0 , 6 , ::booldog::enums::string::CP1251 );
		
		ASSERT_TRUE( strcmp( string.str() , utf8_test0 ) == 0 );

		ASSERT_EQ( string.length() , 6 );

		ASSERT_EQ( string.bytes() , 13 );
	}

	{
		::booldog::string string( cp1251_test0 , 0 , 3 , ::booldog::enums::string::CP1251 );
		
		ASSERT_TRUE( strcmp( string.str() , utf8_test1 ) == 0 );

		ASSERT_EQ( string.length() , 3 );

		ASSERT_EQ( string.bytes() , 7 );
	}


	{
		::booldog::string string( utf16_test0 , 0 , SIZE_MAX , ::booldog::enums::string::UTF16 );
		
		ASSERT_EQ( string.length() , 6 );

		ASSERT_EQ( string.bytes() , 13 );

		ASSERT_TRUE( strcmp( string.str() , utf8_test0 ) == 0 );		
	}

	{
		::booldog::string string( utf16_test0 , 6 , SIZE_MAX , ::booldog::enums::string::UTF16 );
		
		ASSERT_EQ( string.length() , 3 );

		ASSERT_EQ( string.bytes() , 7 );

		ASSERT_TRUE( strcmp( string.str() , utf8_test2 ) == 0 );		
	}

	{
		::booldog::string string( utf16_test0 , 0 , 12 , ::booldog::enums::string::UTF16 );
		
		ASSERT_EQ( string.length() , 6 );

		ASSERT_EQ( string.bytes() , 13 );

		ASSERT_TRUE( strcmp( string.str() , utf8_test0 ) == 0 );		
	}

	{
		::booldog::string string( utf16_test0 , 0 , 6 , ::booldog::enums::string::UTF16 );
		
		ASSERT_EQ( string.length() , 3 );

		ASSERT_EQ( string.bytes() , 7 );

		ASSERT_TRUE( strcmp( string.str() , utf8_test1 ) == 0 );
	}


	{
		::booldog::string string( utf32_test0 , 0 , SIZE_MAX , ::booldog::enums::string::UTF32 );
		
		ASSERT_TRUE( strcmp( string.str() , utf8_test0 ) == 0 );

		ASSERT_EQ( string.length() , 6 );

		ASSERT_EQ( string.bytes() , 13 );
	}

	{
		::booldog::string string( utf32_test0 , 12 , SIZE_MAX , ::booldog::enums::string::UTF32 );
		
		ASSERT_TRUE( strcmp( string.str() , utf8_test2 ) == 0 );

		ASSERT_EQ( string.length() , 3 );

		ASSERT_EQ( string.bytes() , 7 );
	}

	{
		::booldog::string string( utf32_test0 , 0 , 24 , ::booldog::enums::string::UTF32 );
		
		ASSERT_TRUE( strcmp( string.str() , utf8_test0 ) == 0 );

		ASSERT_EQ( string.length() , 6 );

		ASSERT_EQ( string.bytes() , 13 );
	}

	{
		::booldog::string string( utf32_test0 , 0 , 12 , ::booldog::enums::string::UTF32 );
		
		ASSERT_TRUE( strcmp( string.str() , utf8_test1 ) == 0 );

		ASSERT_EQ( string.length() , 3 );

		ASSERT_EQ( string.bytes() , 7 );
	}
};

class boo_arrayTest : public ::testing::Test 
{
};
TEST_F( boo_arrayTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	booldog::_allocator = &allocator;

	::booldog::string item0( "TEST0" );

	::booldog::string item1( "TEST1" );

	::booldog::string item2( "TEST2" );

	::booldog::array< ::booldog::string > string_array;

	::booldog::array< ::booldog::object > object_array;


	ASSERT_EQ( string_array.insert( 3 , item2 , __FILE__ , __LINE__ ) , 0 );

	ASSERT_EQ( string_array.count() , 1 );

	ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

	ASSERT_EQ( string_array.insert( 0 , item0 , __FILE__ , __LINE__ ) , 0 );

	ASSERT_EQ( string_array.count() , 2 );

	ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST0" ) == 0 );

	ASSERT_TRUE( strcmp( string_array[ 1 ].str() , "TEST2" ) == 0 );

	ASSERT_EQ( string_array.insert( 1 , item1 , __FILE__ , __LINE__ ) , 1 );

	ASSERT_EQ( string_array.count() , 3 );

	ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST0" ) == 0 );

	ASSERT_TRUE( strcmp( string_array[ 1 ].str() , "TEST1" ) == 0 );

	ASSERT_TRUE( strcmp( string_array[ 2 ].str() , "TEST2" ) == 0 );

	string_array.clear();

	ASSERT_EQ( string_array.count() , 0 );


	ASSERT_EQ( string_array.add( item2 , __FILE__ , __LINE__ ) , 0 );

	ASSERT_EQ( string_array.count() , 1 );

	ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

	ASSERT_EQ( string_array.add( item0 , __FILE__ , __LINE__ ) , 1 );

	ASSERT_EQ( string_array.count() , 2 );

	ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

	ASSERT_TRUE( strcmp( string_array[ 1 ].str() , "TEST0" ) == 0 );

	ASSERT_EQ( string_array.add( item1 , __FILE__ , __LINE__ ) , 2 );

	ASSERT_EQ( string_array.count() , 3 );

	ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

	ASSERT_TRUE( strcmp( string_array[ 1 ].str() , "TEST0" ) == 0 );

	ASSERT_TRUE( strcmp( string_array[ 2 ].str() , "TEST1" ) == 0 );


	string_array.remove( 1 , 4 , __FILE__ , __LINE__ );

	ASSERT_EQ( string_array.count() , 1 );

	ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );


	ASSERT_EQ( string_array.add( item1 , __FILE__ , __LINE__ ) , 1 );

	ASSERT_EQ( string_array.count() , 2 );

	ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST2" ) == 0 );

	ASSERT_TRUE( strcmp( string_array[ 1 ].str() , "TEST1" ) == 0 );


	string_array.remove( 0 , 1 , __FILE__ , __LINE__ );

	ASSERT_EQ( string_array.count() , 1 );

	ASSERT_TRUE( strcmp( string_array[ 0 ].str() , "TEST1" ) == 0 );


	string_array.insert( 1 , object_array , __FILE__ , __LINE__ );
};


class boo_assignmentTest : public ::testing::Test 
{
};
TEST_F( boo_assignmentTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	booldog::_allocator = &allocator;

	::booldog::object obj;

	::booldog::string str;

	::booldog::array< ::booldog::string > str_array;

	::booldog::array< ::booldog::object > obj_array;

	::booldog::array< ::booldog::array< ::booldog::object > > obj_array_array;

	::booldog::array< ::booldog::array< ::booldog::string > > str_array_array;
};


class boo_checkTest : public ::testing::Test 
{
};
TEST_F( boo_checkTest , test )
{
	::booldog::allocators::stack::simple< 4096 > allocator;

	booldog::_allocator = &allocator;

	::booldog::object obj( &allocator );

	::booldog::string str( &allocator );

	::booldog::array< ::booldog::string > str_array( &allocator );

	::booldog::array< ::booldog::object > obj_array( &allocator );

	::booldog::array< ::booldog::array< ::booldog::object > > obj_array_array( &allocator );

	::booldog::array< ::booldog::array< ::booldog::string > > str_array_array( &allocator );


	ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::string > >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::object > >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj ) );


	ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( str ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::string >( str ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::string > >( str ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::object > >( str ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::object > > >( str ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::string > > >( str ) );


	ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( str_array ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( str_array ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::string > >( str_array ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::object > >( str_array ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::object > > >( str_array ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::string > > >( str_array ) );


	ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj_array ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj_array ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::string > >( obj_array ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::object > >( obj_array ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj_array ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj_array ) );


	ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj_array_array ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj_array_array ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::string > >( obj_array_array ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::object > >( obj_array_array ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj_array_array ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj_array_array ) );


	ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( str_array_array ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( str_array_array ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::string > >( str_array_array ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::object > >( str_array_array ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::object > > >( str_array_array ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::string > > >( str_array_array ) );


	ASSERT_TRUE( ::booldog::isclass< ::booldog::object >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::string > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::object > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj ) );


	ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( str ) );

	ASSERT_TRUE( ::booldog::isclass< ::booldog::string >( str ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::string > >( str ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::object > >( str ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::object > > >( str ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::string > > >( str ) );


	ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( str_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( str_array ) );

	ASSERT_TRUE( ::booldog::isclass< ::booldog::array< ::booldog::string > >( str_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::object > >( str_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::object > > >( str_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::string > > >( str_array ) );


	ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::string > >( obj_array ) );

	ASSERT_TRUE( ::booldog::isclass< ::booldog::array< ::booldog::object > >( obj_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj_array ) );


	ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj_array_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj_array_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::string > >( obj_array_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::object > >( obj_array_array ) );

	ASSERT_TRUE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj_array_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj_array_array ) );


	ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( str_array_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( str_array_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::string > >( str_array_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::object > >( str_array_array ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::object > > >( str_array_array ) );

	ASSERT_TRUE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::string > > >( str_array_array ) );


	obj = str;

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::string >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::string > >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::object > >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj ) );


	ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

	ASSERT_TRUE( ::booldog::isclass< ::booldog::string >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::string > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::object > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj ) );


	obj = str_array;

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::string > >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::object > >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj ) );


	ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

	ASSERT_TRUE( ::booldog::isclass< ::booldog::array< ::booldog::string > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::object > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj ) );


	obj = obj_array;

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::string > >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::object > >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj ) );


	ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::string > >( obj ) );

	ASSERT_TRUE( ::booldog::isclass< ::booldog::array< ::booldog::object > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj ) );


	obj = obj_array_array;

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::string > >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::object > >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj ) );


	ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::string > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::object > >( obj ) );

	ASSERT_TRUE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj ) );


	obj = str_array_array;

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::object >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::string >( obj ) );

	ASSERT_FALSE( ::booldog::can_assign< ::booldog::array< ::booldog::string > >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::object > >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj ) );

	ASSERT_TRUE( ::booldog::can_assign< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj ) );


	ASSERT_FALSE( ::booldog::isclass< ::booldog::object >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::string >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::string > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::object > >( obj ) );

	ASSERT_FALSE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::object > > >( obj ) );

	ASSERT_TRUE( ::booldog::isclass< ::booldog::array< ::booldog::array< ::booldog::string > > >( obj ) );
	//obj().ref;

//	booldog::string< &booldog::_heap > g( "l" );
	//obj = get_string();
};
#ifdef __LINUX__
#include <locale.h>
#include <langinfo.h>
#endif
int main( int argc , char **argv )
{
#ifdef __LINUX__
	char* encoding = nl_langinfo(CODESET);
    printf("Encoding is %s\n", encoding);

	setlocale(LC_ALL, "");
    char* locstr = setlocale(LC_CTYPE, NULL);
    encoding = nl_langinfo(CODESET);
    printf("Locale is %s\n", locstr);
    printf("Encoding is %s\n", encoding);
#endif
    ::testing::InitGoogleTest( &argc , argv );
    return RUN_ALL_TESTS();
};