#ifndef BOO_ERROR_FORMAT_H
#define BOO_ERROR_FORMAT_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_string_utils.h)
#include BOOLDOG_HEADER(boo_error.h)
#include BOOLDOG_HEADER(boo_result.h)
namespace booldog
{
	namespace error
	{
		booinline void format( ::booldog::result* pres , booldog::allocator* allocator , char*& mbchar , size_t& mblen 
			, size_t& mbsize_in_bytes , const ::booldog::debug::info& debuginfo = debuginfo_macros )
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
					if( last_error_void )
					{
						::booldog::utils::string::mbs::insert< 0 >( 0 , allocator , false , 0 , mbchar , mblen , mbsize_in_bytes , (char*)last_error_void 
							, 0 , SIZE_MAX , debuginfo );
						LocalFree( last_error_void );
					}
					else
						::booldog::utils::string::mbs::insert< 0 >( 0 , allocator , false , 0 , mbchar , mblen , mbsize_in_bytes , "unknown error" 
							, 0 , SIZE_MAX , debuginfo );
				}
			}
#else
			else if( error_type == ::booldog::enums::result::error_type_dlerror )
			{
				char* dlerrorstr = pres->dlerror();
				if( dlerrorstr )
					::booldog::utils::string::mbs::insert< 0 >( 0 , allocator , false , 0 , mbchar , mblen , mbsize_in_bytes , dlerrorstr
						, 0 , SIZE_MAX , debuginfo );
				else
					::booldog::utils::string::mbs::insert< 0 >( 0 , allocator , false , 0 , mbchar , mblen , mbsize_in_bytes , "unknown error" 
						, 0 , SIZE_MAX , debuginfo );
			}
#endif
		};
	};
};
#endif