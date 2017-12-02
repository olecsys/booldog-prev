#ifndef BOO_MULTIMEDIA_VIDEO_YUV_H
#define BOO_MULTIMEDIA_VIDEO_YUV_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_multimedia_video_frame.h"
#include "boo_multimedia_enums.h"
namespace booldog
{
	namespace multimedia
	{
		namespace video
		{
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
