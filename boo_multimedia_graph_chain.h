#ifndef BOO_MULTIMEDIA_GRAPH_CHAIN_H
#define BOO_MULTIMEDIA_GRAPH_CHAIN_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_multimedia_video_frame.h"
#include "boo_multimedia_audio_frame.h"
namespace booldog
{
	namespace multimedia
	{
		namespace video
		{
			namespace typedefs
			{
				typedef void (*on_frame_t)(void* owner, void* owner_data, ::booldog::multimedia::video::frame* frame);
                        }
                }
		namespace audio
		{
			namespace typedefs
			{
				typedef void (*on_frame_t)(void* owner, void* owner_data, ::booldog::multimedia::audio::frame* frame);
                        }
                }
		class graph_chain
		{
		public:
			graph_chain* _doubly_linked_list_prev;
			graph_chain* _doubly_linked_list_next;
		public:
			virtual void onvideoframe(void* owner, void* owner_data
				, ::booldog::multimedia::video::typedefs::on_frame_t callback
				, ::booldog::multimedia::video::frame* frame)
			{
				owner = owner;
				owner_data = owner_data;
				callback = callback;
				frame = frame;
                        }
			virtual void onaudioframe(void* owner, void* owner_data
				, ::booldog::multimedia::audio::typedefs::on_frame_t callback
				, ::booldog::multimedia::audio::frame* frame)
			{
				owner = owner;
				owner_data = owner_data;
				callback = callback;
				frame = frame;
                        }
                        virtual void deinitialize(void)
                        {
                        }
                        virtual ~graph_chain(void)
                        {
                        }
		};
        }
}
#endif
