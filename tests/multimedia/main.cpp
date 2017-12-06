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
#include "../../boo_interop_libjpeg_turbo.h"
#include "../../boo_io_file.h"
#include "../../boo_heap_allocator.h"
#include "../../boo_multimedia_usb_camera.h"
void test_libjpeg_turbo() 
{
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
void test_web_camera() {
  ::booldog::multimedia::video::usb::camera cam = {};

  int res = ::booldog::multimedia::video::usb::open_camera(&cam);

  if(!TEST_CHECK(res == 0) == 0) {

    ::booldog::multimedia::video::usb::close_camera(&cam);
  }
}
TEST_LIST = {
    {"interop libjpeg-turbo", test_libjpeg_turbo},
    {"web camera", test_web_camera},
    {NULL, NULL}
};