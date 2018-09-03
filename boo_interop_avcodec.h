#ifndef BOO_INTEROP_AVCODEC_H
#define BOO_INTEROP_AVCODEC_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "boo_multimedia_structs.h"
#include "boo_multimedia_enums.h"
#include "boo_multimedia_video_yuv.h"
#include <string.h>
#ifndef BOOLDOG_MALLOC
#define BOOLDOG_MALLOC(size, allocation_data, allocation_info) malloc(size)
#define BOOLDOG_REALLOC(pointer, size, allocation_udata, allocation_info) realloc(pointer, size)
#define BOOLDOG_FREE(pointer, allocation_udata, allocation_info) free(pointer)
#include <stdlib.h>
#endif

extern "C" {
#include <libavcodec/avcodec.h>
// #include <libavutil/avconfig.h>
#include <libavutil/opt.h>	
#include <libavutil/imgutils.h>	
#include <libswscale/swscale.h>
// #include <libavformat/avformat.h>
//#include <libswresample/swresample.h>
}
#if defined(_MSC_VER)
#pragma comment(lib, "avcodec")
// #pragma comment(lib, "avformat")
#endif
struct boo_avcodec_encoder {
  AVCodecContext* ctx;
  AVFrame* vframe;
  int64_t vframes_written;
  SwsContext* sws;
} boo_avcodec_encoder;
inline int boo_avcodec_close_encoder(struct boo_avcodec_encoder* enc) {
  if(enc->vframes_written)
  {
    AVPacket pkt = {};
    av_init_packet(&pkt);
    for(int got_output = 1; got_output;)  
    {
      int err = avcodec_encode_video2(enc->ctx, &pkt, 0, &got_output);
      if(err < 0)
        break;
      if(got_output) {        
        av_packet_unref(&pkt);
      }
    }
    printf("video written " I64d "\n", (long long int)enc->vframes_written);
  }
  if(enc->ctx) {
    if(enc->ctx->codec) {
      avcodec_close(enc->ctx);
    }
    avcodec_free_context(&enc->ctx);
    enc->ctx = 0;
  }
  if(enc->sws) {
    sws_freeContext(enc->sws);
    enc->sws = 0;
  }
  if(enc->vframe)
  {
    // av_freep(&enc->vframe->data[0]);
    av_frame_free(&enc->vframe);
    enc->vframe = 0;
  }
  return 0;
}
inline int boo_avcodec_open_encoder(struct boo_avcodec_encoder* enc
  , ::booldog::multimedia::video::planes::yuv* yuv
  , ::booldog::enums::multimedia::image::fourcc codec) {
  // av_register_all();
  avcodec_register_all();
  memset(enc, 0, sizeof(struct boo_avcodec_encoder));

  AVCodecID av_codec_id = AV_CODEC_ID_NONE;
  AVPixelFormat av_pixel_format = AV_PIX_FMT_NONE, dst_av_pixel_format = AV_PIX_FMT_NONE;
  switch(codec)
  {   
  case ::booldog::enums::multimedia::image::MJPEG:
    {
      av_codec_id = AV_CODEC_ID_MJPEG;
      av_pixel_format = AV_PIX_FMT_YUVJ422P;
      break;
    }
  case ::booldog::enums::multimedia::image::H264:
    {
      av_codec_id = AV_CODEC_ID_H264;
      break;      
    }
  default:
    return -1;
  }
  switch(yuv->_chrominance_subsampling)
  {   
  case ::booldog::enums::multimedia::chrominance_subsampling_444:
    {
      av_pixel_format = AV_PIX_FMT_YUV444P;
      break;
    }
  case ::booldog::enums::multimedia::chrominance_subsampling_422:
    {
      av_pixel_format = AV_PIX_FMT_YUV422P;
      break;
    }
  case ::booldog::enums::multimedia::chrominance_subsampling_420:
    {
      av_pixel_format = AV_PIX_FMT_YUV420P;
      break;
    }
  default:
    // TODO
    return -1;
  }
  AVCodec* video_codec = avcodec_find_encoder(av_codec_id);
  if(video_codec == 0) {
    // TODO
    return -2;
  }
  enc->ctx = avcodec_alloc_context3(video_codec);
  if(enc->ctx == 0) {
    // TODO 
    return -3;
  }
  int second_try = 0;
  for(;;)
  {
    enc->ctx->codec_type = AVMEDIA_TYPE_VIDEO;
    enc->ctx->codec_id = av_codec_id;

    enc->ctx->width = yuv->_width;
    enc->ctx->height = yuv->_height;

    enc->ctx->time_base.den = 30;
    enc->ctx->time_base.num = 1;

						// enc->ctx->max_b_frames = 0;
    switch(av_codec_id)
    {
    case AV_CODEC_ID_MJPEG:
      {
        enc->ctx->bit_rate = 80000000;
        dst_av_pixel_format = AV_PIX_FMT_YUVJ422P;
        break;
      }
    case AV_CODEC_ID_H264:
      {
        enc->ctx->bit_rate = 512000;
        enc->ctx->gop_size = 12;
        dst_av_pixel_format = AV_PIX_FMT_YUV420P;
        enc->ctx->chroma_sample_location = AVCHROMA_LOC_LEFT;
        enc->ctx->bits_per_raw_sample = 8;
        av_opt_set(enc->ctx->priv_data, "preset", "baseline", 0);
        av_opt_set(enc->ctx->priv_data, "crf", "3", AV_OPT_SEARCH_CHILDREN);
    //	av_opt_set(codec_context_copy->priv_data, "qp", "15", AV_OPT_SEARCH_CHILDREN);
        break;
      }
    case AV_CODEC_ID_MPEG4:
      {
        enc->ctx->bit_rate = 80000000;
        dst_av_pixel_format = AV_PIX_FMT_YUV420P;
        break;
      }
    }
    if(second_try) {
      break;
    }
    else
    {
      second_try = 1;
      enc->ctx->pix_fmt = av_pixel_format;

      if(avcodec_open2(enc->ctx, video_codec, 0) < 0) {
        enc->ctx->pix_fmt = dst_av_pixel_format;
      }
      else
      {
        break;
      }
    }
  }
  if(enc->ctx->codec || avcodec_open2(enc->ctx, video_codec, 0) >= 0)
  {
    if(enc->ctx->pix_fmt != av_pixel_format) {
      enc->sws = sws_getCachedContext(enc->sws, yuv->_width, yuv->_height, av_pixel_format
        , yuv->_width, yuv->_height, dst_av_pixel_format, 0, 0, 0, 0);
      if(enc->sws == 0) {
        boo_avcodec_close_encoder(enc);
        return -4;
      }
    }
    enc->vframe = av_frame_alloc();
    if(enc->vframe)
    {
      av_frame_make_writable(enc->vframe);
      enc->vframe->format = enc->ctx->pix_fmt;
      enc->vframe->width = enc->ctx->width;
      enc->vframe->height = enc->ctx->height;
      enc->vframe->linesize[0] = yuv->_strides[0];
      enc->vframe->linesize[1] = yuv->_strides[1];
      enc->vframe->linesize[2] = yuv->_strides[2];
      enc->vframe->pts = 0;
      enc->vframe->pkt_dts = 0;
    }
  }
  return 0;
}
inline int boo_avcodec_encode(struct boo_avcodec_encoder* enc, ::booldog::data::buffer* buffer
  , ::booldog::multimedia::video::planes::yuv* yuv, void* allocation_udata
  , void* allocation_info) {
  allocation_udata = allocation_udata;
  allocation_info = allocation_info;
  
  if(enc->sws)
  {
    // uint8_t* data[1] = {(uint8_t*)frame->data};
    // int linesize[1] = {2 * enc->ctx->width};
    // if(sws_scale(_sws, data, linesize, 0, enc->ctx->height, enc->vframe->data, enc->vframe->linesize) != enc->ctx->height)
    //   return;
  }
  else
  {
    enc->vframe->data[0] = yuv->_yuv[0];
    enc->vframe->data[1] = yuv->_yuv[1];
    enc->vframe->data[2] = yuv->_yuv[2];
    // memcpy(enc->vframe->data[0], yuv->_yuv[0], yuv->_strides[0]);
    // if(yuv->_strides[1]) {
    //   memcpy(enc->vframe->data[1], yuv->_yuv[1], yuv->_strides[1]);
    // }
    // if(yuv->_strides[2]) {
    //   memcpy(enc->vframe->data[2], yuv->_yuv[2], yuv->_strides[2]);
    // }
  }
  AVPacket pkt;  
  av_init_packet(&pkt);
  pkt.data = (uint8_t*)buffer->buf;
  pkt.size = buffer->allocsize;
  enc->vframe->pts = av_rescale_q_rnd(enc->vframes_written
    , enc->ctx->time_base, enc->ctx->time_base, AV_ROUND_NEAR_INF);
    
  int got_output = 0;
  if(avcodec_encode_video2(enc->ctx, &pkt, enc->vframe, &got_output) < 0)
  {
    printf("avcodec_encode_video2 failed\n");
    return -2;
  }  
  else {
    ++enc->vframes_written;    
    if(got_output == 1) {
      if(pkt.data != buffer->buf) {
        buffer->allocsize = pkt.size;
        buffer->buf = BOOLDOG_REALLOC(buffer->buf, buffer->allocsize, allocation_udata, allocation_info);
        memcpy(buffer->buf, pkt.data, pkt.size);
      }
      buffer->size = pkt.size;
      av_packet_unref(&pkt);
    }
    else {
      buffer->size = 0;
    }
  }
  return 0;
}

struct boo_avcodec_decoder {
  AVCodecContext* ctx;
  AVFrame* vframe;
  // int64_t vframes_written;
  // SwsContext* sws;
} boo_avcodec_decoder;
inline int boo_avcodec_close_decoder(struct boo_avcodec_decoder* dec) {
  if(dec->ctx) {
    if(dec->ctx->codec) {
      avcodec_close(dec->ctx);
    }
    av_free(dec->ctx);
    dec->ctx = 0;
  }
  if(dec->vframe) {
    av_frame_free(&dec->vframe);
    dec->vframe = 0;
  }
  return 0;
}
inline int boo_avcodec_open_decoder(struct boo_avcodec_decoder* dec
  , ::booldog::enums::multimedia::image::fourcc codec, int width, int height) {
  // av_register_all();
  avcodec_register_all();
  memset(dec, 0, sizeof(struct boo_avcodec_decoder));

  AVCodecID av_codec_id = AV_CODEC_ID_NONE;
  switch(codec)
  {   
  case ::booldog::enums::multimedia::image::MJPEG:
    {
      av_codec_id = AV_CODEC_ID_MJPEG;
      break;
    }
  case ::booldog::enums::multimedia::image::H264:
    {
      av_codec_id = AV_CODEC_ID_H264;
      break;      
    }
  default:
    // TODO
    return -1;
  }
  AVCodec* av_codec = avcodec_find_decoder(av_codec_id);
  if(codec == 0) {
    // TODO
    return -2;
  }
  dec->ctx = avcodec_alloc_context3(av_codec);
  if(dec->ctx == 0) {
    // TODO
    return -3;
  }  
  avcodec_get_context_defaults3(dec->ctx, av_codec);
  if(av_codec->capabilities & CODEC_CAP_TRUNCATED)
    dec->ctx->flags |= CODEC_FLAG_TRUNCATED;
  dec->ctx->width = width;
  dec->ctx->height = height;
  if(avcodec_open2(dec->ctx, av_codec, 0) < 0) {
    boo_avcodec_close_decoder(dec);
    // TODO
    return -4;
  }
  dec->vframe = av_frame_alloc();
  if(dec->vframe == 0) {
    // TODO
    return -5;
  }
  av_frame_make_writable(dec->vframe);
  return 0;
}
inline int boo_avcodec_decode(struct boo_avcodec_decoder* dec, ::booldog::data::buffer* data
  , ::booldog::multimedia::video::planes::yuv* yuv, void* allocation_udata
  , void* allocation_info) {
  allocation_udata = allocation_udata;
  allocation_info = allocation_info;

  AVPacket pkt;
  av_init_packet(&pkt);

  pkt.size = data->size;
  pkt.data = (unsigned char*)data->buf;
  int got_output = 0;
  yuv->_strides[0] = 0;
  yuv->_strides[1] = 0;
  yuv->_strides[2] = 0;
  while(pkt.size > 0)
  {
    int len = avcodec_decode_video2(dec->ctx, dec->vframe, &got_output, &pkt);
    if(len < 0)
    {
      // TODO
      printf("avcodec_decode_video2 failed\n");
      return -1;
    }
    if(got_output)
    {
      switch(dec->vframe->format)
      {
      case AV_PIX_FMT_YUV420P:
        {
          yuv->_buffer.size = 0;
          yuv->_chrominance_subsampling = ::booldog::enums::multimedia::chrominance_subsampling_420;
          yuv->_width = dec->vframe->width;
          yuv->_height = dec->vframe->height;

          yuv->_strides[0] = dec->vframe->linesize[0];
          yuv->_strides[1] = dec->vframe->linesize[1];
          yuv->_strides[2] = dec->vframe->linesize[2];

          // unsigned int size = 3 * yuv->_width * yuv->_height / 2;
          // if(size > yuv->_buffer.allocsize) {
          //   yuv->_buffer.buf = BOOLDOG_REALLOC(yuv->_buffer.buf, size, allocation_data, allocation_info);
          //   if(yuv->_buffer.buf == 0) {
          //     int error = ::booldog::enums::result::booerr_type_cannot_alloc_memory;
          //     return error;
          //   }
          //   yuv->_buffer.allocsize = size;
          // }
          // unsigned char* buf = (unsigned char*)yuv->_buffer.buf;
          // yuv->_yuv[0] = buf;
          // yuv->_yuv[1] = &buf[yuv->_width * yuv->_height];
          // yuv->_yuv[2] = &buf[yuv->_width * yuv->_height + yuv->_width * yuv->_height / 4];

          // memcpy(yuv->_yuv[0], dec->vframe->data[0], yuv->_strides[0]);
          // memcpy(yuv->_yuv[1], dec->vframe->data[1], yuv->_strides[1]);
          // memcpy(yuv->_yuv[2], dec->vframe->data[2], yuv->_strides[2]);

          yuv->_yuv[0] = dec->vframe->data[0];
          yuv->_yuv[1] = dec->vframe->data[1];
          yuv->_yuv[2] = dec->vframe->data[2];
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
          // if(___frame.fourcc == ::booldog::enums::multimedia::image::Unknown) {
          //   ___frame.width = _avframe->width;
          //   ___frame.height = _avframe->height;
          //   _y_size = ___frame.width * ___frame.height;
          //   _v_size = _y_size / 2;
          //   _u_size = _v_size;
          //   ___frame.fourcc = ::booldog::enums::multimedia::image::YV16;
          //   ___frame.size = 2 * _y_size;
          //   if(___frame.alloc_size < ___frame.size)
          //   {
          //     ___frame.alloc_size = ___frame.size;
          //     ___frame.data = _allocator->realloc_array< ::booldog::byte >(
          //       (::booldog::byte*)___frame.data, ___frame.alloc_size);													
          //   }												
          // }
          // ::booldog::uint32 src_offset = 0, dst_offset = 0
          //         , copy_size = ___frame.width;
          // if(_avframe->linesize[0] == (int)copy_size)
          //     ::memcpy(___frame.data, _avframe->data[0], _y_size);
          // else
          // {
          //     src_offset = 0, dst_offset = 0;
          //     for(::booldog::uint32 index = 0;index < ___frame.height;++index)
          //     {
          //         //printf("decoder y copy %u<=%u(%u)\n", src_offset, dst_offset, copy_size);
          //         ::memcpy(&___frame.data[src_offset], _avframe->data[0] + dst_offset, copy_size);
          //         src_offset += copy_size;
          //         dst_offset += (::booldog::uint32)_avframe->linesize[0];
          //     }
          // }
          // copy_size = ___frame.width / 2;
          // if(_avframe->linesize[2] == (int)copy_size)
          //     ::memcpy(&___frame.data[_y_size], _avframe->data[2], _v_size);
          // else
          // {
          //     src_offset = _y_size, dst_offset = 0;
          //     for(::booldog::uint32 index = 0;index < ___frame.height;++index)
          //     {
          //         //printf("decoder v copy %u<=%u(%u)\n", src_offset, dst_offset, copy_size);
          //         ::memcpy(&___frame.data[src_offset], _avframe->data[2] + dst_offset, copy_size);
          //         src_offset += copy_size;
          //         dst_offset += (::booldog::uint32)_avframe->linesize[2];
          //     }
          // }
          // if(_avframe->linesize[1] == (int)copy_size)
          //     ::memcpy(&___frame.data[_y_size + _v_size], _avframe->data[1], _u_size);
          // else
          // {
          //     src_offset = _y_size + _v_size, dst_offset = 0;
          //     for(::booldog::uint32 index = 0;index < ___frame.height;++index)
          //     {
          //         //printf("decoder u copy %u<=%u(%u)\n", src_offset, dst_offset, copy_size);
          //         ::memcpy(&___frame.data[src_offset], _avframe->data[1] + dst_offset, copy_size);
          //         src_offset += copy_size;
          //         dst_offset += (::booldog::uint32)_avframe->linesize[1];
          //     }
          // }
          break;
        }
      default:
        printf("decode unsupported format(%d)\n", (int)dec->vframe->format);
        break;
      }
    }
    if(pkt.data)
    {
      pkt.size -= len;
      pkt.data += len;
      if(pkt.size)
        printf("pkt.size\n");
    }
  }
  return 0;
}
#endif
