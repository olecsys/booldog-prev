#ifndef BOO_CP1251_H
#define BOO_CP1251_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_cp1251_consts.h)
namespace booldog
{
	namespace cp1251
	{
		booinline bool isdigit( ::booldog::byte ch )
		{
			return ch > 47 && ch < 58;
		};
		booinline bool isalpha( ::booldog::byte ch )
		{
			return ::booldog::consts::cp1251::_isalpha[ ch ] == 1;
		};
		booinline bool isalnum( ::booldog::byte ch )
		{
			return ::booldog::consts::cp1251::_isalnum[ ch ] == 1;
		};
		booinline ::booldog::enums::string::conversion_result to_upper( const char* src_ptr , size_t src_ptr_count , char* dst_ptr , size_t dst_ptr_count , size_t& dst_bytes )
		{
			const ::booldog::uint8* source = (::booldog::uint8*)src_ptr , * source_end = (::booldog::uint8*)( src_ptr + src_ptr_count );
			::booldog::uint8* target = (::booldog::uint8*)dst_ptr , * target_end = (::booldog::uint8*)( dst_ptr + dst_ptr_count );
			if( target == 0 )
				goto goto_conversion_result_targetExhausted;
			while( source < source_end )
			{
				if( target >= target_end )
					goto goto_conversion_result_targetExhausted;
				*target++ = ::booldog::consts::cp1251::_toupper[ *source++ ];
				if( target[ -1 ] == 0 )
					break;
			}
			if( target )
				dst_bytes = (char*)target - dst_ptr;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			while( source < source_end )
			{
				target++;
				if( *source++ == 0 )
					break;
			}
			if( target )
				dst_bytes = (char*)target - dst_ptr;
			return ::booldog::enums::string::conversion_result_targetExhausted;
		};
		booinline ::booldog::enums::string::conversion_result to_lower( const char* src_ptr , size_t src_ptr_count , char* dst_ptr , size_t dst_ptr_count , size_t& dst_bytes )
		{
			const ::booldog::uint8* source = (::booldog::uint8*)src_ptr , * source_end = (::booldog::uint8*)( src_ptr + src_ptr_count );
			::booldog::uint8* target = (::booldog::uint8*)dst_ptr , * target_end = (::booldog::uint8*)( dst_ptr + dst_ptr_count );
			if( target == 0 )
				goto goto_conversion_result_targetExhausted;
			while( source < source_end )
			{
				if( target >= target_end )
					goto goto_conversion_result_targetExhausted;
				*target++ = ::booldog::consts::cp1251::_tolower[ *source++ ];
				if( target[ -1 ] == 0 )
					break;
			}
			if( target )
				dst_bytes = (char*)target - dst_ptr;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			while( source < source_end )
			{
				target++;
				if( *source++ == 0 )
					break;
			}
			if( target )
				dst_bytes = (char*)target - dst_ptr;
			return ::booldog::enums::string::conversion_result_targetExhausted;
		};
		booinline ::booldog::enums::string::conversion_result to_utf8( const char* cp1251_ptr , size_t& srcbyteindex , size_t cp1251_ptr_count , char* utf8_ptr , size_t& dstbyteindex , size_t utf8_ptr_count , size_t& utf8_bytes , size_t& utf8length )
		{
			utf8_bytes = 0;
			const ::booldog::uint8* source = (::booldog::uint8*)&cp1251_ptr[ srcbyteindex ] , * source_end = (::booldog::uint8*)( cp1251_ptr + cp1251_ptr_count );
			if( source_end < source )
				source_end = (::booldog::uint8*)SIZE_MAX;
			::booldog::uint8* target = (::booldog::uint8*)SIZE_MAX , * target_end = 0;
			if( utf8_ptr )
			{
				target = (::booldog::uint8*)&utf8_ptr[ dstbyteindex ];
				target_end = (::booldog::uint8*)( &utf8_ptr[ utf8_ptr_count - 1 ] + 1 );
			}
			::booldog::byte diff = 0;
			while( source < source_end )
			{
				switch( ::booldog::consts::cp1251::_cp1251_to_utf8_length[ *source ] )
				{
				case 1:
					{
						if( ++target > target_end )
						{
							if( *(::booldog::uint8*)&::booldog::consts::cp1251::_cp1251_to_utf8[ *source++ ] == 0 )
							{
								target--;
								goto goto_conversion_result_null_terminated;
							}
							diff = 1;
							goto goto_conversion_result_targetExhausted;
						}
						target[ -1 ] = *(::booldog::uint8*)&::booldog::consts::cp1251::_cp1251_to_utf8[ *source++ ];
						if( target[ -1 ] == 0 )
						{
							target--;
							goto goto_conversion_result_null_terminated;
						}
						break;
					}
				case 2:
					{
						target += 2;
						if( target > target_end )
						{
							diff = 2;
							source++;
							goto goto_conversion_result_targetExhausted;
						}
						*(::booldog::uint16*)&target[ -2 ] = *(::booldog::uint16*)&::booldog::consts::cp1251::_cp1251_to_utf8[ *source++ ];
						break;
					}
				case 3:
					{
						target += 3;
						if( target > target_end )
						{
							diff = 3;
							source++;
							goto goto_conversion_result_targetExhausted;
						}
						::booldog::uint8* ptr = ((::booldog::uint8*)&::booldog::consts::cp1251::_cp1251_to_utf8[ *source++ ]);
						*(::booldog::uint16*)&target[ -3 ] = *(::booldog::uint16*)ptr;
						target[ -1 ] = ptr[ 2 ];
						break;
					}					
				}
				utf8length++;
			}
goto_conversion_result_null_terminated:
			if( target )
			{
				utf8_bytes = (char*)target - utf8_ptr;
				srcbyteindex += (char*)source - &cp1251_ptr[ srcbyteindex ];
				dstbyteindex = utf8_bytes;
			}
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			if( target )
			{
				utf8_bytes = (char*)target - utf8_ptr;
				srcbyteindex += (char*)source - &cp1251_ptr[ srcbyteindex ] - sizeof( ::booldog::byte );
				dstbyteindex = utf8_bytes - diff;
			}
			while( source < source_end )
			{
				switch( ::booldog::consts::cp1251::_cp1251_to_utf8_length[ *source ] )
				{
				case 1:
					{
						if( *(::booldog::uint8*)&::booldog::consts::cp1251::_cp1251_to_utf8[ *source++ ] == 0 )
							goto goto_conversion_result_null_terminated_end;
						utf8_bytes++;
						break;
					}
				case 2:
					{
						source++;
						utf8_bytes += 2;
						break;
					}
				case 3:
					{
						source++;
						utf8_bytes += 3;
						break;
					}					
				}
			}
goto_conversion_result_null_terminated_end:
			return ::booldog::enums::string::conversion_result_targetExhausted;
		};
		booinline ::booldog::enums::string::conversion_result to_utf16( const char* cp1251_ptr , size_t cp1251_ptr_count , char* utf16_ptr , size_t utf16_ptr_count , size_t& utf16_bytes )
		{
			utf16_bytes = 0;
			const ::booldog::uint8* source = (::booldog::uint8*)cp1251_ptr , * source_end = (::booldog::uint8*)( cp1251_ptr + cp1251_ptr_count );
			::booldog::uint16* target = (::booldog::uint16*)utf16_ptr , * target_end = (::booldog::uint16*)( utf16_ptr + utf16_ptr_count );
			while( source < source_end )
			{
				if( target >= target_end )
					goto goto_conversion_result_targetExhausted;
				*target++ = ::booldog::consts::cp1251::_cp1251_to_utf16[ *source++ ];
			}
			if( target )
				utf16_bytes = (char*)target - utf16_ptr;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			if( target )
				utf16_bytes = (char*)target - utf16_ptr;
			utf16_bytes += source_end - source;
			return ::booldog::enums::string::conversion_result_targetExhausted;
		};
		booinline ::booldog::enums::string::conversion_result to_utf32( const char* cp1251_ptr , size_t cp1251_ptr_count , char* utf32_ptr , size_t utf32_ptr_count , size_t& utf32_bytes )
		{
			utf32_bytes = 0;
			const ::booldog::uint8* source = (::booldog::uint8*)cp1251_ptr , * source_end = (::booldog::uint8*)( cp1251_ptr + cp1251_ptr_count );
			::booldog::uint32* target = (::booldog::uint32*)utf32_ptr , * target_end = (::booldog::uint32*)( utf32_ptr + utf32_ptr_count );
			while( source < source_end )
			{
				if( target >= target_end )
					goto goto_conversion_result_targetExhausted;
				*target++ = ::booldog::consts::cp1251::_cp1251_to_utf32[ *source++ ];
			}
			if( target )
				utf32_bytes = (char*)target - utf32_ptr;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			if( target )
				utf32_bytes = (char*)target - utf32_ptr;
			utf32_bytes += source_end - source;
			return ::booldog::enums::string::conversion_result_targetExhausted;
		};
	};
};
#endif