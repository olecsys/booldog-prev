#ifndef BOO_THREAD_H
#define BOO_THREAD_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_interlocked.h)
#include BOOLDOG_HEADER(boo_threading_utils.h)
#include BOOLDOG_HEADER(boo_result.h)
#include BOOLDOG_HEADER(boo_error.h)

#ifdef __WINDOWS__
#include <process.h>
#else
#include <pthread.h>
#endif
namespace booldog
{
	namespace enums
	{
		namespace threading
		{
			enum state
			{
				state_pending_in_start ,
				state_start ,
				state_stop ,
				state_pending_in_stop
			};
		};
	};
	namespace threading
	{
		class thread;
	};
	namespace events
	{
		namespace typedefs
		{
			typedef void (*onthreadstarted)( ::booldog::threading::thread* thread );
			typedef void (*onthreadstopped)( ::booldog::threading::thread* thread );
			typedef void (*onthreadprocedure)( ::booldog::threading::thread* thread );
		};
	};
	namespace threading
	{
		class thread
		{
			::booldog::interlocked::atomic _state;
			booldog::allocator* _allocator;
			void* _udata;
			::booldog::events::typedefs::onthreadstarted _onthreadstarted;
			::booldog::events::typedefs::onthreadstopped _onthreadstopped;
			::booldog::events::typedefs::onthreadprocedure _onthreadprocedure;
#ifdef __WINDOWS__
			HANDLE _handle;
#else
			pthread_t _handle;
#endif
		public:
			thread( booldog::allocator* allocator )
				: _onthreadstarted( 0 ) , _onthreadstopped( 0 ) , _udata( 0 ) , _allocator( allocator ) , _state( ::booldog::enums::threading::state_stop )
			{
			};
			void* udata( void )
			{
				return _udata;
			};
			bool pending_in_stop( void )
			{
				return booldog::interlocked::compare_exchange( &_state , 0 , 0 ) == ::booldog::enums::threading::state_pending_in_stop;
			};
		private:
#ifdef __WINDOWS__
			static unsigned __stdcall func( void* param )
#else
			static void* func( void* param )
#endif
			{
#ifndef __WINDOWS__
				pthread_detach( pthread_self() );
#endif
				::booldog::threading::thread* thr = (::booldog::threading::thread*)param;
				::booldog::interlocked::exchange( &thr->_state , ::booldog::enums::threading::state_start );
				if( thr->_onthreadstarted )
					thr->_onthreadstarted( thr );
				thr->_onthreadprocedure( thr );
#ifdef __WINDOWS__
				CloseHandle( thr->_handle ); 
#endif
				if( thr->_onthreadstopped )
					thr->_onthreadstopped( thr );
				::booldog::interlocked::exchange( &thr->_state , ::booldog::enums::threading::state_stop );
				return 0;
			};
		public:
			booinline static ::booldog::threading::thread* create( ::booldog::result* pres , booldog::allocator* allocator
				, size_t stack_size , ::booldog::events::typedefs::onthreadstarted onthreadstarted 
				, ::booldog::events::typedefs::onthreadstopped onthreadstopped
				, ::booldog::events::typedefs::onthreadprocedure onthreadprocedure , void* udata
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );

				::booldog::threading::thread* thr = allocator->create< ::booldog::threading::thread >( allocator , debuginfo );
				if( thr )
				{
					::booldog::interlocked::exchange( &thr->_state , ::booldog::enums::threading::state_pending_in_start );
					thr->_udata = udata;
					thr->_onthreadstarted = onthreadstarted;
					thr->_onthreadstopped = onthreadstopped;
					thr->_onthreadprocedure = onthreadprocedure;
#ifdef __WINDOWS__
					thr->_handle = (HANDLE)_beginthreadex( 0 , (unsigned)stack_size , ::booldog::threading::thread::func , thr , 0 , 0 );
					if( thr->_handle == 0 )
					{
						res->seterrno();
						goto goto_destroy;
					}
#else
					pthread_attr_t pthread_attr;		
					int result = pthread_attr_init( &pthread_attr );		
					if( result != 0 )
					{
						res->setpthreaderror( result );
						goto goto_destroy;
					}
					result = pthread_attr_setstacksize( &pthread_attr , stack_size );
					if( result != 0 )
					{
						res->setpthreaderror( result );
						pthread_attr_destroy( &pthread_attr );
						goto goto_destroy;
					}
					result = pthread_attr_setdetachstate( &pthread_attr , PTHREAD_CREATE_DETACHED );
					if( result != 0 )
					{
						res->setpthreaderror( result );
						pthread_attr_destroy( &pthread_attr );
						goto goto_destroy;
					}
					result = pthread_create( &thr->_handle , &pthread_attr , func , (void*)thr );
					if( result != 0 )
					{
						res->setpthreaderror( result );
						pthread_attr_destroy( &pthread_attr );
						goto goto_destroy;
					}
#endif
					goto goto_return;
goto_destroy:
					allocator->destroy< ::booldog::threading::thread >( thr );
					thr = 0;
				}
				else
					res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
goto_return:
				return thr;
			};
			booinline static void wait_for_start( ::booldog::threading::thread* thr )
			{
				if( booldog::interlocked::compare_exchange( &thr->_state , 0 , 0 ) == ::booldog::enums::threading::state_pending_in_start )
				{
					booldog::byte tries = 0;
					while( booldog::interlocked::compare_exchange( &thr->_state , 0 , 0 ) != ::booldog::enums::threading::state_start )
					{
						tries++;
						if( tries == 5 )
						{
							::booldog::threading::sleep( 1 );
							tries = 0;
						}
					}
				}
			};
			booinline static void stop( ::booldog::threading::thread* thr )
			{
				::booldog::threading::thread::wait_for_start( thr );
				booldog::interlocked::compare_exchange( &thr->_state , ::booldog::enums::threading::state_pending_in_stop
					, ::booldog::enums::threading::state_start );
			};
			booinline static void wait_for_stop( ::booldog::threading::thread* thr )
			{
				booldog::byte tries = 0;
				while( booldog::interlocked::compare_exchange( &thr->_state , 0 , 0 ) != ::booldog::enums::threading::state_stop )
				{
					tries++;
					if( tries == 5 )
					{
						::booldog::threading::sleep( 1 );
						tries = 0;
					}
				}
			};
			booinline static void destroy( ::booldog::threading::thread* thr )
			{
				::booldog::threading::thread::wait_for_stop( thr );
				thr->_allocator->destroy< ::booldog::threading::thread >( thr );
			};
		};
	};
};
#endif