#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"

#include "../../../boo_allocation.h"

#include "../../../boo_std_allocator.hpp"

// #include <string>

// typedef std::basic_string< char, std::char_traits<char>, booldog::std::allocator< char > > String;

MunitResult my_test(const MunitParameter params[], void* user_data_or_fixture) {
  // String str0, str1("this is string2");

  // munit_assert_string_equal(str1.c_str(), "this is string2");

  // str0 = "it's a test" + str1;

  // struct boo_stream stream;
  // munit_assert_int(boo_sax_json_parse(&stream), ==, 0);

  munit_assert_false(0);

  // munit_assert_char('a', ==, 'b');

  return MUNIT_OK;
}

MunitTest tests[] = {
  {
    (char*)"/my-test", /* name */
    my_test, /* test */
    NULL, /* setup */
    NULL, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  /* Mark the end of the array with an entry where the test
   * function is NULL */
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
  (char*)"/my-tests", /* name */
  tests, /* tests */
  NULL, /* suites */
  1, /* iterations */
  MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char** argv) {
  return munit_suite_main(&suite, NULL, argc, argv);
}