#ifndef BOO_JSON_H
#define BOO_JSON_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_param.h)
#include BOOLDOG_HEADER(boo_allocator.h)
#include BOOLDOG_HEADER(boo_utf16.h)
#include BOOLDOG_HEADER(boo_utf8.h)
#include BOOLDOG_HEADER(boo_utils.h)
#include BOOLDOG_HEADER(boo_mem.h)
#include BOOLDOG_HEADER(boo_result.h)
#include BOOLDOG_HEADER(boo_bits_utils.h)

#include <math.h>
namespace booldog
{
	namespace consts
	{
		namespace data
		{
			namespace json
			{
				const char _to_serialize_chars[ 256 ] = 
				{
					0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 8 , 9 , 10 , 1 , 12 , 13 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
					1 , 1 , 34 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 47 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
					1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 92 , 1 , 1 , 1 ,
					1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
					1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
					1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
					1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
					1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
				};
			};
		};
	};
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
					object = 6
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
#define BOOLDOG_DATA_JSON_NODE_FREE 3
			struct node;
			struct serializator;		

			struct object_json
			{
				::booldog::data::json::node* nodes;
				::booldog::data::json::serializator* parentserializator;
				::booldog::data::json::node* node;
				booinline operator const char*();
			};

			struct object_value
			{
				::booldog::data::json::node* nodes;
				::booldog::data::json::serializator* parentserializator;
				::booldog::data::json::node* node;
				booinline operator float();
				booinline operator const char*();
				booinline operator ::booldog::int32();
				booinline operator ::booldog::int64();
				booinline operator ::booldog::uint32();
				booinline operator ::booldog::uint64();
				booinline operator bool();
				booinline ::booldog::uint64 namehash( void );
				booinline const char* name( void );
				booinline bool name( ::booldog::result* pres , const char* newname
					, const ::booldog::debug::info& debuginfo = debuginfo_macros );
				booinline ::booldog::data::json::object_value& operator = ( const char* value );
				booinline ::booldog::data::json::object_value& operator = ( ::booldog::int32 value );
				booinline ::booldog::data::json::object_value& operator = ( ::booldog::int64 value );
				booinline ::booldog::data::json::object_value& operator = ( ::booldog::uint32 value );
				booinline ::booldog::data::json::object_value& operator = ( ::booldog::uint64 value );
				booinline ::booldog::data::json::object_value& operator = ( bool value );
			};

			template< class T >
			booinline void checknode( T* nodeholder );

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
				booinline const char* name( void ) const;
				booinline bool name( ::booldog::result* pres , const char* newname
					, const ::booldog::debug::info& debuginfo = debuginfo_macros ) const;
				booinline void jsonoffset( int diff , char* pvalueend )
				{
					::booldog::data::json::node* pnext = child;
					for( ; ; )
					{
						if( pnext )
						{
							pnext->jsonoffset( diff , pvalueend );
							if( pnext->name_or_valuebegin > pvalueend )
								pnext->name_or_valuebegin += diff;
							if( pnext->valueend >= pvalueend )
								pnext->valueend += diff;
						}
						else
							break;
						pnext = pnext->next;
					}
				};
				booinline void newjsonptr( char* oldjsonstr , char* jsonstr )
				{
					::booldog::data::json::node* pnext = child;
					for( ; ; )
					{
						if( pnext )
						{
							pnext->newjsonptr( oldjsonstr , jsonstr );
							pnext->name_or_valuebegin = jsonstr + ( pnext->name_or_valuebegin - oldjsonstr );
							pnext->valueend = jsonstr + ( pnext->valueend - oldjsonstr );
						}
						else
							break;
						pnext = pnext->next;
					}
				};
				booinline const char* json( ::booldog::data::json::serializator* parentserializator 
					, const ::booldog::debug::info& debuginfo = debuginfo_macros ) const;
				template< size_t step , class T >
				booinline bool set( ::booldog::result* pres , char* valuebegin , T value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros );
				template< size_t step >
				booinline bool set( ::booldog::result* pres , char* valuebegin , bool value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros );
				template< size_t step >
				booinline bool set( ::booldog::result* pres , char* valuebegin , const char* value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros );
				booinline operator float();
				booinline operator const char*();
				booinline operator ::booldog::int32();
				booinline operator ::booldog::int64();
				booinline operator ::booldog::uint32();
				booinline operator ::booldog::uint64();
				booinline operator bool();
				booinline bool isstring( void );
				booinline bool isnumber( void );
				booinline bool isnegativenumber( void );
				booinline bool isnull( void );
				booinline bool isboolean( void );
				booinline bool isobject( void );
				booinline bool isarray( void );
				booinline size_t count( void );
			};

			template< size_t step >
			booinline ::booldog::data::json::node* newnode( ::booldog::result* res 
				, ::booldog::data::json::serializator* serializer , ::booldog::data::json::node*& curnode
				, const ::booldog::debug::info& debuginfo );
			template< size_t step >
			booinline ::booldog::data::json::node* newnode( ::booldog::result* res 
				, ::booldog::data::json::serializator* serializer , ::booldog::data::json::node*& curnode 
				, ::booldog::data::json::node*& parentnode , size_t& size , const ::booldog::debug::info& debuginfo );

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
				booinline object( ::booldog::data::json::node* srcnode );
				booinline ::booldog::data::json::object operator[]( size_t index );
				booinline ::booldog::data::json::object operator()( const char* utf8name );
				booinline ::booldog::data::json::object operator()( ::booldog::uint64 utf8namehash );
				booinline ::booldog::data::json::object operator++(int);
				booinline ::booldog::data::json::object& operator++();
				booinline ::booldog::uint64 namehash( void )
				{
					return value.namehash();
				};
				booinline const char* name( void )
				{
					return value.name();
				};
				booinline bool name( ::booldog::result* pres , const char* newname
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					return value.name( pres , newname , debuginfo );
				};
				template< size_t step >
				booinline ::booldog::data::json::object add( ::booldog::result* pres , const char* name , bool value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros );
				booinline bool exists( void )
				{
					return json.node != 0;
				};
				booinline bool isstring( void );
				booinline bool isnumber( void );
				booinline bool isnegativenumber( void );
				booinline bool isnull( void );
				booinline bool isboolean( void );
				booinline bool isobject( void );
				booinline bool isarray( void );
				booinline size_t count( void );
			};
			struct serializator_slow
			{
				char* json;
				size_t jsonsize;
				size_t jsonlen;
				booldog::allocator* jsonallocator;
				size_t nodessize;
				size_t nodesindex;
				::booldog::data::json::node* nodes;
			};
			struct serializator_fast
			{
				booinline char* detach(void)
				{
					char* res = json;
					json = 0;
					if(nodes)
					{
						jsonallocator->free(nodes);
						nodes = 0;
					}
					clear();
					return res;
				};
				booinline void clear( void )
				{
					if( json )
						json[ 0 ] = 0;
					else
						jsonsize = 0;
					jsonlen = 0;
					nodesindex = 0;
					if( nodes == 0 )
						nodessize = 0;
					for( size_t index0 = 0 ; index0 < nodessize ; index0++ )
						nodes[ index0 ].flags = ::booldog::utils::bits::compile::number_from_bit_index< 
						::booldog::byte , BOOLDOG_DATA_JSON_NODE_FREE >::value;
				};
			private:
				template< size_t step >
				bool serialize_and_add( ::booldog::result* pres , const char* string
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					debuginfo_macros_statement( 343 );

					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					const ::booldog::byte* ptrbyte = (::booldog::byte*)string , * to_serialize_chars = 0;
					size_t size = 0 , length = 0 , to_serialize_chars_count = 0;
					for( ; ; )
					{
						switch( ::booldog::consts::data::json::_to_serialize_chars[ *ptrbyte ] )
						{
						case 0:
							++ptrbyte;
							goto goto_next;
						case 1:
							{
								if( ::booldog::utf8::validate_character( ptrbyte ) == false )
								{
									clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								break;
							}
						default:
							{
								if( to_serialize_chars == 0 )
									to_serialize_chars = ptrbyte;
								to_serialize_chars_count++;
								++ptrbyte;
								break;
							}
						}
					}
goto_next:
					debuginfo_macros_statement( 346 );
					length = ( ((const char*)ptrbyte) - string - 1 );
					size = 2 + 2 * length;
					if( jsonlen + size + 1 > jsonsize )
					{
						jsonsize += size + 1 + step;
						json = jsonallocator->realloc_array< char >( json
							, jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					ptrbyte = (::booldog::byte*)string;

					

					json[ jsonlen++ ] = '"';
					if( to_serialize_chars_count )
					{
						debuginfo_macros_statement( 347 );

						if( to_serialize_chars != ptrbyte )
						{
							size = ((const char*)to_serialize_chars) - string;
							::memcpy( &json[ jsonlen ] , string , size );
							jsonlen += size;
							ptrbyte = to_serialize_chars;
						}
						for( ; to_serialize_chars_count ; )
						{
							switch( ::booldog::consts::data::json::_to_serialize_chars[ *ptrbyte ] )
							{
							case 1:
								{
									json[ jsonlen++ ] = (char)*ptrbyte;
									break;
								}
							case 0:
								goto goto_next0;
							case '"':
								{
									const char* fast = "\\\"";
									*(::booldog::uint16*)&json[ jsonlen ] = *(::booldog::uint16*)fast;
									jsonlen += 2;
									to_serialize_chars_count--;
									break;
								}
							case '\\':
								{
									const char* fast = "\\\\";
									*(::booldog::uint16*)&json[ jsonlen ] = *(::booldog::uint16*)fast;
									jsonlen += 2;
									to_serialize_chars_count--;
									break;
								}
							case '/':
								{
									const char* fast = "\\/";
									*(::booldog::uint16*)&json[ jsonlen ] = *(::booldog::uint16*)fast;
									jsonlen += 2;
									to_serialize_chars_count--;
									break;
								}
							case '\b':
								{
									const char* fast = "\\b";
									*(::booldog::uint16*)&json[ jsonlen ] = *(::booldog::uint16*)fast;
									jsonlen += 2;
									to_serialize_chars_count--;
									break;
								}
							case '\f':
								{
									const char* fast = "\\f";
									*(::booldog::uint16*)&json[ jsonlen ] = *(::booldog::uint16*)fast;
									jsonlen += 2;
									to_serialize_chars_count--;
									break;
								}
							case '\n':
								{
									const char* fast = "\\n";
									*(::booldog::uint16*)&json[ jsonlen ] = *(::booldog::uint16*)fast;
									jsonlen += 2;
									to_serialize_chars_count--;
									break;
								}
							case '\r':
								{
									const char* fast = "\\r";
									*(::booldog::uint16*)&json[ jsonlen ] = *(::booldog::uint16*)fast;
									jsonlen += 2;
									to_serialize_chars_count--;
									break;
								}
							case '\t':
								{
									const char* fast = "\\t";
									*(::booldog::uint16*)&json[ jsonlen ] = *(::booldog::uint16*)fast;
									jsonlen += 2;
									to_serialize_chars_count--;
									break;
								}
							}
							++ptrbyte;
						}
						if( *ptrbyte != 0 )
						{
							length -= ((const char*)ptrbyte) - string;
							::memcpy( &json[ jsonlen ] , ptrbyte , length );
							jsonlen += length;
						}
					}
					else
					{
						debuginfo_macros_statement( 348 );

						::memcpy( &json[ jsonlen ] , string , length );
						jsonlen += length;
					}
goto_next0:
					json[ jsonlen ] = '"';
					json[ ++jsonlen ] = 0;
goto_return:
					return res->succeeded();
				};
			public:
				char* json;
				size_t jsonsize;
				size_t jsonlen;
				::booldog::allocator* jsonallocator;
				size_t nodessize;
				size_t nodesindex;
				::booldog::data::json::node* nodes;
				template< size_t step >
				booinline bool begin_object( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}
					if( jsonlen + 3 > jsonsize )
					{
						jsonsize += 3 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					if( jsonlen )
					{
						char letter = json[ jsonlen - 1 ];
						if( letter != '[' && letter != '{' )
							json[ jsonlen++ ] = ',';
					}
					json[ jsonlen++ ] = '{';
					json[ jsonlen ] = 0;
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool add( ::booldog::result* pres , const char* value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}
					if( jsonlen + 2 > jsonsize )
					{
						jsonsize += 2 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					if( jsonlen )
					{
						char letter = json[ jsonlen - 1 ];
						if( letter != '[' && letter != '{' )
							json[ jsonlen++ ] = ',';
					}
					if( serialize_and_add< step >( res , value , debuginfo ) == false )
						goto goto_return;
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool add( ::booldog::result* pres , char* value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					return add< step >( pres , const_cast< const char* >( value ) , debuginfo );
				};
				template< size_t step >
				booinline bool add( ::booldog::result* pres , const char* name , const char* value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}
					if( jsonlen + 2 > jsonsize )
					{
						jsonsize += 2 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					if( jsonlen )
					{
						char letter = json[ jsonlen - 1 ];
						if( letter != '[' && letter != '{' )
							json[ jsonlen++ ] = ',';
					}
					if( serialize_and_add< step >( res , name , debuginfo ) == false )
						goto goto_return;
					if( jsonlen + 2 > jsonsize )
					{
						jsonsize += 2 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					json[ jsonlen++ ] = ':';
					if( serialize_and_add< step >( res , value , debuginfo ) == false )
						goto goto_return;
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool add( ::booldog::result* pres , char* name , char* value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					return add< step >( pres , const_cast< const char* >( name ) , const_cast< const char* >( value ) , debuginfo );
				};
				template< size_t step >
				booinline bool add( ::booldog::result* pres , const char* name , char* value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					return add< step >( pres , name , const_cast< const char* >( value ) , debuginfo );
				};
				template< size_t step >
				booinline bool add( ::booldog::result* pres , char* name , const char* value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					return add< step >( pres , const_cast< const char* >( name ) , value , debuginfo );
				};
				template< size_t step , class T >
				booinline bool add( ::booldog::result* pres , T value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );

					char* ptr = 0 , * begin = 0;
					size_t count_of_digits = 0;
					T locnumber = value;
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}
					if( locnumber == 0 )
					{
						if( jsonlen + 3 > jsonsize )
						{
							jsonsize += 3 + step;
							json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
							if( json == 0 )
							{
								clear();
								res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
								goto goto_return;
							}
						}
						if( jsonlen )
						{
							char letter = json[ jsonlen - 1 ];
							if( letter != '[' && letter != '{' )
								json[ jsonlen++ ] = ',';
						}
						json[ jsonlen++ ] = '0';
						json[ jsonlen ] = 0;
						goto goto_return;
					}
					else if( locnumber < 0 )
#ifdef __WINDOWS__
#pragma warning( push )
#pragma warning( disable: 4146 )
#endif
						locnumber = -locnumber;
#ifdef __WINDOWS__
#pragma warning( pop )
#endif
					while( locnumber )
					{
						locnumber /= 10;
						count_of_digits++;
					}
					if( value < 0 )
						count_of_digits++;
					if( jsonlen + count_of_digits + 2 > jsonsize )
					{
						jsonsize += count_of_digits + 2 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					if( jsonlen )
					{
						char letter = json[ jsonlen - 1 ];
						if( letter != '[' && letter != '{' )
							json[ jsonlen++ ] = ',';
					}
					begin = &json[ jsonlen ];
					if( value < 0 )
					{
						*begin = '-';
						begin++;
#ifdef __WINDOWS__
#pragma warning( push )
#pragma warning( disable: 4146 )
#endif
						value = -value;
#ifdef __WINDOWS__
#pragma warning( pop )
#endif
					}
					jsonlen += count_of_digits;
					ptr = &json[ jsonlen - 1 ];
					for( ; ptr >= begin ; --ptr )
					{
						*ptr = 0x30 + (char)( value % 10 );
						value /= 10;
					}
					json[ jsonlen ] = 0;
goto_return:
					return res->succeeded();
				};
				template< size_t step , class T >
				booinline bool add( ::booldog::result* pres , const char* name , T value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );

					char* ptr = 0 , * begin = 0;
					size_t count_of_digits = 0;
					T locnumber = value;

					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}
					if( jsonlen + 2 > jsonsize )
					{
						jsonsize += 2 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					if( jsonlen )
					{
						char letter = json[ jsonlen - 1 ];
						if( letter != '[' && letter != '{' )
							json[ jsonlen++ ] = ',';
					}
					if( serialize_and_add< step >( res , name , debuginfo ) == false )
						goto goto_return;
					if( locnumber == 0 )
					{
						if( jsonlen + 3 > jsonsize )
						{
							jsonsize += 3 + step;
							json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
							if( json == 0 )
							{
								clear();
								res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
								goto goto_return;
							}
						}
						json[ jsonlen++ ] = ':';
						json[ jsonlen++ ] = '0';
						json[ jsonlen ] = 0;
						goto goto_return;
					}
					else if( locnumber < 0 )
#ifdef __WINDOWS__
#pragma warning( push )
#pragma warning( disable: 4146 )
#endif
						locnumber = -locnumber;
#ifdef __WINDOWS__
#pragma warning( pop )
#endif
					while( locnumber )
					{
						locnumber /= 10;
						count_of_digits++;
					}
					if( value < 0 )
						count_of_digits++;
					if( jsonlen + count_of_digits + 2 > jsonsize )
					{
						jsonsize += count_of_digits + 2 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					json[ jsonlen++ ] = ':';
					begin = &json[ jsonlen ];
					if( value < 0 )
					{
						*begin = '-';
						begin++;
#ifdef __WINDOWS__
#pragma warning( push )
#pragma warning( disable: 4146 )
#endif
						value = -value;
#ifdef __WINDOWS__
#pragma warning( pop )
#endif
					}
					jsonlen += count_of_digits;
					ptr = &json[ jsonlen - 1 ];
					for( ; ptr >= begin ; --ptr )
					{
						*ptr = 0x30 + (char)( value % 10 );
						value /= 10;
					}
					json[ jsonlen ] = 0;
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool add( ::booldog::result* pres , bool value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}
					if( jsonlen + 7 > jsonsize )
					{
						jsonsize += 7 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					if( jsonlen )
					{
						char letter = json[ jsonlen - 1 ];
						if( letter != '[' && letter != '{' )
							json[ jsonlen++ ] = ',';
					}
					if( value )
					{
						json[ jsonlen++ ] = 't';
						json[ jsonlen++ ] = 'r';
						json[ jsonlen++ ] = 'u';
						json[ jsonlen++ ] = 'e';
						json[ jsonlen ] = 0;
					}
					else
					{
						json[ jsonlen++ ] = 'f';
						json[ jsonlen++ ] = 'a';
						json[ jsonlen++ ] = 'l';
						json[ jsonlen++ ] = 's';
						json[ jsonlen++ ] = 'e';
						json[ jsonlen ] = 0;
					}
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool add( ::booldog::result* pres , const char* name , bool value
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}

					if( jsonlen + 2 > jsonsize )
					{
						jsonsize += 2 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}

					if( jsonlen )
					{
						char letter = json[ jsonlen - 1 ];
						if( letter != '[' && letter != '{' )
							json[ jsonlen++ ] = ',';
					}

					if( serialize_and_add< step >( res , name , debuginfo ) == false )
						goto goto_return;

					if( jsonlen + 7 > jsonsize )
					{
						jsonsize += 7 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}

					json[ jsonlen++ ] = ':';
					if( value )
					{
						json[ jsonlen++ ] = 't';
						json[ jsonlen++ ] = 'r';
						json[ jsonlen++ ] = 'u';
						json[ jsonlen++ ] = 'e';
						json[ jsonlen ] = 0;
					}
					else
					{
						json[ jsonlen++ ] = 'f';
						json[ jsonlen++ ] = 'a';
						json[ jsonlen++ ] = 'l';
						json[ jsonlen++ ] = 's';
						json[ jsonlen++ ] = 'e';
						json[ jsonlen ] = 0;
					}
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool addnull( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}
					if( jsonlen + 6 > jsonsize )
					{
						jsonsize += 6 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					if( jsonlen )
					{
						char letter = json[ jsonlen - 1 ];
						if( letter != '[' && letter != '{' )
							json[ jsonlen++ ] = ',';
					}
					json[ jsonlen++ ] = 'n';
					json[ jsonlen++ ] = 'u';
					json[ jsonlen++ ] = 'l';
					json[ jsonlen++ ] = 'l';
					json[ jsonlen ] = 0;
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool addnull( ::booldog::result* pres , const char* name 
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}

					if( jsonlen + 2 > jsonsize )
					{
						jsonsize += 2 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}

					if( jsonlen )
					{
						char letter = json[ jsonlen - 1 ];
						if( letter != '[' && letter != '{' )
							json[ jsonlen++ ] = ',';
					}

					if( serialize_and_add< step >( res , name , debuginfo ) == false )
						goto goto_return;

					if( jsonlen + 6 > jsonsize )
					{
						jsonsize += 6 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}

					json[ jsonlen++ ] = ':';
					json[ jsonlen++ ] = 'n';
					json[ jsonlen++ ] = 'u';
					json[ jsonlen++ ] = 'l';
					json[ jsonlen++ ] = 'l';
					json[ jsonlen ] = 0;
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool begin_object( ::booldog::result* pres , const char* name
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}

					if( jsonlen + 2 > jsonsize )
					{
						jsonsize += 2 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}

					if( jsonlen )
					{
						char letter = json[ jsonlen - 1 ];
						if( letter != '[' && letter != '{' )
							json[ jsonlen++ ] = ',';
					}

					if( serialize_and_add< step >( res , name , debuginfo ) == false )
						goto goto_return;
					
					if( jsonlen + 3 > jsonsize )
					{
						jsonsize += 3 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}

					json[ jsonlen++ ] = ':';
					json[ jsonlen++ ] = '{';
					json[ jsonlen ] = 0;
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool begin_array( ::booldog::result* pres , const char* name
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}

					if( jsonlen + 2 > jsonsize )
					{
						jsonsize += 2 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}

					if( jsonlen )
					{
						char letter = json[ jsonlen - 1 ];
						if( letter != '[' && letter != '{' )
							json[ jsonlen++ ] = ',';
					}

					if( serialize_and_add< step >( res , name , debuginfo ) == false )
						goto goto_return;
					
					if( jsonlen + 3 > jsonsize )
					{
						jsonsize += 3 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}

					json[ jsonlen++ ] = ':';
					json[ jsonlen++ ] = '[';
					json[ jsonlen ] = 0;
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool end_object( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}
					if( jsonlen + 2 > jsonsize )
					{
						jsonsize += 2 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					json[ jsonlen++ ] = '}';
					json[ jsonlen ] = 0;
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool begin_array( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}
					if( jsonlen + 3 > jsonsize )
					{
						jsonsize += 3 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					if( jsonlen )
					{
						char letter = json[ jsonlen - 1 ];
						if( letter != '[' && letter != '{' )
							json[ jsonlen++ ] = ',';
					}
					json[ jsonlen++ ] = '[';
					json[ jsonlen ] = 0;
goto_return:
					return res->succeeded();
				};
				template< size_t step >
				booinline bool end_array( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
					if( nodesindex )
					{
						clear();
						res->booerr( ::booldog::enums::result::booerr_type_object_is_already_initialized );
						goto goto_return;
					}
					if( jsonlen + 2 > jsonsize )
					{
						jsonsize += 2 + step;
						json = jsonallocator->realloc_array< char >( json , jsonsize , debuginfo );
						if( json == 0 )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
					}
					json[ jsonlen++ ] = ']';
					json[ jsonlen ] = 0;
goto_return:
					return res->succeeded();
				};
				template< size_t step , class P0 >
				booinline bool object( ::booldog::result* pres , const char* name0 , P0 value0 , bool close_object_scope
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );

					if( begin_object< step >( res , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name0 , value0 , debuginfo ) == false )
						goto goto_return;

					if( close_object_scope && end_object< step >( res , debuginfo ) == false )
						goto goto_return;
goto_return:
					return res->succeeded();
				};
				template< size_t step , class P0 , class P1 >
				booinline bool object( ::booldog::result* pres , const char* name0 , P0 value0 , const char* name1 , P1 value1
					, bool close_object_scope , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );

					if( begin_object< step >( res , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name0 , value0 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name1 , value1 , debuginfo ) == false )
						goto goto_return;

					if( close_object_scope && end_object< step >( res , debuginfo ) == false )
						goto goto_return;
goto_return:
					return res->succeeded();
				};
				template< size_t step , class P0 , class P1 , class P2 >
				booinline bool object( ::booldog::result* pres , const char* name0 , P0 value0 , const char* name1 , P1 value1
					, const char* name2 , P2 value2 , bool close_object_scope , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );

					if( begin_object< step >( res , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name0 , value0 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name1 , value1 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name2 , value2 , debuginfo ) == false )
						goto goto_return;

					if( close_object_scope && end_object< step >( res , debuginfo ) == false )
						goto goto_return;
goto_return:
					return res->succeeded();
				};
				template< size_t step , class P0 , class P1 , class P2 , class P3 >
				booinline bool object( ::booldog::result* pres , const char* name0 , P0 value0 , const char* name1 , P1 value1
					, const char* name2 , P2 value2 , const char* name3 , P3 value3 , bool close_object_scope 
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );

					if( begin_object< step >( res , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name0 , value0 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name1 , value1 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name2 , value2 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name3 , value3 , debuginfo ) == false )
						goto goto_return;

					if( close_object_scope && end_object< step >( res , debuginfo ) == false )
						goto goto_return;
goto_return:
					return res->succeeded();
				};
				template< size_t step , class P0 , class P1 , class P2 , class P3 , class P4 >
				booinline bool object( ::booldog::result* pres , const char* name0 , P0 value0 , const char* name1 , P1 value1
					, const char* name2 , P2 value2 , const char* name3 , P3 value3 , const char* name4 , P4 value4	, bool close_object_scope
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );

					if( begin_object< step >( res , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name0 , value0 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name1 , value1 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name2 , value2 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name3 , value3 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name4 , value4 , debuginfo ) == false )
						goto goto_return;

					if( close_object_scope && end_object< step >( res , debuginfo ) == false )
						goto goto_return;
goto_return:
					return res->succeeded();
				};

				template< size_t step , class P0 >
				booinline bool object( ::booldog::result* pres , const char* object_name , const char* name0 , P0 value0 , bool close_object_scope
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );

					if( begin_object< step >( res , object_name , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name0 , value0 , debuginfo ) == false )
						goto goto_return;

					if( close_object_scope && end_object< step >( res , debuginfo ) == false )
						goto goto_return;
goto_return:
					return res->succeeded();
				};
				template< size_t step , class P0 , class P1 >
				booinline bool object( ::booldog::result* pres , const char* object_name , const char* name0 , P0 value0 , const char* name1 , P1 value1
					, bool close_object_scope , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );

					if( begin_object< step >( res , object_name , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name0 , value0 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name1 , value1 , debuginfo ) == false )
						goto goto_return;

					if( close_object_scope && end_object< step >( res , debuginfo ) == false )
						goto goto_return;
goto_return:
					return res->succeeded();
				};
				template< size_t step , class P0 , class P1 , class P2 >
				booinline bool object( ::booldog::result* pres , const char* object_name , const char* name0 , P0 value0 , const char* name1 , P1 value1
					, const char* name2 , P2 value2 , bool close_object_scope , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );

					if( begin_object< step >( res , object_name , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name0 , value0 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name1 , value1 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name2 , value2 , debuginfo ) == false )
						goto goto_return;

					if( close_object_scope && end_object< step >( res , debuginfo ) == false )
						goto goto_return;
goto_return:
					return res->succeeded();
				};
				template< size_t step , class P0 , class P1 , class P2 , class P3 >
				booinline bool object( ::booldog::result* pres , const char* object_name , const char* name0 , P0 value0 , const char* name1 , P1 value1
					, const char* name2 , P2 value2 , const char* name3 , P3 value3 , bool close_object_scope 
					, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );

					if( begin_object< step >( res , object_name , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name0 , value0 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name1 , value1 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name2 , value2 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name3 , value3 , debuginfo ) == false )
						goto goto_return;

					if( close_object_scope && end_object< step >( res , debuginfo ) == false )
						goto goto_return;
goto_return:
					return res->succeeded();
				};
				template< size_t step , class P0 , class P1 , class P2 , class P3 , class P4 >
				booinline bool object( ::booldog::result* pres , const char* object_name , const char* name0 , P0 value0 , const char* name1 
					, P1 value1	, const char* name2 , P2 value2 , const char* name3 , P3 value3 , const char* name4 , P4 value4	
					, bool close_object_scope , const ::booldog::debug::info& debuginfo = debuginfo_macros )
				{
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );

					if( begin_object< step >( res , object_name , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name0 , value0 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name1 , value1 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name2 , value2 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name3 , value3 , debuginfo ) == false )
						goto goto_return;

					if( add< step >( res , name4 , value4 , debuginfo ) == false )
						goto goto_return;

					if( close_object_scope && end_object< step >( res , debuginfo ) == false )
						goto goto_return;
goto_return:
					return res->succeeded();
				};
			};

			struct serializator
			{
				union
				{
					serializator_slow slow;
					serializator_fast fast;
				};
				serializator( booldog::allocator* allocator )
				{
					slow.nodessize = 0;
					slow.nodesindex = 0;
					slow.nodes = 0;
					slow.json = 0;
					slow.jsonsize = 0;
					slow.jsonlen = 0;
					slow.jsonallocator = allocator;
				};
				~serializator( void )
				{
					if( slow.json )
						slow.jsonallocator->free( slow.json );
					if( slow.nodes )
						slow.jsonallocator->free( slow.nodes );
				};
				booinline char* detach(void)
				{
					return fast.detach();
				};
				booinline void clear( void )
				{
					fast.clear();
				};
				booinline ::booldog::data::json::serializator& operator = ( const ::booldog::data::json::serializator& obj );
				operator ::booldog::data::json::object() const
				{	
					if( slow.nodesindex )
						return ::booldog::data::json::object( &slow.nodes[ 0 ] );
					else if( slow.jsonlen )
					{
						const_cast< ::booldog::data::json::serializator* >( this )->parse< 16 >( 0 , debuginfo_macros );
						if( slow.nodesindex )
							return ::booldog::data::json::object( &slow.nodes[ 0 ] );
					}
					return ::booldog::data::json::object();
				};
				operator ::booldog::data::json::object()
				{	
					if( slow.nodesindex )
						return ::booldog::data::json::object( &slow.nodes[ 0 ] );
					else if( slow.jsonlen )
					{
						parse< 16 >( 0 , debuginfo_macros );
						if( slow.nodesindex )
							return ::booldog::data::json::object( &slow.nodes[ 0 ] );
					}
					return ::booldog::data::json::object();
				};
				template< size_t step >
				booinline bool parse( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros );
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
			object_value::operator bool()
			{
				if( node )
				{
					::booldog::data::json::checknode( this );
					return node->operator bool();
				}
				return false;
			};
			node::operator bool()
			{
				if( type == ::booldog::enums::data::json::boolean_true )
					return true;
				return false;
			};
			node::operator ::booldog::int32()
			{
				if( this->type != ::booldog::enums::data::json::number )
					return 0;
				char* ptr = this->name_or_valuebegin;
				if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_ROOT ) == 0
					&& this->parent->type == ::booldog::enums::data::json::object )
				{
					ptr--;
					if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
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
					if( ptr == this->valueend + 1 )
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
					if( ptr == this->valueend + 1 )
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
					if( ptr == this->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
				goto goto_return;
goto_exponent_part_minus:
				for( ; ; )
				{
					if( ptr == this->valueend + 1 )
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
				if( realfloatpart != 0 )
					realres = (::booldog::int32)( realres + realfloatpart );
				if( negative )
					realres *= -1;
				return realres;
			};
			object_value::operator ::booldog::int32()
			{
				if( node )
					::booldog::data::json::checknode( this );
				else
					return 0;
				return node->operator booldog::int32();
			};
			node::operator float()
			{
				if( this->type != ::booldog::enums::data::json::number )
					return 0;				
				char* ptr = this->name_or_valuebegin;
				if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_ROOT ) == 0
					&& this->parent->type == ::booldog::enums::data::json::object )
				{
					ptr--;
					if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
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
					if( ptr == this->valueend + 1 )
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
					if( ptr == this->valueend + 1 )
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
					if( ptr == this->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
				goto goto_return;
goto_exponent_part_minus:
				for( ; ; )
				{
					if( ptr == this->valueend + 1 )
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
				if( realfloatpart != 0 )
					realres += realfloatpart;
				if( negative )
					realres *= -1;
				return realres;
			};
			object_value::operator float()
			{
				if( node )
					::booldog::data::json::checknode( this );
				else
					return 0;
				return node->operator float();
			};
			node::operator ::booldog::uint32()
			{
				if( this->type != ::booldog::enums::data::json::number )
					return 0;
				char* ptr = this->name_or_valuebegin;
				if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_ROOT ) == 0
					&& this->parent->type == ::booldog::enums::data::json::object )
				{
					ptr--;
					if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
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
					if( ptr == this->valueend + 1 )
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
					if( ptr == this->valueend + 1 )
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
					if( ptr == this->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
				goto goto_return;
goto_exponent_part_minus:
				for( ; ; )
				{
					if( ptr == this->valueend + 1 )
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
				if( realfloatpart != 0 )
					realres = (::booldog::uint32)( realres + realfloatpart );
				return realres;
			};
			object_value::operator ::booldog::uint32()
			{
				if( node )
					::booldog::data::json::checknode( this );
				else
					return 0;
				return node->operator booldog::uint32();
			};
			node::operator ::booldog::uint64()
			{
				if( this->type != ::booldog::enums::data::json::number )
					return 0;
				char* ptr = this->name_or_valuebegin;
				if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_ROOT ) == 0
					&& this->parent->type == ::booldog::enums::data::json::object )
				{
					ptr--;
					if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
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
					if( ptr == this->valueend + 1 )
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
					if( ptr == this->valueend + 1 )
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
					if( ptr == this->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
				goto goto_return;
goto_exponent_part_minus:
				for( ; ; )
				{
					if( ptr == this->valueend + 1 )
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
				if( realfloatpart != 0 )
					realres = (::booldog::uint64)( realres + realfloatpart );
				return realres;
			};
			object_value::operator ::booldog::uint64()
			{
				if( node )
					::booldog::data::json::checknode( this );
				else
					return 0;
				return node->operator booldog::uint64();
			};
			node::operator ::booldog::int64()
			{
				if( this->type != ::booldog::enums::data::json::number )
					return 0;
				char* ptr = this->name_or_valuebegin;
				if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_ROOT ) == 0
					&& this->parent->type == ::booldog::enums::data::json::object )
				{
					ptr--;
					if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
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
					if( ptr == this->valueend + 1 )
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
					if( ptr == this->valueend + 1 )
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
					if( ptr == this->valueend + 1 )
						goto goto_return;
					exponent_part_count *= 10;
					exponent_part_count += ::booldog::data::json::_decimal_string_to_number_table[ (::booldog::byte)*ptr++ ];
				}
				goto goto_return;
goto_exponent_part_minus:
				for( ; ; )
				{
					if( ptr == this->valueend + 1 )
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
				if( realfloatpart != 0 )
					realres = (::booldog::int64)( realres + realfloatpart );
				if( negative )
					realres *= -1;
				return realres;
			};
			object_value::operator ::booldog::int64()
			{
				if( node )
					::booldog::data::json::checknode( this );
				else
					return 0;
				return node->operator booldog::int64();
			};
			booinline bool checknewjssonptr( char*& ptr , ::booldog::data::json::serializator* parentserializator 
				, const ::booldog::debug::info& debuginfo )
			{
				if( parentserializator->slow.jsonlen + 2 > parentserializator->slow.jsonsize )
				{
					char* oldjsonstr = parentserializator->slow.json;
					parentserializator->slow.jsonsize += 16;
					parentserializator->slow.json = parentserializator->slow.jsonallocator->realloc_array< char >( parentserializator->slow.json
						, parentserializator->slow.jsonsize , debuginfo );
					if( parentserializator->slow.json == 0 )
					{
						parentserializator->clear();
						return false;
					}
					else if( parentserializator->slow.json != oldjsonstr )
					{
						parentserializator->slow.nodes[ 0 ].newjsonptr( oldjsonstr , parentserializator->slow.json );
						parentserializator->slow.nodes[ 0 ].name_or_valuebegin = parentserializator->slow.json;
						parentserializator->slow.nodes[ 0 ].valueend = 
							parentserializator->slow.json + (
							parentserializator->slow.nodes[ 0 ].valueend - oldjsonstr );
						ptr = parentserializator->slow.json + ( ptr - oldjsonstr );
					}
				}
				return true;
			};
			template< size_t step , class T >
			booinline bool node::set( ::booldog::result* pres , char* valuebegin , T value
				, const ::booldog::debug::info& debuginfo )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				if( valuebegin == 0 )
				{
					valuebegin = name_or_valuebegin;
					if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_ROOT ) == 0
						&& parent->type == ::booldog::enums::data::json::object )
					{
						valuebegin--;
						if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
						{
							for( ; ; )
							{
								switch( *++valuebegin )
								{
								case '\\':
									valuebegin++;
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
								if( *++valuebegin == 0 )
									break;
							}
						}
						valuebegin += 2;
					}
				}
				::booldog::data::json::serializator* parentserializator = 0;
				if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_ROOT ) )
					parentserializator = serializator;
				else
				{
					::booldog::data::json::node* pparent = parent;						
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
				char* ptr = 0;
				size_t count_of_digits = 0 , removed_size = valueend - valuebegin + 1;
				T locnumber = value;
				if( locnumber == 0 )
				{
					int diff = 0;
					if( parentserializator->slow.jsonlen + 1 - removed_size + 1 > parentserializator->slow.jsonsize )
					{
						char* oldjsonstr = parentserializator->slow.json;
						parentserializator->slow.jsonsize += 1 - removed_size + 1 + step;
						parentserializator->slow.json = parentserializator->slow.jsonallocator->realloc_array< char >( 
							parentserializator->slow.json , parentserializator->slow.jsonsize , debuginfo );
						if( parentserializator->slow.json == 0 )
						{
							parentserializator->clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
						else if( parentserializator->slow.json != oldjsonstr )
						{
							parentserializator->slow.nodes[ 0 ].newjsonptr( oldjsonstr , parentserializator->slow.json );
							parentserializator->slow.nodes[ 0 ].name_or_valuebegin = parentserializator->slow.json;
							parentserializator->slow.nodes[ 0 ].valueend = 
								parentserializator->slow.json + (
								parentserializator->slow.nodes[ 0 ].valueend - oldjsonstr );
							valuebegin = parentserializator->slow.json + ( valuebegin - oldjsonstr );
						}
					}
					if( 1 > removed_size )
					{		
						diff = (int)( 1 - removed_size );
						::booldog::mem::expand< char >( valuebegin - parentserializator->slow.json
							, parentserializator->slow.json , parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize
							, diff );
					}
					else if( 1 < removed_size )
					{
						diff = (int)( removed_size - 1 );
						::booldog::mem::remove< char >( valuebegin - parentserializator->slow.json
							, parentserializator->slow.json , parentserializator->slow.jsonlen + 1 , diff );
						diff *= -1;
					}
					if( diff != 0 )
					{
						parentserializator->slow.nodes[ 0 ].jsonoffset( diff , valueend );
						parentserializator->slow.nodes[ 0 ].valueend += diff;
						parentserializator->slow.jsonlen += diff;
					}
					*valueend = '0';
					type = ::booldog::enums::data::json::number;
					goto goto_return;
				}
				else if( locnumber < 0 )
#ifdef __WINDOWS__
#pragma warning( push )
#pragma warning( disable: 4146 )
#endif
					locnumber = -locnumber;
#ifdef __WINDOWS__
#pragma warning( pop )
#endif
				while( locnumber )
				{
					locnumber /= 10;
					count_of_digits++;
				}
				if( value < 0 )
					count_of_digits++;
				if( parentserializator->slow.jsonlen + count_of_digits - removed_size + 1 > parentserializator->slow.jsonsize )
				{
					char* oldjsonstr = parentserializator->slow.json;
					parentserializator->slow.jsonsize += count_of_digits - removed_size + 1 + step;
					parentserializator->slow.json = parentserializator->slow.jsonallocator->realloc_array< char >( 
						parentserializator->slow.json , parentserializator->slow.jsonsize , debuginfo );
					if( parentserializator->slow.json == 0 )
					{
						parentserializator->clear();
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						goto goto_return;
					}
					else if( parentserializator->slow.json != oldjsonstr )
					{
						parentserializator->slow.nodes[ 0 ].newjsonptr( oldjsonstr , parentserializator->slow.json );
						parentserializator->slow.nodes[ 0 ].name_or_valuebegin = parentserializator->slow.json;
						parentserializator->slow.nodes[ 0 ].valueend = 
							parentserializator->slow.json + (
							parentserializator->slow.nodes[ 0 ].valueend - oldjsonstr );
						valuebegin = parentserializator->slow.json + ( valuebegin - oldjsonstr );
					}
				}
				if( count_of_digits > removed_size )
				{		
					diff = (int)( count_of_digits - removed_size );
					::booldog::mem::expand< char >( valuebegin - parentserializator->slow.json
						, parentserializator->slow.json , parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize
						, diff );
				}
				else if( count_of_digits < removed_size )
				{
					diff = (int)( removed_size - count_of_digits );
					::booldog::mem::remove< char >( valuebegin - parentserializator->slow.json
						, parentserializator->slow.json , parentserializator->slow.jsonlen + 1 , diff );
					diff *= -1;
				}
				if( diff != 0 )
				{
					parentserializator->slow.nodes[ 0 ].jsonoffset( diff , valueend );
					parentserializator->slow.nodes[ 0 ].valueend += diff;
					parentserializator->slow.jsonlen += diff;
				}
				ptr = valueend;
				if( value < 0 )
				{
					*valuebegin = '-';
					valuebegin++;
#ifdef __WINDOWS__
#pragma warning( push )
#pragma warning( disable: 4146 )
#endif
					value = -value;
#ifdef __WINDOWS__
#pragma warning( pop )
#endif
				}
				for( ; ptr >= valuebegin ; --ptr )
				{
					*ptr = 0x30 + (char)( value % 10 );
					value /= 10;
				}
				type = ::booldog::enums::data::json::number;
goto_return:
				return res->succeeded();
			};
			template< size_t step >
			booinline bool node::set( ::booldog::result* pres , char* valuebegin , bool value
				, const ::booldog::debug::info& debuginfo )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				if( valuebegin == 0 )
				{
					valuebegin = name_or_valuebegin;
					if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_ROOT ) == 0
						&& parent->type == ::booldog::enums::data::json::object )
					{
						valuebegin--;
						if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
						{
							for( ; ; )
							{
								switch( *++valuebegin )
								{
								case '\\':
									valuebegin++;
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
								if( *++valuebegin == 0 )
									break;
							}
						}
						valuebegin += 2;
					}
				}
				::booldog::data::json::serializator* parentserializator = 0;
				if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_ROOT ) )
					parentserializator = serializator;
				else
				{
					::booldog::data::json::node* pparent = parent;						
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
				size_t count_of_digits = value ? 4 : 5 , removed_size = valueend - valuebegin + 1;
				int diff = 0;
				if( parentserializator->slow.jsonlen + count_of_digits - removed_size + 1 > parentserializator->slow.jsonsize )
				{
					char* oldjsonstr = parentserializator->slow.json;
					parentserializator->slow.jsonsize += count_of_digits - removed_size + 1 + step;
					parentserializator->slow.json = parentserializator->slow.jsonallocator->realloc_array< char >( 
						parentserializator->slow.json , parentserializator->slow.jsonsize , debuginfo );
					if( parentserializator->slow.json == 0 )
					{
						parentserializator->clear();
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						goto goto_return;
					}
					else if( parentserializator->slow.json != oldjsonstr )
					{
						parentserializator->slow.nodes[ 0 ].newjsonptr( oldjsonstr , parentserializator->slow.json );
						parentserializator->slow.nodes[ 0 ].name_or_valuebegin = parentserializator->slow.json;
						parentserializator->slow.nodes[ 0 ].valueend = 
							parentserializator->slow.json + (
							parentserializator->slow.nodes[ 0 ].valueend - oldjsonstr );
						valuebegin = parentserializator->slow.json + ( valuebegin - oldjsonstr );
					}
				}
				if( count_of_digits > removed_size )
				{		
					diff = (int)( count_of_digits - removed_size );
					::booldog::mem::expand< char >( valuebegin - parentserializator->slow.json
						, parentserializator->slow.json , parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize
						, diff );
				}
				else if( count_of_digits < removed_size )
				{
					diff = (int)( removed_size - count_of_digits );
					::booldog::mem::remove< char >( valuebegin - parentserializator->slow.json
						, parentserializator->slow.json , parentserializator->slow.jsonlen + 1 , diff );
					diff *= -1;
				}
				if( diff != 0 )
				{
					parentserializator->slow.nodes[ 0 ].jsonoffset( diff , valueend );
					parentserializator->slow.nodes[ 0 ].valueend += diff;
					parentserializator->slow.jsonlen += diff;
				}
				if( value )
				{
					*valuebegin++ = 't';
					*valuebegin++ = 'r';
					*valuebegin++ = 'u';
					*valuebegin++ = 'e';
					type = ::booldog::enums::data::json::boolean_true;
				}
				else
				{
					*valuebegin++ = 'f';
					*valuebegin++ = 'a';
					*valuebegin++ = 'l';
					*valuebegin++ = 's';
					*valuebegin++ = 'e';
					type = ::booldog::enums::data::json::boolean_false;
				}
goto_return:
				return res->succeeded();
			};
			template< size_t step >
			booinline bool node::set( ::booldog::result* pres , char* valuebegin , const char* value
				, const ::booldog::debug::info& debuginfo )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				if( valuebegin == 0 )
				{
					valuebegin = name_or_valuebegin;
					if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_ROOT ) == 0
						&& parent->type == ::booldog::enums::data::json::object )
					{
						valuebegin--;
						if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
						{
							for( ; ; )
							{
								switch( *++valuebegin )
								{
								case '\\':
									valuebegin++;
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
								if( *++valuebegin == 0 )
									break;
							}
						}
						valuebegin += 2;
					}
				}
				::booldog::data::json::serializator* parentserializator = 0;
				if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_ROOT ) )
					parentserializator = serializator;
				else
				{
					::booldog::data::json::node* pparent = parent;						
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
				char* valuebeginbegin = valuebegin;
				int diff = 0;
				const char* ptr = 0;
				const ::booldog::byte* ptrbyte = (::booldog::byte*)value;
				size_t removed_size = valueend - valuebegin + 1 , count_of_digits = 0;
				if( removed_size < 1 )
					goto goto_next1;
				*valuebegin++ = '"';
				removed_size--;
				for( ; ; )
				{
					switch( *ptrbyte )
					{
					case 0:
						if( removed_size < 1 )
							goto goto_next1;
						*valuebegin++ = *ptrbyte++;
						removed_size--;
						goto goto_next3;
					default:
						{
							if( *ptrbyte <= 0x7f )
							{
								if( removed_size < 1 )
									goto goto_next1;
								removed_size--;
							}
							else if( (*ptrbyte >> 5 ) == 0x6 )
							{
								if( removed_size < 2 )
									goto goto_next1;

								*valuebegin++ = *ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									parentserializator->clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								removed_size -= 2;
							}
							/* three byte */
							else if( ( *ptrbyte >> 4 ) == 0x0e ) 
							{
								if( removed_size < 3 )
									goto goto_next1;
								*valuebegin++ = *ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									parentserializator->clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								*valuebegin++ = *ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									parentserializator->clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								removed_size -= 3;
							}
							/* four byte */        
							else if( ( *ptrbyte >> 3 ) == 0x1e )
							{
								if( removed_size < 4 )
									goto goto_next2;
								*valuebegin++ = *ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									parentserializator->clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								*valuebegin++ = *ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									parentserializator->clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								*valuebegin++ = *ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									parentserializator->clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								removed_size -= 4;
							}
							else
							{
								parentserializator->clear();
								res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
								goto goto_return;
							}
							*valuebegin++ = *ptrbyte++;
							break;
						}
					}
				}
goto_next1:
				ptr = (char*)ptrbyte;
				for( ; ; )
				{
					switch( *ptrbyte )
					{
					case 0:
						*ptrbyte++;
						goto goto_next2;
					default:
						{
							if( *ptrbyte <= 0x7f )
							{
							}
							else if( (*ptrbyte >> 5 ) == 0x6 )
							{
								*ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									parentserializator->clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
							}
							/* three byte */
							else if( ( *ptrbyte >> 4 ) == 0x0e ) 
							{
								*ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									parentserializator->clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								*ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									parentserializator->clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
							}
							/* four byte */        
							else if( ( *ptrbyte >> 3 ) == 0x1e )
							{
								*ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									parentserializator->clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								*ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									parentserializator->clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								*ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									parentserializator->clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
							}
							else
							{
								parentserializator->clear();
								res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
								goto goto_return;
							}
							*ptrbyte++;
							break;
						}
					}
				}
goto_next2:
				count_of_digits = ( (char*)ptrbyte - ptr );
				if( parentserializator->slow.jsonlen + count_of_digits - removed_size + 2 > parentserializator->slow.jsonsize )
				{
					char* oldjsonstr = parentserializator->slow.json;
					parentserializator->slow.jsonsize += count_of_digits - removed_size + 2 + step;
					parentserializator->slow.json = parentserializator->slow.jsonallocator->realloc_array< char >( 
						parentserializator->slow.json , parentserializator->slow.jsonsize , debuginfo );
					if( parentserializator->slow.json == 0 )
					{
						parentserializator->clear();
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						goto goto_return;
					}
					else if( parentserializator->slow.json != oldjsonstr )
					{
						parentserializator->slow.nodes[ 0 ].newjsonptr( oldjsonstr , parentserializator->slow.json );
						parentserializator->slow.nodes[ 0 ].name_or_valuebegin = parentserializator->slow.json;
						parentserializator->slow.nodes[ 0 ].valueend = 
							parentserializator->slow.json + (
							parentserializator->slow.nodes[ 0 ].valueend - oldjsonstr );
						valuebegin = parentserializator->slow.json + ( valuebegin - oldjsonstr );
						valuebeginbegin = parentserializator->slow.json + ( valuebeginbegin - oldjsonstr );
					}
				}
				if( count_of_digits > removed_size )
				{		
					diff = (int)( count_of_digits - removed_size );
					::booldog::mem::expand< char >( valuebegin - parentserializator->slow.json
						, parentserializator->slow.json , parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize
						, diff );
				}
				if( valuebeginbegin == valuebegin )
					*valuebegin++ = '"';
				::memcpy( valuebegin , ptr , count_of_digits );
				goto goto_next4;
goto_next3:
				if( count_of_digits < removed_size )
				{
					diff = (int)( removed_size - count_of_digits );
					::booldog::mem::remove< char >( valuebegin - parentserializator->slow.json
						, parentserializator->slow.json , parentserializator->slow.jsonlen + 1 , diff );
					diff *= -1;
				}
goto_next4:
				if( diff != 0 )
				{
					parentserializator->slow.nodes[ 0 ].jsonoffset( diff , valueend );
					parentserializator->slow.nodes[ 0 ].valueend += diff;
					parentserializator->slow.jsonlen += diff;
				}
				type = ::booldog::enums::data::json::string;
				::booldog::utils::unset_bit( flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
goto_return:
				return res->succeeded();
			};
			const char* node::json( ::booldog::data::json::serializator* parentserializator 
				, const ::booldog::debug::info& debuginfo ) const
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
								ptr = pnext->name_or_valuebegin - 1;
								if( ::booldog::utils::get_bit( pnext->flags	, BOOLDOG_DATA_JSON_NAME_SERIALIZED ) == 0 )
								{
									for( ; ; )
									{
										switch( *++ptr )
										{
										case '"':
											{
												if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
													goto goto_error;
												::booldog::mem::insert< char >( ptr - parentserializator->slow.json
													, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
													, parentserializator->slow.jsonsize , 1 , "\\\"" , 2 );
												ptr += 2;
												parentserializator->slow.jsonlen++;
												diff++;
												break;
											}
										case '\\':
											{
												if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
													goto goto_error;
												::booldog::mem::insert< char >( ptr - parentserializator->slow.json
													, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
													, parentserializator->slow.jsonsize , 1 , "\\\\" , 2 );
												ptr += 2;
												parentserializator->slow.jsonlen++;
												diff++;
												break;
											}
										case '/':
											{
												if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
													goto goto_error;
												::booldog::mem::insert< char >( ptr - parentserializator->slow.json
													, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
													, parentserializator->slow.jsonsize , 1 , "\\/" , 2 );
												ptr += 1;
												parentserializator->slow.jsonlen++;
												diff++;
												break;
											}
										case '\b':
											{
												if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
													goto goto_error;
												::booldog::mem::insert< char >( ptr - parentserializator->slow.json
													, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
													, parentserializator->slow.jsonsize , 1 , "\\b" , 2 );
												ptr += 1;
												parentserializator->slow.jsonlen++;
												diff++;
												break;
											}
										case '\f':
											{
												if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
													goto goto_error;
												::booldog::mem::insert< char >( ptr - parentserializator->slow.json
													, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
													, parentserializator->slow.jsonsize , 1 , "\\f" , 2 );
												ptr += 1;
												parentserializator->slow.jsonlen++;
												diff++;
												break;
											}
										case '\n':
											{
												if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
													goto goto_error;
												::booldog::mem::insert< char >( ptr - parentserializator->slow.json
													, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
													, parentserializator->slow.jsonsize , 1 , "\\n" , 2 );
												ptr += 1;
												parentserializator->slow.jsonlen++;
												diff++;
												break;
											}
										case '\r':
											{
												if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
													goto goto_error;
												::booldog::mem::insert< char >( ptr - parentserializator->slow.json
													, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
													, parentserializator->slow.jsonsize , 1 , "\\r" , 2 );
												ptr += 1;
												parentserializator->slow.jsonlen++;
												diff++;
												break;
											}
										case '\t':
											{
												if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
													goto goto_error;
												::booldog::mem::insert< char >( ptr - parentserializator->slow.json
													, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
													, parentserializator->slow.jsonsize , 1 , "\\t" , 2 );
												ptr += 1;
												parentserializator->slow.jsonlen++;
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
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\\"" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '\\':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\\\" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '/':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\/" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '\b':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\b" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '\f':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\f" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '\n':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\n" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '\r':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\r" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '\t':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\t" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
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
									parentserializator->slow.nodes[ 0 ].jsonoffset( diff , pnext->valueend );
									parentserializator->slow.nodes[ 0 ].valueend += diff;
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
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\\"" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '\\':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\\\" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '/':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\/" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '\b':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\b" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '\f':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\f" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '\n':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\n" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '\r':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\r" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
													diff++;
													break;
												}
											case '\t':
												{
													if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
														goto goto_error;
													::booldog::mem::insert< char >( ptr - parentserializator->slow.json
														, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
														, parentserializator->slow.jsonsize , 1 , "\\t" , 2 );
													ptr += 1;
													parentserializator->slow.jsonlen++;
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
									parentserializator->slow.nodes[ 0 ].jsonoffset( diff , pnext->valueend );
									parentserializator->slow.nodes[ 0 ].valueend += diff;
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
						if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED ) == 0 )
						{
							int diff = 0;
							ptr = name_or_valuebegin;
							for( ; ; )
							{
								switch( *++ptr )
								{
								case '"':
									{
										if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
											goto goto_error;
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json
											, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
											, parentserializator->slow.jsonsize , 1 , "\\\"" , 2 );
										ptr += 1;
										parentserializator->slow.jsonlen++;
										diff++;
										break;
									}
								case '\\':
									{
										if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
											goto goto_error;
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json
											, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
											, parentserializator->slow.jsonsize , 1 , "\\\\" , 2 );
										ptr += 1;
										parentserializator->slow.jsonlen++;
										diff++;
										break;
									}
								case '/':
									{
										if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
											goto goto_error;
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json
											, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
											, parentserializator->slow.jsonsize , 1 , "\\/" , 2 );
										ptr += 1;
										parentserializator->slow.jsonlen++;
										diff++;
										break;
									}
								case '\b':
									{
										if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
											goto goto_error;
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json
											, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
											, parentserializator->slow.jsonsize , 1 , "\\b" , 2 );
										ptr += 1;
										parentserializator->slow.jsonlen++;
										diff++;
										break;
									}
								case '\f':
									{
										if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
											goto goto_error;
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json
											, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
											, parentserializator->slow.jsonsize , 1 , "\\f" , 2 );
										ptr += 1;
										parentserializator->slow.jsonlen++;
										diff++;
										break;
									}
								case '\n':
									{
										if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
											goto goto_error;
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json
											, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
											, parentserializator->slow.jsonsize , 1 , "\\n" , 2 );
										ptr += 1;
										parentserializator->slow.jsonlen++;
										diff++;
										break;
									}
								case '\r':
									{
										if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
											goto goto_error;
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json
											, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
											, parentserializator->slow.jsonsize , 1 , "\\r" , 2 );
										ptr += 1;
										parentserializator->slow.jsonlen++;
										diff++;
										break;
									}
								case '\t':
									{
										if( checknewjssonptr( ptr , parentserializator , debuginfo ) == false )
											goto goto_error;
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json
											, parentserializator->slow.json , parentserializator->slow.jsonlen + 1
											, parentserializator->slow.jsonsize , 1 , "\\t" , 2 );
										ptr += 1;
										parentserializator->slow.jsonlen++;
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
								parentserializator->slow.nodes[ 0 ].jsonoffset( diff , valueend );
								parentserializator->slow.nodes[ 0 ].valueend += diff;
							}
						}
					}
				}

				ptr = name_or_valuebegin;
				if( ::booldog::utils::get_bit( flags	, BOOLDOG_DATA_JSON_ROOT ) == 0
					&& parent->type == ::booldog::enums::data::json::object )
				{
					ptr--;
					if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
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
goto_error:
				return 0;
			};
			object_json::operator const char*()
			{
				if( node == 0 )
					return 0;
				::booldog::data::json::checknode( this );
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
			node::operator const char*()
			{
				if( this->type != ::booldog::enums::data::json::string )
					return 0;
				char* ptr = this->name_or_valuebegin;
				if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_ROOT ) == 0
					&& this->parent->type == ::booldog::enums::data::json::object )
				{
					ptr--;
					if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
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
				if( ::booldog::utils::get_bit( this->flags	, BOOLDOG_DATA_JSON_VALUE_SERIALIZED ) )
				{
					::booldog::data::json::serializator* parentserializator = 0;
					if( ::booldog::utils::get_bit( this->flags	, BOOLDOG_DATA_JSON_ROOT ) )
						parentserializator = this->serializator;
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
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json												, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\"" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case '\\':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json												, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\\" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case '/':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json												, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "/" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case 'b':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json												, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\b" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case 'f':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json												, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\f" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case 'n':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json												, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\n" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case 'r':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json												, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\r" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case 't':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json												, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\t" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								}
							}
						}
					}
					if( diff != 0 )
					{
						parentserializator->slow.nodes[ 0 ].jsonoffset( diff , this->valueend );
						parentserializator->slow.nodes[ 0 ].valueend += diff;
					}
					::booldog::utils::unset_bit( this->flags , BOOLDOG_DATA_JSON_VALUE_SERIALIZED );
					return begin;
				}
				return ptr;
			};
			object_value::operator const char*()
			{
				if( node )
					::booldog::data::json::checknode( this );
				else
					return 0;
				return node->operator const char *();
			};
			booinline ::booldog::data::json::object_value& object_value::operator = ( const char* value )
			{		
				if( node )
				{
					::booldog::data::json::checknode( this );
					node->set< 16 >( 0 , 0 , value , debuginfo_macros );
				}
				return *this;
			};
			booinline ::booldog::data::json::object_value& object_value::operator = ( ::booldog::int32 value )
			{		
				if( node )
				{
					::booldog::data::json::checknode( this );
					node->set< 16 >( 0 , 0 , value , debuginfo_macros );
				}
				return *this;
			};
			booinline ::booldog::data::json::object_value& object_value::operator = ( ::booldog::int64 value )
			{
				if( node )
				{
					::booldog::data::json::checknode( this );
					node->set< 16 >( 0 , 0 , value , debuginfo_macros );
				}
				return *this;
			};
			booinline ::booldog::data::json::object_value& object_value::operator = ( ::booldog::uint32 value )
			{
				if( node )
				{
					::booldog::data::json::checknode( this );
					node->set< 16 >( 0 , 0 , value , debuginfo_macros );
				}
				return *this;
			};
			booinline ::booldog::data::json::object_value& object_value::operator = ( ::booldog::uint64 value )
			{
				if( node )
				{
					::booldog::data::json::checknode( this );
					node->set< 16 >( 0 , 0 , value , debuginfo_macros );
				}
				return *this;
			};
			booinline ::booldog::data::json::object_value& object_value::operator = ( bool value )
			{
				if( node )
				{
					::booldog::data::json::checknode( this );
					node->set< 16 >( 0 , 0 , value , debuginfo_macros );
				}
				return *this;
			};
			bool object_value::name( ::booldog::result* pres , const char* newname
				, const ::booldog::debug::info& debuginfo )
			{
				if( node )
				{
					::booldog::data::json::checknode( this );
					return node->name( pres , newname , debuginfo );
				}
				else if( pres )
					pres->booerr( ::booldog::enums::result::booerr_type_json_object_has_not_node );
				return false;
			};
			::booldog::uint64 object_value::namehash( void )
			{
				if( node )
				{
					::booldog::data::json::checknode( this );
					return node->namehash;
				}
				return 0;
			};
			const char* object_value::name( void )
			{
				if( node )
				{
					::booldog::data::json::checknode( this );
					return node->name();
				}
				return 0;
			};
			bool node::name( ::booldog::result* pres , const char* newname
				, const ::booldog::debug::info& debuginfo ) const
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );

				::booldog::uint64 newutf8namehash = 0;
				const char* ptr = newname;
				size_t oldsize = 0 , newsize = 0;
				char* nameend = name_or_valuebegin;
				if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_ROOT ) )
				{
					pres->booerr( ::booldog::enums::result::booerr_type_json_it_is_root_object );
					goto goto_return;
				}
				else if( parent->type != ::booldog::enums::data::json::object )
				{
					pres->booerr( ::booldog::enums::result::booerr_type_json_parent_is_not_object );
					goto goto_return;
				}
				for( ; ; )
				{
					switch( *ptr )
					{
					case 0:
						ptr++;
						goto goto_next;
					default:
						{
							const ::booldog::byte* ptrbyte = (::booldog::byte*)ptr;
							newutf8namehash = newutf8namehash * 33 + *ptrbyte;
							if( *ptrbyte <= 0x7f )
							{
							}
							else if( (*ptrbyte >> 5 ) == 0x6 )
							{
								ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								newutf8namehash = newutf8namehash * 33 + *ptrbyte;
							}
							/* three byte */
							else if( ( *ptrbyte >> 4 ) == 0x0e ) 
							{
								ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								newutf8namehash = newutf8namehash * 33 + *ptrbyte;
								ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								newutf8namehash = newutf8namehash * 33 + *ptrbyte;
							}
							/* four byte */        
							else if( ( *ptrbyte >> 3 ) == 0x1e )
							{
								ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								newutf8namehash = newutf8namehash * 33 + *ptrbyte;
								ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								newutf8namehash = newutf8namehash * 33 + *ptrbyte;
								ptrbyte++;
								if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
								{
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								newutf8namehash = newutf8namehash * 33 + *ptrbyte;
							}
							else
							{
								res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
								goto goto_return;
							}
							ptrbyte++;
							ptr = (char*)ptrbyte;
							break;
						}
					}
				}
goto_next:
				if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
				{
					for( ; ; )
					{
						switch( *nameend++ )
						{
						case '\\':
							nameend++;
							break;
						case '"':
							goto goto_away_from_cycle0;
						}
					}
goto_away_from_cycle0:
					;
				}
				else
				{
					for( ; ; )
					{
						switch( *nameend++ )
						{
						case 0:
							goto goto_away_from_cycle1;
						}
					}
goto_away_from_cycle1:
					;
				}
				oldsize = nameend - name_or_valuebegin
					, newsize = ptr - newname;
				if( oldsize == newsize )
					::memcpy( name_or_valuebegin , newname , newsize );
				else
				{
					::booldog::data::json::serializator* parentserializator = 0;
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
					int diff = (int)( newsize - oldsize );
					if( oldsize < newsize )
					{
						if( parentserializator->slow.jsonlen + diff + 1 > parentserializator->slow.jsonsize )
						{
							char* oldjsonstr = parentserializator->slow.json;
							parentserializator->slow.jsonsize = parentserializator->slow.jsonlen + diff + 1 + 16;
							parentserializator->slow.json = parentserializator->slow.jsonallocator->realloc_array< char >( 
								parentserializator->slow.json , parentserializator->slow.jsonsize , debuginfo );
							if( parentserializator->slow.json == 0 )
							{
								res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
								goto goto_return;
							}
							else if( parentserializator->slow.json != oldjsonstr )
							{
								parentserializator->slow.nodes[ 0 ].newjsonptr( oldjsonstr , parentserializator->slow.json );
								parentserializator->slow.nodes[ 0 ].name_or_valuebegin = parentserializator->slow.json;
								parentserializator->slow.nodes[ 0 ].valueend = 
									parentserializator->slow.json + (
									parentserializator->slow.nodes[ 0 ].valueend - oldjsonstr );
							}
						}
					}
					::booldog::mem::insert< char >( name_or_valuebegin - parentserializator->slow.json 
						, parentserializator->slow.json , parentserializator->slow.jsonlen + 1 
						, parentserializator->slow.jsonsize , oldsize , newname , newsize );
					parentserializator->slow.jsonlen += diff;
					parentserializator->slow.nodes[ 0 ].jsonoffset( diff , valueend );
					parentserializator->slow.nodes[ 0 ].valueend += diff;
				}
				const_cast< ::booldog::data::json::node* >( this )->namehash = newutf8namehash;
				::booldog::utils::unset_bit( flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED );
goto_return:
				return res->succeeded();
			};
			const char* node::name( void ) const
			{
				if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_ROOT )
					|| parent->type != ::booldog::enums::data::json::object )
					return 0;
				if( ::booldog::utils::get_bit( flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
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
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json 
											, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\"" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case '\\':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json 
											, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\\" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case '/':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json 
											, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "/" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case 'b':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json 
											, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\b" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case 'f':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json 
											, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\f" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case 'n':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json 
											, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\n" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case 'r':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json 
											, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\r" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								case 't':
									{
										::booldog::mem::insert< char >( ptr - parentserializator->slow.json - 1 , parentserializator->slow.json 
											, parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize , 2 , "\t" , 1 );
										parentserializator->slow.jsonlen--;
										diff--;
										break;
									}
								}
							}
						}
					}
					if( diff != 0 )
					{
						parentserializator->slow.nodes[ 0 ].jsonoffset( diff , valueend );
						parentserializator->slow.nodes[ 0 ].valueend += diff;
					}
					::booldog::utils::unset_bit( flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED );
				}
				return name_or_valuebegin;
			};
			object::object( ::booldog::data::json::node* srcnode )
			{
				json.node = srcnode;
				if( json.node )
				{
					if( ::booldog::utils::get_bit( json.node->flags , BOOLDOG_DATA_JSON_ROOT ) )
						json.parentserializator = json.node->serializator;
					else
					{
						::booldog::data::json::node* pparent = json.node->parent;						
						for( ; ; )
						{
							if( ::booldog::utils::get_bit( pparent->flags	, BOOLDOG_DATA_JSON_ROOT ) )
							{
								json.parentserializator = pparent->serializator;
								break;
							}
							pparent = pparent->parent;
						}
					}
					json.nodes = json.parentserializator->slow.nodes;
				}
			};
			bool node::isstring( void )
			{
				return this->type == ::booldog::enums::data::json::string;
			};
			bool node::isnumber( void )
			{
				return this->type == ::booldog::enums::data::json::number;
			};
			bool node::isnegativenumber( void )
			{
				if( this->type != ::booldog::enums::data::json::number )
					return false;
				char* ptr = this->name_or_valuebegin;
				if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_ROOT ) == 0
					&& this->parent->type == ::booldog::enums::data::json::object )
				{
					ptr--;
					if( ::booldog::utils::get_bit( this->flags , BOOLDOG_DATA_JSON_NAME_SERIALIZED ) )
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
					return true;
				return false;
			};
			bool node::isnull( void )
			{
				return this->type == ::booldog::enums::data::json::null;
			};
			bool node::isboolean( void )
			{
				return ( this->type == ::booldog::enums::data::json::boolean_true
					|| this->type == ::booldog::enums::data::json::boolean_false );
			};
			bool node::isobject( void )
			{
				return this->type == ::booldog::enums::data::json::object;
			};
			bool node::isarray( void )
			{
				return this->type == ::booldog::enums::data::json::array;
			};
			size_t node::count( void )
			{
				if( ( this->type == ::booldog::enums::data::json::array
					|| this->type == ::booldog::enums::data::json::object ) )
				{
					size_t count = 0;
					::booldog::data::json::node* pnext = this->child;
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
			booinline bool object::isstring( void )
			{
				if( json.node )
				{
					::booldog::data::json::checknode( &json );
					return json.node->type == ::booldog::enums::data::json::string;
				}
				return false;
			};
			booinline bool object::isnegativenumber( void )
			{
				if( json.node )
					::booldog::data::json::checknode( &json );
				else
					return false;
				return json.node->isnegativenumber();
			};
			booinline bool object::isnumber( void )
			{
				if( json.node )
				{
					::booldog::data::json::checknode( &json );
					return json.node->type == ::booldog::enums::data::json::number;
				}
				return false;
			};
			booinline bool object::isnull( void )
			{
				if( json.node )
				{
					::booldog::data::json::checknode( &json );
					return json.node->type == ::booldog::enums::data::json::null;
				}
				return false;
			};
			booinline bool object::isboolean( void )
			{
				if( json.node )
				{
					::booldog::data::json::checknode( &json );
					return ( json.node->type == ::booldog::enums::data::json::boolean_true
						|| json.node->type == ::booldog::enums::data::json::boolean_false );
				}
				return false;
			};
			booinline bool object::isobject( void )
			{
				if( json.node )
				{
					::booldog::data::json::checknode( &json );
					return json.node->type == ::booldog::enums::data::json::object;
				}
				return false;
			};
			booinline bool object::isarray( void )
			{
				if( json.node )
				{
					::booldog::data::json::checknode( &json );
					return json.node->type == ::booldog::enums::data::json::array;
				}
				return false;
			};
			booinline size_t object::count( void )
			{
				if( json.node )
				{
					::booldog::data::json::checknode( &json );
					return json.node->count();
				}
				return 0;
			};
			booinline bool operator==( const ::booldog::data::json::object& lhs , const ::booldog::data::json::object& rhs )
			{ 
				return lhs.json.node == rhs.json.node;
			};
			booinline bool operator!=( const ::booldog::data::json::object& lhs, const ::booldog::data::json::object& rhs)
			{
				return lhs.json.node != rhs.json.node;
			};
			::booldog::data::json::object object::operator[]( size_t index )
			{
				if( json.node )
				{
					::booldog::data::json::checknode( &json );
					if( ( json.node->type == ::booldog::enums::data::json::array 
						|| json.node->type == ::booldog::enums::data::json::object ) )
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
				}
				return ::booldog::data::json::object();
			};
			::booldog::data::json::object& object::operator++()
			{
				if( json.node )
				{
					::booldog::data::json::checknode( &json );
					if( ::booldog::utils::get_bit( json.node->flags , BOOLDOG_DATA_JSON_ROOT )
						|| ( json.node->parent->type != ::booldog::enums::data::json::object
						&& json.node->parent->type != ::booldog::enums::data::json::array ) )
						json.node = 0;
					else
						json.node = json.node->next;
				}
				return *this;
			};
			::booldog::data::json::object object::operator++(int)
			{
				::booldog::data::json::object copy( json.node );
				++*this;
				return copy;
			};
			::booldog::data::json::object object::operator()( const char* utf8name )
			{
				if( json.node )
				{
					::booldog::data::json::checknode( &json );
					if( utf8name && json.node->type == ::booldog::enums::data::json::object )
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
				}
				return ::booldog::data::json::object();
			};
			::booldog::data::json::object object::operator()( ::booldog::uint64 utf8namehash )
			{
				if( json.node )
				{
					::booldog::data::json::checknode( &json );
					if( json.node->type == ::booldog::enums::data::json::object )
					{
						::booldog::data::json::node* pnext = json.node->child;
						for( ; ; )
						{
							if( pnext == 0 )
								break;
							if( pnext->namehash == utf8namehash )
								return ::booldog::data::json::object( pnext );
							pnext = pnext->next;
						}
					}
				}
				return ::booldog::data::json::object();
			};
			template< size_t step >
			booinline ::booldog::data::json::object object::add( ::booldog::result* pres , const char* utf8name , bool value
				, const ::booldog::debug::info& debuginfo )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				if( json.node )
				{
					::booldog::data::json::checknode( &json );

					::booldog::data::json::node* newnode = 0;
					::booldog::uint64 newutf8namehash = 0;
				
					char* end = 0;
					::booldog::data::json::serializator* parentserializator = 0;
					::booldog::data::json::node* pparent = 0;
					::booldog::byte* ptrbyte = (::booldog::byte*)utf8name;

					size_t size = 0;
					if( json.node->type != ::booldog::enums::data::json::object )
					{
						pres->booerr( ::booldog::enums::result::booerr_type_json_parent_is_not_object );
						goto goto_return;
					}
					for( ; ; )
					{
						switch( *ptrbyte )
						{
						case 0:
							ptrbyte++;
							goto goto_next;
						default:
							{
								newutf8namehash = newutf8namehash * 33 + *ptrbyte;
								if( *ptrbyte <= 0x7f )
								{
								}
								else if( (*ptrbyte >> 5 ) == 0x6 )
								{
									ptrbyte++;
									if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
										goto goto_return;
									}
									newutf8namehash = newutf8namehash * 33 + *ptrbyte;
								}
								/* three byte */
								else if( ( *ptrbyte >> 4 ) == 0x0e ) 
								{
									ptrbyte++;
									if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
										goto goto_return;
									}
									newutf8namehash = newutf8namehash * 33 + *ptrbyte;
									ptrbyte++;
									if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
										goto goto_return;
									}
									newutf8namehash = newutf8namehash * 33 + *ptrbyte;
								}
								/* four byte */        
								else if( ( *ptrbyte >> 3 ) == 0x1e )
								{
									ptrbyte++;
									if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
										goto goto_return;
									}
									newutf8namehash = newutf8namehash * 33 + *ptrbyte;
									ptrbyte++;
									if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
										goto goto_return;
									}
									newutf8namehash = newutf8namehash * 33 + *ptrbyte;
									ptrbyte++;
									if( !( ( *ptrbyte >> 6 ) == 0x2 ) )
									{
										res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
										goto goto_return;
									}
									newutf8namehash = newutf8namehash * 33 + *ptrbyte;
								}
								else
								{
									res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
									goto goto_return;
								}
								ptrbyte++;
								break;
							}
						}
					}
	goto_next:
					size = (char*)ptrbyte - utf8name + 2;
					if( json.node->child != 0 )
						size++;
					if( value )
						size += 4;
					else
						size += 5;

					pparent = json.node;
					for( ; ; )
					{
						if( ::booldog::utils::get_bit( pparent->flags , BOOLDOG_DATA_JSON_ROOT ) )
						{
							parentserializator = pparent->serializator;
							break;
						}
						pparent = pparent->parent;
					}

					if( parentserializator->slow.jsonlen + size + 1 > parentserializator->slow.jsonsize )
					{
						char* oldjsonstr = parentserializator->slow.json;
						parentserializator->slow.jsonsize = parentserializator->slow.jsonlen + size + 1 + step;
						parentserializator->slow.json = parentserializator->slow.jsonallocator->realloc_array< char >( 
							parentserializator->slow.json , parentserializator->slow.jsonsize , debuginfo );
						if( parentserializator->slow.json == 0 )
						{
							parentserializator->clear();
							res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
							goto goto_return;
						}
						else if( parentserializator->slow.json != oldjsonstr )
						{
							parentserializator->slow.nodes[ 0 ].newjsonptr( oldjsonstr , parentserializator->slow.json );
							parentserializator->slow.nodes[ 0 ].name_or_valuebegin = parentserializator->slow.json;
							parentserializator->slow.nodes[ 0 ].valueend = 
								parentserializator->slow.json + (
								parentserializator->slow.nodes[ 0 ].valueend - oldjsonstr );
						}
					}
					::booldog::mem::expand< char >( json.node->valueend - parentserializator->slow.json
						, parentserializator->slow.json , parentserializator->slow.jsonlen + 1 , parentserializator->slow.jsonsize
						, size );

					ptrbyte = (::booldog::byte*)json.node->valueend;
					if( json.node->child )
						*ptrbyte++ = ',';
					*ptrbyte++ = '"';
					for( ; ; )
					{
						switch( *utf8name )
						{
						case 0:
							goto goto_next1;
						default:
							*ptrbyte++ = *utf8name++;
							break;
						}
					}
	goto_next1:
					*ptrbyte++ = 0;
					*ptrbyte++ = ':';
					if( value )
					{
						*ptrbyte++ = 't';
						*ptrbyte++ = 'r';
						*ptrbyte++ = 'u';
						*ptrbyte = 'e';
					}
					else
					{
						*ptrbyte++ = 'f';
						*ptrbyte++ = 'a';
						*ptrbyte++ = 'l';
						*ptrbyte++ = 's';
						*ptrbyte = 'e';
					}				
					end = json.node->valueend;
					parentserializator->slow.jsonlen += size;
					parentserializator->slow.nodes[ 0 ].jsonoffset( (int)size , json.node->valueend );
					parentserializator->slow.nodes[ 0 ].valueend += size;

					newnode = ::booldog::data::json::newnode< step >( res , parentserializator , json.node , debuginfo );
					if( newnode )
					{
						if( value )
							newnode->type = ::booldog::enums::data::json::boolean_true;
						else
							newnode->type = ::booldog::enums::data::json::boolean_false;
						if( json.node->child )
						{
							newnode->name_or_valuebegin = end + 2;
							::booldog::data::json::node* prev = json.node->child;
							while( prev->next )
								prev = prev->next;
							prev->next = newnode;
						}
						else
						{
							newnode->name_or_valuebegin = end + 1;
							json.node->child = newnode;
						}
						newnode->namehash = newutf8namehash;					
						newnode->flags = 0;
						newnode->parent = json.node;
						newnode->valueend = (char*)ptrbyte;
						newnode->next = 0;
						newnode->child = 0;
					}
					else
					{
						parentserializator->clear();
						goto goto_return;
					}
	goto_return:
					return ::booldog::data::json::object( newnode );
				}
				else
					res->booerr( ::booldog::enums::result::booerr_type_json_object_has_not_node );
				return ::booldog::data::json::object();
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
					_obj_->serializator->clear();
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
			::booldog::data::json::serializator& serializator::operator = ( const ::booldog::data::json::serializator& obj )
			{
				if( this == &obj )
					return *this;
				if( obj.slow.jsonlen + 1 > slow.jsonsize )
				{
					slow.jsonsize = obj.slow.jsonlen + 1;
					slow.json = slow.jsonallocator->realloc_array< char >( slow.json , slow.jsonsize , debuginfo_macros );
					if( slow.json == 0 )
					{
						clear();
						return *this;
					}
				}
				if( obj.slow.jsonlen )
				{
					slow.jsonlen = obj.slow.jsonlen;
					::memcpy( slow.json , obj.slow.json , obj.slow.jsonlen + 1 );
				}
				else
				{
					slow.jsonlen = 0;
					if( slow.json )
						slow.json[ 0 ] = 0;
				}
				if( obj.slow.nodessize > slow.nodessize )
				{
					slow.nodessize = obj.slow.nodessize;
					slow.nodes = slow.jsonallocator->realloc_array< ::booldog::data::json::node >( slow.nodes , slow.nodessize 
						, debuginfo_macros );
					if( slow.nodes == 0 )
					{
						clear();
						return *this;
					}
				}
				if( obj.slow.nodesindex )
				{
					slow.nodesindex = obj.slow.nodesindex;
					char* nodesptr = (char*)obj.slow.nodes;
					size_t size = 0;
					::memcpy( slow.nodes , obj.slow.nodes , obj.slow.nodessize * sizeof( ::booldog::data::json::node ) );
					for( size_t index0 = 0 ; index0 < slow.nodessize ; index0++ )
					{
						if( slow.nodes[ index0 ].next )
						{
							size = ((char*)slow.nodes[ index0 ].next) - nodesptr;
							slow.nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)slow.nodes) + size);
						}
						if( ::booldog::utils::get_bit( slow.nodes[ index0 ].flags
							, BOOLDOG_DATA_JSON_ROOT ) == 0 )
						{
							size = ((char*)slow.nodes[ index0 ].parent) - nodesptr;
							slow.nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)slow.nodes) + size);
						}
						else
							slow.nodes[ index0 ].serializator = this;
						if( slow.nodes[ index0 ].child )
						{
							size = ((char*)slow.nodes[ index0 ].child) - nodesptr;
							slow.nodes[ index0 ].child = (::booldog::data::json::node*)(((char*)slow.nodes) + size);
						}
					}
					slow.nodes[ 0 ].newjsonptr( obj.slow.json , slow.json );
					slow.nodes[ 0 ].name_or_valuebegin = slow.json;
					slow.nodes[ 0 ].valueend = slow.json + ( obj.slow.nodes[ 0 ].valueend - obj.slow.json );
				}
				else
					slow.nodesindex = 0;
				return *this;
			};
			template< class T >
			booinline void checknode( T* nodeholder )
			{
				if( nodeholder->parentserializator->slow.nodes > nodeholder->node 
					|| ( nodeholder->parentserializator->slow.nodes + nodeholder->parentserializator->slow.nodessize - 1 ) 
						< nodeholder->node )
				{
					nodeholder->node = nodeholder->parentserializator->slow.nodes + ( nodeholder->node - nodeholder->nodes );
					nodeholder->nodes = nodeholder->parentserializator->slow.nodes;
				}
			};
			template< size_t step >
			booinline ::booldog::data::json::node* newnode( ::booldog::result* res 
				, ::booldog::data::json::serializator* serializer , ::booldog::data::json::node*& curnode 
				, ::booldog::data::json::node*& parentnode , size_t& size , const ::booldog::debug::info& debuginfo )
			{
				::booldog::data::json::node* node = 0;
				if( serializer->slow.nodesindex >= serializer->slow.nodessize )
				{
					serializer->slow.nodessize += step;
					char* nodesptr = (char*)serializer->slow.nodes;
					serializer->slow.nodes = serializer->slow.jsonallocator->realloc_array< ::booldog::data::json::node >( 
						serializer->slow.nodes , serializer->slow.nodessize , debuginfo );
					if( serializer->slow.nodes == 0 )
					{
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						return 0;
					}
					for( size_t index0 = serializer->slow.nodesindex ; index0 < serializer->slow.nodessize ; index0++ )
						serializer->slow.nodes[ index0 ].flags = ::booldog::utils::bits::compile::number_from_bit_index< 
							::booldog::byte , BOOLDOG_DATA_JSON_NODE_FREE >::value;
					if( (char*)serializer->slow.nodes != nodesptr )
					{
						if( curnode )
						{
							size = ((char*)curnode) - nodesptr;
							curnode = (::booldog::data::json::node*)(((char*)serializer->slow.nodes) + size);
						}
						if( parentnode )
						{
							size = ((char*)parentnode) - nodesptr;
							parentnode = (::booldog::data::json::node*)(((char*)serializer->slow.nodes) + size);
						}
						for( size_t index0 = 0 ; index0 < serializer->slow.nodessize ; index0++ )
						{
							if( ::booldog::utils::get_bit( serializer->slow.nodes[ index0 ].flags
								, BOOLDOG_DATA_JSON_NODE_FREE ) )
							{
								if( node == 0 )
									node = &serializer->slow.nodes[ index0 ];
								continue;
							}
							if( serializer->slow.nodes[ index0 ].next )
							{
								size = ((char*)serializer->slow.nodes[ index0 ].next) - nodesptr;
								serializer->slow.nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)serializer->slow.nodes) + size);
							}
							if( ::booldog::utils::get_bit( serializer->slow.nodes[ index0 ].flags
								, BOOLDOG_DATA_JSON_ROOT ) == 0 )
							{
								size = ((char*)serializer->slow.nodes[ index0 ].parent) - nodesptr;
								serializer->slow.nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)serializer->slow.nodes) + size);
							}
							if( serializer->slow.nodes[ index0 ].child )
							{
								size = ((char*)serializer->slow.nodes[ index0 ].child) - nodesptr;
								serializer->slow.nodes[ index0 ].child = (::booldog::data::json::node*)(((char*)serializer->slow.nodes) + size);
							}
						}
					}
				}
				if( node == 0 )
				{
					for( size_t index0 = 0 ; index0 < serializer->slow.nodessize ; index0++ )
					{
						if( ::booldog::utils::get_bit( serializer->slow.nodes[ index0 ].flags
							, BOOLDOG_DATA_JSON_NODE_FREE ) )
						{
							node = &serializer->slow.nodes[ index0 ];
							break;
						}
					}
				}
				serializer->slow.nodesindex++;
				return node;
			};
			template< size_t step >
			booinline ::booldog::data::json::node* newnode( ::booldog::result* res 
				, ::booldog::data::json::serializator* serializer , ::booldog::data::json::node*& curnode
				, const ::booldog::debug::info& debuginfo )
			{
				size_t size = 0;
				::booldog::data::json::node* node = 0;
				if( serializer->slow.nodesindex >= serializer->slow.nodessize )
				{
					serializer->slow.nodessize += step;
					char* nodesptr = (char*)serializer->slow.nodes;
					serializer->slow.nodes = serializer->slow.jsonallocator->realloc_array< ::booldog::data::json::node >( 
						serializer->slow.nodes , serializer->slow.nodessize , debuginfo );
					if( serializer->slow.nodes == 0 )
					{
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						return 0;
					}
					for( size_t index0 = serializer->slow.nodesindex ; index0 < serializer->slow.nodessize ; index0++ )
						serializer->slow.nodes[ index0 ].flags = ::booldog::utils::bits::compile::number_from_bit_index< 
							::booldog::byte , BOOLDOG_DATA_JSON_NODE_FREE >::value;
					if( (char*)serializer->slow.nodes != nodesptr )
					{
						if( curnode )
						{
							size = ((char*)curnode) - nodesptr;
							curnode = (::booldog::data::json::node*)(((char*)serializer->slow.nodes) + size);
						}
						for( size_t index0 = 0 ; index0 < serializer->slow.nodessize ; index0++ )
						{
							if( ::booldog::utils::get_bit( serializer->slow.nodes[ index0 ].flags
								, BOOLDOG_DATA_JSON_NODE_FREE ) )
							{
								if( node == 0 )
									node = &serializer->slow.nodes[ index0 ];
								continue;
							}
							if( serializer->slow.nodes[ index0 ].next )
							{
								size = ((char*)serializer->slow.nodes[ index0 ].next) - nodesptr;
								serializer->slow.nodes[ index0 ].next = (::booldog::data::json::node*)(((char*)serializer->slow.nodes) + size);
							}
							if( ::booldog::utils::get_bit( serializer->slow.nodes[ index0 ].flags
								, BOOLDOG_DATA_JSON_ROOT ) == 0 )
							{
								size = ((char*)serializer->slow.nodes[ index0 ].parent) - nodesptr;
								serializer->slow.nodes[ index0 ].parent = (::booldog::data::json::node*)(((char*)serializer->slow.nodes) + size);
							}
							if( serializer->slow.nodes[ index0 ].child )
							{
								size = ((char*)serializer->slow.nodes[ index0 ].child) - nodesptr;
								serializer->slow.nodes[ index0 ].child = (::booldog::data::json::node*)(((char*)serializer->slow.nodes) + size);
							}
						}
					}
				}
				if( node == 0 )
				{
					for( size_t index0 = 0 ; index0 < serializer->slow.nodessize ; index0++ )
					{
						if( ::booldog::utils::get_bit( serializer->slow.nodes[ index0 ].flags
							, BOOLDOG_DATA_JSON_NODE_FREE ) )
						{
							node = &serializer->slow.nodes[ index0 ];
							break;
						}
					}
				}
				serializer->slow.nodesindex++;
				return node;
			};
			template< size_t step >
			booinline bool serializator::parse( ::booldog::result* pres , const ::booldog::debug::info& debuginfo )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				
				size_t size = 0;
				::booldog::data::json::node* node = 0 , * curnode = 0 , * parentnode = 0;
					
				const char* ptr = slow.json;		
				const char* begin = 0 , * name_begin = 0 , * number_string_begin = 0;
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
					::booldog::mem::remove< char >( (size_t)( begin - slow.json ) , slow.json , slow.jsonsize
						, size );
					slow.jsonlen -= size;
					slow.json[ slow.jsonlen ] = 0;
					ptr = begin;
				}
				switch( *ptr )
				{
				case '[':
					{
						node = ::booldog::data::json::newnode< step >( res , this , curnode , parentnode , size , debuginfo );
						if( node == 0 )
							goto goto_return;
						node->type = ::booldog::enums::data::json::array;
						node->name_or_valuebegin = (char*)name_begin;
						node->namehash = name_hash;
						if( slow.nodesindex == 1 )
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED 
								, BOOLDOG_DATA_JSON_ROOT >::value;
							node->serializator = this;
						}
						else
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED >::value;
							node->parent = parentnode;
						}
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
						node = ::booldog::data::json::newnode< step >( res , this , curnode , parentnode , size , debuginfo );
						if( node == 0 )
							goto goto_return;			
						node->type = ::booldog::enums::data::json::object;
						node->name_or_valuebegin = (char*)name_begin;
						node->namehash = name_hash;
						if( slow.nodesindex == 1 )
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED 
								, BOOLDOG_DATA_JSON_ROOT >::value;
							node->serializator = this;
						}
						else
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED >::value;
							node->parent = parentnode;
						}
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
												clear();
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
												clear();
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
												clear();
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
												clear();
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
															clear();
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
															clear();
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
															clear();
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
															clear();
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
												::booldog::mem::insert< char >( begin - slow.json , slow.json 
													, slow.jsonlen + 1 , slow.jsonsize
													, size , utf8 , utf8bytes );
												slow.jsonlen -= size - utf8bytes;
												slow.json[ slow.jsonlen ] = 0;
												ptr = begin + utf8bytes;
											}
											else
											{
												clear();
												res->booerr( ::booldog::enums::result::booerr_type_json_cannot_convert_from_utf16_to_utf8 );
												goto goto_return;
											}
											break;
										}
									case 0:
										{
											clear();
											res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_end_of_string );
											goto goto_return;
										}
									default:
										{
											clear();
											res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_escaped_symbol );
											goto goto_return;
										}
									}
									break;
								}
							case 0:
								{
									clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_end_of_string );
									goto goto_return;
								}
							default:
								{
									ptr--;
									const ::booldog::byte* ptrbyte = (::booldog::byte*)ptr;
									if( ::booldog::utf8::validate_character( ptrbyte ) == false )
									{
										clear();
										res->booerr( ::booldog::enums::result::booerr_type_json_not_utf8_symbol );
										goto goto_return;
									}
									ptr = (char*)ptrbyte;
									break;
								}
							}
						}
	goto_object_name_parse_next1:
						node = ::booldog::data::json::newnode< step >( res , this , curnode , parentnode , size , debuginfo );
						if( node == 0 )
							goto goto_return;
														
						node->type = ::booldog::enums::data::json::string;
						node->name_or_valuebegin = (char*)name_begin;
						node->namehash = name_hash;
						if( slow.nodesindex == 1 )
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED 
								, BOOLDOG_DATA_JSON_ROOT >::value;
							node->serializator = this;
						}
						else
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED >::value;
							node->parent = parentnode;
						}
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
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_false );
							goto goto_return;
						}
						if( *++ptr != 'l' )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_false );
							goto goto_return;
						}
						if( *++ptr != 's' )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_false );
							goto goto_return;
						}
						if( *++ptr != 'e' )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_false );
							goto goto_return;
						}
						
						node = ::booldog::data::json::newnode< step >( res , this , curnode , parentnode , size , debuginfo );
						if( node == 0 )
							goto goto_return;
														
						node->type = ::booldog::enums::data::json::boolean_false;
						node->name_or_valuebegin = (char*)name_begin;
						node->namehash = name_hash;
						if( slow.nodesindex == 1 )
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED 
								, BOOLDOG_DATA_JSON_ROOT >::value;
							node->serializator = this;
						}
						else
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED >::value;
							node->parent = parentnode;
						}
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
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_true );
							goto goto_return;
						}
						if( *++ptr != 'u' )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_true );
							goto goto_return;
						}
						if( *++ptr != 'e' )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_true );
							goto goto_return;
						}
						
						node = ::booldog::data::json::newnode< step >( res , this , curnode , parentnode , size , debuginfo );
						if( node == 0 )
							goto goto_return;
														
						node->type = ::booldog::enums::data::json::boolean_true;
						node->name_or_valuebegin = (char*)name_begin;
						node->namehash = name_hash;
						if( slow.nodesindex == 1 )
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED 
								, BOOLDOG_DATA_JSON_ROOT >::value;
							node->serializator = this;
						}
						else
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED >::value;
							node->parent = parentnode;
						}
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
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_null );
							goto goto_return;
						}
						if( *++ptr != 'l' )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_null );
							goto goto_return;
						}
						if( *++ptr != 'l' )
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_null );
							goto goto_return;
						}

						node = ::booldog::data::json::newnode< step >( res , this , curnode , parentnode , size , debuginfo );
						if( node == 0 )
							goto goto_return;
														
						node->type = ::booldog::enums::data::json::null;
						node->name_or_valuebegin = (char*)name_begin;
						node->namehash = name_hash;
						if( slow.nodesindex == 1 )
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED 
								, BOOLDOG_DATA_JSON_ROOT >::value;
							node->serializator = this;
						}
						else
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED >::value;
							node->parent = parentnode;
						}
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
									clear();
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
									clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_minus_in_number );
									goto goto_return;
								}
							default:
								{
									if( begin == ptr - 1 && *begin == '-' )
									{
										clear();
										res->booerr( ::booldog::enums::result::booerr_type_json_expecting_digit_after_minus );
										goto goto_return;
									}
									goto goto_number_create;
								}
							}
						}
goto_float_parse:
						number_string_begin = ptr;
						for( ; ; )
						{
							switch( *++ptr )
							{
							case '.':
								{
									clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_second_decimal_point_in_number );
									goto goto_return;
								}
							case 'e':
							case 'E':
								{
									if( number_string_begin == ptr - 1 )
									{
										clear();
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
									clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_minus_in_number );
									goto goto_return;
								}
							default:
								{
									if( number_string_begin == ptr - 1 )
									{
										clear();
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
									clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_plus_in_number );
									goto goto_return;
								}
							case '-':
								{
									clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_minus_in_number );
									goto goto_return;
								}
							case '.':
								{
									clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_decimal_point_in_number );
									goto goto_return;
								}
							case 'e':
							case 'E':
								{
									clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_second_exponent_part_symbol_in_number );
									goto goto_return;
								}
							default:
								{
									if( number_string_begin == ptr - 1 )
									{
										clear();
										res->booerr( ::booldog::enums::result::booerr_type_json_expecting_digit_after_exponent_part_symbol );
										goto goto_return;
									}
									goto goto_number_create;
								}
							}
						}
goto_number_create:
						node = ::booldog::data::json::newnode< step >( res , this , curnode , parentnode , size , debuginfo );
						if( node == 0 )
							goto goto_return;
														
						node->type = ::booldog::enums::data::json::number;
						node->name_or_valuebegin = (char*)name_begin;
						node->namehash = name_hash;
						if( slow.nodesindex == 1 )
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED 
								, BOOLDOG_DATA_JSON_ROOT >::value;
							node->serializator = this;
						}
						else
						{
							node->flags = ::booldog::utils::bits::compile::number_from_bit_index< ::booldog::byte 
								, BOOLDOG_DATA_JSON_NAME_SERIALIZED , BOOLDOG_DATA_JSON_VALUE_SERIALIZED >::value;
							node->parent = parentnode;
						}
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
						clear();
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
					::booldog::mem::remove< char >( (size_t)( begin - slow.json ) , slow.json , slow.jsonsize
						, size );
					slow.jsonlen -= size;
					slow.json[ slow.jsonlen ] = 0;
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
							clear();
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
								clear();
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
							clear();
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
					::booldog::mem::remove< char >( (size_t)( begin - slow.json ) , slow.json , slow.jsonsize
						, size );
					slow.jsonlen -= size;
					slow.json[ slow.jsonlen ] = 0;
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
							clear();
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
						clear();
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
										clear();
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
										clear();
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
										clear();
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
										clear();
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
													clear();
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
													clear();
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
													clear();
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
													clear();
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
										::booldog::mem::insert< char >( begin - slow.json , slow.json 
											, slow.jsonlen + 1 , slow.jsonsize
											, size , utf8 , utf8bytes );
										slow.jsonlen -= size - utf8bytes;
										slow.json[ slow.jsonlen ] = 0;
										ptr = begin + utf8bytes;

										for( size_t index = 0 ; index < utf8bytes ; index++ )
											name_hash = name_hash * 33 + (::booldog::byte)utf8[ index ];
									}
									else
									{
										clear();
										res->booerr( ::booldog::enums::result::booerr_type_json_cannot_convert_from_utf16_to_utf8 );
										goto goto_return;
									}
									break;
								}
							case 0:
								{
									clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_end_of_string );
									goto goto_return;
								}
							default:
								{
									clear();
									res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_escaped_symbol );
									goto goto_return;
								}
							}
							break;
						}
					case 0:
						{
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_json_unexpected_end_of_string );
							goto goto_return;
						}
					default:
						{
							ptr--;
							const ::booldog::byte* ptrbyte = (::booldog::byte*)ptr;
							if( ::booldog::utf8::validate_character( ptrbyte ) == false )
							{
								clear();
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
					::booldog::mem::remove< char >( (size_t)( begin - slow.json ) , slow.json , slow.jsonsize
						, size );
					slow.jsonlen -= size;
					slow.json[ slow.jsonlen ] = 0;
					ptr = begin;
				}
				switch( *ptr++ )
				{
				case ':':
					goto goto_value_parse;
				default:
					{
						clear();
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
							clear();
							res->booerr( ::booldog::enums::result::booerr_type_json_expecting_end_of_string );
							goto goto_return;
						}
					}
				}
goto_go_away_from_ws4:
				if( ptr != begin )
				{
					size = ptr - begin;
					::booldog::mem::remove< char >( (size_t)( begin - slow.json ) , slow.json , slow.jsonsize
						, size );
					slow.jsonlen -= size;
					slow.json[ slow.jsonlen ] = 0;
				}
goto_return:
				return res->succeeded();
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
					res->serializator->slow.jsonlen = size - 1;
					if( size > res->serializator->slow.jsonsize )
					{
						res->serializator->slow.jsonsize = size;
						res->serializator->slow.json = res->serializator->slow.jsonallocator->realloc_array< char >( 
							res->serializator->slow.json , res->serializator->slow.jsonsize , debuginfo );
					}
					if( res->serializator->slow.json )
					{
						::memcpy( res->serializator->slow.json , js , res->serializator->slow.jsonlen );
						res->serializator->slow.json[ res->serializator->slow.jsonlen ] = 0;
					}
					else
					{
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						goto goto_return;
					}
					::booldog::result resres;
					if( res->serializator->parse< step >( &resres , debuginfo ) == false )
						res->copy( resres );
				}
				else
					res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
goto_return:
				return res->succeeded();
			};
		};
	};
};
#endif