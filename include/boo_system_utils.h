#ifndef BOO_SYSTEM_UTILS_H
#define BOO_SYSTEM_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_string_utils.h"
#ifdef __WINDOWS__
#pragma comment(lib, "Advapi32")
#else
#ifndef _LARGEFILE64_SOURCE 
#define _LARGEFILE64_SOURCE 
#endif
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif
namespace booldog
{
	namespace utils
	{
		namespace system
		{	
			namespace mbs
			{
				/** Get current process user name
				* @param pres store the function result or detailed error
				* @param allocator a additional allocator that's using when pres is NULL
				* @param debuginfo a debug information
				* @return The function result
				*/
				template< size_t step >
				booinline bool username(::booldog::result_mbchar* pres, ::booldog::allocator* allocator
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					::booldog::result_mbchar locres(allocator);
					BOOINIT_RESULT(::booldog::result_mbchar);					
#ifdef __WINDOWS__
					if(res->mbchar == 0)
					{
						res->mbsize += step;
						res->mbchar = res->mballocator->realloc_array< char >(res->mbchar, res->mbsize, debuginfo);
						if(res->mbchar == 0)
						{
							res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							return false;
						}
					}
					DWORD username_size = (DWORD)res->mbsize;
					if(GetUserNameA(res->mbchar, &username_size) == 0)
					{
						DWORD get_last_error = GetLastError();
						if(get_last_error == ERROR_INSUFFICIENT_BUFFER)
						{
							res->mbsize = username_size;
							res->mbchar = res->mballocator->realloc_array< char >(res->mbchar, res->mbsize, debuginfo);
							if(res->mbchar == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								return false;
							}
							if(GetUserNameA(res->mbchar, &username_size) == 0)
							{
								res->GetLastError();
								return false;
							}
						}
						else
						{
							res->GetLastError(get_last_error);
							return false;
						}
					}
#else
					::booldog::result resres;
					uid_t uid = geteuid();
					struct passwd psw, * ppsw;
					size_t bufsize = step;
					char* buf = 0;
					for(;;)
					{
						buf = res->mballocator->realloc_array< char >(buf, bufsize, debuginfo);
						if(buf == 0)
						{
							res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							return false;
						}
						int errno_int = getpwuid_r(uid, &psw, buf, bufsize, &ppsw);
						if(errno_int == 0)
							break;
						else if(errno_int != ERANGE)
						{
							res->mballocator->free(buf);
							res->seterrno(errno_int);
							return false;
						}
						bufsize += step;
					}
					if(::booldog::utils::string::mbs::assign< step >(&resres, res->mballocator, true, 0, res->mbchar, res->mblen
						, res->mbsize, psw.pw_name, 0, SIZE_MAX, debuginfo) == false)
					{
						res->mballocator->free(buf);
						res->copy(resres);
						return false;
					}
					res->mballocator->free(buf);
#endif
					return true;
				}
			}
		}
	}
}
#endif