#ifndef BOO_JSON_H
#define BOO_JSON_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_param.h>
#include <boo_allocator.h>
#include <boo_utf16.h>
#include <boo_utf8.h>
#include <boo_utils.h>

#include <math.h>
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
					number = 0 ,
					string = 1 ,
					boolean_true = 2 ,
					boolean_false = 3 ,
					null = 4 ,
					array = 5 ,
					object = 6 , 
					notexists = 7
				};
			};
		};
	};
	namespace data
	{
		namespace json
		{
#define BOOLDOG_DATA_JSON_NAME_SERIALIZED 0
#define BOOLDOG_DATA_JSON_ROOT 1
#define BOOLDOG_DATA_JSON_VALUE_SERIALIZED 2
			struct node;
			struct serializator;

			boobegin_struct_pack( 1 )
			struct object_json
			{
				::booldog::data::json::node* node;
				operator const char*() const;
			}
			booend_struct_pack( 1 );

			boobegin_struct_pack( 1 )
			struct object_value
			{
				::booldog::data::json::node* node;
				operator float() const;
				operator const char*() const;
				operator ::booldog::int32() const;
				operator ::booldog::int64() const;
				operator ::booldog::uint32() const;
				operator ::booldog::uint64() const;
				operator bool() const;
				const char* name( void ) const;
			}
			booend_struct_pack( 1 );

			boobegin_struct_pack( 1 )
			struct node
			{	
				::booldog::byte flags;
				::booldog::byte type;
				union
				{
					::booldog::data::json::node* parent;
					::booldog::data::json::serializator* serializator;
				};
				::booldog::uint64 namehash;
				char* name_or_valuebegin;
				char* valueend;
				::booldog::data::json::node* next;
				::booldog::data::json::node* child;
				const char* name( void ) const;
				void offset( int diff , char* valueend )
				{
					::booldog::data::json::node* pnext = child;
					for( ; ; )
					{
						if( pnext )
						{
							pnext->offset( diff , valueend );
							if( pnext->name_or_valuebegin > valueend )
							{
								pnext->name_or_valuebegin += diff;
								pnext->valueend += diff;
							}
						}
						else
							break;
						pnext = pnext->next;
					}
				};
				void offset( char* oldjsonstr , char* jsonstr )
				{
					::booldog::data::json::node* pnext = child;
					for( ; ; )
					{
						if( pnext )
						{
							pnext->offset( oldjsonstr , jsonstr );
							pnext->name_or_valuebegin = jsonstr + ( pnext->name_or_valuebegin - oldjsonstr );
							pnext->valueend = jsonstr + ( pnext->valueend - oldjsonstr );
						}
						else
							break;
						pnext = pnext->next;
					}
				};
				const char* json( ::booldog::data::json::serializator* parentserializator , const ::booldog::debug::info& debuginfo = debuginfo_macros ) const;
			}
			booend_struct_pack( 1 );

			struct object
			{
				union
				{
					object_json json;
					object_value value;
				};
				object( void )
				{
					json.node = 0;
				};
				object( ::booldog::data::json::node* srcnode )
				{
					json.node = srcnode;
				};
				::booldog::data::json::object operator[]( size_t index );
				::booldog::data::json::object operator()( const char* utf8name );
				const char* name( void ) const
				{
					return value.name();
				};
				bool exists( void )
				{
					return json.node != 0;
				};
				bool isstring( void )
				{
					return json.node && json.node->type == ::booldog::enums::data::json::string;
				};
				bool isnumber( void )
				{
					return json.node && json.node->type == ::booldog::enums::data::json::number;
				};
				bool isnull( void )
				{
					return json.node && json.node->type == ::booldog::enums::data::json::null;
				};
				bool isboolean( void )
				{
					return json.node && ( json.node->type == ::booldog::enums::data::json::boolean_true
						|| json.node->type == ::booldog::enums::data::json::boolean_false );
				};
				bool isobject( void )
				{
					return json.node && json.node->type == ::booldog::enums::data::json::object;
				};
				bool isarray( void )
				{
					return json.node && json.node->type == ::booldog::enums::data::json::array;
				};
				size_t count( void )
				{
					if( json.node && ( json.node->type == ::booldog::enums::data::json::array
						|| json.node->type == ::booldog::enums::data::json::object ) )
					{
						size_t count = 0;
						::booldog::data::json::node* pnext = json.node->child;
						for( ; ; )
						{
							if( pnext == 0 )
								break;
							pnext = pnext->next;
							count++;
						}
						return count;
					}
					return 0;
				};
			};
			::booldog::data::json::object object::operator[]( size_t index )
			{
				if( json.node && json.node->type == ::booldog::enums::data::json::array )
				{
					::booldog::data::json::node* pnext = json.node->child;
					for( ; ; )
					{
						if( pnext == 0 )
							break;
						if( index == 0 )
							return ::booldog::data::json::object( pnext );
						pnext = pnext->next;
						index--;
					}
				}
				return ::booldog::data::json::object();
			};
			::booldog::data::json::object object::operator()( const char* utf8name )
			{
				if( utf8name && json.node && json.node->type == ::booldog::enums::data::json::object )
				{
					const char* ptr = utf8name;
					::booldog::uint64 utf8namehash = 0;
					for( ; *ptr != 0 ; ptr++ )
						utf8namehash = utf8namehash * 33 + (::booldog::byte)*ptr;
					::booldog::data::json::node* pnext = json.node->child;
					for( ; ; )
					{
						if( pnext == 0 )
							break;
						if( pnext->namehash == utf8namehash )
						{
							const char* ptr0 = pnext->name_or_valuebegin , * ptr1 = utf8name;
							if( ::booldog::utils::get_bit( pnext->flags	, BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
								ptr0 = pnext->name();
							for( ; ; )
							{
								if( *ptr0 == 0 || *ptr1 == 0 )
								{
									if( *ptr0 == *ptr1 )
										break;
									goto goto_next;
								}
								if( *ptr0++ != *ptr1++ )
									goto goto_next;
							}
							return ::booldog::data::json::object( pnext );
						}
		goto_next:
						pnext = pnext->next;
					}
				}
				return ::booldog::data::json::object();
			};
			struct serializator
			{
				char* json;
				size_t jsonsize;
				size_t jsonlen;
				booldog::allocator* jsonallocator;
				size_t nodessize;
				size_t nodesindex;
				::booldog::data::json::node* nodes;
				serializator( booldog::allocator* allocator )
					: nodessize( 0 ) , nodesindex( 0 ) , nodes( 0 ) , json( 0 ) , jsonsize( 0 ) , jsonlen( 0 ) , jsonallocator( allocator )
				{
				};
				~serializator( void )
				{
					if( json )
						jsonallocator->free( json );
					if( nodes )
						jsonallocator->free( nodes );
				};
				operator ::booldog::data::json::object() const
				{	
					if( nodesindex )
						return ::booldog::data::json::object( &nodes[ 0 ] );
					return ::booldog::data::json::object();
				};
				operator ::booldog::data::json::object()
				{	
					if( nodesindex )
						return ::booldog::data::json::object( &nodes[ 0 ] );
					return ::booldog::data::json::object();
				};
			};
			const ::booldog::byte _decimal_string_to_number_table[] = 
			{
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,//0-15
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,//16-31
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , (::booldog::byte)'.', 0xff,//32-47
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,//48-63
				0xff, 0xff, 0xff, 0xff, 0xff, (::booldog::byte)'e', 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,//64-79
				0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,//80-95
				0xff, 0xff, 0xff, 0xff, 0xff, (::booldog::byte)'e', 0xff, 0xff, 0xff, 0xff , 0xff , 0xff , 0xff , 0xff , 0xff, 0xff,//96-112
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
			object_value::operator bool() const
			{
				if( node && node->type == ::booldog::enums::data::json::boolean_true )
					return true;
				return false;
			};
			object_value::operator ::booldog::int32() const
			{
				if( node == 0 || node->type != ::booldog::enums::data::json::number )
					return 0;
				char* ptr = node->name_or_valuebegin;
				if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_ROOT ) == 0
					&& node->parent->type == ::booldog::enums::data::json::object )
				{
					if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
					{
						for( ; ; )
						{
							switch( *++ptr )
							{
							case '\\':
								ptr++;
								break;
							case '"':
								goto goto_next0;
							}
						}
goto_next0:
						;
					}
					else
					{
						for( ; ; )
						{
							if( *++ptr == 0 )
								break;
						}
					}
					ptr += 2;
				}

				::booldog::uint64 res = 0;
				int exponent_part_count = 0;
				bool negative = false;
				if( *ptr == '-' )
				{
					negative = true;
					ptr++;
				}
				int res_float_part_count = 0;
				::booldog::uint64 res_float_part = 0;				
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					switch( ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr ] )
					{
					case (::booldog::byte)'e':
						{
							ptr++;
							goto goto_exponent_part;
						}
					case (::booldog::byte)'.':
						{
							ptr++;
							goto goto_float;
						}
					default:
						{
							res *= 10;
							res += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
							break;
						}
					}
				}
goto_float:
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					switch( ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr ] )
					{
					case (::booldog::byte)'e':
						{
							ptr++;
							goto goto_exponent_part;
						}
					default:
						{
							res_float_part *= 10;
							res_float_part += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
							res_float_part_count--;
							break;
						}
					}
				}
goto_exponent_part:
				switch( *ptr )
				{
				case '-':
					ptr++;
					goto goto_exponent_part_minus;
				case '+':
					ptr++;
				}
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
				goto goto_return;
goto_exponent_part_minus:
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count -= ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
goto_return:
				::booldog::int32 realres = 0;
				float realfloatpart = 0;

				res_float_part_count += exponent_part_count;
				if( exponent_part_count < 0 )
				{
					float temp = (float)res;
					temp *= pow( 10.f , exponent_part_count );
					realres = (::booldog::int32)temp;
				}
				else if( exponent_part_count > 0 )
				{
					for( int index0 = 0 ; index0 < exponent_part_count ; index0++ )
						res *= 10;
					realres = (::booldog::int32)res;
				}
				else
					realres = (::booldog::int32)res;
				if( res_float_part_count > 0 )
				{
					for( int index0 = 0 ; index0 < res_float_part_count ; index0++ )
						res_float_part *= 10;
					realres = (::booldog::int32)( realres + res_float_part );
				}
				else if( res_float_part_count < 0 )
				{
					realfloatpart = (float)res_float_part;
					realfloatpart *= pow( 10.f , res_float_part_count );
				}
				realres = (::booldog::int32)( realres + realfloatpart );
				if( negative )
					realres *= -1;

				return realres;
			};
			object_value::operator float() const
			{
				if( node == 0 || node->type != ::booldog::enums::data::json::number )
					return 0;
				char* ptr = node->name_or_valuebegin;
				if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_ROOT ) == 0
					&& node->parent->type == ::booldog::enums::data::json::object )
				{
					if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
					{
						for( ; ; )
						{
							switch( *++ptr )
							{
							case '\\':
								ptr++;
								break;
							case '"':
								goto goto_next0;
							}
						}
goto_next0:
						;
					}
					else
					{
						for( ; ; )
						{
							if( *++ptr == 0 )
								break;
						}
					}
					ptr += 2;
				}

				::booldog::uint64 res = 0;
				int exponent_part_count = 0;
				bool negative = false;
				if( *ptr == '-' )
				{
					negative = true;
					ptr++;
				}
				int res_float_part_count = 0;
				::booldog::uint64 res_float_part = 0;				
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					switch( ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr ] )
					{
					case (::booldog::byte)'e':
						{
							ptr++;
							goto goto_exponent_part;
						}
					case (::booldog::byte)'.':
						{
							ptr++;
							goto goto_float;
						}
					default:
						{
							res *= 10;
							res += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
							break;
						}
					}
				}
goto_float:
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					switch( ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr ] )
					{
					case (::booldog::byte)'e':
						{
							ptr++;
							goto goto_exponent_part;
						}
					default:
						{
							res_float_part *= 10;
							res_float_part += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
							res_float_part_count--;
							break;
						}
					}
				}
goto_exponent_part:
				switch( *ptr )
				{
				case '-':
					ptr++;
					goto goto_exponent_part_minus;
				case '+':
					ptr++;
				}
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
				goto goto_return;
goto_exponent_part_minus:
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count -= ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
goto_return:
				float realres = 0;
				float realfloatpart = 0;

				res_float_part_count += exponent_part_count;
				if( exponent_part_count < 0 )
				{
					realres = (float)res;
					realres *= pow( 10.f , exponent_part_count );
				}
				else if( exponent_part_count > 0 )
				{
					for( int index0 = 0 ; index0 < exponent_part_count ; index0++ )
						res *= 10;
					realres = (float)res;
				}
				else
					realres = (float)res;
				if( res_float_part_count > 0 )
				{
					for( int index0 = 0 ; index0 < res_float_part_count ; index0++ )
						res_float_part *= 10;
					realres += res_float_part;
				}
				else if( res_float_part_count < 0 )
				{
					realfloatpart = (float)res_float_part;
					realfloatpart *= pow( 10.f , res_float_part_count );
				}
				realres += realfloatpart;
				if( negative )
					realres *= -1;

				return realres;
			};
			object_value::operator ::booldog::uint32() const
			{
				if( node == 0 || node->type != ::booldog::enums::data::json::number )
					return 0;
				char* ptr = node->name_or_valuebegin;
				if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_ROOT ) == 0
					&& node->parent->type == ::booldog::enums::data::json::object )
				{
					if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
					{
						for( ; ; )
						{
							switch( *++ptr )
							{
							case '\\':
								ptr++;
								break;
							case '"':
								goto goto_next0;
							}
						}
goto_next0:
						;
					}
					else
					{
						for( ; ; )
						{
							if( *++ptr == 0 )
								break;
						}
					}
					ptr += 2;
				}
				if( *ptr == '-' )
					return 0;
				::booldog::uint64 res = 0;
				int exponent_part_count = 0;
				int res_float_part_count = 0;
				::booldog::uint64 res_float_part = 0;				
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					switch( ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr ] )
					{
					case (::booldog::byte)'e':
						{
							ptr++;
							goto goto_exponent_part;
						}
					case (::booldog::byte)'.':
						{
							ptr++;
							goto goto_float;
						}
					default:
						{
							res *= 10;
							res += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
							break;
						}
					}
				}
goto_float:
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					switch( ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr ] )
					{
					case (::booldog::byte)'e':
						{
							ptr++;
							goto goto_exponent_part;
						}
					default:
						{
							res_float_part *= 10;
							res_float_part += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
							res_float_part_count--;
							break;
						}
					}
				}
goto_exponent_part:
				switch( *ptr )
				{
				case '-':
					ptr++;
					goto goto_exponent_part_minus;
				case '+':
					ptr++;
				}
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
				goto goto_return;
goto_exponent_part_minus:
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count -= ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
goto_return:
				::booldog::uint32 realres = 0;
				float realfloatpart = 0;

				res_float_part_count += exponent_part_count;
				if( exponent_part_count < 0 )
				{
					float temp = (float)res;
					temp *= pow( 10.f , exponent_part_count );
					realres = (::booldog::uint32)temp;
				}
				else if( exponent_part_count > 0 )
				{
					for( int index0 = 0 ; index0 < exponent_part_count ; index0++ )
						res *= 10;
					realres = (::booldog::uint32)res;
				}
				else
					realres = (::booldog::uint32)res;
				if( res_float_part_count > 0 )
				{
					for( int index0 = 0 ; index0 < res_float_part_count ; index0++ )
						res_float_part *= 10;
					realres = (::booldog::uint32)( realres + res_float_part );
				}
				else if( res_float_part_count < 0 )
				{
					realfloatpart = (float)res_float_part;
					realfloatpart *= pow( 10.f , res_float_part_count );
				}
				realres = (::booldog::uint32)( realres + realfloatpart );

				return realres;
			};
			object_value::operator ::booldog::uint64() const
			{
				if( node == 0 || node->type != ::booldog::enums::data::json::number )
					return 0;
				char* ptr = node->name_or_valuebegin;
				if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_ROOT ) == 0
					&& node->parent->type == ::booldog::enums::data::json::object )
				{
					if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
					{
						for( ; ; )
						{
							switch( *++ptr )
							{
							case '\\':
								ptr++;
								break;
							case '"':
								goto goto_next0;
							}
						}
goto_next0:
						;
					}
					else
					{
						for( ; ; )
						{
							if( *++ptr == 0 )
								break;
						}
					}
					ptr += 2;
				}
				if( *ptr == '-' )
					return 0;
				::booldog::uint64 res = 0;
				int exponent_part_count = 0;
				int res_float_part_count = 0;
				::booldog::uint64 res_float_part = 0;				
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					switch( ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr ] )
					{
					case (::booldog::byte)'e':
						{
							ptr++;
							goto goto_exponent_part;
						}
					case (::booldog::byte)'.':
						{
							ptr++;
							goto goto_float;
						}
					default:
						{
							res *= 10;
							res += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
							break;
						}
					}
				}
goto_float:
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					switch( ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr ] )
					{
					case (::booldog::byte)'e':
						{
							ptr++;
							goto goto_exponent_part;
						}
					default:
						{
							res_float_part *= 10;
							res_float_part += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
							res_float_part_count--;
							break;
						}
					}
				}
goto_exponent_part:
				switch( *ptr )
				{
				case '-':
					ptr++;
					goto goto_exponent_part_minus;
				case '+':
					ptr++;
				}
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
				goto goto_return;
goto_exponent_part_minus:
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count -= ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
goto_return:
				::booldog::uint64 realres = 0;
				float realfloatpart = 0;

				res_float_part_count += exponent_part_count;
				if( exponent_part_count < 0 )
				{
					float temp = (float)res;
					temp *= pow( 10.f , exponent_part_count );
					realres = (::booldog::uint64)temp;
				}
				else if( exponent_part_count > 0 )
				{
					for( int index0 = 0 ; index0 < exponent_part_count ; index0++ )
						res *= 10;
					realres = res;
				}
				else
					realres = res;
				if( res_float_part_count > 0 )
				{
					for( int index0 = 0 ; index0 < res_float_part_count ; index0++ )
						res_float_part *= 10;
					realres = realres + res_float_part;
				}
				else if( res_float_part_count < 0 )
				{
					realfloatpart = (float)res_float_part;
					realfloatpart *= pow( 10.f , res_float_part_count );
				}
				realres = (::booldog::uint64)( realres + realfloatpart );

				return realres;
			};
			object_value::operator ::booldog::int64() const
			{
				if( node == 0 || node->type != ::booldog::enums::data::json::number )
					return 0;
				char* ptr = node->name_or_valuebegin;
				if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_ROOT ) == 0
					&& node->parent->type == ::booldog::enums::data::json::object )
				{
					if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
					{
						for( ; ; )
						{
							switch( *++ptr )
							{
							case '\\':
								ptr++;
								break;
							case '"':
								goto goto_next0;
							}
						}
goto_next0:
						;
					}
					else
					{
						for( ; ; )
						{
							if( *++ptr == 0 )
								break;
						}
					}
					ptr += 2;
				}

				::booldog::uint64 res = 0;
				int exponent_part_count = 0;
				bool negative = false;
				if( *ptr == '-' )
				{
					negative = true;
					ptr++;
				}
				int res_float_part_count = 0;
				::booldog::uint64 res_float_part = 0;				
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					switch( ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr ] )
					{
					case (::booldog::byte)'e':
						{
							ptr++;
							goto goto_exponent_part;
						}
					case (::booldog::byte)'.':
						{
							ptr++;
							goto goto_float;
						}
					default:
						{
							res *= 10;
							res += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
							break;
						}
					}
				}
goto_float:
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					switch( ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr ] )
					{
					case (::booldog::byte)'e':
						{
							ptr++;
							goto goto_exponent_part;
						}
					default:
						{
							res_float_part *= 10;
							res_float_part += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
							res_float_part_count--;
							break;
						}
					}
				}
goto_exponent_part:
				switch( *ptr )
				{
				case '-':
					ptr++;
					goto goto_exponent_part_minus;
				case '+':
					ptr++;
				}
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
				goto goto_return;
goto_exponent_part_minus:
				for( ; ; )
				{
					if( ptr == node->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count -= ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
goto_return:
				::booldog::int64 realres = 0;
				float realfloatpart = 0;

				res_float_part_count += exponent_part_count;
				if( exponent_part_count < 0 )
				{
					float temp = (float)res;
					temp *= pow( 10.f , exponent_part_count );
					realres = (::booldog::int64)temp;
				}
				else if( exponent_part_count > 0 )
				{
					for( int index0 = 0 ; index0 < exponent_part_count ; index0++ )
						res *= 10;
					realres = (::booldog::int64)res;
				}
				else
					realres = (::booldog::int64)res;
				if( res_float_part_count > 0 )
				{
					for( int index0 = 0 ; index0 < res_float_part_count ; index0++ )
						res_float_part *= 10;
					realres += res_float_part;
				}
				else if( res_float_part_count < 0 )
				{
					realfloatpart = (float)res_float_part;
					realfloatpart *= pow( 10.f , res_float_part_count );
				}
				realres = (::booldog::int64)( realres + realfloatpart );
				if( negative )
					realres *= -1;

				return realres;
			};
			const char* node::json( ::booldog::data::json::serializator* parentserializator , const ::booldog::debug::info& debuginfo ) const
			{
				char* ptr = 0;
				if( child )
				{
					::booldog::data::json::node* pnext = child;
					if( type == ::booldog::enums::data::json::object )
					{
						for( ; ; )
						{
							if( pnext == 0 )
							{
								if( ptr )
								{
									if( type == ::booldog::enums::data::json::object )
										ptr[ 1 ] = '}';
									else
										ptr[ 1 ] = ']';
								}
								break;
							}
							else
							{
								if( ptr )
									ptr[ 1 ] = ',';
								int diff = 0;
								ptr = pnext->name_or_valuebegin;
								if( ::booldog::utils::get_bit( pnext->flags	, BOOLDOG_DATA_JSON_NAME_SERIALIZED ) == 0 )
								{
									for( ; ; )
									{
										switch( *++ptr )
										{
										case '"':
											{
												if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
												{
													char* oldjsonstr = parentserializator->json;
													parentserializator->jsonsize += 16;
													parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
														, parentserializator->jsonsize , debuginfo );
													//if( parentserializator->json != jsonptr )
													{
														parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
														ptr = parentserializator->json + ( ptr - oldjsonstr );
													}
												}
												::booldog::mem::insert< char >( ptr - parentserializator->json
													, parentserializator->json , parentserializator->jsonlen + 1
													, parentserializator->jsonsize , 1 , "\\\"" , 2 );
												ptr += 2;
												parentserializator->jsonlen++;
												diff++;
												break;
											}
										case '\\':
											{
												if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
												{
													char* oldjsonstr = parentserializator->json;
													parentserializator->jsonsize += 16;
													parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
														, parentserializator->jsonsize , debuginfo );
													//if( parentserializator->json != jsonptr )
													{
														parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
														ptr = parentserializator->json + ( ptr - oldjsonstr );
													}
												}
												::booldog::mem::insert< char >( ptr - parentserializator->json
													, parentserializator->json , parentserializator->jsonlen + 1
													, parentserializator->jsonsize , 1 , "\\\\" , 2 );
												ptr += 2;
												parentserializator->jsonlen++;
												diff++;
												break;
											}
										case '/':
											{
												if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
												{
													char* oldjsonstr = parentserializator->json;
													parentserializator->jsonsize += 16;
													parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
														, parentserializator->jsonsize , debuginfo );
													//if( parentserializator->json != jsonptr )
													{
														parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
														ptr = parentserializator->json + ( ptr - oldjsonstr );
													}
												}
												::booldog::mem::insert< char >( ptr - parentserializator->json
													, parentserializator->json , parentserializator->jsonlen + 1
													, parentserializator->jsonsize , 1 , "\\/" , 2 );
												ptr += 1;
												parentserializator->jsonlen++;
												diff++;
												break;
											}
										case '\b':
											{
												if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
												{
													char* oldjsonstr = parentserializator->json;
													parentserializator->jsonsize += 16;
													parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
														, parentserializator->jsonsize , debuginfo );
													//if( parentserializator->json != jsonptr )
													{
														parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
														ptr = parentserializator->json + ( ptr - oldjsonstr );
													}
												}
												::booldog::mem::insert< char >( ptr - parentserializator->json
													, parentserializator->json , parentserializator->jsonlen + 1
													, parentserializator->jsonsize , 1 , "\\b" , 2 );
												ptr += 1;
												parentserializator->jsonlen++;
												diff++;
												break;
											}
										case '\f':
											{
												if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
												{
													char* oldjsonstr = parentserializator->json;
													parentserializator->jsonsize += 16;
													parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
														, parentserializator->jsonsize , debuginfo );
													//if( parentserializator->json != jsonptr )
													{
														parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
														ptr = parentserializator->json + ( ptr - oldjsonstr );
													}
												}
												::booldog::mem::insert< char >( ptr - parentserializator->json
													, parentserializator->json , parentserializator->jsonlen + 1
													, parentserializator->jsonsize , 1 , "\\f" , 2 );
												ptr += 1;
												parentserializator->jsonlen++;
												diff++;
												break;
											}
										case '\n':
											{
												if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
												{
													char* oldjsonstr = parentserializator->json;
													parentserializator->jsonsize += 16;
													parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
														, parentserializator->jsonsize , debuginfo );
													//if( parentserializator->json != jsonptr )
													{
														parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
														ptr = parentserializator->json + ( ptr - oldjsonstr );
													}
												}
												::booldog::mem::insert< char >( ptr - parentserializator->json
													, parentserializator->json , parentserializator->jsonlen + 1
													, parentserializator->jsonsize , 1 , "\\n" , 2 );
												ptr += 1;
												parentserializator->jsonlen++;
												diff++;
												break;
											}
										case '\r':
											{
												if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
												{
													char* oldjsonstr = parentserializator->json;
													parentserializator->jsonsize += 16;
													parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
														, parentserializator->jsonsize , debuginfo );
													//if( parentserializator->json != jsonptr )
													{
														parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
														ptr = parentserializator->json + ( ptr - oldjsonstr );
													}
												}
												::booldog::mem::insert< char >( ptr - parentserializator->json
													, parentserializator->json , parentserializator->jsonlen + 1
													, parentserializator->jsonsize , 1 , "\\r" , 2 );
												ptr += 1;
												parentserializator->jsonlen++;
												diff++;
												break;
											}
										case '\t':
											{
												if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
												{
													char* oldjsonstr = parentserializator->json;
													parentserializator->jsonsize += 16;
													parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
														, parentserializator->jsonsize , debuginfo );
													//if( parentserializator->json != jsonptr )
													{
														parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
														ptr = parentserializator->json + ( ptr - oldjsonstr );
													}
												}
												::booldog::mem::insert< char >( ptr - parentserializator->json
													, parentserializator->json , parentserializator->jsonlen + 1
													, parentserializator->jsonsize , 1 , "\\t" , 2 );
												ptr += 1;
												parentserializator->jsonlen++;
												diff++;
												break;
											}
										case 0:
											{
												*ptr = '"';
												goto goto_next0;
											}
										}
									}
goto_next0:
									::booldog::utils::set_bit( pnext->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED );
								}
								else
								{
									for( ; ; )
									{
										switch( *++ptr )
										{
										case '\\':
											ptr++;
											break;
										case '"':
											goto goto_next1;
										}
									}
			goto_next1:
									;
								}
								if( pnext->type == ::booldog::enums::data::json::string )
								{
									if( ::booldog::utils::get_bit( pnext->flags	, BOOLDOG_DATA_JSON_VALUE_SERIALIZED ) == 0 )
									{
										ptr += 2;
										for( ; ; )
										{
											switch( *++ptr )
											{
											case '"':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\\"" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '\\':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\\\" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '/':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\/" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '\b':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\b" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '\f':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\f" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '\n':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\n" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '\r':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\r" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '\t':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\t" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case 0:
												{
													*ptr = '"';
													goto goto_next4;
												}
											}
										}
	goto_next4:
										::booldog::utils::set_bit( pnext->flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
									}
								}
								if( diff != 0 )
								{
									char* end = pnext->valueend;
									pnext->valueend += diff;
									parentserializator->nodes[ 0 ].offset( diff , end );
								}
								if( pnext->child )
									pnext->json( parentserializator );
								ptr = pnext->valueend;
							}
							pnext = pnext->next;
						}
					}
					else
					{
						for( ; ; )
						{
							if( pnext == 0 )
							{
								if( ptr )
								{
									if( type == ::booldog::enums::data::json::object )
										ptr[ 1 ] = '}';
									else
										ptr[ 1 ] = ']';
								}
								break;
							}
							else
							{
								if( ptr )
									ptr[ 1 ] = ',';
								int diff = 0;
								ptr = pnext->name_or_valuebegin;

								if( pnext->type == ::booldog::enums::data::json::string )
								{
									if( ::booldog::utils::get_bit( pnext->flags	, BOOLDOG_DATA_JSON_VALUE_SERIALIZED ) == 0 )
									{
										for( ; ; )
										{
											switch( *++ptr )
											{
											case '"':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\\"" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '\\':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\\\" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '/':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\/" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '\b':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\b" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '\f':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\f" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '\n':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\n" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '\r':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\r" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case '\t':
												{
													if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
													{
														char* oldjsonstr = parentserializator->json;
														parentserializator->jsonsize += 16;
														parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
															, parentserializator->jsonsize , debuginfo );
														//if( parentserializator->json != jsonptr )
														{
															parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
															ptr = parentserializator->json + ( ptr - oldjsonstr );
														}
													}
													::booldog::mem::insert< char >( ptr - parentserializator->json
														, parentserializator->json , parentserializator->jsonlen + 1
														, parentserializator->jsonsize , 1 , "\\t" , 2 );
													ptr += 1;
													parentserializator->jsonlen++;
													diff++;
													break;
												}
											case 0:
												{
													*ptr = '"';
													goto goto_next2;
												}
											}
										}
	goto_next2:
										::booldog::utils::set_bit( pnext->flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
									}
								}
								if( diff != 0 )
								{
									char* end = pnext->valueend;
									pnext->valueend += diff;
									parentserializator->nodes[ 0 ].offset( diff , end );
								}
								if( pnext->child )
									pnext->json( parentserializator );
								ptr = pnext->valueend;
							}
							pnext = pnext->next;
						}
					}
				}
				else
				{
					if( type == ::booldog::enums::data::json::string )
					{
						if( ::booldog::utils::get_bit( flags	, BOOLDOG_DATA_JSON_VALUE_SERIALIZED ) == 0 )
						{
							int diff = 0;
							ptr = name_or_valuebegin;
							for( ; ; )
							{
								switch( *++ptr )
								{
								case '"':
									{
										if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
										{
											char* oldjsonstr = parentserializator->json;
											parentserializator->jsonsize += 16;
											parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
												, parentserializator->jsonsize , debuginfo );
											//if( parentserializator->json != jsonptr )
											{
												parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
												ptr = parentserializator->json + ( ptr - oldjsonstr );
											}
										}
										::booldog::mem::insert< char >( ptr - parentserializator->json
											, parentserializator->json , parentserializator->jsonlen + 1
											, parentserializator->jsonsize , 1 , "\\\"" , 2 );
										ptr += 1;
										parentserializator->jsonlen++;
										diff++;
										break;
									}
								case '\\':
									{
										if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
										{
											char* oldjsonstr = parentserializator->json;
											parentserializator->jsonsize += 16;
											parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
												, parentserializator->jsonsize , debuginfo );
											//if( parentserializator->json != jsonptr )
											{
												parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
												ptr = parentserializator->json + ( ptr - oldjsonstr );
											}
										}
										::booldog::mem::insert< char >( ptr - parentserializator->json
											, parentserializator->json , parentserializator->jsonlen + 1
											, parentserializator->jsonsize , 1 , "\\\\" , 2 );
										ptr += 1;
										parentserializator->jsonlen++;
										diff++;
										break;
									}
								case '/':
									{
										if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
										{
											char* oldjsonstr = parentserializator->json;
											parentserializator->jsonsize += 16;
											parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
												, parentserializator->jsonsize , debuginfo );
											//if( parentserializator->json != jsonptr )
											{
												parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
												ptr = parentserializator->json + ( ptr - oldjsonstr );
											}
										}
										::booldog::mem::insert< char >( ptr - parentserializator->json
											, parentserializator->json , parentserializator->jsonlen + 1
											, parentserializator->jsonsize , 1 , "\\/" , 2 );
										ptr += 1;
										parentserializator->jsonlen++;
										diff++;
										break;
									}
								case '\b':
									{
										if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
										{
											char* oldjsonstr = parentserializator->json;
											parentserializator->jsonsize += 16;
											parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
												, parentserializator->jsonsize , debuginfo );
											//if( parentserializator->json != jsonptr )
											{
												parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
												ptr = parentserializator->json + ( ptr - oldjsonstr );
											}
										}
										::booldog::mem::insert< char >( ptr - parentserializator->json
											, parentserializator->json , parentserializator->jsonlen + 1
											, parentserializator->jsonsize , 1 , "\\b" , 2 );
										ptr += 1;
										parentserializator->jsonlen++;
										diff++;
										break;
									}
								case '\f':
									{
										if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
										{
											char* oldjsonstr = parentserializator->json;
											parentserializator->jsonsize += 16;
											parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
												, parentserializator->jsonsize , debuginfo );
											//if( parentserializator->json != jsonptr )
											{
												parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
												ptr = parentserializator->json + ( ptr - oldjsonstr );
											}
										}
										::booldog::mem::insert< char >( ptr - parentserializator->json
											, parentserializator->json , parentserializator->jsonlen + 1
											, parentserializator->jsonsize , 1 , "\\f" , 2 );
										ptr += 1;
										parentserializator->jsonlen++;
										diff++;
										break;
									}
								case '\n':
									{
										if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
										{
											char* oldjsonstr = parentserializator->json;
											parentserializator->jsonsize += 16;
											parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
												, parentserializator->jsonsize , debuginfo );
											//if( parentserializator->json != jsonptr )
											{
												parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
												ptr = parentserializator->json + ( ptr - oldjsonstr );
											}
										}
										::booldog::mem::insert< char >( ptr - parentserializator->json
											, parentserializator->json , parentserializator->jsonlen + 1
											, parentserializator->jsonsize , 1 , "\\n" , 2 );
										ptr += 1;
										parentserializator->jsonlen++;
										diff++;
										break;
									}
								case '\r':
									{
										if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
										{
											char* oldjsonstr = parentserializator->json;
											parentserializator->jsonsize += 16;
											parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
												, parentserializator->jsonsize , debuginfo );
											//if( parentserializator->json != jsonptr )
											{
												parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
												ptr = parentserializator->json + ( ptr - oldjsonstr );
											}
										}
										::booldog::mem::insert< char >( ptr - parentserializator->json
											, parentserializator->json , parentserializator->jsonlen + 1
											, parentserializator->jsonsize , 1 , "\\r" , 2 );
										ptr += 1;
										parentserializator->jsonlen++;
										diff++;
										break;
									}
								case '\t':
									{
										if( parentserializator->jsonlen + 2 > parentserializator->jsonsize )
										{
											char* oldjsonstr = parentserializator->json;
											parentserializator->jsonsize += 16;
											parentserializator->json = parentserializator->jsonallocator->realloc_array< char >( parentserializator->json
												, parentserializator->jsonsize , debuginfo );
											//if( parentserializator->json != jsonptr )
											{
												parentserializator->nodes[ 0 ].offset( oldjsonstr , parentserializator->json );
												ptr = parentserializator->json + ( ptr - oldjsonstr );
											}
										}
										::booldog::mem::insert< char >( ptr - parentserializator->json
											, parentserializator->json , parentserializator->jsonlen + 1
											, parentserializator->jsonsize , 1 , "\\t" , 2 );
										ptr += 1;
										parentserializator->jsonlen++;
										diff++;
										break;
									}
								case 0:
									{
										*ptr = '"';
										goto goto_next5;
									}
								}
							}
goto_next5:
							::booldog::data::json::node* __this = const_cast< ::booldog::data::json::node* >( this );
							::booldog::utils::set_bit( __this->flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
							if( diff != 0 )
							{
								char* end = valueend;
								__this->valueend += diff;
								parentserializator->nodes[ 0 ].offset( diff , end );
							}
						}
					}
				}

				ptr = name_or_valuebegin;
				if( ::booldog::utils::get_bit( flags	, BOOLDOG_DATA_JSON_ROOT ) == 0
					&& parent->type == ::booldog::enums::data::json::object )
				{
					if( ::booldog::utils::get_bit( flags	, BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
					{
						for( ; ; )
						{
							switch( *++ptr )
							{
							case '\\':
								ptr++;
								break;
							case '"':
								goto goto_next3;
							}
						}
goto_next3:
						;
					}
					else
					{
						for( ; ; )
						{
							if( *++ptr == 0 )
								break;
						}
					}
					ptr += 2;
				}
				valueend[ 1 ] = 0;
				return ptr;
			};
			object_json::operator const char*() const
			{
				if( node == 0 )
					return 0;
				::booldog::data::json::serializator* parentserializator = 0;
				if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_ROOT ) )
					parentserializator = node->serializator;
				else
				{
					::booldog::data::json::node* pparent = node->parent;						
					for( ; ; )
					{
						if( ::booldog::utils::get_bit( pparent->flags	, BOOLDOG_DATA_JSON_ROOT ) )
						{
							parentserializator = pparent->serializator;
							break;
						}
						pparent = pparent->parent;
					}
				}
				return node->json( parentserializator );
			};
			object_value::operator const char*() const
			{
				if( node == 0 || node->type != ::booldog::enums::data::json::string )
					return 0;
				char* ptr = node->name_or_valuebegin;
				if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_ROOT ) == 0
					&& node->parent->type == ::booldog::enums::data::json::object )
				{
					if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
					{
						for( ; ; )
						{
							switch( *++ptr )
							{
							case '\\':
								ptr++;
								break;
							case '"':
								goto goto_next0;
							}
						}
goto_next0:
						;
					}
					else
					{
						for( ; ; )
						{
							if( *++ptr == 0 )
								break;
						}
					}
					ptr += 3;
				}
				else
					ptr++;
				if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_VALUE_SERIALIZED ) )
				{
					::booldog::data::json::serializator* parentserializator = 0;
					if( ::booldog::utils::get_bit( node->flags	, BOOLDOG_DATA_JSON_ROOT ) )
						parentserializator = node->serializator;
					else
					{
						::booldog::data::json::node* pparent = node->parent;						
						for( ; ; )
						{
							if( ::booldog::utils::get_bit( pparent->flags	, BOOLDOG_DATA_JSON_ROOT ) )
							{
								parentserializator = pparent->serializator;
								break;
							}
							pparent = pparent->parent;
						}
					}
					char* begin = ptr;
					int diff = 0;
					for( ; ; )
					{
						if( *ptr == '"' )
						{
							*ptr = 0;
							break;
						}
						switch( *ptr++ )
						{
						case '\\':
							{
								switch( *ptr )
								{
								case '"':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json												, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\"" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case '\\':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json												, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\\" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case '/':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json												, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "/" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case 'b':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json												, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\b" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case 'f':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json												, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\f" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case 'n':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json												, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\n" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case 'r':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json												, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\r" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case 't':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json												, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\t" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								}
							}
						}
					}
					char* end = node->valueend;
					node->valueend += diff;
					if( diff != 0 )
						parentserializator->nodes[ 0 ].offset( diff , end );
					::booldog::utils::unset_bit( node->flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
					return begin;
				}
				return ptr;
			};
			const char* object_value::name( void ) const
			{
				return node ? node->name() : 0;
			};
			const char* node::name( void ) const
			{
				if( ::booldog::utils::get_bit( flags	, BOOLDOG_DATA_JSON_ROOT )
					|| parent->type != ::booldog::enums::data::json::object )
					return 0;
				if( ::booldog::utils::get_bit( flags	, BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
				{
					::booldog::data::json::serializator* parentserializator = 0;
					if( ::booldog::utils::get_bit( flags	, BOOLDOG_DATA_JSON_ROOT ) )
						parentserializator = serializator;
					else
					{
						::booldog::data::json::node* pparent = this->parent;						
						for( ; ; )
						{
							if( ::booldog::utils::get_bit( pparent->flags	, BOOLDOG_DATA_JSON_ROOT ) )
							{
								parentserializator = pparent->serializator;
								break;
							}
							pparent = pparent->parent;
						}
					}
				
					int diff = 0;
					char* ptr = name_or_valuebegin;
					for( ; ; )
					{
						if( *ptr == '"' )
						{
							*ptr = 0;
							break;
						}
						switch( *ptr++ )
						{
						case '\\':
							{
								switch( *ptr )
								{
								case '"':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json 
											, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\"" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case '\\':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json 
											, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\\" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case '/':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json 
											, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "/" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case 'b':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json 
											, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\b" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case 'f':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json 
											, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\f" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case 'n':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json 
											, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\n" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case 'r':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json 
											, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\r" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								case 't':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->json - 1 , parentserializator->json 
											, parentserializator->jsonlen + 1 , parentserializator->jsonsize , 2 , "\t" , 1 );
										parentserializator->jsonlen--;
										diff--;
										break;
									}
								}
							}
						}
					}
					char* end = valueend;
					const_cast< ::booldog::data::json::node* >( this )->valueend += diff;
					if( diff != 0 )
						parentserializator->nodes[ 0 ].offset( diff , end );
					::booldog::utils::unset_bit( flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED );
				}
				return name_or_valuebegin;
			};
			class result : public ::booldog::result
			{
			private:
				result( const ::booldog::result& )
					: serializator( 0 )
				{
				};
				result( const ::booldog::data::json::result& )
					: serializator( 0 )
				{
				};
				::booldog::data::json::result& operator = ( const ::booldog::data::json::result& )
				{
					return *this;
				};
			public:
				::booldog::data::json::serializator* serializator;
				result( ::booldog::data::json::serializator* pserializator )
 					: serializator( pserializator ) , ::booldog::result()
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
					_obj_->serializator->jsonlen = 0;
					_obj_->serializator->nodesindex = 0;
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
			booinline bool parse( ::booldog::data::json::result* pres , booldog::allocator* allocator , const char* js 
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::data::json::serializator serializator( allocator );
				::booldog::data::json::result locres( &serializator );
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
					res->serializator->jsonlen = size - 1;
					if( size > res->serializator->jsonsize )
					{
						res->serializator->jsonsize = size;
						res->serializator->json = res->serializator->jsonallocator->realloc_array< char >( res->serializator->json , res->serializator->jsonsize
							, debuginfo );
					}
					if( res->serializator->json )
					{
						::memcpy( res->serializator->json , js , res->serializator->jsonlen );
						res->serializator->json[ res->serializator->jsonlen ] = 0;
					}
					else
					{
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						goto goto_return;
					}

					::booldog::data::json::node* node = 0 , * curnode = 0 , * parentnode = 0;
					
					ptr = res->serializator->json;		
					const char* begin = 0 , * name_begin = 0;
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
						::booldog::mem::remove< char >( (size_t)( begin - res->serializator->json ) , res->serializator->json , res->serializator->jsonsize
							, size );
						res->serializator->jsonlen -= size;
						res->serializator->json[ res->serializator->jsonlen ] = 0;
						ptr = begin;
					}

					switch( *ptr )
					{
					case '[':
						{
							if( res->serializator->nodesindex >= res->serializator->nodessize )
							{
								res->serializator->nodessize += step;
								char* nodesptr = (char*)res->serializator->nodes;
								res->serializator->nodes = res->serializator->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->serializator->nodes , res->serializator->nodessize , debuginfo );
								if( res->serializator->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->serializator->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->serializator->nodesindex ; index0++ )
									{
										if( res->serializator->nodes[ index0 ].next )
										{
											size = ((char*)res->serializator->nodes[ index0 ].next) - nodesptr;
											res->serializator->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( ::booldog::utils::get_bit( res->serializator->nodes[ index0 ].flags
											, BOOLDOG_DATA_JSON_ROOT ) == 0 )
										{
											size = ((char*)res->serializator->nodes[ index0 ].parent) - nodesptr;
											res->serializator->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( res->serializator->nodes[ index0 ].child )
										{
											size = ((char*)res->serializator->nodes[ index0 ].child) - nodesptr;
											res->serializator->nodes[ index0 ].child = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
									}
								}
							}
							node = &res->serializator->nodes[ res->serializator->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::array;
							node->name_or_valuebegin = (char*)name_begin;
							node->namehash = name_hash;
							node->flags = 0;
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED );
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
							if( res->serializator->nodesindex == 1 )
							{
								::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_ROOT );
								node->serializator = res->serializator;
							}
							else
								node->parent = parentnode;
							name_begin = 0 , name_hash = 0;
							if( node->name_or_valuebegin == 0 )
								node->name_or_valuebegin = (char*)ptr;
							node->valueend = 0;
							node->next = 0;
							node->child = 0;
							
							if( curnode )
							{
								curnode->next = node;
								curnode = 0;
							}
							if( parentnode && parentnode->child == 0 )
								parentnode->child = node;
							parentnode = node;

							ptr++;
							goto goto_comma_parse;
						}
					case '{':
						{
							if( res->serializator->nodesindex >= res->serializator->nodessize )
							{
								res->serializator->nodessize += step;
								char* nodesptr = (char*)res->serializator->nodes;
								res->serializator->nodes = res->serializator->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->serializator->nodes , res->serializator->nodessize , debuginfo );
								if( res->serializator->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->serializator->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->serializator->nodesindex ; index0++ )
									{
										if( res->serializator->nodes[ index0 ].next )
										{
											size = ((char*)res->serializator->nodes[ index0 ].next) - nodesptr;
											res->serializator->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( ::booldog::utils::get_bit( res->serializator->nodes[ index0 ].flags
											, BOOLDOG_DATA_JSON_ROOT ) == 0 )
										{
											size = ((char*)res->serializator->nodes[ index0 ].parent) - nodesptr;
											res->serializator->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( res->serializator->nodes[ index0 ].child )
										{
											size = ((char*)res->serializator->nodes[ index0 ].child) - nodesptr;
											res->serializator->nodes[ index0 ].child = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
									}
								}
							}
							node = &res->serializator->nodes[ res->serializator->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::object;
							node->name_or_valuebegin = (char*)name_begin;
							node->namehash = name_hash;
							node->flags = 0;
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED );
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
							if( res->serializator->nodesindex == 1 )
							{
								::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_ROOT );
								node->serializator = res->serializator;
							}
							else
								node->parent = parentnode;
							name_begin = 0 , name_hash = 0;
							if( node->name_or_valuebegin == 0 )
								node->name_or_valuebegin = (char*)ptr;
							node->valueend = 0;
							node->next = 0;
							node->child = 0;
							
							if( curnode )
							{
								curnode->next = node;
								curnode = 0;
							}
							if( parentnode && parentnode->child == 0 )
								parentnode->child = node;
							parentnode = node;

							ptr++;
							goto goto_object_name_parse;
						}
					case '"':
						{
							const char* string_begin = ptr;
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
													::booldog::mem::insert< char >( begin - res->serializator->json , res->serializator->json 
														, res->serializator->jsonlen + 1 , res->serializator->jsonsize
														, size , utf8 , utf8bytes );
													res->serializator->jsonlen -= size - utf8bytes;
													res->serializator->json[ res->serializator->jsonlen ] = 0;
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
							if( res->serializator->nodesindex >= res->serializator->nodessize )
							{
								res->serializator->nodessize += step;
								char* nodesptr = (char*)res->serializator->nodes;
								res->serializator->nodes = res->serializator->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->serializator->nodes , res->serializator->nodessize , debuginfo );
								if( res->serializator->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->serializator->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->serializator->nodesindex ; index0++ )
									{
										if( res->serializator->nodes[ index0 ].next )
										{
											size = ((char*)res->serializator->nodes[ index0 ].next) - nodesptr;
											res->serializator->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( ::booldog::utils::get_bit( res->serializator->nodes[ index0 ].flags
											, BOOLDOG_DATA_JSON_ROOT ) == 0 )
										{
											size = ((char*)res->serializator->nodes[ index0 ].parent) - nodesptr;
											res->serializator->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( res->serializator->nodes[ index0 ].child )
										{
											size = ((char*)res->serializator->nodes[ index0 ].child) - nodesptr;
											res->serializator->nodes[ index0 ].child = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
									}
								}
							}
							node = &res->serializator->nodes[ res->serializator->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::string;
							node->name_or_valuebegin = (char*)name_begin;
							node->namehash = name_hash;
							node->flags = 0;
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED );
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
							if( res->serializator->nodesindex == 1 )
							{
								::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_ROOT );
								node->serializator = res->serializator;
							}
							else
								node->parent = parentnode;
							name_begin = 0 , name_hash = 0;
							if( node->name_or_valuebegin == 0 )
								node->name_or_valuebegin = (char*)string_begin;
							node->valueend = (char*)ptr - 1;
							node->next = 0;
							node->child = 0;
							
							if( curnode )
								curnode->next = node;
							curnode = node;
							if( parentnode )
							{
								if( parentnode->child == 0 )
									parentnode->child = node;
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


							if( res->serializator->nodesindex >= res->serializator->nodessize )
							{
								res->serializator->nodessize += step;
								char* nodesptr = (char*)res->serializator->nodes;
								res->serializator->nodes = res->serializator->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->serializator->nodes , res->serializator->nodessize , debuginfo );
								if( res->serializator->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->serializator->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->serializator->nodesindex ; index0++ )
									{
										if( res->serializator->nodes[ index0 ].next )
										{
											size = ((char*)res->serializator->nodes[ index0 ].next) - nodesptr;
											res->serializator->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( ::booldog::utils::get_bit( res->serializator->nodes[ index0 ].flags
											, BOOLDOG_DATA_JSON_ROOT ) == 0 )
										{
											size = ((char*)res->serializator->nodes[ index0 ].parent) - nodesptr;
											res->serializator->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( res->serializator->nodes[ index0 ].child )
										{
											size = ((char*)res->serializator->nodes[ index0 ].child) - nodesptr;
											res->serializator->nodes[ index0 ].child = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
									}
								}
							}
							node = &res->serializator->nodes[ res->serializator->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::boolean_false;
							node->name_or_valuebegin = (char*)name_begin;
							node->namehash = name_hash;
							node->flags = 0;
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED );
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
							if( res->serializator->nodesindex == 1 )
							{
								::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_ROOT );
								node->serializator = res->serializator;
							}
							else
								node->parent = parentnode;
							name_begin = 0 , name_hash = 0;
							if( node->name_or_valuebegin == 0 )
								node->name_or_valuebegin = (char*)( ptr - 4 );
							node->valueend = (char*)ptr;
							node->next = 0;
							node->child = 0;
							
							if( curnode )
								curnode->next = node;
							curnode = node;
							if( parentnode )
							{
								if( parentnode->child == 0 )
									parentnode->child = node;
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


							if( res->serializator->nodesindex >= res->serializator->nodessize )
							{
								res->serializator->nodessize += step;
								char* nodesptr = (char*)res->serializator->nodes;
								res->serializator->nodes = res->serializator->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->serializator->nodes , res->serializator->nodessize , debuginfo );
								if( res->serializator->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->serializator->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->serializator->nodesindex ; index0++ )
									{
										if( res->serializator->nodes[ index0 ].next )
										{
											size = ((char*)res->serializator->nodes[ index0 ].next) - nodesptr;
											res->serializator->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( ::booldog::utils::get_bit( res->serializator->nodes[ index0 ].flags
											, BOOLDOG_DATA_JSON_ROOT ) == 0 )
										{
											size = ((char*)res->serializator->nodes[ index0 ].parent) - nodesptr;
											res->serializator->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( res->serializator->nodes[ index0 ].child )
										{
											size = ((char*)res->serializator->nodes[ index0 ].child) - nodesptr;
											res->serializator->nodes[ index0 ].child = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
									}
								}
							}
							node = &res->serializator->nodes[ res->serializator->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::boolean_true;
							node->name_or_valuebegin = (char*)name_begin;
							node->namehash = name_hash;
							node->flags = 0;
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED );
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
							if( res->serializator->nodesindex == 1 )
							{
								::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_ROOT );
								node->serializator = res->serializator;
							}
							else
								node->parent = parentnode;
							name_begin = 0 , name_hash = 0;
							if( node->name_or_valuebegin == 0 )
								node->name_or_valuebegin = (char*)( ptr - 3 );
							node->valueend = (char*)ptr;
							node->next = 0;
							node->child = 0;
							
							if( curnode )
								curnode->next = node;
							curnode = node;
							if( parentnode )
							{
								if( parentnode->child == 0 )
									parentnode->child = node;
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


							if( res->serializator->nodesindex >= res->serializator->nodessize )
							{
								res->serializator->nodessize += step;
								char* nodesptr = (char*)res->serializator->nodes;
								res->serializator->nodes = res->serializator->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->serializator->nodes , res->serializator->nodessize , debuginfo );
								if( res->serializator->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->serializator->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->serializator->nodesindex ; index0++ )
									{
										if( res->serializator->nodes[ index0 ].next )
										{
											size = ((char*)res->serializator->nodes[ index0 ].next) - nodesptr;
											res->serializator->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( ::booldog::utils::get_bit( res->serializator->nodes[ index0 ].flags
											, BOOLDOG_DATA_JSON_ROOT ) == 0 )
										{
											size = ((char*)res->serializator->nodes[ index0 ].parent) - nodesptr;
											res->serializator->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( res->serializator->nodes[ index0 ].child )
										{
											size = ((char*)res->serializator->nodes[ index0 ].child) - nodesptr;
											res->serializator->nodes[ index0 ].child = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
									}
								}
							}
							node = &res->serializator->nodes[ res->serializator->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::null;
							node->name_or_valuebegin = (char*)name_begin;
							node->namehash = name_hash;
							node->flags = 0;
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED );
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
							if( res->serializator->nodesindex == 1 )
							{
								::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_ROOT );
								node->serializator = res->serializator;
							}
							else
								node->parent = parentnode;
							name_begin = 0 , name_hash = 0;
							if( node->name_or_valuebegin == 0 )
								node->name_or_valuebegin = (char*)( ptr - 3 );
							node->valueend = (char*)ptr;
							node->next = 0;
							node->child = 0;
							
							if( curnode )
								curnode->next = node;
							curnode = node;
							if( parentnode )
							{
								if( parentnode->child == 0 )
									parentnode->child = node;
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
							const char* number_string_begin = ptr;
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
										if( number_string_begin == ptr - 1 )
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
										if( number_string_begin == ptr - 1 )
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
							number_string_begin = ptr;
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
										if( number_string_begin == ptr - 1 )
										{
											res->booerr( ::booldog::enums::result::booerr_type_json_expecting_digit_after_exponent_part_symbol );
											goto goto_return;
										}
										goto goto_number_create;
									}
								}
							}
goto_number_create:
							if( res->serializator->nodesindex >= res->serializator->nodessize )
							{
								res->serializator->nodessize += step;
								char* nodesptr = (char*)res->serializator->nodes;
								res->serializator->nodes = res->serializator->jsonallocator->realloc_array< ::booldog::data::json::node >( 
									res->serializator->nodes , res->serializator->nodessize , debuginfo );
								if( res->serializator->nodes == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
								if( (char*)res->serializator->nodes != nodesptr )
								{
									if( curnode )
									{
										size = ((char*)curnode) - nodesptr;
										curnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									if( parentnode )
									{
										size = ((char*)parentnode) - nodesptr;
										parentnode = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
									}
									for( size_t index0 = 0 ; index0 < res->serializator->nodesindex ; index0++ )
									{
										if( res->serializator->nodes[ index0 ].next )
										{
											size = ((char*)res->serializator->nodes[ index0 ].next) - nodesptr;
											res->serializator->nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( ::booldog::utils::get_bit( res->serializator->nodes[ index0 ].flags
											, BOOLDOG_DATA_JSON_ROOT ) == 0 )
										{
											size = ((char*)res->serializator->nodes[ index0 ].parent) - nodesptr;
											res->serializator->nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
										if( res->serializator->nodes[ index0 ].child )
										{
											size = ((char*)res->serializator->nodes[ index0 ].child) - nodesptr;
											res->serializator->nodes[ index0 ].child = (::booldog::data::json::node*)(((char*)res->serializator->nodes) + size);
										}
									}
								}
							}
							node = &res->serializator->nodes[ res->serializator->nodesindex++ ];
														
							node->type = ::booldog::enums::data::json::number;
							node->name_or_valuebegin = (char*)name_begin;
							node->namehash = name_hash;
							node->flags = 0;
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED );
							::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
							if( res->serializator->nodesindex == 1 )
							{
								::booldog::utils::set_bit( node->flags , BOOLDOG_DATA_JSON_ROOT );
								node->serializator = res->serializator;
							}
							else
								node->parent = parentnode;
							name_begin = 0 , name_hash = 0;
							if( node->name_or_valuebegin == 0 )
								node->name_or_valuebegin = (char*)begin;
							node->valueend = (char*)ptr - 1;
							node->next = 0;
							node->child = 0;
							
							if( curnode )
								curnode->next = node;
							curnode = node;
							if( parentnode )
							{
								if( parentnode->child == 0 )
									parentnode->child = node;
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
						::booldog::mem::remove< char >( (size_t)( begin - res->serializator->json ) , res->serializator->json , res->serializator->jsonsize
							, size );
						res->serializator->jsonlen -= size;
						res->serializator->json[ res->serializator->jsonlen ] = 0;
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
								if( ::booldog::utils::get_bit( parentnode->flags , BOOLDOG_DATA_JSON_ROOT ) == 0 )
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
								if( parentnode->child )
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
								if( ::booldog::utils::get_bit( parentnode->flags , BOOLDOG_DATA_JSON_ROOT ) == 0 )
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
								if( parentnode->child == 0 )
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
						::booldog::mem::remove< char >( (size_t)( begin - res->serializator->json ) , res->serializator->json , res->serializator->jsonsize
							, size );
						res->serializator->jsonlen -= size;
						res->serializator->json[ res->serializator->jsonlen ] = 0;
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
							if( ::booldog::utils::get_bit( parentnode->flags , BOOLDOG_DATA_JSON_ROOT ) == 0 )
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
											::booldog::mem::insert< char >( begin - res->serializator->json , res->serializator->json 
												, res->serializator->jsonlen + 1 , res->serializator->jsonsize
												, size , utf8 , utf8bytes );
											res->serializator->jsonlen -= size - utf8bytes;
											res->serializator->json[ res->serializator->jsonlen ] = 0;
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
						::booldog::mem::remove< char >( (size_t)( begin - res->serializator->json ) , res->serializator->json , res->serializator->jsonsize
							, size );
						res->serializator->jsonlen -= size;
						res->serializator->json[ res->serializator->jsonlen ] = 0;
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
						::booldog::mem::remove< char >( (size_t)( begin - res->serializator->json ) , res->serializator->json , res->serializator->jsonsize
							, size );
						res->serializator->jsonlen -= size;
						res->serializator->json[ res->serializator->jsonlen ] = 0;
					}
				}
				else
					res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
goto_return:
				if( res->succeeded() )
					return true;
				else
				{
					res->serializator->json[ 0 ] = 0;
					res->serializator->jsonlen = 0;
					res->serializator->nodesindex = 0;
					return false;
				}
			};
		};
	};
};
#endif