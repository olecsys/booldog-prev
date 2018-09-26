#ifndef BOO_THREADING_THREAD_H
#define BOO_THREADING_THREAD_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_platform.h"
#ifdef __WINDOWS__
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinBase.h>
#include <process.h>
#else
#ifndef _LARGEFILE64_SOURCE 
#define _LARGEFILE64_SOURCE 
#endif
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#endif
#ifndef BOO_THREAD_CPU_MIN
#define BOO_THREAD_CPU_MIN 0
#endif
#ifndef BOO_THREAD_CPU_MAX
#define BOO_THREAD_CPU_MAX INT_MAX
#endif
#ifndef BOO_THREAD_EXCLUDE_CPU
#define BOO_THREAD_EXCLUDE_CPU INT_MAX
#endif
namespace booldog {
	namespace typedefs {
    namespace threading {
      typedef void (*onthread)(void* arglist);
    }
	}
	namespace threading	{
    struct thread {
#ifdef __WINDOWS__
      uintptr_t handle;
#else
      pthread_t handle;
#endif
      void* arglist;
      ::booldog::typedefs::threading::onthread onthread;
    };
#ifdef __WINDOWS__
    static void __cdecl onthread_detached(void* param) {
      thread* thr = (thread*)param;
      thr->onthread(thr->arglist);      
    }
    static unsigned __stdcall onthread_attached(void* param) {
      thread* thr = (thread*)param;
      thr->onthread(thr->arglist);
      return 0;
    }
#else
    static void* onthread_detached(void* param) {
      pthread_detach(pthread_self());
      thread* thr = (thread*)param;
      thr->onthread(thr->arglist);
      return 0;
    }
    static void* onthread_attached(void* param) {
      thread* thr = (thread*)param;
      thr->onthread(thr->arglist);
      return 0;
    }
#endif
    inline int create_detached(thread* thr, ::booldog::typedefs::threading::onthread onthread, unsigned stack_size, void* arglist) {
#ifdef __WINDOWS__
      thr->onthread = onthread;
      thr->arglist = arglist;
			thr->handle = _beginthread(onthread_detached, stack_size, thr);
			if(thr->handle == 0)
			{ 
        //TODO
        int error = errno;
        error = error;
        return error;
			}
#else
			pthread_attr_t pthread_attr;		
			int result = pthread_attr_init(&pthread_attr);		
			if(result != 0)
			{
        //TODO
        int error = result;
        return error;
			}
			if(stack_size != 0)
			{
#ifdef PTHREAD_STACK_MIN
				if(stack_size < PTHREAD_STACK_MIN)
					stack_size = PTHREAD_STACK_MIN;
				else
#endif
				{
					long sz = sysconf(_SC_PAGESIZE);
					if(stack_size % sz)
						stack_size = sz * (stack_size / sz) + sz;
				}
				result = pthread_attr_setstacksize(&pthread_attr, stack_size);							
				if(result != 0)
				{
					pthread_attr_destroy(&pthread_attr);
					//TODO
          int error = result;
          return error;
				}
			}
			result = pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED);
			if(result != 0)
			{				
				pthread_attr_destroy(&pthread_attr);
				//TODO
        int error = result;
        return error;
			}
			int numberOfProcessors = sysconf(_SC_NPROCESSORS_ONLN);
			if(numberOfProcessors > BOO_THREAD_CPU_MAX)
				numberOfProcessors = BOO_THREAD_CPU_MAX;
      cpu_set_t cpus;
			CPU_ZERO(&cpus);
			for(int i = BOO_THREAD_CPU_MIN;i < numberOfProcessors; ++i)
			{
				if(i != BOO_THREAD_EXCLUDE_CPU)
					CPU_SET(i, &cpus);
			}
			pthread_attr_setaffinity_np(&pthread_attr, sizeof(cpu_set_t), &cpus);
      thr->onthread = onthread;
      thr->arglist = arglist;
			result = pthread_create(&thr->handle, &pthread_attr, onthread_detached, (void*)thr);
			if(result != 0)
			{
				pthread_attr_destroy(&pthread_attr);
				int error = result;
        return error;
			}
      pthread_attr_destroy(&pthread_attr);
#endif
      return 0;
    }
    static int create_attached(thread* thr, ::booldog::typedefs::threading::onthread onthread, unsigned stack_size, void* arglist) {
#ifdef __WINDOWS__
			thr->onthread = onthread;
      thr->arglist = arglist;
			thr->handle = _beginthreadex(0, (unsigned)stack_size, onthread_attached, thr, 0, 0);
			if(thr->handle == 0)
			{ 
        //TODO
        int error = errno;
        error = error;
        return error;
			}
#else
			pthread_attr_t pthread_attr;		
			int result = pthread_attr_init(&pthread_attr);		
			if(result != 0)
			{
        //TODO
        int error = result;
        return error;
			}
			if(stack_size != 0)
			{
#ifdef PTHREAD_STACK_MIN
				if(stack_size < PTHREAD_STACK_MIN)
					stack_size = PTHREAD_STACK_MIN;
				else
#endif
				{
					long sz = sysconf(_SC_PAGESIZE);
					if(stack_size % sz)
						stack_size = sz * (stack_size / sz) + sz;
				}
				result = pthread_attr_setstacksize(&pthread_attr, stack_size);							
				if(result != 0)
				{
					pthread_attr_destroy(&pthread_attr);
					//TODO
          int error = result;
          return error;
				}
			}
			int numberOfProcessors = sysconf(_SC_NPROCESSORS_ONLN);
			if(numberOfProcessors > BOO_THREAD_CPU_MAX)
				numberOfProcessors = BOO_THREAD_CPU_MAX;
      cpu_set_t cpus;
			CPU_ZERO(&cpus);
			for(int i = BOO_THREAD_CPU_MIN;i < numberOfProcessors; ++i)
			{
				if(i != BOO_THREAD_EXCLUDE_CPU)
					CPU_SET(i, &cpus);
			}
			pthread_attr_setaffinity_np(&pthread_attr, sizeof(cpu_set_t), &cpus);

      thr->onthread = onthread;
      thr->arglist = arglist;
			result = pthread_create(&thr->handle, &pthread_attr, onthread_attached, (void*)thr);
			if(result != 0)
			{
				pthread_attr_destroy(&pthread_attr);
				int error = result;
        return error;
			}
      pthread_attr_destroy(&pthread_attr);
#endif
      return 0;
    }
    static int attached_join(thread* thr) {
#ifdef __WINDOWS__
      DWORD error = WaitForSingleObject((HANDLE)thr->handle, INFINITE);
      if(error == WAIT_FAILED) {
        //TODO
        return GetLastError();
      }
      if(CloseHandle((HANDLE)thr->handle) == 0) {
        //TODO
        return GetLastError();
      }
#else
      int error = pthread_join(thr->handle, 0);
      if(error != 0) {
        //TODO
        return error;
      }
#endif
      return 0;
    }
	}
}
#ifndef BOOLDOG_THREAD_ATTACHED
typedef ::booldog::threading::thread BOOLDOG_THREAD;
#define BOOLDOG_THREAD_ATTACHED(thread, onthread, stack_size, arglist) ::booldog::threading::create_attached(thread, onthread, stack_size, arglist)
#define BOOLDOG_THREAD_DETACHED(thread, onthread, stack_size, arglist) ::booldog::threading::create_detached(thread, onthread, stack_size, arglist)
#define BOOLDOG_THREAD_ATTACHED_JOIN(thread) ::booldog::threading::attached_join(thread)
#endif
#endif
