#ifndef BOO_TICKCOUNT_H
#define BOO_TICKCOUNT_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_types.h"
#ifdef __WINDOWS__
#pragma comment(lib, "Winmm")
#else
#include <time.h>
#endif
namespace booldog
{
	namespace utils
	{
		namespace system
		{	
			booinline ::booldog::uint32 tickcount()
			{
#ifdef __LINUX__
				struct timespec ts = {};
				if(clock_gettime(CLOCK_MONOTONIC, &ts))
					clock_gettime(CLOCK_REALTIME, &ts);
				return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
#elif defined(__WINDOWS__)
				return timeGetTime();
#else
				return 0;
#endif
			}
		}
	}
}
#endif