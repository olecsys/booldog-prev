#ifndef BOO_THREADING_UTILS_H
#define BOO_THREADING_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_interlocked.h>
#ifdef __UNIX__
#include <time.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#endif
namespace booldog
{
	namespace threading
	{
		booinline void sleep( ::booldog::uint32 milliseconds )
		{
#ifdef __WINDOWS__
			::Sleep( milliseconds );
#else
			struct timespec ts = { 0 };	
			struct timespec rem = { 0 };
			ts.tv_sec = milliseconds / 1000;
			ts.tv_nsec = ( milliseconds % 1000 ) * 1000000;
			nanosleep( &ts , &rem );
#endif
		};
		booinline ::booldog::pid_t thread_id( void )
		{
#ifdef __WINDOWS__
			return ::GetCurrentThreadId();
#elif defined( __LINUX__ )
			return (::booldog::pid_t)syscall( SYS_gettid );
#elif defined( __SOLARIS__ )
			return pthread_self();
#endif
		};
	};
};
#endif