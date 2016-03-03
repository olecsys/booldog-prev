#ifndef BOO_UI_WINDOW_H
#define BOO_UI_WINDOW_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_render_context.h)
namespace booldog
{
	namespace ui
	{
		class window;
	};
	namespace typedefs
	{
		typedef BOOL (WINAPI *ShowWindow)( HWND hWnd , int nCmdShow );
		typedef HWND (WINAPI *CreateWindowExA)( DWORD dwExStyle , const char* lpClassName , const char* lpWindowName , DWORD dwStyle 
			, int x , int y , int nWidth , int nHeight , HWND hWndParent , HMENU hMenu , HINSTANCE hInstance , LPVOID lpParam );
		typedef bool (*dispatch)( ::booldog::result* pres , void* param );
		typedef bool (*dispatch_execute)( ::booldog::result* pres , ::booldog::typedefs::dispatch pdispatch , void* pdispatchparam 
			, bool wait , const ::booldog::debug::info& debuginfo );
		typedef BOOL (WINAPI *IsWindowVisible)( HWND hWnd );
	};
	namespace events
	{
		namespace typedefs
		{
			typedef void (*onwindowhided)( ::booldog::ui::window* wnd );
			typedef void (*onwindowshown)( ::booldog::ui::window* wnd );
			typedef void (*onwindowresize)( ::booldog::ui::window* wnd , int width , int height );
			typedef void (*onwindowpaint)( ::booldog::ui::window* wnd );
		};
	};
};
namespace booldog
{
	namespace ui
	{
		class application;
		class window
		{
			friend class ::booldog::ui::application;
			void* _udata;
			int _left;
			int _top;
			int _width;
			int _height;
			::booldog::typedefs::dispatch_execute _dispatch_execute;
			::booldog::events::typedefs::onwindowpaint _onwindowpaint;
			::booldog::events::typedefs::onwindowresize _onwindowresize;
			::booldog::events::typedefs::onwindowhided _onwindowhided;
			::booldog::events::typedefs::onwindowshown _onwindowshown;
		public:
#ifdef __WINDOWS__
			HWND _hwnd;
			HWND hwnd( void )
			{
				return _hwnd;
			};
#else
#endif
			booldog::allocator* _allocator;
			::booldog::base::loader* _loader;
			window( booldog::allocator* allocator , ::booldog::base::loader* ploader , int left , int top , int width , int height 
				, ::booldog::typedefs::dispatch_execute pdispatch_execute )
				: _allocator( allocator ) , _loader( ploader ) , _left( left ) , _top( top ) , _width( width ) 
					, _height( height )	, _hwnd( 0 ) , _dispatch_execute( pdispatch_execute ) , _onwindowpaint( 0 )
					, _onwindowresize( 0 ) , _onwindowhided( 0 ) , _onwindowshown( 0 ) , _udata( 0 )
			{
			};
			void* udata( void )
			{
				return _udata;
			};
			void udata( void* pudata )
			{
				_udata = pudata;
			};
			void raise_onresize( int width , int height )
			{
				if( _width != width 
					|| _height != height )
				{
					_width = width;
					_height = height;
					//if( _ctx )
					//	_ctx->raise_onwindowresize( width , height );
					if( _onwindowresize )
						_onwindowresize( this , width , height );
					/*if( window->_both_size_and_move_msg == 1 )
					{
						rux::gui::WindowMoveEvent xevent( window );
						window->raise_event( xevent );
					}
					rux::gui::WindowSizeEvent xevent( window , window->_width , window->_height );
					window->raise_event( xevent );*/
				}
			};
			void raise_onshown( void )
			{
				if( _onwindowshown )
					_onwindowshown( this );
			};
			void raise_onhided( void )
			{
				if( _onwindowhided )
					_onwindowhided( this );
			};
			void raise_onpaint( void )
			{
				if( _onwindowpaint )
					_onwindowpaint( this );
			};
			void onwindowshown( ::booldog::events::typedefs::onwindowshown ponwindowshown )
			{
				_onwindowshown = ponwindowshown;
			};
			void onwindowhided( ::booldog::events::typedefs::onwindowhided ponwindowhided )
			{
				_onwindowhided = ponwindowhided;
			};
			void onwindowresize( ::booldog::events::typedefs::onwindowresize ponwindowresize )
			{
				_onwindowresize = ponwindowresize;
			};
			void onwindowpaint( ::booldog::events::typedefs::onwindowpaint ponwindowpaint )
			{
				_onwindowpaint = ponwindowpaint;
			};
			int width( void )
			{
				return _width;
			};
			int height( void )
			{
				return _height;
			};
			static bool create( ::booldog::result* pres , void* param )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				
				::booldog::ui::window* wnd = (::booldog::ui::window*)param;
				if( wnd->_hwnd == 0 )
				{
					::booldog::result_module resmod;
					if( wnd->_loader->mbsload( &resmod , wnd->_allocator , "User32" , 0 , debuginfo_macros ) )
					{	
						::booldog::result_pointer resptr;
						if( resmod.module->method( &resptr , wnd->_allocator , "CreateWindowExA" , debuginfo_macros ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						::booldog::typedefs::CreateWindowExA pCreateWindowExA = (::booldog::typedefs::CreateWindowExA)resptr.pres;					

						DWORD ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE , style = WS_OVERLAPPEDWINDOW;// WS_POPUP;
//						rux::uint8 is_fullscreen = 0;
//						if( is_fullscreen == 1 )
//						{	
//							ex_style = WS_EX_APPWINDOW;
//							ShowCursor( false );
//						}
//						if( window->_is_top_most )
//							ex_style |= WS_EX_TOPMOST;
						wnd->_hwnd = pCreateWindowExA( ex_style , "boo_opengl_window" , "" 
							, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | style , wnd->_left , wnd->_top , wnd->_width , wnd->_height , NULL 
							, NULL , GetModuleHandle( NULL ) , NULL );
						if( wnd->_hwnd )
						{
//							if( rux::gui::engine::_winapi_trace )
//								::rux::log::WriteTrace( "CreateWindowExA, hwnd=%p" , window->_hwnd );
//							SetWindowLongPtrA( window->_hwnd , GWLP_USERDATA , (LONG_PTR)window );
						}
						else
							res->GetLastError();
	goto_unload:
						wnd->_loader->unload( 0 , resmod.module , 0 , 0 , debuginfo_macros );
					}
					else
						res->copy( resmod );
				}
				return res->succeeded();
			};
			bool visible( void )
			{
				bool res = false;
				if( _hwnd )
				{
					::booldog::result_module resmod;
					if( _loader->mbsload( &resmod , _allocator , "User32" , 0 , debuginfo_macros ) )
					{	
						::booldog::result_pointer resptr;
						if( resmod.module->method( &resptr , _allocator , "IsWindowVisible" , debuginfo_macros ) == false )
							goto goto_unload;
						::booldog::typedefs::IsWindowVisible pIsWindowVisible = (::booldog::typedefs::IsWindowVisible)resptr.pres;
						res = pIsWindowVisible( _hwnd ) ? true : false;
goto_unload:
						_loader->unload( 0 , resmod.module , 0 , 0 , debuginfo_macros );
					}
				}
				return res;
			};
			bool show( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				if( _dispatch_execute( res , ::booldog::ui::window::create , this , true , debuginfo ) )
				{
					::booldog::result_module resmod;
					if( _loader->mbsload( &resmod , _allocator , "User32" , 0 , debuginfo ) )
					{	
						::booldog::result_pointer resptr;
						if( resmod.module->method( &resptr , _allocator , "ShowWindow" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						::booldog::typedefs::ShowWindow pShowWindow = (::booldog::typedefs::ShowWindow)resptr.pres;
						pShowWindow( _hwnd , SW_SHOWNOACTIVATE );
	goto_unload:
						_loader->unload( 0 , resmod.module , 0 , 0 , debuginfo );
					}
					else
						res->copy( resmod );
				}
				return res->succeeded();
			};
		};
	};
};
#endif