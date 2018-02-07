#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#include "acutest.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "../../boo_interop_avformat.h"
//#include "../../boo_interop_libjpeg_turbo.h"
#include "../../boo_io_file.h"
#include "../../boo_heap_allocator.h"
#ifdef __LINUX__
#include "../../boo_multimedia_usb_camera.h"
#endif
#include "../../boo_multimedia_enums.h"

#ifdef _MSC_VER
#pragma comment(lib, "avformat.lib")
#endif

#ifdef BOO_INTEROP_AVFORMAT_H
void test_avformat() {
  ::booldog::allocators::easy::heap heap;
  ::booldog::result_file file;
  TEST_CHECK(::booldog::io::file::mbsopen(&file, &heap, "3.jpeg", ::booldog::enums::io::file_mode_read
    , "../../../../data/multimedia", true));

  if(file.file == 0)
    return;

  ::booldog::results::buffer buffer(&heap);
  TEST_CHECK(file.file->readall< 1024 >(&buffer, buffer));
  file.file->close(0);

  if(buffer.buf == 0)
    return;

  ::booldog::multimedia::image img;
  img.fourcc = ::booldog::enums::multimedia::image::MJPEG;
  img.data = buffer.buf;
  img.width = 1280;
  img.height = 960;
  img.sizeimage = buffer.bufdatasize;

  ::booldog::interop::avformat::formatter fmt = {0, 0, 0};
  


  //av_log_set_level(AV_LOG_ERROR);  
  if(!TEST_CHECK(::booldog::interop::avformat::open_formatter(&fmt, &img, "4.avi") == 0) == 0) {

    for(int index = 0;index < 120;++index) {
      TEST_CHECK(::booldog::interop::avformat::write_video(&fmt, &img) == 0);
    }

    ::booldog::interop::avformat::close_formatter(&fmt);
  }
}
#endif

#ifdef BOO_INTEROP_LIBJPEG_TURBO_H
void test_libjpeg_turbo() {
  ::booldog::allocators::easy::heap heap;
  ::booldog::result_file file;
  TEST_CHECK(::booldog::io::file::mbsopen(&file, &heap, "3.yv12", ::booldog::enums::io::file_mode_read
    , "../../../../data/multimedia", true));

  if(file.file == 0)
    return;

  ::booldog::results::buffer buffer(&heap);
  TEST_CHECK(file.file->readall< 1024 >(&buffer, buffer));
  file.file->close(0);

  if(buffer.buf == 0)
    return;

  unsigned char* yuvbuf = buffer.detach();

  int width = *(int*)yuvbuf;
  int height = *(int*)&yuvbuf[sizeof(int)];
  yuvbuf += 2 * sizeof(int);
  
  ::booldog::multimedia::video::planes::yuv yuv;

  int y_size = width * height;
  int u_size = width * height / 4;

  yuv._yuv[0] = yuvbuf;
  yuv._strides[0] = width;
  yuv._yuv[1] =  &yuvbuf[y_size + u_size];
  yuv._strides[1] = width / 2;
  yuv._yuv[2] = &yuvbuf[y_size];
  yuv._strides[2] = width / 2;
  yuv._width = width;
  yuv._height = height;
  yuv._chrominance_subsampling = ::booldog::enums::multimedia::chrominance_subsampling_420;


  ::booldog::interop::libjpeg_turbo::encoder* enc =
    ::booldog::interop::libjpeg_turbo::open_encoder(0, 0);

  TEST_CHECK(enc != 0);

  ::booldog::interop::libjpeg_turbo::decoder* dec =
    ::booldog::interop::libjpeg_turbo::open_decoder(0, 0);

  TEST_CHECK(dec != 0);

  if(enc && dec)
  {
    ::booldog::data::buffer buf(0, 0);
    if(!TEST_CHECK(::booldog::interop::libjpeg_turbo::encode(enc, &buf, &yuv, 0, 0) == 0) == 0)
    {
      TEST_CHECK(::booldog::io::file::mbsopen(&file, &heap, "3.jpeg", ::booldog::enums::io::file_mode_create
        , ".", true));

      if(file.file)
      {
        size_t written = 0;
        TEST_CHECK(file.file->write(0, (::booldog::byte*)buf.buf, buf.size, 1024, written));
        file.file->close(0);
      }

      if(!TEST_CHECK(::booldog::interop::libjpeg_turbo::decode(dec, &buf, &yuv, 0, 0) == 0) == 0)
      {
        TEST_CHECK(::booldog::interop::libjpeg_turbo::encode(enc, &buf, &yuv, 0, 0) == 0);

        TEST_CHECK(::booldog::io::file::mbsopen(&file, &heap, "3.jpeg", ::booldog::enums::io::file_mode_create
          , ".", true));

        if(file.file)
        {
          size_t written = 0;
          TEST_CHECK(file.file->write(0, (::booldog::byte*)buf.buf, buf.size, 1024, written));
          file.file->close(0);
        }
      }
    }
    if(buf.buf)
      BOOLDOG_FREE(buf.buf, 0, 0);
  }

  if(yuv._buffer.buf)
    BOOLDOG_FREE(yuv._buffer.buf, 0, 0);

  if(enc)
    ::booldog::interop::libjpeg_turbo::close_encoder(enc, 0, 0);

  if(dec)
    ::booldog::interop::libjpeg_turbo::close_decoder(dec, 0, 0);

  yuvbuf -= 2 * sizeof(int);
  heap.free(yuvbuf);
}
#endif

#ifdef __LINUX__
int usb_camera_test_failed = 0;
int usb_camera_frames_count = 0;
::booldog::multimedia::video::usb::frame* usb_camera_frames[10];
void usb_camera_onframe(::booldog::multimedia::video::usb::frame* f, int error, void* udata) {
  udata = udata;
  if(f) {
    if(usb_camera_frames_count == sizeof(usb_camera_frames) / sizeof(usb_camera_frames[0])) {
      for(int index = 0;index < usb_camera_frames_count;++index) {
        error = ::booldog::multimedia::video::usb::unlock_frame(usb_camera_frames[index]);
        if(error)
         usb_camera_test_failed = error;
      }
      usb_camera_frames_count = 0;
    }
    if(::booldog::multimedia::video::usb::lock_frame(f) == 0)
      usb_camera_frames[usb_camera_frames_count++] = f;
  }
  else
    usb_camera_test_failed = error;
}
void test_web_camera() {
  ::booldog::multimedia::video::usb::single_threaded::camera cam;

  int res = ::booldog::multimedia::video::usb::single_threaded::open_camera(&cam, "/dev/video0");

  if(!TEST_CHECK(res == 0) == 0) {

    res = ::booldog::multimedia::video::usb::single_threaded::start_camera(&cam, ::booldog::enums::multimedia::image::YUYV
      , 640, 480, 30, 0, 0);
    if(!TEST_CHECK(res == 0) == 0) {

      for(int index = 0;index < sizeof(usb_camera_frames) / sizeof(usb_camera_frames[0]);++index) {
        res = ::booldog::multimedia::video::usb::single_threaded::boo_multimedia_usb_read_frame(&cam, usb_camera_onframe, 0);
        TEST_CHECK(res == 0);
      }
      for(int index = 0;index < usb_camera_frames_count;++index) {
        res = ::booldog::multimedia::video::usb::unlock_frame(usb_camera_frames[index]);
        TEST_CHECK(res == 0);
      }
      ::booldog::multimedia::video::usb::single_threaded::stop_camera(&cam);
    }

    ::booldog::multimedia::video::usb::single_threaded::close_camera(&cam, 0, 0);

    ::booldog::multimedia::video::usb::multi_threaded::camera mt_cam;

    res = ::booldog::multimedia::video::usb::multi_threaded::open_camera(&mt_cam, "/dev/video0");

    if(!TEST_CHECK(res == 0) == 0) {
      usb_camera_frames_count = 0;

      res = ::booldog::multimedia::video::usb::multi_threaded::start_camera(&mt_cam
        , usb_camera_onframe, 0, ::booldog::enums::multimedia::image::YUYV, 640, 480, 30, 0, 0);
      if(!TEST_CHECK(res == 0) == 0) {
        ::booldog::threading::sleep(5000);

        ::booldog::multimedia::video::usb::multi_threaded::stop_camera(&mt_cam);
        
        for(int index = 0;index < usb_camera_frames_count;++index) {
          res = ::booldog::multimedia::video::usb::unlock_frame(usb_camera_frames[index]);
          TEST_CHECK(res == 0);
        }        
      }

      ::booldog::multimedia::video::usb::multi_threaded::close_camera(&mt_cam, 0, 0);

      TEST_CHECK(usb_camera_test_failed == 0);
    }
  }
}
#endif
TEST_LIST = {
#ifdef BOO_INTEROP_LIBJPEG_TURBO_H
    {"interop libjpeg-turbo", test_libjpeg_turbo},
#endif
#ifdef __LINUX__
    {"web camera", test_web_camera},
#endif
#ifdef BOO_INTEROP_AVFORMAT_H
    {"interop avformat", test_avformat},
#endif
    {NULL, NULL}
};