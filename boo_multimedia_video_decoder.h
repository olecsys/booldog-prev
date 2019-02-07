#ifndef BOO_MULTIMEDIA_VIDEO_DECODER_H
#define BOO_MULTIMEDIA_VIDEO_DECODER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_allocator.h"
#include "boo_multimedia_graph_chain.h"
#include "boo_multimedia_enums.h"
#include "boo_fps_counter.h"
#ifdef __LINUX__
#define BOOLDOG_ENABLE_AVCODEC
#define BOOLDOG_ENABLE_TURBOJPEG
#endif
#ifdef BOOLDOG_ENABLE_AVCODEC
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavutil/avconfig.h>
#include <libavutil/opt.h>	
#include <libavutil/imgutils.h>	
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
}
#endif
#ifdef BOOLDOG_ENABLE_TURBOJPEG
#include <turbojpeg.h>
#endif
#include <stdio.h>
namespace booldog
{
	namespace multimedia
	{
		namespace video
		{
			class decoder : public ::booldog::multimedia::graph_chain
			{
			private:
				::booldog::counters::fps _boofps;
			
				::booldog::allocator* _allocator;

				bool _initialized;
				bool _compressed;
				::booldog::uint32 _fourcc;
                                ::booldog::uint32 _in_width;
                                ::booldog::uint32 _in_height;

				::booldog::multimedia::video::frame ___frame;
				
				::booldog::uint32 _y_size;
				::booldog::uint32 _v_size;
				::booldog::uint32 _u_size;
#ifdef BOOLDOG_ENABLE_AVCODEC
				AVCodecContext* _codec_context;
				AVFrame* _avframe;	
				bool _avcodec_opened;
#endif
#ifdef BOOLDOG_ENABLE_TURBOJPEG
				tjhandle _tj_handle;
#endif			
			public:
				decoder(::booldog::allocator* allocator, ::booldog::typedefs::tickcount ptickcount)
                                        : _boofps(ptickcount), _allocator(allocator)
                                        , _initialized(false), _fourcc(0xffffffff)
#ifdef BOOLDOG_ENABLE_AVCODEC
                                        , _codec_context(0), _avframe(0), _avcodec_opened(false)
#endif
#ifdef BOOLDOG_ENABLE_TURBOJPEG
					, _tj_handle(0)
#endif			
				{
                                }
                                virtual ~decoder(void)
				{
					if(___frame.data)
						_allocator->free(___frame.data);
                                }
				void initialize(::booldog::multimedia::video::frame* frame)
				{
                                        _initialized = false;
#ifdef BOOLDOG_ENABLE_AVCODEC
					AVCodec* _codec = 0;
					AVCodecID codec_id = AV_CODEC_ID_H264;
#endif
					_fourcc = frame->fourcc;
					switch(frame->fourcc)
					{
						case ::booldog::enums::multimedia::image::MJPEG:
#ifdef BOOLDOG_ENABLE_TURBOJPEG
							_tj_handle = tjInitDecompress();
							if(_tj_handle)
							{
								printf("tjInitDecompress succeeded\n");
								
								_in_width = frame->width;
								_in_height = frame->height;
								_compressed = true;
								_initialized = true;
								goto goto_return;
							}
							else
								printf("tjInitDecompress failed, %s\n", tjGetErrorStr());
#else
#ifdef BOOLDOG_ENABLE_AVCODEC
							codec_id = AV_CODEC_ID_MJPEG;
#endif
							_compressed = true;
							break;
#endif						
						case ::booldog::enums::multimedia::image::H264:
#ifdef BOOLDOG_ENABLE_AVCODEC
							codec_id = AV_CODEC_ID_H264;
#endif
							_compressed = true;
							break;
                        case ::booldog::enums::multimedia::image::I420:
                        case ::booldog::enums::multimedia::image::I422:
						case ::booldog::enums::multimedia::image::YUYV:
						case ::booldog::enums::multimedia::image::YV12:
						case ::booldog::enums::multimedia::image::YV16:
                        case ::booldog::enums::multimedia::image::YUY2:
							_initialized = true;
							_compressed = false;
							break;
						default:
							_fourcc = ::booldog::enums::multimedia::image::Unknown;
							break;
					}
					if(_fourcc != ::booldog::enums::multimedia::image::Unknown)
					{
                                                _in_width = frame->width;
                                                _in_height = frame->height;
						if(_compressed)
						{
#ifdef BOOLDOG_ENABLE_AVCODEC
							_codec = avcodec_find_decoder(codec_id);
							if(_codec)
							{
								_codec_context = avcodec_alloc_context3(_codec);
								if(_codec_context)
								{
									avcodec_get_context_defaults3(_codec_context, _codec);
									if(_codec->capabilities & CODEC_CAP_TRUNCATED)
										_codec_context->flags |= CODEC_FLAG_TRUNCATED;	
                                                                        _codec_context->width = _in_width;
                                                                        _codec_context->height = _in_height;
//#if LIBAVCODEC_VER_AT_LEAST(53,6)		
									if(avcodec_open2(_codec_context, _codec, 0) >= 0)
//#else
//									if(avcodec_open(_codec_context, _codec) >= 0)
//#endif									
									{
										_avcodec_opened = true;
										_avframe = av_frame_alloc();
										if(_avframe)
											_initialized = true;
									}
								}
							}
#endif
						}	
                    }
#ifdef BOOLDOG_ENABLE_TURBOJPEG
goto_return:
#endif
					if(_initialized == false)
						deinitialize();
                                }
                                virtual void deinitialize()
				{
#ifdef BOOLDOG_ENABLE_TURBOJPEG
					if(_tj_handle)
					{
						tjDestroy(_tj_handle);
						_tj_handle = 0;
					}
#endif
#ifdef BOOLDOG_ENABLE_AVCODEC
					if(_codec_context)
					{
						if(_avcodec_opened)
						{
							avcodec_close(_codec_context);
							_avcodec_opened = false;
						}
						av_free(_codec_context);
						_codec_context = 0;
					}
					if(_avframe)
					{
						av_frame_free(&_avframe);
						_avframe = 0;
					}
#endif
					_fourcc = 0xffffffff;
					___frame.fourcc = ::booldog::enums::multimedia::image::Unknown;
					_initialized = false;
                                }
				virtual void onvideoframe(void* owner, void* owner_data
					, ::booldog::multimedia::video::typedefs::on_frame_t callback
					, ::booldog::multimedia::video::frame* frame)
				{
                                        if(frame->fourcc != _fourcc || frame->width != _in_width
                                                || frame->height != _in_height)
					{
						deinitialize();
						initialize(frame);
					}
					
					_boofps.increment();
					
					if(_compressed)
					{
#ifdef BOOLDOG_ENABLE_TURBOJPEG
						if(_tj_handle)
						{							
							if(___frame.fourcc == ::booldog::enums::multimedia::image::Unknown)
							{
								printf("TurboJpeg\n");
								int width = 0, height = 0, subsamp = 0;
								if(tjDecompressHeader2(_tj_handle, (unsigned char*)frame->data, frame->size, &width, &height, &subsamp) == 0)
								{									
									unsigned long size = tjBufSizeYUV(width, height, subsamp);
                                                                        if(size == (unsigned long)-1)
										printf("tjBufSizeYUV, failed, arguments are out of bounds\n");
									else
									{										
										___frame.width = width;
										___frame.height = height;
										switch(subsamp)
										{
											case TJSAMP_444:
												printf("TJSAMP_444\n");
												break;
											case TJSAMP_422:
                                                                                                ___frame.fourcc = ::booldog::enums::multimedia::image::I422;
												_y_size = ___frame.width * ___frame.height;
												_v_size = _y_size / 2;
												_u_size = _v_size;
												___frame.size = 2 * _y_size;
												
												printf("TJSAMP_422, %dx%d(%u and %u)\n", width, height, (::booldog::uint32)size, ___frame.size);
											
												break;
											case TJSAMP_420:
												___frame.fourcc = ::booldog::enums::multimedia::image::I420;
												_y_size = ___frame.width * ___frame.height;
												_v_size = _y_size / 4;
												_u_size = _v_size;
												___frame.size = 3 * width * height / 2;
												
												printf("TJSAMP_420, %dx%d(%u)\n", width, height, (::booldog::uint32)size);
												break;
											case TJSAMP_GRAY:
												printf("TJSAMP_GRAY\n");
												break;
											case TJSAMP_440:
												printf("TJSAMP_440\n");
												break;
										}										
										if(___frame.alloc_size < size)
										{
											___frame.alloc_size = size;
											___frame.data = _allocator->realloc_array< ::booldog::byte >(
												(::booldog::byte*)___frame.data, ___frame.alloc_size);													
										}
									}									
								}
								else
									printf("tjDecompressHeader2, failed, %s\n", tjGetErrorStr());
								/*___frame.width = _avframe->width;
								___frame.height = _avframe->height;
								_y_size = ___frame.width * ___frame.height;
								_v_size = _y_size / 2;
								_u_size = _v_size;
								___frame.fourcc = ::booldog::enums::multimedia::image::YV16;
								___frame.size = 2 * _y_size;
								if(___frame.alloc_size < ___frame.size)
								{
									___frame.alloc_size = ___frame.size;
									___frame.data = _allocator->realloc_array< ::booldog::byte >(
										(::booldog::byte*)___frame.data, ___frame.alloc_size);													
								}	*/											
							}
							
							if(tjDecompressToYUV(_tj_handle, (unsigned char*)frame->data, frame->size, ___frame.data, 0) == 0)
							{
								___frame.timestamp = frame->timestamp;
								callback(owner, owner_data, &___frame);
							}
							else
								printf("tjDecompressToYUV failed, %s\n", tjGetErrorStr());
						}
						else
#endif						
#ifdef BOOLDOG_ENABLE_AVCODEC
						if(_codec_context)
						{
							AVPacket pkt;
							av_init_packet(&pkt);

							pkt.size = frame->size;
							pkt.data = (unsigned char*)frame->data;

							int got_output = 0;
							while(pkt.size > 0)
							{
								int len = avcodec_decode_video2(_codec_context, _avframe, &got_output, &pkt);
								if(len < 0)
								{
									printf("avcodec_decode_video2 failed\n");
									return;
								}
								if(got_output)
								{
									switch(_avframe->format)
									{
									case AV_PIX_FMT_YUV420P:
										{
											/*if(___frame.size
											{
												_frame_data_size = 3 * _codec_context->width * _codec_context->height / 2;
												_frame_data = (uint8_t*)::malloc(_frame_data_size);
												_y_size = _codec_context->width * _codec_context->height;
												_v_size = _y_size / 4;
												_u_size = _y_size / 4;
											}
											::memcpy(_frame_data, _avframe->data[0], _y_size);
											::memcpy(&_frame_data[_y_size], _avframe->data[2], _v_size);
											::memcpy(&_frame_data[_y_size + _v_size], _avframe->data[1], _u_size);
											_fourcc = ::booldog::enums::multimedia::image::I420;*/
											break;
										}
									case AV_PIX_FMT_YUYV422:
										/*_frame_data_size = 2 * _codec_context->width * _codec_context->height;
										_fourcc = ::booldog::enums::multimedia::image::YUYV;*/
										break;
									case AV_PIX_FMT_YUVJ422P:
									case AV_PIX_FMT_YUV422P:
										{
											if(___frame.fourcc == ::booldog::enums::multimedia::image::Unknown)
                                                                                        {
                                                                                                ___frame.width = _avframe->width;
                                                                                                ___frame.height = _avframe->height;
                                                                                                _y_size = ___frame.width * ___frame.height;
                                                                                                _v_size = _y_size / 2;
                                                                                                _u_size = _v_size;
												___frame.fourcc = ::booldog::enums::multimedia::image::YV16;
                                                                                                ___frame.size = 2 * _y_size;
												if(___frame.alloc_size < ___frame.size)
												{
													___frame.alloc_size = ___frame.size;
													___frame.data = _allocator->realloc_array< ::booldog::byte >(
														(::booldog::byte*)___frame.data, ___frame.alloc_size);													
												}												
											}
                                                                                        //printf("decoder %u(%d), %u(%d), %u(%d)(%ux%u)(%dx%d)\n", _y_size, _avframe->linesize[0]
                                                                                        //        , _v_size, _avframe->linesize[2], _u_size, _avframe->linesize[1]
                                                                                        //        ,___frame.width, ___frame.height, _codec_context->width, _codec_context->height);
                                                                                        ::booldog::uint32 src_offset = 0, dst_offset = 0
                                                                                                , copy_size = ___frame.width;
                                                                                        if(_avframe->linesize[0] == (int)copy_size)
                                                                                            ::memcpy(___frame.data, _avframe->data[0], _y_size);
                                                                                        else
                                                                                        {
                                                                                            src_offset = 0, dst_offset = 0;
                                                                                            for(::booldog::uint32 index = 0;index < ___frame.height;++index)
                                                                                            {
                                                                                                //printf("decoder y copy %u<=%u(%u)\n", src_offset, dst_offset, copy_size);
                                                                                                ::memcpy(&___frame.data[src_offset], _avframe->data[0] + dst_offset, copy_size);
                                                                                                src_offset += copy_size;
                                                                                                dst_offset += (::booldog::uint32)_avframe->linesize[0];
                                                                                            }
                                                                                        }
                                                                                        copy_size = ___frame.width / 2;
                                                                                        if(_avframe->linesize[2] == (int)copy_size)
                                                                                            ::memcpy(&___frame.data[_y_size], _avframe->data[2], _v_size);
                                                                                        else
                                                                                        {
                                                                                            src_offset = _y_size, dst_offset = 0;
                                                                                            for(::booldog::uint32 index = 0;index < ___frame.height;++index)
                                                                                            {
                                                                                                //printf("decoder v copy %u<=%u(%u)\n", src_offset, dst_offset, copy_size);
                                                                                                ::memcpy(&___frame.data[src_offset], _avframe->data[2] + dst_offset, copy_size);
                                                                                                src_offset += copy_size;
                                                                                                dst_offset += (::booldog::uint32)_avframe->linesize[2];
                                                                                            }
                                                                                        }
                                                                                        if(_avframe->linesize[1] == (int)copy_size)
                                                                                            ::memcpy(&___frame.data[_y_size + _v_size], _avframe->data[1], _u_size);
                                                                                        else
                                                                                        {
                                                                                            src_offset = _y_size + _v_size, dst_offset = 0;
                                                                                            for(::booldog::uint32 index = 0;index < ___frame.height;++index)
                                                                                            {
                                                                                                //printf("decoder u copy %u<=%u(%u)\n", src_offset, dst_offset, copy_size);
                                                                                                ::memcpy(&___frame.data[src_offset], _avframe->data[1] + dst_offset, copy_size);
                                                                                                src_offset += copy_size;
                                                                                                dst_offset += (::booldog::uint32)_avframe->linesize[1];
                                                                                            }
                                                                                        }
											break;
										}
									default:
										printf("decode unsupported format(%d)\n", (int)_avframe->format);
										break;
									}
									___frame.timestamp = frame->timestamp;
									callback(owner, owner_data, &___frame);
								}
								if(pkt.data)
								{
									pkt.size -= len;
									pkt.data += len;
									if(pkt.size)
										printf("pkt.size\n");
								}
							}
						}
#endif
					}
					else
					{
						//::booldog::threading::sleep(100);
						callback(owner, owner_data, frame);
					}
					
					if(_boofps.runtime() >= 1000ULL)
					{
						double gui_fps = _boofps.result();
						_boofps.reset();
						printf("Decoder FPS %.1f\n", (float)gui_fps);
					}
                                }
                        };
                }
        }
}
#endif
