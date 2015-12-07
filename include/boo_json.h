#ifndef BOO_JSON_H
#define BOO_JSON_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_param.h>
#include <boo_allocator.h>
#include <boo_utf16.h>
#include <boo_utf8.h>
namespace booldog
{
	namespace enums
	{
		namespace data
		{
			namespace json
			{
				enum type
				{
					number ,
					string ,
					boolean_true ,
					boolean_false ,
					null ,
					array ,
					object
				};
			};
		};
	};
	namespace data
	{
		namespace json
		{
			struct node
			{		
				::booldog::enums::data::json::type type;
				::booldog::data::json::node* parent;
				::booldog::uint64 namehash;
				char* namebegin;
				char* nameend;
				char* valuebegin;
				char* valueend;
				::booldog::data::json::node* next;
				node( void )
				{
					type = ::booldog::enums::data::json::null;
					parent = 0;
					namehash = 0;
					namebegin = 0;
					nameend = 0;
					valuebegin = 0;
					valueend = 0;
					next = 0;
				};
				static ::booldog::data::json::node empty;
				::booldog::data::json::node& operator[]( size_t index )
				{
					return ::booldog::data::json::node::empty;
				};
				::booldog::data::json::node& operator()( const char* utf8name )
				{
					return ::booldog::data::json::node::empty;
				};
			};
			struct parsed
			{
				char* json;
				size_t jsonsize;
				size_t jsonlen;
				booldog::allocator* jsonallocator;
				size_t nodessize;
				size_t nodesindex;
				::booldog::data::json::node* nodes;
				parsed( booldog::allocator* allocator )
					: nodessize( 0 ) , nodesindex( 0 ) , nodes( 0 ) , json( 0 ) , jsonsize( 0 ) , jsonlen( 0 ) , jsonallocator( allocator )
				{
				};
				~parsed( void )
				{
					if( json )
						jsonallocator->free( json );
					if( nodes )
						jsonallocator->free( nodes );
				};
			};
			class result : public ::booldog::result
			{
			private:
				result( const ::booldog::result& )
					: parsed( 0 )
				{
				};
				result( const ::booldog::data::json::result& )
					: parsed( 0 )
				{
				};
				::booldog::data::json::result& operator = ( const ::booldog::data::json::result& )
				{
					return *this;
				};
			public:
				::booldog::data::json::parsed* parsed;
				result( ::booldog::data::json::parsed* pparsed )
 					: parsed( pparsed ) , ::booldog::result()
				{
				};
				virtual ~result( void )
				{
				};
				virtual void clear( void ) const
				{
					::booldog::data::json::result* _obj_ = const_cast< ::booldog::data::json::result* >( this );
		#ifdef __UNIX__
					_obj_->dlerrorclear();
		#endif
					_obj_->error_type = ::booldog::enums::result::error_type_no_error;
					_obj_->parsed->jsonlen = 0;
					_obj_->parsed->nodesindex = 0;
				};
			};
			const ::booldog::byte _white_space_table[] = 
			{
				0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x20 , 0x20 , 0xff , 0xff , 0x20 , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0x20, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff
			};
			template< size_t step >
			booinline bool parse( ::booldog::data::json::result* pres , const char* js , booldog::allocator* allocator = ::booldog::_allocator , ::booldog::debug::info* debuginfo = 0 )
			{
				::booldog::data::json::parsed parsed( allocator );
				::booldog::data::json::result locres( &parsed );
				BOOINIT_RESULT( ::booldog::data::json::result );
				if( js && js[ 0 ] != 0 )
				{		
					const char* ptr = js;
					for( ; ; )
					{
						switch( *ptr++ )
						{
						case 0:
							goto goto_next;
						}
					}
	goto_next:
					size_t size = ptr - js;
					res->parsed->jsonlen = size - 1;
					if( size > res->parsed->jsonsize )
					{
						res->parsed->jsonsize = size;
						res->parsed->json = res->parsed->jsonallocator->realloc_array< char >( res->parsed->json , res->parsed->jsonsize
							, debuginfo );
					}
					if( res->parsed->json )
					{
						::memcpy( res->parsed->json , js , res->parsed->jsonlen );
						res->parsed->json[ res->parsed->jsonlen ] = 0;
					}
					else
					{
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						goto goto_return;
					}

					::booldog::data::json::node* node = 0 , * curnode = 0 , * parentnode = 0;
					
					ptr = res->parsed->json;		
					const char* begin = 0 , * name_begin = 0 , * name_end = 0 , * string_begin = 0;
					::booldog::uint64 name_hash = 0;
goto_value_parse:
					begin = ptr;
					for( ; ; )
					{
						switch( _white_space_table[ (::booldog::byte)*ptr ] )
						{
						case 0x20:
							{
								ptr++;
								break;
							}
						default:
							goto goto_go_away_from_ws0;
						}
					}
goto_go_away_from_ws0:
					if( ptr != begin )
					{
						size = ptr - begin;
						::booldog::mem::remove< char >( (size_t)( begin - res->parsed->json ) , res->parsed->json , res->parsed->jsonsize
							, size );
						res->parsed->jsonlen -= size;
						res->parsed->json[ res->parsed->jsonlen ] = 0;
						ptr = begin;
					}

					switch( *ptr )
					{
					case '[':
						{
							if( res->parsed->nodesindex >= res->parsed->nodessize )
							{
								res->parsed->nodessize += step;
								char* nodesptr = (char*)res->parsed->nodes;
								res->parsed->nodes = res->parsed->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->parsed->nodes , res->parsed->nodessize , debuginfo );
								if( res->parsed->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->parsed->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->parsed->nodesindex ; index0++ )
									{
										if( res->parsed->nodes[ index0 ].next )
										{
											size = ((char*)res->parsed->nodes[ index0 ].next) - nodesptr;
											res->parsed->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
										if( res->parsed->nodes[ index0 ].parent )
										{
											size = ((char*)res->parsed->nodes[ index0 ].parent) - nodesptr;
											res->parsed->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
									}
								}
							}
							node = &res->parsed->nodes[ res->parsed->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::array;
							node->parent = parentnode;
							node->namebegin = (char*)name_begin;
							node->nameend = (char*)name_end;
							node->namehash = name_hash;
							name_begin = 0 , name_end = 0 , name_hash = 0;
							node->valuebegin = (char*)ptr;
							node->valueend = 0;
							node->next = 0;
							
							if( curnode )
							{
								curnode->next = node;
								curnode = 0;
							}
							if( parentnode && parentnode->next == 0 )
								parentnode->next = node;
							parentnode = node;

							ptr++;
							goto goto_comma_parse;
						}
					case '{':
						{
							if( res->parsed->nodesindex >= res->parsed->nodessize )
							{
								res->parsed->nodessize += step;
								char* nodesptr = (char*)res->parsed->nodes;
								res->parsed->nodes = res->parsed->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->parsed->nodes , res->parsed->nodessize , debuginfo );
								if( res->parsed->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->parsed->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->parsed->nodesindex ; index0++ )
									{
										if( res->parsed->nodes[ index0 ].next )
										{
											size = ((char*)res->parsed->nodes[ index0 ].next) - nodesptr;
											res->parsed->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
										if( res->parsed->nodes[ index0 ].parent )
										{
											size = ((char*)res->parsed->nodes[ index0 ].parent) - nodesptr;
											res->parsed->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
									}
								}
							}
							node = &res->parsed->nodes[ res->parsed->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::object;
							node->parent = parentnode;
							node->namebegin = (char*)name_begin;
							node->nameend = (char*)name_end;
							node->namehash = name_hash;
							name_begin = 0 , name_end = 0 , name_hash = 0;
							node->valuebegin = (char*)ptr;
							node->valueend = 0;
							node->next = 0;
							
							if( curnode )
							{
								curnode->next = node;
								curnode = 0;
							}
							if( parentnode && parentnode->next == 0 )
								parentnode->next = node;
							parentnode = node;

							ptr++;
							goto goto_object_name_parse;
						}
					case '"':
						{
							string_begin = ptr;
							ptr++;							
							for( ; ; )
							{
								switch( *ptr++ )
								{
								case '"':
									goto goto_object_name_parse_next1;
								case '\\':
									{
										switch( *ptr++ )
										{
										case '"':
										case '\\':
										case '/':
										case 'b':
										case 'f':
										case 'n':
										case 'r':
										case 't':
											break;
										case 'u':
											{
												begin = ptr - 2;
												::booldog::uint32 number = 0;
												if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
													number = 10 + *ptr - 0x61;
												else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
													number = *ptr - 0x30;
												else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
													number = 10 + *ptr - 0x41;
												else
												{
													res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
													goto goto_return;
												}

												ptr++;
												number <<= 4;
												if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
													number |= (::booldog::byte)( 10 + *ptr - 0x61 );
												else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
													number |= (::booldog::byte)( *ptr - 0x30 );
												else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
													number |= (::booldog::byte)( 10 + *ptr - 0x41 );
												else
												{
													res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
													goto goto_return;
												}

												ptr++;
												number <<= 4;
												if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
													number |= (::booldog::byte)( 10 + *ptr - 0x61 );
												else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
													number |= (::booldog::byte)( *ptr - 0x30 );
												else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
													number |= (::booldog::byte)( 10 + *ptr - 0x41 );
												else
												{
													res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
													goto goto_return;
												}

												ptr++;
												number <<= 4;
												if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
													number |= (::booldog::byte)( 10 + *ptr - 0x61 );
												else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
													number |= (::booldog::byte)( *ptr - 0x30 );
												else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
													number |= (::booldog::byte)( 10 + *ptr - 0x41 );
												else
												{
													res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
													goto goto_return;
												}

												if( number >= (::booldog::uint32)0xD800 && number <= (::booldog::uint32)0xDBFF ) 
												{
													if( ptr[ 1 ] == '\\' )
													{
														if( ptr[ 2 ] == 'u' )
														{
															::booldog::uint16 lowsurrogate = (::booldog::uint16)number;
															ptr += 3;
															number = 0;
															if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
																number |= (::booldog::byte)( 10 + *ptr - 0x61 );
															else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
																number |= (::booldog::byte)( *ptr - 0x30 );
															else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
																number |= (::booldog::byte)( 10 + *ptr - 0x41 );
															else
															{
																res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
																goto goto_return;
															}

															ptr++;
															number <<= 4;
															if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
																number |= (::booldog::byte)( 10 + *ptr - 0x61 );
															else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
																number |= (::booldog::byte)( *ptr - 0x30 );
															else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
																number |= (::booldog::byte)( 10 + *ptr - 0x41 );
															else
															{
																res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
																goto goto_return;
															}

															ptr++;
															number <<= 4;
															if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
																number |= (::booldog::byte)( 10 + *ptr - 0x61 );
															else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
																number |= (::booldog::byte)( *ptr - 0x30 );
															else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
																number |= (::booldog::byte)( 10 + *ptr - 0x41 );
															else
															{
																res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
																goto goto_return;
															}

															ptr++;
															number <<= 4;
															if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
																number |= (::booldog::byte)( ( 10 + *ptr - 0x61 ) );
															else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
																number |= (::booldog::byte)( *ptr - 0x30 );
															else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
																number |= (::booldog::byte)( 10 + *ptr - 0x41 );
															else
															{
																res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
																goto goto_return;
															}
															number <<= 16;
															number |= lowsurrogate;
														}
													}
												}
												char utf8[ 8 ] = {0};
												ptr++;
												size = ptr - begin;
												size_t utf16index = 0 , utf8bytes = 0 , utf8length = 0 , utf8byteindex = 0;
												if( ::booldog::utf16::to_utf8( (char*)&number , utf16index , size == 6 ? 2 : 4 , utf8
													, utf8byteindex	, 8	, utf8bytes , utf8length ) == ::booldog::enums::string::conversion_result_OK )
												{
													::booldog::mem::insert< char >( begin - res->parsed->json , res->parsed->json 
														, res->parsed->jsonlen + 1 , res->parsed->jsonsize
														, size , utf8 , utf8bytes );
													res->parsed->jsonlen -= size - utf8bytes;
													res->parsed->json[ res->parsed->jsonlen ] = 0;
													ptr = begin + utf8bytes;
												}
												else
												{
													res->booerr( ::booldog::enums::result::booerr_type_json_cannot_convert_from_utf16_to_utf8 );
													goto goto_return;
												}
												break;
											}
										case 0:
											{
												res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_end_of_string );
												goto goto_return;
											}
										default:
											{
												res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_escaped_symbol );
												goto goto_return;
											}
										}
										break;
									}
								case 0:
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_end_of_string );
										goto goto_return;
									}
								default:
									{
										ptr--;
										const ::booldog::byte* ptrbyte = (::booldog::byte*)ptr;
										if( ::booldog::utf8::validate_character( ptrbyte ) == false )
										{
											res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
											goto goto_return;
										}
										ptr = (char*)ptrbyte;
										break;
									}
								}
							}
		goto_object_name_parse_next1:
							if( res->parsed->nodesindex >= res->parsed->nodessize )
							{
								res->parsed->nodessize += step;
								char* nodesptr = (char*)res->parsed->nodes;
								res->parsed->nodes = res->parsed->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->parsed->nodes , res->parsed->nodessize , debuginfo );
								if( res->parsed->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->parsed->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->parsed->nodesindex ; index0++ )
									{
										if( res->parsed->nodes[ index0 ].next )
										{
											size = ((char*)res->parsed->nodes[ index0 ].next) - nodesptr;
											res->parsed->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
										if( res->parsed->nodes[ index0 ].parent )
										{
											size = ((char*)res->parsed->nodes[ index0 ].parent) - nodesptr;
											res->parsed->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
									}
								}
							}
							node = &res->parsed->nodes[ res->parsed->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::string;
							node->parent = parentnode;
							node->namebegin = (char*)name_begin;
							node->nameend = (char*)name_end;
							node->namehash = name_hash;
							name_begin = 0 , name_end = 0 , name_hash = 0;
							node->valuebegin = (char*)string_begin;
							node->valueend = (char*)ptr - 1;
							node->next = 0;
							
							if( curnode )
								curnode->next = node;
							curnode = node;
							if( parentnode )
							{
								if( parentnode->next == 0 )
									parentnode->next = node;
								goto goto_comma_parse;
							}
							else
								goto goto_end_parse;
						}
					case 'f':
						{
							if( *++ptr != 'a' )
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_false );
								goto goto_return;
							}
							if( *++ptr != 'l' )
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_false );
								goto goto_return;
							}
							if( *++ptr != 's' )
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_false );
								goto goto_return;
							}
							if( *++ptr != 'e' )
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_false );
								goto goto_return;
							}


							if( res->parsed->nodesindex >= res->parsed->nodessize )
							{
								res->parsed->nodessize += step;
								char* nodesptr = (char*)res->parsed->nodes;
								res->parsed->nodes = res->parsed->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->parsed->nodes , res->parsed->nodessize , debuginfo );
								if( res->parsed->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->parsed->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->parsed->nodesindex ; index0++ )
									{
										if( res->parsed->nodes[ index0 ].next )
										{
											size = ((char*)res->parsed->nodes[ index0 ].next) - nodesptr;
											res->parsed->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
										if( res->parsed->nodes[ index0 ].parent )
										{
											size = ((char*)res->parsed->nodes[ index0 ].parent) - nodesptr;
											res->parsed->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
									}
								}
							}
							node = &res->parsed->nodes[ res->parsed->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::boolean_false;
							node->parent = parentnode;
							node->namebegin = (char*)name_begin;
							node->nameend = (char*)name_end;
							node->namehash = name_hash;
							name_begin = 0 , name_end = 0 , name_hash = 0;
							node->valuebegin = (char*)( ptr - 4 );
							node->valueend = (char*)ptr;
							node->next = 0;
							
							if( curnode )
								curnode->next = node;
							curnode = node;
							if( parentnode )
							{
								if( parentnode->next == 0 )
									parentnode->next = node;
								ptr++;
								goto goto_comma_parse;
							}
							else
								goto goto_end_parse;
						}
					case 't':
						{
							if( *++ptr != 'r' )
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_true );
								goto goto_return;
							}
							if( *++ptr != 'u' )
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_true );
								goto goto_return;
							}
							if( *++ptr != 'e' )
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_true );
								goto goto_return;
							}


							if( res->parsed->nodesindex >= res->parsed->nodessize )
							{
								res->parsed->nodessize += step;
								char* nodesptr = (char*)res->parsed->nodes;
								res->parsed->nodes = res->parsed->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->parsed->nodes , res->parsed->nodessize , debuginfo );
								if( res->parsed->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->parsed->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->parsed->nodesindex ; index0++ )
									{
										if( res->parsed->nodes[ index0 ].next )
										{
											size = ((char*)res->parsed->nodes[ index0 ].next) - nodesptr;
											res->parsed->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
										if( res->parsed->nodes[ index0 ].parent )
										{
											size = ((char*)res->parsed->nodes[ index0 ].parent) - nodesptr;
											res->parsed->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
									}
								}
							}
							node = &res->parsed->nodes[ res->parsed->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::boolean_true;
							node->parent = parentnode;
							node->namebegin = (char*)name_begin;
							node->nameend = (char*)name_end;
							node->namehash = name_hash;
							name_begin = 0 , name_end = 0 , name_hash = 0;
							node->valuebegin = (char*)( ptr - 3 );
							node->valueend = (char*)ptr;
							node->next = 0;
							
							if( curnode )
								curnode->next = node;
							curnode = node;
							if( parentnode )
							{
								if( parentnode->next == 0 )
									parentnode->next = node;
								ptr++;
								goto goto_comma_parse;
							}
							else
								goto goto_end_parse;
						}
					case 'n':
						{
							if( *++ptr != 'u' )
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_null );
								goto goto_return;
							}
							if( *++ptr != 'l' )
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_null );
								goto goto_return;
							}
							if( *++ptr != 'l' )
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_null );
								goto goto_return;
							}


							if( res->parsed->nodesindex >= res->parsed->nodessize )
							{
								res->parsed->nodessize += step;
								char* nodesptr = (char*)res->parsed->nodes;
								res->parsed->nodes = res->parsed->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->parsed->nodes , res->parsed->nodessize , debuginfo );
								if( res->parsed->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->parsed->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->parsed->nodesindex ; index0++ )
									{
										if( res->parsed->nodes[ index0 ].next )
										{
											size = ((char*)res->parsed->nodes[ index0 ].next) - nodesptr;
											res->parsed->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
										if( res->parsed->nodes[ index0 ].parent )
										{
											size = ((char*)res->parsed->nodes[ index0 ].parent) - nodesptr;
											res->parsed->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
									}
								}
							}
							node = &res->parsed->nodes[ res->parsed->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::null;
							node->parent = parentnode;
							node->namebegin = (char*)name_begin;
							node->nameend = (char*)name_end;
							node->namehash = name_hash;
							name_begin = 0 , name_end = 0 , name_hash = 0;
							node->valuebegin = (char*)( ptr - 3 );
							node->valueend = (char*)ptr;
							node->next = 0;
							
							if( curnode )
								curnode->next = node;
							curnode = node;
							if( parentnode )
							{
								if( parentnode->next == 0 )
									parentnode->next = node;
								ptr++;
								goto goto_comma_parse;
							}
							else
								goto goto_end_parse;
						}
					case '0':
						{
							begin = ptr;
							switch( *++ptr )
							{
								case '.':
									goto goto_float_parse;
								case 'e':
								case 'E':
									goto goto_exponent_parse;
								case '-':
								case '0':
								case '1':
								case '2':
								case '3':
								case '4':
								case '5':
								case '6':
								case '7':
								case '8':
								case '9':
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_expecting_decimal_point_or_exponent_part_in_number );
										goto goto_return;	
									}
							}
							goto goto_number_create;
						}
					case '-':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						{
							begin = ptr;
							for( ; ; )
							{
								switch( *++ptr )
								{
								case '.':
									goto goto_float_parse;
								case 'e':
								case 'E':
									goto goto_exponent_parse;
								case '0':
								case '1':
								case '2':
								case '3':
								case '4':
								case '5':
								case '6':
								case '7':
								case '8':
								case '9':
									break;
								case '-':
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_minus_in_number );
										goto goto_return;
									}
								default:
									{
										if( begin == ptr - 1 && *begin == '-' )
										{
											res->booerr( ::booldog::enums::result::booerr_type_json_expecting_digit_after_minus );
											goto goto_return;
										}
										goto goto_number_create;
									}
								}
							}
goto_float_parse:
							string_begin = ptr;
							for( ; ; )
							{
								switch( *++ptr )
								{
								case '.':
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_second_decimal_point_in_number );
										goto goto_return;
									}
								case 'e':
								case 'E':
									{
										if( string_begin == ptr - 1 )
										{
											res->booerr( ::booldog::enums::result::booerr_type_json_expecting_digit_after_decimal_point );
											goto goto_return;
										}
										goto goto_exponent_parse;
									}
								case '0':
								case '1':
								case '2':
								case '3':
								case '4':
								case '5':
								case '6':
								case '7':
								case '8':
								case '9':
									break;
								case '-':
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_minus_in_number );
										goto goto_return;
									}
								default:
									{
										if( string_begin == ptr - 1 )
										{
											res->booerr( ::booldog::enums::result::booerr_type_json_expecting_digit_after_decimal_point );
											goto goto_return;
										}
										goto goto_number_create;
									}
								}
							}
goto_exponent_parse:
							switch( ptr[ 1 ] )
							{
							case '-':
							case '+':
								{
									ptr++;
									break;
								}
							}
							string_begin = ptr;
							for( ; ; )
							{
								switch( *++ptr )
								{
								case '0':
								case '1':
								case '2':
								case '3':
								case '4':
								case '5':
								case '6':
								case '7':
								case '8':
								case '9':
									break;
								case '+':
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_plus_in_number );
										goto goto_return;
									}
								case '-':
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_minus_in_number );
										goto goto_return;
									}
								case '.':
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_decimal_point_in_number );
										goto goto_return;
									}
								case 'e':
								case 'E':
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_second_exponent_part_symbol_in_number );
										goto goto_return;
									}
								default:
									{
										if( string_begin == ptr - 1 )
										{
											res->booerr( ::booldog::enums::result::booerr_type_json_expecting_digit_after_exponent_part_symbol );
											goto goto_return;
										}
										goto goto_number_create;
									}
								}
							}
goto_number_create:
							if( res->parsed->nodesindex >= res->parsed->nodessize )
							{
								res->parsed->nodessize += step;
								char* nodesptr = (char*)res->parsed->nodes;
								res->parsed->nodes = res->parsed->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->parsed->nodes , res->parsed->nodessize , debuginfo );
								if( res->parsed->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->parsed->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->parsed->nodesindex ; index0++ )
									{
										if( res->parsed->nodes[ index0 ].next )
										{
											size = ((char*)res->parsed->nodes[ index0 ].next) - nodesptr;
											res->parsed->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
										if( res->parsed->nodes[ index0 ].parent )
										{
											size = ((char*)res->parsed->nodes[ index0 ].parent) - nodesptr;
											res->parsed->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->parsed->nodes) + size);
										}
									}
								}
							}
							node = &res->parsed->nodes[ res->parsed->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::number;
							node->parent = parentnode;
							node->namebegin = (char*)name_begin;
							node->nameend = (char*)name_end;
							node->namehash = name_hash;
							name_begin = 0 , name_end = 0 , name_hash = 0;
							node->valuebegin = (char*)begin;
							node->valueend = (char*)ptr - 1;
							node->next = 0;
							
							if( curnode )
								curnode->next = node;
							curnode = node;
							if( parentnode )
							{
								if( parentnode->next == 0 )
									parentnode->next = node;
								goto goto_comma_parse;
							}
							else
								goto goto_end_parse;
						}
					default:
						{
							res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_symbol );
							goto goto_return;
						}
					}
goto_comma_parse:
					begin = ptr;
					for( ; ; )
					{
						switch( _white_space_table[ (::booldog::byte)*ptr ] )
						{
						case 0x20:
							{
								ptr++;
								break;
							}
						default:
							goto goto_go_away_from_ws3;
						}
					}
goto_go_away_from_ws3:
					if( ptr != begin )
					{
						size = ptr - begin;
						::booldog::mem::remove< char >( (size_t)( begin - res->parsed->json ) , res->parsed->json , res->parsed->jsonsize
							, size );
						res->parsed->jsonlen -= size;
						res->parsed->json[ res->parsed->jsonlen ] = 0;
						ptr = begin;
					}
					if( parentnode->type == ::booldog::enums::data::json::object )
					{
						switch( *ptr++ )
						{
						case ',':
							goto goto_object_name_parse;
						case '}':
							{
								parentnode->valueend = (char*)( ptr - 1 );
								if( parentnode->parent )
								{
									curnode = parentnode;
									parentnode = parentnode->parent;
									goto goto_comma_parse;
								}
								else
									goto goto_end_parse;
							}
						default:
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_value_separator );
								goto goto_return;
							}
						}
					}
					else
					{
						switch( *ptr++ )
						{
						case ',':
							{
								if( parentnode->next )
									goto goto_value_parse;
								else
								{
									res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_value_separator );
									goto goto_return;
								}
							}
						case ']':
							{
								parentnode->valueend = (char*)( ptr - 1 );
								if( parentnode->parent )
								{
									curnode = parentnode;
									parentnode = parentnode->parent;
									goto goto_comma_parse;
								}
								else
									goto goto_end_parse;
							}
						default:
							{
								if( parentnode->next == 0 )
								{
									ptr--;
									goto goto_value_parse;
								}
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_value_separator );
								goto goto_return;
							}
						}
					}
goto_object_name_parse:
					begin = ptr;
					for( ; ; )
					{
						switch( _white_space_table[ (::booldog::byte)*ptr ] )
						{
						case 0x20:
							{
								ptr++;
								break;
							}
						default:
							goto goto_go_away_from_ws1;
						}
					}
goto_go_away_from_ws1:
					if( ptr != begin )
					{
						size = ptr - begin;
						::booldog::mem::remove< char >( (size_t)( begin - res->parsed->json ) , res->parsed->json , res->parsed->jsonsize
							, size );
						res->parsed->jsonlen -= size;
						res->parsed->json[ res->parsed->jsonlen ] = 0;
						ptr = begin;
					}
					switch( *ptr++ )
					{
					case '"':
						break;
					case '}':
						{
							if( ptr[ -2 ] == ',' )
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_value_separator );
								goto goto_return;
							}
							parentnode->valueend = (char*)( ptr - 1 );
							if( parentnode->parent )
							{
								curnode = parentnode;
								parentnode = parentnode->parent;
								goto goto_comma_parse;
							}
							else
								goto goto_end_parse;
						}
					default:
						{
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_string_in_object_name );
							goto goto_return;
						}
					}
					name_begin = ptr;
					for( ; ; )
					{
						switch( *ptr++ )
						{
						case '"':
							goto goto_object_name_parse_next0;
						case '\\':
							{
								switch( *ptr++ )
								{
								case '"':
									{
										name_hash = name_hash * 33 + (::booldog::byte)'"';
										break;
									}
								case '\\':
									{
										name_hash = name_hash * 33 + (::booldog::byte)'\\';
										break;
									}
								case '/':
									{
										name_hash = name_hash * 33 + (::booldog::byte)'/';
										break;
									}
								case 'b':
									{
										name_hash = name_hash * 33 + (::booldog::byte)'\b';
										break;
									}
								case 'f':
									{
										name_hash = name_hash * 33 + (::booldog::byte)'\f';
										break;
									}
								case 'n':
									{
										name_hash = name_hash * 33 + (::booldog::byte)'\n';
										break;
									}
								case 'r':
									{
										name_hash = name_hash * 33 + (::booldog::byte)'\r';
										break;
									}
								case 't':
									{
										name_hash = name_hash * 33 + (::booldog::byte)'\t';
										break;
									}
								case 'u':
									{
										begin = ptr - 2;
										::booldog::uint32 number = 0;
										if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
											number = 10 + *ptr - 0x61;
										else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
											number = *ptr - 0x30;
										else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
											number = 10 + *ptr - 0x41;
										else
										{
											res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
											goto goto_return;
										}

										ptr++;
										number <<= 4;
										if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
											number |= (::booldog::byte)( 10 + *ptr - 0x61 );
										else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
											number |= (::booldog::byte)( *ptr - 0x30 );
										else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
											number |= (::booldog::byte)( 10 + *ptr - 0x41 );
										else
										{
											res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
											goto goto_return;
										}

										ptr++;
										number <<= 4;
										if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
											number |= (::booldog::byte)( 10 + *ptr - 0x61 );
										else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
											number |= (::booldog::byte)( *ptr - 0x30 );
										else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
											number |= (::booldog::byte)( 10 + *ptr - 0x41 );
										else
										{
											res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
											goto goto_return;
										}

										ptr++;
										number <<= 4;
										if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
											number |= (::booldog::byte)( 10 + *ptr - 0x61 );
										else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
											number |= (::booldog::byte)( *ptr - 0x30 );
										else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
											number |= (::booldog::byte)( 10 + *ptr - 0x41 );
										else
										{
											res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
											goto goto_return;
										}

										if( number >= (::booldog::uint32)0xD800 && number <= (::booldog::uint32)0xDBFF ) 
										{
											if( ptr[ 1 ] == '\\' )
											{
												if( ptr[ 2 ] == 'u' )
												{
													::booldog::uint16 lowsurrogate = (::booldog::uint16)number;
													ptr += 3;
													number = 0;
													if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
														number |= (::booldog::byte)( 10 + *ptr - 0x61 );
													else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
														number |= (::booldog::byte)( *ptr - 0x30 );
													else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
														number |= (::booldog::byte)( 10 + *ptr - 0x41 );
													else
													{
														res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
														goto goto_return;
													}

													ptr++;
													number <<= 4;
													if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
														number |= (::booldog::byte)( 10 + *ptr - 0x61 );
													else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
														number |= (::booldog::byte)( *ptr - 0x30 );
													else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
														number |= (::booldog::byte)( 10 + *ptr - 0x41 );
													else
													{
														res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
														goto goto_return;
													}

													ptr++;
													number <<= 4;
													if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
														number |= (::booldog::byte)( 10 + *ptr - 0x61 );
													else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
														number |= (::booldog::byte)( *ptr - 0x30 );
													else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
														number |= (::booldog::byte)( 10 + *ptr - 0x41 );
													else
													{
														res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
														goto goto_return;
													}

													ptr++;
													number <<= 4;
													if( *ptr >= 0x61 && *ptr <= 0x66 )//a-f
														number |= (::booldog::byte)( ( 10 + *ptr - 0x61 ) );
													else if( *ptr >= 0x30 && *ptr <= 0x39 )//0-9
														number |= (::booldog::byte)( *ptr - 0x30 );
													else if( *ptr >= 0x41 && *ptr <= 0x46 )//A-F
														number |= (::booldog::byte)( 10 + *ptr - 0x41 );
													else
													{
														res->booerr( ::booldog::enums::result::booerr_type_json_expecting_hex_symbol );
														goto goto_return;
													}
													number <<= 16;
													number |= lowsurrogate;
												}
											}
										}
										char utf8[ 8 ] = {0};
										ptr++;
										size = ptr - begin;
										size_t utf16index = 0 , utf8bytes = 0 , utf8length = 0 , utf8byteindex = 0;
										if( ::booldog::utf16::to_utf8( (char*)&number , utf16index , size == 6 ? 2 : 4 , utf8
											, utf8byteindex	, 8	, utf8bytes , utf8length ) == ::booldog::enums::string::conversion_result_OK )
										{
											::booldog::mem::insert< char >( begin - res->parsed->json , res->parsed->json 
												, res->parsed->jsonlen + 1 , res->parsed->jsonsize
												, size , utf8 , utf8bytes );
											res->parsed->jsonlen -= size - utf8bytes;
											res->parsed->json[ res->parsed->jsonlen ] = 0;
											ptr = begin + utf8bytes;

											for( size_t index = 0 ; index < utf8bytes ; index++ )
												name_hash = name_hash * 33 + (::booldog::byte)utf8[ index ];
										}
										else
										{
											res->booerr( ::booldog::enums::result::booerr_type_json_cannot_convert_from_utf16_to_utf8 );
											goto goto_return;
										}
										break;
									}
								case 0:
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_end_of_string );
										goto goto_return;
									}
								default:
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_escaped_symbol );
										goto goto_return;
									}
								}
								break;
							}
						case 0:
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_end_of_string );
								goto goto_return;
							}
						default:
							{
								ptr--;
								const ::booldog::byte* ptrbyte = (::booldog::byte*)ptr;
								if( ::booldog::utf8::validate_character( ptrbyte ) == false )
								{
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								size = (char*)ptrbyte - ptr;																
								for( size_t index0 = 0 ; index0 < size ; index0++ )
									name_hash = name_hash * 33 + (::booldog::byte)ptr[ index0 ];
								ptr = (char*)ptrbyte;
								break;
							}
						}
					}
goto_object_name_parse_next0:
					name_end = ptr - 1;
					begin = ptr;
					for( ; ; )
					{
						switch( _white_space_table[ (::booldog::byte)*ptr ] )
						{
						case 0x20:
							{
								ptr++;
								break;
							}
						default:
							goto goto_go_away_from_ws2;
						}
					}
goto_go_away_from_ws2:
					if( ptr != begin )
					{
						size = ptr - begin;
						::booldog::mem::remove< char >( (size_t)( begin - res->parsed->json ) , res->parsed->json , res->parsed->jsonsize
							, size );
						res->parsed->jsonlen -= size;
						res->parsed->json[ res->parsed->jsonlen ] = 0;
						ptr = begin;
					}
					switch( *ptr++ )
					{
					case ':':
						goto goto_value_parse;
					default:
						{
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_name_separator );
							goto goto_return;
						}
					}
goto_end_parse:
					begin = ptr;
					for( ; ; )
					{
						switch( _white_space_table[ (::booldog::byte)*ptr ] )
						{
						case 0x20:
							{
								ptr++;
								break;
							}
						case 0:
							goto goto_go_away_from_ws4;
						default:
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_expecting_end_of_string );
								goto goto_return;
							}
						}
					}
goto_go_away_from_ws4:
					if( ptr != begin )
					{
						size = ptr - begin;
						::booldog::mem::remove< char >( (size_t)( begin - res->parsed->json ) , res->parsed->json , res->parsed->jsonsize
							, size );
						res->parsed->jsonlen -= size;
						res->parsed->json[ res->parsed->jsonlen ] = 0;
					}
				}
				else
					res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
goto_return:
				if( res->succeeded() )
					return true;
				else
				{
					res->parsed->json[ 0 ] = 0;
					res->parsed->jsonlen = 0;
					res->parsed->nodesindex = 0;
					return false;
				}
			};
		};
	};
};
#endif