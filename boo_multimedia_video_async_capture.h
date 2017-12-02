#ifndef BOO_MULTIMEDIA_VIDEO_ASYNC_CAPTURE_H
#define BOO_MULTIMEDIA_VIDEO_ASYNC_CAPTURE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_multimedia_video_capture.h"
#include "boo_thread.h"
#include "boo_threading_event.h"

#include <stdio.h>
namespace booldog
{
	namespace multimedia
	{
		namespace video
		{
			namespace async
			{
				class capture;
			}
		}
	}
	namespace results
	{
		namespace multimedia
		{
			namespace video
			{
				namespace async
				{
					class capture : public ::booldog::result
					{
					private:
						capture(const ::booldog::result&)
						{
                                                }
						capture(const ::booldog::results::multimedia::video::async::capture&)
                                                    : result()
						{
                                                }
						::booldog::results::multimedia::video::async::capture& operator = 
							(const ::booldog::results::multimedia::video::async::capture&)
						{
							return *this;
                                                }
					public:
						::booldog::multimedia::video::async::capture* video;
						capture(void)
							: video(0)
						{
                                                }
						virtual ~capture(void)
						{
                                                }
						virtual void clear(void) const
						{
							::booldog::results::multimedia::video::async::capture* _obj_ 
								= const_cast< ::booldog::results::multimedia::video::async::capture* >(this);
#ifdef __UNIX__
							_obj_->dlerrorclear();
#endif
							_obj_->error_type = ::booldog::enums::result::error_type_no_error;
							_obj_->video = 0;
                                                }
					};
                                }
                        }
                }
        }
	namespace multimedia
	{
		namespace video
		{
			namespace async
			{
				class capture
				{
					friend class ::booldog::allocator;
				private:
					::booldog::allocator* _allocator;
					::booldog::threading::thread* _thread;
					::booldog::multimedia::video::capture* _video;
					::booldog::multimedia::video::typedefs::read_frame_callback_t _read_frame_callback;
					void* _read_frame_callback_udata;
					::booldog::uint32 _fourcc;
					::booldog::uint32 _width;
					::booldog::uint32 _height;
					::booldog::uint32 _framerate_numerator;
                    ::booldog::uint32 _framerate_denominator;
                    bool _suspended;
                    ::booldog::threading::event _suspend_event;
#ifdef __WINDOWS__
                    bool _is_preview;
#endif
				private:
                    capture(::booldog::allocator* allocator)
                        : _allocator(allocator), _thread(0), _suspended(false), _suspend_event(0, debuginfo_macros)
#ifdef __WINDOWS__
                        , _is_preview(false)
#endif
					{
					}
					capture(const ::booldog::multimedia::video::async::capture&)
                                            : _suspend_event(0, debuginfo_macros)
					{
					}
					::booldog::multimedia::video::async::capture& operator = (const ::booldog::multimedia::video::async::capture&)
					{
						return *this;
                    }
                    static ::booldog::uint32 tickcount(void)
                    {
                    #ifdef __LINUX__
                        struct timespec ts = {};
                        if(clock_gettime(CLOCK_MONOTONIC, &ts))
                            clock_gettime(CLOCK_REALTIME, &ts);
                        return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
                    #else
                        return 0;
                    #endif
                    }
				public:
					~capture()
					{
                    }
#ifdef __WINDOWS__
                    void is_preview(bool value)
                    {
                        _is_preview = value;
                    }
#endif
					static void thread(::booldog::threading::thread* thread)
                    {
                        ::booldog::multimedia::video::async::capture* capture =
                                (::booldog::multimedia::video::async::capture*)thread->udata();
                        for(;;)
                        {
                            capture->_suspend_event.sleep(0, debuginfo_macros);
                            if(thread->pending_in_stop())
                                break;
                            if(capture->_suspended)
                                continue;
                            ::booldog::result_bool resbool;

                            ::booldog::uint32 ttick = tickcount();

                            if(capture->_video->is_capturing() == false)
                            {
                                ::booldog::uint32 ttick = tickcount();
#ifdef __WINDOWS__
                                capture->_video->is_preview(capture->_is_preview);
#endif
                                if(capture->_video->is_opened() == false || capture->_video->start_capturing(0, capture->_fourcc, capture->_width, capture->_height, capture->_framerate_numerator, capture->_framerate_denominator, debuginfo_macros) == false)
                                {
                                    printf("async video capture, start failed\n");
                                    if(capture->_video->is_opened())
                                    {
                                        while(capture->_video->close(0, false, debuginfo_macros) == false)
                                            ::booldog::threading::sleep(1);
                                    }
                                    for(;;)
                                    {
                                        if(capture->_video->open(0, capture->_video->name(), debuginfo_macros))
                                        {
#ifdef __WINDOWS__
                                            capture->_video->is_preview(capture->_is_preview);
#endif
                                            if(capture->_video->start_capturing(0, capture->_fourcc, capture->_width, capture->_height, capture->_framerate_numerator, capture->_framerate_denominator, debuginfo_macros))
                                                break;
                                            else
                                            {
                                                printf("async video capture, start failed again\n");
                                                while(capture->_video->close(0, false, debuginfo_macros) == false)
                                                    ::booldog::threading::sleep(1);
                                            }
                                        }
                                        else
                                            printf("async video capture, open failed\n");
                                        if(thread->pending_in_stop() || capture->_suspended)
                                            break;
                                    }
                                }
                                else
                                {
                                    ::booldog::uint32 now = tickcount();
                                    if(now - ttick >= 10)
                                        printf("video async capture, start_capturing %u\n", now - ttick);
                                }
                            }
                            ::booldog::uint32 now = tickcount();
                            if(now - ttick >= 20)
                                printf("video async capture %u\n", now - ttick);
                            for(;;)
                            {
                                if(thread->pending_in_stop() || capture->_suspended)
                                        break;
                                if(capture->_video->is_frame_available(&resbool) && resbool.bres)
                                {
                                    capture->_video->read_frame(0, capture->_read_frame_callback, capture->_read_frame_callback_udata
                                            , debuginfo_macros);
                                }
#ifdef __WINDOWS__
                                else
                                    ::booldog::threading::sleep(1);
#endif
                            }
                            while(capture->_video->stop_capturing(0, debuginfo_macros) == false)
                                ::booldog::threading::sleep(1);
                        }
						if(capture->_video->is_opened())
							capture->_video->close(0, false, debuginfo_macros);
					}
					static bool open(::booldog::results::multimedia::video::async::capture* pres, ::booldog::allocator* allocator
						, const char* name, const ::booldog::debug::info& debuginfo = debuginfo_macros)
					{
						::booldog::results::multimedia::video::async::capture locres;
						BOOINIT_RESULT(::booldog::results::multimedia::video::async::capture);						
						::booldog::results::multimedia::video::capture capture;
						if(::booldog::multimedia::video::capture::open(&capture, allocator, name, debuginfo))
						{
							res->video = allocator->create< ::booldog::multimedia::video::async::capture >(allocator, debuginfo);
							if(res->video)
							{
								res->video->_video = capture.video;
#ifdef __WINDOWS__
								capture.video->close(0, false, debuginfo);
#endif
								return true;
							}
							else
							{
								capture.video->close(0, true, debuginfo);
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
						}
						else
							res->copy(capture);
						return false;
					}
					booinline bool close(::booldog::result* pres, const ::booldog::debug::info& debuginfo = debuginfo_macros)
					{
                        debuginfo = debuginfo;
                        ::booldog::result locres;
                        BOOINIT_RESULT(::booldog::result);
						_video->close(res, true, debuginfo);
                        _allocator->destroy(this);
                        return res->succeeded();
                    }
					booinline bool stop_capturing(::booldog::result* pres, const ::booldog::debug::info& debuginfo = debuginfo_macros)
					{
                        ::booldog::result locres;
                        BOOINIT_RESULT(::booldog::result);
                        ::booldog::threading::thread::stop(_thread);
                        _suspend_event.wake(0, debuginfo);
                        ::booldog::threading::thread::wait_for_stop(_thread);
                        ::booldog::threading::thread::destroy(_thread);
                        _thread = 0;
                        return _video->stop_capturing(res, debuginfo);
					}
					booinline bool stop_capturing_async(::booldog::result* pres, const ::booldog::debug::info& debuginfo = debuginfo_macros)
					{
                        debuginfo = debuginfo;
                        ::booldog::result locres;
                        BOOINIT_RESULT(::booldog::result);
                        ::booldog::threading::thread::stop(_thread);
                        _suspend_event.wake(0, debuginfo);
                        return true;
					}
					booinline bool start_capturing(::booldog::result* pres, ::booldog::uint32 fourcc, ::booldog::uint32 width
						, ::booldog::uint32 height, ::booldog::uint32 framerate_numerator, ::booldog::uint32 framerate_denominator
						, ::booldog::multimedia::video::typedefs::read_frame_callback_t read_frame_callback
						, void* read_frame_callback_udata, const ::booldog::debug::info& debuginfo = debuginfo_macros)
					{
						::booldog::result locres;
						BOOINIT_RESULT(::booldog::result);
                        if(_video->is_opened() == false)
                            _video->open(res, _video->name(), debuginfo_macros);
                        if(res->succeeded())
                        {
                            if(_video->start_capturing(res, fourcc, width, height, framerate_numerator, framerate_denominator, debuginfo))
                            {
                                    _read_frame_callback = read_frame_callback;
                                    _read_frame_callback_udata = read_frame_callback_udata;
                                    _thread = ::booldog::threading::thread::create(0, _allocator, 30 * 1024, 0, 0, thread, this);
                                    _suspend_event.wake(0, debuginfo);
                            }
						}
						return res->succeeded();
					}					
					booinline bool start_capturing_async(::booldog::result* pres, ::booldog::uint32 fourcc, ::booldog::uint32 width
						, ::booldog::uint32 height, ::booldog::uint32 framerate_numerator, ::booldog::uint32 framerate_denominator
						, ::booldog::multimedia::video::typedefs::read_frame_callback_t read_frame_callback
						, void* read_frame_callback_udata, const ::booldog::debug::info& debuginfo = debuginfo_macros)
                    {
                        debuginfo = debuginfo;
                        ::booldog::result locres;
                        BOOINIT_RESULT(::booldog::result);

                        _fourcc = fourcc;
                        _width = width;
                        _height = height;
                        _framerate_numerator = framerate_numerator;
                        _framerate_denominator = framerate_denominator;
                        _read_frame_callback = read_frame_callback;
                        _read_frame_callback_udata = read_frame_callback_udata;
                        _thread = ::booldog::threading::thread::create(0, _allocator, 30 * 1024, 0, 0, thread, this);
                        _suspend_event.wake(0, debuginfo);

                        return res->succeeded();
					}
					booinline bool is_capturing()
                    {
                        return _thread != 0;
					}
					booinline bool available_formats(::booldog::result* pres, ::booldog::allocator* allocator
						, ::booldog::multimedia::video::typedefs::available_formats_callback_t callback, void* udata
						, const ::booldog::debug::info& debuginfo = debuginfo_macros)
                    {
                        return _video->available_formats(pres, allocator, callback, udata, debuginfo);
					}
                    booinline void suspend(const ::booldog::debug::info& debuginfo = debuginfo_macros)
                    {
                        _suspended = true;
                        _suspend_event.wake(0, debuginfo);
                    }
                    booinline void resume(const ::booldog::debug::info& debuginfo = debuginfo_macros)
                    {
                        _suspended = false;
                        _suspend_event.wake(0, debuginfo);
                    }
				};
                        }
                }
        }
}
#endif
