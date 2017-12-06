#ifndef BOO_THREADING_EVENT_H
#define BOO_THREADING_EVENT_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_threading_utils.h"
#include "boo_result.h"
#include "boo_error.h"

#ifdef __WINDOWS__
#include <process.h>
#else
#include <pthread.h>
#include <stdio.h>
#endif
namespace booldog
{
	namespace threading
	{
		class event
		{
#ifdef __WINDOWS__
			HANDLE _manual_reset_event;
			HANDLE _auto_reset_event;
#else
			pthread_mutex_t _mutex;//don't touch, address must be aligned by 4
			pthread_cond_t _cond;//don't touch, address must be aligned by 4
			int _clockid;
			int _waiters;
			bool _isset;
			bool _wakeall;
			bool _mutex_inited;
			bool _cond_inited;
#endif
		public:
			event( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				:
#ifdef __WINDOWS__
      _manual_reset_event(0), _auto_reset_event(0)
#else
      _clockid(CLOCK_REALTIME), _waiters(0), _isset(false), _wakeall(false), _mutex_inited(false), _cond_inited(false)
#endif
			{
				debuginfo = debuginfo;
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
				_manual_reset_event = CreateEventA( 0 , TRUE , FALSE , 0 );
				if( _manual_reset_event == 0 )
					goto goto_error;
				else
				{
					_auto_reset_event = CreateEventA( 0 , FALSE , FALSE , 0 );
					if( _auto_reset_event == 0 )
						goto goto_error;
				}
#else
				int result = pthread_mutex_init( &_mutex , 0 );
				if( result == 0 )
				{
					_mutex_inited = true;
					pthread_condattr_t condattr;
					result = pthread_condattr_init( &condattr );
					if( result == 0 )
					{
						_clockid = CLOCK_MONOTONIC;
						result = pthread_condattr_setclock( &condattr , _clockid );
						if( result != 0 )
						{
							_clockid = CLOCK_REALTIME;
							result = pthread_condattr_setclock( &condattr , _clockid );
						}
						if( result == 0 )
							result = pthread_cond_init( &_cond , &condattr );
						else
							pthread_condattr_destroy( &condattr );
						pthread_condattr_destroy( &condattr );
					}
					if( result != 0 )
						result = pthread_cond_init( &_cond , 0 );
					if( result == 0 )
						_cond_inited = true;
					else
						goto goto_error;
				}
				else
					goto goto_error;
#endif
				return;
goto_error:
#ifdef __WINDOWS__
				res->GetLastError();
#else
				res->setpthreaderror( result );
#endif
			};
			~event()
			{
#ifdef __WINDOWS__
				if(_auto_reset_event)
					CloseHandle(_auto_reset_event);
				if(_manual_reset_event)
					CloseHandle(_manual_reset_event);
#else
				if( _mutex_inited )
					pthread_mutex_destroy( &_mutex );
				if( _cond_inited )
					pthread_cond_destroy( &_cond );
#endif
			};
			bool sleep( ::booldog::result_bool* pres , ::booldog::uint32 timeout_in_ms 
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result_bool locres;
				BOOINIT_RESULT( ::booldog::result_bool );
#ifdef __WINDOWS__
				debuginfo_macros_sleep( 53 );
				HANDLE handles[] = { _manual_reset_event , _auto_reset_event };
				DWORD result = WaitForMultipleObjects( 2 , handles , FALSE , timeout_in_ms );
				debuginfo_macros_statement( 54 );
				if( result == WAIT_FAILED )
					res->GetLastError();
				else if( result == WAIT_TIMEOUT )
					res->bres = false;
				else
					res->bres = true;
#else
				struct timespec abstime;
				clock_gettime( _clockid , &abstime );
				abstime.tv_sec += ( timeout_in_ms / 1000 );
				abstime.tv_nsec += ( timeout_in_ms % 1000 ) * 1000000; /* nanoseconds */
				if( abstime.tv_nsec > 999999999 )
				{
					abstime.tv_sec += 1;
					abstime.tv_nsec -= 1000000000;
				}
				int result = 0;
				debuginfo_macros_sleep( 55 );
				pthread_mutex_lock( &_mutex );
				debuginfo_macros_statement( 62 );
				while( _isset == false && _wakeall == false && result != ETIMEDOUT )
				{
					_waiters++;
					debuginfo_macros_sleep( 56 );
					result = pthread_cond_timedwait( &_cond , &_mutex , &abstime );
					debuginfo_macros_statement( 63 );
					_waiters--;
				}
				if( result == 0 )
				{
					_isset = false;
					res->bres = true;
				}
				else if( result == ETIMEDOUT )
					res->bres = false;
				else
					res->setpthreaderror( result );
				pthread_mutex_unlock( &_mutex );
#endif
				return res->succeeded();
			};
			bool sleep( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
				HANDLE handles[] = { _manual_reset_event , _auto_reset_event };
				debuginfo_macros_sleep( 57 );
				if( WaitForMultipleObjects( 2 , handles , FALSE , INFINITE ) == WAIT_FAILED )
					res->GetLastError();
				debuginfo_macros_statement( 64 );
#else				
				int result = 0;
				debuginfo_macros_sleep( 58 );
				pthread_mutex_lock( &_mutex );
				debuginfo_macros_statement( 65 );
				while( _isset == false && _wakeall == false )
				{
					_waiters++;
					debuginfo_macros_sleep( 59 );
					result = pthread_cond_wait( &_cond , &_mutex );
					debuginfo_macros_statement( 66 );
					_waiters--;
					if( result != 0 )
					{
						res->setpthreaderror( result );
						break;
					}
				}
				if( result == 0 )
					_isset = false;
				pthread_mutex_unlock( &_mutex );
#endif
				return res->succeeded();
			};
			bool wake_all( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
				debuginfo = debuginfo;
				if( SetEvent( _manual_reset_event ) == 0 )
					res->GetLastError();
#else
				debuginfo_macros_sleep( 69 );
				pthread_mutex_lock( &_mutex );
				debuginfo_macros_statement( 70 );
				if( _wakeall == false && _waiters )
				{
					int result = pthread_cond_broadcast( &_cond );
					if( result == 0 )
						_wakeall = true;
					else
						res->setpthreaderror( result );
				}
				else
					_wakeall = true;
				pthread_mutex_unlock( &_mutex );
#endif
				return res->succeeded();
			};
			bool wake( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
				debuginfo = debuginfo;
				if( SetEvent( _auto_reset_event ) == 0 )
					res->GetLastError();
#else
				debuginfo_macros_sleep( 60 );
				pthread_mutex_lock( &_mutex );
				debuginfo_macros_statement( 67 );
				if( _isset == false && _waiters )
				{
					int result = pthread_cond_signal( &_cond );
					if( result == 0 )
						_isset = true;
					else
						res->setpthreaderror( result );
				}
				else
					_isset = true;
				pthread_mutex_unlock( &_mutex );
#endif
				return res->succeeded();
			};
			bool reset( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
				debuginfo = debuginfo;
				if( ResetEvent( _manual_reset_event ) == 0 )
					res->GetLastError();
#else
				debuginfo_macros_sleep( 61 );
				pthread_mutex_lock( &_mutex );
				debuginfo_macros_statement( 68 );
				_wakeall = false;
				pthread_mutex_unlock( &_mutex );
#endif
				return res->succeeded();
			};
		};
	};
};
#endif
