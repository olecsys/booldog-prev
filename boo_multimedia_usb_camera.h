/** class capture
* Simplify work with video capture from USB cameras
* Linux(sudo apt-get install libv4l-dev, sudo yum install libv4l-devel)
* Windows(libraries: Ole32 OleAut32 strmiids)
*/

#ifndef BOO_MULTIMEDIA_USB_CAMERA_H
#define BOO_MULTIMEDIA_USB_CAMERA_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_multimedia_enums.h"

//#include "boo_multimedia_video_frame.h"
//#include "boo_time_utils.h"
//#include "boo_error.h"
//#include "boo_result.h"

//#if 1
#ifdef __LINUX__
#include "boo_io_directory.h"
#include <linux/videodev2.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#ifndef _LARGEFILE64_SOURCE 
#define _LARGEFILE64_SOURCE 
#endif
#include <unistd.h>
#include <sys/mman.h>
#include <sys/select.h>

#ifndef V4L2_PIX_FMT_H264
#define V4L2_PIX_FMT_H264     v4l2_fourcc('H', '2', '6', '4') /* H264 with start codes */
#endif
#elif defined(__WINDOWS__)
#include <DShow.h>
#include <dvdmedia.h>

#include "boo_utf16.h"
#include "boo_utf8.h"

#pragma comment(lib, "Ole32")
#pragma comment(lib, "OleAut32")
#pragma comment(lib, "strmiids")

#include "boo_lockfree_queue.h"
#endif
namespace booldog
{
	namespace multimedia
	{
		namespace video
		{
      namespace usb {
        struct camera {

        };
        int open_camera(camera* cam) {

          return 0;
        }
        int close_camera(camera* cam) {

          return 0;
        }
      }
		}
	}
}
#endif
