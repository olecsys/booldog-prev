#ifndef BOO_ERROR_FORMAT_H
#define BOO_ERROR_FORMAT_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_string_utils.h>
#include <boo_error.h>
#include <boo_result.h>
namespace booldog
{
	namespace error
	{
		booinline void format( ::booldog::result* pres , char*& mbchar , size_t& mblen , size_t& mbsize_in_bytes , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
		{
			booldog::enums::result::error_type error_type = pres->get_error_type();
			if( error_type == ::booldog::enums::result::error_type_errno )
			{
			}
			else if( error_type == ::booldog::enums::result::error_type_booerr )
			{
			}
#ifdef __WINDOWS__
			else if( error_type == ::booldog::enums::result::error_type_GetLastError )
			{
				if( pres->get_last_error != 0 )
				{
					void* last_error_void = NULL;
					FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS , NULL , pres->get_last_error , MAKELANGID( LANG_NEUTRAL , SUBLANG_DEFAULT ) , (char*)&last_error_void , 0 , NULL );
					::booldog::result resres;
					if( last_error_void )
					{
						::booldog::utils::string::mbs::insert( &resres , 0 , mbchar , mblen , mbsize_in_bytes , (char*)last_error_void 
							, 0 , SIZE_MAX , allocator , debuginfo );
						LocalFree( last_error_void );
					}
					else
					{
						::booldog::utils::string::mbs::insert( &resres , 0 , mbchar , mblen , mbsize_in_bytes , "unknown error" 
							, 0 , SIZE_MAX , allocator , debuginfo );
					}
				}
			}
#endif
		};
	};
};
#endif