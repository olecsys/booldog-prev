#ifndef BOO_RENDER_CONTEXT_H
#define BOO_RENDER_CONTEXT_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_types.h)
namespace booldog
{
	namespace rendering
	{
		class context;
	};
	namespace events
	{
		namespace typedefs
		{
			typedef void (*oncontextresize)( void* udata , void* ctx , int width , int height );
			typedef void (*oncontextrender)( void* udata , void* ctx );
			typedef void (*oncontextcreated)( void* udata , void* ctx );
			typedef void (*oncontextbeforedestroy)( void* udata , void* ctx );
		};
	};
	namespace rendering
	{
		class context
		{
		protected:
			void* _udata;
			::booldog::events::typedefs::oncontextresize _oncontextresize;
			::booldog::events::typedefs::oncontextrender _oncontextrender;
			::booldog::events::typedefs::oncontextbeforedestroy _oncontextbeforedestroy;
			::booldog::events::typedefs::oncontextcreated _oncontextcreated;
		public:
			void* udata( void )
			{
				return _udata;
			};
			void udata( void* pudata )
			{
				_udata = pudata;
			};
			context( ::booldog::events::typedefs::oncontextcreated poncontextcreated )
				: _udata( 0 ) /*, _fps( 0 )*/ , _oncontextresize( 0 ) , _oncontextrender( 0 ) , _oncontextbeforedestroy( 0 ) 
				, _oncontextcreated( poncontextcreated )
			{
			};
			virtual void before_resize( void ) = 0;
			virtual void resize( int width , int height ) = 0;
			virtual void after_resize( void ) = 0;
			void raise_onwindowresize( int width , int height )
			{	
				before_resize();
				resize( width , height );	
				after_resize();
			};
			void oncontextresize( ::booldog::events::typedefs::oncontextresize poncontextresize )
			{
				_oncontextresize = poncontextresize;
			};
			virtual void oncontextrender( ::booldog::events::typedefs::oncontextrender poncontextrender )
			{
				_oncontextrender = poncontextrender;
			};
			void oncontextbeforedestroy( ::booldog::events::typedefs::oncontextbeforedestroy poncontextbeforedestroy )
			{
				_oncontextbeforedestroy = poncontextbeforedestroy;
			};
			/*void fps( ::booldog::counters::fps* pfps )
			{
				_fps = pfps;
			};
			void fps( void )
			{
				if( _fps )
				{
					if( _fps->runtime() >= 1000ULL )
					{
						printf( "ctx %p, render fps=%.1f\n" , this , _fps->result() );
						_fps->reset();
					}
					else
						_fps->increment();
				}
			};*/
		};
	};
};
#endif