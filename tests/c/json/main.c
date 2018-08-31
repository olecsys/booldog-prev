#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"

#include "../../../boo_sax_json.h"

MunitResult my_test(const MunitParameter params[], void* user_data_or_fixture) {

  struct boo_stream stream;
  munit_assert_int(boo_sax_json_parse(&stream), ==, 0);

  munit_assert_false(0);

  munit_assert_char('a', ==, 'b');

  return MUNIT_OK;
}

MunitTest tests[] = {
  {
    "/my-test", /* name */
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
  "/my-tests", /* name */
  tests, /* tests */
  NULL, /* suites */
  1, /* iterations */
  MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char** argv) {
  return munit_suite_main(&suite, NULL, argc, argv);
}