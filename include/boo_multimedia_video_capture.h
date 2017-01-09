#ifndef BOO_MULTIMEDIA_VIDEO_CAPTURE_H
#define BOO_MULTIMEDIA_VIDEO_CAPTURE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif

#include BOOLDOG_HEADER(boo_multimedia_enums.h)
#include BOOLDOG_HEADER(boo_multimedia_video_frame.h)
#include BOOLDOG_HEADER(boo_time_utils.h)
#include BOOLDOG_HEADER(boo_error.h)
#include BOOLDOG_HEADER(boo_result.h)

//#if 1
#ifdef __LINUX__
#include BOOLDOG_HEADER(boo_io_directory.h)
#include <linux/videodev2.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/select.h>

#ifndef V4L2_PIX_FMT_H264
#define V4L2_PIX_FMT_H264     v4l2_fourcc('H', '2', '6', '4') /* H264 with start codes */
#endif
#endif
namespace booldog
{
	namespace multimedia
	{
		namespace video
		{
			class capture;
                }
        }
	namespace results
	{
		namespace multimedia
		{
			namespace video
			{
				class capture : public ::booldog::result
				{
				private:
					capture(const ::booldog::result&)
					{
                                        }
					capture(const ::booldog::results::multimedia::video::capture&)
                                            : result()
					{
                                        }
					::booldog::results::multimedia::video::capture& operator = (const ::booldog::results::multimedia::video::capture&)
					{
						return *this;
                                        }
				public:
					::booldog::multimedia::video::capture* video;
					capture(void)
						: video(0)
					{
                                        }
					virtual ~capture(void)
					{
                                        }
					virtual void clear(void) const
					{
						::booldog::results::multimedia::video::capture* _obj_ 
							= const_cast< ::booldog::results::multimedia::video::capture* >(this);
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
	namespace multimedia
	{
		namespace video
		{
			namespace typedefs
			{
				typedef bool (*available_cameras_callback_t)(::booldog::allocator* allocator, void* udata, const char* name
					, const char* deviceid, ::booldog::uint32 capabilities);
				typedef bool (*available_formats_callback_t)(::booldog::allocator* allocator, void* udata
					, ::booldog::uint32 fourcc, ::booldog::uint32 width, ::booldog::uint32 height
					, ::booldog::uint32 framerate_numerator, ::booldog::uint32 framerate_denominator, const char* description);
				typedef void (*read_frame_callback_t)(::booldog::allocator* allocator, void* udata, ::booldog::multimedia::video::frame* vframe);
                        }
			class capture
			{
				friend class ::booldog::allocator;
				::booldog::allocator* _allocator;
			private:                                
                                bool _streaming;
				::booldog::uint32 _width;
				::booldog::uint32 _height;
				::booldog::uint32 _fourcc;
                                ::booldog::uint32 _framerate_numerator;
                                ::booldog::uint32 _framerate_denominator;
                                ::booldog::uint32 _size;

	#ifdef __LINUX__
				struct buffer 
				{
					void* start;
					size_t length;
					bool mmap;
                                        size_t offset;
				};				
				int _capture_type;
                                ::booldog::multimedia::video::capture::buffer _buffers[10];
				int _buffers_count;
				static int xioctl(int fh, int request, void *arg)
				{
					int r;
					do
					{
						r = ioctl(fh, request, arg);
					}
					while(-1 == r && EINTR == errno);
					return r;
				}
	#endif
				::booldog::uint64 _difference;
				::booldog::uint64 _timestamp;
				::booldog::uint64 _last_tickcount;
                                char* _filename;
                                size_t _filename_len;
                                size_t _filename_size;
#ifdef __LINUX__
                                int _fd;
#endif
				capture(void)
				{
                                }
				capture(::booldog::allocator* pallocator
	#ifdef __LINUX__
                                        , int pfd
	#endif
					)
                                        : _allocator(pallocator), _streaming(false)
                                        , _width(0), _height(0), _fourcc(0xffffffff), _framerate_numerator(0)
                                        , _framerate_denominator(0), _filename(0), _filename_len(0), _filename_size(0)
	#ifdef __LINUX__
                                        , _fd(pfd)
	#endif
				{
	#ifdef __LINUX__
					::memset(_buffers, 0, sizeof(_buffers));
	#endif
                                }
				capture(const ::booldog::multimedia::video::capture&)
				{
                                }
				::booldog::multimedia::video::capture& operator = (const ::booldog::multimedia::video::capture&)
				{
					return *this;
                                }
			public:
				~capture(void)
				{
	#ifdef __LINUX__
                                        for(_buffers_count = 0 ; _buffers_count < (int)(sizeof(_buffers) / sizeof(_buffers[0])) ; ++_buffers_count)
					{
						if(_buffers[_buffers_count].start)
						{
							if(_buffers[_buffers_count].mmap)
								munmap(_buffers[_buffers_count].start, _buffers[_buffers_count].length);
							else
								_allocator->free(_buffers[_buffers_count].start);
						}
					}
	#endif
                                        if(_filename)
                                            _allocator->free(_filename);
                                }
				static bool open(::booldog::results::multimedia::video::capture* pres, ::booldog::allocator* allocator
					, const char* name, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::results::multimedia::video::capture locres;
					BOOINIT_RESULT(::booldog::results::multimedia::video::capture);
	#ifdef __LINUX__
                                        ::booldog::result simpleres;
					struct v4l2_capability cap;
					int fd = -1;
					struct stat st;
					if(stat(name, &st) == -1)
					{
						res->seterrno();
						goto goto_return;
					}
					if(S_ISCHR(st.st_mode) == 0) 
					{
						res->booerr(::booldog::enums::result::booerr_type_file_is_not_character_device);
						goto goto_return;
					}
					fd = ::open(name, O_RDWR | O_NONBLOCK, 0);
					if(fd == -1)
					{
						res->seterrno();
						goto goto_return;
					}
					else
					{
						if(xioctl(fd, VIDIOC_QUERYCAP, &cap) == -1)
						{
							res->seterrno();
							goto goto_return;
						}
						if((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0)
						{
							res->booerr(::booldog::enums::result::booerr_type_file_is_not_video_capture_device);
							goto goto_return;
						}
					}
	goto_return:
					if(res->succeeded())
					{
                                                res->video = allocator->create< ::booldog::multimedia::video::capture >(allocator, fd);
                                                if(res->video == 0)
						{
							res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							return false;
						}
                                                if(::booldog::utils::string::mbs::assign<16>(&simpleres, allocator
                                                                                          , true, 0, res->video->_filename
                                                                                          , res->video->_filename_len, res->video->_filename_size
                                                                                          , name, 0, SIZE_MAX, debuginfo))
                                                    return true;
                                                else
                                                {
                                                    res->copy(simpleres);
                                                    return false;
                                                }
					}
					else
					{
						if(fd != -1)
							::close(fd);
						return false;
					}
	#else
					allocator = allocator;
					name = name;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
					return res->succeeded();
	#endif				
                                }
                                bool open(::booldog::result* pres, const char* name, const ::booldog::debug::info& debuginfo = debuginfo_macros)
                                {
                                        debuginfo = debuginfo;
                                        ::booldog::results::multimedia::video::capture locres;
                                        BOOINIT_RESULT(::booldog::result);
        #ifdef __LINUX__
                                        ::booldog::result simpleres;
                                        struct v4l2_capability cap;
                                        struct stat st;
                                        if(stat(name, &st) == -1)
                                        {
                                            int err = errno;
                                            printf("stat, errno %d\n", err);
                                                res->seterrno(err);
                                                goto goto_return;
                                        }
                                        if(S_ISCHR(st.st_mode) == 0)
                                        {
                                                res->booerr(::booldog::enums::result::booerr_type_file_is_not_character_device);
                                                goto goto_return;
                                        }
                                        _fd = ::open(name, O_RDWR | O_NONBLOCK, 0);
                                        if(_fd == -1)
                                        {
                                            int err = errno;
                                            printf("open, errno %d\n", err);
                                                res->seterrno(err);
                                                goto goto_return;
                                        }
                                        else
                                        {
                                                if(xioctl(_fd, VIDIOC_QUERYCAP, &cap) == -1)
                                                {
                                                    int err = errno;
                                                    printf("xioctl, errno %d\n", err);
                                                        res->seterrno(err);
                                                        goto goto_return;
                                                }
                                                if((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0)
                                                {
                                                        res->booerr(::booldog::enums::result::booerr_type_file_is_not_video_capture_device);
                                                        goto goto_return;
                                                }
                                        }
        goto_return:
                                        if(res->succeeded())
                                        {
                                            if(_filename == name || ::booldog::utils::string::mbs::assign<16>(res, _allocator
                                                                                      , true, 0, _filename
                                                                                      , _filename_len, _filename_size
                                                                                      , name, 0, SIZE_MAX, debuginfo))
                                                return true;
                                            else
                                                return false;
                                        }
                                        else
                                        {
                                                if(_fd != -1)
                                                {
                                                        ::close(_fd);
                                                    _fd = -1;
                                                }
                                                return false;
                                        }
        #else
                                        name = name;
                                        debuginfo = debuginfo;
                                        res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
                                        return res->succeeded();
        #endif
                                }
				booinline bool available_formats(::booldog::result* pres, ::booldog::allocator* allocator
					, ::booldog::multimedia::video::typedefs::available_formats_callback_t callback, void* udata
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
                                        debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
	#ifdef __LINUX__
					v4l2_fmtdesc fmtdesc;
					fmtdesc.index = 0;
					fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
					bool next = true;
					v4l2_frmsizeenum framesizeenum;
					v4l2_frmivalenum v4l2frameivalenum;
					for(;;)
					{
						if(xioctl(_fd, VIDIOC_ENUM_FMT, &fmtdesc) != -1)
						{
							framesizeenum.index = 0;
							framesizeenum.pixel_format = fmtdesc.pixelformat;
							v4l2frameivalenum.pixel_format = fmtdesc.pixelformat;
							for(;;)
							{
								if(xioctl(_fd, VIDIOC_ENUM_FRAMESIZES, &framesizeenum) != -1)
								{
									if(framesizeenum.type == V4L2_FRMSIZE_TYPE_DISCRETE)
									{
										v4l2frameivalenum.index = 0;	
										v4l2frameivalenum.width = framesizeenum.discrete.width;
										v4l2frameivalenum.height = framesizeenum.discrete.height;
										for(;;)
										{
											if(xioctl(_fd, VIDIOC_ENUM_FRAMEINTERVALS, &v4l2frameivalenum) != -1)
											{
												if(v4l2frameivalenum.type == V4L2_FRMIVAL_TYPE_DISCRETE)
												{
													next = callback(allocator, udata, fmtdesc.pixelformat
														, framesizeenum.discrete.width, framesizeenum.discrete.height
														, v4l2frameivalenum.discrete.numerator
														, v4l2frameivalenum.discrete.denominator
														, (const char*)fmtdesc.description);												

													++v4l2frameivalenum.index;

													if(next == false)
														break;
												}
												else
												{
													next = callback(allocator, udata, fmtdesc.pixelformat
														, framesizeenum.discrete.width
														, framesizeenum.discrete.height, 0, 0
														, (const char*)fmtdesc.description);
													++v4l2frameivalenum.index;
													break;
												}
											}
											else
												break;
										}
										if(v4l2frameivalenum.index == 0)
										{
											next = callback(allocator, udata, fmtdesc.pixelformat, framesizeenum.discrete.width
												, framesizeenum.discrete.height, 0, 0, (const char*)fmtdesc.description);
											//char sfcc[5] = {0}; *((::booldog::uint32*)sfcc) = fmtdesc.pixelformat;										
										}
										++framesizeenum.index;
										if(next == false)
											break;
									}
									else
									{
										next = callback(allocator, udata, fmtdesc.pixelformat, 0, 0, 0, 0
											, (const char*)fmtdesc.description);
										++framesizeenum.index;
										break;
									}
								}
								else
									break;
							}
							if(framesizeenum.index == 0)
								next = callback(allocator, udata, fmtdesc.pixelformat, 640, 480, 0, 0
								, (const char*)fmtdesc.description);
						}
						else
							break;
						++fmtdesc.index;
						if(next == false)
							break;
					}
	#else
					allocator = allocator;
					callback = callback;
					udata = udata;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
	#endif
					return res->succeeded();
                                }
				booinline bool stop_capturing(::booldog::result* pres, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
                                        debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
	#ifdef __LINUX__
                                        if(_streaming)
                                        {
                                            enum v4l2_buf_type type;
                                            switch (_capture_type)
                                            {
                                            case V4L2_MEMORY_USERPTR:
                                                type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                                if(xioctl(_fd, VIDIOC_STREAMOFF, &type) == -1)
                                                {
                                                    res->seterrno();
                                                }
                                                else
                                                {
                                                    struct v4l2_requestbuffers req;
                                                    ::memset(&req, 0, sizeof(req));
                                                    req.count  = 0;
                                                    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                                    req.memory = _capture_type;
                                                    xioctl(_fd, VIDIOC_REQBUFS, &req);
                                                    _streaming = false;
                                                }
                                                break;
                                            case V4L2_MEMORY_MMAP:
                                                    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                                    if(xioctl(_fd, VIDIOC_STREAMOFF, &type) == -1)
                                                    {
                                                        res->seterrno();
                                                    }
                                                    else
                                                        _streaming = false;
                                                    break;
                                            }
                                        }
	#else
					debuginfo = debuginfo;
	#endif
					return res->succeeded();
				}
				booinline bool start_capturing(::booldog::result* pres, ::booldog::uint32 fourcc, ::booldog::uint32 width
					, ::booldog::uint32 height, ::booldog::uint32 framerate_numerator, ::booldog::uint32 framerate_denominator
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);					
	#ifdef __LINUX__
                                        ::booldog::multimedia::video::capture::buffer* pbuffer = 0;
					struct timespec uptime = {};
					enum v4l2_buf_type v4l2buftype;
					struct v4l2_buffer v4l2buf;
					struct v4l2_requestbuffers req;

					struct v4l2_capability cap;
					struct v4l2_cropcap cropcap;
					struct v4l2_crop crop;
					struct v4l2_format fmt;
					struct v4l2_streamparm v4l2streamparm;
					unsigned int min = 0;

                                        bool reinit = false;
                                        if(_fourcc != fourcc || _width != width || _height != height
                                                || _framerate_numerator != framerate_numerator
                                                || _framerate_denominator != framerate_denominator)
                                            reinit = true;
                                        if(reinit)
                                        {
                                            if(xioctl(_fd, VIDIOC_QUERYCAP, &cap) == -1)
                                            {
                                                int err = errno;
                                                printf("xioctl %d, VIDIOC_QUERYCAP\n", err);
                                                    res->seterrno(err);
                                                    goto goto_return;
                                            }
                                            if(cap.capabilities & V4L2_CAP_STREAMING)
                                            {
                                                //if(fourcc == V4L2_PIX_FMT_MJPEG)
                                                    _capture_type = V4L2_MEMORY_MMAP;
                                                //else
                                                //_capture_type = V4L2_MEMORY_USERPTR;
                                            }
                                            else
                                            {
                                                    _capture_type = 0;
                                                    if((cap.capabilities & V4L2_CAP_READWRITE) == false)
                                                    {
                                                            res->booerr(::booldog::enums::result::booerr_type_video_capture_device_does_not_support_neither_streaming_nor_io);
                                                            goto goto_return;
                                                    }
                                            }
                                            ::memset(&cropcap, 0, sizeof(cropcap));
                                            cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                            if(xioctl(_fd, VIDIOC_CROPCAP, &cropcap) == 0)
                                            {
                                                    crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                                    crop.c = cropcap.defrect;
                                                    if(xioctl(_fd, VIDIOC_S_CROP, &crop) == -1)
                                                    {
                                                            switch (errno) {
                                                            case EINVAL:
                                                                    /* Cropping not supported. */
                                                                    break;
                                                            default:
                                                                    /* Errors ignored. */
                                                                    break;
                                                            }
                                                    }
                                            }
                                            else
                                            {
                                                    /* Errors ignored. */
                                            }
                                            ::memset(&fmt, 0, sizeof(fmt));
                                            fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                            fmt.fmt.pix.width = width;
                                            fmt.fmt.pix.height = height;
                                            fmt.fmt.pix.pixelformat = fourcc;
                                            fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;//V4L2_FIELD_ANY
                                            if(xioctl(_fd, VIDIOC_S_FMT, &fmt) == -1)
                                            {
                                                int err = errno;
                                                printf("xioctl %d, VIDIOC_S_FMT\n", err);
                                                    res->seterrno(err);
                                                    goto goto_return;
                                            }
                                            min = fmt.fmt.pix.width * 2;
                                            if(fmt.fmt.pix.bytesperline < min)
                                                    fmt.fmt.pix.bytesperline = min;
                                            min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
                                            if(fmt.fmt.pix.sizeimage < min)
                                                    fmt.fmt.pix.sizeimage = min;
                                            _size = fmt.fmt.pix.sizeimage;

                                            if(xioctl(_fd, VIDIOC_G_FMT, &fmt) == -1)
                                            {
                                                int err = errno;
                                                printf("xioctl %d, VIDIOC_G_FMT\n", err);
                                                res->seterrno(err);
                                                goto goto_return;
                                            }

                                            _width = fmt.fmt.pix.width;
                                            _height = fmt.fmt.pix.height;

                                            if(framerate_numerator != 0 || framerate_denominator != 0)
                                            {
                                                    ::memset(&v4l2streamparm, 0, sizeof(v4l2streamparm));
                                                    v4l2streamparm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                                    if(xioctl(_fd, VIDIOC_G_PARM, &v4l2streamparm) != -1)
                                                    {
                                                            if((v4l2streamparm.parm.capture.capability & V4L2_CAP_TIMEPERFRAME))
                                                            {
                                                                    v4l2streamparm.parm.capture.timeperframe.numerator = framerate_numerator;
                                                                    v4l2streamparm.parm.capture.timeperframe.denominator = framerate_denominator;
                                                                    if(xioctl(_fd, VIDIOC_S_PARM, &v4l2streamparm) == -1)
                                                                    {
                                                                        int err = errno;
                                                                        printf("xioctl %d, VIDIOC_S_PARM\n", err);
                                                                            res->seterrno(err);
                                                                            goto goto_return;
                                                                    }
                                                            }
                                                    }
                                                    else
                                                    {
                                                        int err = errno;
                                                        printf("xioctl %d, VIDIOC_G_PARM\n", err);
                                                            res->seterrno(err);
                                                            goto goto_return;
                                                    }
                                            }
                                        }
                                        else if(_fourcc != 0xffffffff)
                                        {

                                        }

                                        if(_capture_type == V4L2_MEMORY_USERPTR)
                                        {
                                            //if(reinit)
                                            {
                                                ::memset(&req, 0, sizeof(req));

                                                req.count  = sizeof(_buffers) / sizeof(_buffers[0]);
                                                req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                                req.memory = V4L2_MEMORY_USERPTR;

                                                if(xioctl(_fd, VIDIOC_REQBUFS, &req) == -1)
                                                {
                                                        int errnoval = errno;
                                                        if(errnoval != EINVAL)
                                                        {
                                                            printf("xioctl %d, VIDIOC_REQBUFS\n", errnoval);
                                                                res->seterrno(errnoval);
                                                                goto goto_return;
                                                        }
                                                        else
                                                                _capture_type = V4L2_MEMORY_MMAP;
                                                }
                                                else if(reinit)
                                                {
                                                        for(_buffers_count = 0 ; _buffers_count < (int)(sizeof(_buffers) / sizeof(_buffers[0])) ; ++_buffers_count)
                                                        {
                                                            pbuffer = &_buffers[_buffers_count];
                                                                if(pbuffer->mmap)
                                                                {
                                                                        if(pbuffer->start)
                                                                        {
                                                                                munmap(pbuffer->start, pbuffer->length);
                                                                                pbuffer->start = 0;
                                                                                pbuffer->length = 0;
                                                                        }
                                                                }
                                                                if(_size > pbuffer->length)
                                                                {
                                                                    pbuffer->start = _allocator->realloc_array<char>((char*)pbuffer->start
                                                                            , _size, debuginfo);
                                                                    if(pbuffer->start == 0)
                                                                    {
                                                                            res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                                                            goto goto_return;
                                                                    }
                                                                    pbuffer->mmap = false;
                                                                    pbuffer->length = _size;
                                                                }
                                                        }
                                                }
                                            }
                                        }
                                        if(_capture_type == V4L2_MEMORY_MMAP)
                                        {
                                            if(reinit)
                                            {
                                                ::memset(&req, 0, sizeof(req));

                                                req.count = sizeof(_buffers) / sizeof(_buffers[0]);
                                                req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                                req.memory = V4L2_MEMORY_MMAP;

                                                if(xioctl(_fd, VIDIOC_REQBUFS, &req) == -1)
                                                {
                                                        int errnoval = errno;
                                                        if(errnoval != EINVAL)
                                                        {
                                                            printf("xioctl %d, VIDIOC_REQBUFS\n", errnoval);
                                                                res->seterrno(errnoval);
                                                                goto goto_return;
                                                        }
                                                        else
                                                                _capture_type = 0;
                                                }
                                                else
                                                {
                                                        if(req.count < 2)
                                                        {
                                                                res->booerr(::booldog::enums::result::booerr_type_insufficient_memory);
                                                                goto goto_return;
                                                        }

                                                        for(_buffers_count = 0 ;_buffers_count < (int)req.count; ++_buffers_count)
                                                        {
                                                                ::memset(&v4l2buf, 0, sizeof(v4l2buf));

                                                                v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                                                v4l2buf.memory = V4L2_MEMORY_MMAP;
                                                                v4l2buf.index = _buffers_count;

                                                                if(xioctl(_fd, VIDIOC_QUERYBUF, &v4l2buf) == -1)
                                                                {
                                                                    int err = errno;
                                                                    printf("xioctl %d, VIDIOC_QUERYBUF\n", err);
                                                                        res->seterrno(err);
                                                                        goto goto_return;
                                                                }
                                                                pbuffer = &_buffers[_buffers_count];
                                                                if(pbuffer->mmap)
                                                                {
                                                                        if(pbuffer->start && (pbuffer->length != v4l2buf.length || pbuffer->offset != v4l2buf.m.offset))
                                                                        {
                                                                                munmap(pbuffer->start, pbuffer->length);
                                                                                pbuffer->start = 0;
                                                                                pbuffer->length = 0;
                                                                        }
                                                                }
                                                                else
                                                                {                                                                    
                                                                        if(pbuffer->start)
                                                                        {
                                                                                _allocator->free(pbuffer->start);
                                                                                pbuffer->start = 0;
                                                                                pbuffer->length = 0;
                                                                        }
                                                                }
                                                                if(pbuffer->start == 0)
                                                                {
                                                                    _buffers[_buffers_count].start = mmap(0, v4l2buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, _fd
                                                                            , v4l2buf.m.offset);
                                                                    if(_buffers[_buffers_count].start == MAP_FAILED)
                                                                    {
                                                                            _buffers[_buffers_count].start = 0;
                                                                            res->booerr(::booldog::enums::result::booerr_type_map_failed);
                                                                            goto goto_return;
                                                                    }
                                                                    _buffers[_buffers_count].mmap = true;
                                                                    _buffers[_buffers_count].length = v4l2buf.length;
                                                                    _buffers[_buffers_count].offset = v4l2buf.m.offset;
                                                                }
                                                        }
                                                }
                                            }
                                        }
                                        if(_capture_type == 0)
                                        {
                                                if(_buffers[0].mmap)
                                                {
                                                        if(_buffers[0].start)
                                                        {
                                                                munmap(_buffers[0].start, _buffers[0].length);
                                                                _buffers[0].start = 0;
                                                                _buffers[0].length = 0;
                                                        }
                                                }
                                                if(_size > _buffers[0].length)
                                                {
                                                    _buffers[0].start = _allocator->realloc_array<char>((char*)_buffers[0].start
                                                            , _size, debuginfo);
                                                    if(_buffers[0].start == 0)
                                                    {
                                                            res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                                            goto goto_return;
                                                    }
                                                    _buffers[0].mmap = false;
                                                    _buffers[0].length = _size;
                                                }
                                        }
                                        switch(_capture_type)
                                        {
                                        case V4L2_MEMORY_USERPTR:
                                                for(int index = 0;index < _buffers_count; ++index)
                                                {
                                                        ::memset(&v4l2buf, 0, sizeof(v4l2buf));
                                                        v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                                        v4l2buf.memory = V4L2_MEMORY_USERPTR;
                                                        v4l2buf.index = index;
                                                        v4l2buf.m.userptr = (unsigned long)_buffers[index].start;
                                                        v4l2buf.length = _buffers[index].length;
                                                        if(xioctl(_fd, VIDIOC_QBUF, &v4l2buf) == -1)
                                                        {
                                                            int err = errno;
                                                            printf("xioctl %d, VIDIOC_QBUF\n", err);
                                                                res->seterrno(err);
                                                                goto goto_return;
                                                        }
                                                }
                                                break;
                                        case V4L2_MEMORY_MMAP:
                                                for(int index = 0;index < _buffers_count; ++index)
                                                {
                                                        ::memset(&v4l2buf, 0, sizeof(v4l2buf));
                                                        v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                                        v4l2buf.memory = V4L2_MEMORY_MMAP;
                                                        v4l2buf.index = index;
                                                        if(xioctl(_fd, VIDIOC_QBUF, &v4l2buf) == -1)
                                                        {
                                                            int err = errno;
                                                            printf("xioctl %d, VIDIOC_QBUF\n", err);
                                                                res->seterrno(err);
                                                                goto goto_return;
                                                        }
                                                }
                                                break;
                                        default:
                                                goto goto_return;
                                        }
					v4l2buftype = V4L2_BUF_TYPE_VIDEO_CAPTURE;
					if(xioctl(_fd, VIDIOC_STREAMON, &v4l2buftype) == -1)
					{
                                            int err = errno;
                                            printf("xioctl %d, VIDIOC_STREAMON\n", err);
                                                res->seterrno(err);
						goto goto_return;
                                        }					
					_timestamp = ::booldog::utils::time::posix::now_as_utc();					
					clock_gettime(CLOCK_MONOTONIC,&uptime);
					_last_tickcount = uptime.tv_sec * 1000000LL + uptime.tv_nsec / 1000LL;
					//_difference = 0;
	goto_return:
					if(res->succeeded())
                                        {
						_streaming = true;
						_width = width;
						_height = height;
						_fourcc = fourcc;
                                                _framerate_numerator = framerate_numerator;
                                                _framerate_denominator = framerate_denominator;
						return true;
					}
					return false;
	#else
					fourcc = fourcc;
					width = width;
					height = height;
					framerate_numerator = framerate_numerator;
					framerate_denominator = framerate_denominator;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
					return res->succeeded();
	#endif		
                                }
                                booinline bool is_capturing(void)
                                {
                                        return _streaming;
                                }
                                booinline bool is_opened(void)
                                {
                                        return _fd != -1;
                                }
				booinline bool is_frame_available(::booldog::result_bool* pres
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result_bool locres;
					BOOINIT_RESULT(::booldog::result_bool);
        #ifdef __LINUX__
					for(;;)
					{
						fd_set fds;
						FD_ZERO(&fds);
						FD_SET(_fd, &fds);

						struct timeval tv;
						tv.tv_sec = 0;
						tv.tv_usec = 23333;

						int resint = select(_fd + 1, &fds, 0, 0, &tv);
                                                //_timestamp = ::booldog::utils::time::posix::now_as_utc();
						if(resint == -1)
						{
							resint = errno;
							if(resint == EINTR)
								continue;
							res->seterrno(resint);
						}
						else if(resint != 0)
                                                {
							struct timespec uptime = {};
							clock_gettime(CLOCK_MONOTONIC,&uptime);
							
							::booldog::uint64 new_last_tickcount = uptime.tv_sec * 1000000LL + uptime.tv_nsec / 1000LL;
							
							//printf("Frame diff " I64u "\n", new_last_tickcount - _last_tickcount);
							
							_timestamp += new_last_tickcount - _last_tickcount;
							
							_last_tickcount = new_last_tickcount;
						
							res->bres = true;
						}
						break;
					}
	#else
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
	#endif
					return res->succeeded();
				};
				booinline bool read_frame(::booldog::result* pres
					, ::booldog::multimedia::video::typedefs::read_frame_callback_t callback, void* udata
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
                                        debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
	#ifdef __LINUX__
                                        //struct timespec ts = {};
					::booldog::multimedia::video::frame vframe;
					int index = 0;
					struct v4l2_buffer v4l2buf;
					switch(_capture_type)
					{
					case V4L2_MEMORY_USERPTR:
						::memset(&v4l2buf, 0, sizeof(v4l2buf));

						v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
						v4l2buf.memory = V4L2_MEMORY_USERPTR;

						if(xioctl(_fd, VIDIOC_DQBUF, &v4l2buf) == -1)
						{
                                                    int err = errno;
                                                    if(err != EIO)
                                                    {
                                                        printf("xioctl VIDIOC_DQBUF, %d\n", err);
                                                        res->seterrno(err);
							return false;
                                                    }
						}					
						for(;index < _buffers_count;++index)
						{
							if(v4l2buf.m.userptr == (unsigned long)_buffers[index].start
								&& v4l2buf.length == _buffers[index].length)
								break;
						}
						if(index < _buffers_count)
						{
							vframe.fourcc = _fourcc;
							vframe.width = _width;
							vframe.height = _height;
							vframe.data = (::booldog::byte*)v4l2buf.m.userptr;
							vframe.size = (::booldog::uint32)v4l2buf.bytesused;

                                                        /*switch( v4l2buf.flags & V4L2_BUF_FLAG_TIMESTAMP_MASK )
                                                        {
                                                            case V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC:
                                                            {
                                                                struct timespec uptime = {};
                                                                clock_gettime(CLOCK_MONOTONIC,&uptime);
                                                                timestamp = ::booldog::utils::time::posix::now_as_utc();

                                                                ::booldog::int64 now = uptime.tv_sec * 1000000LL + uptime.tv_nsec / 1000LL;
                                                                ::booldog::int64 frame_now = v4l2buf.timestamp.tv_sec * 1000000LL + v4l2buf.timestamp.tv_usec;
                                                                if(now >= frame_now && now - frame_now < 100000)
                                                                    _difference = now - frame_now;
                                                                printf("v4l2 diff " I64u "(" I64d " " I64u " " I64u ")\n", _difference, now - frame_now, now, timestamp);
								if(_last_timestamp < timestamp - _difference)
									timestamp -= _difference;
								else
									timestamp = _last_timestamp;
								
                                                                //float const secs =
                                                                //    (v4l2buf.timestamp.tv_sec - uptime.tv_sec) +
                                                                 //   (v4l2buf.timestamp.tv_usec - uptime.tv_nsec/1000.0f)/1000.0f;

                                                                //if( V4L2_BUF_FLAG_TSTAMP_SRC_SOE == (v4l2buf.flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK) )
                                                                 //   printf("%s: frame exposure started %.03f seconds ago\n",__FUNCTION__,-secs);
                                                                //else if( V4L2_BUF_FLAG_TSTAMP_SRC_EOF == (v4l2buf.flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK) )
                                                                 //   printf("%s: frame finished capturing %.03f seconds ago\n",__FUNCTION__,-secs);
                                                                //else printf("%s: unsupported timestamp in frame\n",__FUNCTION__);

                                                                break;
                                                            }

                                                            case V4L2_BUF_FLAG_TIMESTAMP_UNKNOWN:
                                                            case V4L2_BUF_FLAG_TIMESTAMP_COPY:
                                                            default:
								printf("%s: unknown timestamp\n",__FUNCTION__);
								
								struct timespec uptime = {};
                                                                clock_gettime(CLOCK_REALTIME,&uptime);
								float const secs =
                                                                    (v4l2buf.timestamp.tv_sec - uptime.tv_sec) +
                                                                    (v4l2buf.timestamp.tv_usec - uptime.tv_nsec/1000.0f)/1000.0f;
								if( V4L2_BUF_FLAG_TSTAMP_SRC_SOE == (v4l2buf.flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK) )
                                                                    printf("%s: frame exposure started %.03f seconds ago\n",__FUNCTION__,-secs);
                                                                else if( V4L2_BUF_FLAG_TSTAMP_SRC_EOF == (v4l2buf.flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK) )
                                                                    printf("%s: frame finished capturing %.03f seconds ago\n",__FUNCTION__,-secs);
                                                                else printf("%s: unsupported timestamp in frame\n",__FUNCTION__);
								
								if(_last_timestamp < timestamp - _difference)
									timestamp -= _difference;
								else
									timestamp = _last_timestamp;
                                                        }*/
                                                        //printf("sequence %u\n", v4l2buf.sequence);

                                                        /*if(_difference == 0)
							{
								_difference = v4l2buf.timestamp.tv_sec * 1000000ULL + v4l2buf.timestamp.tv_usec;
								if(v4l2buf.flags & V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC)
								{
									clock_gettime(CLOCK_MONOTONIC, &ts);
									_difference = ts.tv_sec * 1000000LL + (ts.tv_nsec / 1000ULL) - _difference;
									//printf("%d(%x) MONOTONIC(" I64u ", " I64u ", " I64u ")\n", index, v4l2buf.flags, (::booldog::uint64)v4l2buf.timestamp.tv_sec, (::booldog::uint64)v4l2buf.timestamp.tv_usec, _difference);
								}
								else
								{
									clock_gettime(CLOCK_REALTIME, &ts);
									_difference = ts.tv_sec * 1000000LL + (ts.tv_nsec / 1000ULL) - _difference;
								}
                                                        }
                                                        timestamp -= _difference;*/

							/*timestamp = v4l2buf.timestamp.tv_sec * 1000000ULL + v4l2buf.timestamp.tv_usec;
							if(v4l2buf.flags & V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC)
							{
							printf("%d(%x) MONOTONIC(" I64u ", " I64u ")\n", index, v4l2buf.flags, (::booldog::uint64)v4l2buf.timestamp.tv_sec, (::booldog::uint64)v4l2buf.timestamp.tv_usec);
								clock_gettime(CLOCK_MONOTONIC, &ts);
								timestamp = ts.tv_sec * 1000000LL + (ts.tv_nsec / 1000ULL) - timestamp;						
								timestamp = ::booldog::utils::time::posix::now_as_utc() - timestamp;
							}
							else
							printf("UNKNOWN(" I64u ", " I64u ")\n", (::booldog::uint64)v4l2buf.timestamp.tv_sec, (::booldog::uint64)v4l2buf.timestamp.tv_usec);*/
							vframe.timestamp = _timestamp;	
							callback(_allocator, udata, &vframe);
						}
						if(xioctl(_fd, VIDIOC_QBUF, &v4l2buf) == -1)
						{
                                                    int err = errno;
                                                    printf("xioctl %d, VIDIOC_QBUF\n", err);
                                                        res->seterrno(err);
							return false;
						}
						break;
					case V4L2_MEMORY_MMAP:

						::memset(&v4l2buf, 0, sizeof(v4l2buf));

						v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
						v4l2buf.memory = V4L2_MEMORY_MMAP;

						if(xioctl(_fd, VIDIOC_DQBUF, &v4l2buf) == -1)
						{
                                                    int err = errno;
                                                    printf("xioctl %d, VIDIOC_DBUF\n", err);
                                                        res->seterrno(err);
							return false;
						}
						//timestamp = ::booldog::utils::time::posix::now_as_utc();
						vframe.fourcc = _fourcc;
						vframe.width = _width;
						vframe.height = _height;
						vframe.data = (::booldog::byte*)_buffers[v4l2buf.index].start;
						vframe.size = (::booldog::uint32)v4l2buf.bytesused;
						/*timestamp = v4l2buf.timestamp.tv_sec * 1000000ULL + v4l2buf.timestamp.tv_usec;
						if(v4l2buf.flags & V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC)
						{
						printf("MONOTONIC(" I64u ", " I64u ")\n", (::booldog::uint64)v4l2buf.timestamp.tv_sec, (::booldog::uint64)v4l2buf.timestamp.tv_usec);
							clock_gettime(CLOCK_MONOTONIC, &ts);
							timestamp = ts.tv_sec * 1000000LL + ( ts.tv_nsec / 1000ULL ) - timestamp;						
							timestamp = ::booldog::utils::time::posix::now_as_utc() - timestamp;
						}
						else
						printf("UNKNOWN(" I64u ", " I64u ")\n", (::booldog::uint64)v4l2buf.timestamp.tv_sec, (::booldog::uint64)v4l2buf.timestamp.tv_usec);*/
						vframe.timestamp = _timestamp;
						callback(_allocator, udata, &vframe);
						if(xioctl(_fd, VIDIOC_QBUF, &v4l2buf) == -1)
						{
                                                    int err = errno;
                                                    printf("xioctl %d, VIDIOC_QBUF\n", err);
                                                        res->seterrno(err);
							return false;
						}
						break;
					default:
						if(read(_fd, _buffers[0].start, _buffers[0].length) == -1)
						{
							res->seterrno();
							return false;
						}
						//timestamp = ::booldog::utils::time::posix::now_as_utc();
						vframe.fourcc = _fourcc;
						vframe.width = _width;
						vframe.height = _height;
						vframe.data = (::booldog::byte*)_buffers[0].start;
						vframe.size = (::booldog::uint32)_buffers[0].length;
						vframe.timestamp =_timestamp;
					
						callback(_allocator, udata, &vframe);
						break;
					}
					//_last_timestamp = vframe.timestamp;
	#else
					callback = callback;
					udata = udata;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
	#endif
					return res->succeeded();
                                }
                                booinline bool close(::booldog::result* pres, bool destroy, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
	#ifdef __LINUX__
                                        if(_capture_type == V4L2_MEMORY_MMAP)
                                        {
                                            for(_buffers_count = 0 ; _buffers_count < (int)(sizeof(_buffers) / sizeof(_buffers[0])) ; ++_buffers_count)
                                            {
                                                    if(_buffers[_buffers_count].start)
                                                    {
                                                            if(_buffers[_buffers_count].mmap)
                                                            {
                                                                    munmap(_buffers[_buffers_count].start, _buffers[_buffers_count].length);
                                                                    _buffers[_buffers_count].start = 0;
                                                                    _buffers[_buffers_count].length = 0;
                                                            }
                                                    }
                                            }
                                        }
					if(::close(_fd) == -1)
                                        {
                                            int err = errno;
                                            printf("close, %d\n", err);
                                                res->seterrno(err);
                                                return false;
                                        }
	#else
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
	#endif
                                        if(destroy)
                                            _allocator->destroy(this);
                                        else
                                        {
                                            _fd = -1;
                                            _fourcc = 0xffffffff;
                                        }
					return res->succeeded();
                                }
	#ifdef __LINUX__
				struct listdir_callback_info
				{
					::booldog::result* res;
					::booldog::result_mbchar mbchar;
					struct v4l2_capability capability;
					::booldog::multimedia::video::typedefs::available_cameras_callback_t callback;
					void* udata;
					listdir_callback_info(::booldog::allocator* allocator
						, ::booldog::multimedia::video::typedefs::available_cameras_callback_t pcallback, void* pudata)
						: mbchar(allocator), callback(pcallback), udata(pudata)
					{
					};
				};
				static bool listdir_callback(::booldog::allocator* allocator, void* udata, const char* pathname
					, const char* entry_name, ::booldog::enums::io::entry_type entry_type)
				{
					if(entry_type == ::booldog::enums::io::character_device)
					{
						listdir_callback_info* info = (listdir_callback_info*)udata;
						if(::booldog::utils::string::mbs::assign<16>(info->res, allocator, false, 0, info->mbchar.mbchar
							, info->mbchar.mblen, info->mbchar.mbsize, pathname, 0, SIZE_MAX))
						{
							if(::booldog::utils::string::mbs::assign<16>(info->res, allocator, false, info->mbchar.mblen
								, info->mbchar.mbchar, info->mbchar.mblen, info->mbchar.mbsize, entry_name, 0, SIZE_MAX))
							{
								bool next = true;
								int fd = ::open(info->mbchar.mbchar, O_RDWR | O_NONBLOCK, 0);
								if(fd != -1)
								{						
									memset(&info->capability, 0, sizeof(info->capability));
									if(xioctl(fd, VIDIOC_QUERYCAP, &info->capability) != -1)
									{
										if(info->capability.capabilities & V4L2_CAP_VIDEO_CAPTURE)
										{
											const char* name = info->mbchar.mbchar;
											if(info->capability.card && info->capability.card[0])
												name = (const char*)info->capability.card;
											::close(fd);
											fd = -1;
											next = info->callback(allocator, info->udata, name, info->mbchar.mbchar
												, info->capability.capabilities);
										}
									}
									if(fd != -1)
										::close(fd);
								}
								return next;
							}
							else
								return false;
						}
						else
							return false;
					}
					return true;
				};
	#endif
				static bool available_cameras(::booldog::result* pres, ::booldog::allocator* allocator
					, ::booldog::multimedia::video::typedefs::available_cameras_callback_t callback, void* udata
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
	#ifdef __LINUX__
					listdir_callback_info info(allocator, callback, udata);
					info.res = res;
					::booldog::io::directory::mbs::listdir(res, allocator, "/dev/", listdir_callback, &info, debuginfo);				
	#else
					allocator = allocator;
					callback = callback;
					udata = udata;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
	#endif
					return res->succeeded();
                                }
                                booinline const char* name(void)
                                {
                                    return _filename;
                                }
			};
                }
        }
}
#endif
