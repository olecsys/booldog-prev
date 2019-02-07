#ifndef BOO_FILE_UTILS_H
#define BOO_FILE_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_executable_utils.h"
#include "boo_io_utils.h"
#include "boo_param.h"
#include "boo_string_utils.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef __UNIX__
#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif
#include <unistd.h>
#ifdef __LINUX__
#include <sys/sendfile.h>
#endif
#endif
namespace booldog {
  namespace utils {
    namespace io {
      namespace file {
        namespace wcs {
          booinline bool exists(::booldog::result_bool* pres, ::booldog::allocator* allocator,
                                const wchar_t* name_or_path,
                                const ::booldog::debug::info& debuginfo = debuginfo_macros);
          booinline bool exists(::booldog::result_bool* pres, booldog::allocator* allocator,
                                const wchar_t* name_or_path,
                                ::booldog::named_param* named_params = 0,
                                const ::booldog::debug::info& debuginfo = debuginfo_macros);
          booinline bool copyfile(::booldog::result* pres, ::booldog::allocator* allocator,
                                  const wchar_t* srcpathname, size_t srcpathname_length,
                                  const wchar_t* dstpathname, size_t dstpathname_length,
                                  const ::booldog::debug::info& debuginfo = debuginfo_macros);
          booinline bool remove(::booldog::result* pres, ::booldog::allocator* allocator,
                                const wchar_t* pathname, size_t pathname_length,
                                const ::booldog::debug::info& debuginfo = debuginfo_macros);
          booinline bool remove(::booldog::result* pres, ::booldog::allocator* allocator,
                                const wchar_t* pathname,
                                const ::booldog::debug::info& debuginfo = debuginfo_macros);
        }; // namespace wcs
        namespace mbs {
          booinline bool remove(::booldog::result* pres, ::booldog::allocator* allocator,
                                const char* pathname, size_t pathname_length,
                                const ::booldog::debug::info& debuginfo = debuginfo_macros) {
            ::booldog::result locres;
            BOOINIT_RESULT(::booldog::result);
#ifdef __WINDOWS__
            if(pathname_length == SIZE_MAX || pathname_length >= MAX_PATH) {
              ::booldog::results::wchar wchar(allocator);
              if(::booldog::utils::string::mbs::towcs(
                   &wchar, allocator, pathname, 0, SIZE_MAX, debuginfo)) {
                if(wchar.wlen >= MAX_PATH) {
                  if(::booldog::utils::string::wcs::insert(res, allocator, false, 0, wchar.wchar,
                                                           wchar.wlen, wchar.wsize, L"\\\\?\\", 0,
                                                           SIZE_MAX, debuginfo) == false)
                    return false;
                  if(::booldog::utils::io::path::wcs::normalize(
                       res, wchar.wchar, wchar.wlen, wchar.wsize) == false)
                    return false;
                }
                return ::booldog::utils::io::file::wcs::remove(
                  res, allocator, wchar.wchar, wchar.wlen, debuginfo);
              } else {
                res->copy(wchar);
                return false;
              }
            } else if(DeleteFileA(pathname))
              return true;
            else {
              res->GetLastError();
              return false;
            }
#else
            debuginfo = debuginfo;
            pathname_length = pathname_length;
            allocator = allocator;
            if(::remove(pathname) == 0)
              return true;
            else {
              res->seterrno();
              return false;
            }
#endif
          }
          booinline bool remove(::booldog::result* pres, ::booldog::allocator* allocator,
                                const char* pathname,
                                const ::booldog::debug::info& debuginfo = debuginfo_macros) {
            return ::booldog::utils::io::file::mbs::remove(
              pres, allocator, pathname, SIZE_MAX, debuginfo);
          }
          booinline bool copyfile(::booldog::result* pres, ::booldog::allocator* allocator,
                                  const char* srcpathname, size_t srcpathname_length,
                                  const char* dstpathname, size_t dstpathname_length,
                                  const ::booldog::debug::info& debuginfo = debuginfo_macros) {
            ::booldog::result locres;
            BOOINIT_RESULT(::booldog::result);
#ifdef __WINDOWS__
            if(srcpathname_length == SIZE_MAX || dstpathname_length == SIZE_MAX ||
               srcpathname_length >= MAX_PATH || dstpathname_length >= MAX_PATH) {
              ::booldog::results::wchar srcwchar(allocator), dstwchar(allocator);
              if(::booldog::utils::string::mbs::towcs(
                   &srcwchar, allocator, srcpathname, 0, SIZE_MAX, debuginfo)) {
                if(srcwchar.wlen >= MAX_PATH) {
                  if(::booldog::utils::string::wcs::insert(
                       res, allocator, false, 0, srcwchar.wchar, srcwchar.wlen, srcwchar.wsize,
                       L"\\\\?\\", 0, SIZE_MAX, debuginfo) == false)
                    return false;
                  if(::booldog::utils::io::path::wcs::normalize(
                       res, srcwchar.wchar, srcwchar.wlen, srcwchar.wsize) == false)
                    return false;
                }
                if(::booldog::utils::string::mbs::towcs(
                     &dstwchar, allocator, dstpathname, 0, SIZE_MAX, debuginfo)) {
                  if(dstwchar.wlen >= MAX_PATH) {
                    if(::booldog::utils::string::wcs::insert(
                         res, allocator, false, 0, dstwchar.wchar, dstwchar.wlen, dstwchar.wsize,
                         L"\\\\?\\", 0, SIZE_MAX, debuginfo) == false)
                      return false;
                    if(::booldog::utils::io::path::wcs::normalize(
                         res, dstwchar.wchar, dstwchar.wlen, dstwchar.wsize) == false)
                      return false;
                  }
                  return ::booldog::utils::io::file::wcs::copyfile(res, allocator, srcwchar.wchar,
                                                                   srcwchar.wlen, dstwchar.wchar,
                                                                   dstwchar.wlen, debuginfo);
                } else {
                  res->copy(dstwchar);
                  return false;
                }
              } else {
                res->copy(srcwchar);
                return false;
              }
            } else {
              if(CopyFileA(srcpathname, dstpathname, TRUE))
                return true;
              else {
                res->GetLastError();
                return false;
              }
            }
#else
            srcpathname_length = srcpathname_length;
            dstpathname_length = dstpathname_length;
            int srcfd = ::open(srcpathname, O_RDONLY, 0);
            if(srcfd == -1) {
              res->seterrno();
              return false;
            }
            int dstfd = ::open(dstpathname, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
            if(dstfd == -1) {
              ::close(srcfd);
              res->seterrno();
              return false;
            }
            struct stat st;
            if(fstat(srcfd, &st) == -1) {
              ::close(dstfd);
              ::close(srcfd);
              res->seterrno();
              return false;
            }
            ssize_t written = 0;
#ifdef __LINUX__
            off_t offset = 0;
            while(offset != st.st_size) {
              written = sendfile(dstfd, srcfd, &offset, st.st_size);
              if(written == -1) {
                break;
              }
            }
            if(written != -1) {
              ::close(dstfd);
              ::close(srcfd);
              return true;
            }
            if(offset != 0) {
              lseek(dstfd, offset, SEEK_SET);
              lseek(srcfd, offset, SEEK_SET);
            }
            int err = errno;
            if(err != EINVAL && err != ENOSYS) {
              ::close(dstfd);
              ::close(srcfd);
              res->seterrno(err);
              return false;
            }
#endif
            size_t datasize = 8192;
            if(datasize > (size_t)st.st_size)
              datasize = st.st_size;
            unsigned char* data = allocator->realloc_array<unsigned char>(0, datasize, debuginfo);
            if(data == NULL) {
              ::close(dstfd);
              ::close(srcfd);
              res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
              return false;
            }
            while((written = ::read(srcfd, data, datasize)) > 0) {
              if(::write(dstfd, data, written) == -1) {
                written = -1;
                break;
              }
            }
            allocator->free(data);
            ::close(dstfd);
            ::close(srcfd);
            if(written != -1) {
              return true;
            } else {
              res->seterrno();
              return false;
            }
#endif
          }
          booinline bool exists(::booldog::result_bool* pres, ::booldog::allocator* allocator,
                                const char* name_or_path,
                                const ::booldog::debug::info& debuginfo = debuginfo_macros) {
            ::booldog::result_bool locres;
            BOOINIT_RESULT(::booldog::result_bool);
#ifdef __WINDOWS__
            ::booldog::result_wchar reswchar(allocator);
            if(::booldog::utils::string::mbs::towcs(
                 &reswchar, allocator, name_or_path, 0, SIZE_MAX, debuginfo))
              return ::booldog::utils::io::file::wcs::exists(
                res, allocator, reswchar.wchar, debuginfo);
            else {
              res->copy(reswchar);
              return false;
            }
#else
            debuginfo = debuginfo;
            allocator = allocator;
            struct stat st;
            if(stat(name_or_path, &st) == 0) {
              if(S_ISREG(st.st_mode))
                res->bres = true;
              return true;
            } else {
              int err = errno;
              if(err != ENOENT) {
                res->seterrno(err);
                return false;
              }
              return true;
            }
#endif
          }
          booinline bool exists(::booldog::result_bool* pres, booldog::allocator* allocator,
                                const char* name_or_path, ::booldog::named_param* named_params = 0,
                                const ::booldog::debug::info& debuginfo = debuginfo_macros) {
            ::booldog::result_bool locres;
            BOOINIT_RESULT(::booldog::result_bool);
#ifdef __WINDOWS__
            ::booldog::result_wchar reswchar(allocator);
            if(::booldog::utils::string::mbs::towcs(
                 &reswchar, allocator, name_or_path, 0, SIZE_MAX, debuginfo))
              ::booldog::utils::io::file::wcs::exists(
                res, allocator, reswchar.wchar, named_params, debuginfo);
            else
              res->copy(reswchar);
#else
            booldog::named_param settings[] = {
              BOO_SEARCH_NAMED_PARAM_PPARAM("search_paths"),
              BOO_SEARCH_NAMED_PARAM_PCHAR("root_path"), BOO_SEARCH_NAMED_PARAM_WCHAR("root_path"),
              BOO_SEARCH_NAMED_PARAM_BOOL("exedir_as_root_path"), BOO_SEARCH_NAMED_PARAM_NONE};
            ::booldog::utils::param::search(named_params, settings);

            ::booldog::result_mbchar res_name_or_path(allocator);

            ::booldog::result_bool resbool;
            ::booldog::result resres;
            if(::booldog::utils::string::mbs::insert<0>(
                 &resres, allocator, true, 0, res_name_or_path.mbchar, res_name_or_path.mblen,
                 res_name_or_path.mbsize, name_or_path, 0, SIZE_MAX, debuginfo) == false) {
              res->copy(resres);
              goto goto_return;
            }
            if(::booldog::utils::io::path::mbs::isabsolute(&resbool, res_name_or_path.mbchar) ==
               false) {
              res->copy(resbool);
              goto goto_return;
            }
            if(resbool.bres) {
              if(::booldog::utils::io::path::mbs::normalize(&resres, res_name_or_path.mbchar,
                                                            res_name_or_path.mblen,
                                                            res_name_or_path.mbsize) == false) {
                res->copy(resres);
                goto goto_return;
              }
              return ::booldog::utils::io::file::mbs::exists(
                res, allocator, res_name_or_path.mbchar, debuginfo);
            } else {
              ::booldog::result_mbchar res_root_dir(allocator);

              if(settings[1].type != ::booldog::enums::param::type_not_found) {
                if(::booldog::utils::string::mbs::insert<0>(
                     &resres, allocator, false, SIZE_MAX, res_root_dir.mbchar, res_root_dir.mblen,
                     res_root_dir.mbsize, settings[1].pcharvalue, 0, SIZE_MAX,
                     debuginfo) == false) {
                  res->copy(res_root_dir);
                  goto goto_return;
                }
              } else if(settings[2].type != ::booldog::enums::param::type_not_found) {
                if(::booldog::utils::string::wcs::tombs(
                     res_root_dir, settings[2].pwcharvalue, 0, SIZE_MAX, debuginfo) == false) {
                  res->copy(resres);
                  goto goto_return;
                }
              } else {
                if(settings[3].type != ::booldog::enums::param::type_not_found &&
                   settings[3].boolvalue) {
                  if(::booldog::utils::executable::mbs::directory<256>(
                       &res_root_dir, allocator, debuginfo) == false) {
                    res->copy(res_root_dir);
                    goto goto_return;
                  }
                }
              }
              size_t res_root_dir_mblen = 0;
              if(res_root_dir.mbchar) {
                ::booldog::result resres;
                if(::booldog::utils::io::path::mbs::normalize(&resres, res_root_dir.mbchar,
                                                              res_root_dir.mblen,
                                                              res_root_dir.mbsize) == false) {
                  res->copy(resres);
                  goto goto_return;
                }
                res_root_dir_mblen = res_root_dir.mblen;
              }
              if(settings[0].type != ::booldog::enums::param::type_not_found) {
                for(size_t index = 0;
                    settings[0].pparamvalue[index].type != ::booldog::enums::param::type_none;
                    index++) {
                  if(res_root_dir.mbchar) {
                    res_root_dir.mbchar[res_root_dir_mblen] = 0;
                    res_root_dir.mblen = res_root_dir_mblen;
                  }
                  if(res_root_dir_mblen) {
                    if(::booldog::utils::string::mbs::insert<0>(
                         &resres, allocator, false, res_root_dir.mblen, res_root_dir.mbchar,
                         res_root_dir.mblen, res_root_dir.mbsize, &::booldog::io::mbs::slash, 0, 1,
                         debuginfo) == false) {
                      res->copy(resres);
                      goto goto_return;
                    }
                  }
                  if(settings[0].pparamvalue[index].type == ::booldog::enums::param::type_pchar) {
                    if(::booldog::utils::string::mbs::insert<0>(
                         &resres, allocator, false, res_root_dir.mblen, res_root_dir.mbchar,
                         res_root_dir.mblen, res_root_dir.mbsize,
                         settings[0].pparamvalue[index].pcharvalue, 0, SIZE_MAX,
                         debuginfo) == false) {
                      res->copy(resres);
                      goto goto_return;
                    }
                  } else if(settings[0].pparamvalue[index].type ==
                            ::booldog::enums::param::type_pwchar) {
                    if(::booldog::utils::string::wcs::insert(
                         &resres, allocator, false, res_root_dir.mblen, res_root_dir.mbchar,
                         res_root_dir.mblen, res_root_dir.mbsize,
                         settings[0].pparamvalue[index].pwcharvalue, 0, SIZE_MAX,
                         debuginfo) == false) {
                      res->copy(resres);
                      goto goto_return;
                    }
                  } else
                    continue;
                  if(::booldog::utils::string::mbs::insert<0>(
                       &resres, allocator, false, res_root_dir.mblen, res_root_dir.mbchar,
                       res_root_dir.mblen, res_root_dir.mbsize, &::booldog::io::mbs::slash, 0, 1,
                       debuginfo) == false) {
                    res->copy(resres);
                    goto goto_return;
                  }
                  if(::booldog::utils::string::mbs::insert<0>(
                       &resres, allocator, false, res_root_dir.mblen, res_root_dir.mbchar,
                       res_root_dir.mblen, res_root_dir.mbsize, res_name_or_path.mbchar, 0,
                       SIZE_MAX, debuginfo) == false) {
                    res->copy(resres);
                    goto goto_return;
                  }
                  if(::booldog::utils::io::file::mbs::exists(
                       res, allocator, res_root_dir.mbchar, 0, debuginfo) == false ||
                     res->bres)
                    goto goto_return;
                }
              }
              if(res_root_dir.mbchar) {
                res_root_dir.mbchar[res_root_dir_mblen] = 0;
                res_root_dir.mblen = res_root_dir_mblen;
                if(res_root_dir_mblen) {
                  if(::booldog::utils::string::mbs::insert<0>(
                       &resres, allocator, false, res_root_dir.mblen, res_root_dir.mbchar,
                       res_root_dir.mblen, res_root_dir.mbsize, &::booldog::io::mbs::slash, 0, 1,
                       debuginfo) == false) {
                    res->copy(resres);
                    goto goto_return;
                  }
                }
                if(::booldog::utils::string::mbs::insert<0>(
                     &resres, allocator, false, res_root_dir.mblen, res_root_dir.mbchar,
                     res_root_dir.mblen, res_root_dir.mbsize, res_name_or_path.mbchar, 0, SIZE_MAX,
                     debuginfo) == false) {
                  res->copy(resres);
                  goto goto_return;
                }
                if(::booldog::utils::io::file::mbs::exists(
                     res, allocator, res_root_dir.mbchar, 0, debuginfo) == false ||
                   res->bres)
                  goto goto_return;
              } else {
                if(::booldog::utils::io::path::mbs::normalize(&resres, res_name_or_path.mbchar,
                                                              res_name_or_path.mblen,
                                                              res_name_or_path.mbsize) == false) {
                  res->copy(resres);
                  goto goto_return;
                }
                return ::booldog::utils::io::file::mbs::exists(
                  res, allocator, res_name_or_path.mbchar, debuginfo);
              }
            }
          goto_return:
#endif
            return res->succeeded();
          };
        }; // namespace mbs
        namespace wcs {
          booinline bool remove(::booldog::result* pres, ::booldog::allocator* allocator,
                                const wchar_t* pathname, size_t pathname_length,
                                const ::booldog::debug::info& debuginfo) {
            ::booldog::result locres;
            BOOINIT_RESULT(::booldog::result);
#ifdef __WINDOWS__
            debuginfo = debuginfo;
            if(pathname_length == SIZE_MAX || pathname_length >= MAX_PATH) {
              ::booldog::results::wchar wchar(allocator);
              if(::booldog::utils::string::wcs::insert(res, allocator, false, 0, wchar.wchar,
                                                       wchar.wlen, wchar.wsize, L"\\\\?\\", 0,
                                                       SIZE_MAX, debuginfo) == false)
                return false;
              if(::booldog::utils::string::wcs::insert(res, allocator, false, wchar.wlen,
                                                       wchar.wchar, wchar.wlen, wchar.wsize,
                                                       pathname, 0, SIZE_MAX, debuginfo) == false)
                return false;
              if(::booldog::utils::io::path::wcs::normalize(
                   res, wchar.wchar, wchar.wlen, wchar.wsize) == false)
                return false;
              if(DeleteFileW(wchar.wchar))
                return true;
              else {
                res->GetLastError();
                return false;
              }
            } else if(DeleteFileW(pathname))
              return true;
            else {
              res->GetLastError();
              return false;
            }
#else
            ::booldog::results::mbchar mbchar(allocator);
            if(::booldog::utils::string::wcs::tombs(
                 mbchar, pathname, 0, pathname_length, debuginfo))
              return ::booldog::utils::io::file::mbs::remove(
                res, allocator, mbchar.mbchar, mbchar.mblen, debuginfo);
            else {
              res->copy(mbchar);
              return false;
            }
#endif
          }
          booinline bool remove(::booldog::result* pres, ::booldog::allocator* allocator,
                                const wchar_t* pathname, const ::booldog::debug::info& debuginfo) {
            return ::booldog::utils::io::file::wcs::remove(
              pres, allocator, pathname, SIZE_MAX, debuginfo);
          }
          booinline bool copyfile(::booldog::result* pres, ::booldog::allocator* allocator,
                                  const wchar_t* srcpathname, size_t srcpathname_length,
                                  const wchar_t* dstpathname, size_t dstpathname_length,
                                  const ::booldog::debug::info& debuginfo) {
            ::booldog::result locres;
            BOOINIT_RESULT(::booldog::result);
#ifdef __WINDOWS__
            debuginfo = debuginfo;
            allocator = allocator;
            if(srcpathname_length == SIZE_MAX || dstpathname_length == SIZE_MAX ||
               srcpathname_length >= MAX_PATH || dstpathname_length >= MAX_PATH) {
              ::booldog::results::wchar srcwchar(allocator), dstwchar(allocator);
              if(::booldog::utils::string::wcs::insert(res, allocator, false, 0, srcwchar.wchar,
                                                       srcwchar.wlen, srcwchar.wsize, L"\\\\?\\", 0,
                                                       SIZE_MAX, debuginfo) == false)
                return false;
              if(::booldog::utils::string::wcs::insert(res, allocator, false, 0, dstwchar.wchar,
                                                       dstwchar.wlen, dstwchar.wsize, L"\\\\?\\", 0,
                                                       SIZE_MAX, debuginfo) == false)
                return false;
              if(::booldog::utils::string::wcs::insert(
                   res, allocator, false, srcwchar.wlen, srcwchar.wchar, srcwchar.wlen,
                   srcwchar.wsize, srcpathname, 0, SIZE_MAX, debuginfo) == false)
                return false;
              if(::booldog::utils::io::path::wcs::normalize(
                   res, srcwchar.wchar, srcwchar.wlen, srcwchar.wsize) == false)
                return false;
              if(::booldog::utils::string::wcs::insert(
                   res, allocator, false, dstwchar.wlen, dstwchar.wchar, dstwchar.wlen,
                   dstwchar.wsize, dstpathname, 0, SIZE_MAX, debuginfo) == false)
                return false;
              if(::booldog::utils::io::path::wcs::normalize(
                   res, dstwchar.wchar, dstwchar.wlen, dstwchar.wsize) == false)
                return false;
              if(CopyFileW(srcwchar.wchar, dstwchar.wchar, TRUE))
                return true;
              else {
                res->GetLastError();
                return false;
              }
            } else if(CopyFileW(srcpathname, dstpathname, TRUE))
              return true;
            else {
              res->GetLastError();
              return false;
            }
#else
            ::booldog::results::mbchar srcmbchar(allocator), dstmbchar(allocator);
            if(::booldog::utils::string::wcs::tombs(
                 srcmbchar, srcpathname, 0, srcpathname_length, debuginfo)) {
              if(::booldog::utils::string::wcs::tombs(
                   dstmbchar, dstpathname, 0, dstpathname_length, debuginfo)) {
                return ::booldog::utils::io::file::mbs::copyfile(res, allocator, srcmbchar.mbchar,
                                                                 srcmbchar.mblen, dstmbchar.mbchar,
                                                                 dstmbchar.mblen, debuginfo);
              } else {
                res->copy(dstmbchar);
                return false;
              }
            } else {
              res->copy(srcmbchar);
              return false;
            }
#endif
          }
          booinline bool exists(::booldog::result_bool* pres, ::booldog::allocator* allocator,
                                const wchar_t* name_or_path,
                                const ::booldog::debug::info& debuginfo) {
            ::booldog::result_bool locres;
            BOOINIT_RESULT(::booldog::result_bool);
#ifdef __WINDOWS__
            debuginfo = debuginfo;
            allocator = allocator;
            struct _stat64 _Stat64;
            if(_wstat64(name_or_path, &_Stat64) == 0) {
              if((_Stat64.st_mode & _S_IFREG))
                res->bres = true;
              return true;
            } else {
              int err = errno;
              if(err != ENOENT) {
                res->seterrno();
                return false;
              } else
                return true;
            }
#else
            ::booldog::result_mbchar resmbchar(allocator);
            if(::booldog::utils::string::wcs::tombs(
                 resmbchar, name_or_path, 0, SIZE_MAX, debuginfo))
              return ::booldog::utils::io::file::mbs::exists(
                res, allocator, resmbchar.mbchar, debuginfo);
            else {
              res->copy(resmbchar);
              return false;
            }
#endif
          }
          bool exists(::booldog::result_bool* pres, booldog::allocator* allocator,
                      const wchar_t* name_or_path, ::booldog::named_param* named_params,
                      const ::booldog::debug::info& debuginfo) {
            ::booldog::result_bool locres;
            BOOINIT_RESULT(::booldog::result_bool);
#ifdef __WINDOWS__
            booldog::named_param settings[] = {
              BOO_SEARCH_NAMED_PARAM_PPARAM("search_paths"),
              BOO_SEARCH_NAMED_PARAM_PCHAR("root_path"), BOO_SEARCH_NAMED_PARAM_WCHAR("root_path"),
              BOO_SEARCH_NAMED_PARAM_BOOL("exedir_as_root_path"), BOO_SEARCH_NAMED_PARAM_NONE};
            ::booldog::utils::param::search(named_params, settings);

            ::booldog::result_wchar res_name_or_path(allocator);

            ::booldog::result_bool resbool;
            ::booldog::result resres;
            if(::booldog::utils::string::wcs::insert(
                 &resres, allocator, true, 0, res_name_or_path.wchar, res_name_or_path.wlen,
                 res_name_or_path.wsize, name_or_path, 0, SIZE_MAX, debuginfo) == false) {
              res->copy(resres);
              goto goto_return;
            }
            if(::booldog::utils::io::path::wcs::isabsolute(&resbool, res_name_or_path.wchar) ==
               false) {
              res->copy(resbool);
              goto goto_return;
            }
            if(resbool.bres) {
              if(::booldog::utils::io::path::wcs::normalize(&resres, res_name_or_path.wchar,
                                                            res_name_or_path.wlen,
                                                            res_name_or_path.wsize) == false) {
                res->copy(resres);
                goto goto_return;
              }
              return ::booldog::utils::io::file::wcs::exists(
                res, allocator, res_name_or_path.wchar, debuginfo);
            } else {
              ::booldog::result_wchar res_root_dir(allocator);

              if(settings[1].type != ::booldog::enums::param::type_not_found) {
                if(::booldog::utils::string::mbs::towcs(&res_root_dir, allocator,
                                                        settings[1].pcharvalue, 0, SIZE_MAX,
                                                        debuginfo) == false) {
                  res->copy(res_root_dir);
                  goto goto_return;
                }
              } else if(settings[2].type != ::booldog::enums::param::type_not_found) {
                if(::booldog::utils::string::wcs::insert(
                     &resres, allocator, false, SIZE_MAX, res_root_dir.wchar, res_root_dir.wlen,
                     res_root_dir.wsize, settings[2].pwcharvalue, 0, SIZE_MAX,
                     debuginfo) == false) {
                  res->copy(resres);
                  goto goto_return;
                }
              } else {
                if(settings[3].type != ::booldog::enums::param::type_not_found &&
                   settings[3].boolvalue) {
                  if(::booldog::utils::executable::wcs::directory<256>(
                       &res_root_dir, allocator, debuginfo) == false) {
                    res->copy(res_root_dir);
                    goto goto_return;
                  }
                }
              }
              size_t res_root_dir_wlen = 0;
              if(res_root_dir.wchar) {
                ::booldog::result resres1;
                if(::booldog::utils::io::path::wcs::normalize(&resres1, res_root_dir.wchar,
                                                              res_root_dir.wlen,
                                                              res_root_dir.wsize) == false) {
                  res->copy(resres1);
                  goto goto_return;
                }
                res_root_dir_wlen = res_root_dir.wlen;
              }
              if(settings[0].type != ::booldog::enums::param::type_not_found) {
                for(size_t index = 0;
                    settings[0].pparamvalue[index].type != ::booldog::enums::param::type_none;
                    index++) {
                  if(res_root_dir.wchar) {
                    res_root_dir.wchar[res_root_dir_wlen] = 0;
                    res_root_dir.wlen = res_root_dir_wlen;
                  }
                  if(res_root_dir_wlen) {
                    if(::booldog::utils::string::wcs::insert(
                         &resres, allocator, false, res_root_dir.wlen, res_root_dir.wchar,
                         res_root_dir.wlen, res_root_dir.wsize, &::booldog::io::wcs::slash, 0, 1,
                         debuginfo) == false) {
                      res->copy(resres);
                      goto goto_return;
                    }
                  }
                  if(settings[0].pparamvalue[index].type == ::booldog::enums::param::type_pchar) {
                    if(::booldog::utils::string::mbs::insert(
                         &resres, allocator, false, res_root_dir.wlen, res_root_dir.wchar,
                         res_root_dir.wlen, res_root_dir.wsize,
                         settings[0].pparamvalue[index].pcharvalue, 0, SIZE_MAX,
                         debuginfo) == false) {
                      res->copy(resres);
                      goto goto_return;
                    }
                  } else if(settings[0].pparamvalue[index].type ==
                            ::booldog::enums::param::type_pwchar) {
                    if(::booldog::utils::string::wcs::insert(
                         &resres, allocator, false, res_root_dir.wlen, res_root_dir.wchar,
                         res_root_dir.wlen, res_root_dir.wsize,
                         settings[0].pparamvalue[index].pwcharvalue, 0, SIZE_MAX,
                         debuginfo) == false) {
                      res->copy(resres);
                      goto goto_return;
                    }
                  } else
                    continue;
                  if(::booldog::utils::string::wcs::insert(
                       &resres, allocator, false, res_root_dir.wlen, res_root_dir.wchar,
                       res_root_dir.wlen, res_root_dir.wsize, &::booldog::io::wcs::slash, 0, 1,
                       debuginfo) == false) {
                    res->copy(resres);
                    goto goto_return;
                  }
                  if(::booldog::utils::string::wcs::insert(
                       &resres, allocator, false, res_root_dir.wlen, res_root_dir.wchar,
                       res_root_dir.wlen, res_root_dir.wsize, res_name_or_path.wchar, 0, SIZE_MAX,
                       debuginfo) == false) {
                    res->copy(resres);
                    goto goto_return;
                  }
                  if(::booldog::utils::io::file::wcs::exists(
                       res, allocator, res_root_dir.wchar, 0, debuginfo) == false ||
                     res->bres)
                    goto goto_return;
                }
              }
              if(res_root_dir.wchar) {
                res_root_dir.wchar[res_root_dir_wlen] = 0;
                res_root_dir.wlen = res_root_dir_wlen;
                if(res_root_dir_wlen) {
                  if(::booldog::utils::string::wcs::insert(
                       &resres, allocator, false, res_root_dir.wlen, res_root_dir.wchar,
                       res_root_dir.wlen, res_root_dir.wsize, &::booldog::io::wcs::slash, 0, 1,
                       debuginfo) == false) {
                    res->copy(resres);
                    goto goto_return;
                  }
                }
                if(::booldog::utils::string::wcs::insert(
                     &resres, allocator, false, res_root_dir.wlen, res_root_dir.wchar,
                     res_root_dir.wlen, res_root_dir.wsize, res_name_or_path.wchar, 0, SIZE_MAX,
                     debuginfo) == false) {
                  res->copy(resres);
                  goto goto_return;
                }
                if(::booldog::utils::io::file::wcs::exists(
                     res, allocator, res_root_dir.wchar, 0, debuginfo) == false ||
                   res->bres)
                  goto goto_return;
              } else {
                if(::booldog::utils::io::path::wcs::normalize(&resres, res_name_or_path.wchar,
                                                              res_name_or_path.wlen,
                                                              res_name_or_path.wsize) == false) {
                  res->copy(resres);
                  goto goto_return;
                }
                return ::booldog::utils::io::file::wcs::exists(
                  res, allocator, res_name_or_path.wchar, debuginfo);
              }
            }
          goto_return:
#else
            ::booldog::result_mbchar resmbchar(allocator);
            if(::booldog::utils::string::wcs::tombs(
                 resmbchar, name_or_path, 0, SIZE_MAX, debuginfo))
              ::booldog::utils::io::file::mbs::exists(
                res, allocator, resmbchar.mbchar, named_params, debuginfo);
            else
              res->copy(resmbchar);
#endif
            return res->succeeded();
          };
        }; // namespace wcs
      };   // namespace file
    };     // namespace io
  };       // namespace utils
};         // namespace booldog
#endif
