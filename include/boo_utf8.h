#ifndef BOO_UTF8_H
#define BOO_UTF8_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_utf8_consts.h"
#include "boo_utf32.h"
namespace booldog
{
	namespace utf8
	{
#ifndef boo_validate_character_check_without_length_macros
#define boo_validate_character_check_without_length_macros(ptr) ++ptr;\
	if(!((*ptr >> 6) == 0x2))\
		return ::booldog::enums::string::conversion_result_sourceIllegal
#endif
		booinline bool validate_character( const ::booldog::byte*& ptr )
		{
			if( *ptr <= 0x7f )
			{
			}
			else if( (*ptr >> 5 ) == 0x6 )
			{
				boo_validate_character_check_without_length_macros( ptr );
			}
			/* three byte */
			else if( ( *ptr >> 4 ) == 0x0e ) 
			{
				boo_validate_character_check_without_length_macros( ptr );
				boo_validate_character_check_without_length_macros( ptr );
			}
			/* four byte */        
			else if( ( *ptr >> 3 ) == 0x1e )
			{
				boo_validate_character_check_without_length_macros( ptr );
				boo_validate_character_check_without_length_macros( ptr );
				boo_validate_character_check_without_length_macros( ptr );
			}
			else
				return false;
			ptr++;
			return true;
		};
		booinline bool validate_character_check_with_length( const ::booldog::byte*& ptr , size_t* length )
		{
			ptr++;
			if( ( (*length)-- ) == 0 )
				return false;
			if( !( ( *ptr >> 6 ) == 0x2 ) )
				return false;
			return true;
		};
		booinline bool validate_character_with_length_and_character_size( const ::booldog::byte*& ptr , size_t* length , size_t* character_size )
		{
			if( *ptr <= 0x7f )
				*character_size = 1;
			else if( (*ptr >> 5 ) == 0x6 )
			{
				if( validate_character_check_with_length( ptr , length ) == false )
					return false;
				*character_size = 2;
			}
			/* three byte */
			else if( ( *ptr >> 4 ) == 0x0e ) 
			{
				if( validate_character_check_with_length( ptr , length ) == false )
					return false;
				if( validate_character_check_with_length( ptr , length ) == false )
					return false;
				*character_size = 3;
			}
			/* four byte */        
			else if( ( *ptr >> 3 ) == 0x1e )
			{
				if( validate_character_check_with_length( ptr , length ) == false )
					return false;
				if( validate_character_check_with_length( ptr , length ) == false )
					return false;
				if( validate_character_check_with_length( ptr , length ) == false )
					return false;
				*character_size = 4;
			}
			else
				return false;
			(*length)--;
			ptr++;
			return true;
		};
		booinline bool validate_character_with_length( const ::booldog::byte*& ptr , size_t* length )
		{
			if( *ptr <= 0x7f )
			{
			}
			else if( (*ptr >> 5 ) == 0x6 )
			{
				if( validate_character_check_with_length( ptr , length ) == false )
					return false;
			}
			/* three byte */
			else if( ( *ptr >> 4 ) == 0x0e ) 
			{
				if( validate_character_check_with_length( ptr , length ) == false )
					return false;
				if( validate_character_check_with_length( ptr , length ) == false )
					return false;
			}
			/* four byte */        
			else if( ( *ptr >> 3 ) == 0x1e )
			{
				if( validate_character_check_with_length( ptr , length ) == false )
					return false;
				if( validate_character_check_with_length( ptr , length ) == false )
					return false;
				if( validate_character_check_with_length( ptr , length ) == false )
					return false;
			}
			else
				return false;
			(*length)--;
			ptr++;
			return true;
		};
		booinline ::booldog::enums::string::conversion_result to_cp1251( const char* utf8_ptr , size_t utf8_ptr_count , char* cp1251_ptr , size_t cp1251_ptr_count , size_t& cp1251_bytes )
		{
			cp1251_bytes = 0;
			const ::booldog::uint8* source = (::booldog::uint8*)utf8_ptr , * source_end = (::booldog::uint8*)( utf8_ptr + utf8_ptr_count );
			::booldog::uint8* target = (::booldog::uint8*)cp1251_ptr , * target_end = (::booldog::uint8*)( cp1251_ptr + cp1251_ptr_count );
			::booldog::uint32 ch = 0;
			while( source < source_end )
			{
				if( *source == 0 )
				{
					if( target < target_end )
						*target++ = 0;
					break;
				}
				else if( *source <= 0x7f )
					ch = *source++;
				else if( (*source >> 5 ) == 0x6 )
				{
					source += 2;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch = source[-2];
					ch <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch += source[-1];
					ch -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
				}
				else if( ( *source >> 4 ) == 0x0e )
				{
					source += 3;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch = source[-3];
					ch <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch += source[-2];
					ch <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch += source[-1];
					ch -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
				}
				else if( ( *source >> 3 ) == 0x1e )
				{
					source += 4;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch = source[-4];
					ch <<= 6;
					if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch += source[-3];
					ch <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch += source[-2];
					ch <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch += source[-1];
					ch -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				if( ch <= (::booldog::uint32)0x0010FFFF ) 
				{
					if( ch >= (::booldog::uint32)0xD800 && ch <= (::booldog::uint32)0xDFFF )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					else
					{
						if( target < target_end )
						{
							if( ch < 128 )
								*target++ = (::booldog::byte)ch;
							else
							{
								if( ch > 151 && ch < 188 )
								{
									*target = ::booldog::consts::utf32::_utf32_to_cp1251_page_from_152_to_187[ ch - 152 ];
									if( *target++ == 0 )
										return ::booldog::enums::string::conversion_result_sourceIllegal;
								}
								else if( ch > 1024 && ch < 1170 )
								{
									*target = ::booldog::consts::utf32::_utf32_to_cp1251_page_from_1025_to_1169[ ch - 1025 ];
									if( *target++ == 0 )
										return ::booldog::enums::string::conversion_result_sourceIllegal;
								}
								else if( ch > 8210 && ch < 8483 )
								{
									*target = ::booldog::consts::utf32::_utf32_to_cp1251_page_from_8211_to_8482[ ch - 8211 ];
									if( *target++ == 0 )
										return ::booldog::enums::string::conversion_result_sourceIllegal;
								}
								else
									return ::booldog::enums::string::conversion_result_sourceIllegal;
							}
						}
						else
						{
							target++;
							goto goto_conversion_result_targetExhausted;
						}
					}								
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;						
			}
			if( target )
				cp1251_bytes = (char*)target - cp1251_ptr;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			if( target )
				cp1251_bytes = (char*)target - cp1251_ptr;
			while( source < source_end )
			{
				if( *source == 0 )
				{
					cp1251_bytes++;
					break;
				}
				else if( *source <= 0x7f )
					ch = *source++;
				else if( (*source >> 5 ) == 0x6 )
				{
					source += 2;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch = source[-2];
					ch <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch += source[-1];
					ch -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
				}
				else if( ( *source >> 4 ) == 0x0e )
				{
					source += 3;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch = source[-3];
					ch <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch += source[-2];
					ch <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch += source[-1];
					ch -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
				}
				else if( ( *source >> 3 ) == 0x1e )
				{
					source += 4;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch = source[-4];
					ch <<= 6;
					if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch += source[-3];
					ch <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch += source[-2];
					ch <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					ch += source[-1];
					ch -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				if( ch <= (::booldog::uint32)0x0010FFFF ) 
				{
					if( ch >= (::booldog::uint32)0xD800 && ch <= (::booldog::uint32)0xDFFF )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					else
					{
						if( ch < 128 )
							cp1251_bytes++;
						else
						{
							if( ch > 151 && ch < 188 )
							{
								if( ::booldog::consts::utf32::_utf32_to_cp1251_page_from_152_to_187[ ch - 152 ] == 0 )
									return ::booldog::enums::string::conversion_result_sourceIllegal;
								else
									cp1251_bytes++;
							}
							else if( ch > 1024 && ch < 1170 )
							{
								if( ::booldog::consts::utf32::_utf32_to_cp1251_page_from_1025_to_1169[ ch - 1025 ] == 0 )
									return ::booldog::enums::string::conversion_result_sourceIllegal;
								else
									cp1251_bytes++;
							}
							else if( ch > 8210 && ch < 8483 )
							{
								if( ::booldog::consts::utf32::_utf32_to_cp1251_page_from_8211_to_8482[ ch - 8211 ] == 0 )
									return ::booldog::enums::string::conversion_result_sourceIllegal;
								else
									cp1251_bytes++;
							}
							else
								return ::booldog::enums::string::conversion_result_sourceIllegal;
						}
					}								
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;						
			}
			return ::booldog::enums::string::conversion_result_targetExhausted;
		};
		booinline ::booldog::enums::string::conversion_result to_utf32(const char* utf8_ptr, size_t& srcbyteindex
			, size_t utf8_ptr_count, char* utf32_ptr, size_t& dstbyteindex, size_t utf32_ptr_count, size_t& utf32_bytes
			, size_t& utf32length)
		{
			const ::booldog::uint8* source = (::booldog::uint8*)utf8_ptr + srcbyteindex
				, * source_end = (::booldog::uint8*)utf8_ptr + utf8_ptr_count;
			::booldog::uint32* target = (::booldog::uint32*)(utf32_ptr + dstbyteindex)
				, * target_end = (::booldog::uint32*)(utf32_ptr + utf32_ptr_count);
			::booldog::uint32 letter0 = 0;
			::booldog::byte diff = 0;
			if(utf32_ptr == 0)
				goto goto_conversion_result_targetExhausted;
			while(source < source_end)
			{
				if( *source <= 0x7f )
				{
					diff = 1;
					if(*source == 0)
					{
						if(target < target_end)
							*target++ = 0;
						break;
					}
					letter0 = *source++;
				}
				else if((*source >> 5) == 0x6)
				{
					diff = 2;
					source += 2;
					if(source > source_end)
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 = source[-2];
					letter0 <<= 6;
					if(!(((source[-1]) >> 6) == 0x2))
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-1];
					letter0 -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
				}
				else if((*source >> 4) == 0x0e)
				{
					diff = 3;
					source += 3;
					if(source > source_end)
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 = source[-3];
					letter0 <<= 6;
					if(!((source[-2] >> 6) == 0x2))
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-2];
					letter0 <<= 6;
					if(!(((source[-1]) >> 6) == 0x2))
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-1];
					letter0 -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
				}
				else if((*source >> 3) == 0x1e)
				{
					diff = 4;
					source += 4;
					if(source > source_end)
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 = source[-4];
					letter0 <<= 6;
					if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-3];
					letter0 <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-2];
					letter0 <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-1];
					letter0 -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				if( letter0 <= (::booldog::uint32)0x0010FFFF ) 
				{
					if( letter0 >= (::booldog::uint32)0xD800 && letter0 <= (::booldog::uint32)0xDFFF )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					else
					{
						if( target < target_end )
							*target++ = letter0;
						else
						{
							target++;
							goto goto_conversion_result_targetExhausted;
						}
					}								
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				++utf32length;
			}
			utf32_bytes = (char*)target - utf32_ptr;
			srcbyteindex = ((char*)source - utf8_ptr);
			dstbyteindex = utf32_bytes;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			if(utf32_ptr)
			{
				utf32_bytes = (char*)target - utf32_ptr;
				srcbyteindex = ((char*)source - utf8_ptr) - diff;
				dstbyteindex = utf32_bytes - 4;
			}
			while(source < source_end) 
			{
				if(*source == 0)
				{
					utf32_bytes += 4;
					break;
				}
				else if(*source <= 0x7f)
					letter0 = *source++;
				else if((*source >> 5) == 0x6)
				{
					source += 2;
					if(source > source_end)
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 = source[-2];
					letter0 <<= 6;
					if(!(((source[-1]) >> 6) == 0x2))
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-1];
					letter0 -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
				}
				else if((*source >> 4) == 0x0e)
				{
					source += 3;
					if(source > source_end)
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 = source[-3];
					letter0 <<= 6;
					if(!((source[-2] >> 6) == 0x2))
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-2];
					letter0 <<= 6;
					if(!(((source[-1]) >> 6) == 0x2))
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-1];
					letter0 -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
				}
				else if((*source >> 3) == 0x1e)
				{
					source += 4;
					if(source > source_end)
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 = source[-4];
					letter0 <<= 6;
					if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-3];
					letter0 <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-2];
					letter0 <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-1];
					letter0 -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				if(letter0 <= (::booldog::uint32)0x0010FFFF) 
				{
					if(letter0 >= (::booldog::uint32)0xD800 && letter0 <= (::booldog::uint32)0xDFFF)
						return ::booldog::enums::string::conversion_result_sourceIllegal;
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utf32_bytes += 4;
			}
			return ::booldog::enums::string::conversion_result_targetExhausted;
		}
		booinline ::booldog::enums::string::conversion_result to_upper( const char* src_ptr , size_t src_ptr_count , char* dst_ptr , size_t dst_ptr_count , size_t& dst_bytes )
		{
			const ::booldog::uint8* source = (::booldog::uint8*)src_ptr , * source_end = (::booldog::uint8*)( src_ptr + src_ptr_count );
			::booldog::uint8* target = (::booldog::uint8*)dst_ptr , * target_end = (::booldog::uint8*)( dst_ptr + dst_ptr_count );
			::booldog::uint32 utfchar = 0;
			while( source < source_end )
			{
				if( *source <= 0x7f )
				{
					if( *source == 0 )
					{
						if( target < target_end )
							*target++ = 0;
						break;
					}
					utfchar = *source++;
				}
				else if( (*source >> 5 ) == 0x6 )
				{
					source += 2;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar = source[-2];
					utfchar <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-1];
					utfchar -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
				}
				else if( ( *source >> 4 ) == 0x0e )
				{
					source += 3;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar = source[-3];
					utfchar <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-2];
					utfchar <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-1];
					utfchar -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
				}
				else if( ( *source >> 3 ) == 0x1e )
				{
					source += 4;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar = source[-4];
					utfchar <<= 6;
					if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-3];
					utfchar <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-2];
					utfchar <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-1];
					utfchar -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				if( utfchar <= (::booldog::uint32)0x0010FFFF ) 
				{
					if( utfchar >= (::booldog::uint32)0xD800 && utfchar <= (::booldog::uint32)0xDFFF )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					else
					{
						if( utfchar > 0x60 && utfchar < 0x7b )
						{
							utfchar -= 0x20;
						}
						else if( utfchar > 0xdf && utfchar < 0xff )
						{
							switch( utfchar )
							{
							case 0xf7:
								break;
							default:
								utfchar -= 0x20;
							}
						}
						else if( utfchar > 0x0100 && utfchar < 0x0138 )
						{
							if( ::booldog::utils::odd( utfchar ) )
							{
								switch( utfchar )
								{
								case 0x0130:
								case 0x0131:
								case 0x0132:
									break;
								default:
									utfchar--;
								}
							}
						}
						else if( utfchar > 0x0139 && utfchar < 0x0149 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0x014a && utfchar < 0x0178 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x0179 && utfchar < 0x017f )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0x0182 && utfchar < 0x0186 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x01a0 && utfchar < 0x01ae )
						{
							if( ::booldog::utils::odd( utfchar ) )
							{
								switch( utfchar )
								{
								case 0x01a6:
								case 0x01a7:
								case 0x01a9:
								case 0x01aa:
								case 0x01ab:
								case 0x01ac:
									break;
								case 0x01a8:
									{
										utfchar = 0x01a7;
										break;
									}
								default:
									utfchar--;
								}
							}
						}
						else if( utfchar > 0x01b3 && utfchar < 0x01b7 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0x01cd && utfchar < 0x01dd )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0x01de && utfchar < 0x0234 )
						{
							if( ::booldog::utils::odd( utfchar ) )
							{
								switch( utfchar )
								{
								case 0x01f0:
								case 0x01f1:
								case 0x01f2:
								case 0x01f4:
								case 0x01f6:
								case 0x01f7:
								case 0x01f8:
								case 0x0220:
								case 0x0221:
								case 0x0222:
									break;
								case 0x01f3:
									{
										utfchar = 0x01f1;
										break;
									}
								default:
									utfchar--;
								}
							}
						}
						else if( utfchar > 0x0246 && utfchar < 0x0250 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x0255 && utfchar < 0x0258 )
						{
							utfchar -= 0xcd;
						}
						else if( utfchar > 0x0289 && utfchar < 0x028c )
						{
							utfchar -= 0xd9;
						}
						else if( utfchar > 0x0370 && utfchar < 0x0378 )
						{
							if( ::booldog::utils::odd( utfchar ) )
							{
								switch( utfchar )
								{
								case 0x0374:
								case 0x0375:
								case 0x0376:
									break;
								default:
									utfchar--;
								}
							}
						}
						else if( utfchar > 0x037a && utfchar < 0x037e )
						{
							utfchar += 0x82;
						}
						else if( utfchar > 0x03ac && utfchar < 0x03b0 )
						{
							utfchar -= 0x25;
						}
						else if( utfchar > 0x03b0 && utfchar < 0x03cc )
						{
							switch( utfchar )
							{
							case 0x03c2:
								break;
							default:
								utfchar -= 0x20;
							}
						}
						else if( utfchar > 0x03cc && utfchar < 0x03cf )
						{
							utfchar -= 0x3f;
						}
						else if( utfchar > 0x03d8 && utfchar < 0x03f0 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x042f && utfchar < 0x0450 )
						{
							utfchar -= 0x20;
						}
						else if( utfchar > 0x044f && utfchar < 0x0460 )
						{
							utfchar -= 0x50;
						}
						else if( utfchar > 0x0460 && utfchar < 0x0482 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x048a && utfchar < 0x04c0 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x04c1 && utfchar < 0x04cf )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0x04d0 && utfchar < 0x0524 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x0560 && utfchar < 0x0587 )
						{
							utfchar -= 0x30;
						}
						else if( utfchar > 0x1e00 && utfchar < 0x1e96 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x1ea0 && utfchar < 0x1f00 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x1eff && utfchar < 0x1f08 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f0f && utfchar < 0x1f16 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f1f && utfchar < 0x1f28 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f2f && utfchar < 0x1f38 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f3f && utfchar < 0x1f46 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f5f && utfchar < 0x1f68 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f6f && utfchar < 0x1f72 )
						{
							utfchar += 0x4a;
						}
						else if( utfchar > 0x1f71 && utfchar < 0x1f76 )
						{
							utfchar += 0x56;
						}
						else if( utfchar > 0x1f75 && utfchar < 0x1f78 )
						{
							utfchar += 0x64;
						}
						else if( utfchar > 0x1f77 && utfchar < 0x1f7a )
						{
							utfchar += 0x80;
						}
						else if( utfchar > 0x1f79 && utfchar < 0x1f7c )
						{
							utfchar += 0x70;
						}
						else if( utfchar > 0x1f7b && utfchar < 0x1f7e )
						{
							utfchar += 0x7e;
						}
						else if( utfchar > 0x1f7f && utfchar < 0x1f88 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f8f && utfchar < 0x1f98 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f9f && utfchar < 0x1fa8 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1faf && utfchar < 0x1fb2 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1fcf && utfchar < 0x1fd2 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1fdf && utfchar < 0x1fe2 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x216f && utfchar < 0x2180 )
						{
							utfchar -= 0x10;
						}
						else if( utfchar > 0x24cf && utfchar < 0x24ea )
						{
							utfchar -= 0x1a;
						}
						else if( utfchar > 0x2c2f && utfchar < 0x2c5f )
						{
							utfchar -= 0x30;
						}
						else if( utfchar > 0x2c67 && utfchar < 0x2c6d )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0x2c80 && utfchar < 0x2ce4 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x2cff && utfchar < 0x2d26 )
						{
							utfchar -= 0x1c60;
						}
						else if( utfchar > 0xa640 && utfchar < 0xa66e )
						{
							if( ::booldog::utils::odd( utfchar ) )
							{
								switch( utfchar )
								{
								case 0xa660:
								case 0xa661:
								case 0xa662:
									break;
								default:
									utfchar--;
								}
							}
						}
						else if( utfchar > 0xa680 && utfchar < 0xa698 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0xa722 && utfchar < 0xa770 )
						{
							if( ::booldog::utils::odd( utfchar ) )
							{
								switch( utfchar )
								{
								case 0xa730:
								case 0xa731:
								case 0xa732:
									break;
								default:
									utfchar--;
								}
							}
						}
						else if( utfchar > 0xa779 && utfchar < 0xa77d )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0xa77e && utfchar < 0xa788 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0xff40 && utfchar < 0xff5b )
						{
							utfchar -= 0x20;
						}
						else
						{
							switch( utfchar )
							{
							case 0xff:
								utfchar = 0x0178;
								break;
							case 0x0180:
								utfchar = 0x0243;
								break;
							case 0x0188:
								utfchar = 0x0187;
								break;
							case 0x018c:
								utfchar = 0x018b;
								break;
							case 0x0192:
								utfchar = 0x0191;
								break;
							case 0x0195:
								utfchar = 0x01f6;
								break;
							case 0x0199:
								utfchar = 0x0198;
								break;
							case 0x019a:
								utfchar = 0x023d;
								break;
							case 0x019e:
								utfchar = 0x0220;
								break;
							case 0x01a8:
								utfchar = 0x01a7;
								break;
							case 0x01b0:
								utfchar = 0x01af;
								break;
							case 0x01b9:
								utfchar = 0x01b8;
								break;
							case 0x01bd:
								utfchar = 0x01bc;
								break;
							case 0x01bf:
								utfchar = 0x01f7;
								break;
							case 0x01c6:
								utfchar = 0x01c4;
								break;
							case 0x01c9:
								utfchar = 0x01c7;
								break;
							case 0x01cc:
								utfchar = 0x01ca;
								break;
							case 0x01dd:
								utfchar = 0x018e;
								break;
							case 0x01f3:
								utfchar = 0x01f1;
								break;
							case 0x023c:
								utfchar = 0x023b;
								break;
							case 0x0242:
								utfchar = 0x0241;
								break;
							case 0x0250:
								utfchar = 0x2c6f;
								break;
							case 0x0251:
								utfchar = 0x2c6d;
								break;
							case 0x0253:
								utfchar = 0x0181;
								break;
							case 0x0254:
								utfchar = 0x0186;
								break;
							case 0x0259:
								utfchar = 0x018f;
								break;
							case 0x025b:
								utfchar = 0x0190;
								break;
							case 0x0260:
								utfchar = 0x0193;
								break;
							case 0x0263:
								utfchar = 0x0194;
								break;
							case 0x0268:
								utfchar = 0x0197;
								break;
							case 0x0269:
								utfchar = 0x0196;
								break;
							case 0x026b:
								utfchar = 0x2c62;
								break;
							case 0x026f:
								utfchar = 0x019c;
								break;
							case 0x0271:
								utfchar = 0x2c6e;
								break;
							case 0x0272:
								utfchar = 0x019d;
								break;
							case 0x0275:
								utfchar = 0x019f;
								break;
							case 0x027d:
								utfchar = 0x2c64;
								break;
							case 0x0280:
								utfchar = 0x01a6;
								break;
							case 0x0283:
								utfchar = 0x01a9;
								break;
							case 0x0288:
								utfchar = 0x01ae;
								break;
							case 0x0289:
								utfchar = 0x0244;
								break;
							case 0x028c:
								utfchar = 0x0245;
								break;
							case 0x0292:
								utfchar = 0x01b7;
								break;
							case 0x03ac:
								utfchar = 0x0386;
								break;
							case 0x03cc:
								utfchar = 0x038c;
								break;
							case 0x03d7:
								utfchar = 0x03cf;
								break;
							case 0x03f2:
								utfchar = 0x03f9;
								break;
							case 0x03f8:
								utfchar = 0x03f7;
								break;
							case 0x03fb:
								utfchar = 0x03fa;
								break;
							case 0x04cf:
								utfchar = 0x04c0;
								break;
							case 0x1d79:
								utfchar = 0xa77d;
								break;
							case 0x1d7d:
								utfchar = 0x2c63;
								break;
							case 0x1f51:
								utfchar = 0x1f59;
								break;
							case 0x1f53:
								utfchar = 0x1f5b;
								break;
							case 0x1f55:
								utfchar = 0x1f5d;
								break;
							case 0x1f57:
								utfchar = 0x1f5f;
								break;
							case 0x1fb3:
								utfchar = 0x1fbc;
								break;
							case 0x1fc3:
								utfchar = 0x1fcc;
								break;
							case 0x1fe5:
								utfchar = 0x1fec;
								break;
							case 0x1ff3:
								utfchar = 0x1ffc;
								break;
							case 0x214e:
								utfchar = 0x2132;
								break;
							case 0x2184:
								utfchar = 0x2183;
								break;
							case 0x2c61:
								utfchar = 0x2c60;
								break;
							case 0x2c65:
								utfchar = 0x023a;
								break;
							case 0x2c66:
								utfchar = 0x023e;
								break;
							case 0x2c73:
								utfchar = 0x2c72;
								break;
							case 0x2c76:
								utfchar = 0x2c75;
								break;
							case 0xa78c:
								utfchar = 0xa78b;
								break;
							}
						}
						if( utfchar >= (::booldog::uint32)0xD800 && utfchar <= (::booldog::uint32)0xDFFF )
							return ::booldog::enums::string::conversion_result_sourceIllegal;
						if( utfchar < (::booldog::uint32)0x80 )
						{
							target += 1;
							if( target > target_end )
								goto goto_conversion_result_targetExhausted;
							target[ -1 ] = (::booldog::byte)( utfchar | ::booldog::consts::utf32::_firstByteMark[ 1 ] );
						}
						else if( utfchar < (::booldog::uint32)0x800 )
						{
							target += 2;
							if( target > target_end )
								goto goto_conversion_result_targetExhausted;
							target[ -1 ] = (::booldog::byte)((utfchar | 0x80) & 0xBF); utfchar >>= 6;
							target[ -2 ] = (::booldog::byte)( utfchar | ::booldog::consts::utf32::_firstByteMark[ 2 ] );
						} 
						else if( utfchar < (::booldog::uint32)0x10000 )
						{
							target += 3;
							if( target > target_end )
								goto goto_conversion_result_targetExhausted;
							target[ -1 ] = (::booldog::byte)((utfchar | 0x80) & 0xBF); utfchar >>= 6;
							target[ -2 ] = (::booldog::byte)((utfchar | 0x80) & 0xBF); utfchar >>= 6;
							target[ -3 ] = (::booldog::byte)( utfchar | ::booldog::consts::utf32::_firstByteMark[ 3 ] );
						}
						else if( utfchar <= (::booldog::uint32)0x0010FFFF )
						{
							target += 4;
							if( target > target_end )
								goto goto_conversion_result_targetExhausted;
							target[ -1 ] = (::booldog::byte)((utfchar | 0x80) & 0xBF); utfchar >>= 6;
							target[ -2 ] = (::booldog::byte)((utfchar | 0x80) & 0xBF); utfchar >>= 6;
							target[ -3 ] = (::booldog::byte)((utfchar | 0x80) & 0xBF); utfchar >>= 6;
							target[ -4 ] = (::booldog::byte)( utfchar | ::booldog::consts::utf32::_firstByteMark[ 4 ] );
						} 
						else
							return ::booldog::enums::string::conversion_result_sourceIllegal;
					}								
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
			}
			if( target )
				dst_bytes = (char*)target - dst_ptr;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			while( source < source_end )
			{
				if( *source <= 0x7f )
				{
					if( *source == 0 )
					{
						target++;
						break;
					}
					utfchar = *source++;
				}
				else if( (*source >> 5 ) == 0x6 )
				{
					source += 2;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar = source[-2];
					utfchar <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-1];
					utfchar -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
				}
				else if( ( *source >> 4 ) == 0x0e )
				{
					source += 3;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar = source[-3];
					utfchar <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-2];
					utfchar <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-1];
					utfchar -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
				}
				else if( ( *source >> 3 ) == 0x1e )
				{
					source += 4;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar = source[-4];
					utfchar <<= 6;
					if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-3];
					utfchar <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-2];
					utfchar <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-1];
					utfchar -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				if( utfchar <= (::booldog::uint32)0x0010FFFF ) 
				{
					if( utfchar >= (::booldog::uint32)0xD800 && utfchar <= (::booldog::uint32)0xDFFF )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					else
					{
						if( utfchar > 0x60 && utfchar < 0x7b )
						{
							utfchar -= 0x20;
						}
						else if( utfchar > 0xdf && utfchar < 0xff )
						{
							switch( utfchar )
							{
							case 0xf7:
								break;
							default:
								utfchar -= 0x20;
							}
						}
						else if( utfchar > 0x0100 && utfchar < 0x0138 )
						{
							if( ::booldog::utils::odd( utfchar ) )
							{
								switch( utfchar )
								{
								case 0x0130:
								case 0x0131:
								case 0x0132:
									break;
								default:
									utfchar--;
								}
							}
						}
						else if( utfchar > 0x0139 && utfchar < 0x0149 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0x014a && utfchar < 0x0178 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x0179 && utfchar < 0x017f )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0x0182 && utfchar < 0x0186 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x01a0 && utfchar < 0x01ae )
						{
							if( ::booldog::utils::odd( utfchar ) )
							{
								switch( utfchar )
								{
								case 0x01a6:
								case 0x01a7:
								case 0x01a9:
								case 0x01aa:
								case 0x01ab:
								case 0x01ac:
									break;
								case 0x01a8:
									{
										utfchar = 0x01a7;
										break;
									}
								default:
									utfchar--;
								}
							}
						}
						else if( utfchar > 0x01b3 && utfchar < 0x01b7 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0x01cd && utfchar < 0x01dd )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0x01de && utfchar < 0x0234 )
						{
							if( ::booldog::utils::odd( utfchar ) )
							{
								switch( utfchar )
								{
								case 0x01f0:
								case 0x01f1:
								case 0x01f2:
								case 0x01f4:
								case 0x01f6:
								case 0x01f7:
								case 0x01f8:
								case 0x0220:
								case 0x0221:
								case 0x0222:
									break;
								case 0x01f3:
									{
										utfchar = 0x01f1;
										break;
									}
								default:
									utfchar--;
								}
							}
						}
						else if( utfchar > 0x0246 && utfchar < 0x0250 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x0255 && utfchar < 0x0258 )
						{
							utfchar -= 0xcd;
						}
						else if( utfchar > 0x0289 && utfchar < 0x028c )
						{
							utfchar -= 0xd9;
						}
						else if( utfchar > 0x0370 && utfchar < 0x0378 )
						{
							if( ::booldog::utils::odd( utfchar ) )
							{
								switch( utfchar )
								{
								case 0x0374:
								case 0x0375:
								case 0x0376:
									break;
								default:
									utfchar--;
								}
							}
						}
						else if( utfchar > 0x037a && utfchar < 0x037e )
						{
							utfchar += 0x82;
						}
						else if( utfchar > 0x03ac && utfchar < 0x03b0 )
						{
							utfchar -= 0x25;
						}
						else if( utfchar > 0x03b0 && utfchar < 0x03cc )
						{
							switch( utfchar )
							{
							case 0x03c2:
								break;
							default:
								utfchar -= 0x20;
							}
						}
						else if( utfchar > 0x03cc && utfchar < 0x03cf )
						{
							utfchar -= 0x3f;
						}
						else if( utfchar > 0x03d8 && utfchar < 0x03f0 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x042f && utfchar < 0x0450 )
						{
							utfchar -= 0x20;
						}
						else if( utfchar > 0x044f && utfchar < 0x0460 )
						{
							utfchar -= 0x50;
						}
						else if( utfchar > 0x0460 && utfchar < 0x0482 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x048a && utfchar < 0x04c0 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x04c1 && utfchar < 0x04cf )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0x04d0 && utfchar < 0x0524 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x0560 && utfchar < 0x0587 )
						{
							utfchar -= 0x30;
						}
						else if( utfchar > 0x1e00 && utfchar < 0x1e96 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x1ea0 && utfchar < 0x1f00 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x1eff && utfchar < 0x1f08 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f0f && utfchar < 0x1f16 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f1f && utfchar < 0x1f28 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f2f && utfchar < 0x1f38 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f3f && utfchar < 0x1f46 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f5f && utfchar < 0x1f68 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f6f && utfchar < 0x1f72 )
						{
							utfchar += 0x4a;
						}
						else if( utfchar > 0x1f71 && utfchar < 0x1f76 )
						{
							utfchar += 0x56;
						}
						else if( utfchar > 0x1f75 && utfchar < 0x1f78 )
						{
							utfchar += 0x64;
						}
						else if( utfchar > 0x1f77 && utfchar < 0x1f7a )
						{
							utfchar += 0x80;
						}
						else if( utfchar > 0x1f79 && utfchar < 0x1f7c )
						{
							utfchar += 0x70;
						}
						else if( utfchar > 0x1f7b && utfchar < 0x1f7e )
						{
							utfchar += 0x7e;
						}
						else if( utfchar > 0x1f7f && utfchar < 0x1f88 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f8f && utfchar < 0x1f98 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1f9f && utfchar < 0x1fa8 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1faf && utfchar < 0x1fb2 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1fcf && utfchar < 0x1fd2 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x1fdf && utfchar < 0x1fe2 )
						{
							utfchar += 0x08;
						}
						else if( utfchar > 0x216f && utfchar < 0x2180 )
						{
							utfchar -= 0x10;
						}
						else if( utfchar > 0x24cf && utfchar < 0x24ea )
						{
							utfchar -= 0x1a;
						}
						else if( utfchar > 0x2c2f && utfchar < 0x2c5f )
						{
							utfchar -= 0x30;
						}
						else if( utfchar > 0x2c67 && utfchar < 0x2c6d )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0x2c80 && utfchar < 0x2ce4 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0x2cff && utfchar < 0x2d26 )
						{
							utfchar -= 0x1c60;
						}
						else if( utfchar > 0xa640 && utfchar < 0xa66e )
						{
							if( ::booldog::utils::odd( utfchar ) )
							{
								switch( utfchar )
								{
								case 0xa660:
								case 0xa661:
								case 0xa662:
									break;
								default:
									utfchar--;
								}
							}
						}
						else if( utfchar > 0xa680 && utfchar < 0xa698 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0xa722 && utfchar < 0xa770 )
						{
							if( ::booldog::utils::odd( utfchar ) )
							{
								switch( utfchar )
								{
								case 0xa730:
								case 0xa731:
								case 0xa732:
									break;
								default:
									utfchar--;
								}
							}
						}
						else if( utfchar > 0xa779 && utfchar < 0xa77d )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar--;
						}
						else if( utfchar > 0xa77e && utfchar < 0xa788 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar--;
						}
						else if( utfchar > 0xff40 && utfchar < 0xff5b )
						{
							utfchar -= 0x20;
						}
						else
						{
							switch( utfchar )
							{
							case 0xff:
								utfchar = 0x0178;
								break;
							case 0x0180:
								utfchar = 0x0243;
								break;
							case 0x0188:
								utfchar = 0x0187;
								break;
							case 0x018c:
								utfchar = 0x018b;
								break;
							case 0x0192:
								utfchar = 0x0191;
								break;
							case 0x0195:
								utfchar = 0x01f6;
								break;
							case 0x0199:
								utfchar = 0x0198;
								break;
							case 0x019a:
								utfchar = 0x023d;
								break;
							case 0x019e:
								utfchar = 0x0220;
								break;
							case 0x01a8:
								utfchar = 0x01a7;
								break;
							case 0x01b0:
								utfchar = 0x01af;
								break;
							case 0x01b9:
								utfchar = 0x01b8;
								break;
							case 0x01bd:
								utfchar = 0x01bc;
								break;
							case 0x01bf:
								utfchar = 0x01f7;
								break;
							case 0x01c6:
								utfchar = 0x01c4;
								break;
							case 0x01c9:
								utfchar = 0x01c7;
								break;
							case 0x01cc:
								utfchar = 0x01ca;
								break;
							case 0x01dd:
								utfchar = 0x018e;
								break;
							case 0x01f3:
								utfchar = 0x01f1;
								break;
							case 0x023c:
								utfchar = 0x023b;
								break;
							case 0x0242:
								utfchar = 0x0241;
								break;
							case 0x0250:
								utfchar = 0x2c6f;
								break;
							case 0x0251:
								utfchar = 0x2c6d;
								break;
							case 0x0253:
								utfchar = 0x0181;
								break;
							case 0x0254:
								utfchar = 0x0186;
								break;
							case 0x0259:
								utfchar = 0x018f;
								break;
							case 0x025b:
								utfchar = 0x0190;
								break;
							case 0x0260:
								utfchar = 0x0193;
								break;
							case 0x0263:
								utfchar = 0x0194;
								break;
							case 0x0268:
								utfchar = 0x0197;
								break;
							case 0x0269:
								utfchar = 0x0196;
								break;
							case 0x026b:
								utfchar = 0x2c62;
								break;
							case 0x026f:
								utfchar = 0x019c;
								break;
							case 0x0271:
								utfchar = 0x2c6e;
								break;
							case 0x0272:
								utfchar = 0x019d;
								break;
							case 0x0275:
								utfchar = 0x019f;
								break;
							case 0x027d:
								utfchar = 0x2c64;
								break;
							case 0x0280:
								utfchar = 0x01a6;
								break;
							case 0x0283:
								utfchar = 0x01a9;
								break;
							case 0x0288:
								utfchar = 0x01ae;
								break;
							case 0x0289:
								utfchar = 0x0244;
								break;
							case 0x028c:
								utfchar = 0x0245;
								break;
							case 0x0292:
								utfchar = 0x01b7;
								break;
							case 0x03ac:
								utfchar = 0x0386;
								break;
							case 0x03cc:
								utfchar = 0x038c;
								break;
							case 0x03d7:
								utfchar = 0x03cf;
								break;
							case 0x03f2:
								utfchar = 0x03f9;
								break;
							case 0x03f8:
								utfchar = 0x03f7;
								break;
							case 0x03fb:
								utfchar = 0x03fa;
								break;
							case 0x04cf:
								utfchar = 0x04c0;
								break;
							case 0x1d79:
								utfchar = 0xa77d;
								break;
							case 0x1d7d:
								utfchar = 0x2c63;
								break;
							case 0x1f51:
								utfchar = 0x1f59;
								break;
							case 0x1f53:
								utfchar = 0x1f5b;
								break;
							case 0x1f55:
								utfchar = 0x1f5d;
								break;
							case 0x1f57:
								utfchar = 0x1f5f;
								break;
							case 0x1fb3:
								utfchar = 0x1fbc;
								break;
							case 0x1fc3:
								utfchar = 0x1fcc;
								break;
							case 0x1fe5:
								utfchar = 0x1fec;
								break;
							case 0x1ff3:
								utfchar = 0x1ffc;
								break;
							case 0x214e:
								utfchar = 0x2132;
								break;
							case 0x2184:
								utfchar = 0x2183;
								break;
							case 0x2c61:
								utfchar = 0x2c60;
								break;
							case 0x2c65:
								utfchar = 0x023a;
								break;
							case 0x2c66:
								utfchar = 0x023e;
								break;
							case 0x2c73:
								utfchar = 0x2c72;
								break;
							case 0x2c76:
								utfchar = 0x2c75;
								break;
							case 0xa78c:
								utfchar = 0xa78b;
								break;
							}
						}
						if( utfchar >= (::booldog::uint32)0xD800 && utfchar <= (::booldog::uint32)0xDFFF )
							return ::booldog::enums::string::conversion_result_sourceIllegal;
						if( utfchar < (::booldog::uint32)0x80 )
							target += 1;
						else if( utfchar < (::booldog::uint32)0x800 )
							target += 2;
						else if( utfchar < (::booldog::uint32)0x10000 )
							target += 3;
						else if( utfchar <= (::booldog::uint32)0x0010FFFF )
							target += 4;
						else
							return ::booldog::enums::string::conversion_result_sourceIllegal;
					}								
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
			}
			if( target )
				dst_bytes = (char*)target - dst_ptr;
			return ::booldog::enums::string::conversion_result_targetExhausted;
		};
		booinline bool isalpha( ::booldog::uint32 utf8char )
		{
			::booldog::uint32 utfchar = 0;
			const ::booldog::byte* source = (::booldog::byte*)&utf8char;
			if( *source <= 0x7f )
			{
				if( *source == 0 )
					return false;
				utfchar = *source++;
			}
			else if( (*source >> 5 ) == 0x6 )
			{
				source += 2;
				utfchar = source[-2];
				utfchar <<= 6;
				if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-1];
				utfchar -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
			}
			else if( ( *source >> 4 ) == 0x0e )
			{
				source += 3;
				utfchar = source[-3];
				utfchar <<= 6;
				if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-2];
				utfchar <<= 6;
				if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-1];
				utfchar -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
			}
			else if( ( *source >> 3 ) == 0x1e )
			{
				source += 4;
				utfchar = source[-4];
				utfchar <<= 6;
				if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-3];
				utfchar <<= 6;
				if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-2];
				utfchar <<= 6;
				if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-1];
				utfchar -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
			}
			else
				return false;
			if( utfchar <= (::booldog::uint32)0x0010FFFF ) 
			{
				if( utfchar >= (::booldog::uint32)0xD800 && utfchar <= (::booldog::uint32)0xDFFF )
					return false;
				else
					return ::booldog::utf32::isalpha( utfchar );
			}
			else
				return false;
		};
		booinline bool isdigit( ::booldog::uint32 utf8char )
		{
			::booldog::uint32 utfchar = 0;
			const ::booldog::byte* source = (::booldog::byte*)&utf8char;
			if( *source <= 0x7f )
			{
				if( *source == 0 )
					return false;
				utfchar = *source++;
			}
			else if( (*source >> 5 ) == 0x6 )
			{
				source += 2;
				utfchar = source[-2];
				utfchar <<= 6;
				if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-1];
				utfchar -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
			}
			else if( ( *source >> 4 ) == 0x0e )
			{
				source += 3;
				utfchar = source[-3];
				utfchar <<= 6;
				if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-2];
				utfchar <<= 6;
				if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-1];
				utfchar -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
			}
			else if( ( *source >> 3 ) == 0x1e )
			{
				source += 4;
				utfchar = source[-4];
				utfchar <<= 6;
				if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-3];
				utfchar <<= 6;
				if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-2];
				utfchar <<= 6;
				if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-1];
				utfchar -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
			}
			else
				return false;
			if( utfchar <= (::booldog::uint32)0x0010FFFF ) 
			{
				if( utfchar >= (::booldog::uint32)0xD800 && utfchar <= (::booldog::uint32)0xDFFF )
					return false;
				else
					return ::booldog::utf32::isdigit( utfchar );
			}
			else
				return false;
		};
		booinline bool isalnum( ::booldog::uint32 utf8char )
		{
			::booldog::uint32 utfchar = 0;
			const ::booldog::byte* source = (::booldog::byte*)&utf8char;
			if( *source <= 0x7f )
			{
				if( *source == 0 )
					return false;
				utfchar = *source++;
			}
			else if( (*source >> 5 ) == 0x6 )
			{
				source += 2;
				utfchar = source[-2];
				utfchar <<= 6;
				if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-1];
				utfchar -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
			}
			else if( ( *source >> 4 ) == 0x0e )
			{
				source += 3;
				utfchar = source[-3];
				utfchar <<= 6;
				if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-2];
				utfchar <<= 6;
				if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-1];
				utfchar -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
			}
			else if( ( *source >> 3 ) == 0x1e )
			{
				source += 4;
				utfchar = source[-4];
				utfchar <<= 6;
				if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-3];
				utfchar <<= 6;
				if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-2];
				utfchar <<= 6;
				if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utfchar += source[-1];
				utfchar -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
			}
			else
				return false;
			if( utfchar <= (::booldog::uint32)0x0010FFFF ) 
			{
				if( utfchar >= (::booldog::uint32)0xD800 && utfchar <= (::booldog::uint32)0xDFFF )
					return false;
				else
					return ::booldog::utf32::isalnum( utfchar );
			}
			else
				return false;
		};
		booinline size_t char_length( const ::booldog::byte* utf8 )
		{
			if( *utf8 <= 0x7f )
				return 1;
			else if( (*utf8 >> 5 ) == 0x6 )
			{
				utf8++;
				if( !( ( *utf8 >> 6 ) == 0x2 ) )
					return SIZE_MAX;
				return 2;
			}
			/* three byte */
			else if( ( *utf8 >> 4 ) == 0x0e ) 
			{
				utf8++;
				if( !( ( *utf8 >> 6 ) == 0x2 ) )
					return SIZE_MAX;
				utf8++;
				if( !( ( *utf8 >> 6 ) == 0x2 ) )
					return SIZE_MAX;
				return 3;
			}
			/* four byte */        
			else if( ( *utf8 >> 3 ) == 0x1e )
			{
				utf8++;
				if( !( ( *utf8 >> 6 ) == 0x2 ) )
					return SIZE_MAX;
				utf8++;
				if( !( ( *utf8 >> 6 ) == 0x2 ) )
					return SIZE_MAX;
				utf8++;
				if( !( ( *utf8 >> 6 ) == 0x2 ) )
					return SIZE_MAX;
				return 4;
			}
			return SIZE_MAX;
		};
		booinline ::booldog::enums::string::conversion_result to_lower( const char* src_ptr , size_t src_ptr_count , char* dst_ptr , size_t dst_ptr_count , size_t& dst_bytes )
		{
			const ::booldog::uint8* source = (::booldog::uint8*)src_ptr , * source_end = (::booldog::uint8*)( src_ptr + src_ptr_count );
			::booldog::uint8* target = (::booldog::uint8*)dst_ptr , * target_end = (::booldog::uint8*)( dst_ptr + dst_ptr_count );
			::booldog::uint32 utfchar = 0;
			while( source < source_end )
			{
				if( *source <= 0x7f )
				{
					if( *source == 0 )
					{
						if( target < target_end )
							*target++ = 0;
						break;
					}
					utfchar = *source++;
				}
				else if( (*source >> 5 ) == 0x6 )
				{
					source += 2;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar = source[-2];
					utfchar <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-1];
					utfchar -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
				}
				else if( ( *source >> 4 ) == 0x0e )
				{
					source += 3;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar = source[-3];
					utfchar <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-2];
					utfchar <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-1];
					utfchar -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
				}
				else if( ( *source >> 3 ) == 0x1e )
				{
					source += 4;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar = source[-4];
					utfchar <<= 6;
					if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-3];
					utfchar <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-2];
					utfchar <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-1];
					utfchar -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				if( utfchar <= (::booldog::uint32)0x0010FFFF ) 
				{
					if( utfchar >= (::booldog::uint32)0xD800 && utfchar <= (::booldog::uint32)0xDFFF )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					else
					{
						if( utfchar > 0x40 && utfchar < 0x5b )
						{
							utfchar += 0x20;
						}
						else if( utfchar > 0xbf && utfchar < 0xdf )
						{
							switch( utfchar )
							{
							case 0xd7:
								break;
							default:
								utfchar += 0x20;
							}
						}
						else if( utfchar > 0xff && utfchar < 0x0137 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
							{
								switch( utfchar )
								{
								case 0x012f:
								case 0x0130:
								case 0x0131:
									break;
								default:
									utfchar++;
								}
							}
						}
						else if( utfchar > 0x0138 && utfchar < 0x0148 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0x0149 && utfchar < 0x0177 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x0178 && utfchar < 0x017e )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0x0181 && utfchar < 0x0185 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x0188 && utfchar < 0x018b )
						{
							utfchar += 0xcd;
						}
						else if( utfchar > 0x019f && utfchar < 0x01a5 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x01b0 && utfchar < 0x01b3 )
						{
							utfchar += 0xd9;
						}
						else if( utfchar > 0x01b2 && utfchar < 0x01b6 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0x01cc && utfchar < 0x01dc )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0x01dd && utfchar < 0x01f5 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
							{
								switch( utfchar )
								{
								case 0x01ef:
								case 0x01f0:
								case 0x01f2:
								case 0x01f3:
									break;
								case 0x01f1:
									{
										utfchar = 0x01f3;
										break;
									}
								default:
									utfchar++;
								}
							}
						}
						else if( utfchar > 0x01f7 && utfchar < 0x0233 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
							{
								switch( utfchar )
								{
								case 0x021f:
								case 0x0221:
									break;
								case 0x0220:
									{
										utfchar = 0x019e;
										break;
									}
								default:
									utfchar++;
								}
							}
						}
						else if( utfchar > 0x0245 && utfchar < 0x024f )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x036f && utfchar < 0x0377 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
							{
								switch( utfchar )
								{
								case 0x0373:
								case 0x0374:
								case 0x0375:
									break;
								default:
									utfchar++;
								}
							}
						}
						else if( utfchar > 0x0387 && utfchar < 0x038b )
						{
							utfchar += 0x25;
						}
						else if( utfchar > 0x038d && utfchar < 0x0390 )
						{
							utfchar += 0x3f;
						}
						else if( utfchar > 0x0390 && utfchar < 0x03ac )
						{
							switch( utfchar )
							{
							case 0x03a2:
								break;
							default:
								utfchar += 0x20;
							}
						}
						else if( utfchar > 0x03d7 && utfchar < 0x03ef )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x03fc && utfchar < 0x0400 )
						{
							utfchar -= 0x82;
						}
						else if( utfchar > 0x03ff && utfchar < 0x0410 )
						{
							utfchar += 0x50;
						}
						else if( utfchar > 0x040f && utfchar < 0x0430 )
						{
							utfchar += 0x20;
						}
						else if( utfchar > 0x045f && utfchar < 0x0481 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x0489 && utfchar < 0x04bf )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x04c0 && utfchar < 0x04ce )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0x04cf && utfchar < 0x0523 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x0530 && utfchar < 0x0557 )
						{
							utfchar += 0x30;
						}
						else if( utfchar > 0x109f && utfchar < 0x10c6 )
						{
							utfchar += 0x1c60;
						}
						else if( utfchar > 0x1dff && utfchar < 0x1e95 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x1e9f && utfchar < 0x1eff )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x1f07 && utfchar < 0x1f10 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f17 && utfchar < 0x1f1e )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f27 && utfchar < 0x1f30 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f37 && utfchar < 0x1f40 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f47 && utfchar < 0x1f4e )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f67 && utfchar < 0x1f70 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f87 && utfchar < 0x1f90 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f97 && utfchar < 0x1fa0 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1fa7 && utfchar < 0x1fb0 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1fb7 && utfchar < 0x1fba )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1fb9 && utfchar < 0x1fbc )
						{
							utfchar -= 0x4a;
						}
						else if( utfchar > 0x1fc7 && utfchar < 0x1fcc )
						{
							utfchar -= 0x56;
						}
						else if( utfchar > 0x1fd7 && utfchar < 0x1fda )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1fd9 && utfchar < 0x1fdc )
						{
							utfchar -= 0x64;
						}
						else if( utfchar > 0x1fe7 && utfchar < 0x1fea )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1fe9 && utfchar < 0x1fec )
						{
							utfchar -= 0x70;
						}
						else if( utfchar > 0x1ff7 && utfchar < 0x1ffa )
						{
							utfchar -= 0x80;
						}
						else if( utfchar > 0x1ff9 && utfchar < 0x1ffc )
						{
							utfchar -= 0x7e;
						}
						else if( utfchar > 0x215f && utfchar < 0x2170 )
						{
							utfchar += 0x10;
						}
						else if( utfchar > 0x24b5 && utfchar < 0x24d0 )
						{
							utfchar += 0x1a;
						}
						else if( utfchar > 0x2bff && utfchar < 0x2c2f )
						{
							utfchar += 0x30;
						}
						else if( utfchar > 0x2c66 && utfchar < 0x2c6c )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0x2c7f && utfchar < 0x2ce3 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0xa63f && utfchar < 0xa66d )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
							{
								switch( utfchar )
								{
								case 0xa65f:
								case 0xa660:
								case 0xa661:
									break;
								default:
									utfchar++;
								}
							}
						}
						else if( utfchar > 0xa67f && utfchar < 0xa697 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0xa721 && utfchar < 0xa76f )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
							{
								switch( utfchar )
								{
								case 0xa72f:
								case 0xa730:
								case 0xa731:
									break;
								default:
									utfchar++;
								}
							}
						}
						else if( utfchar > 0xa778 && utfchar < 0xa77c )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0xa77d && utfchar < 0xa787 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0xff20 && utfchar < 0xff3b )
						{
							utfchar += 0x20;
						}
						else
						{
							switch( utfchar )
							{
							case 0x0178:
								utfchar = 0xff;
								break;
							case 0x0181:
								utfchar = 0x0253;
								break;
							case 0x0186:
								utfchar = 0x0254;
								break;
							case 0x0187:
								utfchar = 0x0188;
								break;
							case 0x018b:
								utfchar = 0x018c;
								break;
							case 0x018e:
								utfchar = 0x01dd;
								break;
							case 0x018f:
								utfchar = 0x0259;
								break;
							case 0x0190:
								utfchar = 0x025b;
								break;
							case 0x0191:
								utfchar = 0x0192;
								break;
							case 0x0193:
								utfchar = 0x0260;
								break;
							case 0x0194:
								utfchar = 0x0263;
								break;
							case 0x0196:
								utfchar = 0x0269;
								break;
							case 0x0197:
								utfchar = 0x0268;
								break;
							case 0x0198:
								utfchar = 0x0199;
								break;
							case 0x019c:
								utfchar = 0x026f;
								break;
							case 0x019d:
								utfchar = 0x0272;
								break;
							case 0x019f:
								utfchar = 0x0275;
								break;
							case 0x01a6:
								utfchar = 0x0280;
								break;
							case 0x01a7:
								utfchar = 0x01a8;
								break;
							case 0x01a9:
								utfchar = 0x0283;
								break;
							case 0x01ac:
								utfchar = 0x01ad;
								break;
							case 0x01ae:
								utfchar = 0x0288;
								break;
							case 0x01af:
								utfchar = 0x01b0;
								break;
							case 0x01b7:
								utfchar = 0x0292;
								break;
							case 0x01b8:
								utfchar = 0x01b9;
								break;
							case 0x01bc:
								utfchar = 0x01bd;
								break;
							case 0x01c4:
								utfchar = 0x01c6;
								break;
							case 0x01c7:
								utfchar = 0x01c9;
								break;
							case 0x01ca:
								utfchar = 0x01cc;
								break;
							case 0x01f1:
								utfchar = 0x01f3;
								break;
							case 0x01f6:
								utfchar = 0x0195;
								break;
							case 0x01f7:
								utfchar = 0x01bf;
								break;
							case 0x0220:
								utfchar = 0x019e;
								break;
							case 0x023a:
								utfchar = 0x2c65;
								break;
							case 0x023b:
								utfchar = 0x023c;
								break;
							case 0x023d:
								utfchar = 0x019a;
								break;
							case 0x023e:
								utfchar = 0x2c66;
								break;
							case 0x0241:
								utfchar = 0x0242;
								break;
							case 0x0243:
								utfchar = 0x0180;
								break;
							case 0x0244:
								utfchar = 0x0289;
								break;
							case 0x0245:
								utfchar = 0x028c;
								break;
							case 0x0386:
								utfchar = 0x03ac;
								break;
							case 0x038c:
								utfchar = 0x03cc;
								break;
							case 0x03cf:
								utfchar = 0x03d7;
								break;
							case 0x03f7:
								utfchar = 0x03f8;
								break;
							case 0x03f9:
								utfchar = 0x03f2;
								break;
							case 0x03fa:
								utfchar = 0x03fb;
								break;
							case 0x04c0:
								utfchar = 0x04cf;
								break;
							case 0x1f59:
								utfchar = 0x1f51;
								break;
							case 0x1f5b:
								utfchar = 0x1f53;
								break;
							case 0x1f5d:
								utfchar = 0x1f55;
								break;
							case 0x1f5f:
								utfchar = 0x1f57;
								break;
							case 0x1fbc:
								utfchar = 0x1fb3;
								break;
							case 0x1fcc:
								utfchar = 0x1fc3;
								break;
							case 0x1fec:
								utfchar = 0x1fe5;
								break;
							case 0x1ffc:
								utfchar = 0x1ff3;
								break;
							case 0x2132:
								utfchar = 0x214e;
								break;
							case 0x2183:
								utfchar = 0x2184;
								break;
							case 0x2c60:
								utfchar = 0x2c61;
								break;
							case 0x2c62:
								utfchar = 0x026b;
								break;
							case 0x2c63:
								utfchar = 0x1d7d;
								break;
							case 0x2c64:
								utfchar = 0x027d;
								break;
							case 0x2c6d:
								utfchar = 0x0251;
								break;
							case 0x2c6e:
								utfchar = 0x0271;
								break;
							case 0x2c6f:
								utfchar = 0x0250;
								break;
							case 0x2c72:
								utfchar = 0x2c73;
								break;
							case 0x2c75:
								utfchar = 0x2c76;
								break;
							case 0xa77d:
								utfchar = 0x1d79;
								break;
							case 0xa78b:
								utfchar = 0xa78c;
								break;
							}
						}

						if( utfchar >= (::booldog::uint32)0xD800 && utfchar <= (::booldog::uint32)0xDFFF )
							return ::booldog::enums::string::conversion_result_sourceIllegal;
						if( utfchar < (::booldog::uint32)0x80 )
						{
							target += 1;
							if( target > target_end )
								goto goto_conversion_result_targetExhausted;
							target[ -1 ] = (::booldog::byte)( utfchar | ::booldog::consts::utf32::_firstByteMark[ 1 ] );
						}
						else if( utfchar < (::booldog::uint32)0x800 )
						{
							target += 2;
							if( target > target_end )
								goto goto_conversion_result_targetExhausted;
							target[ -1 ] = (::booldog::byte)((utfchar | 0x80) & 0xBF); utfchar >>= 6;
							target[ -2 ] = (::booldog::byte)( utfchar | ::booldog::consts::utf32::_firstByteMark[ 2 ] );
						} 
						else if( utfchar < (::booldog::uint32)0x10000 )
						{
							target += 3;
							if( target > target_end )
								goto goto_conversion_result_targetExhausted;
							target[ -1 ] = (::booldog::byte)((utfchar | 0x80) & 0xBF); utfchar >>= 6;
							target[ -2 ] = (::booldog::byte)((utfchar | 0x80) & 0xBF); utfchar >>= 6;
							target[ -3 ] = (::booldog::byte)( utfchar | ::booldog::consts::utf32::_firstByteMark[ 3 ] );
						}
						else if( utfchar <= (::booldog::uint32)0x0010FFFF )
						{
							target += 4;
							if( target > target_end )
								goto goto_conversion_result_targetExhausted;
							target[ -1 ] = (::booldog::byte)((utfchar | 0x80) & 0xBF); utfchar >>= 6;
							target[ -2 ] = (::booldog::byte)((utfchar | 0x80) & 0xBF); utfchar >>= 6;
							target[ -3 ] = (::booldog::byte)((utfchar | 0x80) & 0xBF); utfchar >>= 6;
							target[ -4 ] = (::booldog::byte)( utfchar | ::booldog::consts::utf32::_firstByteMark[ 4 ] );
						} 
						else
							return ::booldog::enums::string::conversion_result_sourceIllegal;
					}								
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
			}
			if( target )
				dst_bytes = (char*)target - dst_ptr;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			while( source < source_end )
			{
				if( *source <= 0x7f )
				{
					if( *source == 0 )
					{
						if( target < target_end )
							*target++ = 0;
						break;
					}
					utfchar = *source++;
				}
				else if( (*source >> 5 ) == 0x6 )
				{
					source += 2;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar = source[-2];
					utfchar <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-1];
					utfchar -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
				}
				else if( ( *source >> 4 ) == 0x0e )
				{
					source += 3;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar = source[-3];
					utfchar <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-2];
					utfchar <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-1];
					utfchar -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
				}
				else if( ( *source >> 3 ) == 0x1e )
				{
					source += 4;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar = source[-4];
					utfchar <<= 6;
					if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-3];
					utfchar <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-2];
					utfchar <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					utfchar += source[-1];
					utfchar -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				if( utfchar <= (::booldog::uint32)0x0010FFFF ) 
				{
					if( utfchar >= (::booldog::uint32)0xD800 && utfchar <= (::booldog::uint32)0xDFFF )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					else
					{
						if( utfchar > 0x40 && utfchar < 0x5b )
						{
							utfchar += 0x20;
						}
						else if( utfchar > 0xbf && utfchar < 0xdf )
						{
							switch( utfchar )
							{
							case 0xd7:
								break;
							default:
								utfchar += 0x20;
							}
						}
						else if( utfchar > 0xff && utfchar < 0x0137 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
							{
								switch( utfchar )
								{
								case 0x012f:
								case 0x0130:
								case 0x0131:
									break;
								default:
									utfchar++;
								}
							}
						}
						else if( utfchar > 0x0138 && utfchar < 0x0148 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0x0149 && utfchar < 0x0177 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x0178 && utfchar < 0x017e )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0x0181 && utfchar < 0x0185 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x0188 && utfchar < 0x018b )
						{
							utfchar += 0xcd;
						}
						else if( utfchar > 0x019f && utfchar < 0x01a5 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x01b0 && utfchar < 0x01b3 )
						{
							utfchar += 0xd9;
						}
						else if( utfchar > 0x01b2 && utfchar < 0x01b6 )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0x01cc && utfchar < 0x01dc )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0x01dd && utfchar < 0x01f5 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
							{
								switch( utfchar )
								{
								case 0x01ef:
								case 0x01f0:
								case 0x01f2:
								case 0x01f3:
									break;
								case 0x01f1:
									{
										utfchar = 0x01f3;
										break;
									}
								default:
									utfchar++;
								}
							}
						}
						else if( utfchar > 0x01f7 && utfchar < 0x0233 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
							{
								switch( utfchar )
								{
								case 0x021f:
								case 0x0221:
									break;
								case 0x0220:
									{
										utfchar = 0x019e;
										break;
									}
								default:
									utfchar++;
								}
							}
						}
						else if( utfchar > 0x0245 && utfchar < 0x024f )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x036f && utfchar < 0x0377 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
							{
								switch( utfchar )
								{
								case 0x0373:
								case 0x0374:
								case 0x0375:
									break;
								default:
									utfchar++;
								}
							}
						}
						else if( utfchar > 0x0387 && utfchar < 0x038b )
						{
							utfchar += 0x25;
						}
						else if( utfchar > 0x038d && utfchar < 0x0390 )
						{
							utfchar += 0x3f;
						}
						else if( utfchar > 0x0390 && utfchar < 0x03ac )
						{
							switch( utfchar )
							{
							case 0x03a2:
								break;
							default:
								utfchar += 0x20;
							}
						}
						else if( utfchar > 0x03d7 && utfchar < 0x03ef )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x03fc && utfchar < 0x0400 )
						{
							utfchar -= 0x82;
						}
						else if( utfchar > 0x03ff && utfchar < 0x0410 )
						{
							utfchar += 0x50;
						}
						else if( utfchar > 0x040f && utfchar < 0x0430 )
						{
							utfchar += 0x20;
						}
						else if( utfchar > 0x045f && utfchar < 0x0481 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x0489 && utfchar < 0x04bf )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x04c0 && utfchar < 0x04ce )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0x04cf && utfchar < 0x0523 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x0530 && utfchar < 0x0557 )
						{
							utfchar += 0x30;
						}
						else if( utfchar > 0x109f && utfchar < 0x10c6 )
						{
							utfchar += 0x1c60;
						}
						else if( utfchar > 0x1dff && utfchar < 0x1e95 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x1e9f && utfchar < 0x1eff )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0x1f07 && utfchar < 0x1f10 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f17 && utfchar < 0x1f1e )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f27 && utfchar < 0x1f30 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f37 && utfchar < 0x1f40 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f47 && utfchar < 0x1f4e )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f67 && utfchar < 0x1f70 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f87 && utfchar < 0x1f90 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1f97 && utfchar < 0x1fa0 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1fa7 && utfchar < 0x1fb0 )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1fb7 && utfchar < 0x1fba )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1fb9 && utfchar < 0x1fbc )
						{
							utfchar -= 0x4a;
						}
						else if( utfchar > 0x1fc7 && utfchar < 0x1fcc )
						{
							utfchar -= 0x56;
						}
						else if( utfchar > 0x1fd7 && utfchar < 0x1fda )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1fd9 && utfchar < 0x1fdc )
						{
							utfchar -= 0x64;
						}
						else if( utfchar > 0x1fe7 && utfchar < 0x1fea )
						{
							utfchar -= 0x08;
						}
						else if( utfchar > 0x1fe9 && utfchar < 0x1fec )
						{
							utfchar -= 0x70;
						}
						else if( utfchar > 0x1ff7 && utfchar < 0x1ffa )
						{
							utfchar -= 0x80;
						}
						else if( utfchar > 0x1ff9 && utfchar < 0x1ffc )
						{
							utfchar -= 0x7e;
						}
						else if( utfchar > 0x215f && utfchar < 0x2170 )
						{
							utfchar += 0x10;
						}
						else if( utfchar > 0x24b5 && utfchar < 0x24d0 )
						{
							utfchar += 0x1a;
						}
						else if( utfchar > 0x2bff && utfchar < 0x2c2f )
						{
							utfchar += 0x30;
						}
						else if( utfchar > 0x2c66 && utfchar < 0x2c6c )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0x2c7f && utfchar < 0x2ce3 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0xa63f && utfchar < 0xa66d )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
							{
								switch( utfchar )
								{
								case 0xa65f:
								case 0xa660:
								case 0xa661:
									break;
								default:
									utfchar++;
								}
							}
						}
						else if( utfchar > 0xa67f && utfchar < 0xa697 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0xa721 && utfchar < 0xa76f )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
							{
								switch( utfchar )
								{
								case 0xa72f:
								case 0xa730:
								case 0xa731:
									break;
								default:
									utfchar++;
								}
							}
						}
						else if( utfchar > 0xa778 && utfchar < 0xa77c )
						{
							if( ::booldog::utils::odd( utfchar ) )
								utfchar++;
						}
						else if( utfchar > 0xa77d && utfchar < 0xa787 )
						{
							if( ::booldog::utils::odd( utfchar ) == false )
								utfchar++;
						}
						else if( utfchar > 0xff20 && utfchar < 0xff3b )
						{
							utfchar += 0x20;
						}
						else
						{
							switch( utfchar )
							{
							case 0x0178:
								utfchar = 0xff;
								break;
							case 0x0181:
								utfchar = 0x0253;
								break;
							case 0x0186:
								utfchar = 0x0254;
								break;
							case 0x0187:
								utfchar = 0x0188;
								break;
							case 0x018b:
								utfchar = 0x018c;
								break;
							case 0x018e:
								utfchar = 0x01dd;
								break;
							case 0x018f:
								utfchar = 0x0259;
								break;
							case 0x0190:
								utfchar = 0x025b;
								break;
							case 0x0191:
								utfchar = 0x0192;
								break;
							case 0x0193:
								utfchar = 0x0260;
								break;
							case 0x0194:
								utfchar = 0x0263;
								break;
							case 0x0196:
								utfchar = 0x0269;
								break;
							case 0x0197:
								utfchar = 0x0268;
								break;
							case 0x0198:
								utfchar = 0x0199;
								break;
							case 0x019c:
								utfchar = 0x026f;
								break;
							case 0x019d:
								utfchar = 0x0272;
								break;
							case 0x019f:
								utfchar = 0x0275;
								break;
							case 0x01a6:
								utfchar = 0x0280;
								break;
							case 0x01a7:
								utfchar = 0x01a8;
								break;
							case 0x01a9:
								utfchar = 0x0283;
								break;
							case 0x01ac:
								utfchar = 0x01ad;
								break;
							case 0x01ae:
								utfchar = 0x0288;
								break;
							case 0x01af:
								utfchar = 0x01b0;
								break;
							case 0x01b7:
								utfchar = 0x0292;
								break;
							case 0x01b8:
								utfchar = 0x01b9;
								break;
							case 0x01bc:
								utfchar = 0x01bd;
								break;
							case 0x01c4:
								utfchar = 0x01c6;
								break;
							case 0x01c7:
								utfchar = 0x01c9;
								break;
							case 0x01ca:
								utfchar = 0x01cc;
								break;
							case 0x01f1:
								utfchar = 0x01f3;
								break;
							case 0x01f6:
								utfchar = 0x0195;
								break;
							case 0x01f7:
								utfchar = 0x01bf;
								break;
							case 0x0220:
								utfchar = 0x019e;
								break;
							case 0x023a:
								utfchar = 0x2c65;
								break;
							case 0x023b:
								utfchar = 0x023c;
								break;
							case 0x023d:
								utfchar = 0x019a;
								break;
							case 0x023e:
								utfchar = 0x2c66;
								break;
							case 0x0241:
								utfchar = 0x0242;
								break;
							case 0x0243:
								utfchar = 0x0180;
								break;
							case 0x0244:
								utfchar = 0x0289;
								break;
							case 0x0245:
								utfchar = 0x028c;
								break;
							case 0x0386:
								utfchar = 0x03ac;
								break;
							case 0x038c:
								utfchar = 0x03cc;
								break;
							case 0x03cf:
								utfchar = 0x03d7;
								break;
							case 0x03f7:
								utfchar = 0x03f8;
								break;
							case 0x03f9:
								utfchar = 0x03f2;
								break;
							case 0x03fa:
								utfchar = 0x03fb;
								break;
							case 0x04c0:
								utfchar = 0x04cf;
								break;
							case 0x1f59:
								utfchar = 0x1f51;
								break;
							case 0x1f5b:
								utfchar = 0x1f53;
								break;
							case 0x1f5d:
								utfchar = 0x1f55;
								break;
							case 0x1f5f:
								utfchar = 0x1f57;
								break;
							case 0x1fbc:
								utfchar = 0x1fb3;
								break;
							case 0x1fcc:
								utfchar = 0x1fc3;
								break;
							case 0x1fec:
								utfchar = 0x1fe5;
								break;
							case 0x1ffc:
								utfchar = 0x1ff3;
								break;
							case 0x2132:
								utfchar = 0x214e;
								break;
							case 0x2183:
								utfchar = 0x2184;
								break;
							case 0x2c60:
								utfchar = 0x2c61;
								break;
							case 0x2c62:
								utfchar = 0x026b;
								break;
							case 0x2c63:
								utfchar = 0x1d7d;
								break;
							case 0x2c64:
								utfchar = 0x027d;
								break;
							case 0x2c6d:
								utfchar = 0x0251;
								break;
							case 0x2c6e:
								utfchar = 0x0271;
								break;
							case 0x2c6f:
								utfchar = 0x0250;
								break;
							case 0x2c72:
								utfchar = 0x2c73;
								break;
							case 0x2c75:
								utfchar = 0x2c76;
								break;
							case 0xa77d:
								utfchar = 0x1d79;
								break;
							case 0xa78b:
								utfchar = 0xa78c;
								break;
							}
						}
						if( utfchar >= (::booldog::uint32)0xD800 && utfchar <= (::booldog::uint32)0xDFFF )
							return ::booldog::enums::string::conversion_result_sourceIllegal;
						if( utfchar < (::booldog::uint32)0x80 )
							target += 1;
						else if( utfchar < (::booldog::uint32)0x800 )
							target += 2;
						else if( utfchar < (::booldog::uint32)0x10000 )
							target += 3;
						else if( utfchar <= (::booldog::uint32)0x0010FFFF )
							target += 4;
						else
							return ::booldog::enums::string::conversion_result_sourceIllegal;
					}								
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
			}
			if( target )
				dst_bytes = (char*)target - dst_ptr;
			return ::booldog::enums::string::conversion_result_targetExhausted;
		};
		booinline ::booldog::enums::string::conversion_result to_utf16(const char* utf8_ptr, size_t& srcbyteindex
			, size_t utf8_ptr_count, char* utf16_ptr, size_t& dstbyteindex, size_t utf16_ptr_count, size_t& utf16_bytes
			, size_t& utf16length)
		{
			const ::booldog::uint8* source = (::booldog::uint8*)utf8_ptr + srcbyteindex
				, * source_end = (::booldog::uint8*)utf8_ptr + utf8_ptr_count;
			::booldog::uint16* target = (::booldog::uint16*)(utf16_ptr + dstbyteindex)
				, * target_end = (::booldog::uint16*)(utf16_ptr + utf16_ptr_count);
			::booldog::uint32 letter0 = 0;
			::booldog::byte diff = 0;
			if(utf16_ptr == 0)
				goto goto_conversion_result_targetExhausted;			
			while(source < source_end)
			{
				if( *source <= 0x7f )
				{
					diff = 1;
					if( *source == 0 )
					{
						if(target < target_end)
							*target++ = 0;
						break;
					}
					letter0 = *source++;
				}
				else if( ( *source >> 5 ) == 0x6 )
				{
					diff = 2;
					source += 2;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 = source[-2];
					letter0 <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-1];
					letter0 -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
				}
				else if( ( *source >> 4 ) == 0x0e )
				{
					diff = 3;
					source += 3;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 = source[-3];
					letter0 <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-2];
					letter0 <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-1];
					letter0 -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
				}
				else if( ( *source >> 3 ) == 0x1e )
				{
					diff = 4;
					source += 4;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 = source[-4];
					letter0 <<= 6;
					if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-3];
					letter0 <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-2];
					letter0 <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-1];
					letter0 -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				if( letter0 <= (::booldog::uint32)0x0000FFFF )
				{ /* Target is a character <= 0xFFFF */
					/* UTF-16 surrogate values are illegal in UTF-32 */
					if( letter0 >= (::booldog::uint32)0xD800 && letter0 <= (::booldog::uint32)0xDFFF )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					else
					{
						if( target < target_end )
							*target++ = (::booldog::uint16)letter0; /* normal case */
						else
						{
							target++;
							goto goto_conversion_result_targetExhausted;
						}
					}
				}
				else if( letter0 > (::booldog::uint32)0x0010FFFF )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				else 
				{
					/* target is a character in range 0xFFFF - 0x10FFFF. */
					target++;
					if( target >= target_end )
					{
						target++;
						goto goto_conversion_result_targetExhausted;
					}
					letter0 -= 0x0010000UL;
					*target = (::booldog::uint16)( ( letter0 >> 10 ) + (::booldog::uint32)0xD800 );
					*target++ = (::booldog::uint16)( ( letter0 & 0x3FFUL ) + (::booldog::uint32)0xDC00 );
				}
				++utf16length;
			}
			utf16_bytes = (char*)target - utf16_ptr;
			srcbyteindex = ((char*)source - utf8_ptr);
			dstbyteindex = utf16_bytes;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			if(utf16_ptr)
			{
				utf16_bytes = (char*)target - utf16_ptr;
				srcbyteindex = ((char*)source - utf8_ptr) - diff;
				dstbyteindex = utf16_bytes - 2;
			}
			while( source < source_end ) 
			{
				if(*source == 0)
				{
					utf16_bytes += 2;
					break;
				}
				else if( *source <= 0x7f )
					letter0 = *source++;
				else if( (*source >> 5 ) == 0x6 )
				{
					source += 2;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 = source[-2];
					letter0 <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-1];
					letter0 -= 0x00003080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 2 ];
				}
				else if( ( *source >> 4 ) == 0x0e )
				{
					source += 3;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 = source[-3];
					letter0 <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-2];
					letter0 <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-1];
					letter0 -= 0x000E2080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 3 ];
				}
				else if( ( *source >> 3 ) == 0x1e )
				{
					source += 4;
					if( source > source_end )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 = source[-4];
					letter0 <<= 6;
					if( !( ( source[ -3 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-3];
					letter0 <<= 6;
					if( !( ( source[ -2 ] >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-2];
					letter0 <<= 6;
					if( !( ( ( source[ -1 ] ) >> 6 ) == 0x2 ) )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					letter0 += source[-1];
					letter0 -= 0x03C82080UL;//::booldog::utils::string::utf8::_offsets_from_UTF8[ 4 ];
				}
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				if( letter0 <= (::booldog::uint32)0x0000FFFF )
				{
					if( letter0 >= (::booldog::uint32)0xD800 && letter0 <= (::booldog::uint32)0xDFFF )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
				}
				else if( letter0 > (::booldog::uint32)0x0010FFFF )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utf16_bytes += 2;
			}
			return ::booldog::enums::string::conversion_result_targetExhausted;
		}
		template< size_t step >
		booinline bool toutf16(::booldog::result* pres, booldog::allocator* allocator, char*& dst, size_t& dstlen, size_t& dstsize
			, const char* utf8, size_t& srcbyteindex, size_t utf8bytescount
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			::booldog::result locres;
			BOOINIT_RESULT(::booldog::result);
			size_t dstbyteindex = 0 , utf16bytes = 2 * step;
			::booldog::enums::string::conversion_result convres = ::booldog::enums::string::conversion_result_OK;
			for(;;)
			{
				if(dstsize < utf16bytes + 2)
				{
					dstsize = utf16bytes + 2;
					dst = allocator->realloc_array< char >(dst, dstsize, debuginfo);
				}
				if(dst == 0)
				{
					res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
					break;
				}
				convres = ::booldog::utf8::to_utf16(utf8, srcbyteindex, utf8bytescount, dst, dstbyteindex, dstsize, utf16bytes
					, dstlen);
				if(convres == ::booldog::enums::string::conversion_result_sourceIllegal)
				{
					res->booerr(::booldog::enums::result::booerr_type_conversion_result_source_illegal);
					break;
				}
				else if(convres == ::booldog::enums::string::conversion_result_OK)
				{
					if(utf16bytes == dstsize)
					{
						dstsize += 2;
						dst = allocator->realloc_array< char >(dst, dstsize, debuginfo);
						if(dst == 0)
						{
							res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							break;
						}
					}
					*((::booldog::uint16*)&dst[utf16bytes]) = 0;
					break;
				}
				else if(convres == ::booldog::enums::string::conversion_result_sourceExhausted)
				{
					res->booerr(::booldog::enums::result::booerr_type_conversion_result_source_exhausted);
					break;
				}
			}
			return res->succeeded();
		}
		template< size_t step >
		booinline bool toutf16(::booldog::result_mbchar& pres, const char* utf8, size_t& srcbyteindex, size_t utf8bytescount
			, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			size_t dstbyteindex = 0 , utf16bytes = 2 * step;
			::booldog::enums::string::conversion_result convres = ::booldog::enums::string::conversion_result_OK;
			for(;;)
			{
				if(pres.mbsize < utf16bytes + 2)
				{
					pres.mbsize = utf16bytes + 2;
					pres.mbchar = pres.mballocator->realloc_array< char >(pres.mbchar, pres.mbsize, debuginfo);
				}
				if(pres.mbchar == 0)
				{
					pres.booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
					return false;
				}
				convres = ::booldog::utf8::to_utf16(utf8, srcbyteindex, utf8bytescount, pres.mbchar, dstbyteindex, pres.mbsize
					, utf16bytes, pres.mblen);
				if(convres == ::booldog::enums::string::conversion_result_sourceIllegal)
				{
					pres.booerr(::booldog::enums::result::booerr_type_conversion_result_source_illegal);
					return false;
				}
				else if(convres == ::booldog::enums::string::conversion_result_OK)
				{
					if(utf16bytes == pres.mbsize)
					{
						pres.mbsize +=2;
						pres.mbchar = pres.mballocator->realloc_array< char >(pres.mbchar, pres.mbsize, debuginfo);
						if(pres.mbchar == 0)
						{
							pres.booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							return false;
						}
					}
					*((::booldog::uint16*)&pres.mbchar[utf16bytes]) = 0;
					break;
				}
				else if(convres == ::booldog::enums::string::conversion_result_sourceExhausted)
				{
					pres.booerr(::booldog::enums::result::booerr_type_conversion_result_source_exhausted);
					return false;
				}
			}
			return true;
		}
		template< size_t step >
		booinline bool toutf32(::booldog::result* pres, booldog::allocator* allocator, char*& dst, size_t& dstlen, size_t& dstsize
			, const char* utf8, size_t& srcbyteindex, size_t utf8bytescount
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			::booldog::result locres;
			BOOINIT_RESULT(::booldog::result);
			size_t dstbyteindex = 0 , utf32bytes = 4 * step;
			::booldog::enums::string::conversion_result convres = ::booldog::enums::string::conversion_result_OK;
			for(;;)
			{
				if(dstsize < utf32bytes + 4)
				{
					dstsize = utf32bytes + 4;
					dst = allocator->realloc_array< char >(dst, dstsize, debuginfo);
				}
				if(dst == 0)
				{
					res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
					break;
				}
				convres = ::booldog::utf8::to_utf32(utf8, srcbyteindex, utf8bytescount, dst, dstbyteindex, dstsize, utf32bytes
					, dstlen);
				if(convres == ::booldog::enums::string::conversion_result_sourceIllegal)
				{
					res->booerr(::booldog::enums::result::booerr_type_conversion_result_source_illegal);
					break;
				}
				else if(convres == ::booldog::enums::string::conversion_result_OK)
				{
					if(utf32bytes == dstsize)
					{
						dstsize += 4;
						dst = allocator->realloc_array< char >(dst, dstsize, debuginfo);
						if(dst == 0)
						{
							res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							break;
						}
					}
					*((::booldog::uint32*)&dst[utf32bytes]) = 0;
					break;
				}
				else if(convres == ::booldog::enums::string::conversion_result_sourceExhausted)
				{
					res->booerr(::booldog::enums::result::booerr_type_conversion_result_source_exhausted);
					break;
				}
			}
			return res->succeeded();
		}
		template< size_t step >
		booinline bool toutf32(::booldog::result_mbchar& pres, const char* utf8
			, size_t& srcbyteindex, size_t utf8bytescount, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			size_t dstbyteindex = 0 , utf32bytes = 4 * step;
			::booldog::enums::string::conversion_result convres = ::booldog::enums::string::conversion_result_OK;
			for(;;)
			{
				if(pres.mbsize < utf32bytes + 4)
				{
					pres.mbsize = utf32bytes + 4;
					pres.mbchar = pres.mballocator->realloc_array< char >(pres.mbchar, pres.mbsize, debuginfo);
				}
				if(pres.mbchar == 0)
				{
					pres.booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
					return false;
				}
				convres = ::booldog::utf8::to_utf32(utf8, srcbyteindex, utf8bytescount, pres.mbchar, dstbyteindex, pres.mbsize
					, utf32bytes, pres.mblen);
				if(convres == ::booldog::enums::string::conversion_result_sourceIllegal)
				{
					pres.booerr(::booldog::enums::result::booerr_type_conversion_result_source_illegal);
					return false;
				}
				else if(convres == ::booldog::enums::string::conversion_result_OK)
				{
					if(utf32bytes == pres.mbsize)
					{
						pres.mbsize += 4;
						pres.mbchar = pres.mballocator->realloc_array< char >(pres.mbchar, pres.mbsize, debuginfo);
						if(pres.mbchar == 0)
						{
							pres.booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							return false;
						}
					}
					*((::booldog::uint32*)&pres.mbchar[utf32bytes]) = 0;
					break;
				}
				else if(convres == ::booldog::enums::string::conversion_result_sourceExhausted)
				{
					pres.booerr(::booldog::enums::result::booerr_type_conversion_result_source_exhausted);
					return false;
				}
			}
			return true;
		}
	}
}
#endif
