#ifndef BOO_UI_CONTROLS_RENDER_H
#define BOO_UI_CONTROLS_RENDER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_media_enums.h"
#include "boo_render_context.h"
namespace booldog
{
	namespace typedefs
	{
		typedef void* (*create_factory)( void* allocator , void* loader );
		typedef void (*destroy_factory)( void* factory );

		typedef void* (*create_context)( HWND hwnd , void* udata , void* factory 
			, ::booldog::events::typedefs::oncontextcreated poncontextcreated
			, ::booldog::events::typedefs::oncontextresize poncontextresize
			, ::booldog::events::typedefs::oncontextrender poncontextrender 
			, ::booldog::events::typedefs::oncontextbeforedestroy poncontextbeforedestroy );

		typedef void (*onwindowpaintevent)( void* ctx );
		typedef void (*raise_onwindowresize)( void* ctx , int width , int height );

		typedef void (*destroy_context)( void* ctx );

		typedef void* (*create_rectangle_resource)( void* ctx );
		typedef bool (*set_rectangle_resource_position)( void* resource , int left , int top );
		typedef bool (*set_rectangle_resource_size)( void* resource , int width , int height );
		typedef bool (*draw_rectangle_resource)( void* resource );
		typedef bool (*free_rectangle_resource)( void* resource );

		typedef bool (*push_clip_rectangle)( void* ctx , int left , int top , int width , int height , void*& reshandle );
		typedef bool (*pop_clip_rectangle)( void* ctx , void* reshandle );
		typedef bool (*copy_image)( void* ctx , ::booldog::enums::media::fourcc fourcc , int width , int height , void* data );
		typedef bool (*draw_rectangle)( float left , float top , float width , float height );
	};
	namespace ui
	{
		namespace controls
		{
			class render
			{
				void* _factory;
			public:
				::booldog::typedefs::create_factory create_factory;
				::booldog::typedefs::destroy_factory destroy_factory;

				::booldog::typedefs::create_context create_context;
				::booldog::typedefs::onwindowpaintevent onwindowpaint;
				::booldog::typedefs::raise_onwindowresize raise_onwindowresize;
				::booldog::typedefs::destroy_context destroy_context;
			public:
				render( ::booldog::typedefs::create_factory pcreate_factory , ::booldog::typedefs::destroy_factory pdestroy_factory 
					, ::booldog::typedefs::create_context pcreate_context 
					, ::booldog::typedefs::raise_onwindowresize praise_onwindowresize
					, ::booldog::typedefs::onwindowpaintevent ponwindowpaint
					, ::booldog::typedefs::destroy_context pdestroy_context )
					: _factory( 0 ) , create_factory( pcreate_factory ) , destroy_factory( pdestroy_factory ) 
					, create_context( pcreate_context ) , destroy_context( pdestroy_context ) 
					, raise_onwindowresize( praise_onwindowresize ) , onwindowpaint( ponwindowpaint )
				{
				};
				void* factory( void* allocator , void* loader )
				{
					if( _factory == 0 )
						_factory = create_factory( allocator , loader );
					return _factory;
				};
			};
		};
	};
};
#endif