#ifndef BOO_IO_UTILS_H
#define BOO_IO_UTILS_H
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
#ifdef __WINDOWS__
#include <sys/types.h>
#include <sys/stat.h>
#else
#endif
namespace booldog
{	
	namespace utils
	{
		namespace io
		{	
			namespace path
			{
				namespace mbs
				{
					booinline bool toabsolute( ::booldog::result* pres , char* mbchar , size_t& mblen , size_t mbsize_in_bytes )
					{
						::booldog::result locres;
						BOOINIT_RESULT( ::booldog::result );
						if( mbchar [ 0 ] != 0 )
						{
							const char* ptr = mbchar;
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
								ptr++;
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
						
							::booldog::result locres;
							::booldog::utils::io::path::mbs::toabsolute( &locres , res->mbchar , res->mblen , res->mbsize );
							if( locres.succeeded() == false )
							{
								res->clear();
								res->copy( locres );
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
								ptr++;
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
								ptr++;
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
								ptr++;
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
								ptr++;
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
										ptr++;
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
								ptr++;
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
								ptr++;
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
								ptr++;
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
								ptr++;
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
					};
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
								ptr++;
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
								ptr++;
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
										ptr++;
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
								ptr++;
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
						
							::booldog::result locres;
							::booldog::utils::io::path::wcs::toabsolute( &locres , res->wchar , res->wlen , res->wsize );
							if( locres.succeeded() == false )
							{
								res->clear();
								res->copy( locres );
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
								ptr++;
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
								ptr++;
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
								ptr++;
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
								ptr++;
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
								ptr++;
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
								ptr++;
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