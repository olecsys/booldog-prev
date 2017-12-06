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
#include "../../boo_threading_thread.h"
#include "../../boo_threading_utils.h"

static int test = 999;
static void onthread(void* arglist) {
  const char* string = (const char*)arglist;
  test = strcmp(string, "Test string");
}
void test_thread() {
  BOOLDOG_THREAD thr;

  char* arglist = "Test string";

  BOOLDOG_THREAD_ATTACHED(&thr, onthread, 0, arglist);

  BOOLDOG_THREAD_ATTACHED_JOIN(&thr);

  TEST_CHECK(test == 0);

  test = 999;
  BOOLDOG_THREAD_DETACHED(&thr, onthread, 0, arglist);

  int tries = 0;
  while(test == 999 && tries++ < 10)
    ::booldog::threading::sleep(5);

  TEST_CHECK(test == 0);
}
TEST_LIST = {
    {"thread", test_thread},
    {NULL, NULL}
};