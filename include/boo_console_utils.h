#ifndef BOO_CONSOLE_UTILS_H
#define BOO_CONSOLE_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_string_utils.h)
#ifdef __WINDOWS__
#include <io.h>
#else
#include <unistd.h>
#endif
namespace booldog
{	
	namespace enums
	{
		namespace console
		{
			enum colors
			{
				any ,
				red ,
				green ,
				white
			};
		};
	};
	namespace utils
	{
		namespace console
		{
			namespace out
			{
				namespace mbs
				{
					booinline bool printf( ::booldog::result* pres , ::booldog::allocator* allocator 
						, ::booldog::enums::console::colors color , const ::booldog::debug::info& debuginfo , const char* format 
						, ... )
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
						HANDLE stdhandle = GetStdHandle( STD_OUTPUT_HANDLE );
						if( stdhandle == INVALID_HANDLE_VALUE )
						{
							res->GetLastError();
							return false;
						}
#endif
						switch( color )
						{
						case ::booldog::enums::console::red:
#ifdef __WINDOWS__
							SetConsoleTextAttribute( stdhandle , FOREGROUND_RED | FOREGROUND_INTENSITY );	
#else
							write( 1 , "\e[31m" , 5 );
#endif
							break;
						case ::booldog::enums::console::green:
#ifdef __WINDOWS__
							SetConsoleTextAttribute( stdhandle , FOREGROUND_GREEN | FOREGROUND_INTENSITY );
#else
							write( 1 , "\e[32m" , 5 );
#endif
							break;
						case ::booldog::enums::console::white:
#ifdef __WINDOWS__
							SetConsoleTextAttribute( stdhandle 
								, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
#else
							write( 1 , "\e[37m" , 5 );
#endif
							break;
						}
						va_list ap;
						va_start( ap , format );
						::booldog::result_mbchar mbchar( allocator );
						::booldog::utils::string::mbs::sprintf( &mbchar , allocator , format , ap , debuginfo );
						va_end( ap );
						if( mbchar.succeeded() )
						{
#ifdef __WINDOWS__
							if( ::_write( 1 , mbchar.mbchar , (unsigned int)mbchar.mblen ) == -1 )
#else
							if( write( 1 , mbchar.mbchar , mbchar.mblen ) == -1 )
#endif
								res->seterrno();
						}
						else
							res->copy( mbchar );
						if( color != ::booldog::enums::console::any )
						{
#ifdef __WINDOWS__
							SetConsoleTextAttribute( stdhandle 
								, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
#else
							write( 1 , "\e[37m" , 5 );
#endif
						}
#ifdef __WINDOWS__
						fflush( stdout );
#else
						fsync( STDOUT_FILENO );
#endif
						return res->succeeded();
					};
				};
			};
			namespace err
			{
				namespace mbs
				{
					booinline bool printf( ::booldog::result* pres , ::booldog::allocator* allocator 
						, ::booldog::enums::console::colors color , const ::booldog::debug::info& debuginfo , const char* format 
						, ... )
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
						HANDLE stdhandle = GetStdHandle( STD_ERROR_HANDLE );
						if( stdhandle == INVALID_HANDLE_VALUE )
						{
							res->GetLastError();
							return false;
						}
#endif
						switch( color )
						{
						case ::booldog::enums::console::red:
#ifdef __WINDOWS__
							SetConsoleTextAttribute( stdhandle , FOREGROUND_RED | FOREGROUND_INTENSITY );	
#else
							write( 2 , "\e[31m" , 5 );
#endif
							break;
						case ::booldog::enums::console::green:
#ifdef __WINDOWS__
							SetConsoleTextAttribute( stdhandle , FOREGROUND_GREEN | FOREGROUND_INTENSITY );
#else
							write( 2 , "\e[32m" , 5 );
#endif
							break;
						case ::booldog::enums::console::white:
#ifdef __WINDOWS__
							SetConsoleTextAttribute( stdhandle 
								, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
#else
							write( 2 , "\e[37m" , 5 );
#endif
							break;
						}
						va_list ap;
						va_start( ap , format );
						::booldog::result_mbchar mbchar( allocator );
						::booldog::utils::string::mbs::sprintf( &mbchar , allocator , format , ap , debuginfo );
						va_end( ap );
						if( mbchar.succeeded() )
						{
#ifdef __WINDOWS__
							if( ::_write( 2 , mbchar.mbchar , (unsigned int)mbchar.mblen ) == -1 )
#else
							if( write( 2 , mbchar.mbchar , mbchar.mblen ) == -1 )
#endif
								res->seterrno();
						}
						else
							res->copy( mbchar );
						if( color != ::booldog::enums::console::any )
						{
#ifdef __WINDOWS__
							SetConsoleTextAttribute( stdhandle 
								, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
#else
							write( 2 , "\e[37m" , 5 );
#endif
						}
#ifdef __WINDOWS__
						fflush( stderr );
#else
						fsync( STDERR_FILENO );
#endif
						return res->succeeded();
					};
				};
			};
		};
	};
};
#endif