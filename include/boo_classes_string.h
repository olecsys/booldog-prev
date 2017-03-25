/** class string
* Simplify work with C strings
*/

#ifndef BOO_CLASSES_STRING_H
#define BOO_CLASSES_STRING_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_string_utils.h"
#if defined(BOO_UTF16_H) && defined(BOO_UTF32_H)
#include "boo_if.h"
#endif
namespace booldog
{
	namespace classes
	{
		class string
		{
		public:
			::booldog::allocator* _allocator;///< allocator is used to allocate/deallocate _str member
			char* _str;                      ///< store C string data
			size_t _size;                    ///< the size of the allocated memory
			size_t _length;                  ///< the length of the C string _str member(without including the terminating null character itself)
		public:
			/** Default constructor
			* sets a allocator for the field _allocator
			* sets a null for the fields: _str, _size, _length			
			*/
			string(::booldog::allocator* allocator)
				: _allocator(allocator), _str(0), _size(0), _length(0)
			{
			}
			/** Default destructor
			* deallocate _str member
			*/
			~string()
			{
				if(_str)
					_allocator->free(_str);
			}
			/** Assign a new C string
			* @param pres store the function result or detailed error
			* @param str a new C string
			* @param debuginfo a debug information
			* @return The function result
			*/
			template< size_t step >
			bool assign(::booldog::result* pres, const char* str, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				return ::booldog::utils::string::mbs::assign< step >(pres, _allocator, false, 0, _str, _length, _size, str, 0, SIZE_MAX
					, debuginfo);
			}
			/** Assign a new C string
			* @param str a new C string
			* @return this
			*/
			booinline ::booldog::classes::string& operator =(const char* str)
			{
				assign< 16 >(0, str, debuginfo_macros);
				return *this;
			}
			/** Append a C string to _str
			* @param pres store the function result or detailed error
			* @param str a appended C string
			* @param debuginfo a debug information
			* @return The function result
			*/
			template< size_t step >
			bool append(::booldog::result* pres, const char* str, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				return ::booldog::utils::string::mbs::assign< step >(pres, _allocator, false, _length, _str, _length, _size, str, 0, SIZE_MAX
					, debuginfo);
			}
			/** Append a C string to _str
			* @param pres store the function result or detailed error
			* @param str a appended C string
			* @param debuginfo a debug information
			* @return The function result
			*/
			template< size_t step >
			bool append(::booldog::result* pres, char* str, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				return ::booldog::utils::string::mbs::assign< step >(pres, _allocator, false, _length, _str, _length, _size, str, 0, SIZE_MAX
					, debuginfo);
			}
			/** Append a C string to _str
			* @param str a appended C string
			* @return this
			*/
			::booldog::classes::string& operator +=(const char* str)
			{
				append< 16 >(0, str, debuginfo_macros);
				return *this;
			};
			/** Convert number to C string and append it to _str
			* @param pres store the function result or detailed error
			* @param number a appended number
			* @param debuginfo a debug information
			* @return The function result
			*/
			template< size_t step, class T >
			bool append(::booldog::result* pres, T number, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				::booldog::result locres;
				BOOINIT_RESULT(::booldog::result);
				size_t dstlen = 0;
				if(_str && ::booldog::utils::string::mbs::tostring(res, &_str[_length], dstlen, _size - _length - 1, number, debuginfo))
				{
					_length += dstlen;
					_str[_length] = 0;
				}
				else
				{
					_size += dstlen + step;
					_str = _allocator->realloc_array< char >(_str, _size, debuginfo);
					if(_str)
					{
						if(::booldog::utils::string::mbs::tostring(res, &_str[_length], dstlen, _size - _length - 1, number, debuginfo))
						{
							_length += dstlen;
							_str[_length] = 0;
						}
						else
							return false;
					}
					else
					{
						res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
						return false;
					}
				}
				return true;
			}
			/** Convert number to C string and append it to _str
			* @param number a appended number
			* @return this
			*/
			::booldog::classes::string& operator +=(int number)
			{
				append< 16 >(0, number, debuginfo_macros);
				return *this;
			}
			/** Convert number to C string and append it to _str
			* @param number a appended number
			* @return this
			*/
			::booldog::classes::string& operator +=(unsigned int number)
			{
				append< 16 >(0, number, debuginfo_macros);
				return *this;
			}
			/** Convert number to C string and append it to _str
			* @param number a appended number
			* @return this
			*/
			::booldog::classes::string& operator +=(::booldog::int64 number)
			{
				append< 16 >(0, number, debuginfo_macros);
				return *this;
			}
			/** Convert number to C string and append it to _str
			* @param number a appended number
			* @return this
			*/
			::booldog::classes::string& operator +=(::booldog::uint64 number)
			{
				append< 16 >(0, number, debuginfo_macros);
				return *this;
			}
			/** Convert number to C string and append it to _str
			* @param number a appended number
			* @return this
			*/
			::booldog::classes::string& operator +=(::booldog::int16 number)
			{
				append< 16 >(0, number, debuginfo_macros);
				return *this;
			}
			/** Convert number to C string and append it to _str
			* @param number a appended number
			* @return this
			*/
			::booldog::classes::string& operator +=(::booldog::uint16 number)
			{
				append< 16 >(0, number, debuginfo_macros);
				return *this;
			}
			/** Clear C string
			*
			*/
			booinline void clear()
			{
				_length = 0;
			}
			/** Return a C string value
			* @return C string value
			*/
			booinline const char* cstr()
			{
				if(_length)
					return _str;
				else
					return "";
			}
			/** Return a C string length(without including the terminating null character itself)
			* @return C string length(without including the terminating null character itself)
			*/
			booinline size_t length()
			{
				return _length;
			}
#if defined(BOO_UTF16_H) && defined(BOO_UTF32_H)
			/** Convert a C multibyte string to C utf8 string
			* @param pres store the function result or detailed error
			* @param allocator a temporary allocator
			* @param debuginfo a debug information
			* @return The function result
			*/
			template< size_t step >
			bool toutf8(::booldog::result* pres, ::booldog::allocator* allocator, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				::booldog::result locres;
				BOOINIT_RESULT(::booldog::result);

				::booldog::result_wchar reswchar(allocator);
				if(::booldog::utils::string::mbs::towcs(&reswchar, allocator, _str, 0, SIZE_MAX, debuginfo))
				{
					size_t srcbyteindex = 0;
					if(::booldog::compile::If< sizeof( wchar_t ) == 2 >::test())
						return ::booldog::utf16::toutf8< step >(res, _allocator, _str, _length, _size, (char*)reswchar.wchar, srcbyteindex
							, sizeof(wchar_t) * reswchar.wlen, debuginfo);
					else if(::booldog::compile::If< sizeof( wchar_t ) == 4 >::test())
						return ::booldog::utf32::toutf8< step >(res, _allocator, _str, _length, _size, (char*)reswchar.wchar, srcbyteindex
							, sizeof(wchar_t) * reswchar.wlen, debuginfo);
					else
					{
						res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
						return false;
					}
				}
				else
				{
					res->copy(reswchar);
					return false;
				}
				return true;
			}
#endif
		};
	}
}
#endif
