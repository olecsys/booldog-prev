#ifndef BOO_STRING_UTILS_H
#define BOO_STRING_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_result.h)
#include BOOLDOG_HEADER(boo_allocator.h)
#include BOOLDOG_HEADER(boo_mem.h)
#include BOOLDOG_HEADER(boo_error.h)
#include BOOLDOG_HEADER(boo_utf16.h)
#include BOOLDOG_HEADER(boo_utf32.h)
#include BOOLDOG_HEADER(boo_if.h)

#ifdef __UNIX__
#ifndef _LARGEFILE64_SOURCE 
#define _LARGEFILE64_SOURCE 
#endif
#include <unistd.h>
#include <wchar.h>
#endif
#include <stdio.h>
#include <stdarg.h>
namespace booldog
{	
	namespace utils
	{
		namespace string
		{
			namespace mbs
			{
				booinline int vscprintf( const char* format , va_list pargs )
				{
#ifdef __WINDOWS__
					return ::_vscprintf( format , pargs );
#else
					va_list argcopy;
					va_copy( argcopy , pargs ); 
					int retval = ::vsnprintf( NULL , 0 , format , argcopy ); 
					va_end( argcopy );
					return retval;
#endif
				};
				booinline bool sprintf( ::booldog::result_mbchar* pres , ::booldog::allocator* allocator , const char* format
					, va_list pargs , const ::booldog::debug::info& debuginfo )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
					size_t size = ::booldog::utils::string::mbs::vscprintf( format , pargs ) + 1;
					if( size > res->mbsize )
					{
						res->mbsize = size;
						res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
					}
					if( res->mbchar )
					{
#ifdef __WINDOWS__
						vsprintf_s( res->mbchar , res->mbsize , format , pargs );
#else
						vsnprintf( res->mbchar , res->mbsize , format , pargs );
#endif
						res->mblen = size - 1;
						res->mbchar[ res->mblen ] = 0;
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
					return res->succeeded();
				};
				booinline bool sprintf( ::booldog::result_mbchar* pres , ::booldog::allocator* allocator
					, const ::booldog::debug::info& debuginfo , const char* format , ... )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
					va_list ap;
					va_start( ap , format );
					::booldog::utils::string::mbs::sprintf( res , allocator , format , ap , debuginfo );
					va_end( ap );
					return res->succeeded();
				};
				booinline bool towcs( ::booldog::result_wchar* pres , booldog::allocator* allocator , const char* mbchar , size_t charindex = 0 , size_t charcount = SIZE_MAX , const ::booldog::debug::info& debuginfo = debuginfo_macros )
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
#ifndef __WINDOWS__
goto_return:
#endif
					return res->succeeded();
				};
				booinline bool lastindexof( ::booldog::result_size* pres , bool isempty_src_error , const char* src 
					, size_t srccharindex , size_t srccharcount	, const char* target , size_t targetcharindex 
					, size_t targetcharcount , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					debuginfo = debuginfo;
					::booldog::result_size locres;
					BOOINIT_RESULT( ::booldog::result_size );
					if( src )
					{
						const char* srcbegin = &src[ srccharindex ];
						if( *srcbegin != 0 )
						{
							const char* srcbegin = &src[ srccharindex ];
							const char* ptr = srcbegin;
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case 0:
									ptr--;
									goto goto_next0;
								}
								if( (size_t)( ptr - srcbegin ) >= srccharcount )
									break;
							}
		goto_next0:
							srccharcount = ptr - srcbegin;

							const char* targetbegin = &target[ targetcharindex ];
							ptr = targetbegin;
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case 0:
									ptr--;
									goto goto_next1;
								}
								if( (size_t)( ptr - targetbegin ) >= targetcharcount )
									break;
							}
		goto_next1:
							targetcharcount = ptr - targetbegin;
							if( targetcharcount <= srccharcount )
							{
								ptr = &srcbegin[ srccharcount - targetcharcount ];
								if( targetcharcount == sizeof( char ) )
								{
									char targetval = targetbegin[ 0 ];
									while( ptr >= srcbegin )
									{
										if( *ptr == targetval )
										{
											res->sres = ptr - srcbegin;
											break;
										}
										ptr--;
									}
								}
								else if( targetcharcount == sizeof( ::booldog::uint16 ) )
								{
									::booldog::uint16 targetval = *(::booldog::uint16*)targetbegin;
									while( ptr >= srcbegin )
									{
										if( *(::booldog::uint16*)ptr == targetval )
										{
											res->sres = ptr - srcbegin;
											break;
										}
										ptr--;
									}
								}
								else if( targetcharcount == sizeof( ::booldog::uint32 ) )
								{
									::booldog::uint32 targetval = *(::booldog::uint32*)targetbegin;
									while( ptr >= srcbegin )
									{
										if( *(::booldog::uint32*)ptr == targetval )
										{
											res->sres = ptr - srcbegin;
											break;
										}
										ptr--;
									}
								}
								else if( targetcharcount == sizeof( ::booldog::uint64 ) )
								{
									::booldog::uint64 targetval = *(::booldog::uint64*)targetbegin;
									while( ptr >= srcbegin )
									{
										if( *(::booldog::uint64*)ptr == targetval )
										{
											res->sres = ptr - srcbegin;
											break;
										}
										ptr--;
									}
								}
								else
								{
									while( ptr >= srcbegin )
									{
										if( ::memcmp( ptr-- , targetbegin , targetcharcount ) == 0 )
										{
											res->sres = ptr - srcbegin + 1;
											break;
										}
									}
								}
							}
						}
						else
						{
							if( isempty_src_error )
								res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
						}
					}
					else
					{
						if( isempty_src_error )
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
					}
					return res->succeeded();
				};
				booinline bool indexof( ::booldog::result_size* pres , bool isempty_src_error , const char* src 
					, size_t srccharindex , size_t srccharcount	, const char* target , size_t targetcharindex 
					, size_t targetcharcount , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					debuginfo = debuginfo;
					::booldog::result_size locres;
					BOOINIT_RESULT( ::booldog::result_size );
					if( src )
					{
						const char* srcbegin = &src[ srccharindex ];
						if( *srcbegin != 0 )
						{
							const char* srcbegin = &src[ srccharindex ];
							const char* ptr = srcbegin;
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case 0:
									ptr--;
									goto goto_next0;
								}
								if( (size_t)( ptr - srcbegin ) >= srccharcount )
									break;
							}
		goto_next0:
							srccharcount = ptr - srcbegin;

							const char* targetbegin = &target[ targetcharindex ];
							ptr = targetbegin;
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case 0:
									ptr--;
									goto goto_next1;
								}
								if( (size_t)( ptr - targetbegin ) >= targetcharcount )
									break;
							}
		goto_next1:
							targetcharcount = ptr - targetbegin;							
							if( targetcharcount == sizeof( char ) )
							{
								char targetval = targetbegin[ 0 ];
								size_t index = 0;
								while( srccharcount - index >= targetcharcount )
								{
									if( srcbegin[ index++ ] == targetval )
									{
										res->sres = index - 1;
										break;
									}
								}
							}
							else if( targetcharcount == sizeof( ::booldog::uint16 ) )
							{
								::booldog::uint16 targetval = *(::booldog::uint16*)targetbegin;
								size_t index = 0;
								while( srccharcount - index >= targetcharcount )
								{
									if( *(::booldog::uint16*)( &srcbegin[ index++ ] ) == targetval )
									{
										res->sres = index - 1;
										break;
									}
								}
							}
							else if( targetcharcount == sizeof( ::booldog::uint32 ) )
							{
								::booldog::uint32 targetval = *(::booldog::uint32*)targetbegin;
								size_t index = 0;
								while( srccharcount - index >= targetcharcount )
								{
									if( *(::booldog::uint32*)( &srcbegin[ index++ ] ) == targetval )
									{
										res->sres = index - 1;
										break;
									}
								}
							}
							else if( targetcharcount == sizeof( ::booldog::uint64 ) )
							{
								::booldog::uint64 targetval = *(::booldog::uint64*)targetbegin;
								size_t index = 0;
								while( srccharcount - index >= targetcharcount )
								{
									if( *(::booldog::uint64*)( &srcbegin[ index++ ] ) == targetval )
									{
										res->sres = index - 1;
										break;
									}
								}
							}
							else
							{
								size_t index = 0;
								while( srccharcount - index >= targetcharcount )
								{
									if( ::memcmp( &srcbegin[ index++ ] , targetbegin , targetcharcount ) == 0 )
									{
										res->sres = index - 1;
										break;
									}
								}
							}
						}
						else
						{
							if( isempty_src_error )
								res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
						}
					}
					else
					{
						if( isempty_src_error )
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
					}
					return res->succeeded();
				};
				booinline void replace( size_t dstbyteindex , char* dst , size_t dstlen , char oldchar
					, char newchar )
				{
					char* ptr = &dst[ dstlen ];
					if( dstbyteindex == 0 )
					{
						for( ; ; )
						{
							if( *ptr-- == oldchar )
								ptr[ 1 ] = newchar;
							if( dst > ptr )
								break;
						}
					}
					else
					{
						char* begin = &dst[ dstbyteindex ];
						for( ; ; )
						{
							if( begin > ptr )
								break;
							if( *ptr-- == oldchar )
								ptr[ 1 ] = newchar;
							if( dst > ptr )
								break;
						}
					}
				};
				booinline bool insert( ::booldog::result* pres , booldog::allocator* allocator , bool isempty_src_error , size_t dstcharindex , char*& dst , size_t& dstlen 
					, size_t& dstsize_in_bytes , const char* src , size_t srccharindex = 0 , size_t srccharcount = SIZE_MAX 
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
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
						{
							if( isempty_src_error )
								res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
							else if( dst == 0 )
							{
								dstsize_in_bytes = 1;
								dst = allocator->realloc_array< char >( dst , dstsize_in_bytes , debuginfo );
								dstlen = 0;
								dst[ dstlen ] = 0;
							}
						}
					}
					else
					{
						if( isempty_src_error )
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
						else if( dst == 0 )
						{
							dstsize_in_bytes = 1;
							dst = allocator->realloc_array< char >( dst , dstsize_in_bytes , debuginfo );
							dstlen = 0;
							dst[ dstlen ] = 0;
						}
					}
					return res->succeeded();
				}
				booinline bool insert( ::booldog::result* pres , booldog::allocator* allocator , bool isempty_src_error , size_t dstcharindex , wchar_t*& dst , size_t& dstlen 
					, size_t& dstsize_in_bytes , const char* src , size_t srccharindex = 0 , size_t srccharcount = SIZE_MAX 
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
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
						{
							if( isempty_src_error )
								res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
							else if( dst == 0 )
							{
								dstsize_in_bytes = 1;
								dst = allocator->realloc_array< wchar_t >( dst , dstsize_in_bytes , debuginfo );
								dstlen = 0;
								dstsize_in_bytes *= sizeof( wchar_t );
								dst[ dstlen ] = 0;
							}
						}
					}
					else
					{
						if( isempty_src_error )
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
						else if( dst == 0 )
						{
							dstsize_in_bytes = 1;
							dst = allocator->realloc_array< wchar_t >( dst , dstsize_in_bytes , debuginfo );
							dstlen = 0;
							dstsize_in_bytes *= sizeof( wchar_t );
							dst[ dstlen ] = 0;
						}
					}
#ifndef __WINDOWS__
goto_return:
#endif
					return res->succeeded();
				}
			};
			namespace wcs
			{
				template< size_t step >
				booinline bool toutf8( ::booldog::result_mbchar* pres , booldog::allocator* allocator , const wchar_t* wcs
					, size_t charindex = 0 , size_t charcount = SIZE_MAX , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					const wchar_t* begin = &wcs[ charindex ];
					const wchar_t* ptr = begin;
					for( ; ; )
					{
						switch( *ptr++ )
						{
						case 0:
							ptr--;
							goto goto_next;
						}
						if( (size_t)( ptr - begin ) >= charcount )
							break;
					}
goto_next:
					charcount = ptr - begin;
					size_t srcbyteindex = charindex * sizeof( wchar_t );
					if( ::booldog::compile::If< sizeof( wchar_t ) == 2 >::test() )
						return ::booldog::utf16::toutf8< step >( pres , allocator , (const char*)wcs , srcbyteindex , sizeof( wchar_t ) 
						* ( charindex + charcount ) , debuginfo );
					else if( ::booldog::compile::If< sizeof( wchar_t ) == 4 >::test() )
						return ::booldog::utf32::toutf8< step >( pres , allocator , (const char*)wcs , srcbyteindex , sizeof( wchar_t ) 
						* (	charindex + charcount ) , debuginfo );
					if( pres )
						pres->booerr( ::booldog::enums::result::booerr_type_unknown_wchar_t_size );
					return false;
				};
				booinline bool tombs( ::booldog::result_mbchar* pres , booldog::allocator* allocator , const wchar_t* wchar 
					, size_t charindex = 0 , size_t charcount = SIZE_MAX , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result_mbchar locres( allocator );
					BOOINIT_RESULT( ::booldog::result_mbchar );
					const wchar_t* begin = &wchar[ charindex ];
					const wchar_t* ptr = begin;
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
							wchar_t* newbegin = allocator->realloc_array< wchar_t >( 0 , charcount + 1 , debuginfo );
							if( newbegin )
							{
								::memcpy( newbegin , begin , charcount * sizeof( wchar_t ) );
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
					res->mbsize = charcount + 1;
					res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
					if( res->mbchar )
					{
#ifdef __WINDOWS__
						res->mblen = WideCharToMultiByte( CP_ACP , WC_NO_BEST_FIT_CHARS , begin , (int)charcount , res->mbchar , (int)res->mbsize , NULL , NULL );
						if( res->mblen == 0 )
						{
							DWORD get_last_error = GetLastError();
							if( get_last_error == ERROR_INSUFFICIENT_BUFFER )
							{
								res->mblen = WideCharToMultiByte( CP_ACP , WC_NO_BEST_FIT_CHARS , begin , (int)charcount , res->mbchar , 0 , NULL , NULL );
								if( res->mblen > 0 )
								{
									res->mbsize = res->mblen + 1;
									res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
									if( res->mbchar )
									{
										res->mblen = WideCharToMultiByte( CP_ACP , WC_NO_BEST_FIT_CHARS , begin , (int)charcount , res->mbchar , (int)res->mbsize , NULL , NULL );
										if( res->mblen > 0 )
											res->mbchar[ res->mblen ] = 0;
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
							if( res->mblen == res->mbsize )
							{
								res->mbsize = res->mblen + 1;
								res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
								if( res->mbchar )
									res->mbchar[ res->mblen ] = 0;
								else
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );	
							}
							else
								res->mbchar[ res->mblen ] = 0;
						}
#else
						mbstate_t state;
						::memset( &state , 0 , sizeof( state ) );
						const wchar_t* src = begin;
						res->mblen = wcsrtombs( res->mbchar , &src , res->mbsize - 1 , &state );
						if( res->mblen != (size_t)-1 )
						{
							if( src != 0 && src < ptr - 1 )
							{
								::memset( &state , 0 , sizeof( state ) );
								src = begin;
								res->mblen = wcsrtombs( 0 , &src , 0 , &state );
								if( res->mblen != (size_t)-1 )
								{
									res->mbsize = res->mblen + 1;
									res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
									if( res->mbchar )
									{
										::memset( &state , 0 , sizeof( state ) );
										src = begin;
										res->mblen = wcsrtombs( res->mbchar , &src , res->mbsize - 1 , &state );
										if( res->mblen != (size_t)-1 )
											res->mbchar[ res->mblen ] = 0;
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
								if( res->mblen == res->mbsize )
								{
									res->mbsize = res->mblen + 1;
									res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
									if( res->mbchar )
										res->mbchar[ res->mblen ] = 0;
									else
										res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );	
								}
								else
									res->mbchar[ res->mblen ] = 0;
							}
						}
						else
							res->seterrno();
						if( begin != &wchar[ charindex ] )
							allocator->free( (void*)begin );
#endif
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
#ifndef __WINDOWS__
goto_return:
#endif
					return res->succeeded();
				};
				booinline bool insert( ::booldog::result* pres , booldog::allocator* allocator , bool isempty_src_error , size_t dstcharindex , wchar_t*& dst , size_t& dstlen 
					, size_t& dstsize_in_bytes , const wchar_t* src , size_t srccharindex = 0 , size_t srccharcount = SIZE_MAX 
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
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
						{
							if( isempty_src_error )
								res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
							else if( dst == 0 )
							{
								dstsize_in_bytes = 1;
								dst = allocator->realloc_array< wchar_t >( dst , dstsize_in_bytes , debuginfo );
								dstlen = 0;
								dstsize_in_bytes *= sizeof( wchar_t );
								dst[ dstlen ] = 0;
							}
						}
					}
					else
					{
						if( isempty_src_error )
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
						else if( dst == 0 )
						{
							dstsize_in_bytes = 1;
							dst = allocator->realloc_array< wchar_t >( dst , dstsize_in_bytes , debuginfo );
							dstlen = 0;
							dstsize_in_bytes *= sizeof( wchar_t );
							dst[ dstlen ] = 0;
						}
					}
					return res->succeeded();
				};
				booinline bool insert( ::booldog::result* pres , booldog::allocator* allocator , bool isempty_src_error , size_t dstcharindex , char*& dst , size_t& dstlen 
					, size_t& dstsize_in_bytes , const wchar_t* src , size_t srccharindex = 0 , size_t srccharcount = SIZE_MAX 
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
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
#ifdef __WINDOWS__
									ptr++;
#else
									srccharcount = ptr - srcbegin;
									wchar_t* newbegin = allocator->realloc_array< wchar_t >( 0 , srccharcount + 1 , debuginfo );
									if( newbegin )
									{
										::memcpy( newbegin , srcbegin , srccharcount * sizeof( wchar_t ) );
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
							size_t srcwcharcount = WideCharToMultiByte( CP_ACP , WC_NO_BEST_FIT_CHARS , srcbegin , (int)srccharcount , dst , 0 , NULL , NULL );
							if( srcwcharcount > 0 )
#else
							mbstate_t state;
							::memset( &state , 0 , sizeof( state ) );
							const wchar_t* mbsrtowcssrc = srcbegin;
							size_t srcwcharcount = wcsrtombs( 0 , &mbsrtowcssrc , 0 , &state );
							if( srcwcharcount != (size_t)-1 )
#endif							
							{
								if( dstlen + srcwcharcount + 1 > dstsize_in_bytes )
								{
									dstsize_in_bytes = dstlen + srcwcharcount + 1;
									dst = allocator->realloc_array< char >( dst , dstsize_in_bytes , debuginfo );
								}
								if( dst )
								{
									::booldog::mem::expand< char >( dstcharindex , dst , dstlen , dstsize_in_bytes , srcwcharcount );
#ifdef __WINDOWS__
									srcwcharcount = WideCharToMultiByte( CP_ACP , WC_NO_BEST_FIT_CHARS , srcbegin , (int)srccharcount , &dst[ dstcharindex ] , (int)( dstsize_in_bytes - dstcharindex ) , NULL , NULL );
									if( srcwcharcount > 0 )
#else
									::memset( &state , 0 , sizeof( state ) );
									mbsrtowcssrc = srcbegin;
									srcwcharcount = wcsrtombs( &dst[ dstcharindex ] , &mbsrtowcssrc , srcwcharcount , &state );
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
						{
							if( isempty_src_error )
								res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
							else if( dst == 0 )
							{
								dstsize_in_bytes = 1;
								dst = allocator->realloc_array< char >( dst , dstsize_in_bytes , debuginfo );
								dstlen = 0;
								dst[ dstlen ] = 0;
							}
						}
					}
					else
					{
						if( isempty_src_error )
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
						else if( dst == 0 )
						{
							dstsize_in_bytes = 1;
							dst = allocator->realloc_array< char >( dst , dstsize_in_bytes , debuginfo );
							dstlen = 0;
							dst[ dstlen ] = 0;
						}
					}
#ifndef __WINDOWS__
goto_return:
#endif
					return res->succeeded();
				}
			};
		};
	};
};
#endif