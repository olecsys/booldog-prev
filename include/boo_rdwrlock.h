#ifndef BOO_RDWRLOCK_H
#define BOO_RDWRLOCK_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_interlocked.h)
#include BOOLDOG_HEADER(boo_threading_utils.h)
#include BOOLDOG_HEADER(boo_debug_info.h)
namespace booldog
{
	namespace threading
	{
		class rdwrlock
		{
		private:
			static const ::booldog::int32 WRITER_BIT = 1L << ( sizeof( ::booldog::int32 ) * 8 - 2 );
			booldog::interlocked::atomic _writer_readers;
			booldog::interlocked::atomic _writer_recursion;
			booldog::pid_t _writer_thread;
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
				if( booldog::interlocked::increment( &_writer_readers ) >= WRITER_BIT )
				{
					if( _writer_thread != ::booldog::threading::threadid() )
					{
						booldog::byte tries = 0;
						while( booldog::interlocked::compare_exchange( &_writer_readers , 0 , 0 ) >= WRITER_BIT )
						{
							tries++;
							if( tries == 5 )
							{
								::booldog::threading::sleep( 1 );
								tries = 0;
							}
						}
					}
				}
			};
			bool try_wlock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				if( booldog::interlocked::compare_exchange( &_writer_readers , WRITER_BIT , 0 ) == 0 )
				{
					booldog::interlocked::increment( &_writer_recursion );
					_writer_thread = ::booldog::threading::threadid();
					return true;
				}
				return false;
			};
			void wlock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				booldog::pid_t tid = ::booldog::threading::threadid();
				booldog::byte tries = 0;
				while( booldog::interlocked::compare_exchange( &_writer_readers , WRITER_BIT , 0 ) != 0 )
				{
					if( _writer_thread != tid )
					{
						tries++;
						if( tries == 5 )
						{
							::booldog::threading::sleep( 1 );
							tries = 0;
						}
					}
					else
						break;
				}
				booldog::interlocked::increment( &_writer_recursion );
				_writer_thread = tid;
			};
			void runlock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				booldog::interlocked::decrement( &_writer_readers );
			};
			void wunlock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				if( _writer_thread == ::booldog::threading::threadid() )
				{
					if( booldog::interlocked::decrement( &_writer_recursion ) == 0 )
					{
						_writer_thread = 0;
						booldog::interlocked::exchange_add( &_writer_readers , -WRITER_BIT );
					}
				}
			};		
		};
	};
};
#endif