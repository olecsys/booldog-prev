#ifndef BOO_EXECUTABLE_UTILS_H
#define BOO_EXECUTABLE_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_io_utils.h"
#include "boo_string_utils.h"
#ifdef __UNIX__
#ifndef _LARGEFILE64_SOURCE 
#define _LARGEFILE64_SOURCE 
#endif
#include <unistd.h>
#endif
namespace booldog
{
	namespace utils
	{
		namespace executable
		{
			namespace mbs
			{
				template< size_t step >
				booinline bool pathname( ::booldog::result_mbchar* pres , booldog::allocator* allocator , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
					::booldog::result resres;
#ifdef __WINDOWS__
					HMODULE module_handle = GetModuleHandleA( 0 );
					if( module_handle )
					{
						if( res->mbsize < step )
							res->mbsize = step;
						for( ; ; )
						{
							res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
							if( res->mbchar )
							{
								res->mblen = GetModuleFileNameA( module_handle , res->mbchar , (DWORD)res->mbsize );
								if( res->mblen == 0 )
								{
									res->GetLastError();
									goto goto_return;
								}
								else if( res->mblen != res->mbsize )
								{
									res->mbchar[ res->mblen ] = 0;
									if( strncmp( res->mbchar , "\\\\?\\" , 4 ) == 0 )
									{
										::booldog::mem::remove< char >( 0 , res->mbchar , res->mbsize , 4 );
										res->mblen -= 4;
									}
									break;
								}
								else
									res->mbsize += step;
							}
							else
							{
								res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
								goto goto_return;
							}
						}
					}
					else
					{
						res->GetLastError();
						goto goto_return;
					}
#else				
#ifdef __SOLARIS__
					char* path[ 64 ] = {0};
					snprintf( path , 64 , "/proc/%ld/path/a.out" , getpid() );
#elif defined( __LINUX__ )
					const char* path = "/proc/self/exe";
#endif
					if( res->mbsize < step )
						res->mbsize = step;
					for( ; ; )
					{
						res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
						if( res->mbchar )
						{
							res->mblen = readlink( path , res->mbchar , res->mbsize );
							if( res->mblen == (size_t)-1 )
							{
								res->seterrno();
								goto goto_return;
							}
							else if( res->mblen != res->mbsize )
							{
								res->mbchar[ res->mblen ] = 0;
								break;
							}
							else
								res->mbsize += step;
						}
						else
						{
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
#endif
					if( ::booldog::utils::io::path::mbs::normalize( &resres , res->mbchar , res->mblen , res->mbsize ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool directory( ::booldog::result_mbchar* pres , booldog::allocator* allocator , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
					if( ::booldog::utils::executable::mbs::pathname< step >( res , allocator , debuginfo ) )
					{
						::booldog::result locres0;
						if( ::booldog::utils::io::path::mbs::directory( &locres0 , res->mbchar , res->mblen ) == false )
							res->copy( locres0 );
					}
					return res->succeeded();
				};
			};
			namespace wcs
			{
				template< size_t step >
				booinline bool pathname( ::booldog::result_wchar* pres , booldog::allocator* allocator , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result_wchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_wchar );
					::booldog::result resres;
#ifdef __WINDOWS__				
					HMODULE module_handle = GetModuleHandleW( 0 );
					if( module_handle )
					{
						if( res->wsize < step )
							res->wsize = step;
						for( ; ; )
						{
							res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
							if( res->wchar )
							{
								res->wlen = GetModuleFileNameW( module_handle , res->wchar , (DWORD)res->wsize );
								if( res->wlen == 0 )
								{
									res->GetLastError();
									goto goto_return;
								}
								else if( res->wlen != res->wsize )
								{
									res->wchar[ res->wlen ] = 0;
									if( wcsncmp( res->wchar , L"\\\\?\\" , 4 ) == 0 )
									{
										::booldog::mem::remove< wchar_t >( 0 , res->wchar , res->wsize , 4 );
										res->wlen -= 4;
									}
									res->wsize *= sizeof( wchar_t );
									break;
								}
								else
									res->wsize += step;
							}
							else
							{
								res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
								goto goto_return;
							}
						}
					}
					else
					{
						res->GetLastError();
						goto goto_return;
					}
#else
					::booldog::result_mbchar resmbchar( allocator );
					if( ::booldog::utils::executable::mbs::pathname< step >( &resmbchar , allocator , debuginfo ) == false )
					{
						res->copy( resmbchar );
						goto goto_return;
					}
					if( ::booldog::utils::string::mbs::towcs( res , allocator , resmbchar.mbchar , 0 , SIZE_MAX , debuginfo ) == false )
						goto goto_return;
#endif
					if( ::booldog::utils::io::path::wcs::normalize( &resres , res->wchar , res->wlen , res->wsize ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool directory( ::booldog::result_wchar* pres , booldog::allocator* allocator , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result_wchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_wchar );
					if( ::booldog::utils::executable::wcs::pathname< step >( res , allocator , debuginfo ) )
					{
						::booldog::result locres1;
						if( ::booldog::utils::io::path::wcs::directory( &locres1 , res->wchar , res->wlen ) == false )
							res->copy( locres1 );
					}
					return res->succeeded();
				};
			};
			booinline ::booldog::pid_t pid()
			{
#ifdef __WINDOWS__
				return GetCurrentProcessId();
#else
				return getpid();
#endif
			}
		}
	}
}
#endif