#ifndef BOO_BASE_MODULE_H
#define BOO_BASE_MODULE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_string.h>
#include <boo_interlocked.h>
#include <boo_rdwrlock.h>
#include <boo_result.h>
#include <boo_module_utils.h>
namespace booldog
{
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
			virtual bool method( ::booldog::result_pointer* pres , const char* name 
				, booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
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
	public:
		module( void )
		{
			_inited_ref = 0;
			_ref = 1;
			_handle = 0;
		};
		virtual bool loaded( void )
		{
			return _handle != 0;
		};
		virtual bool method( ::booldog::result_pointer* pres , const char* name , booldog::allocator* allocator = ::booldog::_allocator
			, ::booldog::debug::info* debuginfo = 0 )
		{
			::booldog::result_pointer locres;
			BOOINIT_RESULT( ::booldog::result_pointer );
			::booldog::utils::module::mbs::method( res , _handle , name , allocator , debuginfo );
			return res->succeeded();
		};
		virtual ::booldog::module_handle handle( void )
		{
			return _handle;
		};
		void lock( booldog::debug::info* debuginfo = 0 )
		{
			_lock.wlock( debuginfo );
		};
		void unlock( booldog::debug::info* debuginfo = 0 )
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
		bool init( ::booldog::result* pres , void* initparams = 0 , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
		{		
			::booldog::result locres;
			BOOINIT_RESULT( ::booldog::result );
			::booldog::result_pointer respointer;
			::booldog::module_init_t module_init = 0;
			_lock.wlock( debuginfo );
			if( _inited_ref == 0 )
			{
				if( ::booldog::utils::module::mbs::method( &respointer , _handle , "core_init" , allocator , debuginfo ) )
					goto goto_method_success_return;
				if( ::booldog::utils::module::mbs::method( &respointer , _handle , "rux_module_init" , allocator , debuginfo ) )
					goto goto_method_success_return;
				if( ::booldog::utils::module::mbs::method( &respointer , _handle , "dll_init" , allocator , debuginfo ) )
					goto goto_method_success_return;
			}
			goto goto_return;
goto_method_success_return:
			module_init = (::booldog::module_init_t)respointer.pres;
			module_init( initparams );
goto_return:
			_inited_ref++;
			_lock.wunlock( debuginfo );
			return res->succeeded();
		};
		bool free( ::booldog::result* pres , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
		{
			::booldog::result locres;
			BOOINIT_RESULT( ::booldog::result );
			_lock.wlock( debuginfo );
			if( _inited_ref )
			{
				_inited_ref--;			
				if( _inited_ref == 0 )
				{
					::booldog::result_pointer respointer;
					if( ::booldog::utils::module::mbs::method( &respointer , _handle , "core_free" , allocator , debuginfo ) )
						goto goto_method_success_return;
					if( ::booldog::utils::module::mbs::method( &respointer , _handle , "rux_module_free" , allocator , debuginfo ) )
						goto goto_method_success_return;
					if( ::booldog::utils::module::mbs::method( &respointer , _handle , "dll_free" , allocator , debuginfo ) )
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