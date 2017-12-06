#ifndef BOO_THREADING_UTILS_H
#define BOO_THREADING_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_platform.h"

#ifdef __WINDOWS__
#include <WinBase.h>
#else
#include <time.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef _LARGEFILE64_SOURCE 
#define _LARGEFILE64_SOURCE 
#endif
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/prctl.h>
#ifdef __LINUX__
#include <linux/prctl.h>
#endif
#endif
namespace booldog
{
	namespace threading
	{
		inline void sleep(unsigned int milliseconds)
		{
#ifdef __WINDOWS__
      ::Sleep(milliseconds);
#else
      struct timespec ts = {};
      struct timespec rem = {};
			ts.tv_sec = milliseconds / 1000;
			ts.tv_nsec = (milliseconds % 1000) * 1000000;
			nanosleep(&ts, &rem);
#endif
    }
		inline unsigned int threadid( void )
		{
#ifdef __WINDOWS__
			return ::GetCurrentThreadId();
#elif defined( __LINUX__ )
#ifdef __ANDROID__
			return (unsigned int)gettid();
#else
			return (unsigned int)syscall( SYS_gettid );
#endif
#elif defined( __SOLARIS__ )
			return pthread_self();
#endif
		};
		inline void set_thread_name(const char* name)
		{
#ifdef __WINDOWS__			
			struct
			{
				unsigned int _type;
				const char* _name;
				unsigned int _thread_id;
				unsigned int _flags;		
			}info = {0x1000, name, ::booldog::threading::threadid(), 0}; 
			__try
			{
#ifdef __x64__
				RaiseException(0x406d1388, 0, sizeof(info) / sizeof(unsigned int), (unsigned __int64*)&info);
#elif defined( __x86__ )
				RaiseException(0x406d1388, 0, sizeof(info) / sizeof(unsigned long), (unsigned long*)&info);
#endif
			}
			__except( EXCEPTION_CONTINUE_EXECUTION )
			{
			}
#elif defined( __LINUX__ )
			prctl(PR_SET_NAME, name);
#endif
		}
	}
}
#endif
