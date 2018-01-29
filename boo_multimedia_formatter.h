#ifndef BOO_MULTIMEDIA_FORMATTER_H
#define BOO_MULTIMEDIA_FORMATTER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_allocator.h"
#include "boo_multimedia_graph_chain.h"
#include "boo_multimedia_enums.h"
#include "boo_string_utils.h"
#include "boo_fps_counter.h"
#include "boo_time_utils.h"
#ifdef __LINUX__
#define BOOLDOG_ENABLE_AVCODEC
#endif
extern "C"
{
#ifdef BOOLDOG_ENABLE_AVCODEC
#include <libavcodec/avcodec.h>
#include <libavutil/avconfig.h>
#include <libavutil/opt.h>	
#include <libavutil/imgutils.h>	
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#endif
}

#include <stdio.h>
namespace booldog
{
	namespace multimedia
	{
		class formatter : public ::booldog::multimedia::graph_chain
		{
		private:
                        ::booldog::int64 _video_timestamp_delimiter;
			::booldog::uint32 _video_frame_written;
			bool _isaudio_inited;
			bool _isvideo_inited;

			bool _video_and_audio;
			::booldog::allocator* _allocator;
			char* _filename;
			size_t _filename_len;
			size_t _filename_size;

			::booldog::uint32 _infourcc;
			::booldog::uint32 _width;
			::booldog::uint32 _height;
			::booldog::uint32 _in_audio_fourcc;
			::booldog::uint32 _bytes_per_sample;
			::booldog::uint32 _channels;
			::booldog::uint32 _samples_written;


			::booldog::counters::fps _boofps;
#ifdef BOOLDOG_ENABLE_AVCODEC
			AVFormatContext* _context;
			AVStream* _video_stream;

			//AVCodecContext* _audio_codec_context;

			AVStream* _audio_stream;
			SwrContext* _swr;

			SwsContext* _sws;
			AVFrame* _frame;
			AVFrame* _audio_frame;
#endif
			::booldog::multimedia::video::frame _last_vframe;
			::booldog::multimedia::audio::frame _last_aframe;

			::booldog::uint64 _last_audio_timestamp;
			::booldog::uint64 _video_first_timestamp;
			::booldog::uint64 _audio_first_timestamp;

                        ::booldog::uint32 _sample_rate;
                        bool _audio_written;
                        ::booldog::uint64 _audio_timestamp_delimiter;
                        bool _video_written;
                        bool _video_compressed;
                        int _out_bytes_per_sample;
                        int _swr_converted_samples;
                        bool _is_audio_format_planar;
                        bool _audio_compressed;
		public:
			formatter(const char* filename, ::booldog::allocator* allocator, ::booldog::typedefs::tickcount ptickcount)
                                : _video_timestamp_delimiter(0), _video_frame_written(0)
                                , _isaudio_inited(false), _isvideo_inited(false)
                                , _video_and_audio(true), _allocator(allocator), _filename(0)
                                , _filename_len(0)
                                , _filename_size(0), _infourcc(0xffffffff)
                                , _in_audio_fourcc(0xffffffff), _samples_written(0)
                                , _boofps(ptickcount)
#ifdef BOOLDOG_ENABLE_AVCODEC
                                , _context(0), _video_stream(0), _audio_stream(0), _swr(0), _sws(0)
                                , _frame(0), _audio_frame(0)
#endif
                                , _last_audio_timestamp(0)
                                , _video_first_timestamp(0)
                                , _audio_first_timestamp(0), _audio_written(false), _audio_timestamp_delimiter(0), _video_written(false), _video_compressed(false)
                                , _out_bytes_per_sample(0), _swr_converted_samples(0), _audio_compressed(false)
			{
				::booldog::utils::string::mbs::assign<16>(0, _allocator, true, 0, _filename, _filename_len, _filename_size
					, filename, 0, SIZE_MAX, debuginfo_macros);
                        }
                        virtual ~formatter(void)
			{
				if(_filename)
					_allocator->free(_filename);
				if(_last_vframe.data)
					_allocator->free(_last_vframe.data);
				if(_last_aframe.data)
					_allocator->free(_last_aframe.data);
                        }                        
			void initialize(::booldog::multimedia::video::frame* frame, ::booldog::multimedia::audio::frame* audio_frame)
      {
				bool res = false;
#ifdef BOOLDOG_ENABLE_AVCODEC
				if(_context || avformat_alloc_output_context2(&_context, 0, 0, _filename) >= 0)
        {
          if(_context->oformat->video_codec == AV_CODEC_ID_NONE)
          {
              printf("This format does not support video codec\n");
              _video_and_audio = false;
              if(frame)
              {
                  _infourcc = frame->fourcc;
                  _width = frame->width;
                  _height = frame->height;
              }
              res = true;
          }
          else
          {
            if(frame)
            {
                         // _context->oformat->video_codec = AV_CODEC_ID_MJPEG;
              _video_compressed = false;
                          AVPixelFormat av_pixel_format = AV_PIX_FMT_NONE
                                  , dst_av_pixel_format = AV_PIX_FMT_NONE;
              switch(frame->fourcc)
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
                case ::booldog::enums::multimedia::image::MJPEG:
                  {
                    _video_compressed = true;
                    _context->oformat->video_codec = AV_CODEC_ID_MJPEG;
                                      av_pixel_format = AV_PIX_FMT_YUVJ422P;
                    break;
                  }
                          }
              AVCodec* video_codec = avcodec_find_encoder(_context->oformat->video_codec);
              if(video_codec)
              {
                _video_stream = avformat_new_stream(_context, video_codec);
                if(_video_stream)
                {
                  _video_stream->id = _context->nb_streams - 1;
                  if(avcodec_get_context_defaults3(_video_stream->codec, video_codec) >= 0)
                  {
                      bool avcodec_opened = false, second_try = false;
                      for(;;)
                      {
                          _video_stream->codec->codec_type = AVMEDIA_TYPE_VIDEO;
                          _video_stream->codec->codec_id = _context->oformat->video_codec;

                          _video_stream->codec->width = frame->width;
                          _video_stream->codec->height = frame->height;

                          _video_stream->codec->time_base.den = 30;
                          _video_stream->codec->time_base.num = 1;
                          //_video_stream->time_base.den = 25;
                          //_video_stream->time_base.num = 1;

    //						_video_stream->codec->max_b_frames = 1;
                          if(_context->oformat->flags & AVFMT_GLOBALHEADER)
                              _video_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
                          switch(_context->oformat->video_codec)
                          {
                          case AV_CODEC_ID_MJPEG:
                              {
                                  _video_stream->codec->bit_rate = 80000000;
                                  dst_av_pixel_format = AV_PIX_FMT_YUVJ422P;
                                  break;
                              }
                          case AV_CODEC_ID_H264:
                              {
                                  _video_stream->codec->bit_rate = 512000;
                                  _video_stream->codec->gop_size = 12;
                                  dst_av_pixel_format = AV_PIX_FMT_YUV420P;
                                  _video_stream->codec->chroma_sample_location = AVCHROMA_LOC_LEFT;
                                  _video_stream->codec->bits_per_raw_sample = 8;
                                  av_opt_set(_video_stream->codec->priv_data, "preset", "ultrafast", 0);
                                  av_opt_set(_video_stream->codec->priv_data, "crf", "3", AV_OPT_SEARCH_CHILDREN);
                              //	iav_opt_set(codec_context_copy->priv_data, "qp", "15", AV_OPT_SEARCH_CHILDREN);
                                  break;
                              }
                          case AV_CODEC_ID_MPEG4:
                              {
                                  _video_stream->codec->bit_rate = 80000000;
                                  dst_av_pixel_format = AV_PIX_FMT_YUV420P;
                                  break;
                              }
                          }
                          if(second_try)
                              break;
                          else
                          {
                              second_try = true;
                              _video_stream->codec->pix_fmt = av_pixel_format;

                              if(avcodec_open2(_video_stream->codec, video_codec, 0) < 0)
                              {
                                  _video_stream->codec->pix_fmt = dst_av_pixel_format;
                                  _sws = sws_getCachedContext(_sws, frame->width, frame->height, av_pixel_format, frame->width, frame->height, dst_av_pixel_format, 0, 0, 0, 0);
                                  if(_sws == 0)
                                      goto goto_return;
                              }
                              else
                              {
                                  avcodec_opened = true;
                                  break;
                              }
                          }
                      }
                      if(avcodec_opened || avcodec_open2(_video_stream->codec, video_codec, 0) >= 0)
                    {
                      _frame = av_frame_alloc();
                      if(_frame)
                      {
                        _frame->format = _video_stream->codec->pix_fmt;
                        _frame->width = _video_stream->codec->width;
                        _frame->height = _video_stream->codec->height;
                        if(av_image_alloc(_frame->data, _frame->linesize, _video_stream->codec->width
                          , _video_stream->codec->height, _video_stream->codec->pix_fmt, 32) < 0)
                        {
                          av_frame_free(&_frame);
                          _frame = 0;
                        }
                        else
                        {
                          _infourcc = frame->fourcc;
                          _width = frame->width;
                          _height = frame->height;

                          _frame->pts = 0;
                          _frame->pkt_dts = 0;
                          res = true;
                          _isvideo_inited = true;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          if(_context->oformat->audio_codec == AV_CODEC_ID_NONE)
          {
              printf("This format does not support audio codec\n");
              _video_and_audio = false;
              if(audio_frame)
              {
                  _bytes_per_sample = audio_frame->bytes_per_sample;
                  _channels = audio_frame->channels;
                  _in_audio_fourcc = audio_frame->fourcc;
                  _sample_rate = audio_frame->sample_rate;
              }
              res = true;
          }
          else
          {
            _audio_compressed = true;
            _context->oformat->audio_codec = AV_CODEC_ID_PCM_S16LE;// AV_CODEC_ID_PCM_ALAW;
            if(audio_frame && _context->oformat->audio_codec != AV_CODEC_ID_NONE)
            {
              AVSampleFormat avsample_format = AV_SAMPLE_FMT_S16;

              printf("audio codec %d\n", (int)_context->oformat->audio_codec);

              AVCodec* audio_codec = avcodec_find_encoder(_context->oformat->audio_codec);
              if(audio_codec)
              {
                _audio_stream = avformat_new_stream(_context, audio_codec);
                if(_audio_stream)
                {
                  _audio_stream->id = _context->nb_streams - 1;
                  //if(avcodec_get_context_defaults3(_audio_stream->codec, audio_codec) >= 0)
                  {
                    AVCodecContext* _audio_codec_context = _audio_stream->codec;
                    _audio_codec_context->sample_fmt = audio_codec->sample_fmts ? audio_codec->sample_fmts[0] :
                      AV_SAMPLE_FMT_FLTP;
                    if(audio_codec->sample_fmts)
                    {
                      for(int index = 0;audio_codec->sample_fmts[index] != -1;++index)
                      {
                        printf("Supported sample format %s\n", av_get_sample_fmt_name(audio_codec->sample_fmts[index]));
                        if(audio_codec->sample_fmts[index] == avsample_format)
                          _audio_codec_context->sample_fmt = avsample_format;
                      }
                    }
                    _audio_codec_context->bit_rate = 64000;
                    if(_context->oformat->audio_codec == AV_CODEC_ID_PCM_S16LE)
                      _audio_codec_context->sample_rate = audio_frame->sample_rate;
                    else
                      _audio_codec_context->sample_rate = 48000;//44100;
                    if(audio_codec->supported_samplerates)
                    {
                      _audio_codec_context->sample_rate = audio_codec->supported_samplerates[0];
                      for(int index = 0;audio_codec->supported_samplerates[index];++index)
                      {
                        printf("Supported sample rate %d\n", audio_codec->supported_samplerates[index]);
                        if(audio_codec->supported_samplerates[index] == (int)audio_frame->sample_rate)
                          _audio_codec_context->sample_rate = audio_frame->sample_rate;
                      }
                    }

                    //_audio_codec_context->channels = 2;
                    //_audio_codec_context->channel_layout = av_get_default_channel_layout(_audio_codec_context->channels);
                    _audio_codec_context->channels =
                      av_get_channel_layout_nb_channels(_audio_codec_context->channel_layout);
                    _audio_codec_context->channel_layout = AV_CH_LAYOUT_STEREO;
                    if(audio_codec->channel_layouts)
                    {
                      _audio_codec_context->channel_layout = audio_codec->channel_layouts[0];
                      for(int index = 0;audio_codec->channel_layouts[index];++index)
                      {
                        //printf("Supported channel layout %d\n", audio_codec->channel_layouts[index]);
                        if(audio_codec->channel_layouts[index] == AV_CH_LAYOUT_STEREO)
                          _audio_codec_context->channel_layout = AV_CH_LAYOUT_STEREO;
                      }
                      _audio_codec_context->channels =
                        av_get_channel_layout_nb_channels(_audio_codec_context->channel_layout);
                    }
                    _audio_codec_context->channels =
                      av_get_channel_layout_nb_channels(_audio_codec_context->channel_layout);
                    //_audio_stream->time_base = (AVRational){1, _audio_codec_context->sample_rate};

                   // printf("Default channels %d\n", _audio_codec_context->channels);

                    if(_context->oformat->flags & AVFMT_GLOBALHEADER)
                      _audio_codec_context->flags |= CODEC_FLAG_GLOBAL_HEADER;
                    AVDictionary* opts = 0;
                    av_dict_set(&opts, "strict", "experimental", 0);
                    if(avcodec_open2(_audio_codec_context, audio_codec, &opts) >= 0)
                    {
                      int nb_samples = _audio_codec_context->frame_size;
                      if(_audio_codec_context->codec->capabilities & CODEC_CAP_VARIABLE_FRAME_SIZE)
                        nb_samples = 10000;


                      _audio_frame = av_frame_alloc();
                      if(_audio_frame)
                      {
                        _audio_frame->format = _audio_codec_context->sample_fmt;
                        //_audio_frame->channels = _audio_codec_context->channels;
                        _audio_frame->channel_layout = _audio_codec_context->channel_layout;
                        //_audio_frame->sample_rate = _audio_codec_context->sample_rate;
                        _audio_frame->nb_samples = nb_samples;
                        if(nb_samples)
                        {
                          /*int buffer_size = av_samples_get_buffer_size(0, _audio_frame->channels, _audio_frame->nb_samples
                                                     , _audio_codec_context->sample_fmt, 1);

                          printf("Buffer size %d\n", buffer_size);

                          uint8_t* samples = (uint8_t*)av_malloc(buffer_size);
                          if(samples)
                          {
                              res = avcodec_fill_audio_frame(_audio_frame, _audio_frame->channels, _audio_codec_context->sample_fmt
                                                       , samples, buffer_size, 1) >= 0;
                          }*/

                          res = av_frame_get_buffer(_audio_frame, 1) >= 0;
                        }
                        else
                          res = true;
                        if(res)
                        {
                            if(_audio_codec_context->sample_fmt != AV_SAMPLE_FMT_S16
                              || _audio_codec_context->sample_rate != (int)audio_frame->sample_rate)
                            {
                              _swr = swr_alloc();
                              if(_swr)
                              {
                                      av_opt_set_int(_swr, "in_channel_count", audio_frame->channels, 0);
                                      av_opt_set_int(_swr, "in_sample_rate", audio_frame->sample_rate, 0);
                                      av_opt_set_int(_swr, "in_sample_fmt", AV_SAMPLE_FMT_S16, 0);
                                      av_opt_set_int(_swr, "out_channel_count", _audio_codec_context->channels, 0);
                                      av_opt_set_int(_swr, "out_sample_rate", _audio_codec_context->sample_rate, 0);
                                      av_opt_set_int(_swr, "out_sample_fmt", _audio_codec_context->sample_fmt, 0);
                                      if(swr_init(_swr) < 0)
                                              res = false;
                              }
                              else
                                      res = false;
                            }
                            if(res)
                            {
                              _is_audio_format_planar = av_sample_fmt_is_planar(_audio_codec_context->sample_fmt) == 1;
                              _swr_converted_samples = 0;
                              _out_bytes_per_sample = av_get_bytes_per_sample((AVSampleFormat)_audio_frame->format);

                              _audio_frame->pts = 0;
                              _audio_frame->pkt_dts = 0;

                              _bytes_per_sample = audio_frame->bytes_per_sample;
                              _channels = audio_frame->channels;
                              _in_audio_fourcc = audio_frame->fourcc;
                              _sample_rate = audio_frame->sample_rate;

                              printf("Sample format %s, channels %d, sample rate %d, frame size %d\n"
                                     , av_get_sample_fmt_name((AVSampleFormat)_audio_frame->format)
                                     , _audio_codec_context->channels, _audio_codec_context->sample_rate, _audio_codec_context->frame_size);
                              printf("planar(%s), %d, nb_samples %d\n", _is_audio_format_planar ? "true" : "false", _out_bytes_per_sample, _audio_frame->nb_samples);
                              printf("linesize[0] %d, %p\n", _audio_frame->linesize[0], _audio_frame->data[0]);
                              printf("linesize[1] %d, %p\n", _audio_frame->linesize[1], _audio_frame->data[1]);

                              _isaudio_inited = true;
                            }
                        }
                        if(res == false)
                        {
                          av_frame_free(&_audio_frame);
                          _audio_frame = 0;
                        }
                      }
                    }
                    av_dict_free(&opts);
                  }
                }
              }
            }
          }
					if(res)
					{
            if((_video_and_audio && _isaudio_inited && _isvideo_inited)
              || (_video_and_audio == false && (_isaudio_inited || _isvideo_inited)))
						{
							res = false;
							av_dump_format(_context, 0, _filename, 1);
              if(avio_open(&_context->pb, _filename, AVIO_FLAG_WRITE) >= 0) {
								if(avformat_write_header(_context, 0) == 0)
									res = true;
							}
						}
					}
				}
goto_return:
#endif
				if(res == false)
          deinitialize();
      }
      virtual void deinitialize(void)
			{
#ifdef BOOLDOG_ENABLE_AVCODEC
				if(_video_stream)
				{
          if(_video_written)
					{
            AVPacket pkt = {};
						av_init_packet(&pkt);
						for(int got_output = 1; got_output;)  
						{
							int err = avcodec_encode_video2(_video_stream->codec, &pkt, 0, &got_output);
							if(err < 0)
								break;
							if(got_output)
							{
								pkt.stream_index = _video_stream->index;
								av_packet_rescale_ts(&pkt, _video_stream->codec->time_base, _video_stream->time_base);
								err = av_interleaved_write_frame(_context, &pkt);
								//err = av_write_frame(_context, &pkt);
								if(err != 0)				
									printf("video av_write_frame failed\n");
								//av_free_packet(&pkt);
							}
						}
            printf("video written %u(%.1f)\n", (::booldog::uint32)_video_frame_written, (float)_video_frame_written / 30.f);
          }
				}
				if(_audio_stream)
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
				}                                
				if(_context)
				{
					if((_video_and_audio && _isaudio_inited && _isvideo_inited)
							|| (_video_and_audio == false && (_isaudio_inited || _isvideo_inited)))
					{
						av_write_trailer(_context);
						if(_context->pb)
							avio_close(_context->pb);
					}
          if(_video_stream)
          {
            avcodec_close(_video_stream->codec);
            _video_stream = 0;
          }
          if(_audio_stream)
          {
            avcodec_close(_audio_stream->codec);
            _audio_stream = 0;
          }
					avformat_free_context(_context);
					_context = 0;
        }
				if(_swr)
				{
					swr_free(&_swr);
					_swr = 0;
				}
				if(_sws)
				{
					sws_freeContext(_sws);
					_sws = 0;
				}
				if(_frame)
				{
					av_freep(&_frame->data[0]);
					av_frame_free(&_frame);
					_frame = 0;
				}
				if(_audio_frame)
				{
					av_frame_free(&_audio_frame);
					_audio_frame = 0;
				}
#endif
				_in_audio_fourcc = 0xffffffff;
				_infourcc = 0xffffffff;
				_samples_written = 0;
				_video_frame_written = 0;
				_video_timestamp_delimiter = 0;
        _audio_timestamp_delimiter = 0;
				_video_first_timestamp = 0;
				_audio_first_timestamp = 0;
				_isaudio_inited = false;
				_isvideo_inited = false;
				_last_vframe.timestamp = 0;
				_last_aframe.timestamp = 0;
				_last_audio_timestamp = 0;
        _audio_written = false;
        _video_written = false;
      }
			virtual void onaudioframe(void* owner, void* owner_data
				, ::booldog::multimedia::audio::typedefs::on_frame_t callback
				, ::booldog::multimedia::audio::frame* frame)
			{
				owner = owner;
				owner_data = owner_data;
				callback = callback;
#ifdef BOOLDOG_ENABLE_AVCODEC
				if(frame->fourcc != _in_audio_fourcc || frame->bytes_per_sample != _bytes_per_sample
          || frame->channels != _channels || frame->sample_rate != _sample_rate)
				{
					printf("initialize audio old(%u, %u, %u), new(%u, %u, %u)\n", _in_audio_fourcc, _bytes_per_sample, _channels, frame->fourcc, frame->bytes_per_sample, frame->channels);
					if(_isaudio_inited)
						deinitialize();
					initialize(0, frame);
				}                                
        if(_isaudio_inited == false || (_video_and_audio && _isvideo_inited == false))
					return;
        if(_video_and_audio && &_last_aframe != frame)
				{
          if(_audio_written == false)
					{
            _audio_first_timestamp = frame->timestamp;
            _last_aframe.copyfrom(0, _allocator, frame);
            if(_video_first_timestamp == 0)
                return;
            if(_video_first_timestamp > _audio_first_timestamp)
            {
              ::booldog::uint64 diff = _video_first_timestamp - _audio_first_timestamp;
              ::booldog::uint64 frame_period = 1000000ULL * _video_stream->codec->time_base.num / _video_stream->codec->time_base.den;
              _video_frame_written += (::booldog::uint32)(diff / frame_period);

              printf("1)video diff %u\n", (::booldog::uint32)_video_frame_written);

              onvideoframe(0, 0, 0, &_last_vframe);
              if(_video_written == false)
              {
                _video_frame_written = 0;
                return;
              }
            }
            else
            {
              onvideoframe(0, 0, 0, &_last_vframe);
              if(_video_written == false)
                return;
              int64_t audio_diff = ((_sample_rate * (_audio_first_timestamp - _video_first_timestamp)) / 1000000LL);

              printf("1)audio diff %u\n", (::booldog::uint32)audio_diff);

              if(audio_diff)
              {
                if(_swr)
                  audio_diff = av_rescale_rnd(swr_get_delay(_swr, _audio_stream->codec->sample_rate) + audio_diff, _sample_rate
                                              , _audio_stream->codec->sample_rate, AV_ROUND_UP);
                //if(_audio_frame)
                //    audio_diff -= audio_diff % _audio_frame->nb_samples;
                _samples_written += (::booldog::uint32)audio_diff;
              }
            }
					}
        }
        ::booldog::byte* samples = frame->data;
        ::booldog::uint32 src_samples = (frame->size / frame->bytes_per_sample) / frame->channels;
                //, nb_sample_in_bytes = _audio_frame->nb_samples * _audio_stream->codec->channels * _out_bytes_per_sample;
        //if(_audio_frame->nb_samples < (int)src_samples)
        //    src_samples = _audio_frame->nb_samples;
        //::booldog::uint32 samples_in_bytes = src_samples * frame->channels * frame->bytes_per_sample;
        //while(samples < frame->data + frame->size)
        for(;;)
        {
          if(av_frame_make_writable(_audio_frame) >= 0)
          {
            int copy_src_samples = src_samples;
            if(copy_src_samples > _audio_frame->nb_samples - _swr_converted_samples)
              copy_src_samples = _audio_frame->nb_samples - _swr_converted_samples;
            int dst_samples = copy_src_samples;
            if(_swr)
            {
              //int dst_samples = av_rescale_rnd(swr_get_delay(_swr, _audio_stream->codec->sample_rate) + src_samples, frame->sample_rate, _audio_stream->codec->sample_rate, AV_ROUND_UP);
              const uint8_t* data[1] = {(uint8_t*)samples};

              uint8_t* src[32] = {};
              if(_is_audio_format_planar)
              {
                for(int channel = 0;channel < _audio_frame->channels;++channel)
                  src[channel] = &_audio_frame->data[channel][_swr_converted_samples * _out_bytes_per_sample];
              }
              else
                src[0] = &_audio_frame->data[0][_audio_frame->channels * _swr_converted_samples * _out_bytes_per_sample];
              //int dst_samples = _audio_frame->nb_samples;

              dst_samples = swr_convert(_swr, src, _audio_frame->nb_samples - _swr_converted_samples, 0, 0);
              if(dst_samples <= 0 && samples)
              {
                //dst_samples = swr_convert(_swr, _audio_frame->data, dst_samples, data, src_samples);
                dst_samples = swr_convert(_swr, src, _audio_frame->nb_samples - _swr_converted_samples, data, copy_src_samples);
                src_samples -= copy_src_samples;
                if(src_samples == 0)
                  samples = 0;
                else
                  samples += (frame->channels * frame->bytes_per_sample * copy_src_samples);
              }
            }
            else
            {
              if(samples)
              {
                if(_is_audio_format_planar)
                {
                  for(int channel = 0;channel < _audio_frame->channels;++channel)
                  {
                    ::memcpy(&_audio_frame->data[channel][_swr_converted_samples * _out_bytes_per_sample], &samples[channel * frame->bytes_per_sample * copy_src_samples], frame->bytes_per_sample * copy_src_samples);
                  }
                }
                else
                {
                  ::memcpy(&_audio_frame->data[0][_audio_frame->channels * _swr_converted_samples * _out_bytes_per_sample], samples, frame->channels * frame->bytes_per_sample * copy_src_samples);
                }
                src_samples -= copy_src_samples;
                if(src_samples == 0)
                  samples = 0;
                else
                  samples += (frame->channels * frame->bytes_per_sample * copy_src_samples);
              }
              else
                dst_samples = 0;
            }
            if(dst_samples <= 0)
              break;
            else
            {
              _swr_converted_samples += dst_samples;
              if(_audio_frame->nb_samples == 10000)
              {
                _audio_frame->nb_samples = dst_samples;
                dst_samples = 10000;
              }
              if(_swr_converted_samples == _audio_frame->nb_samples)
              {
                AVPacket pkt = {};
                av_init_packet(&pkt);

                AVRational avrational = {1, (int)frame->sample_rate};


                int got_output = 0;
                if(_audio_compressed)
                {
                  pkt.pts = pkt.dts = av_rescale_q((int64_t)_samples_written, avrational, _audio_stream->codec->time_base);
                  pkt.data = _audio_frame->data[0];
                  pkt.size = _audio_frame->nb_samples * _audio_frame->channels * _out_bytes_per_sample;
                  got_output = 1;
                }
                else
                {
                  _audio_frame->pts = av_rescale_q((int64_t)_samples_written, avrational, _audio_stream->codec->time_base);
                  if(avcodec_encode_audio2(_audio_stream->codec, &pkt, _audio_frame, &got_output) < 0)
                  {
                    printf("avcodec_encode_audio2 failed\n");
                    if(dst_samples == 10000)
                      _audio_frame->nb_samples = 10000;
                    break;
                  }
                }
                if(_audio_written == false)
                {
                  printf("audio begin(" I64u "\n", ::booldog::utils::time::posix::now_as_utc());
                  _audio_first_timestamp = frame->timestamp;
                  _audio_written = true;
                }

                _samples_written += _swr_converted_samples;
                _swr_converted_samples = 0;

                //printf("audio written %u, " I64u "\n", _samples_written, frame->timestamp);
                if(got_output)
                {
                  pkt.stream_index = _audio_stream->index;
                  //pkt.flags |= AV_PKT_FLAG_KEY;

                  av_packet_rescale_ts(&pkt, _audio_stream->codec->time_base, _audio_stream->time_base);

                 if(av_interleaved_write_frame(_context, &pkt) != 0)
                 // if(av_write_frame(_context, &pkt) != 0)
                    printf("audio av_write_frame failed\n");
                  //av_free_packet(&pkt);
                }
                else
                  printf("audio got_output == 0\n");

//                                                break;//temp
              }
              if(dst_samples == 10000)
                _audio_frame->nb_samples = 10000;
            }
          }
          else
          {
            printf("av_frame_make_writable error\n");
            break;
          }
        }
#endif
      }
			virtual void onvideoframe(void* owner, void* owner_data
				, ::booldog::multimedia::video::typedefs::on_frame_t callback
				, ::booldog::multimedia::video::frame* frame)
      {
        owner = owner;
        owner_data = owner_data;
        callback = callback;
#ifdef BOOLDOG_ENABLE_AVCODEC
        if(frame->fourcc != _infourcc || frame->width != _width
          || frame->height != _height)
        {
          if(_isvideo_inited)
           deinitialize();
          initialize(frame, 0);
        }
        if(_isvideo_inited == false || (_video_and_audio && (_isaudio_inited == false)))
          return;
        if(_video_and_audio && &_last_vframe != frame)
        {
          if(_video_written == false)
          {
            _video_first_timestamp = frame->timestamp;
            _last_vframe.copyfrom(0, _allocator, frame);
            if(_audio_first_timestamp == 0)
              return;
            if(_video_first_timestamp > _audio_first_timestamp)
            {
              onaudioframe(0, 0, 0, &_last_aframe);
              if(_audio_written == false)
                return;
              ::booldog::uint64 diff = _video_first_timestamp - _audio_first_timestamp;
              ::booldog::uint64 frame_period = 1000000ULL * _video_stream->codec->time_base.num / _video_stream->codec->time_base.den;
              _video_frame_written += (::booldog::uint32)(diff / frame_period);

              printf("2)video diff %u\n", (::booldog::uint32)_video_frame_written);
            }
            else
            {
              int64_t audio_diff = ((_sample_rate * (_audio_first_timestamp - _video_first_timestamp)) / 1000000LL);

              printf("2)audio diff %u\n", (::booldog::uint32)audio_diff);

              if(audio_diff)
              {
                if(_swr)
                  audio_diff = av_rescale_rnd(swr_get_delay(_swr, _audio_stream->codec->sample_rate) + audio_diff, _sample_rate
                                              , _audio_stream->codec->sample_rate, AV_ROUND_UP);
                _samples_written += (::booldog::uint32)audio_diff;
              }
              onaudioframe(0, 0, 0, &_last_aframe);
              if(_audio_written == false)
              {
                _samples_written = 0;
                return;
              }
            }
          }
          else
          {
            if(_last_vframe.timestamp != 0)
            {
              ::booldog::int64 diff = frame->timestamp - _last_vframe.timestamp;
              _last_vframe.timestamp = frame->timestamp;
              diff += _video_timestamp_delimiter;
              if(diff >= 0)
              {
                ::booldog::int64 frame_period = (1000000LL * _video_stream->codec->time_base.num) / _video_stream->codec->time_base.den;
                if(frame_period >= diff)
                  _video_timestamp_delimiter = diff - frame_period;
                else
                {
                  _video_timestamp_delimiter = diff % frame_period;
                  diff /= frame_period;
                  //printf("diff " I64u  ",period " I64u ", delimiter " I64u "\n", diff, frame_period, delimiter);
                  if(diff > 1)
                  {
                    --diff;
                    printf("video diff %u\n", (::booldog::uint32)diff);

                    _video_frame_written += (::booldog::uint32)diff;
                  }
                }
              }
              else
                _video_timestamp_delimiter = diff;
            }
            else
                _last_vframe.timestamp = frame->timestamp;
          }
        }
        bool res = false;

        int got_output = 0;
                    AVPacket pkt = {};
                    av_init_packet(&pkt);
        if(_video_compressed)
        {
      //av_interleaved_write_frame(_context, 0);

      //_last_vframe.copyfrom(0, _allocator, frame);
          pkt.data = frame->data;
          pkt.size = frame->size;
          //pkt.dts = av_rescale_q_rnd(_video_frame_written == 0 ? 0 : _video_frame_written - 1, _video_stream->codec->time_base, _video_stream->codec->time_base, AV_ROUND_NEAR_INF);
          pkt.pts = pkt.dts = av_rescale_q_rnd(_video_frame_written, _video_stream->codec->time_base, _video_stream->codec->time_base, AV_ROUND_NEAR_INF);
          got_output = 1;
        }
        else
        {
          if(_sws)
          {
            uint8_t* data[1] = {(uint8_t*)frame->data};
            int linesize[1] = {2 * _video_stream->codec->width};
            if(sws_scale(_sws, data, linesize, 0, _video_stream->codec->height, _frame->data, _frame->linesize) != _video_stream->codec->height)
              return;
          }
          else
          {
          switch((int)_video_stream->codec->pix_fmt)
            {
            case AV_PIX_FMT_YUV422P:
            case AV_PIX_FMT_YUVJ422P:
            {
            ::booldog::uint32 NxM = _video_stream->codec->width * _video_stream->codec->height;
            ::booldog::uint32 NxMdenom2 = NxM / 2;

            ::booldog::uint32 src_offset = 0, dst_offset = 0
            , linesize = _video_stream->codec->width;
            if((int)linesize == _frame->linesize[0])
              ::memcpy(_frame->data[0], frame->data, NxM);
            else
            {
              for(int index = 0;index < _video_stream->codec->height;++index)
              {
            ::memcpy(_frame->data[0] + src_offset, frame->data + dst_offset, linesize);
            src_offset += _frame->linesize[0];
            dst_offset += linesize;
              }
            }
            src_offset = 0, dst_offset = 0, linesize /= 2;

            uint8_t* v = frame->data + NxM, * u = frame->data + NxM + NxMdenom2;
            if(frame->fourcc == ::booldog::enums::multimedia::image::I422)
            {
              uint8_t* temp = u;
              u = v;
              v = temp;
            }
            if((int)linesize == _frame->linesize[2])
              ::memcpy(_frame->data[2], v, NxMdenom2);
            else
            {
              for(int index = 0;index < _video_stream->codec->height;++index)
              {
            ::memcpy(_frame->data[2] + src_offset, v + dst_offset, linesize);
            src_offset += _frame->linesize[2];
            dst_offset += linesize;
              }
            }
            src_offset = 0, dst_offset = 0;
            if((int)linesize == _frame->linesize[1])
              ::memcpy(_frame->data[1], u, NxMdenom2);
            else
            {
              for(int index = 0;index < _video_stream->codec->height;++index)
              {
            ::memcpy(_frame->data[1] + src_offset, u + dst_offset, linesize);
            src_offset += _frame->linesize[1];
            dst_offset += linesize;
              }
            }
            break;
            }
            case AV_PIX_FMT_YUV420P:
              {
                ::booldog::uint32 NxM = _video_stream->codec->width * _video_stream->codec->height;
                ::booldog::uint32 NxMdenom2 = NxM / 4;

                ::booldog::uint32 src_offset = 0, dst_offset = 0
                  , linesize = _video_stream->codec->width;
                if((int)linesize == _frame->linesize[0])
                  ::memcpy(_frame->data[0], frame->data, NxM);
                else
                {
                  for(int index = 0;index < _video_stream->codec->height;++index)
                  {
                    ::memcpy(_frame->data[0] + src_offset, frame->data + dst_offset, linesize);
                    src_offset += _frame->linesize[0];
                    dst_offset += linesize;
                  }
                }
                src_offset = 0, dst_offset = NxM, linesize /= 2;
                if((int)linesize == _frame->linesize[1])
                  ::memcpy(_frame->data[1], frame->data + NxM, NxMdenom2);
                else
                {
                  for(int index = 0;index < _video_stream->codec->height;++index)
                  {
                    ::memcpy(_frame->data[1] + src_offset, frame->data + dst_offset, linesize);
                    src_offset += _frame->linesize[1];
                    dst_offset += linesize;
                  }
                }
                src_offset = 0, dst_offset = NxM + NxMdenom2;
                if((int)linesize == _frame->linesize[2])
                  ::memcpy(_frame->data[2], frame->data + NxM + NxMdenom2, NxMdenom2);
                else
                {
                  for(int index = 0;index < _video_stream->codec->height;++index)
                  {
                    ::memcpy(_frame->data[2] + src_offset, frame->data + dst_offset, linesize);
                    src_offset += _frame->linesize[2];
                    dst_offset += linesize;
                  }
                }
                break;
              }
            }
          }
        pkt.data = 0;
        pkt.size = 0;
        _frame->pts = av_rescale_q_rnd(_video_frame_written, _video_stream->codec->time_base, _video_stream->codec->time_base, AV_ROUND_NEAR_INF);
        //printf("pts " I64d "\n", (long long int)_frame->pts);
        /*for(;;)
        {
        int err = avcodec_send_frame(_video_stream->codec, _frame);
        if(err == EAGAIN)
        continue;
        res = err == 0;
        break;
        }
        if(res)
        {
        for(;;)
        {
        int err = avcodec_receive_packet(_video_stream->codec, &pkt);
        if(err == EAGAIN)
        continue;
        res = err == 0;
        break;
        }
        if(res)
        {
        pkt.stream_index = _video_stream->index;

        av_packet_rescale_ts(&pkt, _video_stream->codec->time_base, _video_stream->time_base);

        //if(pkt.pts != AV_NOPTS_VALUE)
        //	pkt.pts = av_rescale_q(pkt.pts, _video_stream->codec->time_base, _video_stream->time_base);
        //if(pkt.dts != AV_NOPTS_VALUE)
        //	pkt.dts = av_rescale_q(pkt.dts, _video_stream->codec->time_base, _video_stream->time_base);
        //pkt.duration =  av_rescale_q(pkt.duration, _video_stream->codec->time_base, _video_stream->time_base);

        //res = av_interleaved_write_frame(_context, &pkt) == 0;

        res = av_write_frame(_context, &pkt) == 0;

        if(res)
        {
        if(_video_frame_written++ == 0)
        _video_first_timestamp = frame->timestamp;
        printf("video written %u, " I64u "\n", _video_frame_written, frame->timestamp);
        }
        else
        printf("video av_write_frame failed\n");
        }
        else
        ptintf("avcodec_receive_packet failed\n");
        }
        else
        ptintf("avcodec_send_frame failed\n");*/
        if(avcodec_encode_video2(_video_stream->codec, &pkt, _frame, &got_output) < 0)
        {
        printf("avcodec_encode_video2 failed\n");
        return;
        }
        }
                                _boofps.increment();
                                ++_video_frame_written;
                                if(_video_written == false)
                                {
                                    printf("video begin(" I64u "\n", ::booldog::utils::time::posix::now_as_utc());
                                    _video_first_timestamp = frame->timestamp;
                                    _video_written = true;
                                }
                                //printf("video written %u, " I64u "\n", _video_frame_written, frame->timestamp);
                                if(got_output)
                                {


                                        //if(_frame->key_frame)
                                        //	pkt.flags |= AV_PKT_FLAG_KEY;
                                        pkt.stream_index = _video_stream->index;

                                        av_packet_rescale_ts(&pkt, _video_stream->codec->time_base, _video_stream->time_base);

                                        //if(pkt.pts != AV_NOPTS_VALUE)
                                        //	pkt.pts = av_rescale_q(pkt.pts, _video_stream->codec->time_base, _video_stream->time_base);
                                        //if(pkt.dts != AV_NOPTS_VALUE)
                                        //	pkt.dts = av_rescale_q(pkt.dts, _video_stream->codec->time_base, _video_stream->time_base);
                                        //pkt.duration =  av_rescale_q(pkt.duration, _video_stream->codec->time_base, _video_stream->time_base);

                                        //if(_video_compressed)
                                        //    res = av_write_frame(_context, &pkt) == 0;
                                        //else
                                            res = av_interleaved_write_frame(_context, &pkt) == 0;

                                        if(res == false)
                                                printf("video av_write_frame failed\n");
                                        //else
                                        //    av_interleaved_write_frame(_context, 0);
                                        //if(_video_compressed)
                                        //    av_free_packet(&pkt);
                                }
                                else
                                {
                                        //printf("video got_output == 0\n");
                                        res = true;
                                }
                    #endif
                    if(_boofps.runtime() >= 1000ULL)
                    {
                    double gui_fps = _boofps.result();
                    _boofps.reset();
                    printf("Formatter video FPS %.1f\n", (float)gui_fps);
                                }
                        }
                        booinline bool filename(::booldog::result* pres, const char* pfilename
                                      , const ::booldog::debug::info& debuginfo = debuginfo_macros)
                        {
                            return ::booldog::utils::string::mbs::assign<16>(pres, _allocator, true, 0, _filename
                                                                      , _filename_len, _filename_size
                                                                      , pfilename, 0, SIZE_MAX, debuginfo);
                        }
                        booinline void flush(void)
                        {
#ifdef BOOLDOG_ENABLE_AVCODEC
                            if(_context->pb)
                                avio_flush(_context->pb);
#endif
                        }
						booinline void video_and_audio(bool value)
						{
							_video_and_audio = value;
						}
                };
        }
}
#endif
