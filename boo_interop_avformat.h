#ifndef BOO_INTEROP_AVFORMAT_H
#define BOO_INTEROP_AVFORMAT_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "boo_multimedia_structs.h"
#include "boo_multimedia_enums.h"
#ifndef BOOLDOG_MALLOC
#define BOOLDOG_MALLOC(size, allocation_data, allocation_info) malloc(size)
#define BOOLDOG_REALLOC(pointer, size, allocation_udata, allocation_info) realloc(pointer, size)
#define BOOLDOG_FREE(pointer, allocation_udata, allocation_info) free(pointer)
#include <stdlib.h>
#endif

extern "C" {
#include <libavcodec/avcodec.h>
//#include <libavutil/avconfig.h>
#include <libavutil/opt.h>	
#include <libavutil/imgutils.h>	
//#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
//#include <libswresample/swresample.h>
}
#if defined(_MSC_VER)
//#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat")
#endif
namespace booldog {
	namespace interop	{
    namespace avformat {
      struct formatter {
        AVFormatContext* ctx;
        AVStream* vstream;
        AVFrame* vframe;
        unsigned int vframes_written;
      };
      inline int close_formatter(formatter* fmt)	{
				if(fmt->vstream) {
          if(fmt->vframes_written)
					{
            AVPacket pkt = {};
						av_init_packet(&pkt);
						for(int got_output = 1; got_output;)  
						{
							int err = avcodec_encode_video2(fmt->vstream->codec, &pkt, 0, &got_output);
							if(err < 0)
								break;
							if(got_output) {
								pkt.stream_index = fmt->vstream->index;
								av_packet_rescale_ts(&pkt, fmt->vstream->codec->time_base, fmt->vstream->time_base);
								err = av_interleaved_write_frame(fmt->ctx, &pkt);
								if(err != 0)				
									printf("video av_write_frame failed\n");
							}
						}
            printf("video written %u(%.1f)\n", (unsigned int)fmt->vframes_written
              , (float)fmt->vframes_written / 30.f);
          }
				}
				/*if(_audio_stream)
				{
          if(_audio_written)
          {
            AVPacket pkt = {};
            av_init_packet(&pkt);
            for(int got_output = 1; got_output;)
            {
                    int err = avcodec_encode_audio2(_audio_stream->codec, &pkt, 0, &got_output);
                    if(err < 0)
                      break;
                    if(got_output)
                    {
                      pkt.stream_index = _audio_stream->index;
                      av_packet_rescale_ts(&pkt, _audio_stream->codec->time_base, _audio_stream->time_base);
                      err = av_interleaved_write_frame(_context, &pkt);
                      //err = av_write_frame(_context, &pkt);
                      if(err != 0)
                        printf("audio av_write_frame failed\n");
                      //av_free_packet(&pkt);
                    }
            }
            printf("audio written %u(%.1f)\n", (::booldog::uint32)_samples_written, (float)_samples_written / (float)_sample_rate);
          }
				}    */                            
				if(fmt->ctx) {
					if(fmt->ctx->pb) {
						av_write_trailer(fmt->ctx);
						if(fmt->ctx->pb)
							avio_close(fmt->ctx->pb);
					}
          if(fmt->vstream) {
            avcodec_close(fmt->vstream->codec);
            fmt->vstream = 0;
          }
          /*if(_audio_stream)
          {
            avcodec_close(_audio_stream->codec);
            _audio_stream = 0;
          }*/
					avformat_free_context(fmt->ctx);
					fmt->ctx = 0;
        }
				/*if(_swr)
				{
					swr_free(&_swr);
					_swr = 0;
				}
				if(_sws)
				{
					sws_freeContext(_sws);
					_sws = 0;
				}*/
				if(fmt->vframe) {
					av_freep(&fmt->vframe->data[0]);
					av_frame_free(&fmt->vframe);
					fmt->vframe = 0;
				}
				/*if(_audio_frame)
				{
					av_frame_free(&_audio_frame);
					_audio_frame = 0;
				}*/
        return 0;
      }
      inline int open_formatter(formatter* fmt, ::booldog::multimedia::image* img, const char* filename) {
        av_register_all();
        avcodec_register_all();
        if(fmt->ctx == 0 && avformat_alloc_output_context2(&fmt->ctx, 0, 0, filename) < 0)
          return -1;

        if(img) {
          if(fmt->ctx->oformat->video_codec == AV_CODEC_ID_NONE) {
            /* printf("This format does not support video codec\n");
            _video_and_audio = false;
            if(frame)
            {
                _infourcc = frame->fourcc;
                _width = frame->width;
                _height = frame->height;
            }
            res = true;*/
            return -2;
          }
        
          AVPixelFormat av_pixel_format = AV_PIX_FMT_NONE, dst_av_pixel_format = AV_PIX_FMT_NONE;
          switch(img->fourcc)
          {
          case ::booldog::enums::multimedia::image::YUYV:
          case ::booldog::enums::multimedia::image::YUY2:
            av_pixel_format = AV_PIX_FMT_YUYV422;
            break;
          case ::booldog::enums::multimedia::image::I422:
          case ::booldog::enums::multimedia::image::YV16:
            av_pixel_format = AV_PIX_FMT_YUVJ422P;
            break;
          case ::booldog::enums::multimedia::image::I420:
            av_pixel_format = AV_PIX_FMT_YUV420P;
            break;
          case ::booldog::enums::multimedia::image::MJPEG: {
              fmt->ctx->oformat->video_codec = AV_CODEC_ID_MJPEG;
              av_pixel_format = AV_PIX_FMT_YUVJ422P;
              break;
            }
          default:
            return -3;
          }
          AVCodec* video_codec = avcodec_find_encoder(fmt->ctx->oformat->video_codec);
          if(video_codec == 0) {
            return -4;
          }

          fmt->vstream = avformat_new_stream(fmt->ctx, video_codec);
          if(fmt->vstream == 0) {
            return -5;
          }

          fmt->vstream->id = fmt->ctx->nb_streams - 1;
          if(avcodec_get_context_defaults3(fmt->vstream->codec, video_codec) < 0) {
            return -6;
          }

          bool avcodec_opened = false, second_try = false;
          for(;;) {
            fmt->vstream->codec->codec_type = AVMEDIA_TYPE_VIDEO;
            fmt->vstream->codec->codec_id = fmt->ctx->oformat->video_codec;

            fmt->vstream->codec->width = img->width;
            fmt->vstream->codec->height = img->height;

            fmt->vstream->codec->time_base.den = 30;
            fmt->vstream->codec->time_base.num = 1;

            //_video_stream->codec->max_b_frames = 1;
            if(fmt->ctx->oformat->flags & AVFMT_GLOBALHEADER)
              fmt->vstream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
            switch(fmt->ctx->oformat->video_codec)
            {
            case AV_CODEC_ID_MJPEG: {
                fmt->vstream->codec->bit_rate = 80000000;
                dst_av_pixel_format = AV_PIX_FMT_YUVJ422P;
                break;
              }
            case AV_CODEC_ID_H264: {
                fmt->vstream->codec->bit_rate = 512000;
                fmt->vstream->codec->gop_size = 12;
                dst_av_pixel_format = AV_PIX_FMT_YUV420P;
                fmt->vstream->codec->chroma_sample_location = AVCHROMA_LOC_LEFT;
                fmt->vstream->codec->bits_per_raw_sample = 8;
                av_opt_set(fmt->vstream->codec->priv_data, "preset", "ultrafast", 0);
                av_opt_set(fmt->vstream->codec->priv_data, "crf", "3", AV_OPT_SEARCH_CHILDREN);
                //av_opt_set(codec_context_copy->priv_data, "qp", "15", AV_OPT_SEARCH_CHILDREN);
                break;
              }
            case AV_CODEC_ID_MPEG4: {
                fmt->vstream->codec->bit_rate = 80000000;
                dst_av_pixel_format = AV_PIX_FMT_YUV420P;
                break;
              }
            }
            if(second_try)
              break;
            else {
              second_try = true;
              fmt->vstream->codec->pix_fmt = av_pixel_format;

              if(avcodec_open2(fmt->vstream->codec, video_codec, 0) < 0) {
                fmt->vstream->codec->pix_fmt = dst_av_pixel_format;
                //_sws = sws_getCachedContext(_sws, img->width, img->height
                //  , av_pixel_format, img->width, img->height, dst_av_pixel_format, 0, 0, 0, 0);
                //if(_sws == 0)
                //  goto goto_return;
              }
              else {
                avcodec_opened = true;
                break;
              }
            }
          }

          if(avcodec_opened == false && avcodec_open2(fmt->vstream->codec, video_codec, 0) < 0) {
            fmt->vstream = 0;

            return -7;
          }

          fmt->vframe = av_frame_alloc();
          if(fmt->vframe == 0) {
            return -8;
          }

          fmt->vframe->format = fmt->vstream->codec->pix_fmt;
          fmt->vframe->width = fmt->vstream->codec->width;
          fmt->vframe->height = fmt->vstream->codec->height;
          if(av_image_alloc(fmt->vframe->data, fmt->vframe->linesize, fmt->vstream->codec->width
            , fmt->vstream->codec->height, fmt->vstream->codec->pix_fmt, 32) < 0) {
            av_frame_free(&fmt->vframe);
            fmt->vframe = 0;
            return -9;
          }
          
          //_infourcc = frame->fourcc;
          //_width = frame->width;
          //_height = frame->height;

          fmt->vframe->pts = 0;
          fmt->vframe->pkt_dts = 0;
          fmt->vframes_written = 0;
        }
          
        
        //if((_video_and_audio && _isaudio_inited && _isvideo_inited)
        //  || (_video_and_audio == false && (_isaudio_inited || _isvideo_inited)))
        {
          av_dump_format(fmt->ctx, 0, filename, 1);
          if(avio_open(&fmt->ctx->pb, filename, AVIO_FLAG_WRITE) < 0) {
            return -10;
          }
          if(avformat_write_header(fmt->ctx, 0) != 0)
            return -11;
        }
        return 0;
      }
      inline int write_video(formatter* fmt, ::booldog::multimedia::image* img)
      {
        int got_output = 0;
        AVPacket pkt = {};
        av_init_packet(&pkt);
        
        pkt.data = img->data;
        pkt.size = (int)img->sizeimage;
        pkt.pts = pkt.dts = av_rescale_q_rnd(fmt->vframes_written, fmt->vstream->codec->time_base
          , fmt->vstream->codec->time_base, AV_ROUND_NEAR_INF);
        got_output = 1;

        ++fmt->vframes_written;
        if(got_output)
        {
          pkt.stream_index = fmt->vstream->index;

          av_packet_rescale_ts(&pkt, fmt->vstream->codec->time_base, fmt->vstream->time_base);
          if(av_interleaved_write_frame(fmt->ctx, &pkt) < 0) {
            return -1;
          }
        }
        return 0;      
      }
    }
  }
}
#endif
