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
#include <wchar.h>
#endif
namespace booldog
{	
	namespace utils
	{
		namespace string
		{
			namespace mbs
			{
				bool towcs( ::booldog::result_wchar* pres , const char* mbchar , size_t charindex = 0 , size_t charcount = SIZE_MAX , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result_wchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_wchar );
					const char* begin = &mbchar[ charindex ];
					const char* ptr = begin;
					for( ; ; )
					{
						switch( *ptr++ )
						{
						case 0:
							goto goto_next;
						}
						if( (size_t)( ptr - begin ) >= charcount )
						{
#ifdef __WINDOWS__
							ptr++;
#else
							charcount = ptr - begin;
							char* newbegin = allocator->realloc_array< char >( 0 , charcount + 1 , debuginfo );
							if( newbegin )
							{
								::memcpy( newbegin , begin , charcount );
								newbegin[ charcount ] = 0;
								begin = newbegin;
								ptr = &newbegin[ charcount ];
								ptr++;
							}
							else
							{
								res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
								goto goto_return;
							}
#endif
							break;
						}
					}
goto_next:
					charcount = ptr - begin - 1;
					res->wsize = charcount + 1;
					res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
					if( res->wchar )
					{
#ifdef __WINDOWS__
						res->wlen = MultiByteToWideChar( CP_ACP , MB_USEGLYPHCHARS , begin , (int)charcount , res->wchar , (int)res->wsize );
						if( res->wlen == 0 )
						{
							DWORD get_last_error = GetLastError();
							if( get_last_error == ERROR_INSUFFICIENT_BUFFER )
							{
								res->wlen = MultiByteToWideChar( CP_ACP , MB_USEGLYPHCHARS , begin , (int)charcount , res->wchar , 0 );
								if( res->wlen > 0 )
								{
									res->wsize = res->wlen + 1;
									res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
									if( res->wchar )
									{
										res->wlen = MultiByteToWideChar( CP_ACP , MB_USEGLYPHCHARS , begin , (int)charcount , res->wchar , (int)res->wsize );
										if( res->wlen > 0 )
										{
											res->wchar[ res->wlen ] = 0;
											res->wsize *= sizeof( wchar_t );
										}
										else
											res->GetLastError();
									}
									else
										res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
								}
								else
									res->GetLastError();
							}
							else
								res->GetLastError( get_last_error );
						}
						else
						{
							if( res->wlen == res->wsize )
							{
								res->wsize = res->wlen + 1;
								res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
								if( res->wchar )
								{
									res->wchar[ res->wlen ] = 0;
									res->wsize *= sizeof( wchar_t );
								}
								else
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );	
							}
							else
							{
								res->wchar[ res->wlen ] = 0;
								res->wsize *= sizeof( wchar_t );
							}
						}
#else
						mbstate_t state;
						::memset( &state , 0 , sizeof( state ) );
						const char* src = begin;
						res->wlen = mbsrtowcs( res->wchar , &src , res->wsize - 1 , &state );
						if( res->wlen != (size_t)-1 )
						{
							if( src != 0 && src < ptr - 1 )
							{
								::memset( &state , 0 , sizeof( state ) );
								src = begin;
								res->wlen = mbsrtowcs( 0 , &src , 0 , &state );
								if( res->wlen != (size_t)-1 )
								{
									res->wsize = res->wlen + 1;
									res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
									if( res->wchar )
									{
										::memset( &state , 0 , sizeof( state ) );
										src = begin;
										res->wlen = mbsrtowcs( res->wchar , &src , res->wsize - 1 , &state );
										if( res->wlen != (size_t)-1 )
										{
											res->wchar[ res->wlen ] = 0;
											res->wsize *= sizeof( wchar_t );
										}
										else
											res->seterrno();
									}
									else
										res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
								}
								else
									res->seterrno();
							}
							else
							{
								if( res->wlen == res->wsize )
								{
									res->wsize = res->wlen + 1;
									res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
									if( res->wchar )
									{
										res->wchar[ res->wlen ] = 0;
										res->wsize *= sizeof( wchar_t );
									}
									else
										res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );	
								}
								else
								{
									res->wchar[ res->wlen ] = 0;
									res->wsize *= sizeof( wchar_t );
								}
							}

						}
						else
							res->seterrno();
						if( begin != &mbchar[ charindex ] )
							allocator->free( (void*)begin );
#endif
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
goto_return:
					return res->succeeded();
				};
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
				bool insert( ::booldog::result* pres , size_t dstcharindex , wchar_t*& dst , size_t& dstlen 
					, size_t& dstsize_in_bytes , const char* src , size_t srccharindex = 0 , size_t srccharcount = SIZE_MAX 
					, booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
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
#ifdef __WINDOWS__
									ptr++;
#else
									srccharcount = ptr - srcbegin;
									char* newbegin = allocator->realloc_array< char >( 0 , srccharcount + 1 , debuginfo );
									if( newbegin )
									{
										::memcpy( newbegin , srcbegin , srccharcount );
										newbegin[ srccharcount ] = 0;
										srcbegin = newbegin;
										ptr = &newbegin[ srccharcount ];
										ptr++;
									}
									else
									{
										res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
										goto goto_return;
									}
#endif
									break;
								}
							}
goto_next:
							if( dstcharindex > dstlen )
								dstcharindex = dstlen;
							srccharcount = ptr - srcbegin - 1;
#ifdef __WINDOWS__
							size_t srcwcharcount = MultiByteToWideChar( CP_ACP , MB_USEGLYPHCHARS , srcbegin , (int)srccharcount , dst , 0 );
							if( srcwcharcount > 0 )
#else
							mbstate_t state;
							::memset( &state , 0 , sizeof( state ) );
							const char* mbsrtowcssrc = srcbegin;
							size_t srcwcharcount = mbsrtowcs( 0 , &mbsrtowcssrc , 0 , &state );
							if( srcwcharcount != (size_t)-1 )
#endif							
							{
								dstsize_in_bytes /= sizeof( wchar_t );
								if( dstlen + srcwcharcount + 1 > dstsize_in_bytes )
								{
									dstsize_in_bytes = dstlen + srcwcharcount + 1;
									dst = allocator->realloc_array< wchar_t >( dst , dstsize_in_bytes , debuginfo );
								}
								if( dst )
								{
									::booldog::mem::expand< wchar_t >( dstcharindex , dst , dstlen , dstsize_in_bytes , srcwcharcount );
#ifdef __WINDOWS__
									srcwcharcount = MultiByteToWideChar( CP_ACP , MB_USEGLYPHCHARS , srcbegin , (int)srccharcount , &dst[ dstcharindex ] , (int)( dstsize_in_bytes - dstcharindex ) );
									if( srcwcharcount > 0 )
#else
									::memset( &state , 0 , sizeof( state ) );
									mbsrtowcssrc = srcbegin;
									srcwcharcount = mbsrtowcs( &dst[ dstcharindex ] , &mbsrtowcssrc , srcwcharcount , &state );
									if( srcwcharcount != (size_t)-1 )
#endif
									{
										dstlen += srcwcharcount;
										dst[ dstlen ] = 0;
									}
									else
#ifdef __WINDOWS__
										res->GetLastError();
#else
										res->seterrno();
#endif
								}
								else
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
								dstsize_in_bytes *= sizeof( wchar_t );
							}
							else
#ifdef __WINDOWS__
								res->GetLastError();
#else
								res->seterrno();
							if( srcbegin != &src[ srccharindex ] )
								allocator->free( (void*)srcbegin );
#endif
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
goto_return:
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
		};
	};
};
#endif