#ifndef BOO_MONITOR_H
#define BOO_MONITOR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_base_loader.h"
namespace booldog
{
	namespace typedefs
	{
#ifdef __WINDOWS__
		typedef BOOL (WINAPI *EnumDisplayDevicesA)( const char* lpDevice , DWORD iDevNum , PDISPLAY_DEVICEA lpDisplayDevice , DWORD dwFlags );
		typedef BOOL (WINAPI *EnumDisplaySettingsExA)( const char* lpszDeviceName , DWORD iModeNum , DEVMODEA* lpDevMode , DWORD dwFlags );
#else
#endif
	};
	namespace events
	{
		namespace typedefs
		{
			typedef void (*onmonitorfound)( void* udata , int x , int y , int width , int height );
		};
	};
	namespace system
	{
		class monitor
		{
		public:
			static booinline bool enumerate( ::booldog::result* pres , ::booldog::allocator* pallocator , ::booldog::base::loader* ploader
				, ::booldog::events::typedefs::onmonitorfound ponmonitorfound , void* udata 
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
				::booldog::result_module resmodUser32;
				if( ploader->mbsload( &resmodUser32 , pallocator , "User32" , 0 , debuginfo ) )
				{
					::booldog::result_pointer resptr;
					if( resmodUser32.module->method( &resptr , pallocator , "EnumDisplayDevicesA" , debuginfo ) == false )
					{
						res->copy( resptr );
						goto goto_unload;
					}
					::booldog::typedefs::EnumDisplayDevicesA pEnumDisplayDevicesA = (::booldog::typedefs::EnumDisplayDevicesA)resptr.pres;
					if( resmodUser32.module->method( &resptr , pallocator , "EnumDisplaySettingsExA" , debuginfo ) == false )
					{
						res->copy( resptr );
						goto goto_unload;
					}
					::booldog::typedefs::EnumDisplaySettingsExA pEnumDisplaySettingsExA = (::booldog::typedefs::EnumDisplaySettingsExA)resptr.pres;
					
					DISPLAY_DEVICEA card_device;
					memset( &card_device , 0 , sizeof( DISPLAY_DEVICEA ) );
					card_device.cb = sizeof( card_device );
					DWORD device_index = 0;
					while( pEnumDisplayDevicesA( NULL , device_index , &card_device , 0 ) )
					{
						if( ( card_device.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP ) )
						{
							DISPLAY_DEVICEA display_device;
							memset( &display_device , 0 , sizeof( DISPLAY_DEVICEA ) );
							display_device.cb = sizeof( display_device );
							DWORD monitor_index = 0;
							if( pEnumDisplayDevicesA( card_device.DeviceName , monitor_index , &display_device , 0 ) )
							{
								DEVMODEA dev_mode;
								memset( &dev_mode , 0 , sizeof( DEVMODEA ) );
								dev_mode.dmSize = sizeof( DEVMODEA );
								dev_mode.dmDriverExtra = 0;
								if( pEnumDisplaySettingsExA( card_device.DeviceName , ENUM_CURRENT_SETTINGS , &dev_mode , EDS_RAWMODE ) )
									ponmonitorfound( udata , dev_mode.dmPosition.x , dev_mode.dmPosition.y , dev_mode.dmPelsWidth 
										, dev_mode.dmPelsHeight );
								monitor_index++;
							}
						}
						device_index++;
					}
goto_unload:
					if( resmodUser32.module )
						ploader->unload( 0 , resmodUser32.module , 0 , 0 , debuginfo );
				}
				else
					res->copy( resmodUser32 );
#else
#endif
				return res->succeeded();
			};
		};
	}
};
#endif