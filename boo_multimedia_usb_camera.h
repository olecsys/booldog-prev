/** class capture
* Simplify work with video capture from USB cameras
* Linux(sudo apt-get install libv4l-dev, sudo yum install libv4l-devel)
* v4l2-ctl -d /dev/video0 --list-formats
* v4l2-ctl -d /dev/video0 --list-formats-ext
* Windows(libraries: Ole32 OleAut32 strmiids)
*/

#ifndef BOO_MULTIMEDIA_USB_CAMERA_H
#define BOO_MULTIMEDIA_USB_CAMERA_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef BOOLDOG_MALLOC
#define BOOLDOG_MALLOC(size, allocation_data, allocation_info) malloc(size)
#define BOOLDOG_REALLOC(pointer, size, allocation_udata, allocation_info) realloc(pointer, size)
#define BOOLDOG_FREE(pointer, allocation_udata, allocation_info) free(pointer)
#include <stdlib.h>
#endif

#ifndef BOOLDOG_THREAD_ATTACHED
#include "boo_threading_thread.h"
#endif
#include "boo_platform.h"
#include "boo_error.h"
#include "boo_multimedia_structs.h"

//#if 1
#ifdef __LINUX__
#include "boo_threading_utils.h"
//#include "boo_io_directory.h"
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
#include <time.h>
#include <errno.h>
#include <string.h>

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
        namespace single_threaded {
          struct camera;
        }
        struct frame {
          ::booldog::multimedia::image image;
#if defined(__LINUX__)
          struct v4l2_buffer v4l2buf;
          volatile long locked;
#endif          
          unsigned long long timestamp;
          single_threaded::camera* cam;
        };
        int lock_frame(::booldog::multimedia::video::usb::frame* f);
        int unlock_frame(::booldog::multimedia::video::usb::frame* f);
      }
    }
  }
  namespace typedefs {
    namespace multimedia {
      namespace video {
        namespace usb {
          typedef void (*onframe)(::booldog::multimedia::video::usb::frame* f, int error, void* udata);
        }
      }
    }
  }
	namespace multimedia
	{
		namespace video
		{
      namespace usb {
        namespace single_threaded {
#if defined(__LINUX__)
          struct buffer 
          {
            void* start;
            __u32 length;
            unsigned char mmap;
            __u32 offset;
          };
#endif        
          struct camera {
#ifdef __WINDOWS__
#elif defined(__LINUX__)
            int fd;
            int capture_type;
            buffer buffers[10];
            unsigned int buffers_count;
            int fourcc;
            int width;
            int height;
            int framerate;
            unsigned int sizeimage;
            unsigned long long timestamp;
            unsigned long long last_tickcount;
            ::booldog::multimedia::video::usb::frame frames[20];
#endif
         };        
#ifdef __LINUX__
          static int boo_multimedia_usb_ioctl(int fd, int request, void *arg)
          {
            int r;
            do
            {
              r = ioctl(fd, request, arg);
            }
            while(-1 == r && EINTR == errno);
            return r;
          }          
          static int boo_multimedia_usb_read_frame(camera* cam
            , ::booldog::typedefs::multimedia::video::usb::onframe onframe, void* onframe_udata) {
            for(;;)
            {
              fd_set fds;
              FD_ZERO(&fds);
              FD_SET(cam->fd, &fds);

              struct timeval tv = {0, 0};
              tv.tv_sec = 0;
              tv.tv_usec = 23333;

              int resint = select(cam->fd + 1, &fds, 0, 0, &tv);
              if(resint == -1) {
                resint = errno;
                if(resint == EINTR)
                  continue;
                onframe(0, resint, onframe_udata);
                //TODO
                return resint;
              }
              else if(resint != 0) {
                struct timespec ts = {0, 0};
                clock_gettime(CLOCK_MONOTONIC,&ts);
                
                unsigned long long new_last_tickcount = ts.tv_sec * 1000000ULL + (ts.tv_nsec / 1000LL);
                cam->timestamp += new_last_tickcount - cam->last_tickcount;
                cam->last_tickcount = new_last_tickcount;
                
                unsigned int index = 0;
                frame* f = 0;
                for(index = 0;index < sizeof(cam->frames) / sizeof(cam->frames[0]);++index) {
                  f = &cam->frames[index];
                  if(__sync_val_compare_and_swap(&f->locked, 0, 1) == 0)
                    break;
                }
                if(index == sizeof(cam->frames) / sizeof(cam->frames[0])) {                  
                  //TODO
                  int error = ::booldog::enums::result::booerr_type_all_frames_locked;
                  onframe(0, error, onframe_udata);
                  return error;
                }
                switch(cam->capture_type)
                {
                case V4L2_MEMORY_USERPTR: {
                    memset(&f->v4l2buf, 0, sizeof(f->v4l2buf));
                    f->v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                    f->v4l2buf.memory = V4L2_MEMORY_USERPTR;
                    if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_DQBUF, &f->v4l2buf) == -1)
                    {                    
                      int error = errno;
                      if(error != EIO) {
                        f->locked = 0;
                        //TODO
                        onframe(0, error, onframe_udata);
                        return error;
                      }
                    }					
                    for(index = 0;index < cam->buffers_count;++index) {
                      if(f->v4l2buf.m.userptr == (unsigned long)cam->buffers[index].start
                        && f->v4l2buf.length == cam->buffers[index].length)
                        break;
                    }
                    if(index < cam->buffers_count)
                    {
                      f->image.fourcc = cam->fourcc;
                      f->image.width = cam->width;
                      f->image.height = cam->height;
                      f->image.data = (unsigned char*)f->v4l2buf.m.userptr;
                      f->image.sizeimage = (unsigned int)f->v4l2buf.bytesused;
                      f->timestamp = cam->timestamp;
                      onframe(f, 0, onframe_udata);
                    }
                    return unlock_frame(f);
                  }
                case V4L2_MEMORY_MMAP: {
                    memset(&f->v4l2buf, 0, sizeof(f->v4l2buf));
                    f->v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                    f->v4l2buf.memory = V4L2_MEMORY_MMAP;
                    if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_DQBUF, &f->v4l2buf) == -1) {
                      f->locked = 0;
                      //TODO
                      int error = errno;
                      onframe(0, error, onframe_udata);
                      return error;
                    }
                    f->image.fourcc = cam->fourcc;
                    f->image.width = cam->width;
                    f->image.height = cam->height;
                    f->image.data = (unsigned char*)cam->buffers[f->v4l2buf.index].start;
                    f->image.sizeimage = (unsigned int)f->v4l2buf.bytesused;
                    f->timestamp = cam->timestamp;
                    onframe(f, 0, onframe_udata);
                    return unlock_frame(f);
                  }
                /*default: {
                    if(read(_fd, _buffers[0].start, _buffers[0].length) == -1)
                    {
                      res->seterrno();
                      return false;
                    }
                    //timestamp = ::booldog::utils::time::posix::now_as_utc();
                    vframe.fourcc = _fourcc;
                    vframe.width = _width;
                    vframe.height = _height;
                    vframe.data = (::booldog::byte*)_buffers[0].start;
                    vframe.size = (::booldog::uint32)_buffers[0].length;
                    vframe.timestamp =_timestamp;
                  
                    callback(_allocator, udata, &vframe);
                    break;
                  }*/
                }
              }
              return 0;
            }
          }
#endif        
          inline int open_camera(camera* cam, const char* name) {
#ifdef __LINUX__
            struct stat st;
            if(stat(name, &st) == -1)
            {
              //TODO
              int error = errno;
              return error;
            }
            if(S_ISCHR(st.st_mode) == 0) 
            {
              //TODO
              int error = ::booldog::enums::result::booerr_type_file_is_not_character_device;
              return error;
            }
            cam->fd = open(name, O_RDWR | O_NONBLOCK, 0);
            if(cam->fd == -1)
            {
              //TODO
              int error = errno;
              return error;
            }
            struct v4l2_capability cap;
            if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_QUERYCAP, &cap) == -1)
            {
              //TODO
              close(cam->fd);
              cam->fd = -1;
              int error = errno;
              return error;
            }
            if((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0)
            {
              //TODO
              close(cam->fd);
              cam->fd = -1;
              int error = ::booldog::enums::result::booerr_type_file_is_not_video_capture_device;
              return error;
            }
            for(unsigned int index = 0;index < sizeof(cam->buffers) / sizeof(cam->buffers[0]);++index)
              memset(&cam->buffers[index], 0, sizeof(buffer));
            for(unsigned int index = 0;index < sizeof(cam->frames) / sizeof(cam->frames[0]);++index) {
              cam->frames[index].cam = cam;
              cam->frames[index].locked = 0;
            }
#endif          
            return 0;
          }
          inline int start_camera(camera* cam, int fourcc, int width, int height, int framerate, void* allocation_data
            , void* allocation_info) {
            allocation_data = allocation_data;
            allocation_info = allocation_info;
#ifdef __LINUX__
            buffer* pbuffer = 0;
            struct v4l2_requestbuffers req;

            enum v4l2_buf_type v4l2buftype;
            struct v4l2_buffer v4l2buf;
            

            
            
            
            
            
            

            unsigned char reinit = 0;
            if(cam->fourcc != fourcc || cam->width != width || cam->height != height
              || cam->framerate != framerate)
              reinit = 1;
            if(reinit)
            {
              struct v4l2_capability cap;
              if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_QUERYCAP, &cap) == -1)
              {
                cam->fourcc = 0xffffffff;
                //TODO
                int error = errno;
                return error;
              }
              if(cap.capabilities & V4L2_CAP_STREAMING)
                cam->capture_type = V4L2_MEMORY_MMAP;
              else
              {
                cam->capture_type = 0;
                if((cap.capabilities & V4L2_CAP_READWRITE) == 0)
                {
                  cam->fourcc = 0xffffffff;
                  //TODO
                  int error = ::booldog::enums::result::booerr_type_video_capture_device_does_not_support_neither_streaming_nor_io;
                  return error;
                }
              }
              struct v4l2_cropcap cropcap;
              memset(&cropcap, 0, sizeof(cropcap));
              cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
              if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_CROPCAP, &cropcap) == 0)
              {
                struct v4l2_crop crop;
                crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                crop.c = cropcap.defrect;
                if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_S_CROP, &crop) == -1)
                {
                  switch (errno) {
                  case EINVAL:
                    /* Cropping not supported. */
                    break;
                  default:
                    /* Errors ignored. */
                    break;
                  }
                }
              }
              else
              {
                /* Errors ignored. */
              }

              struct v4l2_format fmt;
              memset(&fmt, 0, sizeof(fmt));
              fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
              fmt.fmt.pix.width = width;
              fmt.fmt.pix.height = height;
              fmt.fmt.pix.pixelformat = fourcc;
              fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;//V4L2_FIELD_ANY
              if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_S_FMT, &fmt) == -1)
              {
                cam->fourcc = 0xffffffff;
                //TODO
                int error = errno;
                return error;
              }
              unsigned int min = fmt.fmt.pix.width * 2;
              if(fmt.fmt.pix.bytesperline < min)
                fmt.fmt.pix.bytesperline = min;
              min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
              if(fmt.fmt.pix.sizeimage < min)
                fmt.fmt.pix.sizeimage = min;
              cam->sizeimage = fmt.fmt.pix.sizeimage;
              cam->width = fmt.fmt.pix.width;
              cam->height = fmt.fmt.pix.height;
              cam->fourcc = fourcc;

              if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_G_FMT, &fmt) == -1)
              {
                cam->fourcc = 0xffffffff;
                //TODO
                int error = errno;
                return error;
              }
              if(framerate != 0)
              {
                struct v4l2_streamparm v4l2streamparm;
                memset(&v4l2streamparm, 0, sizeof(v4l2streamparm));
                v4l2streamparm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_G_PARM, &v4l2streamparm) != -1)
                {
                  if(v4l2streamparm.parm.capture.capability & V4L2_CAP_TIMEPERFRAME)
                  {
                    v4l2streamparm.parm.capture.timeperframe.numerator = 1;
                    v4l2streamparm.parm.capture.timeperframe.denominator = framerate;
                    if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_S_PARM, &v4l2streamparm) == -1)
                    {
                      cam->fourcc = 0xffffffff;
                      //TODO
                      int error = errno;
                      return error;
                    }
                  }
                }
                else
                {
                  cam->fourcc = 0xffffffff;
                  //TODO
                  int error = errno;
                  return error;
                }
              }
              cam->framerate = framerate;        
            }
            if(cam->capture_type == V4L2_MEMORY_USERPTR)
            {
              memset(&req, 0, sizeof(req));

              req.count  = sizeof(cam->buffers) / sizeof(cam->buffers[0]);
              req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
              req.memory = V4L2_MEMORY_USERPTR;

              if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_REQBUFS, &req) == -1)
              {
                int errnoval = errno;
                if(errnoval != EINVAL)
                {
                  cam->fourcc = 0xffffffff;
                  //TODO
                  return errnoval;
                }
                else
                  cam->capture_type = V4L2_MEMORY_MMAP;
              }
              else if(reinit)
              {
                for(cam->buffers_count = 0
                  ;cam->buffers_count < (int)(sizeof(cam->buffers) / sizeof(cam->buffers[0]))
                  ;++cam->buffers_count)
                {
                  pbuffer = &cam->buffers[cam->buffers_count];
                  if(pbuffer->mmap)
                  {
                    munmap(pbuffer->start, pbuffer->length);
                    memset(pbuffer, 0, sizeof(buffer));
                  }
                  if(cam->sizeimage > pbuffer->length)
                  {
                    pbuffer->start = BOOLDOG_REALLOC(pbuffer->start, cam->sizeimage, allocation_data
                      , allocation_info);
                    if(pbuffer->start == 0)
                    {
                      cam->fourcc = 0xffffffff;
                      memset(pbuffer, 0, sizeof(buffer));
                      //TODO                    
                      int error = ::booldog::enums::result::booerr_type_cannot_alloc_memory;
                      return error;
                    }
                    pbuffer->length = cam->sizeimage;
                  }
                }
              }
            }
            if(cam->capture_type == V4L2_MEMORY_MMAP)
            {
              if(reinit)
              {              
                memset(&req, 0, sizeof(req));

                req.count = sizeof(cam->buffers) / sizeof(cam->buffers[0]);
                req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                req.memory = V4L2_MEMORY_MMAP;

                if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_REQBUFS, &req) == -1)
                {
                  int errnoval = errno;
                  if(errnoval != EINVAL)
                  {
                    cam->fourcc = 0xffffffff;
                    //TODO
                    return errnoval;
                  }
                  else
                    cam->capture_type = 0;
                }
                else
                {
                  if(req.count < 2)
                  {
                    cam->fourcc = 0xffffffff;
                    //TODO
                    int error = ::booldog::enums::result::booerr_type_insufficient_memory;
                    return error;
                  }
                  for(cam->buffers_count = 0;cam->buffers_count < req.count;++cam->buffers_count) {
                    memset(&v4l2buf, 0, sizeof(v4l2buf));

                    v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                    v4l2buf.memory = V4L2_MEMORY_MMAP;
                    v4l2buf.index = cam->buffers_count;

                    if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_QUERYBUF, &v4l2buf) == -1)
                    {
                      cam->fourcc = 0xffffffff;
                      //TODO
                      int error = errno;
                      return error;
                    }
                    pbuffer = &cam->buffers[cam->buffers_count];
                    if(pbuffer->mmap)
                    {
                      if((pbuffer->length != v4l2buf.length || pbuffer->offset != v4l2buf.m.offset))
                      {
                        munmap(pbuffer->start, pbuffer->length);
                        memset(pbuffer, 0, sizeof(buffer));
                      }
                    }
                    else
                    {                                                                    
                      if(pbuffer->length)
                      {
                        BOOLDOG_FREE(pbuffer->start, allocation_data, allocation_info);
                        memset(pbuffer, 0, sizeof(buffer));
                      }
                    }
                    if(pbuffer->length == 0)
                    {
                      pbuffer->start = mmap(0, v4l2buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, cam->fd
                        , v4l2buf.m.offset);
                      if(pbuffer->start == MAP_FAILED)
                      {
                        cam->fourcc = 0xffffffff;
                        memset(pbuffer, 0, sizeof(buffer));
                        //TODO
                        int error = ::booldog::enums::result::booerr_type_map_failed;
                        return error;
                      }
                      pbuffer->mmap = 1;
                      pbuffer->length = v4l2buf.length;
                      pbuffer->offset = v4l2buf.m.offset;
                    }
                  }
                }
              }
            }
            if(cam->capture_type == 0)
            {
              pbuffer = &cam->buffers[0];
              if(pbuffer->mmap)
              {
                munmap(pbuffer->start, pbuffer->length);
                memset(pbuffer, 0, sizeof(buffer));
              }
              if(cam->sizeimage > pbuffer->length)
              {
                pbuffer->start = BOOLDOG_REALLOC(pbuffer->start, cam->sizeimage, allocation_data, allocation_info);
                if(pbuffer->start == 0)
                {
                  cam->fourcc = 0xffffffff;
                  memset(pbuffer, 0, sizeof(buffer));
                  //TODO
                  int error = ::booldog::enums::result::booerr_type_cannot_alloc_memory;
                  return error;
                }
                pbuffer->length = cam->sizeimage;
              }
            }
            switch(cam->capture_type)
            {
            case V4L2_MEMORY_USERPTR:
              {
                for(unsigned int index = 0;index < cam->buffers_count;++index)
                {
                  pbuffer = &cam->buffers[index];
                  memset(&v4l2buf, 0, sizeof(v4l2buf));
                  v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                  v4l2buf.memory = V4L2_MEMORY_USERPTR;
                  v4l2buf.index = index;
                  v4l2buf.m.userptr = (unsigned long)pbuffer->start;
                  v4l2buf.length = pbuffer->length;
                  if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_QBUF, &v4l2buf) == -1)
                  {
                    cam->fourcc = 0xffffffff;
                    //TODO
                    int error = errno;
                    return error;
                  }
                }
                break;
              }
            case V4L2_MEMORY_MMAP:
              {
                for(unsigned int index = 0;index < cam->buffers_count;++index)
                {
                  memset(&v4l2buf, 0, sizeof(v4l2buf));
                  v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                  v4l2buf.memory = V4L2_MEMORY_MMAP;
                  v4l2buf.index = index;
                  if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_QBUF, &v4l2buf) == -1)
                  {
                    cam->fourcc = 0xffffffff;
                    //TODO
                    int error = errno;
                    return error;
                  }
                }
                break;
              }
            default:
              return 0;
            }
            v4l2buftype = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_STREAMON, &v4l2buftype) == -1)
            {
              cam->fourcc = 0xffffffff;
              //TODO
              int error = errno;
              return error;
            }
            struct timespec ts = {0, 0};
            clock_gettime(CLOCK_REALTIME, &ts);
            cam->timestamp = ts.tv_sec * 1000000ULL + (ts.tv_nsec / 1000ULL);	
            clock_gettime(CLOCK_MONOTONIC,&ts);
            cam->last_tickcount = ts.tv_sec * 1000000ULL + (ts.tv_nsec / 1000ULL);
            return 0;
#endif
            int error = ::booldog::enums::result::booerr_type_method_is_not_implemented_yet;
            return error;
          }
          inline int stop_camera(camera* cam) {
#ifdef __LINUX__
            enum v4l2_buf_type type;
            switch (cam->capture_type)
            {
            case V4L2_MEMORY_USERPTR: {
                type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_STREAMOFF, &type) == -1) {
                  //TODO
                  int error = errno;
                  return error;
                }
                else {
                    struct v4l2_requestbuffers req;
                    memset(&req, 0, sizeof(req));
                    req.count  = 0;
                    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                    req.memory = (v4l2_memory)cam->capture_type;
                    boo_multimedia_usb_ioctl(cam->fd, VIDIOC_REQBUFS, &req);
                }
                break;
              }
            case V4L2_MEMORY_MMAP: {
                type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                if(boo_multimedia_usb_ioctl(cam->fd, VIDIOC_STREAMOFF, &type) == -1) {
                  //TODO
                  int error = errno;
                  return error;
                }
                break;
              }
            }
            return 0;
#endif
            int error = ::booldog::enums::result::booerr_type_method_is_not_implemented_yet;
            return error;
          }
          inline int close_camera(camera* cam, void* allocation_data, void* allocation_info) {
            allocation_data = allocation_data;
            allocation_info = allocation_info;
#ifdef __LINUX__
            buffer* pbuffer = 0;
            for(unsigned int index = 0;index < sizeof(cam->buffers) / sizeof(cam->buffers[0]);++index)
            {
              pbuffer = &cam->buffers[index];
              if(pbuffer->mmap) {
                munmap(pbuffer->start, pbuffer->length);
                memset(pbuffer, 0, sizeof(buffer));
              }
              else if(pbuffer->length) {
                BOOLDOG_FREE(pbuffer->start, allocation_data, allocation_info);
                memset(pbuffer, 0, sizeof(buffer));
              }
            }
            if(close(cam->fd) == -1)
            {
              //TODO
              int error = errno;
              return error;
            }
            else
              cam->fd = -1;
            return 0;
#endif
            int error = ::booldog::enums::result::booerr_type_method_is_not_implemented_yet;
            return error;
          }
        }
        namespace multi_threaded {
          struct camera { 
#ifdef __WINDOWS__
#elif defined(__LINUX__)
            ::booldog::multimedia::video::usb::single_threaded::camera cam;
            BOOLDOG_THREAD thr;
            unsigned char thr_started;
            unsigned char cam_started;
            ::booldog::typedefs::multimedia::video::usb::onframe onframe;
            void* onframe_udata;
#endif
          };
          static void camera_capture_thread(void* arglist) {
            camera* cam = (camera*)arglist;
            cam->thr_started = 1;
            int res = 0;
            while(cam->cam_started == 0) {
              if(res++ == 5) {
                ::booldog::threading::sleep(1);
                res = 0;
              }
            }
            while(cam->cam_started == 1) {
              res = ::booldog::multimedia::video::usb::single_threaded::boo_multimedia_usb_read_frame(&cam->cam, cam->onframe, cam->onframe_udata);
            }
          }
          inline int open_camera(camera* cam, const char* name) {
#ifdef __LINUX__
            return ::booldog::multimedia::video::usb::single_threaded::open_camera(&cam->cam, name);            
#endif          
            int error = ::booldog::enums::result::booerr_type_method_is_not_implemented_yet;
            return error;
          }
          inline int start_camera(camera* cam, ::booldog::typedefs::multimedia::video::usb::onframe onframe, void* onframe_udata
            , int fourcc, int width, int height, int framerate, void* allocation_data, void* allocation_info) {
            allocation_data = allocation_data;
            allocation_info = allocation_info;
#ifdef __LINUX__
            cam->thr_started = 0;
            cam->cam_started = 0;
            cam->onframe = onframe;
            cam->onframe_udata = onframe_udata;
            int res = BOOLDOG_THREAD_ATTACHED(&cam->thr, camera_capture_thread, 0, cam);
            if(res == 0)
            {
              int tries = 0;
              while(cam->thr_started == 0)
              {
                if(tries++ == 5)
                {
                  ::booldog::threading::sleep(1);
                  tries = 0;
                }
              }
              res = ::booldog::multimedia::video::usb::single_threaded::start_camera(&cam->cam, fourcc, width
                , height, framerate, allocation_data, allocation_info);
              if(res) {
                cam->cam_started = 2;
                BOOLDOG_THREAD_ATTACHED_JOIN(&cam->thr);
              }
              else
                cam->cam_started = 1;
            }
            return res;
#endif
            int error = ::booldog::enums::result::booerr_type_method_is_not_implemented_yet;
            return error;
          }
          inline int stop_camera(camera* cam) {
#ifdef __LINUX__
            cam->cam_started = 2;
            BOOLDOG_THREAD_ATTACHED_JOIN(&cam->thr);
            return ::booldog::multimedia::video::usb::single_threaded::stop_camera(&cam->cam);
#endif
            int error = ::booldog::enums::result::booerr_type_method_is_not_implemented_yet;
            return error;
          }
          inline int close_camera(camera* cam, void* allocation_data, void* allocation_info) {
#ifdef __LINUX__
            return ::booldog::multimedia::video::usb::single_threaded::close_camera(&cam->cam, allocation_data, allocation_info);
#endif
            int error = ::booldog::enums::result::booerr_type_method_is_not_implemented_yet;
            return error;
          }

        }
        inline int lock_frame(::booldog::multimedia::video::usb::frame* f) {
          __sync_add_and_fetch(&f->locked, 1);
          return 0;
        }
        inline int unlock_frame(::booldog::multimedia::video::usb::frame* f) {
          if(__sync_sub_and_fetch(&f->locked, 1) == 0) {
            if(::booldog::multimedia::video::usb::single_threaded::boo_multimedia_usb_ioctl(
              f->cam->fd, VIDIOC_QBUF, &f->v4l2buf) == -1) {
              //TODO
              int error = errno;
              return error;
            }
          }
          return 0;
        }
      }
		}
	}
}
#endif
