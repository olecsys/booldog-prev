#ifndef BOO_IO_FILE_H
#define BOO_IO_FILE_H
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

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef __WINDOWS__
#include <io.h>
#include <share.h>
#else
#ifndef _LARGEFILE64_SOURCE 
#define _LARGEFILE64_SOURCE 
#endif
#include <unistd.h>
#endif
namespace booldog
{
	namespace enums
	{
		namespace io
		{
			enum oflag
			{
#ifdef __WINDOWS__
				CREAT = _O_CREAT ,
				RDWR = _O_RDWR ,
				APPEND = _O_APPEND ,
				TRUNC = _O_TRUNC ,
				WRONLY = _O_WRONLY ,
				RDONLY = _O_RDONLY
#else
				CREAT = O_CREAT ,
				RDWR = O_RDWR ,
				APPEND = O_APPEND ,
				TRUNC = O_TRUNC ,
				WRONLY = O_WRONLY ,
				RDONLY = O_RDONLY
#endif
			};
			enum file_mode
			{
				file_mode_append = 1 ,
				file_mode_read = 2 ,	
				file_mode_write = 4 ,
				file_mode_create = 8 ,
                                file_mode_truncate = 16,
                                file_mode_tmpfile = 32,
                                file_mode_nobuffering = 64
			};
			enum file_position_origin
			{
				file_position_origin_begin = SEEK_SET ,
				file_position_origin_curpos = SEEK_CUR ,
				file_position_origin_end = SEEK_END
			};
                }
        }
	namespace io
	{
		class file;
        }
	class result_file : public ::booldog::result
	{
	private:
		result_file( const ::booldog::result& )
		{
                }
                result_file(const ::booldog::result_file&)
                    : result()
		{
                }
		::booldog::result_file& operator = ( const ::booldog::result_file& )
		{
			return *this;
                }
	public:
		::booldog::io::file* file;
		result_file( void )
		{
			file = 0;
                }
		virtual ~result_file( void )
		{
                }
		virtual void clear( void ) const
		{
			::booldog::result_file* _obj_ = const_cast< ::booldog::result_file* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			_obj_->file = 0;
                }
	};
	namespace io
	{
		class file
		{
			friend class ::booldog::allocator;
			::booldog::allocator* _allocator;
			//char* _filename;
			int _file;
			int _file_mode;
		private:
			file( void )
			{
                        }
			file( ::booldog::allocator* pallocator , int pfh , int file_mode )
				: _allocator( pallocator ) , _file( pfh ) , _file_mode( file_mode )
			{
                        }
			file( const ::booldog::io::file& )
			{
                        }
			::booldog::io::file& operator = ( const ::booldog::io::file& )
			{
				return *this;
                        }
		public:
			static bool mbsopen( ::booldog::result_file* pres , booldog::allocator* allocator , const char* name_or_path , int file_mode
				, ::booldog::named_param* named_params = 0 , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result_file locres;
				BOOINIT_RESULT( ::booldog::result_file );
				int pfh = -1;
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
				if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , true , 0 , res_name_or_path.mbchar , res_name_or_path.mblen
					, res_name_or_path.mbsize , name_or_path , 0 , SIZE_MAX , debuginfo ) == false )
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
					int mode = 0;
#ifdef __WINDOWS__
                                        if(file_mode & ::booldog::enums::io::file_mode_tmpfile)
                                        {
                                            mode |= O_TMPFILE;
                                            mode |= ::booldog::enums::io::CREAT;
                                        }
                                        else if(file_mode & ::booldog::enums::io::file_mode_create)
                                            mode |= ::booldog::enums::io::CREAT;
#else
                                        if(file_mode & ::booldog::enums::io::file_mode_tmpfile)
                                            mode |= O_TMPFILE;
                                        else if(file_mode & ::booldog::enums::io::file_mode_create)
                                            mode |= ::booldog::enums::io::CREAT;
                                        if(file_mode & ::booldog::enums::io::file_mode_nobuffering)
                                            mode |= O_SYNC;
#endif
					if( ( file_mode & ::booldog::enums::io::file_mode_read )
						&& ( file_mode & ::booldog::enums::io::file_mode_write ) )
					{
						mode |= ::booldog::enums::io::RDWR;
						if( file_mode & ::booldog::enums::io::file_mode_append )
							mode |= ::booldog::enums::io::APPEND;
						if( file_mode & ::booldog::enums::io::file_mode_truncate )
							mode |= ::booldog::enums::io::TRUNC;
					}
					else if( file_mode & ::booldog::enums::io::file_mode_write )
					{
						mode |= ::booldog::enums::io::WRONLY;
						if( file_mode & ::booldog::enums::io::file_mode_append )
							mode |= ::booldog::enums::io::APPEND;
						if( file_mode & ::booldog::enums::io::file_mode_truncate )
							mode |= ::booldog::enums::io::TRUNC;
					}
					else
					{
						if( file_mode & ::booldog::enums::io::file_mode_create )
						{
							mode |= ::booldog::enums::io::WRONLY;
							if( file_mode & ::booldog::enums::io::file_mode_append )
								mode |= ::booldog::enums::io::APPEND;
							if( file_mode & ::booldog::enums::io::file_mode_truncate )
								mode |= ::booldog::enums::io::TRUNC;
						}
						else
							mode |= ::booldog::enums::io::RDONLY;
                                        }
#ifdef __WINDOWS__
					_sopen_s( &pfh , res_name_or_path.mbchar , mode , _SH_DENYNO , _S_IREAD | _S_IWRITE );
#else
					pfh = ::open( res_name_or_path.mbchar , mode , S_IRUSR | S_IWUSR );
#endif
					if( pfh != -1 )
						goto goto_return;
					else
						res->seterrno();
				}
				else
				{
					::booldog::result_mbchar res_root_dir( allocator );

					if(settings[ 1 ].type != ::booldog::enums::param::type_not_found 
						&& settings[ 1 ].pcharvalue)
					{
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , SIZE_MAX , res_root_dir.mbchar , res_root_dir.mblen 
							, res_root_dir.mbsize , settings[ 1 ].pcharvalue , 0 , SIZE_MAX , debuginfo ) == false )
						{
							res->copy( res_root_dir );
							goto goto_return;							
						}
					}
					else if(settings[ 2 ].type != ::booldog::enums::param::type_not_found 
						&& settings[ 2 ].pwcharvalue)
					{
						if( ::booldog::utils::string::wcs::tombs( &res_root_dir , allocator , settings[ 2 ].pwcharvalue , 0 , SIZE_MAX 
							, debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;							
						}
					}
					else
					{
						if(settings[3].type != ::booldog::enums::param::type_not_found && settings[3].boolvalue)
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
								if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
									, res_root_dir.mblen , res_root_dir.mbsize , &::booldog::io::mbs::slash , 0
									, 1 , debuginfo ) == false )
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
							if( mbsopen( res , allocator , res_root_dir.mbchar , file_mode , 0 , debuginfo ) )
								goto goto_return;
						}
					}
					if( res_root_dir.mbchar )
					{
						res_root_dir.mbchar[ res_root_dir_mblen ] = 0;
						res_root_dir.mblen = res_root_dir_mblen;
						if( res_root_dir_mblen )
						{
							if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
								, res_root_dir.mblen , res_root_dir.mbsize , &::booldog::io::mbs::slash , 0
								, 1 , debuginfo ) == false )
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
						if( mbsopen( res , allocator , res_root_dir.mbchar , file_mode  , 0 , debuginfo ) )
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
						int mode = 0;
						if( file_mode & ::booldog::enums::io::file_mode_create )
							mode |= ::booldog::enums::io::CREAT;
						if( ( file_mode & ::booldog::enums::io::file_mode_read )
							&& ( file_mode & ::booldog::enums::io::file_mode_write ) )
						{
							mode |= ::booldog::enums::io::RDWR;
							if( file_mode & ::booldog::enums::io::file_mode_append )
								mode |= ::booldog::enums::io::APPEND;
							if( file_mode & ::booldog::enums::io::file_mode_truncate )
								mode |= ::booldog::enums::io::TRUNC;
						}
						else if( file_mode & ::booldog::enums::io::file_mode_write )
						{
							mode |= ::booldog::enums::io::WRONLY;
							if( file_mode & ::booldog::enums::io::file_mode_append )
								mode |= ::booldog::enums::io::APPEND;
							if( file_mode & ::booldog::enums::io::file_mode_truncate )
								mode |= ::booldog::enums::io::TRUNC;
						}
						else
						{
							if( file_mode & ::booldog::enums::io::file_mode_create )
							{
								mode |= ::booldog::enums::io::WRONLY;
								if( file_mode & ::booldog::enums::io::file_mode_append )
									mode |= ::booldog::enums::io::APPEND;
								if( file_mode & ::booldog::enums::io::file_mode_truncate )
									mode |= ::booldog::enums::io::TRUNC;
							}
							else
								mode |= ::booldog::enums::io::RDONLY;
						}
#ifdef __WINDOWS__
						_sopen_s( &pfh , res_name_or_path.mbchar , mode , _SH_DENYNO , _S_IREAD | _S_IWRITE );
#else
						pfh = ::open( res_name_or_path.mbchar , mode , S_IRUSR | S_IWUSR );
#endif
						if( pfh != -1 )
							goto goto_return;
						else
							res->seterrno();
					}
				}
	goto_return:
				if( res->file == 0 && pfh != -1 )
				{
					res->file = allocator->create< ::booldog::io::file >( allocator , pfh , file_mode );
					if( res->file == 0 )
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
				}
				return res->succeeded();
                        }
			static bool mbsopen( ::booldog::result_file* pres , booldog::allocator* allocator , const char* name_or_path 
				, int file_mode	, const char* search_path , bool exedir_as_root_path 
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				booldog::param search_paths_params[] =
				{
					BOOPARAM_PCHAR( search_path ) ,
					BOOPARAM_NONE
				};
				booldog::named_param load_params[] =
				{
					BOONAMED_PARAM_PPARAM( "search_paths" , search_paths_params ) ,
					BOONAMED_PARAM_BOOL( "exedir_as_root_path" , exedir_as_root_path ) ,
					BOONAMED_PARAM_NONE
				};
				return ::booldog::io::file::mbsopen( pres , allocator , name_or_path , file_mode , load_params );
                        }
			bool close( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
				if( _close( _file ) == -1 )
#else
				if( ::close( _file ) == -1 )
#endif
					res->seterrno();
				_allocator->destroy( this );
				return res->succeeded();
                        }
			bool write(::booldog::result* pres, ::booldog::byte* buffer, size_t buffer_size, size_t portion_size, size_t& written
				, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				debuginfo = debuginfo;
				::booldog::result locres;
				BOOINIT_RESULT(::booldog::result);
				written = 0;
#ifdef __WINDOWS__
				int writeres = 0;
#else
				ssize_t writeres = 0;
#endif
				if(portion_size > buffer_size)
					portion_size = buffer_size;
                                for(;;)
				{
					if(buffer_size == written)
						break;
					else if(portion_size > buffer_size - written)
						portion_size = buffer_size - written;
#ifdef __WINDOWS__
					writeres = _write(_file, &buffer[written], (unsigned int)portion_size);
#else
					writeres = ::write(_file, &buffer[written], portion_size);
#endif
					if(writeres == -1)
					{
						res->seterrno();
						break;
					}
					written += writeres;
				}
				return res->succeeded();
                        }
			bool read( ::booldog::result_buffer* pres , booldog::allocator* allocator
				, size_t portionsize , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result_buffer locres( allocator );
				BOOINIT_RESULT( ::booldog::result_buffer );
#ifdef __WINDOWS__
				int readres = 0;
#else
				ssize_t readres = 0;
#endif
				if( res->bufsize < portionsize )
				{
					res->bufsize = portionsize;
					res->buf = res->allocator->realloc_array< unsigned char >( res->buf , res->bufsize , debuginfo );
					if( res->buf == 0 )
					{
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						goto goto_return;
					}
				}
#ifdef __WINDOWS__
				readres = _read( _file , res->buf , (unsigned int)portionsize );
#else
				readres = ::read( _file , res->buf , portionsize );
#endif
				if( readres == -1 )
				{
					res->seterrno();
					goto goto_return;
				}
				res->bufdatasize = readres;
goto_return:
				return res->succeeded();
                        }
			bool position( ::booldog::result_int64* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				::booldog::result_int64 locres;
				BOOINIT_RESULT( ::booldog::result_int64 );
#ifdef __WINDOWS__
				res->int64res = _telli64( _file ); 
				if( res->int64res == -1 )
#else
				off64_t pos = lseek64( _file , 0 , SEEK_CUR );
				if( pos != (off64_t)-1 )
					res->int64res = pos;
				else
#endif
					res->seterrno();
				return res->succeeded();
                        }
			bool position( ::booldog::result* pres , ::booldog::int64 offset , ::booldog::enums::io::file_position_origin origin
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				::booldog::result locres;
                                BOOINIT_RESULT(::booldog::result);
#ifdef __WINDOWS__
                            if( _lseeki64( _file , offset , origin ) == -1 )
#else
                            if( lseek64( _file , (off64_t)offset , origin ) == (off64_t)-1 )
#endif
                                    res->seterrno();
				return res->succeeded();
                        }
                        bool flush(::booldog::result* pres, const ::booldog::debug::info& debuginfo = debuginfo_macros)
                        {
                            debuginfo = debuginfo;
                            ::booldog::result locres;
                            BOOINIT_RESULT(::booldog::result);
#ifdef __WINDOWS__
                            if(FlushFileBuffers((HANDLE)_file) == 0)
                            {
                                res->GetLastError();
                                return false;
                            }
#else
                            if(fdatasync(_file) == -1)
                            {
                                res->seterrno();
                                return false;
                            }
#endif
                            return true;
                        }
			template< size_t step >
			bool readline( ::booldog::result_buffer* pres , booldog::allocator* allocator
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result_buffer locres( allocator );
				BOOINIT_RESULT( ::booldog::result_buffer );
				::booldog::result_size resindexof;
#ifdef __WINDOWS__
				int readres = 0;
#else
				ssize_t readres = 0;
#endif
				for( ; ; )
				{
					if( res->bufsize == res->bufdatasize )
					{
						res->bufsize += step;
						res->buf = res->allocator->realloc_array< unsigned char >( res->buf , res->bufsize , debuginfo );
						if( res->buf == 0 )
						{
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							break;
						}
					}
					size_t offset = res->bufdatasize;
#ifdef __WINDOWS__
					readres = _read( _file , &res->buf[ offset ] , (unsigned int)( res->bufsize - offset ) );
#else
					readres = ::read( _file , &res->buf[ offset ] , res->bufsize - offset );
#endif
					if( readres == -1 )
					{
						res->seterrno();
						break;
					}
					if( readres == 0 )
						break;
					res->bufdatasize += readres;
					::booldog::utils::string::mbs::indexof( &resindexof , false , (char*)res->buf
						, offset , res->bufdatasize - offset , "\n" , 0 , 1 , debuginfo );
					if( resindexof.sres != SIZE_MAX )
					{
						offset += resindexof.sres;
						if( res->bufdatasize != offset )
						{
							::booldog::result resres;
							if( position( &resres , -1 * (::booldog::int64)( res->bufdatasize - offset - 1 )
								, ::booldog::enums::io::file_position_origin_curpos , debuginfo ) == false )
							{
								res->copy( resres );
								break;
							}
						}

						res->bufdatasize = offset;
						res->buf[ res->bufdatasize ] = 0;
						break;
					}
				}
				return res->succeeded();
			};

			template< size_t step >
			bool readall( ::booldog::result_buffer* pres , booldog::allocator* allocator
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result_buffer locres( allocator );
				BOOINIT_RESULT( ::booldog::result_buffer );
#ifdef __WINDOWS__
				int readres = 0;
#else
				ssize_t readres = 0;
#endif
				for( ; ; )
				{
					if( res->bufsize == res->bufdatasize )
					{
						res->bufsize += step;
						res->buf = res->allocator->realloc_array< unsigned char >( res->buf , res->bufsize , debuginfo );
						if( res->buf == 0 )
						{
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							break;
						}
					}
#ifdef __WINDOWS__
					readres = _read( _file , &res->buf[ res->bufdatasize ] , (unsigned int)( res->bufsize - res->bufdatasize ) );
#else
					readres = ::read( _file , &res->buf[ res->bufdatasize ] , res->bufsize - res->bufdatasize );
#endif
					if( readres == -1 )
					{
						res->seterrno();
						break;
					}
					if( readres == 0 )
						break;
					res->bufdatasize += readres;
				}
				return res->succeeded();
			};
		};
	};
};
#endif
