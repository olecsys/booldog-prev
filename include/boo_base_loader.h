#ifndef BOO_BASE_LOADER_H
#define BOO_BASE_LOADER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_base_module.h>
#include <boo_array.h>
#include <boo_result.h>
#include <boo_param.h>
#include <boo_stack_allocator.h>
#include <boo_rdwrlock.h>
#include <boo_io_utils.h>
#include <boo_module_utils.h>
#include <boo_string_utils.h>
#ifdef __UNIX__
#include <dlfcn.h>
#include <link.h>
#include <limits.h>
#endif
namespace booldog
{
	class result_module : public ::booldog::result
	{
	private:
		result_module( const ::booldog::result& )
		{
		};
		result_module( const ::booldog::result_module& )
		{
		};
		::booldog::result_module& operator = ( const ::booldog::result_module& )
		{
			return *this;
		};
	public:
		::booldog::base::module* module;
		result_module( void )
		{
			module = 0;
		};
		virtual ~result_module( void )
		{
		};
		virtual void clear( void ) const
		{
			::booldog::result_module* _obj_ = const_cast< ::booldog::result_module* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			_obj_->module = 0;
		};
	};
	namespace base
	{
		class loader
		{
		public:
			virtual bool utf8load( ::booldog::result_module* pres , booldog::allocator* allocator , const char* name_or_path , ::booldog::named_param* named_params = 0 , const ::booldog::debug::info& debuginfo = debuginfo_macros ) = 0;
			virtual bool mbsload( ::booldog::result_module* pres , booldog::allocator* allocator , const char* name_or_path , ::booldog::named_param* named_params = 0 , const ::booldog::debug::info& debuginfo = debuginfo_macros ) = 0;
			virtual bool wcsload( ::booldog::result_module* pres , booldog::allocator* allocator , const wchar_t* name_or_path , ::booldog::named_param* named_params = 0 , const ::booldog::debug::info& debuginfo = debuginfo_macros ) = 0;
			virtual bool unload( ::booldog::result* pres , ::booldog::base::module* module , const ::booldog::debug::info& debuginfo = debuginfo_macros ) = 0;
		};
	};
	class loader : public ::booldog::base::loader
	{
		booldog::allocator* _allocator;
		booldog::threading::rdwrlock _lock;
		booldog::array< booldog::module* > _modules;
#ifdef __UNIX__
		booldog::threading::rdwrlock _lock_loaded_dirs;
		booldog::array< char* > _loaded_dirs;
#endif
	private:
#ifdef __WINDOWS__
		booinline bool get_loaded_module( ::booldog::result_module* pres , const wchar_t* res_name_or_path 
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			::booldog::module_handle module_handle = 0;
			if( GetModuleHandleExW( 0 , res_name_or_path , &module_handle ) )
#else
		booinline bool get_loaded_module( ::booldog::result_module* pres , const char* res_name_or_path 
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			char* dl_error = 0;
			::booldog::module_handle module_handle = dlopen( res_name_or_path , RTLD_NOLOAD | RTLD_NOW | RTLD_GLOBAL );
			if( module_handle )
#endif
			{
				::booldog::module* module = 0;
				_lock.wlock( debuginfo );
				for( size_t index0 = 0 ; index0 < _modules.count() ; index0++ )
				{
					if( _modules[ index0 ]->handle() == module_handle )
					{
						module = _modules[ index0 ];
						module->addref();
						break;
					}
				}
				if( module == 0 )
				{
					module = _allocator->create< ::booldog::module >( debuginfo );
					module->_handle = module_handle;
					_modules.add( module , debuginfo );
				}
				_lock.wunlock( debuginfo );
				pres->clear();
				pres->module = module;
				return true;
			}
			return false;
		};
	public:
		loader( booldog::allocator* allocator )
			: _modules( allocator )
#ifdef __UNIX__
			, _loaded_dirs( allocator )
#endif
		{
			_allocator = allocator;
		};
		~loader( void )
		{
#ifdef __UNIX__
			_lock_loaded_dirs.wlock( debuginfo_macros );
			for( size_t index0 = 0 ; index0 < _loaded_dirs.count() ; index0++ )
				_allocator->free( _loaded_dirs[ index0 ] );
			_lock_loaded_dirs.wunlock( debuginfo_macros );
#endif
		};
		virtual bool utf8load( ::booldog::result_module* pres , booldog::allocator* allocator , const char* name_or_path 
			, ::booldog::named_param* named_params = 0 , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			::booldog::result_module locres;
			BOOINIT_RESULT( ::booldog::result_module );
			
			return res->succeeded();
		};
		virtual bool mbsload( ::booldog::result_module* pres , booldog::allocator* allocator , const char* name_or_path 
			, ::booldog::named_param* named_params = 0 , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			::booldog::result_module locres;
			BOOINIT_RESULT( ::booldog::result_module );
#ifdef __WINDOWS__
			::booldog::result_wchar reswchar( allocator );
			if( ::booldog::utils::string::mbs::towcs( &reswchar , allocator , name_or_path , 0 , SIZE_MAX , debuginfo ) )
				wcsload( res , allocator , reswchar.wchar , named_params , debuginfo );
			else
				res->copy( reswchar );
#else
			bool locked = false;
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
			if( ::booldog::utils::string::mbs::insert( &resres , 0 , res_name_or_path.mbchar , res_name_or_path.mblen
				, res_name_or_path.mbsize , name_or_path , 0 , SIZE_MAX , allocator , debuginfo ) == false )
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
				::booldog::module_handle module_handle = 0;				

				if( get_loaded_module( res , res_name_or_path.mbchar , debuginfo ) )
					goto goto_return;
				module_handle = dlopen( res_name_or_path.mbchar , RTLD_NOW | RTLD_GLOBAL );
				if( module_handle )
				{
					::booldog::result_mbchar resdirmbchar( _allocator );
					if( ::booldog::utils::io::path::mbs::directory( &resdirmbchar , res_name_or_path.mbchar , 0 , SIZE_MAX , _allocator , debuginfo ) )
					{
						::booldog::module* module = 0;
						_lock.wlock( debuginfo );
						for( size_t index0 = 0 ; index0 < _modules.count() ; index0++ )
						{
							if( _modules[ index0 ]->handle() == module_handle )
							{
								module = _modules[ index0 ];
								module->addref();
								break;
							}
						}
						if( module == 0 )
						{
							module = _allocator->create< ::booldog::module >( debuginfo );
							module->_handle = module_handle;
							_modules.add( module , debuginfo );
						}
						_lock.wunlock( debuginfo );
						res->clear();
						res->module = module;						

						bool found = false;
						_lock_loaded_dirs.wlock( debuginfo );
						for( size_t index0 = 0 ; index0 < _loaded_dirs.count() ; index0++ )
						{
							if( strcmp( resdirmbchar.mbchar , _loaded_dirs[ index0 ] ) == 0 )
							{
								found = true;
								break;
							}
						}
						if( found == false )
							_loaded_dirs.add( resdirmbchar.detach() );
						_lock_loaded_dirs.wunlock( debuginfo );
					}
					else
					{
						res->copy( resdirmbchar );
						dlclose( module_handle );
					}
					goto goto_return;
				}
				else
					res->setdlerror( allocator , dlerror() , debuginfo );
			}
			else
			{
				::booldog::result_mbchar res_root_dir( allocator );

				if( settings[ 1 ].type != ::booldog::enums::param::type_not_found )
				{
					if( ::booldog::utils::string::mbs::insert( &resres , SIZE_MAX , res_root_dir.mbchar , res_root_dir.mblen 
						, res_root_dir.mbsize , settings[ 1 ].pcharvalue , 0 , SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( res_root_dir );
						goto goto_return;							
					}
				}
				else if( settings[ 2 ].type != ::booldog::enums::param::type_not_found )
				{
					if( ::booldog::utils::string::wcs::tombs( &res_root_dir , settings[ 2 ].pwcharvalue , 0 , SIZE_MAX 
						, allocator , debuginfo ) == false )
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
							if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
								, res_root_dir.mblen , res_root_dir.mbsize , &::booldog::io::mbs::slash , 0
								, 1 , allocator , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pchar )
						{
							if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
								, res_root_dir.mblen , res_root_dir.mbsize , settings[ 0 ].pparamvalue[ index ].pcharvalue , 0
								, SIZE_MAX , allocator , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						else if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pwchar )
						{
							if( ::booldog::utils::string::wcs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
								, res_root_dir.mblen , res_root_dir.mbsize , settings[ 0 ].pparamvalue[ index ].pwcharvalue , 0
								, SIZE_MAX , allocator , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						else
							continue;
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , &::booldog::io::mbs::slash , 0
							, 1 , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						size_t res_dir_mblen = res_root_dir.mblen;
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( mbsload( res , res_root_dir.mbchar , 0 , allocator , debuginfo ) )
							goto goto_return;

						res_root_dir.mbchar[ res_dir_mblen ] = 0;
						res_root_dir.mblen = res_dir_mblen;
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , ".so" , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( mbsload( res , res_root_dir.mbchar , 0 , allocator , debuginfo ) )
							goto goto_return;

						res_root_dir.mbchar[ res_dir_mblen ] = 0;
						res_root_dir.mblen = res_dir_mblen;
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , "lib" , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( mbsload( res , res_root_dir.mbchar , 0 , allocator , debuginfo ) )
							goto goto_return;

						res_root_dir.mbchar[ res_dir_mblen ] = 0;
						res_root_dir.mblen = res_dir_mblen;
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , "lib" , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , ".so" , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( mbsload( res , res_root_dir.mbchar , 0 , allocator , debuginfo ) )
							goto goto_return;
					}
				}
				if( res_root_dir.mbchar )
				{
					res_root_dir.mbchar[ res_root_dir_mblen ] = 0;
					res_root_dir.mblen = res_root_dir_mblen;
					if( res_root_dir_mblen )
					{
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , &::booldog::io::mbs::slash , 0
							, 1 , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
					}
					size_t res_dir_mblen = res_root_dir.mblen;
					if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( mbsload( res , res_root_dir.mbchar , 0 , allocator , debuginfo ) )
						goto goto_return;

					res_root_dir.mbchar[ res_dir_mblen ] = 0;
					res_root_dir.mblen = res_dir_mblen;
					if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , ".so" , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( mbsload( res , res_root_dir.mbchar , 0 , allocator , debuginfo ) )
						goto goto_return;

					res_root_dir.mbchar[ res_dir_mblen ] = 0;
					res_root_dir.mblen = res_dir_mblen;
					if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , "lib" , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( mbsload( res , res_root_dir.mbchar , 0 , allocator , debuginfo ) )
						goto goto_return;

					res_root_dir.mbchar[ res_dir_mblen ] = 0;
					res_root_dir.mblen = res_dir_mblen;
					if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , "lib" , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , ".so" , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( mbsload( res , res_root_dir.mbchar , 0 , allocator , debuginfo ) )
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
					
					_lock_loaded_dirs.rlock( debuginfo );
					for( size_t index0 = 0 ; index0 < _loaded_dirs.count() ; index0++ )
					{
						if( res_root_dir.mbchar )
						{
							res_root_dir.mbchar[ 0 ] = 0;
							res_root_dir.mblen = 0;
						}
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , _loaded_dirs[ index0 ] , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , &::booldog::io::mbs::slash , 0
							, 1 , allocator , debuginfo ) == false )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							res->copy( resres );
							goto goto_return;
						}
						res_root_dir_mblen = res_root_dir.mblen;
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							res->copy( resres );
							goto goto_return;
						}
						if( get_loaded_module( res , res_root_dir.mbchar , debuginfo ) )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							goto goto_return;
						}
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , ".so" , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							res->copy( resres );
							goto goto_return;
						}
						if( get_loaded_module( res , res_root_dir.mbchar , debuginfo ) )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							goto goto_return;
						}
						res_root_dir.mbchar[ res_root_dir_mblen ] = 0;
						res_root_dir.mblen = res_root_dir_mblen;
					
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , "lib" , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							res->copy( resres );
							goto goto_return;
						}
						if( get_loaded_module( res , res_root_dir.mbchar , debuginfo ) )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							goto goto_return;
						}
						if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , ".so" , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							res->copy( resres );
							goto goto_return;
						}
						if( get_loaded_module( res , res_root_dir.mbchar , debuginfo ) )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							goto goto_return;
						}
					}
					_lock_loaded_dirs.runlock( debuginfo );

					::booldog::module_handle module_handle = dlopen( res_name_or_path.mbchar , RTLD_NOW | RTLD_GLOBAL );
					if( module_handle )
						goto goto_loaded_module;
					else
						res->setdlerror( allocator , dlerror() , debuginfo );
					res_root_dir_mblen = res_name_or_path.mblen;
					if( ::booldog::utils::string::mbs::insert( &resres , res_name_or_path.mblen , res_name_or_path.mbchar 
						, res_name_or_path.mblen , res_name_or_path.mbsize , ".so" , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					module_handle = dlopen( res_name_or_path.mbchar , RTLD_NOW | RTLD_GLOBAL );
					if( module_handle )
						goto goto_loaded_module;
					else
						res->setdlerror( allocator , dlerror() , debuginfo );
					res_name_or_path.mbchar[ res_root_dir_mblen ] = 0;
					res_name_or_path.mblen = res_root_dir_mblen;
					
					if( ::booldog::utils::string::mbs::insert( &resres , 0 , res_name_or_path.mbchar 
						, res_name_or_path.mblen , res_name_or_path.mbsize , "lib" , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					module_handle = dlopen( res_name_or_path.mbchar , RTLD_NOW | RTLD_GLOBAL );
					if( module_handle )
						goto goto_loaded_module;
					else
						res->setdlerror( allocator , dlerror() , debuginfo );
					if( ::booldog::utils::string::mbs::insert( &resres , res_name_or_path.mblen , res_name_or_path.mbchar 
						, res_name_or_path.mblen , res_name_or_path.mbsize , ".so" , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					module_handle = dlopen( res_name_or_path.mbchar , RTLD_NOW | RTLD_GLOBAL );
					if( module_handle )
						goto goto_loaded_module;
					else
						res->setdlerror( allocator , dlerror() , debuginfo );
					goto goto_return;
goto_loaded_module:
					struct link_map *map = 0;
					if( dlinfo( module_handle , RTLD_DI_LINKMAP , &map ) != -1 )
					{
						::booldog::result_mbchar resdirmbchar( _allocator );
						if( ::booldog::utils::io::path::mbs::directory( &resdirmbchar , map->l_name , 0 , SIZE_MAX 
							, _allocator , debuginfo ) == false )
						{
							res->copy( resres );
							dlclose( module_handle );
							goto goto_return;
						}
						if( ::booldog::utils::io::path::mbs::normalize( &resres , resdirmbchar.mbchar , resdirmbchar.mblen 
							, resdirmbchar.mbsize ) == false )
						{
							res->copy( resres );
							dlclose( module_handle );
							goto goto_return;
						}	
						::booldog::module* module = 0;
						_lock.wlock( debuginfo );
						for( size_t index0 = 0 ; index0 < _modules.count() ; index0++ )
						{
							if( _modules[ index0 ]->handle() == module_handle )
							{
								module = _modules[ index0 ];
								module->addref();
								break;
							}
						}
						if( module == 0 )
						{
							module = _allocator->create< ::booldog::module >( debuginfo );
							module->_handle = module_handle;
							_modules.add( module , debuginfo );
						}
						_lock.wunlock( debuginfo );
						res->clear();
						res->module = module;
						
						bool found = false;
						_lock_loaded_dirs.wlock( debuginfo );
						for( size_t index0 = 0 ; index0 < _loaded_dirs.count() ; index0++ )
						{
							if( strcmp( resdirmbchar.mbchar , _loaded_dirs[ index0 ] ) == 0 )
							{
								found = true;
								break;
							}
						}
						if( found == false )
							_loaded_dirs.add( resdirmbchar.detach() );
						_lock_loaded_dirs.wunlock( debuginfo );
					}
					else
					{
						res->setdlerror( allocator , dlerror() , debuginfo );
						dlclose( module_handle );
					}
				}
			}
goto_return:
			if( locked )
				_lock.wunlock( debuginfo );
#endif
			return res->succeeded();
		};
		virtual bool wcsload( ::booldog::result_module* pres , booldog::allocator* allocator , const wchar_t* name_or_path 
			, ::booldog::named_param* named_params = 0 , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			::booldog::result_module locres;
			BOOINIT_RESULT( ::booldog::result_module );
#ifdef __WINDOWS__
			bool locked = false;
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
			if( ::booldog::utils::string::wcs::insert( &resres , allocator , 0 , res_name_or_path.wchar , res_name_or_path.wlen
				, res_name_or_path.wsize , name_or_path , 0 , SIZE_MAX , debuginfo ) == false )
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
				if( ::booldog::utils::io::path::wcs::normalize( &resres , res_name_or_path.wchar , res_name_or_path.wlen 
					, res_name_or_path.wsize ) == false )
				{
					res->copy( resres );
					goto goto_return;
				}
				::booldog::module_handle module_handle = 0;
				
				if( get_loaded_module( res , res_name_or_path.wchar , debuginfo ) )
					goto goto_return;
				module_handle = LoadLibraryExW( res_name_or_path.wchar , 0 , 0 );
				if( module_handle )
				{
					::booldog::module* module = 0;
					_lock.wlock( debuginfo );
					for( size_t index0 = 0 ; index0 < _modules.count() ; index0++ )
					{
						if( _modules[ index0 ]->handle() == module_handle )
						{
							module = _modules[ index0 ];
							module->addref();
							break;
						}
					}
					if( module == 0 )
					{
						module = _allocator->create< ::booldog::module >( debuginfo );
						module->_handle = module_handle;
						_modules.add( module , debuginfo );
					}
					_lock.wunlock( debuginfo );
					res->clear();
					res->module = module;
					goto goto_return;
				}
				else
					res->GetLastError();
			}
			else
			{
				::booldog::result_wchar res_root_dir( allocator );

				if( settings[ 1 ].type != ::booldog::enums::param::type_not_found )
				{
					if( ::booldog::utils::string::mbs::towcs( &res_root_dir , allocator , settings[ 1 ].pcharvalue , 0 , SIZE_MAX 
						, debuginfo ) == false )
					{
						res->copy( res_root_dir );
						goto goto_return;							
					}
				}
				else if( settings[ 2 ].type != ::booldog::enums::param::type_not_found )
				{
					if( ::booldog::utils::string::wcs::insert( &resres , allocator , SIZE_MAX , res_root_dir.wchar , res_root_dir.wlen 
						, res_root_dir.wsize , settings[ 2 ].pwcharvalue , 0 , SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;							
					}
				}
				else
				{
					if( settings[ 3 ].type != ::booldog::enums::param::type_not_found && settings[ 3 ].boolvalue )
					{
						if( ::booldog::utils::executable::wcs::directory< 256 >( &res_root_dir , allocator , debuginfo ) == false )
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
					if( ::booldog::utils::io::path::wcs::normalize( &resres , res_root_dir.wchar , res_root_dir.wlen 
						, res_root_dir.wsize ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					res_root_dir_wlen = res_root_dir.wlen;
				}
				if( settings[ 0 ].type != ::booldog::enums::param::type_not_found )
				{
					for( size_t index = 0 ; settings[ 0 ].pparamvalue[ index ].type != ::booldog::enums::param::type_none ; index++ )
					{
						if( res_root_dir.wchar )
						{
							res_root_dir.wchar[ res_root_dir_wlen ] = 0;
							res_root_dir.wlen = res_root_dir_wlen;
						}
						if( res_root_dir_wlen )
						{
							if( ::booldog::utils::string::wcs::insert( &resres , allocator , res_root_dir.wlen , res_root_dir.wchar 
								, res_root_dir.wlen , res_root_dir.wsize , &::booldog::io::wcs::slash , 0
								, 1 , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pchar )
						{
							if( ::booldog::utils::string::mbs::insert( &resres , allocator , res_root_dir.wlen , res_root_dir.wchar 
								, res_root_dir.wlen , res_root_dir.wsize , settings[ 0 ].pparamvalue[ index ].pcharvalue , 0
								, SIZE_MAX , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						else if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pwchar )
						{
							if( ::booldog::utils::string::wcs::insert( &resres , allocator , res_root_dir.wlen , res_root_dir.wchar 
								, res_root_dir.wlen , res_root_dir.wsize , settings[ 0 ].pparamvalue[ index ].pwcharvalue , 0
								, SIZE_MAX , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						else
							continue;
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , &::booldog::io::wcs::slash , 0
							, 1 , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						size_t res_dir_wlen = res_root_dir.wlen;
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , res_name_or_path.wchar , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( wcsload( res , allocator , res_root_dir.wchar , 0 , debuginfo ) )
							goto goto_return;

						res_root_dir.wchar[ res_dir_wlen ] = 0;
						res_root_dir.wlen = res_dir_wlen;
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , L"lib" , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , res_name_or_path.wchar , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( wcsload( res , allocator , res_root_dir.wchar , 0 , debuginfo ) )
							goto goto_return;
					}
				}
				if( res_root_dir.wchar )
				{
					res_root_dir.wchar[ res_root_dir_wlen ] = 0;
					res_root_dir.wlen = res_root_dir_wlen;
					if( res_root_dir_wlen )
					{
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , &::booldog::io::wcs::slash , 0
							, 1 , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
					}
					size_t res_dir_wlen = res_root_dir.wlen;
					if( ::booldog::utils::string::wcs::insert( &resres , allocator , res_root_dir.wlen , res_root_dir.wchar 
						, res_root_dir.wlen , res_root_dir.wsize , res_name_or_path.wchar , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( wcsload( res , allocator , res_root_dir.wchar , 0 , debuginfo ) )
						goto goto_return;

					res_root_dir.wchar[ res_dir_wlen ] = 0;
					res_root_dir.wlen = res_dir_wlen;
					if( ::booldog::utils::string::wcs::insert( &resres , allocator , res_root_dir.wlen , res_root_dir.wchar 
						, res_root_dir.wlen , res_root_dir.wsize , L"lib" , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( ::booldog::utils::string::wcs::insert( &resres , allocator , res_root_dir.wlen , res_root_dir.wchar 
						, res_root_dir.wlen , res_root_dir.wsize , res_name_or_path.wchar , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( wcsload( res , allocator , res_root_dir.wchar , 0 , debuginfo ) )
						goto goto_return;
				}
				else
				{
					if( ::booldog::utils::io::path::wcs::normalize( &resres , res_name_or_path.wchar , res_name_or_path.wlen 
						, res_name_or_path.wsize ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					::booldog::module_handle module_handle = 0;
					
					if( get_loaded_module( res , res_name_or_path.wchar , debuginfo ) )
						goto goto_return;
					module_handle = LoadLibraryExW( res_name_or_path.wchar , 0 , 0 );
					if( module_handle )
					{
						::booldog::module* module = 0;
						_lock.wlock( debuginfo );
						for( size_t index0 = 0 ; index0 < _modules.count() ; index0++ )
						{
							if( _modules[ index0 ]->handle() == module_handle )
							{
								module = _modules[ index0 ];
								module->addref();
								break;
							}
						}
						if( module == 0 )
						{
							module = _allocator->create< ::booldog::module >( debuginfo );
							module->_handle = module_handle;
							_modules.add( module , debuginfo );
						}
						_lock.wunlock( debuginfo );
						res->clear();
						res->module = module;
						goto goto_return;
					}
					else
						res->GetLastError();

					if( ::booldog::utils::string::wcs::insert( &resres , allocator , res_root_dir.wlen , res_root_dir.wchar 
						, res_root_dir.wlen , res_root_dir.wsize , L"lib" , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( get_loaded_module( res , res_name_or_path.wchar , debuginfo ) )
						goto goto_return;
					module_handle = LoadLibraryExW( res_name_or_path.wchar , 0 , 0 );
					if( module_handle )
					{
						::booldog::module* module = 0;
						_lock.wlock( debuginfo );
						for( size_t index0 = 0 ; index0 < _modules.count() ; index0++ )
						{
							if( _modules[ index0 ]->handle() == module_handle )
							{
								module = _modules[ index0 ];
								module->addref();
								break;
							}
						}
						if( module == 0 )
						{
							module = _allocator->create< ::booldog::module >( debuginfo );
							module->_handle = module_handle;
							_modules.add( module , debuginfo );
						}
						_lock.wunlock( debuginfo );
						res->clear();
						res->module = module;
						goto goto_return;
					}
					else
						res->GetLastError();
				}
			}
goto_return:
			if( locked )
				_lock.wunlock( debuginfo );
#else
			::booldog::result_mbchar resmbchar( allocator );
			if( ::booldog::utils::string::wcs::tombs( &resmbchar , name_or_path , 0 , SIZE_MAX , allocator , debuginfo ) )
				mbsload( res , resmbchar.mbchar , named_params , allocator , debuginfo );
			else
				res->copy( resmbchar );
#endif
			return res->succeeded();
		};
		virtual bool unload( ::booldog::result* pres , ::booldog::base::module* module , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			debuginfo = debuginfo;
			::booldog::result locres;
			BOOINIT_RESULT( ::booldog::result );
			_lock.wlock( debuginfo );
			for( size_t index0 = 0 ; index0 < _modules.count() ; index0++ )
			{
				if( _modules[ index0 ] == module )
				{
					::booldog::module* mod = _modules[ index0 ];
#ifdef __WINDOWS__
					FreeLibrary( mod->_handle );
#else
					dlclose( mod->_handle );
#endif
					if( mod->release() == 0 )
					{						
						_modules.remove( index0 );
						_allocator->destroy< ::booldog::module >( mod );
					}
					goto goto_return;
				}
			}
			res->booerr( ::booldog::enums::result::booerr_type_module_not_found_in_the_list );
goto_return:
			_lock.wunlock( debuginfo );
			return res->succeeded();
		};
	};
};
#endif