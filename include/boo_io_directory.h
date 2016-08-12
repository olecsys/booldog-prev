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
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#endif
namespace booldog
{
	namespace enums
	{
		namespace io
		{
			enum entry_type
			{
				file,
				directory,
				block_device,
				character_device,
				fifo,
				link,
				unix_domain_socket,
				unknown
			};
		};
	};
	namespace typedefs
	{
		typedef bool (*listdir_callback_t)(::booldog::allocator* allocator, void* udata, const char* pathname
			, const char* entry_name, ::booldog::enums::io::entry_type entry_type);
	};
	namespace io
	{
		namespace directory
		{
			namespace mbs
			{
				booinline bool listdir(::booldog::result* pres , booldog::allocator* allocator, const char* pathname
					, ::booldog::typedefs::listdir_callback_t callback, void* udata
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
					::booldog::enums::io::entry_type entry_type = ::booldog::enums::io::unknown;
#ifdef __WINDOWS__		
					udata = udata;
					callback = callback;
					entry_type = entry_type;

					::booldog::result_mbchar pathname_mbchar(allocator);
					if(::booldog::utils::string::mbs::assign<16>(res, allocator, false, 0, pathname_mbchar.mbchar
						, pathname_mbchar.mblen, pathname_mbchar.mbsize, pathname, 0, SIZE_MAX, debuginfo) == false)
						goto goto_return;
					if(::booldog::utils::string::mbs::assign<16>(res, allocator, false, pathname_mbchar.mblen
						, pathname_mbchar.mbchar, pathname_mbchar.mblen, pathname_mbchar.mbsize, "/*", 0, SIZE_MAX
						, debuginfo) == false)
						goto goto_return;
					/*{
						rux::uint32 symbol = directory_name.get_UTF8Char( directory_name.Length() - 1 );
						if( symbol == '/' )
							directory_name += L"*";
						else
							directory_name += L"/*";		
						directory_name.set_ByRef( directory_name.ConvertToUTF16() );
						HANDLE find_handle = NULL;
						WIN32_FIND_DATAW win32_find_data;
						if( ( find_handle = FindFirstFileW( (wchar_t*)directory_name.str() , &win32_find_data ) ) != INVALID_HANDLE_VALUE )
						{
							rux::io::XDirectory directory;
							do
							{
								if( ( win32_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
								{
									if( XString::IsEqualUTF16( (uint16*)win32_find_data.cFileName , (uint16*)L"." ) == 0
										&& XString::IsEqualUTF16( (uint16*)win32_find_data.cFileName , (uint16*)L".." ) == 0 )
									{
										directory = rux::io::XDirectory();
										directory()->_directory_name = _directory_name;
										directory()->_directory_name = directory()->_directory_name.ReplaceAll( '\\' , '/' );
										symbol = directory()->_directory_name.get_UTF8Char( directory()->_directory_name.Length() - 1 );
										if( symbol == '/' )
											directory()->_directory_name += 	win32_find_data.cFileName;		
										else
										{
											directory()->_directory_name += "/";
											directory()->_directory_name += win32_find_data.cFileName;		
										}
										directories.Add( directory );
									}
								}
							}
							while( FindNextFileW( find_handle , &win32_find_data ) );
							FindClose( find_handle );
						}
					}*/			
goto_return:
#else
					long name_max = 0;
					size_t dirent_len = 0;
					int readdir_res = 0;
					dirent* dirent_result = 0;
					dirent* dirent_object_ptr = 0;
					DIR* dir_ptr = opendir(pathname);
					if(dir_ptr == 0)
					{
						res->seterrno();
						goto goto_return;
					}
					name_max = pathconf(pathname, _PC_NAME_MAX);
					if(name_max == -1)
						name_max = 255;
					dirent_len = offsetof(struct dirent, d_name) + name_max + 1;
					dirent_object_ptr = (dirent*)allocator->realloc_array< char* >(0, dirent_len, debuginfo);
					if(dirent_object_ptr == 0)
					{
						res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
						goto goto_return;
					}
					for(;;)
					{
						readdir_res = readdir_r(dir_ptr, dirent_object_ptr, &dirent_result);
						if(readdir_res == 0)
						{
							if(dirent_result)
							{
								if(strcmp(dirent_object_ptr->d_name, ".") == 0
									|| strcmp(dirent_object_ptr->d_name, "..") == 0)
									continue;
								switch(dirent_object_ptr->d_type)
								{
								case DT_BLK:
									entry_type = ::booldog::enums::io::block_device;
									break;
								case DT_CHR:
									entry_type = ::booldog::enums::io::character_device;
									break;
								case DT_DIR:
									entry_type = ::booldog::enums::io::directory;
									break;
								case DT_FIFO:
									entry_type = ::booldog::enums::io::fifo;
									break;
								case DT_LNK:
									entry_type = ::booldog::enums::io::link;
									break;
								case DT_REG:
									entry_type = ::booldog::enums::io::file;
									break;
								case DT_SOCK:
									entry_type = ::booldog::enums::io::unix_domain_socket;
									break;
								case DT_UNKNOWN:
								default:
									entry_type = ::booldog::enums::io::unknown;
									break;
								}
								if(callback(allocator, udata, pathname, dirent_object_ptr->d_name, entry_type) == false)
									break;
							}
							else
								break;
						}
						else
						{
							res->seterrno(readdir_res);
							goto goto_return;
						}
					}
goto_return:
					if(dirent_object_ptr)
						allocator->free(dirent_object_ptr);
					if(dir_ptr)
						closedir(dir_ptr);
#endif
					return res->succeeded();
				};
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