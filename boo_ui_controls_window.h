#ifndef BOO_UI_CONTROLS_WINDOW_H
#define BOO_UI_CONTROLS_WINDOW_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_ui_application.h"
#include "boo_ui_controls_control.h"
#include "boo_fps_counter.h"
namespace booldog
{
	namespace ui
	{
		namespace controls
		{
			class window
			{
				::booldog::counters::fps _fps;
				::booldog::ui::application* _app;
				::booldog::ui::window* _wnd;
				::booldog::ui::controls::render* _render;
				void* _ctx;
			public:
				static void onwindowshown( ::booldog::ui::window* wnd )
				{
					::booldog::ui::controls::window* _this = (::booldog::ui::controls::window*)wnd->udata();
					if( _this->_ctx == 0 )
						_this->render( _this->_render , false );
				};
				static void onwindowhided( ::booldog::ui::window* wnd )
				{
					::booldog::ui::controls::window* _this = (::booldog::ui::controls::window*)wnd->udata();
				};
				static void onwindowresize( ::booldog::ui::window* wnd , int width , int height )
				{
					::booldog::ui::controls::window* _this = (::booldog::ui::controls::window*)wnd->udata();
					if( _this->_ctx )
						_this->_render->raise_onwindowresize( _this->_ctx , width , height );
				};
				static void oncontextresize( void* udata , void* ctx , int width , int height )
				{
					::booldog::ui::controls::window* _this = (::booldog::ui::controls::window*)udata;
				};
				static void oncontextrender( void* udata , void* ctx )
				{
					::booldog::ui::controls::window* _this = (::booldog::ui::controls::window*)udata;
					if( _this->_fps.runtime() >= 1000ULL )
					{
						printf( "ctx %p, render fps=%.1f\n" , ctx , _this->_fps.result() );
						_this->_fps.reset();
					}
					else
						_this->_fps.increment();
				};
				static void oncontextcreated( void* udata , void* ctx )
				{
					::booldog::ui::controls::window* _this = (::booldog::ui::controls::window*)udata;
				};
				static void oncontextbeforedestroy( void* udata , void* ctx )
				{
					::booldog::ui::controls::window* _this = (::booldog::ui::controls::window*)udata;
				};
				static void onwindowpaint( ::booldog::ui::window* wnd )
				{
					::booldog::ui::controls::window* _this = (::booldog::ui::controls::window*)wnd->udata();
					if( _this->_ctx )
						_this->_render->onwindowpaint( _this->_ctx );
				};
				window( ::booldog::result* res , ::booldog::ui::application* app , int x , int y , int width
					, int height , const ::booldog::debug::info& debuginfo = debuginfo_macros )
					: _render( 0 ) , _app( app ) , _ctx( 0 ) , _fps( app->stickcount )
				{
					_wnd = app->create( res , x , y , width , height , debuginfo );
					_wnd->udata( this );
					_wnd->onwindowshown( onwindowshown );
					_wnd->onwindowhided( onwindowhided );
					_wnd->onwindowresize( onwindowresize );
				};
				void render( ::booldog::ui::controls::render* prender , bool check_wnd_visibility = true )
				{
					if( _render )
					{
						if( _ctx )
						{
							_render->destroy_context( _ctx );
							_ctx = 0;
						}
					}
					if( prender )
					{
						if( check_wnd_visibility == false || _wnd->visible() )
						{
							_ctx = prender->create_context( _wnd->hwnd() , this , prender->factory( _app->allocator() , _app->loader() ) 
								, oncontextcreated , oncontextresize , oncontextrender , oncontextbeforedestroy );
							if( prender->onwindowpaint )
								_wnd->onwindowpaint( onwindowpaint );
							else
								_wnd->onwindowpaint( 0 );
						}
					}
					_render = prender;
				};
				~window( void )
				{
					this->render( 0 );
					_app->destroy( _wnd );
				};
				bool show( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					return _wnd->show( pres , debuginfo );
				};
			};
		};
	};
};
#endif