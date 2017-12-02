#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
TEST_CASE("test")
{
	int test = 1986;
	REQUIRE(test == 1986);
}