#ifndef BOO_FPS_COUNTER_H
#define BOO_FPS_COUNTER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_types.h)
namespace booldog
{
	namespace typedefs
	{
		typedef ::booldog::uint32 (*tickcount)( void );
	};
};
namespace booldog
{
	namespace counters
	{
		struct fps
		{
			::booldog::typedefs::tickcount _tickcount;
			::booldog::uint32 _frames_count;
			::booldog::uint32 _start_time;
			::booldog::uint32 _last_frame_time;
			fps( ::booldog::typedefs::tickcount ptickcount )
				: _tickcount( ptickcount )
			{
				_last_frame_time = 0;
				_frames_count = 0;
				_start_time = 0;
			};
			::booldog::uint32 runtime( void )
			{
				if( _start_time == 0 )
					return 0;
				else
				{
					::booldog::uint32 now = _tickcount();
					if( _start_time > now )
						_start_time = now;
					return now - _start_time;
				}
			};
			void increment( void )
			{
				if( _frames_count == 0 )
					_start_time = _tickcount();
				_frames_count++;
			};
			double result( void )
			{
				::booldog::uint32 now = _tickcount();
				if( _start_time > now )
					_start_time = now;
				::booldog::uint32 difference = now - _start_time;
				if( difference )
					return ( (double)_frames_count / ( (double)difference / (double)( 1000ULL ) ) );
				else
					return 25;
			};
			void reset( void )
			{
				_frames_count = 0;
				_start_time = _tickcount();
			};
			void clear( void )
			{
				_last_frame_time = 0;
				_frames_count = 0;
				_start_time = 0;
			};
		};
	};
};
#endif