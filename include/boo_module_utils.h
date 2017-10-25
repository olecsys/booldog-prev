#ifndef BOO_MODULE_UTILS_H
#define BOO_MODULE_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_result.h"
#include "boo_allocator.h"
#include "boo_mem.h"
#include "boo_error.h"
#include "boo_io_utils.h"
#include "boo_string_utils.h"

#ifdef __UNIX__
#ifndef _LARGEFILE64_SOURCE 
#define _LARGEFILE64_SOURCE 
#endif
#include <unistd.h>

#include <dlfcn.h>
#include <link.h>
#include <limits.h>
#endif
#ifdef __ANDROID__
#include "boo_io_file.h"
#include "boo_io_utils.h"
#endif
namespace booldog
{
	namespace utils
	{
		namespace module
		{			
			booinline bool free( ::booldog::result* pres , booldog::allocator* allocator , ::booldog::module_handle handle
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
				allocator = allocator;
				if( FreeLibrary( handle ) == 0 )
					res->GetLastError();
#else
				if( dlclose( handle ) != 0 )
					res->setdlerror( allocator , dlerror() , debuginfo );
#endif
				return res->succeeded();
			};
			namespace mbs
			{
				booinline ::booldog::module_handle handle( ::booldog::result* pres , booldog::allocator* allocator 
					, const char* modulename , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
					allocator = allocator;
					::booldog::module_handle module_handle = 0;
					if( GetModuleHandleExA( 0 , modulename , &module_handle ) == 0 )
						res->GetLastError();
#else
#ifdef __ANDROID__
					::booldog::module_handle module_handle = 0;
					::booldog::result_file resfile;
					::booldog::result_mbchar mbchar( allocator );
					::booldog::result_mbchar mbchardir( allocator ) , mbchardirenum( allocator );
					if( ::booldog::utils::io::path::mbs::directory( &mbchardir , allocator , modulename , 0 , SIZE_MAX 
						, debuginfo ) )
					{
						res->copy( mbchardir );
						goto goto_return;
					}
					
					::booldog::utils::string::mbs::format(&mbchar, allocator, debuginfo, "/proc/%u/maps"
						, (::booldog::uint32)getpid());
					
					if( ::booldog::io::file::mbsopen( &resfile , allocator , mbchar.mbchar 
						, ::booldog::enums::io::RDONLY , 0 , false , debuginfo ) )
					{
						::booldog::result_size index;
						::booldog::result_buffer buffer( allocator );
						while(resfile.file->readline< 64 >(buffer, debuginfo))
						{
							if(buffer.bufdatasize == 0)
								break;
							::booldog::utils::string::mbs::indexof(&index, false, (char*)buffer.buf
								, 0, buffer.bufdatasize, modulename, 0, SIZE_MAX, debuginfo);
							if( index.sres != SIZE_MAX )
							{
								::booldog::result_size index0;
								::booldog::utils::string::mbs::indexof( &index0 , false , (char*)buffer.buf
									, 0 , buffer.bufdatasize , "/" , 0 , 1 , debuginfo );
								if( index.sres >= index0.sres && index0.sres != SIZE_MAX )
								{
									if( ::booldog::utils::io::path::mbs::directory( &mbchardirenum , allocator 
										, (char*)&buffer.buf[ index0.sres ] , 0 , SIZE_MAX , debuginfo ) )
									{
										res->copy( mbchardirenum );
										break;
									}
									module_handle = dlopen( (char*)&buffer.buf[ index0.sres ]
										, RTLD_NOW );
									if( module_handle )
									{
										res->clear();
										break;
									}
									else
										res->setdlerror( allocator , dlerror() , debuginfo );
								}
							}
						}
						resfile.file->close( 0 , debuginfo );
					}
					else
						res->copy( resfile );
goto_return:
#else
					::booldog::module_handle module_handle = dlopen( modulename , RTLD_NOLOAD | RTLD_NOW );
					if( module_handle == 0 )
						res->setdlerror( allocator , dlerror() , debuginfo );
#endif
#endif
					return module_handle;
				};
				template< size_t step >
				booinline bool pathname( ::booldog::result_mbchar* pres , booldog::allocator* allocator 
					, ::booldog::module_handle module_handle , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
					if( module_handle )
					{
						::booldog::result resres;
#ifdef __WINDOWS__	
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
#else
#ifdef __ANDROID__
						//goto goto_return;
						::booldog::result_mbchar mbchar( res->mballocator );
						::booldog::utils::string::mbs::format(&mbchar, res->mballocator, debuginfo, "/proc/%u/maps" 
							, (::booldog::uint32)getpid());
						::booldog::result_file resfile;
						if( ::booldog::io::file::mbsopen( &resfile , res->mballocator , mbchar.mbchar 
							, ::booldog::enums::io::RDONLY , 0 , false , debuginfo ) )
						{
							::booldog::result_size index;
							::booldog::result_buffer buffer( res->mballocator );
							while(resfile.file->readline< 64 >(buffer, debuginfo))
							{
								if(buffer.bufdatasize == 0)
									break;
								::booldog::utils::string::mbs::indexof(&index, false, (char*)buffer.buf
									, 0, buffer.bufdatasize, "/", 0, 1, debuginfo);
								if( index.sres != SIZE_MAX )
								{
									::booldog::module_handle findmodule_handle = dlopen( (char*)&buffer.buf[ index.sres ]
										, RTLD_NOW );
									if( findmodule_handle )
									{
										if( module_handle == findmodule_handle )
										{
											res->clear();
											if( res->mbchar )
												res->mballocator->free( res->mbchar );

											res->mblen = buffer.bufdatasize - index.sres;
											res->mbsize = buffer.bufsize;
											res->mbchar = (char*)buffer.detach();
											
											::booldog::mem::remove< char >( 0 , res->mbchar , res->mbsize , index.sres );
											
											dlclose( findmodule_handle );
											break;
										}
										dlclose( findmodule_handle );
									}
									else
										res->setdlerror( res->mballocator , dlerror() , debuginfo );
								}
							}
							resfile.file->close( 0 , debuginfo );
						}
						else
						{
							res->copy( resfile );
							goto goto_return;
						}
#else
						struct link_map *map = 0;
						if( dlinfo( module_handle , RTLD_DI_LINKMAP , &map ) != -1 )
						{
							if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , true , 0 , res->mbchar , res->mblen , res->mbsize 
								, map->l_name , 0 , SIZE_MAX , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						else
						{
							res->setdlerror( allocator , dlerror() , debuginfo );
							goto goto_return;
						}
#endif
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
				template< size_t step >
				booinline bool pathname_from_address( ::booldog::result_mbchar* pres , booldog::allocator* allocator , void* address 
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
					if( address )
					{
#ifdef __WINDOWS__
						HMODULE hmodule = 0;
						if( GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS , reinterpret_cast< LPCWSTR >( address ) 
							, &hmodule ) != 0 )
						{
							if( GetModuleHandle( 0 ) == hmodule )
								res->booerr( ::booldog::enums::result::booerr_type_handle_is_executable );
							else
								::booldog::utils::module::mbs::pathname< step >( res , allocator , hmodule , debuginfo );
							FreeLibrary( hmodule );
						}
						else
						{
							res->GetLastError();
							goto goto_return;
						}
#else
						Dl_info info;
						if( dladdr( address , &info ) != 0 )
						{
							::booldog::result resres;
							if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , true , 0 , res->mbchar , res->mblen
								, res->mbsize , info.dli_fname , 0 , SIZE_MAX , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
							if( ::booldog::utils::io::path::mbs::normalize( &resres , res->mbchar , res->mblen , res->mbsize ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						else
							res->setdlerror( allocator , dlerror() , debuginfo );
#endif
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_pointer_parameter_is_null );
goto_return:
					return res->succeeded();
				};
				booinline bool method( ::booldog::result_pointer* pres , booldog::allocator* allocator , ::booldog::module_handle module_handle , const char* name , const ::booldog::debug::info& debuginfo = debuginfo_macros )
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
						res->setdlerror( allocator , dlerror() , debuginfo );
					else
					{
						Dl_info info;
						if( dladdr( (void*)res->pres , &info ) != 0 )
						{
							if( info.dli_fname && info.dli_fname[ 0 ] != 0 )
							{
								::booldog::result_mbchar resmbchar( allocator );
								::booldog::result resres;
								if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , true , 0 , resmbchar.mbchar , resmbchar.mblen 
									, resmbchar.mbsize , info.dli_fname , 0 , SIZE_MAX , debuginfo ) == false )
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
								if( ::booldog::utils::module::mbs::pathname< 256 >( &resmbpathname , allocator , module_handle 
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
							res->setdlerror( allocator , dlerror() , debuginfo );
					}
goto_return:
#endif
					return res->succeeded();
				};
			};
			namespace wcs
			{
				booinline ::booldog::module_handle handle( ::booldog::result* pres , booldog::allocator* allocator , const wchar_t* modulename 
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					::booldog::module_handle module_handle = 0;
#ifdef __WINDOWS__
					allocator = allocator;
					if( GetModuleHandleExW( 0 , modulename , &module_handle ) == 0 )
						res->GetLastError();
					else
					{
						if( GetModuleHandle( 0 ) == module_handle )
						{
							res->booerr( ::booldog::enums::result::booerr_type_handle_is_executable );
							FreeLibrary( module_handle );
							module_handle = 0;
						}
					}
#else
					::booldog::result_mbchar resmbchar( allocator );
					if(::booldog::utils::string::wcs::tombs(resmbchar, modulename, 0, SIZE_MAX, debuginfo))
						module_handle = ::booldog::utils::module::mbs::handle( res , allocator , resmbchar.mbchar , debuginfo );
					else
						res->copy( resmbchar );
#endif
					return module_handle;
				};
				template< size_t step >
				booinline bool pathname( ::booldog::result_wchar* pres , booldog::allocator* allocator 
					, ::booldog::module_handle module_handle , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result_wchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_wchar );
					if( module_handle )
					{
						::booldog::result resres;
#ifdef __WINDOWS__	
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
						if( ::booldog::utils::io::path::wcs::normalize( &resres , res->wchar , res->wlen , res->wsize ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
#else
						::booldog::result_mbchar resmbchar( allocator );
						if( ::booldog::utils::module::mbs::pathname< step >( &resmbchar , allocator , module_handle , debuginfo ) )
							::booldog::utils::string::mbs::towcs( res , allocator , resmbchar.mbchar , 0 , SIZE_MAX , debuginfo );
						else
						{
							res->copy( resmbchar );
							goto goto_return;
						}
#endif
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_pointer_parameter_is_null );
goto_return:
					return res->succeeded();
				};

				template< size_t step >
				booinline bool pathname_from_address( ::booldog::result_wchar* pres , booldog::allocator* allocator , void* address 
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result_wchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_wchar );
					if( address )
					{
#ifdef __WINDOWS__
						HMODULE hmodule = 0;
						if( GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS , reinterpret_cast< LPCWSTR >( address ) 
							, &hmodule ) != 0 )
						{
							if( GetModuleHandle( 0 ) == hmodule )
								res->booerr( ::booldog::enums::result::booerr_type_handle_is_executable );
							else
								::booldog::utils::module::wcs::pathname< step >( res , allocator , hmodule , debuginfo );
							FreeLibrary( hmodule );
						}
						else
						{
							res->GetLastError();
							goto goto_return;
						}
#else
						::booldog::result_mbchar resmbchar( allocator );
						if( ::booldog::utils::module::mbs::pathname_from_address< step >( &resmbchar , allocator , address , debuginfo ) )
							::booldog::utils::string::mbs::towcs( res , allocator , resmbchar.mbchar , 0 , SIZE_MAX , debuginfo );
						else
						{
							res->copy( resmbchar );
							goto goto_return;
						}
#endif
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_pointer_parameter_is_null );
goto_return:
					return res->succeeded();
				};
			};
			booinline ::booldog::module_handle handle( ::booldog::result* pres , booldog::allocator* allocator 
				, void* address , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				::booldog::module_handle module_handle = 0;
#ifdef __WINDOWS__
				allocator = allocator;
				if( GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS , reinterpret_cast< LPCWSTR >( address ) 
					, &module_handle ) == 0 )
					res->GetLastError();
				else
				{
					if( GetModuleHandle( 0 ) == module_handle )
					{
						res->booerr( ::booldog::enums::result::booerr_type_handle_is_executable );
						FreeLibrary( module_handle );
						module_handle = 0;
					}
				}
#else
				::booldog::result_mbchar resmbchar( allocator );
				if( ::booldog::utils::module::mbs::pathname_from_address< 64 >( &resmbchar , allocator , address , debuginfo ) )
					module_handle = ::booldog::utils::module::mbs::handle( res , allocator , resmbchar.mbchar , debuginfo );
				else
					res->copy( resmbchar );
#endif
				return module_handle;
			};
		};
	};
};
#endif