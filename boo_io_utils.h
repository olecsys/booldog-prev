#ifndef BOO_IO_UTILS_H
#define BOO_IO_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_result.h"
#include "boo_allocator.h"
#include "boo_mem.h"
#include "boo_error.h"
#ifdef __WINDOWS__
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#if (_MSC_VER <= 1600 )
#define va_copy(dst, src) dst = src
#else
#include <stdarg.h>
#endif
#else
#ifndef _LARGEFILE64_SOURCE 
#define _LARGEFILE64_SOURCE 
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <wchar.h>
#endif
namespace booldog
{	
	namespace utils
	{
		namespace io
		{	
			namespace mbs
			{
				booinline bool isfifo(::booldog::results::boolean* pres, const char* pathname
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::results::boolean locres;
					BOOINIT_RESULT(::booldog::results::boolean);
#ifdef __WINDOWS__
					pathname = pathname;
					res->booerr(::booldog::enums::result::booerr_type_windows_has_not_fifo);
					return false;
#else
					struct stat st;
					if(stat(pathname, &st) == 0)
						res->bres = (S_ISFIFO(st.st_mode) != 0);
					else
						res->seterrno();
#endif				
					return res->succeeded();
				}
				booinline bool rename(::booldog::result* pres, const char* oldpath, const char* newpath
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
#ifdef __WINDOWS__
					if(MoveFileA(oldpath, newpath) == 0)
					{
						res->GetLastError();
						return false;
					}
#else
					if(::rename(oldpath, newpath) == -1)
					{
						res->seterrno();
						return false;
					}
#endif
					return true;
				}
				booinline bool rmdir(::booldog::result* pres, const char* path
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
#ifdef __WINDOWS__
					if(RemoveDirectoryA(path) == 0)
					{
						res->GetLastError();
						return false;
					}
#else
					if(::rmdir(path) == -1)
					{
						res->seterrno();
						return false;
					}
#endif
					return true;
				}
			}
			namespace path
			{
				namespace mbs
				{
					booinline bool toabsolute(::booldog::result* pres, char* mbchar, size_t& mblen, size_t mbsize_in_bytes)
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
						if(mbchar[0] != 0)
						{
							const char* ptr = mbchar;
							if(strncmp(mbchar, "\\\\?\\", 4) == 0)
								ptr += 4;
							size_t sections_count = *ptr == '\\' || *ptr == '/' ? 0 : 1;
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case 0:
									goto goto_next_step2;
								case '/':
								case '\\':
									sections_count++;
									switch( *ptr++ )
									{
									case '.':
										{
											switch( *ptr++ )
											{
											case '.':
												{
													switch( *ptr++ )
													{
													case '/':
													case '\\':
														{
															if( sections_count > 1 )
															{
																const char* reverse_ptr = ptr - 4;
																if( reverse_ptr != mbchar )
																{
																	reverse_ptr--;
																	for( ; ; )
																	{
																		switch( *reverse_ptr-- )
																		{
																		case '/':
																		case '\\':
																			goto goto_next_step3;
																		}
																		if( reverse_ptr < mbchar )
																			break;
																	}
goto_next_step3:
																	reverse_ptr++;
																}
																::booldog::mem::remove< char >( (size_t)( reverse_ptr - mbchar ) , mbchar , mbsize_in_bytes , (size_t)( ptr - reverse_ptr - 1 ) );
																ptr = reverse_ptr;
																sections_count -= 2;
															}
															else
															{
																res->booerr( ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
																goto goto_return;
															}
															break;
														}
													case 0:
														{
															if( sections_count > 1 )
															{
																const char* reverse_ptr = ptr - 4;
																if( reverse_ptr != mbchar )
																{
																	reverse_ptr--;
																	for( ; ; )
																	{
																		switch( *reverse_ptr-- )
																		{
																		case '/':
																		case '\\':
																			goto goto_next_step4;
																		}
																		if( reverse_ptr < mbchar )
																			break;
																	}
goto_next_step4:
																	reverse_ptr++;
																}
																::booldog::mem::remove< char >( (size_t)( reverse_ptr - mbchar ) , mbchar , mbsize_in_bytes , (size_t)( ptr - reverse_ptr - 1 ) );
																ptr = reverse_ptr + 1;
																goto goto_next_step2;
															}
															else
															{
																res->booerr( ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
																goto goto_return;
															}
															break;
														}
													}
													break;
												}
											case '/':
											case '\\':										
												{
													::booldog::mem::remove< char >( (size_t)( ptr - mbchar - 2 ) , mbchar , mbsize_in_bytes , 2 );
													ptr -= 3;
													sections_count--;
													break;
												}
											case 0:
												{
													::booldog::mem::remove< char >( (size_t)( ptr - mbchar - 2 ) , mbchar , mbsize_in_bytes , 2 );
													ptr -= 2;
													goto goto_next_step2;
												}
											}
											break;
										}
									case '/':
									case '\\':
										res->booerr( ::booldog::enums::result::booerr_type_path_has_incorrect_format );
										goto goto_return;
									case 0:
										goto goto_next_step2;
									}									
									break;
								case '.':
									{
										switch( *ptr++ )
										{
										case '.':
											res->booerr( ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
											goto goto_return;
										case '/':
										case '\\':
											::booldog::mem::remove< char >( 0 , mbchar , mbsize_in_bytes , 2 );
											ptr = mbchar;
											break;
										case 0:
											{
												::booldog::mem::remove< char >( 0 , mbchar , mbsize_in_bytes , 1 );
												ptr = mbchar + 1;
												goto goto_next_step2;
											}
											break;
										}
										break;				
									}
								}
							}
goto_next_step2:
							mblen = ptr - mbchar - 1;
							mbchar[ mblen ] = 0;
						}
goto_return:
						return res->succeeded();
					};
					booinline bool normalize( ::booldog::result* pres , char* mbchar , size_t& mblen , size_t mbsize_in_bytes )
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
						if( ::booldog::utils::io::path::mbs::toabsolute( res , mbchar , mblen , mbsize_in_bytes ) )
						{
							char* ptr = &mbchar[ mblen ];
							for( ; ; )
							{
								switch( *ptr-- )
								{
								case '\\':
								case '/':
									ptr[ 1 ] = ::booldog::io::mbs::slash;
									break;
								}
								if( mbchar > ptr )
									break;
							}
							if( mbchar[ mblen - 1 ] == ::booldog::io::mbs::slash )
							{
								mblen--;
								mbchar[ mblen ] = 0;
							}
						}
						return res->succeeded();
					};
					booinline bool toabsolute( ::booldog::result_mbchar* pres , booldog::allocator* allocator , const char* path 
						, size_t charindex = 0 , size_t charcount = SIZE_MAX 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_mbchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_mbchar );
						const char* begin = &path[ charindex ];
						const char* ptr = begin;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case 0:
								goto goto_next_step1;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next_step1:
						res->mbsize = ptr - begin;
						res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
						res->mblen = res->mbsize - 1;						
						if( res->mbchar )
						{
							if( res->mblen )
								::memcpy( res->mbchar , begin , res->mblen );
							res->mbchar[ res->mblen ] = 0;
						
							::booldog::result locres1;
							::booldog::utils::io::path::mbs::toabsolute( &locres1 , res->mbchar , res->mblen , res->mbsize );
							if( locres1.succeeded() == false )
							{
								res->clear();
								res->copy( locres1 );
							}
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						return res->succeeded();
					};
					booinline bool directory( ::booldog::result* pres , char* pathname , size_t& pathnamelen )
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
						if( pathname && pathnamelen > 0 )
						{
							char* ptr = &pathname[ pathnamelen ];
							for( ; ; )
							{
								switch( *ptr-- )
								{
								case '\\':
								case '/':
									ptr[ 1 ] = 0;
									pathnamelen = ptr - pathname + 1;
									goto goto_next;
								}
								if( pathname > ptr )
									break;
							}
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
	goto_next:
						return res->succeeded();
					};
					booinline bool pathname_without_extension( ::booldog::result_mbchar* pres , booldog::allocator* allocator 
						, const char* pathname , size_t charindex = 0 , size_t charcount = SIZE_MAX 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_mbchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_mbchar );
						const char* begin = &pathname[ charindex ];
						const char* ptr = begin , * start = begin;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '/':
							case '\\':
								start = ptr;
								break;
							case 0:
								goto goto_next0;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next0:
						const char* end = ptr;
						ptr = start;						
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '.':
								end = ptr;
								break;
							case 0:
								goto goto_next1;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next1:
						res->mbsize = end - begin;
						res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
						res->mblen = res->mbsize - 1;
						if( res->mbchar )
						{
							if( res->mblen )
								::memcpy( res->mbchar , begin , res->mblen );
							res->mbchar[ res->mblen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						return res->succeeded();
					};
					booinline bool filename_without_extension( ::booldog::result* pres , char* pathname , size_t& pathnamelen )
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
						if( pathname && pathnamelen > 0 )
						{
							const char* ptr = pathname , * start = pathname;
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case '/':
								case '\\':
									start = ptr;
									break;
								case 0:
									goto goto_next0;
								}
							}
	goto_next0:
							const char* end = ptr;
							ptr = start;						
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case '.':
									end = ptr;
									break;
								case 0:
									goto goto_next1;
								}
							}
	goto_next1:
							pathnamelen = end - start - 1;
							if( pathnamelen )
								::memmove( pathname , start , pathnamelen );
							pathname[ pathnamelen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
						return res->succeeded();
					};
					booinline bool pathname_without_extension( ::booldog::result* pres , char* pathname , size_t& pathnamelen )
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
						if( pathname && pathnamelen > 0 )
						{
							char* ptr = &pathname[ pathnamelen ];
							for( ; ; )
							{
								switch( *ptr-- )
								{
								case '\\':
								case '/':
									goto goto_next;
								case '.':
									ptr[ 1 ] = 0;
									pathnamelen = ptr - pathname + 1;
									goto goto_next;
								}
								if( pathname > ptr )
									break;
							}
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
	goto_next:
						return res->succeeded();
					};
					booinline bool filename_without_extension( ::booldog::result_mbchar* pres , booldog::allocator* allocator
						, const char* path , size_t charindex = 0 , size_t charcount = SIZE_MAX 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_mbchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_mbchar );
						const char* begin = &path[ charindex ];
						const char* ptr = begin , * start = begin;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '/':
							case '\\':
								start = ptr;
								break;
							case 0:
								goto goto_next0;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next0:
						const char* end = ptr;
						ptr = start;						
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '.':
								end = ptr;
								break;
							case 0:
								goto goto_next1;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next1:
						res->mbsize = end - start;
						res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
						res->mblen = res->mbsize - 1;
						if( res->mbchar )
						{
							if( res->mblen )
								::memcpy( res->mbchar , start , res->mblen );
							res->mbchar[ res->mblen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );					
						return res->succeeded();
					};
					booinline bool has_levels( ::booldog::result_bool* pres , const char* path , size_t charindex = 0 , size_t charcount = SIZE_MAX )
					{
						::booldog::result_bool locres;
						BOOINIT_RESULT( ::booldog::result_bool );
						if( path )
						{
							const char* begin = &path[ charindex ];
							if( *begin != 0 )
							{
								const char* ptr = begin;
								for( ; ; )
								{								
									switch( *ptr++ )
									{
									case '/':
									case '\\':
									{
										if( (size_t)( ptr - begin ) < charcount && *ptr != 0 )
											res->bres = true;
										goto goto_return;
									}
									case 0:
										goto goto_return;
									}
									if( (size_t)( ptr - begin ) >= charcount )
									{
										++ptr;
										break;
									}
								}
							}
							else
								res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
goto_return:
						return res->succeeded();
					};
					booinline bool isabsolute( ::booldog::result_bool* pres , const char* mbchar )
					{
						::booldog::result_bool locres;
						BOOINIT_RESULT( ::booldog::result_bool );
						if( mbchar )
						{
							if( mbchar[ 0 ] != '/' )
							{
								if( mbchar[ 0 ] != 0 )
								{
									if( mbchar[ 1 ] != ':' )
									{
										if( mbchar[ 1 ] != 0 )
										{
											if( mbchar[ 2 ] != ':' )
											{
												if( mbchar[ 2 ] != 0 )
												{
													if( mbchar[ 3 ] == ':' )
														res->bres = true;
												}
											}
											else
												res->bres = true;
										}
									}
									else
										res->bres = true;
								}
							}
							else
								res->bres = true;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
						return res->succeeded();
					};
					booinline bool extension( ::booldog::result_mbchar* pres , booldog::allocator* allocator , const char* path 
						, size_t charindex = 0 , size_t charcount = SIZE_MAX 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_mbchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_mbchar );
						const char* begin = &path[ charindex ];
						const char* ptr = begin , * start = begin;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '/':
							case '\\':
								start = ptr;
								break;
							case 0:
								goto goto_next0;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next0:
						ptr = start , start = 0;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '.':
								start = ptr;
								break;
							case 0:
								goto goto_next1;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next1:
						res->mbsize = start ? ptr - start : 1;
						res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
						res->mblen = res->mbsize - 1;
						if( res->mbchar )
						{
							if( res->mblen )
								::memcpy( res->mbchar , start , res->mblen );
							res->mbchar[ res->mblen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );					
						return res->succeeded();
					};
					booinline bool filename( ::booldog::result_mbchar* pres , booldog::allocator* allocator , const char* path 
						, size_t charindex = 0 , size_t charcount = SIZE_MAX 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_mbchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_mbchar );
						const char* begin = &path[ charindex ];
						const char* ptr = begin , * start = begin;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '/':
							case '\\':
								start = ptr;
								break;
							case 0:
								goto goto_next;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next:
						res->mbsize = ptr - start;
						res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
						res->mblen = res->mbsize - 1;
						if( res->mbchar )
						{
							if( res->mblen )
								::memcpy( res->mbchar , start , res->mblen );
							res->mbchar[ res->mblen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );					
						return res->succeeded();
					};
					booinline bool directory( ::booldog::result_mbchar* pres , booldog::allocator* allocator , const char* path 
						, size_t charindex = 0 , size_t charcount = SIZE_MAX 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_mbchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_mbchar );
						const char* begin = &path[ charindex ];
						const char* ptr = begin , * end = begin;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '/':
							case '\\':
								end = ptr;
								break;
							case 0:
								goto goto_next;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next:
						res->mbsize = end - begin;
						res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize , debuginfo );
						res->mblen = res->mbsize - 1;
						if( res->mbchar )
						{
							if( res->mblen )
								::memcpy( res->mbchar , begin , res->mblen );
							res->mbchar[ res->mblen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );					
						return res->succeeded();
					}
					/** Join one or more path components intelligently. The return value is the concatenation of path and any members
					* of pargs with exactly one directory separator (@param sep) following each non-empty part except the last,
					* meaning that the result will only end in a separator if the last part is empty
					* @param pres store the function result or detailed error
					* @param sep a directory separator
					* @param pargs a directory part. It must ends with empty string ""
					* @param debuginfo a debug information
					* @return The function result
					*/
					template< size_t step, size_t sizes_size >
					booinline bool join(::booldog::results::mbchar& pres, char sep, va_list pargs
						, const ::booldog::debug::info& debuginfo = debuginfo_macros)
					{
						size_t size = 0, sizes[sizes_size] = {}, sizes_count = 0, * sizes_ptr = sizes, sizes_ptr_size = sizes_size;
						char* val = 0, * ptr = 0;
						pres.clear();
						va_list argcopy;
						va_copy(argcopy, pargs);
						for(;;)
						{
							val = va_arg(argcopy, char*);
							if(val)
							{	
								for(ptr = val; *ptr; ++ptr);
								if(val == ptr)
									break;
								ptr -= 1;
								if(sizes_count == sizes_ptr_size)
								{
									sizes_ptr_size += step;
									if(sizes_ptr == sizes)
									{
										sizes_ptr = pres.mballocator->realloc_array< size_t >(0, sizes_ptr_size, debuginfo);
										if(sizes_ptr)
										{
											for(size_t index = 0;index < sizes_count;++index)
												sizes_ptr[index] = sizes[index];
										}
										else
										{
											pres.booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
											return false;
										}
									}
									else
									{
										sizes_ptr = pres.mballocator->realloc_array< size_t >(sizes_ptr, sizes_ptr_size, debuginfo);
										if(sizes_ptr == 0)
										{
											pres.booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
											return false;
										}
									}
								}								
								for(;;)
								{
									switch(*ptr)
									{
									case '/':
									case '\\':
										{
											--ptr;
											continue;
										}
									}
									break;
								}
								sizes_ptr[sizes_count] = (size_t)(ptr - val + 2);
								if(sizes_ptr[sizes_count] == 1)
									break;
								size += sizes_ptr[sizes_count++];
							}
							else
							{
								if(size == 0)
									++size;
								break;
							}
						}
						va_end(argcopy);
						if(size > pres.mbsize)
						{
							pres.mbsize = size;
							pres.mbchar = pres.mballocator->realloc_array< char >(pres.mbchar, pres.mbsize, debuginfo);
						}
						if(pres.mbchar)
						{
							ptr = pres.mbchar;
							for(size_t index0 = 0;index0 < sizes_count;++index0)
							{
								val = va_arg(pargs, char*);
								::memcpy(ptr, val, sizes_ptr[index0]);
								ptr += sizes_ptr[index0];
								ptr[-1] = sep;
							}
							pres.mblen = size - 1;
							pres.mbchar[pres.mblen] = 0;
							if(sizes_ptr != sizes)
								pres.mballocator->free(sizes_ptr);
							return true;
						}
						else
						{
							if(sizes_ptr != sizes)
								pres.mballocator->free(sizes_ptr);
							pres.booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							return false;
						}
					}
					/** Join one or more path components intelligently. The return value is the concatenation of path and any members
					* of pargs with exactly one directory separator (@param sep) following each non-empty part except the last,
					* meaning that the result will only end in a separator if the last part is empty
					* @param pres store the function result or detailed error
					* @param debuginfo a debug information
					* @param sep a directory separator
					* @param ... a directory parts. It must ends with empty string ""
					* @return The function result
					*/
					template< size_t step, size_t sizes_size >
					booinline bool join(::booldog::results::mbchar& pres, const ::booldog::debug::info& debuginfo, char sep, ...)
					{
						va_list pargs;
						va_start(pargs, sep); 
						bool retval = join<step, sizes_size>(pres, sep, pargs, debuginfo);
						va_end(pargs);
						return retval;						
					}
				};
				namespace wcs
				{
					booinline bool filename_without_extension( ::booldog::result* pres , wchar_t* pathname , size_t& pathnamelen )
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
						if( pathname && pathnamelen > 0 )
						{
							const wchar_t* ptr = pathname , * start = pathname;
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case '/':
								case '\\':
									start = ptr;
									break;
								case 0:
									goto goto_next0;
								}
							}
	goto_next0:
							const wchar_t* end = ptr;
							ptr = start;						
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case '.':
									end = ptr;
									break;
								case 0:
									goto goto_next1;
								}
							}
	goto_next1:
							pathnamelen = end - start - 1;
							if( pathnamelen )
								::memmove( pathname , start , pathnamelen * sizeof( wchar_t ) );
							pathname[ pathnamelen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
						return res->succeeded();
					};
					booinline bool directory( ::booldog::result* pres , wchar_t* pathname , size_t& pathnamelen )
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
						if( pathname && pathnamelen > 0 )
						{
							wchar_t* ptr = &pathname[ pathnamelen ];
							for( ; ; )
							{
								switch( *ptr-- )
								{
								case '\\':
								case '/':
									ptr[ 1 ] = 0;
									pathnamelen = ptr - pathname + 1;
									goto goto_next;
								}
								if( pathname > ptr )
									break;
							}
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
	goto_next:
						return res->succeeded();
					};
					booinline bool pathname_without_extension( ::booldog::result_wchar* pres , booldog::allocator* allocator 
						, const wchar_t* pathname , size_t charindex = 0 , size_t charcount = SIZE_MAX 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_wchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_wchar );
						const wchar_t* begin = &pathname[ charindex ];
						const wchar_t* ptr = begin , * start = begin;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '/':
							case '\\':
								start = ptr;
								break;
							case 0:
								goto goto_next0;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next0:
						const wchar_t* end = ptr;
						ptr = start;						
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '.':
								end = ptr;
								break;
							case 0:
								goto goto_next1;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next1:
						res->wsize = end - begin;
						res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
						res->wlen = res->wsize - 1;
						res->wsize *= sizeof( wchar_t );
						if( res->wchar )
						{
							if( res->wlen )
								::memcpy( res->wchar , begin , res->wlen * sizeof( wchar_t ) );
							res->wchar[ res->wlen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						return res->succeeded();
					};
					booinline bool has_levels( ::booldog::result_bool* pres , const wchar_t* path , size_t charindex = 0 , size_t charcount = SIZE_MAX )
					{
						::booldog::result_bool locres;
						BOOINIT_RESULT( ::booldog::result_bool );
						if( path )
						{
							const wchar_t* begin = &path[ charindex ];
							if( *begin != 0 )
							{
								const wchar_t* ptr = begin;
								for( ; ; )
								{								
									switch( *ptr++ )
									{
									case '/':
									case '\\':
									{
										if( (size_t)( ptr - begin ) < charcount && *ptr != 0 )
											res->bres = true;
										goto goto_return;
									}
									case 0:
										goto goto_return;
									}
									if( (size_t)( ptr - begin ) >= charcount )
									{
										++ptr;
										break;
									}
								}
							}
							else
								res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
goto_return:
						return res->succeeded();
					};
					booinline bool isabsolute( ::booldog::result_bool* pres , const wchar_t* wchar )
					{
						::booldog::result_bool locres;
						BOOINIT_RESULT( ::booldog::result_bool );
						if( wchar )
						{
							if( wchar[ 0 ] != '/' )
							{
								if( wchar[ 0 ] != 0 )
								{
									if( wchar[ 1 ] != ':' )
									{
										if( wchar[ 1 ] != 0 )
										{
											if( wchar[ 2 ] != ':' )
											{
												if( wchar[ 2 ] != 0 )
												{
													if( wchar[ 3 ] == ':' )
														res->bres = true;
												}
											}
											else
												res->bres = true;
										}
									}
									else
										res->bres = true;
								}
							}
							else
								res->bres = true;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
						return res->succeeded();
					};
					booinline bool toabsolute( ::booldog::result* pres , wchar_t* wchar , size_t& wlen , size_t wsize_in_bytes )
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
						if( wchar[ 0 ] != 0 )
						{
							wsize_in_bytes /= sizeof( wchar_t );							
							const wchar_t* ptr = wchar;
							if(wcsncmp(wchar, L"\\\\?\\", 4) == 0)
								ptr += 4 * sizeof(wchar_t);
							size_t sections_count = *ptr == '\\' || *ptr == '/' ? 0 : 1;
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case 0:
									goto goto_next_step2;
								case '/':
								case '\\':
									sections_count++;
									switch( *ptr++ )
									{
									case '.':
										{
											switch( *ptr++ )
											{
											case '.':
												{
													switch( *ptr++ )
													{
													case '/':
													case '\\':
														{
															if( sections_count > 1 )
															{
																const wchar_t* reverse_ptr = ptr - 4;
																if( reverse_ptr != wchar )
																{
																	reverse_ptr--;
																	for( ; ; )
																	{
																		switch( *reverse_ptr-- )
																		{
																		case '/':
																		case '\\':
																			goto goto_next_step3;
																		}
																		if( reverse_ptr < wchar )
																			break;
																	}
goto_next_step3:
																	reverse_ptr++;
																}
																::booldog::mem::remove< wchar_t >( (size_t)( reverse_ptr - wchar ) , wchar , wsize_in_bytes , (size_t)( ptr - reverse_ptr - 1 ) );
																ptr = reverse_ptr;
																sections_count -= 2;
															}
															else
															{
																res->booerr( ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
																goto goto_return;
															}
															break;
														}
													case 0:
														{
															if( sections_count > 1 )
															{
																const wchar_t* reverse_ptr = ptr - 4;
																if( reverse_ptr != wchar )
																{
																	reverse_ptr--;
																	for( ; ; )
																	{
																		switch( *reverse_ptr-- )
																		{
																		case '/':
																		case '\\':
																			goto goto_next_step4;
																		}
																		if( reverse_ptr < wchar )
																			break;
																	}
goto_next_step4:
																	reverse_ptr++;
																}
																::booldog::mem::remove< wchar_t >( (size_t)( reverse_ptr - wchar ) , wchar , wsize_in_bytes , (size_t)( ptr - reverse_ptr - 1 ) );
																ptr = reverse_ptr + 1;
																goto goto_next_step2;
															}
															else
															{
																res->booerr( ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
																goto goto_return;
															}
															break;
														}
													}
													break;
												}
											case '/':
											case '\\':										
												{
													::booldog::mem::remove< wchar_t >( (size_t)( ptr - wchar - 2 ) , wchar , wsize_in_bytes , 2 );
													ptr -= 3;
													sections_count--;
													break;
												}
											case 0:
												{
													::booldog::mem::remove< wchar_t >( (size_t)( ptr - wchar - 2 ) , wchar , wsize_in_bytes , 2 );
													ptr -= 2;
													goto goto_next_step2;
												}
											}
											break;
										}
									case '/':
									case '\\':
										res->booerr( ::booldog::enums::result::booerr_type_path_has_incorrect_format );
										goto goto_return;
									case 0:
										goto goto_next_step2;
									}									
									break;
								case '.':
									{
										switch( *ptr++ )
										{
										case '.':
											res->booerr( ::booldog::enums::result::booerr_type_not_enough_top_level_folders );
											goto goto_return;
										case '/':
										case '\\':
											::booldog::mem::remove< wchar_t >( 0 , wchar , wsize_in_bytes , 2 );
											ptr = wchar;
											break;
										case 0:
											{
												::booldog::mem::remove< wchar_t >( 0 , wchar , wsize_in_bytes , 1 );
												ptr = wchar + 1;
												goto goto_next_step2;
											}
											break;
										}
										break;				
									}
								}
							}
goto_next_step2:
							wlen = ptr - wchar - 1;
							wchar[ wlen ] = 0;
						}
goto_return:
						return res->succeeded();
					};
					booinline bool normalize( ::booldog::result* pres , wchar_t* wchar , size_t& wlen , size_t wsize_in_bytes )
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
						if( ::booldog::utils::io::path::wcs::toabsolute( res , wchar , wlen , wsize_in_bytes ) )
						{
							wchar_t* ptr = &wchar[ wlen ];
							for( ; ; )
							{
								switch( *ptr-- )
								{
								case '\\':
								case '/':
									ptr[ 1 ] = ::booldog::io::wcs::slash;
									break;
								}
								if( wchar > ptr )
									break;
							}
							if( wchar[ wlen - 1 ] == ::booldog::io::wcs::slash )
							{
								wlen--;
								wchar[ wlen ] = 0;
							}
						}
						return res->succeeded();
					};
					booinline bool pathname_without_extension( ::booldog::result* pres , wchar_t* pathname , size_t& pathnamelen )
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
						if( pathname && pathnamelen > 0 )
						{
							wchar_t* ptr = &pathname[ pathnamelen ];
							for( ; ; )
							{
								switch( *ptr-- )
								{
								case '\\':
								case '/':
									goto goto_next;
								case '.':
									ptr[ 1 ] = 0;
									pathnamelen = ptr - pathname + 1;
									goto goto_next;
								}
								if( pathname > ptr )
									break;
							}
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
	goto_next:
						return res->succeeded();
					};
					booinline bool toabsolute( ::booldog::result_wchar* pres , booldog::allocator* allocator , const wchar_t* path 
						, size_t charindex = 0 , size_t charcount = SIZE_MAX 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_wchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_wchar );
						const wchar_t* begin = &path[ charindex ];
						const wchar_t* ptr = begin;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case 0:
								goto goto_next_step1;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next_step1:
						res->wsize = ptr - begin;
						res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
						res->wlen = res->wsize - 1;						
						if( res->wchar )
						{
							if( res->wlen )
								::memcpy( res->wchar , begin , res->wlen * sizeof( wchar_t ) );
							res->wchar[ res->wlen ] = 0;
							res->wsize *= sizeof( wchar_t );
						
							::booldog::result locres1;
							::booldog::utils::io::path::wcs::toabsolute( &locres1 , res->wchar , res->wlen , res->wsize );
							if( locres1.succeeded() == false )
							{
								res->clear();
								res->copy( locres1 );
							}
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						return res->succeeded();
					};
					booinline bool filename( ::booldog::result_wchar* pres , booldog::allocator* allocator , const wchar_t* path 
						, size_t charindex = 0 , size_t charcount = SIZE_MAX 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_wchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_wchar );
						const wchar_t* begin = &path[ charindex ];
						const wchar_t* ptr = begin , * start = begin;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '/':
							case '\\':
								start = ptr;
								break;
							case 0:
								goto goto_next;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next:
						res->wsize = ptr - start;
						res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
						res->wlen = res->wsize - 1;
						res->wsize *= sizeof( wchar_t );
						if( res->wchar )
						{
							if( res->wlen )
								::memcpy( res->wchar , start , res->wlen * sizeof( wchar_t ) );
							res->wchar[ res->wlen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );					
						return res->succeeded();
					};
					booinline bool filename_without_extension( ::booldog::result_wchar* pres , booldog::allocator* allocator 
						, const wchar_t* path , size_t charindex = 0 , size_t charcount = SIZE_MAX 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_wchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_wchar );
						const wchar_t* begin = &path[ charindex ];
						const wchar_t* ptr = begin , * start = begin;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '/':
							case '\\':
								start = ptr;
								break;
							case 0:
								goto goto_next0;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next0:
						const wchar_t* end = ptr;
						ptr = start;						
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '.':
								end = ptr;
								break;
							case 0:
								goto goto_next1;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next1:
						res->wsize = end - start;
						res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
						res->wlen = res->wsize - 1;
						res->wsize *= sizeof( wchar_t );
						if( res->wchar )
						{
							if( res->wlen )
								::memcpy( res->wchar , start , res->wlen * sizeof( wchar_t ) );
							res->wchar[ res->wlen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );					
						return res->succeeded();
					};
					booinline bool extension( ::booldog::result_wchar* pres , booldog::allocator* allocator , const wchar_t* path 
						, size_t charindex = 0 , size_t charcount = SIZE_MAX 
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_wchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_wchar );
						const wchar_t* begin = &path[ charindex ];
						const wchar_t* ptr = begin , * start = begin;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '/':
							case '\\':
								start = ptr;
								break;
							case 0:
								goto goto_next0;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next0:
						ptr = start , start = 0;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '.':
								start = ptr;
								break;
							case 0:
								goto goto_next1;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next1:
						res->wsize = start ? ptr - start : 1;
						res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
						res->wlen = res->wsize - 1;
						res->wsize *= sizeof( wchar_t );
						if( res->wchar )
						{
							if( res->wlen )
								::memcpy( res->wchar , start , res->wlen * sizeof( wchar_t ) );
							res->wchar[ res->wlen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );					
						return res->succeeded();
					};
					booinline bool directory( ::booldog::result_wchar* pres , booldog::allocator* allocator , const wchar_t* path 
						, size_t charindex = 0 , size_t charcount = SIZE_MAX
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_wchar locres( allocator );
						BOOINIT_RESULT( ::booldog::result_wchar );
						const wchar_t* begin = &path[ charindex ];
						const wchar_t* ptr = begin , * end = begin;
						for( ; ; )
						{
							switch( *ptr++ )
							{
							case '/':
							case '\\':
								end = ptr;
								break;
							case 0:
								goto goto_next;
							}
							if( (size_t)( ptr - begin ) >= charcount )
							{
								++ptr;
								break;
							}
						}
	goto_next:
						res->wsize = end - begin;
						res->wchar = res->wallocator->realloc_array< wchar_t >( res->wchar , res->wsize , debuginfo );
						res->wlen = res->wsize - 1;
						res->wsize *= sizeof( wchar_t );
						if( res->wchar )
						{
							if( res->wlen )
								::memcpy( res->wchar , begin , res->wlen * sizeof( wchar_t ) );
							res->wchar[ res->wlen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );					
						return res->succeeded();
					};
				};
			};
		};
	};
};
#endif
