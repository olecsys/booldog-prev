#ifndef BOO_BASE_LOADER_H
#define BOO_BASE_LOADER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_base_module.h"
#include "boo_array.h"
#include "boo_result.h"
#include "boo_param.h"
#include "boo_stack_allocator.h"
#include "boo_rdwrlock.h"
#include "boo_io_utils.h"
#include "boo_executable_utils.h"
#include "boo_file_utils.h"

#ifdef __UNIX__
#include <dlfcn.h>
#include <link.h>
#include <limits.h>
#include "boo_module_utils.h"
#endif
namespace booldog
{
	namespace events
	{
		namespace typedefs
		{
			typedef void (*onbeforeunload)(void* udata, ::booldog::base::module* module);
		}
	}
	class result_module : public ::booldog::result
	{
	private:
		result_module(const ::booldog::result&);
		result_module(const ::booldog::result_module&);
		::booldog::result_module& operator = (const ::booldog::result_module&);
	public:
		::booldog::base::module* module;
		result_module()
			: module(0)
		{
		}
		virtual ~result_module()
		{
		}
		virtual void clear() const
		{
			::booldog::result_module* _obj_ = const_cast< ::booldog::result_module* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			_obj_->module = 0;
		}
	};
	namespace base
	{
		class loader
		{
		public:
			virtual bool mbsload(::booldog::result_module* pres, ::booldog::allocator* allocator, const char* name_or_path
				, ::booldog::named_param* named_params = 0, const ::booldog::debug::info& debuginfo = debuginfo_macros) = 0;
			virtual bool wcsload(::booldog::result_module* pres, ::booldog::allocator* allocator, const wchar_t* name_or_path
				, ::booldog::named_param* named_params = 0, const ::booldog::debug::info& debuginfo = debuginfo_macros) = 0;
			virtual bool unload(::booldog::result* pres, ::booldog::base::module* module
				, ::booldog::events::typedefs::onbeforeunload ponbeforeunload, void* udata
				, const ::booldog::debug::info& debuginfo = debuginfo_macros) = 0;
			virtual booldog::allocator* allocator() = 0;
		};
	};
	class loader : public ::booldog::base::loader
	{
		booldog::allocator* _allocator;
		booldog::threading::rdwrlock _lock;
		booldog::module* _modules_begin;
#ifdef __UNIX__
		booldog::threading::rdwrlock _lock_loaded_dirs;
		booldog::array< char* > _loaded_dirs;
#endif
	private:
#ifdef __WINDOWS__
		typedef wchar_t tchar;
#else
		typedef char tchar;
#endif
		::booldog::interlocked::atomic _loading_count;
		::booldog::interlocked::atomic _unloading_count;
		booinline ::booldog::module* find_or_create(const ::booldog::loader::tchar* res_name_or_path
			, ::booldog::module_handle module_handle, bool& tryagain, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			tryagain = false;
			_lock.wlock(debuginfo);
			::booldog::module* module_next = _modules_begin, * module_free = 0;
			while(module_next)
			{
				if(module_next->_handle == module_handle)
				{	
					if(module_next->addref() == 1)
					{
						module_next->lock();
						if(module_next->_handle)
						{
							module_next->unlock();
							module_next->release();
#ifdef __WINDOWS__
							FreeLibrary(module_handle);
#else
							dlclose(module_handle);
#endif
							_lock.wunlock(debuginfo);
							while(::booldog::interlocked::compare_exchange(&_unloading_count, 0, 0) == 0)
								::booldog::threading::sleep(1);
							::booldog::interlocked::decrement(&_loading_count);
							while(::booldog::interlocked::compare_exchange(&_unloading_count, 0, 0))
								::booldog::threading::sleep(1);
							::booldog::interlocked::increment(&_loading_count);
							tryagain = true;
							return 0;
						}
						module_next->_handle = module_handle;
						module_next->unlock();
#ifdef __UNIX__
						debuginfo.log_debug("<booldog>mbsload, %s loaded", res_name_or_path);
#else
						res_name_or_path = res_name_or_path;
#endif
					}
					_lock.wunlock(debuginfo);
					return module_next;
				}
				else if(module_free == 0 && ::booldog::interlocked::compare_exchange(&module_next->_ref, 0, 0) == 0)
				{
					if(module_next->_handle == 0)
					{
						module_next->lock();
						if(module_next->_handle == 0)
							module_free = module_next;
						module_next->unlock();
					}
				}
				module_next = module_next->_prev;
			}
			if(module_free)
			{
				module_next = module_free;
				module_next->addref();
			}
			else
			{
				module_next = _allocator->create< ::booldog::module >(debuginfo);
				module_next->_prev = _modules_begin;
				_modules_begin = module_next;
			}
			module_next->_handle = module_handle;
#ifdef __UNIX__
			debuginfo.log_debug("<booldog>mbsload, %s loaded", res_name_or_path);
#else
			res_name_or_path = res_name_or_path;
#endif
			_lock.wunlock(debuginfo);
			return module_next;
		}
		booinline bool get_loaded_module(::booldog::result_module* pres, const ::booldog::loader::tchar* res_name_or_path
			, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
#ifdef __WINDOWS__
			::booldog::module_handle module_handle = 0;
			if(GetModuleHandleExW(0, res_name_or_path, &module_handle))
			{
				if(GetModuleHandle(0) == module_handle)
				{
					FreeLibrary(module_handle);
					module_handle = 0;
				}
			}
#else
			::booldog::module_handle module_handle = ::booldog::utils::module::mbs::handle(0, _allocator, res_name_or_path
				, debuginfo);
#endif
			if(module_handle)
			{
				bool tryagain = false;
				::booldog::module* module = find_or_create(res_name_or_path, module_handle, tryagain, debuginfo);
				if(tryagain)
					return get_loaded_module(pres, res_name_or_path, debuginfo);
				pres->clear();
				pres->module = module;
				return true;
			}
			return false;
		}
		bool load(::booldog::result_module* pres, ::booldog::allocator* allocator
			, const ::booldog::loader::tchar* name_or_path, ::booldog::named_param* named_params, bool inc
			, const ::booldog::debug::info& debuginfo)
		{
			::booldog::interlocked::automatic::decrementer decrementer(0);
			if(inc)
			{
				while(::booldog::interlocked::compare_exchange(&_unloading_count, 0, 0))
					::booldog::threading::sleep(1);
				decrementer.target = &_loading_count;
				::booldog::interlocked::increment(&_loading_count);
			}
			bool tryagain = false;
			::booldog::result_module locres;
			BOOINIT_RESULT(::booldog::result_module);
#ifdef __WINDOWS__			
			booldog::named_param settings[] =
			{
				BOO_SEARCH_NAMED_PARAM_PPARAM("search_paths"),
				BOO_SEARCH_NAMED_PARAM_PCHAR("root_path"),
				BOO_SEARCH_NAMED_PARAM_WCHAR("root_path") ,
				BOO_SEARCH_NAMED_PARAM_BOOL("exedir_as_root_path") ,
				BOO_SEARCH_NAMED_PARAM_NONE
			};
			::booldog::utils::param::search(named_params, settings);

			::booldog::result_wchar res_name_or_path(allocator);
			::booldog::result_module resmod;			

			::booldog::result_bool resbool;
			::booldog::result resres;
			if( ::booldog::utils::string::wcs::insert(&resres, allocator, true, 0, res_name_or_path.wchar, res_name_or_path.wlen
				, res_name_or_path.wsize, name_or_path, 0, SIZE_MAX, debuginfo) == false)
			{
				res->copy(resres);
				goto goto_return;
			}
			if(::booldog::utils::io::path::wcs::isabsolute(&resbool, res_name_or_path.wchar) == false)
			{
				res->copy(resbool);
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
				if(::booldog::utils::io::file::wcs::exists(&resbool, allocator, res_name_or_path.wchar, debuginfo)
					== false || resbool.bres == false)
					goto goto_return;

				::booldog::module_handle module_handle = 0;
				
				if(get_loaded_module(res, res_name_or_path.wchar, debuginfo))
					goto goto_return;
				module_handle = LoadLibraryExW(res_name_or_path.wchar, 0, 0);
				if(module_handle)
				{
					::booldog::module* module = find_or_create(name_or_path, module_handle, tryagain, debuginfo);
					if(tryagain)
						return load(pres, allocator, name_or_path, named_params, false, debuginfo);
					res->clear();
					res->module = module;
					goto goto_return;
				}
				else
					res->GetLastError();
			}
			else
			{
				::booldog::result_wchar res_root_dir(allocator);

				if(settings[1].type != ::booldog::enums::param::type_not_found && settings[1].pcharvalue)
				{
					if( ::booldog::utils::string::mbs::towcs( &res_root_dir , allocator , settings[ 1 ].pcharvalue , 0 , SIZE_MAX 
						, debuginfo ) == false )
					{
						res->copy( res_root_dir );
						goto goto_return;							
					}
				}
				else if( settings[ 2 ].type != ::booldog::enums::param::type_not_found
					&& settings[ 2 ].pwcharvalue)
				{
					if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , SIZE_MAX , res_root_dir.wchar , res_root_dir.wlen 
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
					::booldog::result resres1;
					if( ::booldog::utils::io::path::wcs::normalize( &resres1 , res_root_dir.wchar , res_root_dir.wlen 
						, res_root_dir.wsize ) == false )
					{
						res->copy( resres1 );
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
							if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
								, res_root_dir.wlen , res_root_dir.wsize , &::booldog::io::wcs::slash , 0
								, 1 , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pchar )
						{
							if( ::booldog::utils::string::mbs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
								, res_root_dir.wlen , res_root_dir.wsize , settings[ 0 ].pparamvalue[ index ].pcharvalue , 0
								, SIZE_MAX , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						else if( settings[ 0 ].pparamvalue[ index ].type == ::booldog::enums::param::type_pwchar )
						{
							if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
								, res_root_dir.wlen , res_root_dir.wsize , settings[ 0 ].pparamvalue[ index ].pwcharvalue , 0
								, SIZE_MAX , debuginfo ) == false )
							{
								res->copy( resres );
								goto goto_return;
							}
						}
						else
							continue;
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , &::booldog::io::wcs::slash , 0
							, 1 , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						size_t res_dir_wlen = res_root_dir.wlen;
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , res_name_or_path.wchar , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if(load(&resmod, allocator, res_root_dir.wchar, 0, false, debuginfo))
						{
							res->clear();
							res->module = resmod.module;
							goto goto_return;
						}
						else if( resmod.error_type == ::booldog::enums::result::error_type_GetLastError )
							res->copy( resmod );

						if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , L".dll" , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if(load(&resmod, allocator, res_root_dir.wchar, 0, false, debuginfo))
						{
							res->clear();
							res->module = resmod.module;
							goto goto_return;
						}
						else if( resmod.error_type == ::booldog::enums::result::error_type_GetLastError )
							res->copy( resmod );

						res_root_dir.wchar[ res_dir_wlen ] = 0;
						res_root_dir.wlen = res_dir_wlen;
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , L"lib" , 0
							, SIZE_MAX , debuginfo ) == false )
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
						if(load(&resmod, allocator, res_root_dir.wchar, 0, false, debuginfo))
						{
							res->clear();
							res->module = resmod.module;
							goto goto_return;
						}
						else if( resmod.error_type == ::booldog::enums::result::error_type_GetLastError )
							res->copy( resmod );

						if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , L".dll" , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if(load(&resmod, allocator, res_root_dir.wchar, 0, false, debuginfo))
						{
							res->clear();
							res->module = resmod.module;
							goto goto_return;
						}
						else if( resmod.error_type == ::booldog::enums::result::error_type_GetLastError )
							res->copy( resmod );
					}
				}
				if( res_root_dir.wchar )
				{
					res_root_dir.wchar[ res_root_dir_wlen ] = 0;
					res_root_dir.wlen = res_root_dir_wlen;
					if( res_root_dir_wlen )
					{
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , &::booldog::io::wcs::slash , 0
							, 1 , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
					}
					size_t res_dir_wlen = res_root_dir.wlen;
					if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
						, res_root_dir.wlen , res_root_dir.wsize , res_name_or_path.wchar , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if(load(&resmod, allocator, res_root_dir.wchar, 0, false, debuginfo))
					{
						res->clear();
						res->module = resmod.module;
						goto goto_return;
					}
					else if( resmod.error_type == ::booldog::enums::result::error_type_GetLastError )
						res->copy( resmod );

					if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
						, res_root_dir.wlen , res_root_dir.wsize , L".dll" , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if(load(&resmod, allocator, res_root_dir.wchar, 0, false, debuginfo))
					{
						res->clear();
						res->module = resmod.module;
						goto goto_return;
					}
					else if( resmod.error_type == ::booldog::enums::result::error_type_GetLastError )
						res->copy( resmod );

					res_root_dir.wchar[ res_dir_wlen ] = 0;
					res_root_dir.wlen = res_dir_wlen;
					if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
						, res_root_dir.wlen , res_root_dir.wsize , L"lib" , 0
						, SIZE_MAX , debuginfo ) == false )
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
					if(load(&resmod, allocator, res_root_dir.wchar, 0, false, debuginfo))
					{
						res->clear();
						res->module = resmod.module;
						goto goto_return;
					}
					else if( resmod.error_type == ::booldog::enums::result::error_type_GetLastError )
						res->copy( resmod );

					if(::booldog::utils::string::wcs::insert(&resres, allocator, false, res_root_dir.wlen, res_root_dir.wchar
						, res_root_dir.wlen, res_root_dir.wsize, L".dll", 0, SIZE_MAX, debuginfo) == false)
					{
						res->copy( resres );
						goto goto_return;
					}
					if(load(&resmod, allocator, res_root_dir.wchar, 0, false, debuginfo))
					{
						res->clear();
						res->module = resmod.module;
						goto goto_return;
					}
					else if( resmod.error_type == ::booldog::enums::result::error_type_GetLastError )
						res->copy( resmod );
				}
				else
				{
					if(::booldog::utils::io::path::wcs::normalize(&resres, res_name_or_path.wchar, res_name_or_path.wlen
						, res_name_or_path.wsize) == false)
					{
						res->copy(resres);
						goto goto_return;
					}
					::booldog::module_handle module_handle = 0;
					
					if(get_loaded_module(res, res_name_or_path.wchar, debuginfo))
						goto goto_return;
					module_handle = LoadLibraryExW(res_name_or_path.wchar, 0, 0);
					if( module_handle == 0 )
						res->GetLastError();

					if( module_handle == 0 )
					{
						size_t res_root_dir_prev = res_root_dir.wlen;
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , L".dll" , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if(get_loaded_module(res, res_name_or_path.wchar, debuginfo))
							goto goto_return;
						module_handle = LoadLibraryExW( res_name_or_path.wchar , 0 , 0 );
						if( module_handle == 0 )
						{
							res->GetLastError();
							res_root_dir.wchar[ res_root_dir_prev ] = 0;
							res_root_dir.wlen = res_root_dir_prev;
						}
					}

					if( module_handle == 0 )
					{
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , 0 , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , L"lib" , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if(get_loaded_module(res, res_name_or_path.wchar, debuginfo))
							goto goto_return;
						module_handle = LoadLibraryExW( res_name_or_path.wchar , 0 , 0 );
						if( module_handle == 0 )
							res->GetLastError();
					}
					
					if( module_handle == 0 )
					{
						if( ::booldog::utils::string::wcs::insert( &resres , allocator , false , res_root_dir.wlen , res_root_dir.wchar 
							, res_root_dir.wlen , res_root_dir.wsize , L".dll" , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if(get_loaded_module(res, res_name_or_path.wchar, debuginfo))
							goto goto_return;
						module_handle = LoadLibraryExW( res_name_or_path.wchar , 0 , 0 );
						if( module_handle == 0 )
							res->GetLastError();
					}
										
					if( module_handle )
					{
						::booldog::module* module = find_or_create(name_or_path, module_handle, tryagain, debuginfo);
						if(tryagain)
							return load(pres, allocator, name_or_path, named_params, false, debuginfo);
						res->clear();
						res->module = module;
						goto goto_return;
					}
				}
			}
goto_return:			
#else
			booldog::named_param settings[] =
			{
				BOO_SEARCH_NAMED_PARAM_PPARAM("search_paths"),
				BOO_SEARCH_NAMED_PARAM_PCHAR("root_path"),
				BOO_SEARCH_NAMED_PARAM_WCHAR("root_path"),
				BOO_SEARCH_NAMED_PARAM_BOOL("exedir_as_root_path"),
				BOO_SEARCH_NAMED_PARAM_NONE
			};
			::booldog::utils::param::search(named_params, settings);

			::booldog::result_mbchar res_name_or_path(allocator);
			
			::booldog::result_module resmod;

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
				if( ::booldog::utils::io::file::mbs::exists( &resbool , allocator , res_name_or_path.mbchar , debuginfo ) 
					== false || resbool.bres == false )
					goto goto_return;

				::booldog::module_handle module_handle = 0;

				if(get_loaded_module(res, res_name_or_path.mbchar, debuginfo))
					goto goto_return;
				module_handle = dlopen(res_name_or_path.mbchar, RTLD_NOW);
				if( module_handle )
				{
					::booldog::result_mbchar resdirmbchar( _allocator );
					if( ::booldog::utils::io::path::mbs::directory( &resdirmbchar , _allocator , res_name_or_path.mbchar , 0 , SIZE_MAX 
						, debuginfo ) )
					{
						::booldog::module* module = find_or_create(name_or_path, module_handle, tryagain
							, debuginfo);
						if(tryagain)
							return load(pres, allocator, name_or_path, named_params, false, debuginfo);
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

				if( settings[ 1 ].type != ::booldog::enums::param::type_not_found
					&& settings[ 1 ].pcharvalue)
				{
					if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , SIZE_MAX , res_root_dir.mbchar , res_root_dir.mblen 
						, res_root_dir.mbsize , settings[ 1 ].pcharvalue , 0 , SIZE_MAX , debuginfo ) == false )
					{
						res->copy( res_root_dir );
						goto goto_return;							
					}
				}
				else if( settings[ 2 ].type != ::booldog::enums::param::type_not_found
					&& settings[ 2 ].pwcharvalue)
				{
					if(::booldog::utils::string::wcs::tombs(res_root_dir, settings[2].pwcharvalue, 0, SIZE_MAX, debuginfo) == false)
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
						size_t res_dir_mblen = res_root_dir.mblen;
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if(load(&resmod, allocator, res_root_dir.mbchar, 0, false, debuginfo))
						{
							res->clear();
							res->module = resmod.module;
							goto goto_return;
						}
						else if( resmod.error_type == ::booldog::enums::result::error_type_dlerror )
							res->copy( resmod );

						res_root_dir.mbchar[ res_dir_mblen ] = 0;
						res_root_dir.mblen = res_dir_mblen;
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , ".so" , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if(load(&resmod, allocator, res_root_dir.mbchar, 0, false, debuginfo))
						{
							res->clear();
							res->module = resmod.module;
							goto goto_return;
						}
						else if( resmod.error_type == ::booldog::enums::result::error_type_dlerror )
							res->copy( resmod );

						res_root_dir.mbchar[ res_dir_mblen ] = 0;
						res_root_dir.mblen = res_dir_mblen;
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , "lib" , 0
							, SIZE_MAX , debuginfo ) == false )
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
						if(load(&resmod, allocator, res_root_dir.mbchar, 0, false, debuginfo))
						{
							res->clear();
							res->module = resmod.module;
							goto goto_return;
						}
						else if( resmod.error_type == ::booldog::enums::result::error_type_dlerror )
							res->copy( resmod );

						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , ".so" , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							res->copy( resres );
							goto goto_return;
						}
						if(load(&resmod, allocator, res_root_dir.mbchar, 0, false, debuginfo))
						{
							res->clear();
							res->module = resmod.module;
							goto goto_return;
						}
						else if( resmod.error_type == ::booldog::enums::result::error_type_dlerror )
							res->copy( resmod );
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
					size_t res_dir_mblen = res_root_dir.mblen;
					if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if(load(&resmod, allocator, res_root_dir.mbchar, 0, false, debuginfo))
					{
						res->clear();
						res->module = resmod.module;
						goto goto_return;
					}
					else if( resmod.error_type == ::booldog::enums::result::error_type_dlerror )
						res->copy( resmod );

					res_root_dir.mbchar[ res_dir_mblen ] = 0;
					res_root_dir.mblen = res_dir_mblen;
					if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , ".so" , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if(load(&resmod, allocator, res_root_dir.mbchar, 0, false, debuginfo))
					{
						res->clear();
						res->module = resmod.module;
						goto goto_return;
					}
					else if( resmod.error_type == ::booldog::enums::result::error_type_dlerror )
						res->copy( resmod );

					res_root_dir.mbchar[ res_dir_mblen ] = 0;
					res_root_dir.mblen = res_dir_mblen;
					if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , "lib" , 0
						, SIZE_MAX , debuginfo ) == false )
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
					if(load(&resmod, allocator, res_root_dir.mbchar, 0, false, debuginfo))
					{
						res->clear();
						res->module = resmod.module;
						goto goto_return;
					}
					else if( resmod.error_type == ::booldog::enums::result::error_type_dlerror )
						res->copy( resmod );

					if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
						, res_root_dir.mblen , res_root_dir.mbsize , ".so" , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					if(load(&resmod, allocator, res_root_dir.mbchar, 0, false, debuginfo))
					{
						res->clear();
						res->module = resmod.module;
						goto goto_return;
					}
					else if( resmod.error_type == ::booldog::enums::result::error_type_dlerror )
						res->copy( resmod );
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
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , _loaded_dirs[ index0 ] , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , &::booldog::io::mbs::slash , 0
							, 1 , debuginfo ) == false )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							res->copy( resres );
							goto goto_return;
						}
						res_root_dir_mblen = res_root_dir.mblen;
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
							, SIZE_MAX , debuginfo ) == false )
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
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , ".so" , 0
							, SIZE_MAX , debuginfo ) == false )
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
					
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , "lib" , 0
							, SIZE_MAX , debuginfo ) == false )
						{
							_lock_loaded_dirs.runlock( debuginfo );
							res->copy( resres );
							goto goto_return;
						}
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , res_name_or_path.mbchar , 0
							, SIZE_MAX , debuginfo ) == false )
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
						if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_root_dir.mblen , res_root_dir.mbchar 
							, res_root_dir.mblen , res_root_dir.mbsize , ".so" , 0
							, SIZE_MAX , debuginfo ) == false )
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

					::booldog::module_handle module_handle = dlopen(res_name_or_path.mbchar, RTLD_NOW);
					if(module_handle)
						goto goto_loaded_module;
					else
						res->setdlerror( allocator , dlerror() , debuginfo );
					res_root_dir_mblen = res_name_or_path.mblen;
					if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_name_or_path.mblen , res_name_or_path.mbchar 
						, res_name_or_path.mblen , res_name_or_path.mbsize , ".so" , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}

					module_handle = dlopen( res_name_or_path.mbchar , RTLD_NOW );
					if( module_handle )
						goto goto_loaded_module;
					else
						res->setdlerror( allocator , dlerror() , debuginfo );

					res_name_or_path.mbchar[ res_root_dir_mblen ] = 0;
					res_name_or_path.mblen = res_root_dir_mblen;
					
					if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , 0 , res_name_or_path.mbchar 
						, res_name_or_path.mblen , res_name_or_path.mbsize , "lib" , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}

					module_handle = dlopen( res_name_or_path.mbchar , RTLD_NOW );
					if( module_handle )
						goto goto_loaded_module;
					else
						res->setdlerror( allocator , dlerror() , debuginfo );

					if( ::booldog::utils::string::mbs::insert< 0 >( &resres , allocator , false , res_name_or_path.mblen , res_name_or_path.mbchar 
						, res_name_or_path.mblen , res_name_or_path.mbsize , ".so" , 0
						, SIZE_MAX , debuginfo ) == false )
					{
						res->copy( resres );
						goto goto_return;
					}
					
					module_handle = dlopen( res_name_or_path.mbchar , RTLD_NOW );
					if( module_handle )
						goto goto_loaded_module;
					else
						res->setdlerror( allocator , dlerror() , debuginfo );
					goto goto_return;
goto_loaded_module:	
					::booldog::result_mbchar resdirmbchar(_allocator);
					if(::booldog::utils::module::mbs::pathname< 64 >(&resdirmbchar, _allocator, module_handle, debuginfo) == false)
					{
						res->copy(resdirmbchar);
						dlclose(module_handle);
						goto goto_return;
					}
					if( ::booldog::utils::io::path::mbs::directory( &resres , resdirmbchar.mbchar 
						, resdirmbchar.mblen ) == false )
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
					::booldog::module* module = find_or_create(name_or_path, module_handle, tryagain, debuginfo);
					if(tryagain)
						return load(pres, allocator, name_or_path, named_params, false, debuginfo);
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
			}
goto_return:
#endif
			if(res->module == 0)
			{
				if(res->succeeded())
					res->booerr(::booldog::enums::result::booerr_type_file_does_not_exist);
			}
			return res->succeeded();
		}
	public:
		loader(::booldog::allocator* allocator)
			: _allocator(allocator), _modules_begin(0)
#ifdef __UNIX__
			, _loaded_dirs(allocator)
#endif
			, _loading_count(0), _unloading_count(0)
		{
		}
		~loader()
		{
			_lock.wlock(debuginfo_macros);
			::booldog::module* module_next = _modules_begin;
			while(module_next)
			{
				::booldog::module* prev = module_next->_prev;
				_allocator->destroy(module_next);
				module_next = prev;
			}
			_lock.wunlock(debuginfo_macros);
#ifdef __UNIX__
			_lock_loaded_dirs.wlock(debuginfo_macros);
			for( size_t index0 = 0 ; index0 < _loaded_dirs.count() ; index0++ )
				_allocator->free( _loaded_dirs[ index0 ] );
			_lock_loaded_dirs.wunlock(debuginfo_macros);
#endif
		};
		virtual booldog::allocator* allocator()
		{
			return _allocator;
		}
		virtual bool mbsload(::booldog::result_module* pres, ::booldog::allocator* allocator, const char* name_or_path
			, ::booldog::named_param* named_params = 0, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{	
#ifdef __WINDOWS__
			::booldog::result_wchar reswchar(allocator);
			if(::booldog::utils::string::mbs::towcs(&reswchar, allocator, name_or_path, 0, SIZE_MAX, debuginfo))
				return load(pres, allocator, reswchar.wchar, named_params, true, debuginfo);
			else if(pres)
				pres->copy(reswchar);
			return false;
#else
			return load(pres, allocator, name_or_path, named_params, true, debuginfo);
#endif
		}
		virtual bool wcsload( ::booldog::result_module* pres , booldog::allocator* allocator , const wchar_t* name_or_path 
			, ::booldog::named_param* named_params = 0 , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
#ifdef __WINDOWS__
			return load(pres, allocator, name_or_path, named_params, true, debuginfo);
#else
			::booldog::result_mbchar resmbchar(allocator);
			if(::booldog::utils::string::wcs::tombs(resmbchar, name_or_path, 0, SIZE_MAX, debuginfo))
				return load(pres, allocator, resmbchar.mbchar, named_params, true, debuginfo);
			else if(pres)
				pres->copy(resmbchar);
			return false;
#endif
		}
		virtual bool unload(::booldog::result* pres, ::booldog::base::module* module
			, ::booldog::events::typedefs::onbeforeunload ponbeforeunload, void* udata
			, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			::booldog::result locres;
			BOOINIT_RESULT(::booldog::result);
			::booldog::module* mod = (::booldog::module*)module;			
			if(mod->release() == 0)
			{
				if(ponbeforeunload)
					ponbeforeunload(udata, mod);

				::booldog::interlocked::increment(&_unloading_count);
				while(::booldog::interlocked::compare_exchange(&_loading_count, 0, 0))
					::booldog::threading::sleep(1);
#ifdef __WINDOWS__
				FreeLibrary(mod->_handle);
#else
				dlclose(mod->_handle);
#endif
				mod->lock(debuginfo);
				mod->_inited_ref = 0;
				mod->_udata = 0;
				mod->_handle = 0;
				mod->unlock(debuginfo);
				::booldog::interlocked::decrement(&_unloading_count);
			}
			else
#ifdef __WINDOWS__
				FreeLibrary(mod->_handle);
#else
				dlclose(mod->_handle);
#endif
			return true;
		}
	};
}
#endif