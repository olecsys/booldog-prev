#ifndef BOO_IO_FILE_H
#define BOO_IO_FILE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_io_utils.h>
#include <boo_param.h>
#include <boo_string_utils.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef __WINDOWS__
#include <io.h>
#include <share.h>
#else
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
				file_mode_truncate = 16
			};
		};
	};
	namespace io
	{
		class file;
	};
	class result_file : public ::booldog::result
	{
	private:
		result_file( const ::booldog::result& )
		{
		};
		result_file( const ::booldog::result_file& )
		{
		};
		::booldog::result_file& operator = ( const ::booldog::result_file& )
		{
			return *this;
		};
	public:
		::booldog::io::file* file;
		result_file( void )
		{
			file = 0;
		};
		virtual ~result_file( void )
		{
		};
		virtual void clear( void ) const
		{
			::booldog::result_file* _obj_ = const_cast< ::booldog::result_file* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			_obj_->file = 0;
		};
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
			};
			file( ::booldog::allocator* pallocator , int pfh , int file_mode )
				: _allocator( pallocator ) , _file( pfh ) , _file_mode( file_mode )
			{
			};
			file( const ::booldog::io::file& )
			{
			};
			::booldog::io::file& operator = ( const ::booldog::io::file& )
			{
				return *this;
			};
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
				if( ::booldog::utils::string::mbs::insert( &resres , allocator , true , 0 , res_name_or_path.mbchar , res_name_or_path.mblen
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
				else
				{
					::booldog::result_mbchar res_root_dir( allocator );

					if( settings[ 1 ].type != ::booldog::enums::param::type_not_found )
					{
						if( ::booldog::utils::string::mbs::insert( &resres , allocator , false , SIZE_MAX , res_root_dir.mbchar , res_root_dir.mblen 
							, res_root_dir.mbsize , settings[ 1 ].pcharvalue , 0 , SIZE_MAX , debuginfo ) == false )
						{
							res->copy( res_root_dir );
							goto goto_return;							
						}
					}
					else if( settings[ 2 ].type != ::booldog::enums::param::type_not_found )
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
								if( ::booldog::utils::string::mbs::insert( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
									, res_root_dir.mblen , res_root_dir.mbsize , &::booldog::io::mbs::slash , 0
									, 1 , debuginfo ) == false )
								{
									res->copy( resres );
									goto goto_return;
								}
							}
							if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pchar )
							{
								if( ::booldog::utils::string::mbs::insert( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
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
							if( ::booldog::utils::string::mbs::insert( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
								, res_root_dir.mblen , res_root_dir.mbsize , &::booldog::io::mbs::slash , 0
								, 1 , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
							if( ::booldog::utils::string::mbs::insert( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
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
							if( ::booldog::utils::string::mbs::insert( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
								, res_root_dir.mblen , res_root_dir.mbsize , &::booldog::io::mbs::slash , 0
								, 1 , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						if( ::booldog::utils::string::mbs::insert( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
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
			};
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
							res->buf = res->allocator->realloc_array< unsigned char >( res->buf , res->bufsize , debuginfo );
							if( res->buf )
							{
#ifdef __WINDOWS__
								if( _lseek( _file , 0 , SEEK_SET ) == -1 )
#else
								if( lseek( _file , 0 , SEEK_SET ) == (off_t)-1 )
#endif								
								{
									res->seterrno();
									break;
								}
							}
							else
							{
								res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
								break;
							}
						}
					}
#ifdef __WINDOWS__
					readres = _read( _file , &res->buf[ res->bufdatasize ] , (unsigned int)( res->bufsize - res->bufdatasize ) );
#else
					readres = read( _file , &res->buf[ res->bufdatasize ] , res->bufsize - res->bufdatasize );
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