#ifndef BOO_HASH_SHA1_H
#define BOO_HASH_SHA1_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_allocator.h)
#include BOOLDOG_HEADER(boo_result.h)
#include BOOLDOG_HEADER(boo_types.h)
#include BOOLDOG_HEADER(boo_error.h)

#include <stdarg.h>
namespace booldog
{
	namespace hash
	{
		namespace sha1
		{
			booinline void calculate_hash_step( const ::booldog::byte* message_part , ::booldog::uint64 message_offset 
				, ::booldog::uint64 message_size , ::booldog::uint64 message_padding , ::booldog::uint32 digest[ 5 ] )
			{
				::booldog::uint32 a = digest[ 0 ] , b = digest[ 1 ] , c = digest[ 2 ] , 
					d = digest[ 3 ] , e = digest[ 4 ];
				::booldog::uint32 w[ 80 ] = {0} , temp_uint32 = 0 , * w_ptr = NULL;
				::booldog::uint64 index1 = 0 , k = 0 , index2 = 0;
				for( index1 = 0 ; index1 < 16 ; index1++ )
				{		
					if( message_offset + k < message_size )
					{
						index2 = message_size - k - message_offset;
						if( index2 >= sizeof( ::booldog::uint32 ) )
						{
							temp_uint32 = *message_part++ << 24;
							temp_uint32 |= *message_part++ << 16;
							temp_uint32 |= *message_part++ << 8;
							temp_uint32 |= *message_part++;
						}
						else if( index2 == 3 )
						{
							temp_uint32 = *message_part++ << 24;
							temp_uint32 |= *message_part++ << 16;
							temp_uint32 |= *message_part++ << 8;
							temp_uint32 |= 0x80;
						}
						else if( index2 == 2 )
						{
							temp_uint32 = *message_part++ << 24;
							temp_uint32 |= *message_part++ << 16;
							temp_uint32 |= 0x80 << 8;
							temp_uint32 |= 0x00;
						}
						else if( index2 == 1 )
						{
							temp_uint32 = *message_part++ << 24;
							temp_uint32 |= 0x80 << 16;
							temp_uint32 |= 0x00 << 8;
							temp_uint32 |= 0x00;
						}
					}
					else if( message_offset + k == message_size )
					{
						temp_uint32 = static_cast< ::booldog::uint32 >( 0x80 << 24 );
						temp_uint32 |= 0x00 << 16;
						temp_uint32 |= 0x00 << 8;
						temp_uint32 |= 0x00;
					}
					else if( message_offset + k < message_size + message_padding )
						temp_uint32 = 0x00000000;
					else 
					{
						::booldog::uint64 message_bits_size = message_size * 8;
						::booldog::uint8* message_bits_ptr = (::booldog::uint8*)&message_bits_size;
						message_bits_ptr = &message_bits_ptr[ 7 - ( k - 56 ) ];
						temp_uint32 = *message_bits_ptr-- << 24;
						temp_uint32 |= *message_bits_ptr-- << 16;
						temp_uint32 |= *message_bits_ptr-- << 8;
						temp_uint32 |= *message_bits_ptr--;
					}
					w[ index1 ] = temp_uint32;
					k += sizeof( ::booldog::uint32 );
				}
				w_ptr = &w[ 16 ];
				for( index1 = 16 ; index1 < 80 ; index1++ )
				{			
					*w_ptr = ( w[ index1 - 3 ] ^ w[ index1 - 8 ] ^ w[ index1 - 14 ] ^ w[ index1 - 16 ] );
					*w_ptr++ = ( ( *w_ptr ) << 1 ) | ( ( *w_ptr ) >> 31 );//циклический сдвиг
				}
				w_ptr = w;
				for( index1 = 0 ; index1 < 20 ; index1++ )
				{			
					k = (::booldog::uint32)( ( ( a << 5 ) | ( a >> 27 ) ) + ( ( b & c ) | ( (~ b) & d ) ) + e + 0x5A827999
						+ *w_ptr++ ); //a = ( a << 5 ) | ( a >> 27 );
					e = d;
					d = c;
					c = ( b << 30 ) | ( b >> 2 );
					b = a;
					a = static_cast< ::booldog::uint32 >( k );
				}
				for( ; index1 < 40 ; index1++ )
				{			
					k = (::booldog::uint32)( ( a << 5 ) | ( a >> 27 ) ) + ( b ^ c ^ d ) + e + 0x6ED9EBA1 + *w_ptr++;
					e = d;
					d = c;
					c = ( b << 30 ) | ( b >> 2 );
					b = a;
					a = static_cast< ::booldog::uint32 >( k );
				}
				for( ; index1 < 60 ; index1++ )
				{			
					k = (::booldog::uint32)( ( a << 5 ) | ( a >> 27 ) ) + ( (b & c) | (b & d) | (c & d) ) + e + 0x8F1BBCDC
						+ *w_ptr++;
					e = d;
					d = c;
					c = ( b << 30 ) | ( b >> 2 );
					b = a;
					a = static_cast< ::booldog::uint32 >( k );
				}
				for( ; index1 < 80 ; index1++ )
				{			
					k = (::booldog::uint32)( ( a << 5 ) | ( a >> 27 ) ) + ( b ^ c ^ d ) + e + 0xCA62C1D6 + *w_ptr++;
					e = d;
					d = c;
					c = ( b << 30 ) | ( b >> 2 );
					b = a;
					a = static_cast< ::booldog::uint32 >( k );
				}			
				digest[ 0 ] += a;
				digest[ 1 ] += b; 
				digest[ 2 ] += c;
				digest[ 3 ] += d;
				digest[ 4 ] += e;
			};
			booinline bool calculate( ::booldog::result_buffer* pres , booldog::allocator* allocator 
				, const ::booldog::byte* message_ptr , ::booldog::uint64 message_size 
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result_buffer locres( allocator );
				BOOINIT_RESULT( ::booldog::result_buffer );
				::booldog::uint32 digest[ 5 ] = {0};
				::booldog::uint64 message_padding = 0;	
				if( res->bufsize < 20 )
				{
					res->bufsize = 20;
					res->buf = res->allocator->realloc_array< unsigned char >( res->buf , res->bufsize , debuginfo );
					if( res->buf == 0 )
					{
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						goto goto_return;
					}
				}
				if( message_size < 56 )		//448 bits
					message_padding = 56 - message_size;
				else if( message_size < 64 )		
					message_padding = 120 - message_size;//960 bits		
				else
				{
					::booldog::uint32 remainder = message_size % 64;//512 bits			
					if( remainder > 55 )//440 bits			
						message_padding = 120 - remainder;
					else			
						message_padding = 56 - remainder;
				}
				digest[ 0 ] = 0x67452301;
				digest[ 1 ] = 0xEFCDAB89;
				digest[ 2 ] = 0x98BADCFE;
				digest[ 3 ] = 0x10325476;
				digest[ 4 ] = 0xC3D2E1F0;
				for( ::booldog::uint64 index0 = 0 ; index0 < message_size + message_padding + 8 ; index0 += 64 )
					::booldog::hash::sha1::calculate_hash_step( &message_ptr[ index0 ] , index0 , message_size , message_padding 
					, digest );
				for( ::booldog::int32 index0 = 0; index0 < 20; ++index0 )		
					res->buf[ index0 ] = static_cast< ::booldog::uint8 >( digest[ index0 >> 2 ] >> 8 * ( 3 - ( index0 & 0x03 ) ) );
				res->bufdatasize = 20;
goto_return:
				return res->succeeded();
			};
			/*booinline ::booldog::uint64 calculate( size_t count , va_list ap )
			{
				::booldog::uint64 hash = 0;
				const ::booldog::byte* ptr = 0;
				for( size_t index0 = 0 ; index0 < count ; index0++ )
				{
					ptr = (const ::booldog::uint8*)va_arg( ap , char* );
					for( ; *ptr ; ptr++ )
						hash = hash * 33 + *ptr;
				}
				return hash;
			};
			booinline ::booldog::uint64 calculate( size_t count , ... )
			{
				va_list ap;
				va_start( ap , count );
				::booldog::uint64 hash = calculate( count , ap );
				va_end( ap );
				return hash;
			};*/
		};
	};
};

#endif
