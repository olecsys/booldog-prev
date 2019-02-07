#ifndef BOO_INTEROP_LIBJPEG_TURBO_H
#define BOO_INTEROP_LIBJPEG_TURBO_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_multimedia_video_yuv.h"
#ifndef BOOLDOG_MALLOC
#define BOOLDOG_MALLOC(size, allocation_data, allocation_info) malloc(size)
#define BOOLDOG_REALLOC(pointer, size, allocation_udata, allocation_info) realloc(pointer, size)
#define BOOLDOG_FREE(pointer, allocation_udata, allocation_info) free(pointer)
#include <stdlib.h>
#endif

#include <stdio.h>

#include <turbojpeg.h>
#if defined(_MSC_VER)
#pragma comment(lib, "turbojpeg")
#endif
namespace booldog {
  namespace typedefs {
    namespace interop {
     namespace libjpeg_turbo {
        typedef int DLLCALL (*tjCompressFromYUVPlanes_t)(tjhandle handle,
          unsigned char **srcPlanes, int width, int *strides, int height, int subsamp,
          unsigned char **jpegBuf, unsigned long *jpegSize, int jpegQual, int flags);
     }
    }
  }
	namespace interop
	{
    namespace libjpeg_turbo
    {
      struct encoder 
      {
        tjhandle _tj_handle;
        typedefs::interop::libjpeg_turbo::tjCompressFromYUVPlanes_t _tjCompressFromYUVPlanes;
      };
      inline encoder* open_encoder(void* allocation_udata, void* allocation_info) {
        allocation_udata= allocation_udata;
        allocation_info = allocation_info;
        tjhandle handle = tjInitCompress();
        if(handle)
        {
          encoder* enc = (encoder*)BOOLDOG_MALLOC(sizeof(encoder), allocation_udata, allocation_info);
          enc->_tj_handle = handle;
          enc->_tjCompressFromYUVPlanes = (typedefs::interop::libjpeg_turbo::tjCompressFromYUVPlanes_t)tjCompressFromYUVPlanes;
          return enc;
        }
        else
        {
          //TODO
          char* error = tjGetErrorStr();
          error = error;
        }
        return 0;
      }
      inline size_t encode_buffer_size(::booldog::multimedia::video::planes::yuv* yuv) {
        switch(yuv->_chrominance_subsampling)
        {
        case ::booldog::enums::multimedia::chrominance_subsampling_420:
          return tjBufSize(yuv->_width, yuv->_height, TJSAMP_420);
        case ::booldog::enums::multimedia::chrominance_subsampling_422:
          return tjBufSize(yuv->_width, yuv->_height, TJSAMP_422);
        default:
          return (size_t)-1;
        }
      }
      inline int encode(encoder* enc, ::booldog::data::buffer* buffer, ::booldog::multimedia::video::planes::yuv* yuv
        , void* allocation_udata, void* allocation_info) {
        allocation_udata = allocation_udata;
        allocation_info = allocation_info;
        int subsamp = TJSAMP_420;
        switch(yuv->_chrominance_subsampling)
        {
        case ::booldog::enums::multimedia::chrominance_subsampling_422:
            {
              subsamp = TJSAMP_422;
              break;
            }
        }
        size_t preallocated_jpeg_size = encode_buffer_size(yuv);
        if(preallocated_jpeg_size > buffer->allocsize)
        {
          buffer->allocsize = preallocated_jpeg_size;
          buffer->buf = BOOLDOG_REALLOC(buffer->buf, preallocated_jpeg_size, allocation_udata, allocation_info);
          if(buffer->buf == 0)
          {
            //TODO
            return -1;
          }
        }
        unsigned long jpeg_size = (unsigned long)buffer->allocsize;
        unsigned char* yuv_planes[3] = {yuv->_yuv[0], yuv->_yuv[1], yuv->_yuv[2]};
        unsigned char** jpeg = (unsigned char**)&buffer->buf;
        int res = enc->_tjCompressFromYUVPlanes(enc->_tj_handle, yuv_planes, yuv->_width, yuv->_strides, yuv->_height, subsamp, jpeg
          , &jpeg_size, 100, TJFLAG_NOREALLOC);
        if(res == 0)
        {
          buffer->size = (size_t)jpeg_size;
          return 0;
        }
        else
        {
          //TODO
          char* error = tjGetErrorStr();
          error = error;
          return -1;
        }
      }
      inline int encode_from_bgr(encoder* enc, ::booldog::data::buffer* buffer
        , void* bgr, int width, int height
        , void* allocation_udata, void* allocation_info) {
        allocation_udata = allocation_udata;
        allocation_info = allocation_info;
        int subsamp = TJSAMP_420;
        size_t preallocated_jpeg_size = tjBufSize(width, height, subsamp);
        if(preallocated_jpeg_size > buffer->allocsize) {
          buffer->allocsize = preallocated_jpeg_size;
          buffer->buf = BOOLDOG_REALLOC(buffer->buf, preallocated_jpeg_size, allocation_udata, allocation_info);
          if(buffer->buf == 0)
          {
            //TODO
            return -1;
          }
        }
        unsigned long jpeg_size = (unsigned long)buffer->allocsize;
        unsigned char** jpeg = (unsigned char**)&buffer->buf;
        int res = tjCompress2(enc->_tj_handle, (unsigned char*)bgr, width, 0, height
          , TJPF_BGR, jpeg, &jpeg_size, subsamp, 100, TJFLAG_NOREALLOC);
        if(res == 0) {
          buffer->size = (size_t)jpeg_size;
          return 0;
        }
        else
        {
          //TODO
          char* error = tjGetErrorStr();
          error = error;
          return -1;
        }
      }
      inline void close_encoder(encoder* enc, void* allocation_udata, void* allocation_info) {
        allocation_udata = allocation_udata;
        allocation_info = allocation_info;
        tjDestroy(enc->_tj_handle);
        BOOLDOG_FREE(enc, allocation_udata, allocation_info);
      }


      struct decoder 
      {
        tjhandle _tj_handle;
      };
      inline decoder* open_decoder(void* allocation_udata, void* allocation_info) {
        allocation_udata = allocation_udata;
        allocation_info = allocation_info;
        tjhandle handle = tjInitDecompress();
        if(handle)
        {
          decoder* dec = (decoder*)BOOLDOG_MALLOC(sizeof(decoder), allocation_udata, allocation_info);
          dec->_tj_handle = handle;
          return dec;
        }
        else
        {
          //TODO
          char* error = tjGetErrorStr();
          error = error;
        }
        return 0;
      }
      inline int decode(decoder* dec, ::booldog::data::buffer* jpg, ::booldog::multimedia::video::planes::yuv* yuv
        , void* allocation_udata, void* allocation_info) {
        allocation_udata = allocation_udata;
        allocation_info = allocation_info;
        int width = 0, height = 0, subsamp = 0;
				if(tjDecompressHeader2(dec->_tj_handle, (unsigned char*)jpg->buf, (unsigned long)jpg->size, &width, &height, &subsamp) == 0)
				{									
					size_t preallocated_yuv_size = tjBufSizeYUV(width, height, subsamp);
          if(preallocated_yuv_size == (unsigned long)-1)
          {
            //TODO
            printf("tjBufSizeYUV, failed, arguments are out of bounds\n");
            return -1;
          }
					else
					{
            if(preallocated_yuv_size > yuv->_buffer.allocsize)
            {
              yuv->_buffer.allocsize = preallocated_yuv_size;
              yuv->_buffer.buf = BOOLDOG_REALLOC(yuv->_buffer.buf, preallocated_yuv_size, allocation_udata, allocation_info);
              if(yuv->_buffer.buf == 0)
              {
                //TODO
                return -1;
              }
            }
            unsigned char* yuvbuf = (unsigned char*)yuv->_buffer.buf;
            int y_stride = width, u_offset = 0, v_offset = 0, u_stride = 0, v_stride = 0;
						switch(subsamp)
						{
							case TJSAMP_444:
                {
                  yuv->_chrominance_subsampling = ::booldog::enums::multimedia::chrominance_subsampling_444;
                  u_stride = v_stride = width;
                  u_offset = y_stride * height;
                  v_offset = u_offset + u_stride * height;
                  //printf("TJSAMP_444\n");
								  break;
                }
							case TJSAMP_422:
                {
                  yuv->_chrominance_subsampling = ::booldog::enums::multimedia::chrominance_subsampling_422;
                  u_stride = v_stride = width / 2;
                  u_offset = y_stride * height;
                  v_offset = u_offset + u_stride * height;
                  //printf("TJSAMP_422\n");
								  break;
                }
							case TJSAMP_420:
								{
                  yuv->_chrominance_subsampling = ::booldog::enums::multimedia::chrominance_subsampling_420;
                  u_stride = v_stride = width / 2;
                  u_offset = y_stride * height;
                  v_offset = u_offset + (u_stride * height / 2);
                  //printf("TJSAMP_420\n");
								  break;
                }
							case TJSAMP_GRAY:
								{
                  yuv->_chrominance_subsampling = ::booldog::enums::multimedia::chrominance_subsampling_gray;
                  u_stride = v_stride = 0;
                  u_offset = v_offset = 0;
                  //printf("TJSAMP_GRAY\n");
								  break;
                }
							case TJSAMP_440:
                {
                  //printf("TJSAMP_440\n");
                  break;
                }
            default:
                {
                  printf("Unknown subsamp %d\n", subsamp);
                  break;
                }
						}
            yuv->_yuv[0] = yuvbuf;
            yuv->_strides[0] = y_stride;                
            yuv->_yuv[1] = &yuvbuf[u_offset];
            yuv->_strides[1] = u_stride;
            yuv->_yuv[2] = &yuvbuf[v_offset];
            yuv->_strides[2] = v_stride;
            yuv->_width = width;
            yuv->_height = height;

            if(tjDecompressToYUVPlanes(dec->_tj_handle, (unsigned char*)jpg->buf, (unsigned long)jpg->size, yuv->_yuv, width
              , yuv->_strides, height, TJFLAG_NOREALLOC) == 0)
              return 0;
						else
            {
              //TODO
              char* error = tjGetErrorStr();
              printf("tjDecompressToYUVPlanes failed, %s\n", error);
              error = error;
              return -1;
            }
					}									
				}
				else
        {          
          //TODO
          char* error = tjGetErrorStr();
          printf("tjDecompressHeader2, failed, %s\n", error);
          error = error;
          return -1;
        }
      }
      inline int decode_to_bgr(decoder* dec, ::booldog::data::buffer* jpg
        , ::booldog::data::buffer* rgb, int* pwidth, int* pheight, void* allocation_udata, void* allocation_info) {
        allocation_udata = allocation_udata;
        allocation_info = allocation_info;
        int width = 0, height = 0, subsamp = 0;
				if(tjDecompressHeader2(dec->_tj_handle, (unsigned char*)jpg->buf, (unsigned long)jpg->size
          , &width, &height, &subsamp) == 0)
				{									
					size_t preallocated_yuv_size = tjBufSize(width, height, subsamp);
          if(preallocated_yuv_size == (unsigned long)-1)
          {
            //TODO
            printf("tjBufSize, failed, arguments are out of bounds\n");
            return -1;
          }
					else
					{
            if(preallocated_yuv_size > rgb->allocsize)
            {
              rgb->allocsize = preallocated_yuv_size;
              rgb->buf = BOOLDOG_REALLOC(rgb->buf, preallocated_yuv_size, allocation_udata, allocation_info);
              if(rgb->buf == 0)
              {
                //TODO
                return -1;
              }
            }
            *pwidth = width;
            *pheight = height;
            if(tjDecompress2(dec->_tj_handle, (unsigned char*)jpg->buf, (unsigned long)jpg->size
              , (unsigned char*)rgb->buf, width, 0, height, TJPF_BGR, TJFLAG_NOREALLOC) == 0)
              return 0;
						else
            {
              //TODO
              char* error = tjGetErrorStr();
              printf("tjDecompress2 failed, %s\n", error);
              error = error;
              return -1;
            }
					}									
				}
				else
        {          
          //TODO
          char* error = tjGetErrorStr();
          printf("tjDecompressHeader2, failed, %s\n", error);
          error = error;
          return -1;
        }
      }
      inline void close_decoder(decoder* dec, void* allocation_udata, void* allocation_info) {
        allocation_udata = allocation_udata;
        allocation_info = allocation_info;
        tjDestroy(dec->_tj_handle);
        BOOLDOG_FREE(dec, allocation_udata, allocation_info);
      }
    }
  }
}
#endif
