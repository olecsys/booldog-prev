#ifndef BOO_NETWORK_UTILS_H
#define BOO_NETWORK_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_string_utils.h)
namespace booldog
{
	namespace utils
	{
		namespace network
		{
			booinline bool ip( ::booldog::result* pres , char* dst , size_t& dstlen , size_t dstsize , ::booldog::uint32 ip
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;

				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );

				::booldog::byte* ipparts = (::booldog::byte*)&ip;

				char* begin = 0 , * ptr = 0;
			
				dstlen = 0;
				size_t part_size = 0;

				::booldog::uint32 locnumber = ipparts[ 3 ];
				if( locnumber )
				{
					while( locnumber )
					{
						locnumber /= 10;
						part_size++;
					}
				}
				else
					part_size = 1;
				
				dstlen += part_size + 1;
				if( dstlen > dstsize )
				{
					res->booerr( ::booldog::enums::result::booerr_type_insufficient_memory );
					return false;
				}
				locnumber = ipparts[ 3 ];
				if( locnumber )
				{
					begin = dst;
					ptr = &dst[ dstlen - 2 ];
					for( ; ptr >= begin ; --ptr )
					{
						*ptr = 0x30 + (char)( locnumber % 10 );
						locnumber /= 10;
					}
				}
				else
					dst[ 0 ] = '0';
				dst[ dstlen - 1 ] = '.';

				part_size = 0;
				locnumber = ipparts[ 2 ];
				if( locnumber )
				{
					while( locnumber )
					{
						locnumber /= 10;
						part_size++;
					}
				}
				else
					part_size = 1;
				
				dstlen += part_size + 1;
				if( dstlen > dstsize )
				{
					res->booerr( ::booldog::enums::result::booerr_type_insufficient_memory );
					return false;
				}
				locnumber = ipparts[ 2 ];
				if( locnumber )
				{
					begin = &dst[ dstlen - part_size - 1 ];
					ptr = &dst[ dstlen - 2 ];
					for( ; ptr >= begin ; --ptr )
					{
						*ptr = 0x30 + (char)( locnumber % 10 );
						locnumber /= 10;
					}
				}
				else
					dst[ dstlen - 2 ] = '0';
				dst[ dstlen - 1 ] = '.';

				part_size = 0;
				locnumber = ipparts[ 1 ];
				if( locnumber )
				{
					while( locnumber )
					{
						locnumber /= 10;
						part_size++;
					}
				}
				else
					part_size = 1;
				dstlen += part_size + 1;
				if( dstlen > dstsize )
				{
					res->booerr( ::booldog::enums::result::booerr_type_insufficient_memory );
					return false;
				}
				locnumber = ipparts[ 1 ];
				if( locnumber )
				{
					begin = &dst[ dstlen - part_size - 1 ];
					ptr = &dst[ dstlen - 2 ];
					for( ; ptr >= begin ; --ptr )
					{
						*ptr = 0x30 + (char)( locnumber % 10 );
						locnumber /= 10;
					}
				}
				else
					dst[ dstlen - 2 ] = '0';
				dst[ dstlen - 1 ] = '.';

				part_size = 0;
				locnumber = ipparts[ 0 ];
				if( locnumber )
				{
					while( locnumber )
					{
						locnumber /= 10;
						part_size++;
					}
				}
				else
					part_size = 1;
				dstlen += part_size + 1;
				if( dstlen > dstsize )
				{
					res->booerr( ::booldog::enums::result::booerr_type_insufficient_memory );
					return false;
				}
				locnumber = ipparts[ 0 ];
				if( locnumber )
				{
					begin = &dst[ dstlen - part_size - 1 ];
					ptr = &dst[ dstlen - 2 ];
					for( ; ptr >= begin ; --ptr )
					{
						*ptr = 0x30 + (char)( locnumber % 10 );
						locnumber /= 10;
					}
				}
				else
					dst[ dstlen - 2 ] = '0';
				dst[ dstlen - 1 ] = 0;
				dstlen--;
				return res->succeeded();
			};
		};
	};
};
#endif