#ifndef BOO_THREADING_UTILS_H
#define BOO_THREADING_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_types.h"

#ifdef __UNIX__
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
		booinline void sleep( ::booldog::uint32 milliseconds )
		{
#ifdef __WINDOWS__
                        ::Sleep(milliseconds);
#else
                        struct timespec ts = {};
                        struct timespec rem = {};
			ts.tv_sec = milliseconds / 1000;
			ts.tv_nsec = ( milliseconds % 1000 ) * 1000000;
			nanosleep( &ts , &rem );
#endif
                }
		booinline ::booldog::pid_t threadid( void )
		{
#ifdef __WINDOWS__
			return ::GetCurrentThreadId();
#elif defined( __LINUX__ )
#ifdef __ANDROID__
			return (::booldog::pid_t)gettid();
#else
			return (::booldog::pid_t)syscall( SYS_gettid );
#endif
#elif defined( __SOLARIS__ )
			return pthread_self();
#endif
		};
		booinline void set_thread_name( const char* name )
		{
#ifdef __WINDOWS__			
			struct
			{
				::booldog::uint32 _type;
				const char* _name;
				::booldog::uint32 _thread_id;
				::booldog::uint32 _flags;		
			}info = { 0x1000 , name , ::booldog::threading::threadid() , 0 }; 
			__try
			{
#ifdef __x64__
				RaiseException( 0x406d1388 , 0 , sizeof( info ) / sizeof( ::booldog::uint32 ) , (::booldog::uint64*)&info );
#elif defined( __x86__ )
				RaiseException( 0x406d1388 , 0 , sizeof( info ) / sizeof( unsigned long ) , (unsigned long*)&info );
#endif
			}
			__except( EXCEPTION_CONTINUE_EXECUTION )
			{
			};
#elif defined( __LINUX__ )
			prctl( PR_SET_NAME , name );
#endif
		};
	};
};
#endif
