#ifndef BOO_TIME_UTILS_H
#define BOO_TIME_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_result.h)
#include BOOLDOG_HEADER(boo_allocator.h)
#include BOOLDOG_HEADER(boo_types.h)
#include BOOLDOG_HEADER(boo_interlocked.h)
#include BOOLDOG_HEADER(boo_threading_utils.h)
#include BOOLDOG_HEADER(boo_string_utils.h)
#include <time.h>
namespace booldog
{	
	namespace utils
	{
		namespace time
		{
			booinline int tz( void )
			{
				static ::booldog::interlocked::atomic bootimezone = ::booldog::interlocked::max;
				::booldog::interlocked::atomic_return res = ::booldog::interlocked::compare_exchange( &bootimezone
					, ::booldog::interlocked::max - 1 , ::booldog::interlocked::max );
				if( res == ::booldog::interlocked::max )
				{
#ifdef __UNIX__
					::tzset();
#else
					::_tzset();
					long timezone = 0;
				    _get_timezone( &timezone );
#endif
					::booldog::interlocked::compare_exchange( &bootimezone , timezone , ::booldog::interlocked::max - 1 );
				}
				else if( res == ::booldog::interlocked::max - 1 )
				{
					::booldog::byte tries = 0;
					while( ::booldog::interlocked::compare_exchange( &bootimezone , 0 , 0 ) == ::booldog::interlocked::max - 1 )
					{
						tries++;
						if( tries == 5 )
						{
							::booldog::threading::sleep( 1 );
							tries = 0;
						}
					}
				}
				else
					return (int)res;
				return (int)::booldog::interlocked::compare_exchange( &bootimezone , 0 , 0 );
			};
			booinline ::booldog::uint32 days_in_month( ::booldog::uint32 month , ::booldog::uint32 year )
			{	    
				return ( 30 + ( ( ( month & 9 ) == 8 ) || ( ( month & 9 ) == 1 ) ) - ( month == 2 ) - ( !( ( ( year % 4 ) == 0 ) 
					&& ( ( ( year % 100 ) != 0 ) || ( ( year % 400 ) == 0 ) ) ) && ( month == 2 ) ) );
			};
			booinline ::booldog::uint32 days_in_year( ::booldog::uint32 year )
			{
				::booldog::uint32 days = 0;
				for( ::booldog::uint32 month = 1 ; month < 13 ; month++ )
					days += ::booldog::utils::time::days_in_month( month , year );
				return days;
			};
			namespace posix
			{
				booinline ::booldog::uint64 tolocal( ::booldog::uint64 timems )
				{
					return timems - ( ::booldog::utils::time::tz() * 1000000LL );
				};
				booinline ::booldog::uint64 toutc( ::booldog::uint64 timems )
				{
					return timems + ( ::booldog::utils::time::tz() * 1000000LL );
				};
				booinline ::booldog::uint64 now_as_utc( void )
				{	
	#ifdef __WINDOWS__
					::booldog::uint64 time = 0;
					FILETIME now;
					GetSystemTimeAsFileTime( (LPFILETIME)&now );
					time = now.dwHighDateTime;
					time <<= 32;
					time |= now.dwLowDateTime;
					time /= 10;
					time -= 11644473600000000LL;//DELTA_EPOCH_IN_USEC
					return time;
	#else
					struct timespec ts;
					clock_gettime( CLOCK_REALTIME , &ts );
					return ts.tv_sec * 1000000LL + ( ts.tv_nsec / 1000ULL );
	#endif
				};
				booinline void date( ::booldog::uint64 time , ::booldog::uint32& year , ::booldog::uint32& month 
					, ::booldog::uint32& day_of_month )
				{
					day_of_month = (::booldog::uint32)( ( time / 1000000ULL ) / ( 60ULL * 60ULL * 24ULL ) );
					if( day_of_month >= 2 * 365 )
					{
						day_of_month -= 2 * 365;
						::booldog::uint32 leapyears = day_of_month / ( 3 * 365 + 366 );
						year = 1972 + leapyears * 4;
						day_of_month -= leapyears * ( 3 * 365 + 366 );
						if( day_of_month >= 366 )
						{
							day_of_month -= 366;
							year++;
						}
					}
					else
						year = 1970;
					year += day_of_month / 365;
					day_of_month %= 365;
					::booldog::uint32 days_in_month_in_year = 0;
					month = 1;
					for( ; month < 13 ; month++ )
					{
						days_in_month_in_year = ::booldog::utils::time::days_in_month( month , year );
						if( days_in_month_in_year > day_of_month )
							break;
						else
							day_of_month -= days_in_month_in_year;
					}
					day_of_month++;
				};
				booinline ::booldog::uint32 day_of_week( ::booldog::uint64 time )
				{
					return ( 4 + (::booldog::uint32)( ( time / 1000000ULL ) / ( 60ULL * 60ULL * 24ULL ) ) ) % 7;
				};
				booinline ::booldog::uint32 month( ::booldog::uint64 time )
				{
					::booldog::uint32 year = 0 , month = 0 , day_of_month = 0;
					::booldog::utils::time::posix::date( time , year , month , day_of_month );
					return month;
				};
				booinline ::booldog::uint32 day_of_month( ::booldog::uint64 time )
				{
					::booldog::uint32 year = 0 , month = 0 , day_of_month = 0;
					::booldog::utils::time::posix::date( time , year , month , day_of_month );
					return day_of_month;
				};
				booinline ::booldog::uint32 year( ::booldog::uint64 time )
				{
					::booldog::uint32 year = 0 , month = 0 , day_of_month = 0;
					::booldog::utils::time::posix::date( time , year , month , day_of_month );
					return year;
				};
				booinline void time( ::booldog::uint64 time , ::booldog::uint32& hour , ::booldog::uint32& minute
					, ::booldog::uint32& second , ::booldog::uint32& milliseconds )
				{
					::booldog::uint32 days = (::booldog::uint32)( ( time / 1000000ULL ) / ( 60ULL * 60ULL * 24ULL ) );
					::booldog::uint64 time_offset00 = days * 60ULL * 60ULL * 24ULL * 1000000ULL;

					time_offset00 = time - time_offset00;
					hour = (::booldog::uint32)( time_offset00 / ( 60ULL * 60ULL * 1000000ULL ) );
					time_offset00 -= hour * 60ULL * 60ULL * 1000000ULL;
					minute = (::booldog::uint32)( time_offset00 / ( 60ULL * 1000000ULL ) );
					time_offset00 -= minute * 60ULL * 1000000ULL;
					second = (::booldog::uint32)( time_offset00 / 1000000ULL );
					time_offset00 -= second * 1000000ULL;
					milliseconds = (::booldog::uint32)( time_offset00 / 1000ULL );
				};
				booinline ::booldog::uint32 hour( ::booldog::uint64 time )
				{
					::booldog::uint32 hour = 0 , minute = 0 , second = 0 , millisecond = 0;
					::booldog::utils::time::posix::time( time , hour , minute , second , millisecond );
					return hour;
				};
				booinline ::booldog::uint32 minute( ::booldog::uint64 time )
				{
					::booldog::uint32 hour = 0 , minute = 0 , second = 0 , millisecond = 0;
					::booldog::utils::time::posix::time( time , hour , minute , second , millisecond );
					return minute;
				};
				booinline ::booldog::uint32 second( ::booldog::uint64 time )
				{
					::booldog::uint32 hour = 0 , minute = 0 , second = 0 , millisecond = 0;
					::booldog::utils::time::posix::time( time , hour , minute , second , millisecond );
					return second;
				};
				booinline ::booldog::uint32 millisecond( ::booldog::uint64 time )
				{
					::booldog::uint32 hour = 0 , minute = 0 , second = 0 , millisecond = 0;
					::booldog::utils::time::posix::time( time , hour , minute , second , millisecond );
					return millisecond;
				};
				booinline ::booldog::uint64 generate( ::booldog::uint32 millisecond , ::booldog::uint32 second 
					, ::booldog::uint32 minute , ::booldog::uint32 hour , ::booldog::uint32 day_of_month 
					, ::booldog::uint32 month , ::booldog::uint32 year )
				{
					if( year >= 1970 )
					{
						::booldog::uint64 time = ( day_of_month - 1 ) * 24ULL * 3600ULL * 1000000ULL 
							+ hour * 60ULL * 60ULL * 1000000ULL + minute * 60ULL * 1000000ULL
							+ second * 1000000ULL + millisecond * 1000ULL;
						month--;
						for( ; month > 0 ; month-- )
							time += ::booldog::utils::time::days_in_month( month , year ) * 24ULL * 3600ULL * 1000000ULL;
						year -= 1970;
						if( year >= 2 )
						{
							day_of_month = 2 * 365;
							::booldog::uint32 quarter_years = ( year - 2 ) / 4;
							day_of_month += quarter_years * ( 3 * 365 + 366 );
							year -= 2 + 4 * quarter_years;
							if( year > 0 )
								day_of_month += ( 366 + ( year - 1 ) * 365 );
						}
						else
							day_of_month = year * 365ULL;
						time += day_of_month * 24ULL * 3600ULL * 1000000ULL;
						return time;
					}
					return 0;
				};
				booinline ::booldog::uint64 add_months( ::booldog::uint64 time , ::booldog::uint32 added )
				{
					::booldog::uint32 year = 0 , month = 0 , day_of_month = 0;
					::booldog::utils::time::posix::date( time , year , month , day_of_month );

					year += ( month + added - 1 ) / 12;
					month += added % 12;

					::booldog::uint32 hour = 0 , minute = 0 , second = 0 , millisecond = 0;
					::booldog::utils::time::posix::time( time , hour , minute , second , millisecond );

					return ::booldog::utils::time::posix::generate( millisecond , second , minute , hour , day_of_month 
						, month , year );
				};
				booinline ::booldog::uint64 sub_months( ::booldog::uint64 time , ::booldog::uint32 added )
				{
					::booldog::uint32 year = 0 , month = 0 , day_of_month = 0;
					::booldog::utils::time::posix::date( time , year , month , day_of_month );

					year -= added / 12;

					added %= 12;
					if( added >= month )
					{
						month -= added - 12;
						year--;
					}
					else
						month -= added;

					::booldog::uint32 hour = 0 , minute = 0 , second = 0 , millisecond = 0;
					::booldog::utils::time::posix::time( time , hour , minute , second , millisecond );

					return ::booldog::utils::time::posix::generate( millisecond , second , minute , hour , day_of_month 
						, month , year );
				};
				booinline ::booldog::uint64 add_years( ::booldog::uint64 time , ::booldog::uint32 added )
				{
					::booldog::uint32 year = 0 , month = 0 , day_of_month = 0;
					::booldog::utils::time::posix::date( time , year , month , day_of_month );
					year += added;
					::booldog::uint32 hour = 0 , minute = 0 , second = 0 , millisecond = 0;
					::booldog::utils::time::posix::time( time , hour , minute , second , millisecond );
					return ::booldog::utils::time::posix::generate( millisecond , second , minute , hour , day_of_month 
						, month , year );
				};
				booinline ::booldog::uint64 sub_years( ::booldog::uint64 time , ::booldog::uint32 added )
				{
					::booldog::uint32 year = 0 , month = 0 , day_of_month = 0;
					::booldog::utils::time::posix::date( time , year , month , day_of_month );
					year -= added;
					::booldog::uint32 hour = 0 , minute = 0 , second = 0 , millisecond = 0;
					::booldog::utils::time::posix::time( time , hour , minute , second , millisecond );
					return ::booldog::utils::time::posix::generate( millisecond , second , minute , hour , day_of_month 
						, month , year );
				};
				booinline ::booldog::uint64 add_days( ::booldog::uint64 time , ::booldog::uint32 added )
				{
					return time + added * 24ULL * 3600ULL * 1000000ULL;
				};
				booinline ::booldog::uint64 sub_days( ::booldog::uint64 time , ::booldog::uint32 added )
				{
					return time - added * 24ULL * 3600ULL * 1000000ULL;
				};
				booinline ::booldog::uint64 add_hours( ::booldog::uint64 time , ::booldog::uint32 added )
				{
					return time + added * 3600ULL * 1000000ULL;
				};
				booinline ::booldog::uint64 sub_hours( ::booldog::uint64 time , ::booldog::uint32 added )
				{
					return time - added * 3600ULL * 1000000ULL;
				};
				booinline ::booldog::uint64 add_minutes( ::booldog::uint64 time , ::booldog::uint32 added )
				{
					return time + added * 60ULL * 1000000ULL;
				};
				booinline ::booldog::uint64 sub_minutes( ::booldog::uint64 time , ::booldog::uint32 added )
				{
					return time - added * 60ULL * 1000000ULL;
				};
				booinline ::booldog::uint64 add_seconds( ::booldog::uint64 time , ::booldog::uint32 added )
				{
					return time + added * 1000000ULL;
				};
				booinline ::booldog::uint64 sub_seconds( ::booldog::uint64 time , ::booldog::uint32 added )
				{
					return time - added * 1000000ULL;
				};
				namespace mbs
				{
					/*
					format(%H - hour, %M - minute, %S - second, %MS - milisecond, %d - day, %m - month, %Y - year)
					*/
					template< size_t step >
					booinline bool tostring( ::booldog::result_mbchar* pres , ::booldog::allocator* allocator , const char* format
						, ::booldog::uint64 time , const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						debuginfo_macros_statement( 9 );

						::booldog::result_mbchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_mbchar );

						if( format == 0 || format[ 0 ] == 0 )
							format = "%H:%M:%S %d.%m.%Y";

						::booldog::result resres;
						::booldog::uint32 hour = 0 , minute = 0 , second = 0 , millisecond = 0;
						::booldog::uint32 year = 0 , month = 0 , day_of_month = 0;
						size_t diff = 0;

						size_t hourstrlen = 0 , minutestrlen = 0 , secondstrlen = 0
							, millisecondstrlen = 0 , yearstrlen = 0 , monthstrlen = 0
							, day_of_monthstrlen = 0;
						char hourstr[ 3 ] = {0} , minutestr[ 3 ] = {0} , secondstr[ 3 ] = {0} 
							, millisecondstr[ 4 ] = {0} , yearstr[ 8 ] = {0} , monthstr[ 3 ] = {0} 
							, day_of_monthstr[ 3 ] = {0};
						char* ptr = 0;

						debuginfo_macros_statement( 8 );

						if( ::booldog::utils::string::mbs::assign< 8 >( &resres , res->mballocator , false , 0 , res->mbchar 
							, res->mblen , res->mbsize , format , 0 , SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}

						debuginfo_macros_statement( 1 );						

						::booldog::utils::time::posix::time( time , hour , minute , second , millisecond );					
		
						debuginfo_macros_statement( 2 );
							
						::booldog::utils::time::posix::date( time , year , month , day_of_month );

						debuginfo_macros_statement( 3 );

						ptr = res->mbchar;
						for( ; ; )
						{
							debuginfo_macros_statement( 4 );
							
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case 0:
									goto goto_return;
								case '%':
									goto goto_away_from_for;
								}
							}
goto_away_from_for:				
							debuginfo_macros_statement( 6 );
							switch( *ptr )
							{
							case 'H':
								debuginfo_macros_statement( 16 );	
								if( hourstrlen == 0 )
								{
									if( ::booldog::utils::string::mbs::tostring( &resres , hourstr , hourstrlen , 3 , hour 
										, debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
								}
								if( hourstrlen == 1 )
								{
									ptr[ -1 ] = '0';
									*ptr = hourstr[ 0 ];
								}
								else
								{
									ptr[ -1 ] = hourstr[ 0 ];
									*ptr = hourstr[ 1 ];
								}
								break;
							case 'M':
								debuginfo_macros_statement( 17 );	
								if( ptr[ 1 ] == 'S' )
								{
									if( millisecondstrlen == 0 )
									{
										if( ::booldog::utils::string::mbs::tostring( &resres , millisecondstr , millisecondstrlen 
											, 4 , millisecond , debuginfo ) == false )
										{
											res->copy( resres );
											goto goto_return;
										}
									}
									if( millisecondstrlen == 1 )
									{
										ptr[ -1 ] = '0';
										*ptr = '0';
										ptr[ 1 ] = millisecondstr[ 0 ];
									}
									else if( millisecondstrlen == 2 )
									{
										ptr[ -1 ] = '0';
										*ptr = millisecondstr[ 0 ];
										ptr[ 1 ] = millisecondstr[ 1 ];
									}
									else
									{
										ptr[ -1 ] = millisecondstr[ 0 ];
										*ptr = millisecondstr[ 1 ];
										ptr[ 1 ] = millisecondstr[ 2 ];
									}
									ptr++;
								}
								else
								{
									if( minutestrlen == 0 )
									{
										if( ::booldog::utils::string::mbs::tostring( &resres , minutestr , minutestrlen , 3 
											, minute , debuginfo ) == false )
										{
											res->copy( resres );
											goto goto_return;
										}
									}
									if( minutestrlen == 1 )
									{
										ptr[ -1 ] = '0';
										*ptr = minutestr[ 0 ];
									}
									else
									{
										ptr[ -1 ] = minutestr[ 0 ];
										*ptr = minutestr[ 1 ];
									}
								}
								break;
							case 'S':
								debuginfo_macros_statement( 18 );
								if( secondstrlen == 0 )
								{
									if( ::booldog::utils::string::mbs::tostring( &resres , secondstr , secondstrlen , 3 , second 
										, debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
								}
								if( secondstrlen == 1 )
								{
									ptr[ -1 ] = '0';
									*ptr = secondstr[ 0 ];
								}
								else
								{
									ptr[ -1 ] = secondstr[ 0 ];
									*ptr = secondstr[ 1 ];
								}
								break;
							case 'd':
								debuginfo_macros_statement( 19 );
								if( day_of_monthstrlen == 0 )
								{
									if( ::booldog::utils::string::mbs::tostring( &resres , day_of_monthstr , day_of_monthstrlen 
										, 3 , day_of_month , debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
								}
								if( day_of_monthstrlen == 1 )
								{
									ptr[ -1 ] = '0';
									*ptr = day_of_monthstr[ 0 ];
								}
								else
								{
									ptr[ -1 ] = day_of_monthstr[ 0 ];
									*ptr = day_of_monthstr[ 1 ];
								}
								break;
							case 'm':
								debuginfo_macros_statement( 20 );

								if( monthstrlen == 0 )
								{
									if( ::booldog::utils::string::mbs::tostring( &resres , monthstr , monthstrlen , 3 , month 
										, debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
								}
								if( monthstrlen == 1 )
								{
									ptr[ -1 ] = '0';
									*ptr = monthstr[ 0 ];
								}
								else
								{
									ptr[ -1 ] = monthstr[ 0 ];
									*ptr = monthstr[ 1 ];
								}
								break;
							case 'Y':
								debuginfo_macros_statement( 21 );

								if( yearstrlen == 0 )
								{
									if( ::booldog::utils::string::mbs::tostring( &resres , yearstr , yearstrlen , 8 , year 
										, debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
								}
								debuginfo_macros_statement( 23 );
								if( res->mblen + yearstrlen - 1 > res->mbsize )
								{
									debuginfo_macros_statement( 24 );
									res->mbsize = res->mblen + yearstrlen - 1 + step;
									char* oldmbchar = res->mbchar;
									res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
									if( res->mbchar == 0 )
									{
										res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
										goto goto_return;
									}
									ptr = &res->mbchar[ (size_t)( ptr - oldmbchar ) ];
								}
								debuginfo_macros_statement( 25 );
								::booldog::mem::insert< char >( (size_t)( ptr - res->mbchar ) - 1 , res->mbchar , res->mblen + 1 
									, res->mbsize , 2 , yearstr , yearstrlen );
								diff = yearstrlen - 2;
								res->mblen += diff;
								ptr += diff;
								break;
							case 0:
								goto goto_return;
							}
							ptr++;

							debuginfo_macros_statement( 7 );
						}
	goto_return:
						return res->succeeded();
					};
					/*
					format(%H - hour, %M - minute, %S - second, %MS - milisecond, %d - day, %m - month, %Y - year)
					*/
					booinline ::booldog::uint64 parse( const char* timestring , const char* format )
					{
						if( format == 0 || format[ 0 ] == 0 )
							format = "%H:%M:%S %d.%m.%Y";

						::booldog::uint64 time = 0;
						::booldog::uint32 millisecond = 0 , second = 0 , minute = 0 , hour = 0 , day_of_month = 1 
							, month = 1 , year = 1970;

						const char* fmtptr = format;
						const ::booldog::byte* ptr = (::booldog::byte*)timestring;
goto_begin:						
						for( ; ; )
						{
							switch( *fmtptr )
							{
							case 0:
								if( *ptr != 0 )
									goto goto_return;
								goto goto_cycle_away;
							case '%':
								goto goto_process;
							default:
								if( *fmtptr++ != (char)*ptr++ )
									goto goto_return;
							}
						}
goto_process:
						switch( *++fmtptr )
						{
						case 'Y':
							fmtptr++;
							year = ::booldog::utils::decimal_string_to_number< ::booldog::uint32 >( ptr );
							break;
						case 'm':
							fmtptr++;
							month = ::booldog::utils::decimal_string_to_number< ::booldog::uint32 >( ptr );
							break;
						case 'd':
							fmtptr++;
							day_of_month = ::booldog::utils::decimal_string_to_number< ::booldog::uint32 >( ptr );
							break;
						case 'S':
							fmtptr++;
							second = ::booldog::utils::decimal_string_to_number< ::booldog::uint32 >( ptr );
							break;
						case 'M':
							if( *++fmtptr == 'S' )
							{
								fmtptr++;
								millisecond = ::booldog::utils::decimal_string_to_number< ::booldog::uint32 >( ptr );
							}
							else							
								minute = ::booldog::utils::decimal_string_to_number< ::booldog::uint32 >( ptr );
							break;
						case 'H':
							fmtptr++;
							hour = ::booldog::utils::decimal_string_to_number< ::booldog::uint32 >( ptr );
							break;
						default:
							if( fmtptr[ -1 ] != (char)*ptr++ )
								goto goto_return;
							break;
						}
						goto goto_begin;
goto_cycle_away:
						time = ::booldog::utils::time::posix::generate( millisecond , second , minute , hour , day_of_month 
							, month , year );
goto_return:					
						return time;
					};
				};
				namespace wcs
				{
				};
			};
		};
	};
};
#endif