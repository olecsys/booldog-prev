#ifndef BOO_SAX_JSON_H
#define BOO_SAX_JSON_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_stream.h"

int boo_sax_json_parse(struct boo_stream* stream);

inline int boo_sax_json_parse(struct boo_stream* stream) {
  stream->read(0, 1024);
  return 0;
}

#endif