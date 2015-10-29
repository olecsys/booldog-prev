#include <boo_object.h>
#include <boo_if.h>
#include <boo_check.h>
#include <boo_string.h>
#include <boo_array.h>
#include <boo_stack.h>
#include <boo_string.h>
int main( int argc , char **argv )
{
	argc = argc;
	argv = argv;

	::booldog::allocators::stack::simple< 4096 > allocator;

	::booldog::_allocator = &allocator;

	{
		::booldog::string string( (const char*)0 );

		bool res = strcmp( string.str() , "" ) == 0;

		res = string.length() == 0;

		res = string.bytes() == 0;
	}

	{
		::booldog::string string( "" );

		bool res = strcmp( string.str() , "" ) == 0;

		res = string.length() == 0;

		res = string.bytes() == 0;
	}

	{
		::booldog::string string( "TEST" );

		bool res = strcmp( string.str() , "TEST" ) == 0;

		res = string.length() == 4;

		res = string.bytes() == 5;
	}

	{
		::booldog::string string( "Hello, TEST" , 7 );

		bool res = strcmp( string.str() , "TEST" ) == 0;

		res = string.length() == 4;

		res = string.bytes() == 5;
	}

	{
		::booldog::string string( "Hello, TEST, it's our first meeting" , 6 , 4 );

		bool res = strcmp( string.str() , "TEST" ) == 0;

		res = string.length() == 4;

		res = string.bytes() == 5;
	}


	//MessageBox( 0 , 0 , 0 , MB_OK );

	////HMODULE handle = LoadLibraryW( L"opengl32.dll" );

	//size_t displays_count = 0;
	//booldog::uint32 display_bits = 0;
	//DISPLAY_DEVICEA display_device;
	//memset( &display_device , 0 , sizeof( DISPLAY_DEVICEA ) );
	//display_device.cb = sizeof( display_device );
	//char device_name[ 32 ] = { 0 } , device_string[ 128 ] = { 0 };
	//::booldog::int32 device_index = 0;
	//while( EnumDisplayDevicesA( NULL , device_index , &display_device , 0 ) )
	//{
	//	if( ( display_device.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP ) )
	//	{
	//		strcpy( device_name , display_device.DeviceName );
	//		//::rux::safe_strncpy( device_name , display_device.DeviceName , 32 );
	//		//::rux::safe_strncpy( device_string, display_device.DeviceString , 128 );
	//		::booldog::int32 monitor_index = 0;
	//		if( EnumDisplayDevicesA( device_name , monitor_index , &display_device , 0 ) )
	//		{
	//			DEVMODEA dev_mode;
	//			memset( &dev_mode , 0 , sizeof( DEVMODEA ) );
	//			dev_mode.dmSize = sizeof( DEVMODEA );
	//			dev_mode.dmDriverExtra = 0;
	//			if( EnumDisplaySettingsExA( device_name , ENUM_CURRENT_SETTINGS , &dev_mode , EDS_RAWMODE ) )
	//			{
	//				if( displays_count == 0 )
	//					display_bits = dev_mode.dmBitsPerPel;
	//				//::rux::gui::engine::_display_bits[ ::rux::gui::engine::_displays_count ] = dev_mode.dmBitsPerPel;
	//				//::rux::gui::engine::_display_frequencies[ ::rux::gui::engine::_displays_count ] = dev_mode.dmDisplayFrequency;
	//				displays_count++;
	//			}
	//			monitor_index++;
	//		}
	//	}
	//	device_index++;
	//}



	//WNDCLASSA wnd_class;
	//if( GetClassInfoA( GetModuleHandle( NULL ) , "rux_ui_window" , &wnd_class ) == false )
	//{
	//	wnd_class.style = CS_DBLCLKS  | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	//	wnd_class.lpfnWndProc = DefWindowProc;
	//	wnd_class.cbClsExtra = 0;
	//	wnd_class.cbWndExtra = 0;
	//	wnd_class.hInstance = GetModuleHandle( NULL );
	//	wnd_class.hIcon = LoadIcon( NULL , IDI_WINLOGO );
	//	wnd_class.hCursor = LoadCursor( NULL , IDC_ARROW );
	//	wnd_class.hbrBackground = NULL;
	//	wnd_class.lpszMenuName = NULL;
	//	wnd_class.lpszClassName = "rux_ui_window";
	//	RegisterClassA( &wnd_class );
	//}



	//booldog::uint32 ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE , style = WS_POPUP;
	//booldog::uint8 is_fullscreen = 0;
	//if( is_fullscreen == 1 )
	//{	
	//	ex_style = WS_EX_APPWINDOW;
	//	ShowCursor( false );
	//}

	//HWND hwnd = CreateWindowExA( ex_style , "rux_ui_window" , "" , WS_CLIPSIBLINGS | WS_CLIPCHILDREN | style , 0 , 0 , 200 , 200 , NULL , NULL , GetModuleHandle( NULL ) , NULL );
	//
	//SetWindowPos( hwnd , HWND_NOTOPMOST , 49 , 1544 , 921 , 691 , SWP_NOACTIVATE );					

	//ShowWindow( hwnd , SW_SHOWNOACTIVATE );

	//HDC hdc = GetDC( hwnd );

	//PIXELFORMATDESCRIPTOR _pfd;
 //   _pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );
	//_pfd.nVersion = 1;
	//_pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	//_pfd.iPixelType = PFD_TYPE_RGBA;

	//if( displays_count > 0 )
	//	_pfd.cColorBits = display_bits;
	//else
	//	_pfd.cColorBits = 32;//pfd.cColorBits     = 32;
	//_pfd.cRedBits = 0;//_pfd.cRedBits       = 8;
	//_pfd.cRedShift = 0;//_pfd.cRedShift      = 16;
	//_pfd.cGreenBits = 0;//_pfd.cGreenBits     = 8;
	//_pfd.cGreenShift = 0;//_pfd.cGreenShift    = 8;
	//_pfd.cBlueBits = 0;//_pfd.cBlueBits      = 8;
	//_pfd.cBlueShift = 0;
	//_pfd.cAlphaBits = 0;
	//_pfd.cAlphaShift = 0;
	//_pfd.cAccumBits = 0;    //_pfd.cAccumBits     = 64;    
	//_pfd.cAccumRedBits = 0;//_pfd.cAccumRedBits  = 16;
	//_pfd.cAccumGreenBits = 0;//_pfd.cAccumGreenBits   = 16;
	//_pfd.cAccumBlueBits = 0;//_pfd.cAccumBlueBits    = 16;
	//_pfd.cAccumAlphaBits = 0;
	//_pfd.cDepthBits = 32;
	//_pfd.cStencilBits = 32;//_pfd.cStencilBits      = 8;
	//_pfd.cAuxBuffers = 0;
	//_pfd.iLayerType = PFD_MAIN_PLANE;
	//_pfd.bReserved = 0;
	//_pfd.dwLayerMask = 0;
	//_pfd.dwVisibleMask = 0;
	//_pfd.dwDamageMask = 0;		
	//booldog::int32 pixel_format_index = ChoosePixelFormat( hdc , &_pfd );
	//if( pixel_format_index == 0 )
	//{
	//	pixel_format_index = 1;    
	//	if( DescribePixelFormat( hdc , pixel_format_index , sizeof( PIXELFORMATDESCRIPTOR ) , &_pfd ) == 0 )
	//	{
	//	}
	//}
	//if( SetPixelFormat( hdc, pixel_format_index, &_pfd ) == FALSE )
	//{
	//}
	////FreeLibrary( handle );
    return 0;
};