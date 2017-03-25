#ifndef BOO_BASE64_H
#define BOO_BASE64_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_allocator.h"
#include "boo_result.h"
#include "boo_types.h"
#include "boo_error.h"
namespace booldog
{
	namespace data
	{
		namespace base64
		{
			const ::booldog::byte encode_6_to_8[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
			const ::booldog::byte web_encode_6_to_8[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
			booinline ::booldog::byte encode_8_to_6( ::booldog::uint8 symbol )
			{
				if( 'A' <= symbol && symbol <= 'Z' )
					return symbol - 'A';
				else if( 'a' <= symbol && symbol <= 'z' )
					return ( 'Z' - 'A' + 1 ) + symbol - 'a';
				else if( '0' <= symbol && symbol <= '9' )
					return 2 * ( 'Z' - 'A' + 1 ) + symbol - '0';
				else if( symbol == '-' )
					return 62;
				else if( symbol == '_' )
					return 63;
				else if( symbol == '+' )
					return 62;
				else if( symbol == '/' )
					return 63;
				return 0;
			};
			booinline size_t encoded_size( size_t decoded_data_ptr_size , bool padding )
			{
				if( padding )
				{
					if( decoded_data_ptr_size % 3 )
						return ( ( decoded_data_ptr_size / 3 ) + 1 ) * 4;
					else
						return decoded_data_ptr_size / 3 * 4;
				}
				else
				{
					switch( decoded_data_ptr_size % 3 )
					{
					case 1:
						return decoded_data_ptr_size / 3 * 4 + 2;
					case 2:
						return decoded_data_ptr_size / 3 * 4 + 3;
					default:
						return decoded_data_ptr_size / 3 * 4;
					}
				}
			};
			booinline size_t decoded_size( const char* encoded_data , size_t size , size_t& actual_size )
			{
				if( size == 0 )
					size = encoded_data ? strlen( encoded_data ) : 0;
				actual_size = size;
				if( actual_size > 0 && encoded_data[ actual_size - 1 ] == '=' )
					actual_size--;
				if( actual_size > 0 && encoded_data[ actual_size - 1 ] == '=' )
					actual_size--;
				switch( actual_size % 4 )
				{
				case 1:
					return SIZE_MAX;
				case 2:
					return actual_size / 4 * 3 + 1;
				case 3:
					return actual_size / 4 * 3 + 2;
				default:
					return actual_size / 4 * 3;
				}
			};
			booinline bool decode( ::booldog::result_buffer* pres , booldog::allocator* allocator , const char* src 
				, size_t srccharindex = 0 , size_t srccharcount = SIZE_MAX 
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result_buffer locres( allocator );
				BOOINIT_RESULT( ::booldog::result_buffer );
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
						srccharcount = ptr - srcbegin - 1;

						size_t actual_size = 0;
						size_t decoded_data_ptr_size2 = ::booldog::data::base64::decoded_size( srcbegin , srccharcount
							, actual_size );
						if( decoded_data_ptr_size2 != SIZE_MAX )
						{
							if( decoded_data_ptr_size2 > 0 )
							{
								if( res->bufsize < decoded_data_ptr_size2 )
								{
									res->bufsize = decoded_data_ptr_size2;
									res->buf = res->allocator->realloc_array< unsigned char >( res->buf , res->bufsize 
										, debuginfo );
									if( res->buf == 0 )
									{
										res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
										goto goto_return;
									}
								}
								res->bufdatasize = decoded_data_ptr_size2;

								::booldog::uint8* begin_ptr = (::booldog::uint8*)srcbegin;
								::booldog::uint8* end_ptr = begin_ptr + actual_size;
								::booldog::uint8* ptr_ptr = res->buf;
								::booldog::uint8 in[ 4 ] = { 0 };
								while( end_ptr - begin_ptr >= 4 ) 
								{
									for( size_t index0 = 0 ; index0 < 4 ; index0++ )
										in[ index0 ] = encode_8_to_6( begin_ptr[ index0 ] );
									ptr_ptr[ 0 ] = (::booldog::uint8)( in[ 0 ] << 2 | in[ 1 ] >> 4 );
									ptr_ptr[ 1 ] = (::booldog::uint8)( in[ 1 ] << 4 | in[ 2 ] >> 2 );
									ptr_ptr[ 2 ] = (::booldog::uint8)( ( ( in[ 2 ] << 6 ) & 0xc0 ) | in[ 3 ] );
									begin_ptr += 4;
									ptr_ptr += 3;
								}
								if( end_ptr != begin_ptr )
								{
									size_t length = end_ptr - begin_ptr;
									for( size_t index0 = 0 ; index0 < length ; index0++ )
										in[ index0 ] = encode_8_to_6( begin_ptr[ index0 ] );
									ptr_ptr[ 0 ] = (::booldog::uint8)( in[ 0 ] << 2 | in[ 1 ] >> 4 );
									if( length > 2 )
									{
										ptr_ptr[ 1 ] = (::booldog::uint8)( in[ 1 ] << 4 | in[ 2 ] >> 2 );
										if( length > 3 )
											ptr_ptr[ 2 ] = (::booldog::uint8)( ( ( in[ 2 ] << 6 ) & 0xc0 ) | in[ 3 ] );
									}
								}
							}
							else
								res->booerr( ::booldog::enums::result::booerr_type_base64_decoded_length_is_equal_0 );
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_base64_incorrect_encoded_length );
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
				}
				else
					res->booerr( ::booldog::enums::result::booerr_type_string_parameter_is_empty );
goto_return:
				return res->succeeded();
			};
			booinline bool encode( ::booldog::result_mbchar* pres , booldog::allocator* allocator
				, ::booldog::byte* decoded_data_ptr , size_t decoded_data_ptr_size , bool web , bool padding 
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result_mbchar locres( allocator );
				BOOINIT_RESULT( ::booldog::result_mbchar );
				if( decoded_data_ptr )
				{
					if( decoded_data_ptr_size > 0 )
					{
						size_t encoded_data_ptr_size = encoded_size( decoded_data_ptr_size , padding );
						if( encoded_data_ptr_size > 0 )
						{
							::booldog::uint8* begin_ptr = decoded_data_ptr;
							::booldog::uint8* end_ptr = decoded_data_ptr + decoded_data_ptr_size;

							res->mblen = encoded_data_ptr_size;
							if( res->mbsize < res->mblen + 1 )
							{
								res->mbsize = res->mblen + 1;
								res->mbchar = res->mballocator->realloc_array< char >( res->mbchar , res->mbsize 
									, debuginfo );
								if( res->mbchar == 0 )
								{
									res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
									goto goto_return;
								}
							}
							::booldog::uint8* out_ptr = (::booldog::uint8*)res->mbchar;
							const ::booldog::byte* encode_6_to_8_ptr = encode_6_to_8;
							if( web )
								encode_6_to_8_ptr = web_encode_6_to_8;
							while( end_ptr - begin_ptr >= 3 )
							{
								out_ptr[0] = encode_6_to_8_ptr[ begin_ptr[0] >> 2];
								out_ptr[1] = encode_6_to_8_ptr[((begin_ptr[0] & 0x03) << 4) | ((begin_ptr[1] & 0xf0) >> 4)];
								out_ptr[2] = encode_6_to_8_ptr[((begin_ptr[1] & 0x0f) << 2) | ((begin_ptr[2] & 0xc0) >> 6)];
								out_ptr[3] = encode_6_to_8_ptr[begin_ptr[2] & 0x3f];
								begin_ptr += 3;
								out_ptr += 4;
							}
							if( end_ptr != begin_ptr )
							{
								size_t length = end_ptr - begin_ptr;		
								out_ptr[ 0 ] = encode_6_to_8_ptr[ begin_ptr[ 0 ] >> 2 ];
								if( length == 1 )
								{
									out_ptr[ 1 ] = encode_6_to_8_ptr[ ( begin_ptr[ 0 ] & 0x03 ) << 4 ];
									if( padding )
									{
										out_ptr[ 2 ] = '=';
										out_ptr[ 3 ] = '=';
									}
								}
								else 
								{
									out_ptr[ 1 ] = encode_6_to_8_ptr[ ( ( begin_ptr[ 0 ] & 0x03 ) << 4 ) 
										| ( ( begin_ptr[ 1 ] & 0xf0 ) >> 4 ) ];
									out_ptr[ 2 ] = encode_6_to_8_ptr[ ( begin_ptr[ 1 ] & 0x0f ) << 2 ];
									if( padding )
										out_ptr[ 3 ] = '=';
								}
							}
							res->mbchar[ res->mblen ] = 0;
						}
						else
							res->booerr( ::booldog::enums::result::booerr_type_base64_encoded_data_pointer_size_is_equal_0 );
					}
					else
						res->booerr( ::booldog::enums::result::booerr_type_base64_decoded_data_pointer_size_is_equal_0 );
				}
				else
					res->booerr( ::booldog::enums::result::booerr_type_base64_decoded_data_pointer_is_NULL );
goto_return:
				return res->succeeded();
			};
		};
	};
};

#endif
