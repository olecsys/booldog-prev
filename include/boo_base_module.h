#ifndef BOO_BASE_MODULE_H
#define BOO_BASE_MODULE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_string.h"
#include "boo_interlocked.h"
#include "boo_rdwrlock.h"
#include "boo_result.h"
#include "boo_module_utils.h"
namespace booldog
{
	namespace base
	{
		class module;
	};
	namespace events
	{
		namespace typedefs
		{
			typedef void (*onbeforefree)( void* udata , ::booldog::base::module* module );
		};
	};
	typedef int (*module_init_t)( void* p );
	typedef int (*module_free_t)( void );
	namespace base
	{
		class module
		{
		public:
			virtual bool loaded( void )
			{
				return false;
			};
			virtual bool method( ::booldog::result_pointer* pres , booldog::allocator* allocator , const char* name 
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				pres = pres;
				name = name;
				allocator = allocator;
				debuginfo = debuginfo;
				return 0;
			};
			virtual ::booldog::module_handle handle( void )
			{
				return 0;
			};
			virtual void udata( void* userdata )
			{
				userdata = userdata;
			};
			virtual void* udata( void )
			{
				return 0;
			};
			virtual bool init( ::booldog::result* pres , booldog::allocator* allocator , void* initparams = 0 
				, ::booldog::events::typedefs::onbeforefree ponafterinit = 0 , void* udata = 0
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				ponafterinit = ponafterinit;
				udata = udata;
				pres = pres;
				allocator = allocator;
				initparams = initparams;
				debuginfo = debuginfo;
				return false;
			};
			virtual bool free( ::booldog::result* pres , booldog::allocator* allocator , ::booldog::events::typedefs::onbeforefree ponbeforefree 
				, void* udata , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				ponbeforefree = ponbeforefree;
				udata = udata;
				pres = pres;
				allocator = allocator;
				debuginfo = debuginfo;
				return false;
			};
			virtual bool inited( void )
			{
				return false;
			};
			virtual void lock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
			};
			virtual void unlock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
			};
		};
	};
	class loader;
	class module : public ::booldog::base::module
	{
		friend class ::booldog::loader;
	private:
		::booldog::interlocked::atomic _ref;
		::booldog::module_handle _handle;
		::booldog::threading::rdwrlock _lock;
		::booldog::uint32 _inited_ref;
		void* _udata;

		::booldog::module* _prev;
	public:
		module( void )
			: _udata( 0 ) , _prev( 0 )
		{
			_inited_ref = 0;
			_ref = 0;
			_handle = 0;
		};
		virtual void udata( void* pudata )
		{
			_udata = pudata;
		};
		virtual void* udata( void )
		{
			return _udata;
		};
		virtual bool loaded( void )
		{
			return _handle != 0;
		};
		virtual bool method( ::booldog::result_pointer* pres , booldog::allocator* allocator , const char* name
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			::booldog::result_pointer locres;
			BOOINIT_RESULT( ::booldog::result_pointer );
			::booldog::utils::module::mbs::method( res , allocator , _handle , name , debuginfo );
			return res->succeeded();
		};
		virtual ::booldog::module_handle handle( void )
		{
			return _handle;
		};
		virtual void lock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			_lock.wlock( debuginfo );
		};
		virtual void unlock( const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			_lock.wunlock( debuginfo );
		};
		void addref( void ) const
		{
			::booldog::interlocked::increment( const_cast< ::booldog::interlocked::atomic* >( &_ref ) );
		};
		::booldog::interlocked::atomic_return release( void ) const
		{
			return ::booldog::interlocked::decrement( const_cast< ::booldog::interlocked::atomic* >( &_ref ) );
		};
		virtual bool inited( void )
		{
			bool res = false;
			_lock.rlock( debuginfo_macros );
			res = _inited_ref > 0 && _inited_ref != UINT32_MAX;
			_lock.runlock( debuginfo_macros );
			return res;
		};
		virtual bool init( ::booldog::result* pres , booldog::allocator* allocator , void* initparams = 0
			, ::booldog::events::typedefs::onbeforefree ponafterinit = 0 , void* udata = 0
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{		
			::booldog::result locres;
			BOOINIT_RESULT( ::booldog::result );
			::booldog::result_pointer respointer;
			::booldog::module_init_t module_init = 0;
			_lock.wlock( debuginfo );
			if(_inited_ref == 0)
			{
				if(::booldog::utils::module::mbs::method(&respointer, allocator, _handle, "core_init", debuginfo))
					goto goto_method_success_return;
				if(::booldog::utils::module::mbs::method(&respointer, allocator, _handle, "rux_module_init", debuginfo))
					goto goto_method_success_return;
				if(::booldog::utils::module::mbs::method(&respointer, allocator, _handle, "dll_init", debuginfo))
					goto goto_method_success_return;
				goto goto_return;
			}
			else if(_inited_ref == UINT32_MAX)
			{
				res->booerr(::booldog::enums::result::booerr_type_module_is_deinitialized_and_must_be_unloaded);
				goto goto_return;
			}
			goto goto_inited_ref;
goto_method_success_return:
			module_init = (::booldog::module_init_t)respointer.pres;
			module_init(initparams);			
			if(ponafterinit)
				ponafterinit(udata, this);
goto_inited_ref:
			++_inited_ref;
goto_return:
			_lock.wunlock( debuginfo );
			return res->succeeded();
		};
		virtual bool free(::booldog::result* pres, booldog::allocator* allocator, ::booldog::events::typedefs::onbeforefree ponbeforefree
			, void* udata, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			::booldog::result locres;
			BOOINIT_RESULT( ::booldog::result );
			_lock.wlock( debuginfo );
			if(_inited_ref && _inited_ref != UINT32_MAX)
			{
				--_inited_ref;			
				if(_inited_ref == 0)
				{
					_inited_ref = UINT32_MAX;
					if( ponbeforefree )
						ponbeforefree( udata , this );
					::booldog::result_pointer respointer;
					if( ::booldog::utils::module::mbs::method( &respointer , allocator , _handle , "core_free" , debuginfo ) )
						goto goto_method_success_return;
					if( ::booldog::utils::module::mbs::method( &respointer , allocator , _handle , "rux_module_free" , debuginfo ) )
						goto goto_method_success_return;
					if( ::booldog::utils::module::mbs::method( &respointer , allocator , _handle , "dll_free" , debuginfo ) )
						goto goto_method_success_return;
					res->copy( respointer );
					goto goto_return;
goto_method_success_return:
					::booldog::module_free_t module_free = (::booldog::module_free_t)respointer.pres;
					module_free();
				}
			}
goto_return:
			_lock.wunlock( debuginfo );
			return res->succeeded();
		};
	};
};
#endif