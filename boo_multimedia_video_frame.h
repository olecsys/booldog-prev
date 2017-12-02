#ifndef BOO_MULTIMEDIA_VIDEO_FRAME_H
#define BOO_MULTIMEDIA_VIDEO_FRAME_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_types.h"
#include "boo_result.h"
#include "boo_error.h"
namespace booldog
{
	namespace multimedia
	{
		namespace video
		{
			struct frame
			{
				::booldog::uint32 fourcc;
				::booldog::uint32 width;
				::booldog::uint32 height;				
				::booldog::uint32 size;				
				::booldog::uint64 timestamp;

                                ::booldog::uint32 alloc_size;
                                ::booldog::byte* data;
				::booldog::multimedia::video::frame* volatile _next;
				frame(void)
                                        : fourcc(0xffffffff), width(0), height(0), size(0), timestamp(0), alloc_size(0), data(0)
				{
                                }
				booinline bool copyfrom(::booldog::result* pres, ::booldog::allocator* allocator, ::booldog::multimedia::video::frame* vframe, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
					if(alloc_size < vframe->size)
					{
						alloc_size = vframe->size;						
						data = allocator->realloc_array< ::booldog::byte >(data, alloc_size, debuginfo);
						if(data == 0)
						{						
							res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							return false;
						}
					}
					fourcc = vframe->fourcc;
					width = vframe->width;
					height = vframe->height;
					size = vframe->size;
					timestamp = vframe->timestamp;
					::memcpy(data, vframe->data, vframe->size);					
					return true;
                                }
			};
                }
        }
}
#endif
