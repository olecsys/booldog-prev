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
#include <boo_string_utils.h>
#ifdef __UNIX__
#include <unistd.h>
#include <dlfcn.h>
#include <link.h>
#include <limits.h>
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
				booinline bool pathname( ::booldog::result_mbchar* pres , ::booldog::module_handle module_handle , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
					if( module_handle )
					{
						::booldog::result resres;
#ifdef __WINDOWS__	
						res->mbsize = step;
						for( ; ; )
						{
							res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
							if( res->mbchar )
							{
								res->mblen = GetModuleFileNameA( module_handle , res->mbchar , res->mbsize );
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
#else
						struct link_map *map = 0;
						if( dlinfo( module_handle , RTLD_DI_LINKMAP , &map ) != -1 )
						{
							if( ::booldog::utils::string::mbs::insert( &resres , 0 , res->mbchar , res->mblen , res->mbsize 
								, map->l_name , 0 , SIZE_MAX , allocator , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						else
						{
							res->setdlerror( dlerror() , allocator , debuginfo );
							goto goto_return;
						}
#endif
						if( ::booldog::utils::io::path::mbs::normalize( &resres , res->mbchar , res->mblen , res->mbsize ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_pointer_parameter_is_null );
goto_return:
					return res->succeeded();
				};
				booinline bool method( ::booldog::result_pointer* pres , ::booldog::module_handle module_handle , const char* name , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					allocator = allocator;
					debuginfo = debuginfo;
					::booldog::result_pointer locres;
					BOOINIT_RESULT( ::booldog::result_pointer );
					res->pres = (void*)dlsym( module_handle , name );
					if( res->pres == 0 )
#ifdef __WINDOWS__
						res->GetLastError();
#else
						res->setdlerror( dlerror() , allocator , debuginfo );
					else
					{
						Dl_info info;
						if( dladdr( (void*)res->pres , &info ) != 0 )
						{
							if( info.dli_fname && info.dli_fname[ 0 ] != 0 )
							{
								::booldog::result_mbchar resmbchar( allocator );
								::booldog::result resres;
								if( ::booldog::utils::string::mbs::insert( &resres , 0 , resmbchar.mbchar , resmbchar.mblen 
									, resmbchar.mbsize , info.dli_fname , 0 , SIZE_MAX , allocator , debuginfo ) == false )
								{
									res->copy( resres );
									goto goto_return;
								}
								if( ::booldog::utils::io::path::mbs::normalize( &resres , resmbchar.mbchar , resmbchar.mblen 
									, resmbchar.mbsize ) == false )
								{
									res->copy( resres );
									goto goto_return;
								}
								::booldog::result_mbchar resmbpathname( allocator );
								if( ::booldog::utils::module::mbs::pathname< 256 >( &resmbpathname , module_handle , allocator 
									, debuginfo ) == false )
								{
									res->copy( resmbpathname );
									goto goto_return;
								}
								if( strcmp( resmbchar.mbchar , resmbpathname.mbchar ) != 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_function_not_found_in_module );
									goto goto_return;
								}
							}
						}
						else
							res->setdlerror( dlerror() , allocator , debuginfo );
					}
goto_return:
#endif
					return res->succeeded();
				};
			};
			namespace wcs
			{
				template< size_t step >
				booinline bool pathname( ::booldog::result_wchar* pres , ::booldog::module_handle module_handle , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_wchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_wchar );
					if( module_handle )
					{
						::booldog::result resres;
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
#else
						::booldog::result_mbchar resmbchar( allocator );
						if( ::booldog::utils::module::mbs::pathname< step >( &resmbchar , module_handle , allocator , debuginfo ) )
						{
							::booldog::result_wchar reswchar( allocator );
							if( ::booldog::utils::string::mbs::towcs( &reswchar , resmbchar.mbchar , 0 , SIZE_MAX , allocator 
								, debuginfo ) )
							{
								res->wchar = reswchar.wchar;
								res->wsize = reswchar.wsize;
								res->wlen = reswchar.wlen;
								reswchar.detach();
							}
							else
							{
								res->copy( reswchar );
								goto goto_return;
							}
						}
						else
						{
							res->copy( resmbchar );
							goto goto_return;
						}
#endif
						if( ::booldog::utils::io::path::wcs::normalize( &resres , res->wchar , res->wlen , res->wsize ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_pointer_parameter_is_null );
goto_return:
					return res->succeeded();
				};
			};
		};
		namespace executable
		{
			namespace mbs
			{
				template< size_t step >
				booinline bool pathname( ::booldog::result_mbchar* pres , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
					::booldog::result resres;
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
				booinline bool directory( ::booldog::result_mbchar* pres , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
					if( ::booldog::utils::executable::mbs::pathname< step >( res , allocator , debuginfo ) )
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
				booinline bool pathname( ::booldog::result_wchar* pres , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_wchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_wchar );
					::booldog::result resres;
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
					if( ::booldog::utils::string::mbs::towcs( res , resmbchar.mbchar , 0 , SIZE_MAX , allocator , debuginfo ) == false )
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
				booinline bool directory( ::booldog::result_wchar* pres , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_wchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_wchar );
					if( ::booldog::utils::executable::wcs::pathname< step >( res , allocator , debuginfo ) )
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