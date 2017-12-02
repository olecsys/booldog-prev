#ifndef BOO_APPLICATION_H
#define BOO_APPLICATION_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_base_loader.h"
namespace booldog
{
	namespace typedefs
	{
#ifdef __WINDOWS__
		typedef DWORD (*timeGetTime)( void );
#else
#endif
	};
	class application;
	class application_data
	{
		friend class ::booldog::application;
		booldog::allocator* _allocator;
		booldog::threading::rdwrlock _lock;
		booldog::array< char* > _names;
		booldog::array< void* > _datas;
	public:
		application_data( booldog::allocator* pallocator )
			: _allocator( pallocator ) , _datas( pallocator ) , _names( pallocator )
		{
		};
		~application_data( void )
		{
			_lock.wlock( debuginfo_macros );
			for( size_t index0 = 0 ; index0 < _names.count() ; index0++ )
				_allocator->free( _names[ index0 ] );
			_lock.wunlock( debuginfo_macros );
		};
		void remove( const char* name , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			_lock.wlock( debuginfo );
			for( size_t index0 = 0 ; index0 < _names.count() ; index0++ )
			{
				if( strcmp( _names[ index0 ] , name ) == 0 )
				{
					char* lname = _names[ index0 ];
					_names.remove( index0 , debuginfo );
					_datas.remove( index0 );
					_allocator->free( lname );
					break;
				}
			}
			_lock.wunlock( debuginfo );
		};
		bool add( ::booldog::result* pres , const char* name , void* data , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			::booldog::result locres;
			BOOINIT_RESULT( ::booldog::result );
			const char* ptr = name;
			for( ; ; )
			{
				switch( *ptr++ )
				{
				case 0:
					goto goto_next;
				}
			}
goto_next:
			char* lname = _allocator->realloc_array< char >( 0 , ptr - name , debuginfo );
			if( lname )
			{
				memcpy( lname , name , ptr - name );
				_lock.wlock( debuginfo );
				_names.add( lname , debuginfo );
				_datas.add( data , debuginfo );
				_lock.wunlock( debuginfo );
			}
			else
				res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
			return res->succeeded();
		};
		void* operator()( const char* name )
		{
			void* data = 0;
			_lock.rlock( debuginfo_macros );
			for( size_t index0 = 0 ; index0 < _names.count() ; index0++ )
			{
				if( strcmp( _names[ index0 ] , name ) == 0 )
				{
					data = _datas[ index0 ];
					break;
				}
			}
			_lock.runlock( debuginfo_macros );
			return data;
		};
	};
	class application
	{
	protected:
		
		booldog::base::loader* _loader;
		
		void* _udata;
#ifdef __WINDOWS__
		::booldog::base::module* _winmm;
		::booldog::typedefs::timeGetTime _timeGetTime;
#else
#endif
	public:
		::booldog::application_data data;
		application( booldog::allocator* allocator , booldog::base::loader* loader )
			: _loader( loader ) , data( allocator ) , _udata( 0 )
#ifdef __WINDOWS__
			, _winmm( 0 ) , _timeGetTime( 0 )
#else
#endif
		{
#ifdef __WINDOWS__
			::booldog::result_module reswinmm;
			if( _loader->mbsload( &reswinmm , data._allocator , "winmm" , 0 , debuginfo_macros ) )
			{
				_winmm = reswinmm.module;
				::booldog::result_pointer resptr;
				if( reswinmm.module->method( &resptr , data._allocator , "timeGetTime" , debuginfo_macros ) )
					_timeGetTime = (::booldog::typedefs::timeGetTime)resptr.pres;
			}
#else
#endif
		};
		~application( void )
		{
#ifdef __WINDOWS__
			if( _winmm )
				_loader->unload( 0 , _winmm , 0 , 0 , debuginfo_macros );
#else
#endif
		};
		booldog::base::loader* loader( void )
		{
			return this->_loader;
		};
		booldog::allocator* allocator( void )
		{
			return data._allocator;
		};
		void* udata( void )
		{
			return _udata;
		};
		void udata( void* pudata )
		{
			_udata = pudata;
		};
		virtual void start( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros ) = 0;
		virtual void stop( void ) = 0;
		virtual ::booldog::uint32 tickcount( void )
		{
#ifdef __WINDOWS__
			if( _timeGetTime )
				return _timeGetTime();
#else
			struct timespec ts = { 0 };
			clock_gettime( CLOCK_MONOTONIC , &ts );
			return ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000ULL;
#endif
			return 0;
		};
	};
	booldog::application* _application = 0;
};
#endif