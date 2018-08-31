#ifndef BOO_STREAM_H
#define BOO_STREAM_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_platform.h"

#ifndef BOO_UINT64_DEFINED
  #define BOO_UINT64_DEFINED
  #ifdef BOO_WINDOWS_OS
typedef unsigned __int64 boo_uint64;
  #else
typedef unsigned long long int boo_uint64;
  #endif
#endif

typedef int (*boo_stream_read_t)(void* data, size_t data_size);

struct boo_stream {
  boo_stream_read_t read;
  int ee;
} boo_stream;

#endif