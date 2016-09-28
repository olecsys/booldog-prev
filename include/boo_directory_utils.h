#ifndef BOO_DIRECTORY_UTILS_H
#define BOO_DIRECTORY_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_string_utils.h)
#include BOOLDOG_HEADER(boo_param.h)
#include BOOLDOG_HEADER(boo_executable_utils.h)
#include <sys/types.h>
#include <sys/stat.h>
#ifdef __UNIX__
#include <unistd.h>
#endif
namespace booldog
{	
	namespace utils
	{
		namespace io
		{
			namespace directory
			{
				namespace wcs
				{
					booinline bool exists( ::booldog::result_bool* pres , ::booldog::allocator* allocator 
						, const wchar_t* name_or_path , const ::booldog::debug::info& debuginfo = debuginfo_macros );
					booinline bool exists( ::booldog::result_bool* pres , booldog::allocator* allocator
						, const wchar_t* name_or_path , ::booldog::named_param* named_params = 0 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros );
				};
				namespace mbs
				{
					booinline bool exists( ::booldog::result_bool* pres , ::booldog::allocator* allocator 
						, const char* name_or_path , const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_bool locres;
						BOOINIT_RESULT( ::booldog::result_bool );
#ifdef __WINDOWS__
						::booldog::result_wchar reswchar( allocator );
						if( ::booldog::utils::string::mbs::towcs( &reswchar , allocator , name_or_path , 0 , SIZE_MAX
							, debuginfo ) )
							::booldog::utils::io::directory::wcs::exists( res , allocator , reswchar.wchar , debuginfo );
						else
							res->copy( reswchar );
#else
						allocator = allocator;
						struct stat st;
						if( stat( name_or_path , &st ) == 0 )
						{
							if(S_ISDIR(st.st_mode))
								res->bres = true;
						}
#endif
						return res->succeeded();
					};
					booinline bool exists( ::booldog::result_bool* pres , booldog::allocator* allocator
						, const char* name_or_path , ::booldog::named_param* named_params = 0 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_bool locres;
						BOOINIT_RESULT( ::booldog::result_bool );
#ifdef __WINDOWS__
						::booldog::result_wchar reswchar( allocator );
						if( ::booldog::utils::string::mbs::towcs( &reswchar , allocator , name_or_path , 0 , SIZE_MAX 
							, debuginfo ) )
							::booldog::utils::io::directory::wcs::exists( res , allocator , reswchar.wchar , named_params 
							, debuginfo );
						else
							res->copy( reswchar );
#else
						booldog::named_param settings[] =
						{
							BOO_SEARCH_NAMED_PARAM_PPARAM( "search_paths" ) ,
							BOO_SEARCH_NAMED_PARAM_PCHAR( "root_path" ) ,
							BOO_SEARCH_NAMED_PARAM_WCHAR( "root_path" ) ,
							BOO_SEARCH_NAMED_PARAM_BOOL( "exedir_as_root_path" ) ,
							BOO_SEARCH_NAMED_PARAM_NONE
						};
						::booldog::utils::param::search( named_params , settings );

						::booldog::result_mbchar res_name_or_path( allocator );
			
						::booldog::result_bool resbool;
						::booldog::result resres;
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , true , 0 
							, res_name_or_path.mbchar , res_name_or_path.mblen , res_name_or_path.mbsize , name_or_path , 0 
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::io::path::mbs::isabsolute( &resbool , res_name_or_path.mbchar ) == false )
						{
							res->copy( resbool );
							goto goto_return;
						}
						if( resbool.bres )
						{	
							if( ::booldog::utils::io::path::mbs::normalize( &resres , res_name_or_path.mbchar 
								, res_name_or_path.mblen , res_name_or_path.mbsize ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
							return ::booldog::utils::io::directory::mbs::exists( res , allocator , res_name_or_path.mbchar 
								, debuginfo );
						}
						else
						{
							::booldog::result_mbchar res_root_dir( allocator );

							if( settings[ 1 ].type != ::booldog::enums::param::type_not_found )
							{
								if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , SIZE_MAX 
									, res_root_dir.mbchar , res_root_dir.mblen , res_root_dir.mbsize , settings[ 1 ].pcharvalue 
									, 0 , SIZE_MAX , debuginfo ) == false )
								{
									res->copy( res_root_dir );
									goto goto_return;							
								}
							}
							else if( settings[ 2 ].type != ::booldog::enums::param::type_not_found )
							{
								if( ::booldog::utils::string::wcs::tombs( &res_root_dir , allocator , settings[ 2 ].pwcharvalue 
									, 0 , SIZE_MAX , debuginfo ) == false )
								{
									res->copy( resres );
									goto goto_return;							
								}
							}
							else
							{
								if( settings[ 3 ].type != ::booldog::enums::param::type_not_found && settings[ 3 ].boolvalue )
								{
									if( ::booldog::utils::executable::mbs::directory< 256 >( &res_root_dir , allocator 
										, debuginfo ) == false )
									{
										res->copy( res_root_dir );
										goto goto_return;
									}
								}
							}
							size_t res_root_dir_mblen = 0;
							if( res_root_dir.mbchar )
							{
								::booldog::result resres;
								if( ::booldog::utils::io::path::mbs::normalize( &resres , res_root_dir.mbchar 
									, res_root_dir.mblen , res_root_dir.mbsize ) == false )
								{
									res->copy( resres );
									goto goto_return;
								}
								res_root_dir_mblen = res_root_dir.mblen;
							}
							if( settings[ 0 ].type != ::booldog::enums::param::type_not_found )
							{
								for( size_t index = 0 ; settings[ 0 ].pparamvalue[ index ].type 
									!= ::booldog::enums::param::type_none ; index++ )
								{
									if( res_root_dir.mbchar )
									{
										res_root_dir.mbchar[ res_root_dir_mblen ] = 0;
										res_root_dir.mblen = res_root_dir_mblen;
									}
									if( res_root_dir_mblen )
									{
										if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false 
											, res_root_dir.mblen , res_root_dir.mbchar , res_root_dir.mblen 
											, res_root_dir.mbsize , &::booldog::io::mbs::slash , 0 , 1 , debuginfo ) == false )
										{
											res->copy( resres );
											goto goto_return;
										}
									}
									if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pchar )
									{
										if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false 
											, res_root_dir.mblen , res_root_dir.mbchar , res_root_dir.mblen 
											, res_root_dir.mbsize , settings[ 0 ].pparamvalue[ index ].pcharvalue , 0
											, SIZE_MAX , debuginfo ) == false )
										{
											res->copy( resres );
											goto goto_return;
										}
									}
									else if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pwchar )
									{
										if( ::booldog::utils::string::wcs::insert( &resres , allocator , false 
											, res_root_dir.mblen , res_root_dir.mbchar , res_root_dir.mblen 
											, res_root_dir.mbsize , settings[ 0 ].pparamvalue[ index ].pwcharvalue , 0
											, SIZE_MAX , debuginfo ) == false )
										{
											res->copy( resres );
											goto goto_return;
										}
									}
									else
										continue;
									if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false 
										, res_root_dir.mblen , res_root_dir.mbchar , res_root_dir.mblen , res_root_dir.mbsize 
										, &::booldog::io::mbs::slash , 0 , 1 , debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
									if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false 
										, res_root_dir.mblen , res_root_dir.mbchar , res_root_dir.mblen , res_root_dir.mbsize 
										, res_name_or_path.mbchar , 0 , SIZE_MAX , debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
									if( ::booldog::utils::io::directory::mbs::exists( res , allocator , res_root_dir.mbchar , 0
										, debuginfo ) == false || res->bres )
										goto goto_return;
								}
							}
							if( res_root_dir.mbchar )
							{
								res_root_dir.mbchar[ res_root_dir_mblen ] = 0;
								res_root_dir.mblen = res_root_dir_mblen;
								if( res_root_dir_mblen )
								{
									if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false 
										, res_root_dir.mblen , res_root_dir.mbchar , res_root_dir.mblen , res_root_dir.mbsize 
										, &::booldog::io::mbs::slash , 0 , 1 , debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
								}
								if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen
									, res_root_dir.mbchar , res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar 
									, 0 , SIZE_MAX , debuginfo ) == false )
								{
									res->copy( resres );
									goto goto_return;
								}
								if( ::booldog::utils::io::directory::mbs::exists( res , allocator , res_root_dir.mbchar , 0
									, debuginfo ) == false || res->bres )
									goto goto_return;
							}
							else
							{
								if( ::booldog::utils::io::path::mbs::normalize( &resres , res_name_or_path.mbchar 
									, res_name_or_path.mblen , res_name_or_path.mbsize ) == false )
								{
									res->copy( resres );
									goto goto_return;
								}
								return ::booldog::utils::io::directory::mbs::exists( res , allocator , res_name_or_path.mbchar 
									, debuginfo );
							}
						}
goto_return:
#endif
						return res->succeeded();
					};
				};
				namespace wcs
				{
					booinline bool exists( ::booldog::result_bool* pres , ::booldog::allocator* allocator 
						, const wchar_t* name_or_path , const ::booldog::debug::info& debuginfo )
					{
						::booldog::result_bool locres;
						BOOINIT_RESULT( ::booldog::result_bool );
#ifdef __WINDOWS__
						debuginfo = debuginfo;
						allocator = allocator;
						struct _stat64 _Stat64;
						if( _wstat64( name_or_path , &_Stat64 ) == 0 )
						{
							if((_Stat64.st_mode & _S_IFDIR))
								res->bres = true;
						}
#else
						::booldog::result_mbchar resmbchar( allocator );
						if( ::booldog::utils::string::wcs::tombs( &resmbchar , allocator , name_or_path , 0 , SIZE_MAX 
							, debuginfo ) )
							::booldog::utils::io::directory::mbs::exists( res , allocator , resmbchar.mbchar , debuginfo );
						else
							res->copy( resmbchar );
#endif
						return res->succeeded();
					};
					bool exists( ::booldog::result_bool* pres , booldog::allocator* allocator , const wchar_t* name_or_path 
						, ::booldog::named_param* named_params , const ::booldog::debug::info& debuginfo )
					{
						::booldog::result_bool locres;
						BOOINIT_RESULT( ::booldog::result_bool );
#ifdef __WINDOWS__
						booldog::named_param settings[] =
						{
							BOO_SEARCH_NAMED_PARAM_PPARAM( "search_paths" ) ,
							BOO_SEARCH_NAMED_PARAM_PCHAR( "root_path" ) ,
							BOO_SEARCH_NAMED_PARAM_WCHAR( "root_path" ) ,
							BOO_SEARCH_NAMED_PARAM_BOOL( "exedir_as_root_path" ) ,
							BOO_SEARCH_NAMED_PARAM_NONE
						};
						::booldog::utils::param::search( named_params , settings );

						::booldog::result_wchar res_name_or_path( allocator );
			
						::booldog::result_bool resbool;
						::booldog::result resres;
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , true , 0 , res_name_or_path.wchar 
							, res_name_or_path.wlen	, res_name_or_path.wsize , name_or_path , 0 , SIZE_MAX 
							, debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::io::path::wcs::isabsolute( &resbool , res_name_or_path.wchar ) == false )
						{
							res->copy( resbool );
							goto goto_return;
						}
						if( resbool.bres )
						{
							if( ::booldog::utils::io::path::wcs::normalize( &resres , res_name_or_path.wchar 
								, res_name_or_path.wlen , res_name_or_path.wsize ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
							return ::booldog::utils::io::directory::wcs::exists( res , allocator , res_name_or_path.wchar 
								, debuginfo );
						}
						else
						{
							::booldog::result_wchar res_root_dir( allocator );

							if( settings[ 1 ].type != ::booldog::enums::param::type_not_found )
							{
								if( ::booldog::utils::string::mbs::towcs( &res_root_dir , allocator , settings[ 1 ].pcharvalue
									, 0 , SIZE_MAX , debuginfo ) == false )
								{
									res->copy( res_root_dir );
									goto goto_return;							
								}
							}
							else if( settings[ 2 ].type != ::booldog::enums::param::type_not_found )
							{
								if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , SIZE_MAX 
									, res_root_dir.wchar , res_root_dir.wlen , res_root_dir.wsize , settings[ 2 ].pwcharvalue 
									, 0 , SIZE_MAX , debuginfo ) == false )
								{
									res->copy( resres );
									goto goto_return;							
								}
							}
							else
							{
								if( settings[ 3 ].type != ::booldog::enums::param::type_not_found && settings[ 3 ].boolvalue )
								{
									if( ::booldog::utils::executable::wcs::directory< 256 >( &res_root_dir , allocator 
										, debuginfo ) == false )
									{
										res->copy( res_root_dir );
										goto goto_return;
									}
								}
							}
							size_t res_root_dir_wlen = 0;
							if( res_root_dir.wchar )
							{
								::booldog::result resres;
								if( ::booldog::utils::io::path::wcs::normalize( &resres , res_root_dir.wchar
									, res_root_dir.wlen , res_root_dir.wsize ) == false )
								{
									res->copy( resres );
									goto goto_return;
								}
								res_root_dir_wlen = res_root_dir.wlen;
							}
							if( settings[ 0 ].type != ::booldog::enums::param::type_not_found )
							{
								for( size_t index = 0 ; settings[ 0 ].pparamvalue[ index ].type 
									!= ::booldog::enums::param::type_none ; index++ )
								{
									if( res_root_dir.wchar )
									{
										res_root_dir.wchar[ res_root_dir_wlen ] = 0;
										res_root_dir.wlen = res_root_dir_wlen;
									}
									if( res_root_dir_wlen )
									{
										if( ::booldog::utils::string::wcs::insert( &resres , allocator , false
											, res_root_dir.wlen , res_root_dir.wchar , res_root_dir.wlen , res_root_dir.wsize 
											, &::booldog::io::wcs::slash , 0 , 1 , debuginfo ) == false )
										{
											res->copy( resres );
											goto goto_return;
										}
									}
									if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pchar )
									{
										if( ::booldog::utils::string::mbs::insert( &resres , allocator , false 
											, res_root_dir.wlen , res_root_dir.wchar , res_root_dir.wlen , res_root_dir.wsize 
											, settings[ 0 ].pparamvalue[ index ].pcharvalue , 0	, SIZE_MAX 
											, debuginfo ) == false )
										{
											res->copy( resres );
											goto goto_return;
										}
									}
									else if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pwchar )
									{
										if( ::booldog::utils::string::wcs::insert( &resres , allocator , false
											, res_root_dir.wlen , res_root_dir.wchar , res_root_dir.wlen , res_root_dir.wsize 
											, settings[ 0 ].pparamvalue[ index ].pwcharvalue , 0 , SIZE_MAX 
											, debuginfo ) == false )
										{
											res->copy( resres );
											goto goto_return;
										}
									}
									else
										continue;
									if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen 
										, res_root_dir.wchar , res_root_dir.wlen , res_root_dir.wsize 
										, &::booldog::io::wcs::slash , 0 , 1 , debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
									if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
										, res_root_dir.wlen , res_root_dir.wsize , res_name_or_path.wchar , 0
										, SIZE_MAX , debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
									if( ::booldog::utils::io::directory::wcs::exists( res , allocator , res_root_dir.wchar , 0 
										, debuginfo ) == false || res->bres )
										goto goto_return;
								}
							}
							if( res_root_dir.wchar )
							{
								res_root_dir.wchar[ res_root_dir_wlen ] = 0;
								res_root_dir.wlen = res_root_dir_wlen;
								if( res_root_dir_wlen )
								{
									if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen
										, res_root_dir.wchar , res_root_dir.wlen , res_root_dir.wsize 
										, &::booldog::io::wcs::slash , 0 , 1 , debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
								}
								if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen 
									, res_root_dir.wchar , res_root_dir.wlen , res_root_dir.wsize , res_name_or_path.wchar , 0
									, SIZE_MAX , debuginfo ) == false )
								{
									res->copy( resres );
									goto goto_return;
								}
								if( ::booldog::utils::io::directory::wcs::exists( res , allocator , res_root_dir.wchar , 0 
									, debuginfo ) == false || res->bres                   )
									goto goto_return;
							}
							else
							{
								if( ::booldog::utils::io::path::wcs::normalize( &resres , res_name_or_path.wchar 
									, res_name_or_path.wlen , res_name_or_path.wsize ) == false )
								{
									res->copy( resres );
									goto goto_return;
								}
								return ::booldog::utils::io::directory::wcs::exists( res , allocator , res_name_or_path.wchar 
									, debuginfo );
							}
						}
goto_return:
#else
						::booldog::result_mbchar resmbchar( allocator );
						if( ::booldog::utils::string::wcs::tombs( &resmbchar , allocator , name_or_path , 0 , SIZE_MAX 
							, debuginfo ) )
							::booldog::utils::io::directory::mbs::exists( res , allocator , resmbchar.mbchar , named_params
							, debuginfo );
						else
							res->copy( resmbchar );
#endif
						return res->succeeded();
					};
				};
			};
		};
	};
};
#endif