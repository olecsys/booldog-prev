#ifndef BOO_WEB_CAMERA_H
#define BOO_WEB_CAMERA_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif

#include BOOLDOG_HEADER(boo_multimedia_enums.h)
#include BOOLDOG_HEADER(boo_error.h)

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
#else
#include BOOLDOG_HEADER(boo_result.h)
#endif
//#include BOOLDOG_HEADER(boo_param.h)
//#include BOOLDOG_HEADER(boo_string_utils.h)
//#include BOOLDOG_HEADER(boo_executable_utils.h)

//#include <fcntl.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#ifdef __WINDOWS__
//#include <io.h>
//#include <share.h>
//#else
//#ifndef _LARGEFILE64_SOURCE 
//#define _LARGEFILE64_SOURCE 
//#endif
//#include <unistd.h>
//#endif
namespace booldog
{
	namespace multimedia
	{
		class web_camera;
	};
	namespace results
	{
		namespace multimedia
		{
			class camera : public ::booldog::result
			{
			private:
				camera(const ::booldog::result&)
				{
				};
				camera(const ::booldog::results::multimedia::camera&)
				{
				};
				::booldog::results::multimedia::camera& operator = (const ::booldog::results::multimedia::camera&)
				{
					return *this;
				};
			public:
				::booldog::multimedia::web_camera* cam;
				camera(void)
				{
					cam = 0;
				};
				virtual ~camera(void)
				{
				};
				virtual void clear(void) const
				{
					::booldog::results::multimedia::camera* _obj_ 
						= const_cast< ::booldog::results::multimedia::camera* >(this);
#ifdef __UNIX__
					_obj_->dlerrorclear();
#endif
					_obj_->error_type = ::booldog::enums::result::error_type_no_error;
					_obj_->cam = 0;
				};
			};
		};
	};
	namespace multimedia
	{
		namespace typedefs
		{
			typedef bool (*available_cameras_callback_t)(::booldog::allocator* allocator, void* udata, const char* name
				, const char* deviceid, ::booldog::uint32 capabilities);
			typedef bool (*available_formats_callback_t)(::booldog::allocator* allocator, void* udata
				, ::booldog::uint32 fourcc, ::booldog::uint32 width, ::booldog::uint32 height, const char* description);
			typedef void (*read_frame_callback_t)(::booldog::allocator* allocator, void* udata, void* frame
				, ::booldog::uint32 frame_size, ::booldog::uint32 fourcc, ::booldog::uint32 width
				, ::booldog::uint32 height);
		};
		class web_camera
		{
			friend class ::booldog::allocator;
			::booldog::allocator* _allocator;
		private:
			::booldog::uint32 _width;
			::booldog::uint32 _height;
			::booldog::uint32 _fourcc;
#ifdef __LINUX__
			struct buffer 
			{
				void* start;
				size_t length;
				bool mmap;
			};
			int _fd;
			int _capture_type;
			::booldog::multimedia::web_camera::buffer _buffers[4];
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
			web_camera(void)
			{
			};
			web_camera(::booldog::allocator* pallocator
#ifdef __LINUX__
				, int pfd
#endif
				)
				: _allocator(pallocator)
#ifdef __LINUX__
				, _fd(pfd)
#endif
			{
#ifdef __LINUX__
				::memset(_buffers, 0, sizeof(_buffers));
#endif
			};
			web_camera(const ::booldog::multimedia::web_camera&)
			{
			};
			::booldog::multimedia::web_camera& operator = (const ::booldog::multimedia::web_camera&)
			{
				return *this;
			};
		public:
			~web_camera(void)
			{
#ifdef __LINUX__
				for(_buffers_count = 0 ; _buffers_count < sizeof(_buffers) / sizeof(_buffers[0]) ; ++_buffers_count)
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
			};
			static bool open(::booldog::results::multimedia::camera* pres, ::booldog::allocator* allocator
				, const char* name, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				debuginfo = debuginfo;
				::booldog::results::multimedia::camera locres;
				BOOINIT_RESULT(::booldog::results::multimedia::camera);
#ifdef __LINUX__
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
					res->cam = allocator->create< ::booldog::multimedia::web_camera >(allocator, fd);
					if(res->cam == 0)
					{
						res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
						return false;
					}
					return true;
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
			};
			booinline bool available_formats(::booldog::result* pres, ::booldog::allocator* allocator
				, ::booldog::multimedia::typedefs::available_formats_callback_t callback, void* udata
				, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				::booldog::result locres;
				BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__
				v4l2_fmtdesc fmtdesc;
				fmtdesc.index = 0;
				fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
				bool next = true;
				v4l2_frmsizeenum framesizeenum;
				for(;;)
				{
					if(xioctl(_fd, VIDIOC_ENUM_FMT, &fmtdesc) != -1)
					{
						framesizeenum.index = 0;
						framesizeenum.pixel_format = fmtdesc.pixelformat;
						for(;;)
						{
							if(xioctl(_fd, VIDIOC_ENUM_FRAMESIZES, &framesizeenum) != -1)
							{
								if(framesizeenum.type == V4L2_FRMSIZE_TYPE_DISCRETE)
								{
									next = callback(allocator, udata, fmtdesc.pixelformat, framesizeenum.discrete.width
										, framesizeenum.discrete.height, (const char*)fmtdesc.description);
									//char sfcc[5] = {0}; *((::booldog::uint32*)sfcc) = fmtdesc.pixelformat;

									++framesizeenum.index;

									if(next == false)
										break;
								}
								else
								{
									next = callback(allocator, udata, fmtdesc.pixelformat, 0, 0, (const char*)fmtdesc.description);
									++framesizeenum.index;
									break;
								}
							}
							else
								break;
						}
						if(framesizeenum.index == 0)
							next = callback(allocator, udata, fmtdesc.pixelformat, 640, 480, (const char*)fmtdesc.description);
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
			};
			booinline bool start_capturing(::booldog::result* pres, ::booldog::uint32 fourcc, ::booldog::uint32 width
				, ::booldog::uint32 height, ::booldog::multimedia::typedefs::available_formats_callback_t callback
				, void* udata, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				::booldog::result locres;
				BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__
				enum v4l2_buf_type v4l2buftype;
				struct v4l2_buffer v4l2buf;
				struct v4l2_requestbuffers req;

				struct v4l2_capability cap;
				struct v4l2_cropcap cropcap;
				struct v4l2_crop crop;
				struct v4l2_format fmt;
				unsigned int min = 0;

				if(xioctl(_fd, VIDIOC_QUERYCAP, &cap) == -1)
				{
					res->seterrno();
					goto goto_return;
				}
				if(cap.capabilities & V4L2_CAP_STREAMING)
					_capture_type = V4L2_MEMORY_USERPTR;
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
				fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
				if(xioctl(_fd, VIDIOC_S_FMT, &fmt) == -1)
				{
					res->seterrno();
					goto goto_return;
				}
				min = fmt.fmt.pix.width * 2;
				if(fmt.fmt.pix.bytesperline < min)
					fmt.fmt.pix.bytesperline = min;
				min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
				if(fmt.fmt.pix.sizeimage < min)
					fmt.fmt.pix.sizeimage = min;
				if(_capture_type == V4L2_MEMORY_USERPTR)
				{
					::memset(&req, 0, sizeof(req));

					req.count  = 4;
					req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
					req.memory = V4L2_MEMORY_USERPTR;

					if(xioctl(_fd, VIDIOC_REQBUFS, &req) == -1)
					{
						int errnoval = errno;
						if(errnoval != EINVAL) 
						{
							res->seterrno(errnoval);
							goto goto_return;
						} 
						else
							_capture_type = V4L2_MEMORY_MMAP;
					}
					else
					{
						for(_buffers_count = 0 ; _buffers_count < sizeof(_buffers) / sizeof(_buffers[0]) ; ++_buffers_count)
						{
							if(_buffers[_buffers_count].mmap)
							{
								if(_buffers[_buffers_count].start)
								{
									munmap(_buffers[_buffers_count].start, _buffers[_buffers_count].length);
									_buffers[_buffers_count].start = 0;
								}
							}
							_buffers[_buffers_count].start = _allocator->realloc_array<char>((char*)_buffers[_buffers_count].start
								, fmt.fmt.pix.sizeimage, debuginfo);
							if(_buffers[_buffers_count].start == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								goto goto_return;
							}
							_buffers[_buffers_count].mmap = false;
							_buffers[_buffers_count].length = fmt.fmt.pix.sizeimage;
						}
					}
				}
				if(_capture_type == V4L2_MEMORY_MMAP)
				{
					::memset(&req, 0, sizeof(req));

					req.count = 4;
					req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
					req.memory = V4L2_MEMORY_MMAP;

					if(xioctl(_fd, VIDIOC_REQBUFS, &req) == -1)
					{
						int errnoval = errno;
						if(errnoval != EINVAL) 
						{
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

						for(_buffers_count = 0 ; _buffers_count < req.count ; ++_buffers_count)
						{
							::memset(&v4l2buf, 0, sizeof(v4l2buf));
							
							v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
							v4l2buf.memory = V4L2_MEMORY_MMAP;
							v4l2buf.index = _buffers_count;

							if(xioctl(_fd, VIDIOC_QUERYBUF, &v4l2buf) == -1)
							{
								res->seterrno();
								goto goto_return;
							}
							if(_buffers[_buffers_count].mmap)
							{
								if(_buffers[_buffers_count].start)
								{
									munmap(_buffers[_buffers_count].start, _buffers[_buffers_count].length);
									_buffers[_buffers_count].start = 0;
								}
							}
							else
							{
								if(_buffers[_buffers_count].start)
								{
									_allocator->free(_buffers[_buffers_count].start);
									_buffers[_buffers_count].start = 0;
								}
							}
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
						}
					}
					_buffers[0].start = _allocator->realloc_array<char>((char*)_buffers[0].start
						, fmt.fmt.pix.sizeimage, debuginfo);
					if(_buffers[0].start == 0)
					{
						res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
						goto goto_return;
					}
					_buffers[0].mmap = false;
					_buffers[0].length = fmt.fmt.pix.sizeimage;
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
							res->seterrno();
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
							res->seterrno();
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
					res->seterrno();
					goto goto_return;
				}
goto_return:
				if(res->succeeded())
				{
					_width = width;
					_height = height;
					_fourcc = fourcc;
					return true;
				}
				return false;
#else
				fourcc = fourcc;
				width = width;
				height = height;
				callback = callback;
				udata = udata;
				debuginfo = debuginfo;
				res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
				return res->succeeded();
#endif		
			};
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
					tv.tv_sec = 2;
					tv.tv_usec = 0;

					int resint = select(_fd + 1, &fds, 0, 0, &tv);
					if(resint == -1)
					{
						resint = errno;
						if(resint == EINTR)
							continue;
						res->seterrno(resint);
					}
					else if(resint != 0)
						res->bres = true;
					break;
				}
#else
				debuginfo = debuginfo;
				res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
#endif
				return res->succeeded();
			};
			booinline bool read_frame(::booldog::result* pres
				, ::booldog::multimedia::typedefs::read_frame_callback_t callback, void* udata
				, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				::booldog::result locres;
				BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__
				struct v4l2_buffer v4l2buf;
				switch(_capture_type)
				{
				case V4L2_MEMORY_USERPTR:
					::memset(&v4l2buf, 0, sizeof(v4l2buf));

					v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
					v4l2buf.memory = V4L2_MEMORY_USERPTR;

					if(xioctl(_fd, VIDIOC_DQBUF, &v4l2buf) == -1)
					{
						res->seterrno();
						return false;
					}
					int index = 0;
					for(;index < _buffers_count;++index)
					{
						if(v4l2buf.m.userptr == (unsigned long)_buffers[index].start
							&& v4l2buf.length == _buffers[index].length)
							break;
					}
					if(index < _buffer_count)
						callback(_allocator, udata, (void*)v4l2buf.m.userptr, v4l2buf.byteused, _fourcc, _width, _height);
					if(xioctl(_fd, VIDIOC_QBUF, &v4l2buf) == -1)
					{
						res->seterrno();
						return false;
					}
					break;
				case V4L2_MEMORY_MMAP:

					::memset(&v4l2buf, 0, sizeof(v4l2buf));

					v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
					v4l2buf.memory = V4L2_MEMORY_MMAP;

					if(xioctl(_fd, VIDIOC_DQBUF, &v4l2buf) == -1)
					{
						res->seterrno();
						return false;
					}
					callback(_allocator, udata, _buffers[v4l2buf.index].start, v4l2buf.byteused, _fourcc, _width, _height);
					if(xioctl(_fd, VIDIOC_QBUF, &v4l2buf) == -1)
					{
						res->seterrno();
						return false;
					}
					break;
				default:
					if(read(_fd, _buffers[0].start, _buffers[0].length) == -1)
					{
						res->seterrno();
						return false;
					}
					callback(_allocator, udata, _buffers[0].start, _buffers[0].length, _fourcc, _width, _height);
				}
#else
				callback = callback;
				udata = udata;
				debuginfo = debuginfo;
				res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
#endif
				return res->succeeded();
			};
			booinline bool close(::booldog::result* pres, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				debuginfo = debuginfo;
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
#ifdef __LINUX__				
#else
				debuginfo = debuginfo;
				res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
#endif
				_allocator->destroy(this);
				return res->succeeded();
			};
#ifdef __LINUX__
			struct listdir_callback_info
			{
				::booldog::result* res;
				::booldog::result_mbchar mbchar;
				struct v4l2_capability capability;
				::booldog::multimedia::typedefs::available_cameras_callback_t callback;
				void* udata;
				listdir_callback_info(::booldog::allocator* allocator
					, ::booldog::multimedia::typedefs::available_cameras_callback_t pcallback, void* pudata)
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
				, ::booldog::multimedia::typedefs::available_cameras_callback_t callback, void* udata
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
			};
		};
	};
};
#endif