#ifndef BOO_MEDIA_ENUMS_H
#define BOO_MEDIA_ENUMS_H
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
		namespace media
		{
			enum fourcc
			{
				fourcc_BI_RGB = 0x00000000 ,
				fourcc_I420 = 0x30323449 ,
				fourcc_RGB = 0x32424752 ,
				fourcc_YV12 = 0x32315659 ,
				fourcc_YUYV = 0x56595559 ,
				fourcc_BGR3 = 0x33524742 ,
				fourcc_GREY = 0x59455247 ,
				fourcc_Y800 = 0x30303859 ,
				fourcc_Y8 = 0x20203859 ,
				fourcc_Unknown = 0xffffffff
			};
		};
	};
};
#endif
