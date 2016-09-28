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
		};
		class web_camera
		{
			friend class ::booldog::allocator;
			::booldog::allocator* _allocator;
		private:
#ifdef __LINUX__
			int _fd;
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
			};
			web_camera(const ::booldog::multimedia::web_camera&)
			{
			};
			::booldog::multimedia::web_camera& operator = (const ::booldog::multimedia::web_camera&)
			{
				return *this;
			};
		public:
			static bool open(::booldog::results::multimedia::camera* pres, ::booldog::allocator* allocator
				, const char* name, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				debuginfo = debuginfo;
				::booldog::results::multimedia::camera locres;
				BOOINIT_RESULT(::booldog::results::multimedia::camera);
#ifdef __LINUX__
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
goto_return:
				if(res->succeeded() == false)
				{
					if(fd != -1)
						::close(fd);
					return false;
				}
				else
				{
					res->cam = allocator->create< ::booldog::multimedia::web_camera >(allocator, fd);
					if(res->cam == 0)
					{
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
									//char sfcc[5] = {0}; *((rux::uint32*)sfcc) = fmtdesc.pixelformat;

									++framesizeenum.index;
									if(next == false)
										break;
								}
								else
									break;
							}
							else
								break;
						}
						if(framesizeenum.index == 0)
							next = callback(allocator, udata, fmtdesc.pixelformat, 0, 0, (const char*)fmtdesc.description);
					}
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