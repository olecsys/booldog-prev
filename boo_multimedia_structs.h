#ifndef BOO_MULTIMEDIA_STRUCTS_H
#define BOO_MULTIMEDIA_STRUCTS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_platform.h"
namespace booldog
{
  namespace multimedia
  {
    namespace audio
    {

    }
    struct image {
      int fourcc;
      int width;
      int height;
      unsigned int sizeimage;
      unsigned char* data;
    };
  }
}
#endif
