#ifndef BOO_STRING_UTILS_H
#define BOO_STRING_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_result.h>
#include <boo_allocator.h>
#include <boo_mem.h>
#include <boo_error.h>
#ifdef __UNIX__
#include <unistd.h>
#endif
namespace booldog
{	
	namespace utils
	{
		namespace string
		{
			namespace mbs
			{
				bool insert( ::booldog::result_bool* pres , size_t dstcharindex , char*& dst , size_t& dstlen 
					, size_t& dstsize_in_bytes , const char* src , size_t srccharindex = 0 , size_t srccharcount = SIZE_MAX 
					, booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_bool locres;
					BOOINIT_RESULT( ::booldog::result_bool );
					if( src )
					{
						const char* srcbegin = &src[ srccharindex ];
						if( *srcbegin != 0 )
						{
							const char* ptr = srcbegin;
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case 0:
									goto goto_next;
								}
								if( (size_t)( ptr - srcbegin ) >= srccharcount )
								{
									ptr++;
									break;
								}
							}
goto_next:
							if( dstcharindex > dstlen )
								dstcharindex = dstlen;
							srccharcount = ptr - srcbegin - 1;
							if( dstlen + srccharcount + 1 > dstsize_in_bytes )
							{
								dstsize_in_bytes = dstlen + srccharcount + 1;
								dst = allocator->realloc_array< char >( dst , dstsize_in_bytes , debuginfo );
							}
							if( dst )
							{
								::booldog::mem::insert< char >( dstcharindex , dst , dstlen , dstsize_in_bytes , 0 , srcbegin , srccharcount );
								dstlen += srccharcount;
								dst[ dstlen ] = 0;
							}
							else
								res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
					return res->succeeded();
				}
			};
			namespace wcs
			{
				bool insert( ::booldog::result_bool* pres , size_t dstcharindex , wchar_t*& dst , size_t& dstlen 
					, size_t& dstsize_in_bytes , const wchar_t* src , size_t srccharindex = 0 , size_t srccharcount = SIZE_MAX 
					, booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_bool locres;
					BOOINIT_RESULT( ::booldog::result_bool );
					if( src )
					{
						const wchar_t* srcbegin = &src[ srccharindex ];
						if( *srcbegin != 0 )
						{
							const wchar_t* ptr = srcbegin;
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case 0:
									goto goto_next;
								}
								if( (size_t)( ptr - srcbegin ) >= srccharcount )
								{
									ptr++;
									break;
								}
							}
goto_next:
							if( dstcharindex > dstlen )
								dstcharindex = dstlen;
							dstsize_in_bytes /= sizeof( wchar_t );
							srccharcount = ptr - srcbegin - 1;
							if( dstlen + srccharcount + 1 > dstsize_in_bytes )
							{
								dstsize_in_bytes = dstlen + srccharcount + 1;
								dst = allocator->realloc_array< wchar_t >( dst , dstsize_in_bytes , debuginfo );
							}
							if( dst )
							{
								::booldog::mem::insert< wchar_t >( dstcharindex , dst , dstlen , dstsize_in_bytes , 0 , srcbegin , srccharcount );
								dstlen += srccharcount;
								dstsize_in_bytes *= sizeof( wchar_t );
								dst[ dstlen ] = 0;
							}
							else
								res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
					return res->succeeded();
				}
			};
			//booinline size_t wcsindexof( const wchar_t* src , const wchar_t* 
		};
	};
};
#endif