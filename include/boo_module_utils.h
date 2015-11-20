#ifndef BOO_MODULE_UTILS_H
#define BOO_MODULE_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_result.h>
#include <boo_allocator.h>
#include <boo_mem.h>
#include <boo_error.h>
#include <boo_io_utils.h>
#ifdef __UNIX__
#include <unistd.h>
#endif
namespace booldog
{
	namespace utils
	{
		namespace module
		{
			namespace mbs
			{
				template< size_t step >
				bool filename( ::booldog::result_mbchar* pres , ::booldog::module_handle module_handle , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
					if( module_handle )
					{
#ifdef __WINDOWS__	
						res->mbsize = step;
						for( ; ; )
						{
							res->mbchar = res->mallocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
							if( res->mbchar )
							{
								res->mblen = GetModuleFileNameW( module_handle , res->mbchar , res->mbsize );
								if( res->mblen == 0 )
								{
									res->GetLastError();
									break;
								}
								else if( res->mblen != res->mbsize )
								{
									res->mbchar[ res->mblen ] = 0;
									if( strncmp( res->mbchar , L"\\\\?\\" , 4 ) == 0 )
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
								break;
							}
						}
#else
						//dlinfo
#endif
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_pointer_parameter_is_null );
					return res->succeeded();
				};
			};
			namespace wcs
			{
				template< size_t step >
				bool filename( ::booldog::result_wchar* pres , ::booldog::module_handle module_handle , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_wchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_wchar );
					if( module_handle )
					{
#ifdef __WINDOWS__	
						res->wsize = step;
						for( ; ; )
						{
							res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
							if( res->wchar )
							{
								res->wlen = GetModuleFileNameW( module_handle , res->wchar , res->wsize );
								if( res->wlen == 0 )
								{
									res->GetLastError();
									break;
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
								break;
							}
						}
#else
						::booldog::result_mbchar mbcharres( allocator );
						filename< step >( mbcharres , allocator );
						if( mbcharres.succeeded() )
						{
						}
						else
							res->copy( mbcharres );		
#endif
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_pointer_parameter_is_null );
					return res->succeeded();
				};
			};
		};
		namespace executable
		{
			namespace mbs
			{
				template< size_t step >
				bool filename( ::booldog::result_mbchar* pres , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
#ifdef __WINDOWS__				
					HMODULE module_handle = GetModuleHandleA( 0 );
					if( module_handle )
					{
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
									break;
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
								break;
							}
						}
					}
					else
						res->GetLastError();
#else				
#ifdef __SOLARIS__
					char* path[ 64 ] = {0};
					snprintf( path , 64 , "/proc/%ld/path/a.out" , getpid() );
#elif defined( __LINUX__ )
					const char* path = "/proc/self/exe";
#endif
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
								break;
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
							break;
						}
					}					
#endif
					return res->succeeded();
				};
				template< size_t step >
				bool directory( ::booldog::result_mbchar* pres , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
					if( ::booldog::utils::executable::mbs::filename< step >( res , allocator , debuginfo ) )
					{
						::booldog::result locres;
						if( ::booldog::utils::io::path::mbs::directory( &locres , res->mbchar , res->mblen ) == false )
							res->copy( locres );
					}
					return res->succeeded();
				};
			};
			namespace wcs
			{
				template< size_t step >
				bool filename( ::booldog::result_wchar* pres , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_wchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_wchar );
#ifdef __WINDOWS__				
					HMODULE module_handle = GetModuleHandleW( 0 );
					if( module_handle )
					{
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
									break;
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
								break;
							}
						}
					}
					else
						res->GetLastError();
#else
					::booldog::result_mbchar resmbchar( allocator );
					if( ::booldog::utils::executable::mbs::filename< step >( &resmbchar , allocator , debuginfo ) )
					{
					}
					else
						res->copy( resmbchar );
#endif
					return res->succeeded();
				};
				template< size_t step >
				bool directory( ::booldog::result_wchar* pres , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_wchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_wchar );
					if( ::booldog::utils::executable::wcs::filename< step >( res , allocator , debuginfo ) )
					{
						::booldog::result locres;
						if( ::booldog::utils::io::path::wcs::directory( &locres , res->wchar , res->wlen ) == false )
							res->copy( locres );
					}
					return res->succeeded();
				};
			};
		};
	};
};
#endif