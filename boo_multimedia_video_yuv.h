#ifndef BOO_MULTIMEDIA_VIDEO_YUV_H
#define BOO_MULTIMEDIA_VIDEO_YUV_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_multimedia_video_frame.h"
#include "boo_multimedia_enums.h"

#ifndef BOOLDOG_MALLOC
#define BOOLDOG_MALLOC(size, allocation_data, allocation_info) malloc(size)
#define BOOLDOG_REALLOC(pointer, size, allocation_udata, allocation_info) realloc(pointer, size)
#define BOOLDOG_FREE(pointer, allocation_udata, allocation_info) free(pointer)
#include <stdlib.h>
#endif
namespace booldog
{
  namespace enums
  {
    namespace multimedia {
      typedef enum
      {
        chrominance_subsampling_444,
        chrominance_subsampling_422,
        chrominance_subsampling_420,
        chrominance_subsampling_gray
      } chrominance_subsampling;
    }
  }
	namespace multimedia
	{
		namespace video
		{
      namespace planes
      {
        struct yuv 
        { 
          ::booldog::data::buffer _buffer;
          unsigned char* _yuv[3];
          int _strides[3];
          int _width;
          int _height;
          ::booldog::enums::multimedia::chrominance_subsampling _chrominance_subsampling;
        };
				inline int copyfrom_yv12(yuv* dst, unsigned char* src, int width, int height, void* allocation_data, void* allocation_info)
        {
          allocation_data = allocation_data;
          allocation_info = allocation_info;

          dst->_width = width;
          dst->_height = height;
          dst->_chrominance_subsampling = ::booldog::enums::multimedia::chrominance_subsampling_420;
          dst->_strides[0] = width;
          dst->_strides[1] = dst->_strides[2] = width / 2;
							
          unsigned int size = 3 * width * height / 2;
          if(size > dst->_buffer.allocsize) {
            dst->_buffer.buf = BOOLDOG_REALLOC(dst->_buffer.buf, size, allocation_data, allocation_info);
            if(dst->_buffer.buf == 0) {
              int error = ::booldog::enums::result::booerr_type_cannot_alloc_memory;
              return error;
            }
            dst->_buffer.allocsize = size;
          }
          dst->_buffer.size = size;
          unsigned char* yuv = (unsigned char*)dst->_buffer.buf;
          dst->_yuv[0] = yuv;
          dst->_yuv[1] = yuv + dst->_strides[0] * height / 2;
          dst->_yuv[2] = dst->_yuv[1] + dst->_strides[1] * height / 2;

          unsigned char* y = dst->_yuv[0], * v = dst->_yuv[1], * u = dst->_yuv[2];
          unsigned int y_offset = 0, uv_offset = 0, index = 0;
          while(index < size)
					{								
            y[y_offset++] = src[index];
            u[uv_offset] = src[++index];
            y[y_offset++] = src[++index];
            v[uv_offset++] = src[++index];
						++index;
          }
          return 0;
        }
        inline int copyfrom_yuyv(yuv* dst, unsigned char* src, int width, int height, void* allocation_data, void* allocation_info)
        {
          allocation_data = allocation_data;
          allocation_info = allocation_info;

          dst->_width = width;
          dst->_height = height;
          dst->_chrominance_subsampling = ::booldog::enums::multimedia::chrominance_subsampling_422;
          dst->_strides[0] = width;
          dst->_strides[1] = dst->_strides[2] = width / 2;
							
          unsigned int size = 2 * width * height;
          if(size > dst->_buffer.allocsize) {
            dst->_buffer.buf = BOOLDOG_REALLOC(dst->_buffer.buf, size, allocation_data, allocation_info);
            if(dst->_buffer.buf == 0) {
              int error = ::booldog::enums::result::booerr_type_cannot_alloc_memory;
              return error;
            }
            dst->_buffer.allocsize = size;
          }
          dst->_buffer.size = size;
          unsigned char* yuv = (unsigned char*)dst->_buffer.buf;
          dst->_yuv[0] = yuv;
          dst->_yuv[1] = yuv + dst->_strides[0] * height;
          dst->_yuv[2] = dst->_yuv[1] + dst->_strides[1] * height;

          unsigned char* y = dst->_yuv[0], * u = dst->_yuv[1], * v = dst->_yuv[2];
          unsigned int y_offset = 0, uv_offset = 0, index = 0;
          while(index < size)
					{								
            y[y_offset++] = src[index];
            u[uv_offset] = src[++index];
            y[y_offset++] = src[++index];
            v[uv_offset++] = src[++index];
						++index;
          }
          return 0;
        }
      }
			struct yuv
			{
				bool isallocated;
				::booldog::byte* y;
				::booldog::byte* u;
				::booldog::byte* v;
				::booldog::uint32 y_width;
				::booldog::uint32 y_height;
				::booldog::uint32 u_width;
				::booldog::uint32 u_height;
				::booldog::uint32 v_width;
				::booldog::uint32 v_height;
								
				::booldog::multimedia::video::yuv* volatile _next;
				yuv(void)
					: y(0), u(0), v(0)
				{
                }
				booinline bool copyfrom(::booldog::result* pres, ::booldog::allocator* allocator, ::booldog::multimedia::video::frame* vframe, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
					if(isallocated == false)
						y = u = v = 0;
					switch(vframe->fourcc)
					{
					case ::booldog::enums::multimedia::image::YUYV:
                    case ::booldog::enums::multimedia::image::YUY2:
						{
							isallocated = true;
							y_width = vframe->width;
							y_height = vframe->height;
							v_width = u_width = vframe->width / 2;
							v_height = u_height = vframe->height;
							
							::booldog::uint32 y_size = y_width * y_height;
							::booldog::uint32 u_size = y_size / 2;
							::booldog::uint32 v_size = u_size;
							
							y = allocator->realloc_array< ::booldog::byte >(y, y_size, debuginfo);
							if(y == 0)
							{						
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							u = allocator->realloc_array< ::booldog::byte >(u, u_size, debuginfo);
							if(u == 0)
							{						
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							v = allocator->realloc_array< ::booldog::byte >(v, v_size, debuginfo);
							if(v == 0)
							{						
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							::booldog::uint32 y_offset = 0, uv_offset = 0, index = 0;
							while(index < vframe->size)
							{								
								y[y_offset++] = vframe->data[index];
								u[uv_offset] = vframe->data[++index];
								y[y_offset++] = vframe->data[++index];
								v[uv_offset++] = vframe->data[++index];
								++index;
							}
							break;
						}
					case ::booldog::enums::multimedia::image::YV16:
						{
							isallocated = true;
							y_width = vframe->width;
							y_height = vframe->height;
							v_width = u_width = vframe->width / 2;
							v_height = u_height = vframe->height;
							
							::booldog::uint32 y_size = y_width * y_height;
							::booldog::uint32 u_size = y_size / 2;
							::booldog::uint32 v_size = u_size;
							
							y = allocator->realloc_array< ::booldog::byte >(y, y_size, debuginfo);
							if(y == 0)
							{						
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							u = allocator->realloc_array< ::booldog::byte >(u, u_size, debuginfo);
							if(u == 0)
							{						
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							v = allocator->realloc_array< ::booldog::byte >(v, v_size, debuginfo);
							if(v == 0)
							{						
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							::memcpy(y, vframe->data, y_size);
							::memcpy(v, &vframe->data[y_size], v_size);
							::memcpy(u, &vframe->data[y_size + v_size], u_size);
							break;
						}
					case ::booldog::enums::multimedia::image::I422:
						{
							isallocated = true;
							y_width = vframe->width;
							y_height = vframe->height;
							v_width = u_width = vframe->width / 2;
							v_height = u_height = vframe->height;
							
							::booldog::uint32 y_size = y_width * y_height;
							::booldog::uint32 u_size = y_size / 2;
							::booldog::uint32 v_size = u_size;
							
							y = allocator->realloc_array< ::booldog::byte >(y, y_size, debuginfo);
							if(y == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							u = allocator->realloc_array< ::booldog::byte >(u, u_size, debuginfo);
							if(u == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							v = allocator->realloc_array< ::booldog::byte >(v, v_size, debuginfo);
							if(v == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							::memcpy(y, vframe->data, y_size);
							::memcpy(u, &vframe->data[y_size], v_size);
							::memcpy(v, &vframe->data[y_size + v_size], u_size);
							break;
						}
					case ::booldog::enums::multimedia::image::I420:
						{
							isallocated = true;
							y_width = vframe->width;
							y_height = vframe->height;
							v_width = u_width = vframe->width / 2;
							v_height = u_height = vframe->height / 2;
							
							::booldog::uint32 y_size = y_width * y_height;
							::booldog::uint32 u_size = v_width * v_height;
							::booldog::uint32 v_size = u_size;
							
							y = allocator->realloc_array< ::booldog::byte >(y, y_size, debuginfo);
							if(y == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							u = allocator->realloc_array< ::booldog::byte >(u, u_size, debuginfo);
							if(u == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							v = allocator->realloc_array< ::booldog::byte >(v, v_size, debuginfo);
							if(v == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							::memcpy(y, vframe->data, y_size); 
							::memcpy(u, &vframe->data[y_size], v_size);
							::memcpy(v, &vframe->data[y_size + v_size], u_size);
							break;
						}
					case ::booldog::enums::multimedia::image::YV12:
						{
							isallocated = true;
							y_width = vframe->width;
							y_height = vframe->height;
							v_width = u_width = vframe->width / 2;
							v_height = u_height = vframe->height / 2;
							
							::booldog::uint32 y_size = y_width * y_height;
							::booldog::uint32 u_size = v_width * v_height;
							::booldog::uint32 v_size = u_size;
							
							y = allocator->realloc_array< ::booldog::byte >(y, y_size, debuginfo);
							if(y == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							u = allocator->realloc_array< ::booldog::byte >(u, u_size, debuginfo);
							if(u == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							v = allocator->realloc_array< ::booldog::byte >(v, v_size, debuginfo);
							if(v == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							::memcpy(y, vframe->data, y_size);
							::memcpy(u, &vframe->data[y_size + v_size], u_size);
							::memcpy(v, &vframe->data[y_size], v_size);
							break;
						}
					default:
						res->booerr(::booldog::enums::result::booerr_type_video_format_is_not_supported);
						return false;
					}			
					return true;
				}
                booinline bool scale_copyfrom(::booldog::result* pres
                                              , ::booldog::allocator* allocator
                                              , ::booldog::multimedia::video::frame* vframe
                                              , ::booldog::uint32 scale_factor
                                              , const ::booldog::debug::info& debuginfo = debuginfo_macros)
                    {
                        ::booldog::result locres;
                        BOOINIT_RESULT(::booldog::result);
                        if(scale_factor == 1)
                            return copyfrom(res, allocator, vframe, debuginfo);

                        if(isallocated == false)
                                y = u = v = 0;
                        switch(vframe->fourcc)
                        {
                        case ::booldog::enums::multimedia::image::YUYV:
                        case ::booldog::enums::multimedia::image::YUY2:
                                {
                                        isallocated = true;
                                        y_width = vframe->width / scale_factor;
                                        y_height = vframe->height / scale_factor;
                                        v_width = u_width = y_width / 2;
                                        v_height = u_height = y_height;

                                        ::booldog::uint32 y_size = y_width * y_height;
                                        ::booldog::uint32 u_size = y_size / 2;
                                        ::booldog::uint32 v_size = u_size;

                                        y = allocator->realloc_array< ::booldog::byte >(y, y_size, debuginfo);
                                        if(y == 0)
                                        {
                                                res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                                return false;
                                        }
                                        u = allocator->realloc_array< ::booldog::byte >(u, u_size, debuginfo);
                                        if(u == 0)
                                        {
                                                res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                                return false;
                                        }
                                        v = allocator->realloc_array< ::booldog::byte >(v, v_size, debuginfo);
                                        if(v == 0)
                                        {
                                                res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                                return false;
                                        }

                                        ::booldog::uint32 src_y_width = 4 * vframe->width;
                                        //::booldog::uint32 src_y_height = vframe->height;
                                        //::booldog::uint32 src_u_width = y_width / 2;
                                        //::booldog::uint32 src_v_width = u_width;
                                        //::booldog::uint32 u_height = src_y_height;
                                        //::booldog::uint32 v_height = src_y_height;

                                        ::booldog::uint32 y_offset = 0, uv_offset = 0, index = 0, shift = 4 * (scale_factor - 1) + 1
                                                , line_shift = 4 * (scale_factor - 1 ) * src_y_width;

                                        while(index < vframe->size)
                                        {
                                                y[y_offset++] = vframe->data[index];
                                                u[uv_offset] = vframe->data[++index];
                                                y[y_offset++] = vframe->data[++index];
                                                v[uv_offset++] = vframe->data[++index];
                                                index += shift;
                                                if(index % src_y_width == 0)
                                                    index += line_shift;
                                        }
                                        break;
                                }
                        case ::booldog::enums::multimedia::image::YV16:
                                {
                                        isallocated = true;
                                        y_width = vframe->width / scale_factor;
                                        y_height = vframe->height / scale_factor;
                                        v_width = u_width = y_width / 2;
                                        v_height = u_height = y_height;

                                        ::booldog::uint32 y_size = y_width * y_height;
                                        ::booldog::uint32 u_size = y_size / 2;
                                        ::booldog::uint32 v_size = u_size;

                                        y = allocator->realloc_array< ::booldog::byte >(y, y_size, debuginfo);
                                        if(y == 0)
                                        {
                                                res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                                return false;
                                        }
                                        u = allocator->realloc_array< ::booldog::byte >(u, u_size, debuginfo);
                                        if(u == 0)
                                        {
                                                res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                                return false;
                                        }
                                        v = allocator->realloc_array< ::booldog::byte >(v, v_size, debuginfo);
                                        if(v == 0)
                                        {
                                                res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                                return false;
                                        }

                                        ::booldog::byte* ptr = vframe->data;
                                        for(::booldog::uint32 i = 0;i < y_size; ++i)
                                            y[i] = ptr[i * scale_factor];
                                        ptr += y_size;
                                        for(::booldog::uint32 i = 0;i < v_size; ++i)
                                            v[i] = ptr[i * scale_factor];
                                        ptr += v_size;
                                        for(::booldog::uint32 i = 0;i < u_size; ++i)
                                            u[i] = ptr[i * scale_factor];
                                        break;
                                }
                        default:
                                res->booerr(::booldog::enums::result::booerr_type_video_format_is_not_supported);
                                return false;
                        }
                        return true;
                    }
                };
            }
        }
}
#endif
