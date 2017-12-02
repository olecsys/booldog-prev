#ifndef BOO_PROCESS_UTILS_H
#define BOO_PROCESS_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_string_utils.h"
#ifdef __WINDOWS__
#else
#include <sys/types.h>
#ifndef _LARGEFILE64_SOURCE 
#define _LARGEFILE64_SOURCE 
#endif
#include <unistd.h>
#endif
namespace booldog
{
	namespace utils
	{
		namespace process
		{	
			booinline ::booldog::pid_t pid()
			{
#ifdef __WINDOWS__
				return GetCurrentProcessId();
#else
				return getpid();
#endif
			}
		}
	}
}
#endif