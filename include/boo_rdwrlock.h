#ifndef BOO_RDWRLOCK_H
#define BOO_RDWRLOCK_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_interlocked.h"
#include "boo_threading_utils.h"
#include "boo_debug_info.h"
namespace booldog
{
	namespace threading
	{
		class rdwrlock
		{
		public:
			static const ::booldog::int32 WRITER_BIT = 1L << ( sizeof( ::booldog::int32 ) * 8 - 2 );
			booldog::interlocked::atomic _writer_readers;
			booldog::interlocked::atomic _writer_recursion;
			booldog::interlocked::atomic _writer_thread;
		public:
			rdwrlock( void )
				: _writer_readers( 0 ) , _writer_recursion( 0 ) , _writer_thread( 0 )
			{
			};
			~rdwrlock( void )
			{
			};
			void rlock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{				
				debuginfo = debuginfo;
				if( ::booldog::interlocked::increment( &_writer_readers ) >= WRITER_BIT )
				{
					::booldog::pid_t tid = ::booldog::threading::threadid();
					if( (::booldog::pid_t)::booldog::interlocked::compare_exchange( &_writer_thread , 0 , 0 ) != tid )
					{
						::booldog::byte tries = 0;
						while( booldog::interlocked::compare_exchange( &_writer_readers , 0 , 0 ) >= WRITER_BIT )
						{
							tries++;
							if( tries == 5 )
							{
								debuginfo_macros_sleep( 49 );
								::booldog::threading::sleep( 1 );
								debuginfo_macros_statement( 52 );
								tries = 0;
							}
						}
					}
				}
			};
			bool try_wlock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				booldog::pid_t tid = ::booldog::threading::threadid();
				if( (::booldog::pid_t)::booldog::interlocked::compare_exchange( &_writer_thread , 0 , 0 ) != tid )
				{
					if( booldog::interlocked::compare_exchange( &_writer_readers , WRITER_BIT , 0 ) != 0 )
						return false;
				}
				else
				{
					::booldog::interlocked::increment( &_writer_recursion );
					return true;
				}
				::booldog::interlocked::increment( &_writer_recursion );
				::booldog::interlocked::exchange( &_writer_thread , tid );
				return true;
			};
			void wlock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				booldog::pid_t tid = ::booldog::threading::threadid();
				if( (::booldog::pid_t)::booldog::interlocked::compare_exchange( &_writer_thread , 0 , 0 ) == tid )
				{
					::booldog::interlocked::increment( &_writer_recursion );
					return;
				}
				else
				{
					booldog::byte tries = 0;
					while( booldog::interlocked::compare_exchange( &_writer_readers , WRITER_BIT , 0 ) != 0 )
					{
						tries++;
						if( tries == 5 )
						{
							debuginfo_macros_sleep( 50 );
							::booldog::threading::sleep( 1 );
							debuginfo_macros_statement( 51 );
							tries = 0;
						}
					}
				}
				::booldog::interlocked::increment( &_writer_recursion );
				::booldog::interlocked::exchange( &_writer_thread , tid );
			};
			void runlock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				booldog::interlocked::decrement( &_writer_readers );
			};
			void wunlock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				::booldog::pid_t tid = ::booldog::threading::threadid();
				if( (::booldog::pid_t)::booldog::interlocked::compare_exchange( &_writer_thread , 0 , 0 ) == tid )
				{
					if( booldog::interlocked::decrement( &_writer_recursion ) == 0 )
					{
						::booldog::interlocked::exchange_add( &_writer_readers , -WRITER_BIT );
						::booldog::interlocked::compare_exchange( &_writer_thread , 0 , tid );
					}
				}
			};		
		};
	};
};
#endif