#ifndef BOO_MULTIMEDIA_VIDEO_SCALER_H
#define BOO_MULTIMEDIA_VIDEO_SCALER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER(header) <header>
#endif
#include BOOLDOG_HEADER(boo_allocator.h)
#include BOOLDOG_HEADER(boo_multimedia_graph_chain.h)
#include BOOLDOG_HEADER(boo_multimedia_enums.h)
//#include BOOLDOG_HEADER(boo_string_utils.h)
#include BOOLDOG_HEADER(boo_fps_counter.h)
#include BOOLDOG_HEADER(boo_time_utils.h)

extern "C"
{
//#include <libavcodec/avcodec.h>
//#include <libavutil/avconfig.h>
//#include <libavutil/opt.h>	
#include <libavutil/imgutils.h>	
#include <libswscale/swscale.h>
}

#include <stdio.h>
namespace booldog
{
	namespace multimedia
	{
		namespace video
		{
			class scaler : public ::booldog::multimedia::graph_chain
			{
			private:
				::booldog::allocator* _allocator;

				::booldog::uint32 _infourcc;
				::booldog::uint32 _inwidth;
				::booldog::uint32 _inheight;
				
				::booldog::uint32 _outwidth;
				::booldog::uint32 _outheight;

				::booldog::counters::fps _boofps;

				SwsContext* _sws;
				AVPixelFormat _av_pixel_format;
				::booldog::multimedia::video::frame _vframe;
                                AVFrame* _inframe;
                                AVFrame* _outframe;
                                ::booldog::uint32 _width_scale_factor;
                                ::booldog::uint32 _height_scale_factor;
                                bool _scale_factor;
			public:
				scaler(::booldog::allocator* allocator, ::booldog::typedefs::tickcount ptickcount)
					: _allocator(allocator), _infourcc(0xffffffff), _outwidth(320), _outheight(240)
                                        , _boofps(ptickcount), _sws(0), _inframe(0), _outframe(0), _width_scale_factor(2), _height_scale_factor(2)
                                        , _scale_factor(true)
				{
				}
				virtual ~scaler(void)
				{
					if(_vframe.data)
						_allocator->free(_vframe.data);
				}               
                                void width(::booldog::uint32 width)
				{
					_outwidth = width;
				}
                                void height(::booldog::uint32 height)
				{
					_outheight = height;
				}
                                void width_scale_factor(::booldog::uint32 scale_factor)
                                {
                                        _width_scale_factor = scale_factor;
                                }
                                void height_scale_factor(::booldog::uint32 scale_factor)
                                {
                                        _height_scale_factor = scale_factor;
                                }
                                booinline void scale_factor(bool val)
                                {
                                    _scale_factor = val;
                                }
				void initialize(::booldog::multimedia::video::frame* frame)
				{
					bool res = false;
                                        if(_scale_factor)
                                        {
                                            _outwidth = frame->width / _width_scale_factor;
                                            _outheight = frame->height / _height_scale_factor;
                                        }
                                        if( frame->width == _outwidth && frame->height == _outheight)
                                        {
                                            _infourcc = frame->fourcc;
                                            _inwidth = frame->width;
                                            _inheight = frame->height;
                                        }
                                        else
                                        {
                                            _av_pixel_format = AV_PIX_FMT_YUV420P;
                                            switch(frame->fourcc)
                                            {
                                                    case ::booldog::enums::multimedia::image::YUYV:
                                                            _av_pixel_format = AV_PIX_FMT_YUYV422;
                                                            break;
                                                    case ::booldog::enums::multimedia::image::I420:
                                                            _av_pixel_format = AV_PIX_FMT_YUV420P;
                                                            break;
                                            }
                                            _sws = sws_getCachedContext(_sws, frame->width, frame->height, _av_pixel_format, _outwidth, _outheight, _av_pixel_format, SWS_POINT, 0, 0, 0);
                                            if(_sws)
                                            {
                                                    _inframe = av_frame_alloc();
                                                    if(_inframe)
                                                    {
                                                            _inframe->format = _av_pixel_format;
                                                            _inframe->width = frame->width;
                                                            _inframe->height = frame->height;
                                                            _outframe = av_frame_alloc();
                                                            if(_outframe)
                                                            {
                                                                    _outframe->format = _av_pixel_format;
                                                                    _outframe->width = _outwidth;
                                                                    _outframe->height = _outheight;
                                                                    if(av_image_alloc(_outframe->data, _outframe->linesize, _outwidth
                                                                            , _outheight, _av_pixel_format, 32) < 0)
                                                                    {
                                                                            av_frame_free(&_outframe);
                                                                            _outframe = 0;
                                                                    }
                                                                    else
                                                                    {
                                                                            _infourcc = frame->fourcc;
                                                                            _inwidth = frame->width;
                                                                            _inheight = frame->height;
                                                                            res = true;
                                                                    }
                                                            }
                                                    }
                                            }
                                            if(res == false)
                                                    deinitialize();
                                        }
				}
				virtual void deinitialize(void)
				{
					if(_sws)
					{
						sws_freeContext(_sws);
						_sws = 0;
					}
                                        if(_inframe)
                                        {
                                                av_frame_free(&_inframe);
						_inframe = 0;
					}
					if(_outframe)
					{
						av_freep(&_outframe->data[0]);
						av_frame_free(&_outframe);
						_outframe = 0;
					}
					_infourcc = 0xffffffff;
				}
				virtual void onvideoframe(void* owner, void* owner_data
					, ::booldog::multimedia::video::typedefs::on_frame_t callback
					, ::booldog::multimedia::video::frame* frame)
				{
					if(frame->fourcc != _infourcc || frame->width != _inwidth 
						|| frame->height != _inheight)
					{
                                                deinitialize();
						initialize(frame);
					}
					_boofps.increment();
                                        if(_sws)
                                        {
                                            //printf("inframe av_image_fill_arrays %p\n", _inframe->data[0]);
                                            //int src_size = av_image_fill_pointers(_inframe->data, _av_pixel_format, frame->height, frame->data, _inframe->linesize);
                                            int src_size = av_image_fill_arrays(_inframe->data, _inframe->linesize, frame->data, _av_pixel_format, frame->width, frame->height, 1);
                                            if(src_size > 0)
                                            {
                                                //printf("inframe av_image_fill_arrays %p\n", _inframe->data[0]);
                                                    //printf("%d %u\n", src_size, frame->size);
                                                    if(sws_scale(_sws, _inframe->data, _inframe->linesize, 0, _inframe->height, _outframe->data, _outframe->linesize) == _outframe->height)
                                                    {
                                                            int dst_size = av_image_get_buffer_size(_av_pixel_format, _outframe->width, _outframe->height, 1);
                                                            if(_vframe.alloc_size < (::booldog::uint32)dst_size)
                                                            {
                                                                    _vframe.alloc_size = dst_size;
                                                                    _vframe.data = _allocator->realloc_array< ::booldog::byte >(
                                                                            (::booldog::byte*)_vframe.data, _vframe.alloc_size);
                                                            }
                                                            if(_vframe.data)
                                                            {
                                                                //printf("scaler callback0 %p\n", _vframe.data);
                                                                    if(av_image_copy_to_buffer(_vframe.data, dst_size, _outframe->data, _outframe->linesize, _av_pixel_format, _outwidth, _outheight, 1) > 0)
                                                                    {
                                                                            //printf("scaler callback %p\n", _vframe.data);
                                                                            _vframe.fourcc = _infourcc;
                                                                            _vframe.width = _outwidth;
                                                                            _vframe.height = _outheight;
                                                                            _vframe.size = (::booldog::uint32)dst_size;
                                                                            _vframe.timestamp = frame->timestamp;
                                                                            callback(owner, owner_data, &_vframe);
                                                                    }
                                                            }
                                                    }
                                            }
                                        }
                                        else
                                            callback(owner, owner_data, frame);
					if(_boofps.runtime() >= 1000ULL)
					{
						double gui_fps = _boofps.result();
						_boofps.reset();
						printf("Scaler video FPS %.1f\n", (float)gui_fps);
					}
				}
			};
		}
    }
}
#endif
