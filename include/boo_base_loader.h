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
			virtual bool utf8load( ::booldog::result_module* pres , const char* name_or_path , ::booldog::named_param* named_params = 0 , ::booldog::debug::info* debuginfo = 0 , booldog::allocator* allocator = ::booldog::_allocator ) = 0;
			virtual bool mbload( ::booldog::result_module* pres , const char* name_or_path , ::booldog::named_param* named_params = 0 , ::booldog::debug::info* debuginfo = 0 , booldog::allocator* allocator = ::booldog::_allocator ) = 0;
			virtual bool wcsload( ::booldog::result_module* pres , const wchar_t* name_or_path , ::booldog::named_param* named_params = 0 , ::booldog::debug::info* debuginfo = 0 , booldog::allocator* allocator = ::booldog::_allocator ) = 0;
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
	public:
		loader( booldog::allocator* allocator = ::booldog::_allocator )
		{
			_allocator = allocator;
		};
		virtual bool utf8load( ::booldog::result_module* pres , const char* name_or_path , ::booldog::named_param* named_params = 0
			, ::booldog::debug::info* debuginfo = 0 , booldog::allocator* allocator = ::booldog::_allocator )
		{
			::booldog::result_module locres;
			BOOINIT_RESULT( ::booldog::result_module );
			
			return res->succeeded();
		};
		virtual bool mbload( ::booldog::result_module* pres , const char* name_or_path , ::booldog::named_param* named_params = 0
			, ::booldog::debug::info* debuginfo = 0 , booldog::allocator* allocator = ::booldog::_allocator )
		{
			::booldog::result_module locres;
			BOOINIT_RESULT( ::booldog::result_module );

			return res->succeeded();
		};
		virtual bool wcsload( ::booldog::result_module* pres , const wchar_t* name_or_path , ::booldog::named_param* named_params = 0 
			, ::booldog::debug::info* debuginfo = 0 , booldog::allocator* allocator = ::booldog::_allocator )
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
			if( named_params )
				::booldog::utils::param::search( named_params , settings );
			::booldog::result_wchar respathname_wo_ext( allocator );
			if( ::booldog::utils::io::path::wcs::pathname_without_extension( &respathname_wo_ext , name_or_path , 0 , SIZE_MAX , allocator , debuginfo ) )
			{
				::booldog::result_bool resbool;
				if( ::booldog::utils::io::path::wcs::isabsolute( &resbool , respathname_wo_ext.wchar ) )
				{
					if( resbool.bres )
					{

					}
					else
					{
						::booldog::result_wchar res_root_dir( allocator );

						if( settings[ 2 ].param.type == ::booldog::enums::param::type_not_found )
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
						else
						{
							if( ::booldog::utils::string::wcs::insert( &resbool , SIZE_MAX , res_root_dir.wchar , res_root_dir.wlen 
								, res_root_dir.wsize , settings[ 2 ].param.pwcharvalue , 0 , SIZE_MAX , allocator , debuginfo ) == false )
							{
								res->copy( resbool );
								goto goto_return;
							}
						}
						if( res_root_dir.wchar )
						{
							::booldog::result resres;
							if( ::booldog::utils::io::path::wcs::normalize( &resres , res_root_dir.wchar , res_root_dir.wlen 
								, res_root_dir.wsize ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}

						//for( ; ; )
						{

						}
					}
				}
				else
					res->copy( resbool );

			//::booldog::result_bool resbool;
			//if( ::booldog::utils::io::path::wcs::has_levels( &resbool , name_or_path ) )

				//if( resbool.bres )
				//{
				//}
				//else
				//{
					//::booldog::result_wchar reswcs( allocator );
					//if( ::booldog::utils::io::path::wcs::filename_without_extension( &reswcs , name_or_path , 0 , SIZE_MAX , allocator , debuginfo ) )
					//{
					//	::booldog::base::module_handle module_handle = 0;

					//	if( GetModuleHandleExW( 0 , reswcs.wchar , &module_handle ) )
					//	{
					//		/*_lock.wlock( debuginfo );

					//		_lock.wunlock( debuginfo );*/
					//	}
					//}
					//else
					//	res->copy( reswcs );
			}
			else
				res->copy( respathname_wo_ext );
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