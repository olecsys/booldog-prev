#ifndef BOO_MULTIMEDIA_ENUMS_H
#define BOO_MULTIMEDIA_ENUMS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_types.h)
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
					Unknown = 0xffffffff
				};
			};
		};
	};
};
#endif
