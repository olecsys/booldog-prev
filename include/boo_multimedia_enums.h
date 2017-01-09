#ifndef BOO_MULTIMEDIA_ENUMS_H
#define BOO_MULTIMEDIA_ENUMS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_types.h)
#define BOOLDOG_MAKEFCC(ch0, ch1, ch2, ch3)                              \
                ((::booldog::uint32)(::booldog::uint8)(ch0) | ((::booldog::uint32)(::booldog::uint8)(ch1) << 8) |   \
                ((::booldog::uint32)(::booldog::uint8)(ch2) << 16) | ((::booldog::uint32)(::booldog::uint8)(ch3) << 24 ))
namespace booldog
{
	namespace enums
	{
		namespace multimedia
		{
			namespace image
			{
				enum fourcc
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
					Unknown = 0xffffffff
				};
                        }
                }
        }
}
#endif
