#ifndef BOO_UI_APPLICATION_H
#define BOO_UI_APPLICATION_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_application.h)
#include BOOLDOG_HEADER(boo_threading_utils.h)
#include BOOLDOG_HEADER(boo_array.h)
#include BOOLDOG_HEADER(boo_rdwrlock.h)
#include BOOLDOG_HEADER(boo_ui_window.h)
namespace booldog
{
	namespace typedefs
	{
		typedef BOOL (WINAPI *PeekMessageA)( LPMSG lpMsg , HWND hWnd , UINT wMsgFilterMin , UINT wMsgFilterMax , UINT wRemoveMsg );
		typedef BOOL (WINAPI *TranslateMessage)( const MSG* lpMsg );
		typedef LRESULT (WINAPI *DispatchMessageA)( const MSG* lpmsg );
		typedef ATOM (WINAPI *RegisterClassA)( const WNDCLASSA* lpWndClass );
		typedef BOOL (WINAPI *GetClassInfoA)( HINSTANCE hInstance , const char* lpClassName , WNDCLASSA* lpWndClass );
		typedef HICON (WINAPI *LoadIconA)( HINSTANCE hInstance , const char* lpIconName );
		typedef HCURSOR (WINAPI *LoadCursorA)( HINSTANCE hInstance , const char* lpCursorName );
		typedef LRESULT (WINAPI *DefWindowProcA)( HWND hWnd , UINT Msg , WPARAM wParam , LPARAM lParam );
		typedef BOOL (WINAPI *InvalidateRect)( HWND hWnd , const RECT* lpRect , BOOL bErase );
		typedef BOOL (WINAPI *ValidateRect)( HWND hWnd , const RECT* lpRect );
	};
	namespace ui
	{
		class application;
	};
	namespace events
	{
		namespace typedefs
		{
			typedef void (*onstarted)( ::booldog::ui::application* app );
		};
	};
};
namespace booldog
{
	namespace ui
	{
		namespace dispatch
		{
			struct data
			{
				::booldog::typedefs::dispatch pdispatch;
				void* pdispatchparam;
				bool wait;
				bool executed;
				::booldog::result* pres;
			};	
		};
		class application : public ::booldog::application
		{
			booldog::threading::rdwrlock _lock_dispatches;
			booldog::array< ::booldog::ui::dispatch::data* > _dispatches;
			booldog::threading::rdwrlock _lock_windows;
			booldog::array< ::booldog::ui::window* > _windows;
			bool _quit;
			::booldog::pid_t _loop_tid;
			::booldog::events::typedefs::onstarted _onstarted;
#ifdef __WINDOWS__
			::booldog::typedefs::DefWindowProcA _pDefWindowProcA;
			::booldog::typedefs::InvalidateRect _pInvalidateRect;
			::booldog::typedefs::ValidateRect _pValidateRect;
#endif
		public:
			application( booldog::allocator* allocator , booldog::base::loader* loader )
				: ::booldog::application( allocator , loader ) , _dispatches( allocator ) , _windows( allocator ) , _onstarted( 0 )
			{
			};
			void onstarted( ::booldog::events::typedefs::onstarted ponstarted )
			{
				_onstarted = ponstarted;
			};
			static booinline ::booldog::uint32 stickcount( void )
			{
				return ::booldog::_application->tickcount();
			};
			static booinline bool dispatch( ::booldog::result* pres , ::booldog::typedefs::dispatch pdispatch , void* pdispatchparam , bool wait 
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );

				::booldog::ui::application* app = (::booldog::ui::application*)::booldog::_application;

				if( app->_loop_tid == ::booldog::threading::threadid() )
					return pdispatch( pres , pdispatchparam );
				if( wait )
				{
					::booldog::ui::dispatch::data data;
					data.pdispatch = pdispatch;
					data.pdispatchparam = pdispatchparam;
					data.wait = wait;
					data.executed = false;
					data.pres = res;

					app->_lock_dispatches.wlock( debuginfo );
					app->_dispatches.add( &data , debuginfo );
					app->_lock_dispatches.wunlock( debuginfo );
	
					while( data.executed == false )
						::booldog::threading::sleep( 1 );
				}
				else
				{
					::booldog::ui::dispatch::data* data = app->allocator()->create< ::booldog::ui::dispatch::data >( debuginfo );
					if( data == 0 )
					{
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						return false;
					}
					data->pdispatch = pdispatch;
					data->pdispatchparam = pdispatchparam;
					data->wait = wait;
					data->executed = false;
					data->pres = 0;

					app->_lock_dispatches.wlock( debuginfo );
					app->_dispatches.add( data , debuginfo );
					app->_lock_dispatches.wunlock( debuginfo );
				}
				return res->succeeded();
			};
			void destroy( ::booldog::ui::window* wnd )
			{
			};
			::booldog::ui::window* create( ::booldog::result* pres , int left , int top , int width , int height
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				::booldog::allocator* pallocator = allocator();
				::booldog::ui::window* window = pallocator->create< ::booldog::ui::window >( pallocator , loader() , left , top 
					, width , height , ::booldog::ui::application::dispatch , debuginfo );
				if( window == 0 )
				{
					res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
					return 0;
				}
				else
				{
					_lock_windows.wlock( debuginfo );
					_windows.add( window , debuginfo );
					_lock_windows.wunlock( debuginfo );
				}
				return window;
			};
			::booldog::ui::window* find( HWND hwnd , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				_lock_windows.rlock( debuginfo );
				for( size_t index0 = 0 ; index0 < _windows.count() ; index0++ )
				{
					if( _windows[ index0 ]->_hwnd == hwnd )
					{
						::booldog::ui::window* wnd = _windows[ index0 ];
						_lock_windows.runlock( debuginfo );
						return wnd;
					}	
				}
				_lock_windows.runlock( debuginfo );
				return 0;	
			}
			static LRESULT CALLBACK WndProc( HWND hwnd , UINT msg , WPARAM wparam , LPARAM lparam )
			{
				::booldog::ui::application* app = (::booldog::ui::application*)::booldog::_application;
				if( hwnd )
				{
					::booldog::ui::window* wnd = app->find( hwnd , debuginfo_macros );
					if( wnd )
					{
						switch( msg )
						{
						case WM_SHOWWINDOW:
							{
								if( wparam == TRUE && lparam == 0 )
									wnd->raise_onshown();
								else if( wparam == FALSE && lparam == 0 )
									wnd->raise_onhided();
								if( lparam == SW_OTHERUNZOOM )
								{
									//if( rux::gui::engine::_winapi_trace )
									//	::rux::log::WriteTrace( "SW_OTHERUNZOOM" );
								}
								else if( lparam == SW_OTHERZOOM )
								{
									//::rux::log::WriteTrace( "SW_OTHERZOOM" );
								}
								else if( lparam == SW_PARENTCLOSING )
								{
									//if( rux::gui::engine::_winapi_trace )
									//	::rux::log::WriteTrace( "SW_PARENTCLOSING" );
								}
								else if( lparam == SW_PARENTOPENING )
								{
									//if( rux::gui::engine::_winapi_trace )
									//	::rux::log::WriteTrace( "SW_PARENTOPENING" );
								}
								break;
							}
						case WM_SIZE:
							{
								int width = (int)(short)LOWORD( lparam );
								int height = (int)(short)HIWORD( lparam );
								if( wparam == SIZE_MAXIMIZED )
								{
								}
								else if( wparam == SIZE_MAXSHOW )
								{
								}
								else if( wparam == SIZE_MINIMIZED )
								{
								}
								else if( wparam == SIZE_RESTORED )
								{	
								}
								wnd->raise_onresize( width , height );
								return 0;
							}
						case WM_DISPLAYCHANGE:
							{
								app->_pInvalidateRect( hwnd , 0 , FALSE );
								return 0;
							}
						case WM_PAINT:
							{
								wnd->raise_onpaint();
								app->_pValidateRect( hwnd , 0 );
								return 0;
							}
						}
					}
				}
				return app->_pDefWindowProcA( hwnd, msg, wparam, lparam );
			};
			virtual void start( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );

				::booldog::result_module resmodUser32;
				::booldog::result_module resmodGdi32;
				::booldog::allocator* pallocator = allocator();
				if( _loader->mbsload( &resmodUser32 , pallocator , "User32" , 0 , debuginfo ) )
				{	
					if( _loader->mbsload( &resmodGdi32 , pallocator , "Gdi32" , 0 , debuginfo ) )
					{
						::booldog::result_pointer resptr;
						if( resmodUser32.module->method( &resptr , pallocator , "PeekMessageA" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						::booldog::typedefs::PeekMessageA pPeekMessageA = (::booldog::typedefs::PeekMessageA)resptr.pres;

						if( resmodUser32.module->method( &resptr , pallocator , "TranslateMessage" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						::booldog::typedefs::TranslateMessage pTranslateMessage = (::booldog::typedefs::TranslateMessage)resptr.pres;

						if( resmodUser32.module->method( &resptr , pallocator , "DispatchMessageA" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						::booldog::typedefs::DispatchMessageA pDispatchMessageA = (::booldog::typedefs::DispatchMessageA)resptr.pres;

						if( resmodUser32.module->method( &resptr , pallocator , "RegisterClassA" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						::booldog::typedefs::RegisterClassA pRegisterClassA = (::booldog::typedefs::RegisterClassA)resptr.pres;

						if( resmodUser32.module->method( &resptr , pallocator , "GetClassInfoA" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						::booldog::typedefs::GetClassInfoA pGetClassInfoA = (::booldog::typedefs::GetClassInfoA)resptr.pres;

						if( resmodUser32.module->method( &resptr , pallocator , "LoadIconA" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						::booldog::typedefs::LoadIconA pLoadIconA = (::booldog::typedefs::LoadIconA)resptr.pres;

						if( resmodUser32.module->method( &resptr , pallocator , "LoadCursorA" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						::booldog::typedefs::LoadCursorA pLoadCursorA = (::booldog::typedefs::LoadCursorA)resptr.pres;
						if( resmodUser32.module->method( &resptr , pallocator , "DefWindowProcA" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						_pDefWindowProcA = (::booldog::typedefs::DefWindowProcA)resptr.pres;					
						if( resmodUser32.module->method( &resptr , pallocator , "InvalidateRect" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						_pInvalidateRect = (::booldog::typedefs::InvalidateRect)resptr.pres;
						if( resmodUser32.module->method( &resptr , pallocator , "ValidateRect" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						_pValidateRect = (::booldog::typedefs::ValidateRect)resptr.pres;	
				
						{
							HMODULE hmod = GetModuleHandle( 0 );
							WNDCLASSA wnd_class;
							if( pGetClassInfoA( hmod , "boo_opengl_window" , &wnd_class ) == false )
							{
								wnd_class.style = CS_DBLCLKS  | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
								wnd_class.lpfnWndProc = (WNDPROC)::booldog::ui::application::WndProc;
								wnd_class.cbClsExtra = 0;
								wnd_class.cbWndExtra = 0;
								wnd_class.hInstance = hmod;
								wnd_class.hIcon = pLoadIconA( NULL , IDI_WINLOGO );
								wnd_class.hCursor = pLoadCursorA( NULL , IDC_ARROW );
								wnd_class.hbrBackground = NULL;
								wnd_class.lpszMenuName = NULL;
								wnd_class.lpszClassName = "boo_opengl_window";
								pRegisterClassA( &wnd_class );
							}
						}

						_loop_tid = ::booldog::threading::threadid();
						_quit = false;
						{
							MSG msg;				
							if( pPeekMessageA( &msg , NULL , 0 , 0 , PM_REMOVE ) )
							{
								pTranslateMessage( &msg ); 
								pDispatchMessageA( &msg );
							}
							if( _onstarted )
								_onstarted( this );
						}
						for( ; ; )
						{
							_lock_windows.rlock( debuginfo );
							if( _windows.count() )
							{
								for( size_t index0 = 0 ; index0 < _windows.count() ; index0++ )
									_windows[ index0 ]->raise_onpaint();
							}
							_lock_windows.runlock( debuginfo );

							_lock_dispatches.wlock( debuginfo );
							if( _dispatches.count() )
							{
								::booldog::ui::dispatch::data* data = 0;
								for( ; ; )
								{
									data = _dispatches[ 0 ];
									_dispatches.remove( 0 , debuginfo );
									_lock_dispatches.wunlock( debuginfo );
									data->pdispatch( data->pres , data->pdispatchparam );
									data->executed = true;
									if( data->wait == false )
										pallocator->destroy< ::booldog::ui::dispatch::data >( data );
									_lock_dispatches.wlock( debuginfo );
									if( _dispatches.count() == 0 )
										break;
								}
							}
							_lock_dispatches.wunlock( debuginfo );

							if( _quit )
								break;
							MSG msg;				
							if( pPeekMessageA( &msg , NULL , 0 , 0 , PM_REMOVE ) )
							{
								pTranslateMessage( &msg ); 
								pDispatchMessageA( &msg );
							}	
							::booldog::threading::sleep( 1 );
						}
					}
					else
						res->copy( resmodGdi32 );
goto_unload:
					_loader->unload( 0 , resmodGdi32.module , 0 , 0 , debuginfo );
					_loader->unload( 0 , resmodUser32.module , 0 , 0 , debuginfo );
				}
				else
					res->copy( resmodUser32 );
			};
			virtual void stop( void )
			{
				_quit = true;
			};
		};
	};
};
#endif