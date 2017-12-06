#ifndef BOO_INTEROP_AVFORMAT_H
#define BOO_INTEROP_AVFORMAT_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "boo_multimedia_enums.h"
//#include "boo_multimedia_video_yuv.h"
#ifndef BOOLDOG_MALLOC
#define BOOLDOG_MALLOC(size, allocation_data, allocation_info) malloc(size)
#define BOOLDOG_REALLOC(pointer, size, allocation_udata, allocation_info) realloc(pointer, size)
#define BOOLDOG_FREE(pointer, allocation_udata, allocation_info) free(pointer)
#endif

extern "C"
{
//#include <libavcodec/avcodec.h>
//#include <libavutil/avconfig.h>
//#include <libavutil/opt.h>	
//#include <libavutil/imgutils.h>	
//#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
//#include <libswresample/swresample.h>
}
#if defined(__WINDOWS__)
#pragma comment(lib, "avformat")
#endif
namespace booldog
{
	namespace interop
	{
    namespace avformat
    {
      struct formatter
      {
      };
      formatter* open_formatter(int fourcc) {

      }
    }
  }
}
#endif
