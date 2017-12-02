#ifndef BOO_MULTIMEDIA_AUDIO_FRAME_H
#define BOO_MULTIMEDIA_AUDIO_FRAME_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_result.h"
#include "boo_error.h"
namespace booldog
{
	namespace multimedia
	{
		namespace audio
		{
			struct frame
			{
				::booldog::uint32 fourcc;
				::booldog::uint32 bytes_per_sample;
				::booldog::uint32 channels;
				::booldog::uint32 sample_rate;				
				::booldog::uint32 size;
                                ::booldog::uint64 timestamp;

				::booldog::uint32 alloc_size;				
                                ::booldog::byte* data;
				::booldog::multimedia::audio::frame* volatile _next;
				frame(void)
                                        : fourcc(0xffffffff), size(0), timestamp(0), alloc_size(0), data(0)
				{
                                }
				booinline bool copyfrom(::booldog::result* pres, ::booldog::allocator* allocator, ::booldog::multimedia::audio::frame* aframe, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
					if(alloc_size < aframe->size)
					{
						alloc_size = aframe->size;						
						data = allocator->realloc_array< ::booldog::byte >(data, alloc_size, debuginfo);
						if(data == 0)
						{						
							res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							return false;
						}
					}
					fourcc = aframe->fourcc;
					bytes_per_sample = aframe->bytes_per_sample;
					channels = aframe->channels;
					sample_rate = aframe->sample_rate;
					size = aframe->size;
					timestamp = aframe->timestamp;					
					::memcpy(data, aframe->data, aframe->size);					
					return true;
                                }
			};
                }
        }
}
#endif
