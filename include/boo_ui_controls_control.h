#ifndef BOO_UI_CONTROLS_CONTROL_H
#define BOO_UI_CONTROLS_CONTROL_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_ui_controls_render.h)
namespace booldog
{
	namespace ui
	{
		namespace controls
		{
			class control
			{
			public:
				virtual bool visible( void ) = 0;
				virtual bool inside( int x , int y ) = 0;
				virtual void render( void* ctx , ::booldog::ui::controls::render* prender ) = 0;
			};
		};
	};
};
#endif