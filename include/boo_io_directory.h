#ifndef BOO_IO_DIRECTORY_H
#define BOO_IO_DIRECTORY_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_io_utils.h)
#include BOOLDOG_HEADER(boo_param.h)
#include BOOLDOG_HEADER(boo_string_utils.h)
#include BOOLDOG_HEADER(boo_executable_utils.h)

#ifdef __WINDOWS__
#include <direct.h>
#else
#include <sys/stat.h>
#endif
namespace booldog
{
	namespace io
	{
		namespace directory
		{
			namespace mbs
			{
				static bool create( ::booldog::result* pres , booldog::allocator* allocator , const char* name_or_path 
					, ::booldog::named_param* named_params = 0 , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
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
					if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , true , 0 , res_name_or_path.mbchar 
						, res_name_or_path.mblen , res_name_or_path.mbsize , name_or_path , 0 , SIZE_MAX , debuginfo ) == false )
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
						if( ::booldog::utils::io::path::mbs::normalize( &resres , res_name_or_path.mbchar , res_name_or_path.mblen 
							, res_name_or_path.mbsize ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
#ifdef __WINDOWS__
						if( _mkdir( res_name_or_path.mbchar ) == 0 )
#else
						if( mkdir( res_name_or_path.mbchar , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ) == 0 )
#endif
							goto goto_return;
						else
							res->seterrno();
					}
					else
					{
						::booldog::result_mbchar res_root_dir( allocator );

						if( settings[ 1 ].type != ::booldog::enums::param::type_not_found )
						{
							if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , SIZE_MAX
								, res_root_dir.mbchar , res_root_dir.mblen , res_root_dir.mbsize , settings[ 1 ].pcharvalue , 0 
								, SIZE_MAX , debuginfo ) == false )
							{
								res->copy( res_root_dir );
								goto goto_return;							
							}
						}
						else if( settings[ 2 ].type != ::booldog::enums::param::type_not_found )
						{
							if( ::booldog::utils::string::wcs::tombs( &res_root_dir , allocator , settings[ 2 ].pwcharvalue , 0 
								, SIZE_MAX , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;							
							}
						}
						else
						{
							if( settings[ 3 ].type != ::booldog::enums::param::type_not_found && settings[ 3 ].boolvalue )
							{
								if( ::booldog::utils::executable::mbs::directory< 256 >( &res_root_dir , allocator , debuginfo ) == false )
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
							if( ::booldog::utils::io::path::mbs::normalize( &resres , res_root_dir.mbchar , res_root_dir.mblen 
								, res_root_dir.mbsize ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
							res_root_dir_mblen = res_root_dir.mblen;
						}
						if( settings[ 0 ].type != ::booldog::enums::param::type_not_found )
						{
							for( size_t index = 0 ; settings[ 0 ].pparamvalue[ index ].type != ::booldog::enums::param::type_none ; index++ )
							{
								if( res_root_dir.mbchar )
								{
									res_root_dir.mbchar[ res_root_dir_mblen ] = 0;
									res_root_dir.mblen = res_root_dir_mblen;
								}
								if( res_root_dir_mblen )
								{
									if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen 
										, res_root_dir.mbchar , res_root_dir.mblen , res_root_dir.mbsize 
										, &::booldog::io::mbs::slash , 0 , 1 , debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
								}
								if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pchar )
								{
									if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
										, res_root_dir.mblen , res_root_dir.mbsize , settings[ 0 ].pparamvalue[ index ].pcharvalue , 0
										, SIZE_MAX , debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
								}
								else if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pwchar )
								{
									if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
										, res_root_dir.mblen , res_root_dir.mbsize , settings[ 0 ].pparamvalue[ index ].pwcharvalue , 0
										, SIZE_MAX , debuginfo ) == false )
									{
										res->copy( resres );
										goto goto_return;
									}
								}
								else
									continue;
								if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
									, res_root_dir.mblen , res_root_dir.mbsize , &::booldog::io::mbs::slash , 0
									, 1 , debuginfo ) == false )
								{
									res->copy( resres );
									goto goto_return;
								}
								if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
									, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
									, SIZE_MAX , debuginfo ) == false )
								{
									res->copy( resres );
									goto goto_return;
								}
								if( ::booldog::io::directory::mbs::create( res , allocator , res_root_dir.mbchar , 0
									, debuginfo ) )
									goto goto_return;
							}
						}
						if( res_root_dir.mbchar )
						{
							res_root_dir.mbchar[ res_root_dir_mblen ] = 0;
							res_root_dir.mblen = res_root_dir_mblen;
							if( res_root_dir_mblen )
							{
								if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen 
									, res_root_dir.mbchar , res_root_dir.mblen , res_root_dir.mbsize , &::booldog::io::mbs::slash 
									, 0	, 1 , debuginfo ) == false )
								{
									res->copy( resres );
									goto goto_return;
								}
							}
							if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
								, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
								, SIZE_MAX , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
							if( ::booldog::io::directory::mbs::create( res , allocator , res_root_dir.mbchar , 0 , debuginfo ) )
								goto goto_return;
						}
						else
						{
							if( ::booldog::utils::io::path::mbs::normalize( &resres , res_name_or_path.mbchar , res_name_or_path.mblen 
								, res_name_or_path.mbsize ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
#ifdef __WINDOWS__
							if( _mkdir( res_name_or_path.mbchar ) == 0 )
#else
							if( mkdir( res_name_or_path.mbchar , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ) == 0 )
#endif
								goto goto_return;
							else
								res->seterrno();
						}
					}
		goto_return:
					return res->succeeded();
				};
			};
		};
	};
};
#endif