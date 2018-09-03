#ifndef BOO_ENVIRONMENT_UTILS_H
#define BOO_ENVIRONMENT_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_string_utils.h"
namespace booldog
{
	namespace utils
	{
		namespace environment
		{	
			namespace wcs
			{
				/** Change environment variable PATH
				* @param pres store the function result or detailed error
				* @param allocator a additional allocator that's using local purposes
				* @param path a path that will be added to environment variable PATH
				* @param path_length a path length if equal to SIZE_MAX then it's calculated inside function
				* @param debuginfo a debug information
				* @return The function result
				*/
				booinline bool set_path(::booldog::result& pres, ::booldog::allocator* allocator
					, const wchar_t* path, size_t path_length = SIZE_MAX
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					pres.clear();
					allocator = allocator;
					path_length = path_length;
					debuginfo = debuginfo;
#ifdef __WINDOWS__
					if(SetEnvironmentVariableW(L"PATH", path) == 0)	{
						pres.GetLastError();
						return false;
					}
					return true;
#else
					allocator = allocator;
					path = path;
					path_length = path_length;
					debuginfo = debuginfo;
					pres.booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
					return false;
#endif
				}
				/** Add path to environment variable PATH
				* @param pres store the function result or detailed error
				* @param allocator a additional allocator that's using local purposes
				* @param path a path that will be added to environment variable PATH
				* @param path_length a path length if equal to SIZE_MAX then it's calculated inside function
				* @param debuginfo a debug information
				* @return The function result
				*/
				booinline bool add_path(::booldog::result& pres, ::booldog::allocator* allocator, const wchar_t* path
					, size_t path_length = SIZE_MAX, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					pres.clear();
#ifdef __WINDOWS__
					DWORD env_length = GetEnvironmentVariableW(L"PATH", 0, 0);
					if(env_length == 0)	{
						pres.GetLastError();
						return false;
					}
					wchar_t* ptr0 = 0;
					const wchar_t* ptr1 = path;
					if(path_length == SIZE_MAX) {
						path_length = wcslen(ptr1);
					}
					env_length += (DWORD)path_length + 2;
					wchar_t* env_path = allocator->realloc_array< wchar_t >(0, env_length, debuginfo);
					if(env_path == 0)
					{
						pres.booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
						return false;
					}
					env_length = GetEnvironmentVariableW(L"PATH", env_path, env_length);
					if(env_length == 0)
					{
						allocator->free(env_path);
						pres.GetLastError();
						return false;
					}
					bool exists = false, first = true;
					ptr0 = env_path;
					for(;;)
					{
						switch(*ptr0)
						{
						default:
							if(first)
							{
								--ptr0;
								first = false;
							}
							else
								break;
						case ';':
							++ptr0;
							ptr1 = path;
							for(;;)
							{
								if(*ptr0 == 0 || *ptr0 == ';' || *ptr1 == 0)
									break;
								if(*ptr0 == *ptr1)
								{
									++ptr0;
									++ptr1;
								}
								else
									break;
							}
							if(*ptr0 == 0 || *ptr0 == ';')
							{								
								if(*ptr1 == 0)
								{
									exists = true;
									goto goto_leave_loop;
								}
								continue;
							}
							break;
						case 0:
							goto goto_leave_loop;
						}
						++ptr0;
					}
goto_leave_loop:
					if(exists == false)
					{
						ptr0 = &env_path[env_length];
						*ptr0++ = ';';
						::memcpy(ptr0, path, path_length * sizeof(wchar_t));
						ptr0 += path_length;
						*ptr0 = 0;
						if(SetEnvironmentVariableW(L"PATH", env_path) == 0)
						{
							allocator->free(env_path);
							pres.GetLastError();
							return false;
						}
					}
					allocator->free(env_path);
					return true;
#else
					allocator = allocator;
					path = path;
					path_length = path_length;
					debuginfo = debuginfo;
					pres.booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
					return false;
#endif
				}
			}
			namespace mbs
			{
				/** Change environment variable PATH
				* @param pres store the function result or detailed error
				* @param allocator a additional allocator that's using local purposes
				* @param path a path that will be added to environment variable PATH
				* @param path_length a path length(if equal to SIZE_MAX then it's calculated inside function)
				* @param debuginfo a debug information
				* @return The function result
				*/
				booinline bool set_path(::booldog::result& pres, ::booldog::allocator* allocator, const char* path
					, size_t path_length = SIZE_MAX, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					pres.clear();
#ifdef __WINDOWS__
					::booldog::result_wchar reswchar(allocator);
					if(::booldog::utils::string::mbs::towcs(&reswchar, allocator, path, 0, path_length
						, debuginfo)) {
						return ::booldog::utils::environment::wcs::set_path(pres, allocator, reswchar.wchar
							, reswchar.wlen, debuginfo);
					}
					else {
						pres.copy(reswchar);
					}
					return false;
#else
					allocator = allocator;
					path = path;
					path_length = path_length;
					debuginfo = debuginfo;
					pres.booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
					return false;
#endif
				}
				/** Add path to environment variable PATH
				* @param pres store the function result or detailed error
				* @param allocator a additional allocator that's using local purposes
				* @param path a path that will be added to environment variable PATH
				* @param path_length a path length(if equal to SIZE_MAX then it's calculated inside function)
				* @param debuginfo a debug information
				* @return The function result
				*/
				booinline bool add_path(::booldog::result& pres, ::booldog::allocator* allocator, const char* path
					, size_t path_length = SIZE_MAX, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					pres.clear();
#ifdef __WINDOWS__
					::booldog::result_wchar reswchar(allocator);
					if(::booldog::utils::string::mbs::towcs(&reswchar, allocator, path, 0, path_length, debuginfo))
						return ::booldog::utils::environment::wcs::add_path(pres, allocator, reswchar.wchar, reswchar.wlen
						, debuginfo);
					else
						pres.copy(reswchar);
					return false;
#else
					allocator = allocator;
					path = path;
					path_length = path_length;
					debuginfo = debuginfo;
					pres.booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
					return false;
#endif
				}
			}
		}
	}
}
#endif
