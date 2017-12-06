#ifndef BOO_MULTIMEDIA_ENUMS_H
#define BOO_MULTIMEDIA_ENUMS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_platform.h"
#define BOOLDOG_MAKEFCC(ch0, ch1, ch2, ch3) \
  ((unsigned int)(unsigned char)(ch0) | ((unsigned int)(unsigned char)(ch1) << 8) | \
  ((unsigned int)(unsigned char)(ch2) << 16) | ((unsigned int)(unsigned char)(ch3) << 24 ))
namespace booldog
{
	namespace enums
	{
		namespace multimedia
		{
			namespace audio
			{
				typedef enum
				{	
					PCM = BOOLDOG_MAKEFCC('P', 'C', 'M', ' '),
					Unknown = 0xffffffff
				} fourcc;
			}
			namespace image
			{
				typedef enum
				{
					BITMAP_RGB = 0x00000000 ,
					I420 = 0x30323449 ,
					RGB = 0x32424752 ,
					YV12 = 0x32315659 ,
					YUYV = 0x56595559 ,
					BGR3 = 0x33524742 ,
					GREY = 0x59455247 ,
					Y800 = 0x30303859 ,
					Y8 = 0x20203859 ,
					H264 = BOOLDOG_MAKEFCC('H', '2', '6', '4'),
					MJPEG = BOOLDOG_MAKEFCC('M', 'J', 'P', 'G'),
					YV16 = BOOLDOG_MAKEFCC('Y', 'V', '1', '6'),
					I422 = BOOLDOG_MAKEFCC('I', '4', '2', '2'),
          YUY2 = BOOLDOG_MAKEFCC('Y', 'U', 'Y', '2'),
					PCM = BOOLDOG_MAKEFCC('P', 'C', 'M', ' '),
					Unknown = 0xffffffff
				} fourcc;
			}
		}
	}
}
#endif
