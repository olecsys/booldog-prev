#ifndef BOO_BASE_MODULE_H
#define BOO_BASE_MODULE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_string.h>
#include <boo_interlocked.h>
#include <boo_rdwrlock.h>
#include <boo_result.h>
namespace booldog
{
	namespace base
	{
		class module
		{
		public:
			virtual const ::booldog::string name( void )
			{
				::booldog::string s;
				return s;
			};
			virtual const ::booldog::string path( void )
			{
				::booldog::string s;
				return s;
			};
			virtual bool loaded( void )
			{
				return false;
			};
			virtual void* method( const char* name )
			{
				name = name;
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
		bool _inited;
	public:
		module( void )
		{
			_inited = false;
			_ref = 1;
			_handle = 0;
		};
		virtual const ::booldog::string name( void )
		{
			::booldog::string s;
			return s;
		};
		virtual const ::booldog::string path( void )
		{
			::booldog::string s;
			return s;
		};
		virtual bool loaded( void )
		{
			return _handle != 0;
		};
		virtual void* method( const char* name )
		{
			name = name;
			return 0;
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
		bool init( ::booldog::result* pres , void* initparams )
		{		
			::booldog::result locres;
			BOOINIT_RESULT( ::booldog::result );
			{
				booldog::debug::info debuginfo( __FILE__ , __LINE__ );
				_lock.wlock( &debuginfo );
			}
			
			{
				booldog::debug::info debuginfo( __FILE__ , __LINE__ );
				_lock.wunlock( &debuginfo );
			}
			return res->succeeded();
		};
		bool free( ::booldog::result* pres )
		{
			::booldog::result locres;
			BOOINIT_RESULT( ::booldog::result );
			{
				booldog::debug::info debuginfo( __FILE__ , __LINE__ );
				_lock.wlock( &debuginfo );
			}

			{
				booldog::debug::info debuginfo( __FILE__ , __LINE__ );
				_lock.wunlock( &debuginfo );
			}
			return res->succeeded();
		};
	};
};
#endif