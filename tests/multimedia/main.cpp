#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#include "acutest.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

void test_web_camera() 
{
	int test = 1986;
	  TEST_CHECK(test == 1986);

	TEST_CHECK(test == 1988);
}
TEST_LIST = {
    {"web camera", test_web_camera},
    {NULL, NULL}
};