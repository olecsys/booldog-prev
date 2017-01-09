#ifndef BOO_MULTIMEDIA_AUDIO_ASYNC_CAPTURE_H
#define BOO_MULTIMEDIA_AUDIO_ASYNC_CAPTURE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER(header) <header>
#endif
#include BOOLDOG_HEADER(boo_multimedia_audio_capture.h)
#include BOOLDOG_HEADER(boo_thread.h)
#include BOOLDOG_HEADER(boo_threading_event.h)
#include BOOLDOG_HEADER(boo_lockfree_queue.h)

#include <stdio.h>
namespace booldog
{
	namespace multimedia
	{
		namespace audio
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
			namespace audio
			{
				namespace async
				{
					class capture : public ::booldog::result
					{
					private:
						capture(const ::booldog::result&)
						{
                                                }
						capture(const ::booldog::results::multimedia::audio::async::capture&)
                                                    : result()
						{
                                                }
						::booldog::results::multimedia::audio::async::capture& operator = 
							(const ::booldog::results::multimedia::audio::async::capture&)
						{
							return *this;
                                                }
					public:
						::booldog::multimedia::audio::async::capture* audio;
						capture(void)
							: audio(0)
						{
                                                }
						virtual ~capture(void)
						{
                                                }
						virtual void clear(void) const
						{
							::booldog::results::multimedia::audio::async::capture* _obj_ 
								= const_cast< ::booldog::results::multimedia::audio::async::capture* >(this);
#ifdef __UNIX__
							_obj_->dlerrorclear();
#endif
							_obj_->error_type = ::booldog::enums::result::error_type_no_error;
							_obj_->audio = 0;
                                                }
					};
                                }
                        }
                }
        }
	namespace multimedia
	{
		namespace audio
		{
			namespace async
			{
				class capture
				{
					friend class ::booldog::allocator;
				private:
                                        ::booldog::allocator* _allocator;
                                        ::booldog::threading::thread* _read_thread;
					::booldog::multimedia::audio::capture* _audio;
					::booldog::multimedia::audio::typedefs::read_frame_callback_t _read_frame_callback;
					void* _read_frame_callback_udata;
                                        ::booldog::data::lockfree::queue< ::booldog::multimedia::audio::frame > _samples;
                                        ::booldog::data::lockfree::queue< ::booldog::multimedia::audio::frame > _avail_samples;
                                        ::booldog::uint32 _samples_count;
				private:
					capture(::booldog::allocator* allocator)
                                                : _allocator(allocator), _read_thread(0), _samples_count(120)
					{
                                        }
                                        capture(const ::booldog::multimedia::audio::async::capture&)
					{
                                        }
					::booldog::multimedia::audio::async::capture& operator = (const ::booldog::multimedia::audio::async::capture&)
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
					~capture(void)
					{
                                            for(;;)
                                            {
                                                    ::booldog::multimedia::audio::frame* next = _samples.dequeue();
                                                    if(next)
                                                    {
                                                            if(next->data)
                                                                    _allocator->free(next->data);
                                                            _allocator->destroy(next);
                                                    }
                                                    else
                                                            break;
                                            }
                                            for(;;)
                                            {
                                                    ::booldog::multimedia::audio::frame* next = _avail_samples.dequeue();
                                                    if(next)
                                                    {
                                                            if(next->data)
                                                                    _allocator->free(next->data);
                                                            _allocator->destroy(next);
                                                    }
                                                    else
                                                            break;
                                            }
					}
                                        static void callback_thread(::booldog::threading::thread* thread)
					{
						::booldog::multimedia::audio::async::capture* capture = 
							(::booldog::multimedia::audio::async::capture*)thread->udata();
						for(;;)
                                                {
                                                    ::booldog::multimedia::audio::frame* sample = capture->_samples.dequeue();
                                                    if(sample)
                                                    {
                                                        capture->_read_frame_callback(capture->_allocator, capture->_read_frame_callback_udata, sample);
                                                        capture->_avail_samples.enqueue(sample);
                                                    }
                                                    else
                                                        ::booldog::threading::sleep(1);
                                                    if(thread->pending_in_stop())
                                                        break;
						}
                                        }
                                        static void read_thread(::booldog::threading::thread* thread)
                                        {
                                                ::booldog::multimedia::audio::async::capture* capture =
                                                        (::booldog::multimedia::audio::async::capture*)thread->udata();
                                            /*::booldog::multimedia::audio::frame* sample = 0;
                                            ::booldog::uint32 count = 0;
                                            while(count != capture->_samples_count)
                                            {
                                                sample = capture->_avail_samples.dequeue();
                                                if(sample == 0)
                                                {
                                                    sample = capture->_allocator->create< ::booldog::multimedia::audio::frame >(debuginfo_macros);
                                                    if(sample == 0)
                                                        break;
                                                }
                                                if(capture->_audio->prepare_frame(0, capture->_allocator, sample, debuginfo_macros) == false)
                                                {
                                                    if(sample->data)
                                                        capture->_allocator->free(sample->data);
                                                    capture->_allocator->destroy(sample);
                                                    for(;;)
                                                    {
                                                            sample = capture->_avail_samples.dequeue();
                                                            if(sample)
                                                            {
                                                                    if(sample->data)
                                                                            capture->_allocator->free(sample->data);
                                                                    capture->_allocator->destroy(sample);
                                                            }
                                                            else
                                                                    break;
                                                    }
                                                    break;
                                                }
                                                capture->_samples.enqueue(sample);
                                                ++count;
                                            }
                                            for(;;)
                                            {
                                                    sample = capture->_samples.dequeue();
                                                    if(sample)
                                                        capture->_avail_samples.enqueue(sample);
                                                    else
                                                        break;
                                            }
                                            ::booldog::threading::thread* _thread = ::booldog::threading::thread::create(0, capture->_allocator, 30 * 1024, 0, 0, callback_thread, capture);
                                            */
                                                ::booldog::result_bool resbool;
                                                for(;;)
                                                {
                                                        if(capture->_audio->is_frame_available(&resbool) && resbool.bres)
                                                        {
                                                            {
                                                                ::booldog::uint32 ttick = tickcount();

                                                                //sample = capture->_avail_samples.dequeue();

                                                                ::booldog::uint32 now = tickcount();
                                                                if(now - ttick > 10)
                                                                    printf("avail_samples %u\n", now - ttick);

                                                                //if(sample)
                                                                {
                                                                    //::booldog::uint32 ttick0 = tickcount();
                                                                    if(capture->_audio->read_frame(0, capture->_read_frame_callback, capture->_read_frame_callback_udata, debuginfo_macros))
                                                                    //if(capture->_audio->read_frame(0, sample, debuginfo_macros))
                                                                    {


                                                                        //capture->_read_frame_callback(capture->_allocator, capture->_read_frame_callback_udata, sample);
                                                                        //capture->_avail_samples.enqueue(sample);



                                                                        /*now = tickcount();
                                                                        if(now - ttick0 > 10)
                                                                            printf("read_frame %u\n", now - ttick0);


                                                                        ttick0 = tickcount();
                                                                        capture->_samples.enqueue(sample);

                                                                        now = tickcount();
                                                                        if(now - ttick0 > 10)
                                                                            printf("samples.enqueue %u\n", now - ttick0);


                                                                        now = tickcount();
                                                                        if(now - ttick > 22)
                                                                            printf("read_audio %u\n", now - ttick);*/
                                                                    }
                                                                    else
                                                                    {
                                                                        printf("read sample error\n");
                                                                        //capture->_avail_samples.enqueue(sample);
                                                                    }
                                                                }
                                                                //else
                                                                //    printf("cannot get sample from avail\n");
                                                            }
                                                        }
                                                        if(thread->pending_in_stop())
                                                                break;
                                                }                                                
                                                //::booldog::threading::thread::stop(_thread);
                                                //::booldog::threading::thread::wait_for_stop(_thread);
                                                //::booldog::threading::thread::destroy(_thread);
                                        }
					static bool open(::booldog::results::multimedia::audio::async::capture* pres, ::booldog::allocator* allocator, ::booldog::typedefs::tickcount ptickcount
						, const char* name, const ::booldog::debug::info& debuginfo = debuginfo_macros)
					{
						::booldog::results::multimedia::audio::async::capture locres;
						BOOINIT_RESULT(::booldog::results::multimedia::audio::async::capture);						
						::booldog::results::multimedia::audio::capture capture;
						if(::booldog::multimedia::audio::capture::open(&capture, allocator, ptickcount, name, debuginfo))
						{
							res->audio = allocator->create< ::booldog::multimedia::audio::async::capture >(allocator, debuginfo);
							if(res->audio)
							{
								res->audio->_audio = capture.audio;
								return true;
							}
							else
							{
								capture.audio->close(0);
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
						_audio->close(res);						
						_allocator->destroy(this);
						return res->succeeded();
                                        }
					booinline bool stop_capturing(::booldog::result* pres, const ::booldog::debug::info& debuginfo = debuginfo_macros)
					{
						::booldog::result locres;
                                                BOOINIT_RESULT(::booldog::result);
                                                ::booldog::threading::thread::stop(_read_thread);
                                                ::booldog::threading::thread::wait_for_stop(_read_thread);
                                                ::booldog::threading::thread::destroy(_read_thread);
                                                _read_thread = 0;

                                                ::booldog::multimedia::audio::frame* sample = 0;
                                                for(;;)
                                                {
                                                    sample = _samples.dequeue();
                                                    if(sample)
                                                        _avail_samples.enqueue(sample);
                                                    else
                                                        break;
                                                }
						return _audio->stop_capturing(res, debuginfo);
					}
					booinline bool start_capturing(::booldog::result* pres, ::booldog::uint32 fourcc, ::booldog::multimedia::audio::typedefs::read_frame_callback_t read_frame_callback
						, void* read_frame_callback_udata, const ::booldog::debug::info& debuginfo = debuginfo_macros)
					{
						::booldog::result locres;
						BOOINIT_RESULT(::booldog::result);
						if(_audio->start_capturing(res, fourcc, debuginfo))
						{					
							_read_frame_callback = read_frame_callback;
							_read_frame_callback_udata = read_frame_callback_udata;							
                                                        _read_thread = ::booldog::threading::thread::create(0, _allocator, 30 * 1024, 0, 0, read_thread, this);
						}
						return res->succeeded();
                                        }
                                        booinline bool is_capturing(void)
                                        {
                                                return _read_thread != 0;
                                        }
				};
                        }
                }
        }
}
#endif
