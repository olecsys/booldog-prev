#ifndef BOO_BASE_LOADER_H
#define BOO_BASE_LOADER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_base_module.h>
#include <boo_array.h>
#include <boo_result.h>
#include <boo_param.h>
#include <boo_stack.h>
#include <boo_rdwrlock.h>
#include <boo_io_utils.h>
#include <boo_module_utils.h>
#include <boo_string_utils.h>
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
		~result_module( void )
		{
		};
		virtual void clear( void ) const
		{
			::booldog::result_module* _obj_ = const_cast< ::booldog::result_module* >( this );
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			_obj_->module = 0;
		};
	};
	namespace base
	{
		class loader
		{
		public:
			virtual bool utf8load( ::booldog::result_module* pres , const char* name_or_path , ::booldog::named_param* named_params = 0 , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 ) = 0;
			virtual bool mbload( ::booldog::result_module* pres , const char* name_or_path , ::booldog::named_param* named_params = 0 , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 ) = 0;
			virtual bool wcsload( ::booldog::result_module* pres , const wchar_t* name_or_path , ::booldog::named_param* named_params = 0 , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 ) = 0;
			virtual bool unload( ::booldog::result* pres , ::booldog::base::module* module , ::booldog::debug::info* debuginfo = 0 ) = 0;
			//virtual void utf8add_search_path( const char* path , ::booldog::named_param* named_params = 0 ) = 0;
			//virtual void mbadd_search_path( const char* path , ::booldog::named_param* named_params = 0 ) = 0;
			//virtual void wcsadd_search_path( const wchar_t* path , ::booldog::named_param* named_params = 0 ) = 0;
		};
	};
	booldog::base::loader* _loader = 0;
	class loader : public ::booldog::base::loader
	{
		booldog::allocator* _allocator;
		booldog::threading::rdwrlock _lock;
		booldog::array< booldog::module* > _modules;
	public:
		loader( booldog::allocator* allocator = ::booldog::_allocator )
		{
			_allocator = allocator;
		};
		virtual bool utf8load( ::booldog::result_module* pres , const char* name_or_path , ::booldog::named_param* named_params = 0 
			, booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
		{
			::booldog::result_module locres;
			BOOINIT_RESULT( ::booldog::result_module );
			
			return res->succeeded();
		};
		virtual bool mbload( ::booldog::result_module* pres , const char* name_or_path , ::booldog::named_param* named_params = 0
			, booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
		{
			::booldog::result_module locres;
			BOOINIT_RESULT( ::booldog::result_module );
#ifdef __WINDOWS__
			::booldog::result_wchar reswchar( allocator );
			if( ::booldog::utils::string::mbs::towcs( &reswchar , name_or_path , 0 , SIZE_MAX , allocator , debuginfo ) )
				wcsload( res , reswchar.wchar , named_params , allocator , debuginfo );
			else
				res->copy( reswchar );
#else
#endif
			return res->succeeded();
		};
		virtual bool wcsload( ::booldog::result_module* pres , const wchar_t* name_or_path , ::booldog::named_param* named_params = 0 
			, booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
		{
			::booldog::result_module locres;
			BOOINIT_RESULT( ::booldog::result_module );
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
			if( ::booldog::utils::string::wcs::insert( &resres , 0 , res_name_or_path.wchar , res_name_or_path.wlen
				, res_name_or_path.wsize , name_or_path , 0 , SIZE_MAX , allocator , debuginfo ) == false )
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
				_lock.wlock( debuginfo );
				if( GetModuleHandleExW( 0 , res_name_or_path.wchar , &module_handle ) )
				{
					::booldog::module* module = 0;
					for( size_t index0 = 0 ; index0 < _modules.count() ; index0++ )
					{
						if( _modules[ index0 ]->handle() == module_handle )
						{
							module = _modules[ index0 ];
							module->addref();
							goto goto_step0_and_return;
						}
					}
					module = _allocator->create< ::booldog::module >( debuginfo );
					module->_handle = module_handle;
goto_step0_and_return:
					res->module = module;
					_lock.wunlock( debuginfo );
					goto goto_return;
				}
				module_handle = LoadLibraryExW( res_name_or_path.wchar , 0 , 0 );
				if( module_handle )
				{
					::booldog::module* module = _allocator->create< ::booldog::module >( debuginfo );
					module->_handle = module_handle;
					_modules.add( module , debuginfo );
					_lock.wunlock( debuginfo );
					res->module = module;
					goto goto_return;
				}
				else
					res->GetLastError();
				_lock.wunlock( debuginfo );
			}
			else
			{
				::booldog::result_wchar res_root_dir( allocator );

				if( settings[ 1 ].param.type != ::booldog::enums::param::type_not_found )
				{
					if( ::booldog::utils::string::mbs::towcs( &res_root_dir , settings[ 1 ].param.pcharvalue , 0 , SIZE_MAX 
						, allocator , debuginfo ) == false )
					{
						res->copy( res_root_dir );
						goto goto_return;							
					}
				}
				else if( settings[ 2 ].param.type != ::booldog::enums::param::type_not_found )
				{
					if( ::booldog::utils::string::wcs::insert( &resres , SIZE_MAX , res_root_dir.wchar , res_root_dir.wlen 
						, res_root_dir.wsize , settings[ 2 ].param.pwcharvalue , 0 , SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;							
					}
				}
				else
				{
					if( settings[ 3 ].param.type != ::booldog::enums::param::type_not_found && settings[ 3 ].param.boolvalue )
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
				if( settings[ 0 ].param.type != ::booldog::enums::param::type_not_found )
				{
					for( size_t index = 0 ; settings[ 0 ].param.pparamvalue[ index ].type != ::booldog::enums::param::type_none ; index++ )
					{
						if( res_root_dir.wchar )
						{
							res_root_dir.wchar[ res_root_dir_wlen ] = 0;
							res_root_dir.wlen = res_root_dir_wlen;
						}
						if( res_root_dir_wlen )
						{
							if( ::booldog::utils::string::wcs::insert( &resres , res_root_dir.wlen , res_root_dir.wchar 
								, res_root_dir.wlen , res_root_dir.wsize , &::booldog::io::wcs::slash , 0
								, 1 , allocator , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						if( settings[ 0 ].param.pparamvalue[ index ].type == ::booldog::enums::param::type_pchar )
						{
							if( ::booldog::utils::string::mbs::insert( &resres , res_root_dir.wlen , res_root_dir.wchar 
								, res_root_dir.wlen , res_root_dir.wsize , settings[ 0 ].param.pparamvalue[ index ].pcharvalue , 0
								, SIZE_MAX , allocator , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						else if( settings[ 0 ].param.pparamvalue[ index ].type == ::booldog::enums::param::type_pwchar )
						{
							if( ::booldog::utils::string::wcs::insert( &resres , res_root_dir.wlen , res_root_dir.wchar 
								, res_root_dir.wlen , res_root_dir.wsize , settings[ 0 ].param.pparamvalue[ index ].pwcharvalue , 0
								, SIZE_MAX , allocator , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						else
							continue;
						if( ::booldog::utils::string::wcs::insert( &resres , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , &::booldog::io::wcs::slash , 0
							, 1 , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						size_t res_dir_wlen = res_root_dir.wlen;
						if( ::booldog::utils::string::wcs::insert( &resres , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , res_name_or_path.wchar , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( wcsload( res , res_root_dir.wchar , 0 , allocator , debuginfo ) )
							goto goto_return;

						res_root_dir.wchar[ res_dir_wlen ] = 0;
						res_root_dir.wlen = res_dir_wlen;
						if( ::booldog::utils::string::wcs::insert( &resres , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , L"lib" , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::string::wcs::insert( &resres , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , res_name_or_path.wchar , 0
							, SIZE_MAX , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( wcsload( res , res_root_dir.wchar , 0 , allocator , debuginfo ) )
							goto goto_return;
					}
				}
				if( res_root_dir.wchar )
				{
					res_root_dir.wchar[ res_root_dir_wlen ] = 0;
					res_root_dir.wlen = res_root_dir_wlen;
					if( res_root_dir_wlen )
					{
						if( ::booldog::utils::string::wcs::insert( &resres , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , &::booldog::io::wcs::slash , 0
							, 1 , allocator , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
					}
					size_t res_dir_wlen = res_root_dir.wlen;
					if( ::booldog::utils::string::wcs::insert( &resres , res_root_dir.wlen , res_root_dir.wchar 
						, res_root_dir.wlen , res_root_dir.wsize , res_name_or_path.wchar , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( wcsload( res , res_root_dir.wchar , 0 , allocator , debuginfo ) )
						goto goto_return;

					res_root_dir.wchar[ res_dir_wlen ] = 0;
					res_root_dir.wlen = res_dir_wlen;
					if( ::booldog::utils::string::wcs::insert( &resres , res_root_dir.wlen , res_root_dir.wchar 
						, res_root_dir.wlen , res_root_dir.wsize , L"lib" , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( ::booldog::utils::string::wcs::insert( &resres , res_root_dir.wlen , res_root_dir.wchar 
						, res_root_dir.wlen , res_root_dir.wsize , res_name_or_path.wchar , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( wcsload( res , res_root_dir.wchar , 0 , allocator , debuginfo ) )
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
					_lock.wlock( debuginfo );
					if( GetModuleHandleExW( 0 , res_name_or_path.wchar , &module_handle ) )
					{
						::booldog::module* module = 0;
						for( size_t index0 = 0 ; index0 < _modules.count() ; index0++ )
						{
							if( _modules[ index0 ]->handle() == module_handle )
							{
								module = _modules[ index0 ];
								module->addref();
								goto goto_step1_and_return;
							}
						}
						module = _allocator->create< ::booldog::module >( debuginfo );
						module->_handle = module_handle;
	goto_step1_and_return:
						res->module = module;
						_lock.wunlock( debuginfo );
						goto goto_return;
					}
					module_handle = LoadLibraryExW( res_name_or_path.wchar , 0 , 0 );
					if( module_handle )
					{
						::booldog::module* module = _allocator->create< ::booldog::module >( debuginfo );
						module->_handle = module_handle;
						_modules.add( module , debuginfo );
						_lock.wunlock( debuginfo );
						res->module = module;
						goto goto_return;
					}
					else
						res->GetLastError();

					if( ::booldog::utils::string::wcs::insert( &resres , res_root_dir.wlen , res_root_dir.wchar 
						, res_root_dir.wlen , res_root_dir.wsize , L"lib" , 0
						, SIZE_MAX , allocator , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}

					if( GetModuleHandleExW( 0 , res_name_or_path.wchar , &module_handle ) )
					{
						::booldog::module* module = 0;
						for( size_t index0 = 0 ; index0 < _modules.count() ; index0++ )
						{
							if( _modules[ index0 ]->handle() == module_handle )
							{
								module = _modules[ index0 ];
								module->addref();
								goto goto_step2_and_return;
							}
						}
						module = _allocator->create< ::booldog::module >( debuginfo );
						module->_handle = module_handle;
	goto_step2_and_return:
						res->module = module;
						_lock.wunlock( debuginfo );
						goto goto_return;
					}
					module_handle = LoadLibraryExW( res_name_or_path.wchar , 0 , 0 );
					if( module_handle )
					{
						::booldog::module* module = _allocator->create< ::booldog::module >( debuginfo );
						module->_handle = module_handle;
						_modules.add( module , debuginfo );
						_lock.wunlock( debuginfo );
						res->module = module;
						goto goto_return;
					}
					else
						res->GetLastError();

					_lock.wunlock( debuginfo );
				}
			}
#else

#endif
goto_return:
			return res->succeeded();
		};
		virtual bool unload( ::booldog::result* pres , ::booldog::base::module* module , ::booldog::debug::info* debuginfo = 0 )
		{
			debuginfo = debuginfo;
			::booldog::result locres;
			BOOINIT_RESULT( ::booldog::result );
			
			return res->succeeded();
		};
	};
};
#endif