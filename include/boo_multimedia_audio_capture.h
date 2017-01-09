/*
  sudo apt-get install libasound2-dev
  name example: hw:0
*/
#ifndef BOO_MULTIMEDIA_AUDIO_CAPTURE_H
#define BOO_MULTIMEDIA_AUDIO_CAPTURE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER(header) <header>
#endif

#include BOOLDOG_HEADER(boo_multimedia_audio_frame.h)
#include BOOLDOG_HEADER(boo_multimedia_enums.h)
#include BOOLDOG_HEADER(boo_error.h)
#include BOOLDOG_HEADER(boo_result.h)
#include BOOLDOG_HEADER(boo_time_utils.h)

#include BOOLDOG_HEADER(boo_fps_counter.h)

#include <alsa/asoundlib.h>

#include <stdio.h>
namespace booldog
{
	namespace multimedia
	{
		namespace audio
		{
			class capture;
                }
        }
	namespace results
	{
		namespace multimedia
		{
			namespace audio
			{
				class capture : public ::booldog::result
				{
				private:
					capture(const ::booldog::result&)
					{
                                        }
					capture(const ::booldog::results::multimedia::audio::capture&)
                                            : result()
					{
                                        }
					::booldog::results::multimedia::audio::capture& operator = 
						(const ::booldog::results::multimedia::audio::capture&)
					{
						return *this;
                                        }
				public:
					::booldog::multimedia::audio::capture* audio;
					capture(void)
						: audio(0)
					{
                                        }
					virtual ~capture(void)
					{
                                        }
					virtual void clear(void) const
					{
						::booldog::results::multimedia::audio::capture* _obj_ 
							= const_cast< ::booldog::results::multimedia::audio::capture* >(this);
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
	namespace multimedia
	{		
		namespace audio
		{
			namespace typedefs
			{
				typedef void (*read_frame_callback_t)(::booldog::allocator* allocator, void* udata, ::booldog::multimedia::audio::frame* aframe);
                        }
			class capture
			{	
				friend class ::booldog::allocator;
			private:
				bool _snd_pcm_started;
				::booldog::counters::fps _boofps;
			
				::booldog::allocator* _allocator;

				snd_pcm_t* _snd_pcm;

				int _bytes_per_sample;
				unsigned int _channels;
				snd_pcm_uframes_t _buffer_frames;
				char* _buffer;
				struct pollfd* _ufds;
				unsigned int _ufds_count;
				::booldog::uint32 _buffer_size;
				::booldog::uint32 _fourcc;
				::booldog::uint64 _timestamp;
                                ::booldog::uint32 _sample_rate;
			private:
				capture(::booldog::allocator* allocator, ::booldog::typedefs::tickcount ptickcount, snd_pcm_t* snd_pcm)
                                        : _boofps(ptickcount), _allocator(allocator)
                                        , _snd_pcm(snd_pcm), _buffer_frames(0), _buffer(0)
                                        , _ufds(0), _sample_rate(48000)
				{
                                }
				capture(const ::booldog::multimedia::audio::capture&)
					: _boofps(0)
				{
                                }
				::booldog::multimedia::audio::capture& operator = (const ::booldog::multimedia::audio::capture&)
				{
					return *this;
                                }
			public:				
				~capture(void)
				{
					if(_ufds)
						_allocator->free(_ufds);
					if(_buffer)
						_allocator->free(_buffer);
				}
				static bool open(::booldog::results::multimedia::audio::capture* pres, ::booldog::allocator* allocator, ::booldog::typedefs::tickcount ptickcount
					, const char* name, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::results::multimedia::audio::capture locres;
					BOOINIT_RESULT(::booldog::results::multimedia::audio::capture);
	#ifdef __LINUX__
					snd_pcm_t* snd_pcm = 0;
					int err = snd_pcm_open(&snd_pcm, name, SND_PCM_STREAM_CAPTURE, 0);
					if(err < 0)
					{
						res->setalsaerror(err);
						return false;
					}
					else
					{
						res->audio = allocator->create< ::booldog::multimedia::audio::capture >(allocator, ptickcount, snd_pcm, debuginfo);
						if(res->audio == 0)
						{
							snd_pcm_close(snd_pcm);
							res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							return false;
						}
						return true;
					}
	#else
					allocator = allocator;
					name = name;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);			
					return res->succeeded();
	#endif									
                                }
				booinline bool close(::booldog::result* pres, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__
					int err = snd_pcm_close(_snd_pcm);
					if(err < 0)
						res->setalsaerror(err);
#else
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
#endif
					_allocator->destroy(this);
					return res->succeeded();
                                }
				booinline bool stop_capturing(::booldog::result* pres, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
                                    debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);

                                        int err = snd_pcm_drop(_snd_pcm);
                                        if(err < 0)
                                        {
                                            res->setalsaerror(err);
                                            return false;
                                        }
                                        _snd_pcm_started = false;
                                        return true;
				}
				booinline bool start_capturing(::booldog::result* pres, ::booldog::uint32 fourcc
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
                                    fourcc = fourcc;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
					
#ifdef __LINUX__
                                        unsigned int min_channels = 0, max_channels = 0, buffer_time = 0;
					_snd_pcm_started = false;
					_bytes_per_sample = 0;
                                        _channels = 2;
					_timestamp = 0;
					//snd_pcm_uframes_t buffer_size = 0;
					
					int dir = 0;
                                        _buffer_frames = 0;
                                        snd_pcm_uframes_t buffer_frames = 8 * _buffer_frames;
					
                                        unsigned int rate = _sample_rate;
					snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;
					//snd_pcm_format_t format = SND_PCM_FORMAT_FLOAT_LE;

                                        snd_pcm_sw_params_t* sw_params = 0;
					snd_pcm_hw_params_t* hw_params = 0;
					int err = snd_pcm_hw_params_malloc(&hw_params);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));
						res->setalsaerror(err);
						goto goto_return;
					}
					err = snd_pcm_hw_params_any(_snd_pcm, hw_params);
					if(err < 0)
					{
										printf("%d, error %s\n", __LINE__, snd_strerror(err));
						res->setalsaerror(err);
						goto goto_return;
					}
					err = snd_pcm_hw_params_set_access(_snd_pcm, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}
					err = snd_pcm_hw_params_set_format(_snd_pcm, hw_params, format);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}
					err = snd_pcm_hw_params_set_rate_near(_snd_pcm, hw_params, &rate, 0);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
                                        }
					
					err = snd_pcm_hw_params_test_channels(_snd_pcm, hw_params, _channels);
					if(err < 0)
					{
						err = snd_pcm_hw_params_get_channels_min(hw_params, &min_channels);
						if(err < 0)
						{
						printf("%d, error %s\n", __LINE__, snd_strerror(err));					
							res->setalsaerror(err);
							goto goto_return;
						}
						err = snd_pcm_hw_params_get_channels_max(hw_params, &max_channels);
						if(err < 0)
						{
						printf("%d, error %s\n", __LINE__, snd_strerror(err));					
							res->setalsaerror(err);
							goto goto_return;
						}		
						for(unsigned int i = min_channels;i <= max_channels; ++i) 
						{
							if(snd_pcm_hw_params_test_channels(_snd_pcm, hw_params, i) == 0)
								printf("channels %u\n", i);
						}						
					}
					else
					{					
						err = snd_pcm_hw_params_set_channels(_snd_pcm, hw_params, _channels);
						if(err < 0)
						{
						printf("%d, error %s\n", __LINE__, snd_strerror(err));					
							res->setalsaerror(err);
							goto goto_return;
						}
					}
                                        if(_buffer_frames == 0)
                                        {
                                            err = snd_pcm_hw_params_get_buffer_time_max(hw_params, &buffer_time, &dir);
                                            if(err < 0)
                                            {
                                                printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                    res->setalsaerror(err);
                                                    goto goto_return;
                                            }
                                            if(buffer_time > 500000)
                                                buffer_time = 500000;

                                            err = snd_pcm_hw_params_set_buffer_time_near(_snd_pcm, hw_params, &buffer_time, &dir);
                                            if(err < 0)
                                            {
                                                printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                    res->setalsaerror(err);
                                                    goto goto_return;
                                            }
                                            buffer_time /= 4;
                                            err = snd_pcm_hw_params_set_period_time_near(_snd_pcm, hw_params, &buffer_time, &dir);
                                            if(err < 0)
                                            {
                                                printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                    res->setalsaerror(err);
                                                    goto goto_return;
                                            }
                                        }
                                        else
                                        {
                                            err = snd_pcm_hw_params_set_period_size_near(_snd_pcm, hw_params, &_buffer_frames, &dir);
                                            if(err < 0)
                                            {
                                            printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                    res->setalsaerror(err);
                                                    goto goto_return;
                                            }

                                            err = snd_pcm_hw_params_set_buffer_size_near(_snd_pcm, hw_params, &buffer_frames);
                                            if(err < 0)
                                            {
                                            printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                    res->setalsaerror(err);
                                                    goto goto_return;
                                            }
                                        }

					err = snd_pcm_hw_params(_snd_pcm, hw_params);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
                                        }
					
					err = snd_pcm_hw_params_get_sbits(hw_params);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}
					_bytes_per_sample = err / 8;
                                        printf("bytes per sample %d\n", err);
					
					err = snd_pcm_hw_params_get_channels(hw_params, &_channels); 
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}
					printf("channels %u\n", _channels);
					
                                        err = snd_pcm_hw_params_get_buffer_size(hw_params, &buffer_frames);
                                        if(err < 0)
                                        {
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }
                                        printf("buffer size %u\n", (::booldog::uint32)buffer_frames);

					err = snd_pcm_hw_params_get_period_size(hw_params, &_buffer_frames, &dir);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}
					printf("period size %u\n", (::booldog::uint32)_buffer_frames);

                                        err = snd_pcm_hw_params_get_rate(hw_params, &_sample_rate, &dir);
                                        if(err < 0)
                                        {
                                        printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }
                                        printf("sample rate %u\n", _sample_rate);




                                        err = snd_pcm_sw_params_malloc(&sw_params);
                                        if(err < 0)
                                        {
                                        printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }

                                        err = snd_pcm_sw_params_current(_snd_pcm, sw_params);
                                        if(err < 0)
                                        {
                                        printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }

                                        err = snd_pcm_sw_params_set_avail_min(_snd_pcm, sw_params, _buffer_frames);
                                        if(err < 0)
                                        {
                                        printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }

                                        err = snd_pcm_sw_params(_snd_pcm, sw_params);
                                        if(err < 0)
                                        {
                                        printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }


					
					_buffer_size = _buffer_frames * _bytes_per_sample * _channels;
					_buffer = _allocator->realloc_array< char >(_buffer, _buffer_size, debuginfo);
					if(_buffer == 0)
					{
										printf("%d, error %s\n", __LINE__, snd_strerror(err));
						res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
						goto goto_return;
					}
						
					_ufds_count = snd_pcm_poll_descriptors_count(_snd_pcm);
					
					printf("ufds count %u\n", (::booldog::uint32)_ufds_count);
					
					_ufds = _allocator->realloc_array< struct pollfd >(_ufds, _ufds_count, debuginfo);
					if(_ufds == 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
						goto goto_return;
					}
						
					err = snd_pcm_poll_descriptors(_snd_pcm, _ufds, _ufds_count);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}
					
					err = snd_pcm_prepare(_snd_pcm);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}					
goto_return:
					if(hw_params)
						snd_pcm_hw_params_free(hw_params);
                                        if(sw_params)
                                                snd_pcm_sw_params_free(sw_params);
					return res->succeeded();
#else
					fourcc = fourcc;

					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);					
					return res->succeeded();
#endif
                                }
				booinline bool is_frame_available(::booldog::result_bool* pres
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result_bool locres;
					BOOINIT_RESULT(::booldog::result_bool);
	#ifdef __LINUX__
					int resint = 0;
					unsigned short revents = 0;
					if(_snd_pcm_started == false)
					{
						int err = snd_pcm_start(_snd_pcm);						
                                                if(err >= 0)
                                                    _snd_pcm_started = true;
						else
						{
							res->setalsaerror(err);
							goto goto_return;
						}
					}
					for(;;)
                                        {
                                                resint = ::poll(_ufds, _ufds_count, 40);
						if(resint == -1)
						{
							printf("poll error %d\n", resint);
							resint = errno;
							if(resint == EINTR || resint == EAGAIN)
								continue;
							res->seterrno(resint);
						}
						else if(resint != 0)
						{
							revents = 0;
							resint = snd_pcm_poll_descriptors_revents(_snd_pcm, _ufds, _ufds_count, &revents);
							if(resint == 0)
							{
								if (revents & POLLIN)
                                                                {
                                                                    if(_timestamp == 0)
                                                                        _timestamp = ::booldog::utils::time::posix::now_as_utc();
									//avail_frames = snd_pcm_avail_update(_snd_pcm);
									//printf("avail audio frames %u\n", (unsigned int)avail_frames);									
								
									res->bres = true;
								}
							}
							else
								res->setalsaerror(resint);
                                                }
						break;
					}
goto_return:
	#else
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
	#endif
					return res->succeeded();
                                }
				booinline bool read_frame(::booldog::result* pres
					, ::booldog::multimedia::audio::typedefs::read_frame_callback_t callback, void* udata
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
                                        debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__					
					::booldog::uint32 buffer_size = _buffer_size;
					int rc = snd_pcm_readi(_snd_pcm, _buffer, _buffer_frames);
                                        if(rc == -EPIPE)
					{
						int err = snd_pcm_avail(_snd_pcm);
						printf("overrun occurred(%d)\n", err);
					
						err = snd_pcm_prepare(_snd_pcm);
						if(err < 0)
							res->setalsaerror(err);
						else
						{
							err = snd_pcm_start(_snd_pcm);
							if(err < 0)
								res->setalsaerror(err);
						}
						return false;
					} 
					else if(rc < 0)
					{
						printf("snd_pcm_readi error %d\n", rc);
						res->setalsaerror(rc);
						return false;
					}
					else if(rc != (int)_buffer_frames)
					{
						buffer_size = rc * _bytes_per_sample * _channels;
						printf("short read, read %d frames\n", rc);
					}                                        
					::booldog::multimedia::audio::frame aframe;
					aframe.fourcc = 0;
					aframe.bytes_per_sample = _bytes_per_sample;
					aframe.channels = _channels;
                                        aframe.sample_rate = _sample_rate;
					aframe.data = (::booldog::byte*)_buffer;
					aframe.size = buffer_size;
                                        aframe.timestamp = _timestamp;
                                        _timestamp += (1000000ULL * rc) / _sample_rate;
					callback(_allocator, udata, &aframe);
					return true;
#else
					callback = callback;
					udata = udata;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
					return res->succeeded();
#endif
                                }
                                booinline bool prepare_frame(::booldog::result* pres, ::booldog::allocator* allocator
                                        , ::booldog::multimedia::audio::frame* aframe
                                        , const ::booldog::debug::info& debuginfo = debuginfo_macros)
                                {
                                    ::booldog::result locres;
                                    BOOINIT_RESULT(::booldog::result);
                                    if(_buffer_size > aframe->alloc_size)
                                    {
                                        aframe->alloc_size = _buffer_size;
                                        aframe->data = allocator->realloc_array< ::booldog::byte >(aframe->data, aframe->alloc_size, debuginfo);
                                        if(aframe->data == 0)
                                        {
                                                res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                                return false;
                                        }
                                    }
                                    return true;
                                }
                                booinline bool read_frame(::booldog::result* pres, ::booldog::multimedia::audio::frame* aframe
                                        , const ::booldog::debug::info& debuginfo = debuginfo_macros)
                                {
                                        ::booldog::result locres;
                                        BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__
                                        debuginfo = debuginfo;
                                        ::booldog::uint32 buffer_size = _buffer_size;
                                        int rc = snd_pcm_readi(_snd_pcm, aframe->data, _buffer_frames);
                                        if(rc == -EPIPE)
                                        {
                                                int err = snd_pcm_avail(_snd_pcm);
                                                printf("overrun occurred(%d)\n", err);

                                                err = snd_pcm_prepare(_snd_pcm);
                                                if(err < 0)
                                                        res->setalsaerror(err);
                                                else
                                                {
                                                        err = snd_pcm_start(_snd_pcm);
                                                        if(err < 0)
                                                                res->setalsaerror(err);
                                                }
                                                return false;
                                        }
                                        else if(rc < 0)
                                        {
                                                printf("snd_pcm_readi error %d\n", rc);
                                                res->setalsaerror(rc);
                                                return false;
                                        }
                                        else if(rc != (int)_buffer_frames)
                                        {
                                                buffer_size = rc * _bytes_per_sample * _channels;
                                                printf("short read, read %d frames\n", rc);
                                        }
                                        aframe->fourcc = 0;
                                        aframe->bytes_per_sample = _bytes_per_sample;
                                        aframe->channels = _channels;
                                        aframe->sample_rate = _sample_rate;
                                        aframe->size = buffer_size;
                                        aframe->timestamp = _timestamp;
                                        _timestamp += (1000000ULL * rc) / _sample_rate;
                                        return true;
#else
                                        aframe = aframe;
                                        debuginfo = debuginfo;
                                        res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
                                        return res->succeeded();
#endif
                                }
			};
                }
        }
}
#endif
