#ifndef BOO_HASH_MD5_H
#define BOO_HASH_MD5_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_allocator.h"
#include "boo_result.h"
#include "boo_types.h"
#include "boo_error.h"

#include <stdarg.h>
namespace booldog
{
	namespace hash
	{
		namespace md5
		{
			booinline bool calculate( ::booldog::result_buffer* pres , booldog::allocator* allocator 
				, const ::booldog::byte* message_ptr , ::booldog::uint64 message_ptr_size 
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result_buffer locres( allocator );
				BOOINIT_RESULT( ::booldog::result_buffer );
				
				::booldog::uint32 padding_length = 0;
				::booldog::uint8 message_length_ptr[ 8 ] = {0};

				::booldog::uint32 a = 0x67452301;
				::booldog::uint32 b = 0xefcdab89;
				::booldog::uint32 c = 0x98badcfe;
				::booldog::uint32 d = 0x10325476;
				::booldog::uint32 aa = 0x67452301;
				::booldog::uint32 bb = 0xefcdab89;
				::booldog::uint32 cc = 0x98badcfe;
				::booldog::uint32 dd = 0x10325476;
				::booldog::uint32 index1 = 0;
				::booldog::uint32 x = 0;

				if( res->bufsize < 16 )
				{
					res->bufsize = 16;
					res->buf = res->allocator->realloc_array< unsigned char >( res->buf , res->bufsize , debuginfo );
					if( res->buf == 0 )
					{
						res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
						goto goto_return;
					}
				}

				if( message_ptr_size < 56 )		//448 bits
					padding_length = 56 - static_cast< ::booldog::uint32 >( message_ptr_size );
				else if( message_ptr_size < 64 )		
					padding_length = 120 - static_cast< ::booldog::uint32 >( message_ptr_size );//960 bits		
				else
				{
					::booldog::uint32 remainder = message_ptr_size % 64;//512 bits			
					if( remainder > 55 )//440 bits			
						padding_length = 120 - remainder;
					else			
						padding_length = 56 - remainder;
				}
				message_ptr_size *= 8;
				message_length_ptr[ 0 ] = (::booldog::byte)( message_ptr_size & 0xff );
				message_length_ptr[ 1 ] = (::booldog::byte)( ( message_ptr_size >> 8 ) & 0xff );
				message_length_ptr[ 2 ] = (::booldog::byte)( ( message_ptr_size >> 16 ) & 0xff );
				message_length_ptr[ 3 ] = (::booldog::byte)( ( message_ptr_size >> 24 ) & 0xff );
				message_length_ptr[ 4 ] = (::booldog::byte)( ( message_ptr_size >> 32 ) & 0xff );
				message_length_ptr[ 5 ] = (::booldog::byte)( ( message_ptr_size >> 40 ) & 0xff );
				message_length_ptr[ 6 ] = (::booldog::byte)( ( message_ptr_size >> 48 ) & 0xff );
				message_length_ptr[ 7 ] = (::booldog::byte)( ( message_ptr_size >> 56 ) & 0xff );
				message_ptr_size /= 8;
				for( ::booldog::uint32 index0 = 0 ; index0 < message_ptr_size + padding_length + 8 ; index0 += 64 )
				{
					/* Round 1 */
					a = aa;
					b = bb;
					c = cc;
					d = dd;
					x = index0;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( ( b & c ) | ( ( ~b ) & d ) ) + x + 0xd76aa478;
					a = ( a << 7 ) | ( a >> ( 25 ) );
					a += b;		
					x = index0 + 4;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];				  
					d += ( ( a & b ) | ( ( ~a ) & c ) ) + x + 0xe8c7b756;
					d = ( d << 12 ) | ( d >> 20 );
					d += a;
					x = index0 + 8;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];				  
					c += ( ( d & a ) | ( ( ~d ) & b ) ) + x + 0x242070db;
					c = ( c << 17 ) | ( c >> 15 );
					c += d;
					x = index0 + 12;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];				
					b += ( ( c & d ) | ( ( ~c ) & a ) ) + x + 0xc1bdceee;
					b = ( b << 22 ) | ( b >> 10 );
					b += c;
					x = index0 + 16;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];				
					a += ( ( b & c ) | ( ( ~b ) & d ) ) + x + 0xf57c0faf;
					a = ( a << 7 ) | ( a >> ( 25 ) );
					a += b;
					x = index0 + 20;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( ( a & b ) | ( ( ~a ) & c ) ) + x + 0x4787c62a;
					d = ( d << 12 ) | ( d >> 20 );
					d += a;
					x = index0 + 24;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( ( d & a ) | ( ( ~d ) & b ) ) + x + 0xa8304613;
					c = ( c << 17 ) | ( c >> 15 );
					c += d;
					x = index0 + 28;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( ( c & d ) | ( ( ~c ) & a ) ) + x + 0xfd469501;
					b = ( b << 22 ) | ( b >> 10 );
					b += c;
					x = index0 + 32;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( ( b & c ) | ( ( ~b ) & d ) ) + x + 0x698098d8;
					a = ( a << 7 ) | ( a >> ( 25 ) );
					a += b;
					x = index0 + 36;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( ( a & b ) | ( ( ~a ) & c ) ) + x + 0x8b44f7af;
					d = ( d << 12 ) | ( d >> 20 );
					d += a;
					x = index0 + 40;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( ( d & a ) | ( ( ~d ) & b ) ) + x + 0xffff5bb1;
					c = ( c << 17 ) | ( c >> 15 );
					c += d;
					x = index0 + 44;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( ( c & d ) | ( ( ~c ) & a ) ) + x + 0x895cd7be;
					b = ( b << 22 ) | ( b >> 10 );
					b += c;
					x = index0 + 48;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( ( b & c ) | ( ( ~b ) & d ) ) + x + 0x6b901122;
					a = ( a << 7 ) | ( a >> ( 25 ) );
					a += b;
					x = index0 + 52;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( ( a & b ) | ( ( ~a ) & c ) ) + x + 0xfd987193;
					d = ( d << 12 ) | ( d >> 20 );
					d += a;
					x = index0 + 56;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( ( d & a ) | ( ( ~d ) & b ) ) + x + 0xa679438e;
					c = ( c << 17 ) | ( c >> 15 );
					c += d;
					x = index0 + 60;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( ( c & d ) | ( ( ~c ) & a ) ) + x + 0x49b40821;
					b = ( b << 22 ) | ( b >> 10 );
					b += c;
					/* Round 2 */    
					x = index0 + 4;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( ( b & d ) | ( c & ( ~d ) ) ) + x + 0xf61e2562;
					a = ( a << 5 ) | ( a >> ( 27 ) );
					a += b;
					x = index0 + 24;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( ( a & c ) | ( b & ( ~c ) ) ) + x + 0xc040b340;
					d = ( d << 9) | ( d >> 23 );
					d += a;
					x = index0 + 44;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( ( d & b ) | ( a & ( ~b ) ) ) + x + 0x265e5a51;
					c = ( c << 14 ) | ( c >> 18 );
					c += d;
					x = index0;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( ( c & a ) | ( d & ( ~a ) ) ) + x + 0xe9b6c7aa;
					b = ( b << 20 ) | ( b >> 12 );
					b += c;
					x = index0 + 20;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( ( b & d ) | ( c & ( ~d ) ) ) + x + 0xd62f105d;
					a = ( a << 5 ) | ( a >> ( 27 ) );
					a += b;
					x = index0 + 40;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( ( a & c ) | ( b & ( ~c ) ) ) + x + 0x2441453;
					d = ( d << 9 ) | ( d >> 23 );
					d += a;
					x = index0 + 60;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( ( d & b ) | ( a & ( ~b ) ) ) + x + 0xd8a1e681;
					c = ( c << 14 ) | ( c >> 18 );
					c += d;
					x = index0 + 16;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( ( c & a ) | ( d & ( ~a ) ) ) + x + 0xe7d3fbc8;
					b = ( b << 20 ) | ( b >> 12 );
					b += c;
					x = index0 + 36;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( ( b & d ) | ( c & ( ~d ) ) ) + x + 0x21e1cde6;
					a = ( a << 5 ) | ( a >> ( 27 ) );
					a += b;
					x = index0 + 56;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( ( a & c ) | ( b & ( ~c ) ) ) + x + 0xc33707d6;
					d = ( d << 9 ) | ( d >> 23 );
					d += a;
					x = index0 + 12;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( ( d & b ) | ( a & ( ~b ) ) ) + x + 0xf4d50d87;
					c = ( c << 14 ) | ( c >> 18 );
					c += d;
					x = index0 + 32;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( ( c & a ) | ( d & ( ~a ) ) ) + x + 0x455a14ed;
					b = ( b << 20 ) | ( b >> 12 );
					b += c;
					x = index0 + 52;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( ( b & d ) | ( c & ( ~d ) ) ) + x + 0xa9e3e905;
					a = ( a << 5 ) | ( a >> ( 27 ) );
					a += b;
					x = index0 + 8;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( ( a & c ) | ( b & ( ~c ) ) ) + x + 0xfcefa3f8;
					d = ( d << 9 ) | ( d >> 23 );
					d += a;				
					x = index0 + 28;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( ( d & b ) | ( a & ( ~b ) ) ) + x + 0x676f02d9;
					c = ( c << 14 ) | ( c >> 18 );
					c += d;				
					x = index0 + 48;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( ( c & a ) | ( d & ( ~a ) ) ) + x + 0x8d2a4c8a;
					b = ( b << 20 ) | ( b >> 12 );
					b += c;				
					/* Round 3 */
					x = index0 + 20;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( b ^ c ^ d ) + x + 0xfffa3942;
					a = ( a << 4 ) | ( a >> ( 28 ) );
					a += b;
					x = index0 + 32;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( a ^ b ^ c ) + x + 0x8771f681;
					d = ( d << 11 ) | ( d >> 21 );
					d += a;
					x = index0 + 44;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( d ^ a ^ b ) + x + 0x6d9d6122;
					c = ( c << 16 ) | ( c >> 16 );
					c += d;
					x = index0 + 56;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( c ^ d ^ a ) + x + 0xfde5380c;
					b = ( b << 23 ) | ( b >> 9 );
					b += c;  
					x = index0 + 4;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( b ^ c ^ d ) + x + 0xa4beea44;
					a = ( a << 4 ) | ( a >> ( 28 ) );
					a += b;  
					x = index0 + 16;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( a ^ b ^ c ) + x + 0x4bdecfa9;
					d = ( d << 11 ) | ( d >> 21 );
					d += a;  
					x = index0 + 28;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( d ^ a ^ b ) + x + 0xf6bb4b60;
					c = ( c << 16 ) | ( c >> 16 );
					c += d;  
					x = index0 + 40;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( c ^ d ^ a ) + x + 0xbebfbc70;
					b = ( b << 23 ) | ( b >> 9 );
					b += c;  
					x = index0 + 52;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( b ^ c ^ d ) + x + 0x289b7ec6;
					a = ( a << 4 ) | ( a >> ( 28 ) );
					a += b;  
					x = index0;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( a ^ b ^ c ) + x + 0xeaa127fa;
					d = ( d << 11 ) | ( d >> 21 );
					d += a;  
					x = index0 + 12;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( d ^ a ^ b ) + x + 0xd4ef3085;
					c = ( c << 16 ) | ( c >> 16 );
					c += d;  
					x = index0 + 24;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( c ^ d ^ a ) + x + 0x4881d05;
					b = ( b << 23 ) | ( b >> 9 );
					b += c;  
					x = index0 + 36;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( b ^ c ^ d ) + x + 0xd9d4d039;
					a = ( a << 4 ) | ( a >> ( 28 ) );
					a += b;    
					x = index0 + 48;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( a ^ b ^ c ) + x + 0xe6db99e5;
					d = ( d << 11 ) | ( d >> 21 );
					d += a;    
					x = index0 + 60;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( d ^ a ^ b ) + x + 0x1fa27cf8;
					c = ( c << 16 ) | ( c >> 16 );
					c += d;    
					x = index0 + 8;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( c ^ d ^ a ) + x + 0xc4ac5665;
					b = ( b << 23 ) | ( b >> 9 );
					b += c;       
					/* Round 4 */			
					x = index0;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( c ^ ( b | (~d) ) ) + x + 0xf4292244;
					a = ( a << 6 ) | ( a >> ( 26 ) );
					a += b;
					x = index0 + 28;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] ) | ( 0x00000080 << 8 ) | ( 0x00000000 << 16 ) | ( 0x00000000 << 24 );
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( b ^ ( a | (~c) ) ) + x + 0x432aff97;
					d = ( d << 10 ) | ( d >> 22 );
					d += a;
					x = index0 + 56;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( a ^ ( d | (~b) ) ) + x + 0xab9423a7;
					c = ( c << 15 ) | ( c >> 17 );
					c += d;
					x = index0 + 20;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( d ^ ( c | (~a) ) ) + x + 0xfc93a039;
					b = ( b << 21 ) | ( b >> 11 );
					b += c;
					x = index0 + 48;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( c ^ ( b | (~d) ) ) + x + 0x655b59c3;
					a = ( a << 6 ) | ( a >> ( 26 ) );
					a += b;
					x = index0 + 12;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( b ^ ( a | (~c) ) ) + x + 0x8f0ccc92;
					d = ( d << 10 ) | ( d >> 22 );
					d += a;
					x = index0 + 40;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( a ^ ( d | (~b) ) ) + x + 0xffeff47d;
					c = ( c << 15 ) | ( c >> 17 );
					c += d;
					x = index0 + 4;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( d ^ ( c | (~a) ) ) + x + 0x85845dd1;
					b = ( b << 21 ) | ( b >> 11 );
					b += c;
					x = index0 + 32;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( c ^ ( b | (~d) ) ) + x + 0x6fa87e4f;
					a = ( a << 6 ) | ( a >> ( 26 ) );
					a += b;
					x = index0 + 60;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( b ^ ( a | (~c) ) ) + x + 0xfe2ce6e0;
					d = ( d << 10 ) | ( d >> 22 );
					d += a;
					x = index0 + 24;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( a ^ ( d | (~b) ) ) + x + 0xa3014314;
					c = ( c << 15 ) | ( c >> 17 );
					c += d;  
					x = index0 + 52;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )			
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( d ^ ( c | (~a) ) ) + x + 0x4e0811a1;
					b = ( b << 21 ) | ( b >> 11 );
					b += c;  
					x = index0 + 16;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					a += ( c ^ ( b | (~d) ) ) + x + 0xf7537e82;
					a = ( a << 6 ) | ( a >> ( 26 ) );
					a += b;  
					x = index0 + 44;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					d += ( b ^ ( a | (~c) ) ) + x + 0xbd3af235;
					d = ( d << 10 ) | ( d >> 22 );
					d += a;  
					x = index0 + 8;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					c += ( a ^ ( d | (~b) ) ) + x + 0x2ad7d2bb;
					c = ( c << 15 ) | ( c >> 17 );
					c += d;
					x = index0 + 36;
					if( x < message_ptr_size )
					{
						index1 = static_cast< ::booldog::uint32 >( message_ptr_size ) - x;
						if( index1 >= sizeof( ::booldog::uint32 ) )
							x = *(::booldog::uint32*)&message_ptr[ x ];
						else if( index1 == 3 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) & 0xff00 ) | ( ( ( (::booldog::uint32)message_ptr[ x + 2 ]) << 16 ) & 0xff0000 ) | 0x80000000;
						else if( index1 == 2 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | ( ( ( (::booldog::uint32)message_ptr[ x + 1 ] ) << 8 ) &0xff00 ) | 0x00800000;
						else if( index1 == 1 )
							x = ( (::booldog::uint32)message_ptr[ x ] & 0xff ) | 0x00008000;
					}
					else if( x == message_ptr_size )
						x = 0x00000080;
					else if( x < message_ptr_size + padding_length )
						x = 0x00000000;
					else 
						x = *(::booldog::uint32*)&message_length_ptr[ x - index0 - 56 ];	
					b += ( d ^ ( c | (~a) ) ) + x + 0xeb86d391;
					b = ( b << 21 ) | ( b >> 11 );
					b += c;
					aa += a;
					bb += b;
					cc += c;
					dd += d;
				}	
				res->buf[ 0 ] = (::booldog::byte)( aa & 0xff );
				res->buf[ 1 ] = (::booldog::byte)( ( aa >> 8 ) & 0xff );
				res->buf[ 2 ] = (::booldog::byte)( ( aa >> 16 ) & 0xff );
				res->buf[ 3 ] = (::booldog::byte)( ( aa >> 24 ) & 0xff );
				res->buf[ 4 ] = (::booldog::byte)( bb & 0xff );
				res->buf[ 5 ] = (::booldog::byte)( ( bb >> 8 ) & 0xff );
				res->buf[ 6 ] = (::booldog::byte)( ( bb >> 16 ) & 0xff );
				res->buf[ 7 ] = (::booldog::byte)( ( bb >> 24 ) & 0xff );
				res->buf[ 8 ] = (::booldog::byte)( cc & 0xff );
				res->buf[ 9 ] = (::booldog::byte)( ( cc >> 8 ) & 0xff );
				res->buf[ 10 ] = (::booldog::byte)( ( cc >> 16 ) & 0xff );
				res->buf[ 11 ] = (::booldog::byte)( ( cc >> 24 ) & 0xff );
				res->buf[ 12 ] = (::booldog::byte)( dd & 0xff );
				res->buf[ 13 ] = (::booldog::byte)( ( dd >> 8 ) & 0xff );
				res->buf[ 14 ] = (::booldog::byte)( ( dd >> 16 ) & 0xff );
				res->buf[ 15 ] = (::booldog::byte)( ( dd >> 24 ) & 0xff );				
				res->bufdatasize = 16;
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
