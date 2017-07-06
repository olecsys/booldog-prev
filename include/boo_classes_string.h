/** class string
* Simplify work with C strings
*/

#ifndef BOO_CLASSES_STRING_H
#define BOO_CLASSES_STRING_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_string_utils.h"
#if (defined(BOO_UTF16_H) && defined(BOO_UTF32_H)) || defined(BOO_UTF8_H)
#include "boo_if.h"
#endif
namespace booldog
{
	namespace classes
	{
		class string
		{
		public:
			struct string_return
			{
				::booldog::allocator* _allocator;///< allocator is used to allocate/deallocate _str member
				char* _str;                      ///< store C string data
				size_t _size;                    ///< the size of the allocated memory
				size_t _length;                  ///< the length of the C string _str member(without including the terminating null character itself)
				explicit string_return(::booldog::classes::string& string)
					: _allocator(string._allocator), _str(string._str), _size(string._size), _length(string._length)
				{
					string._str = 0;
				}
				string_return(const ::booldog::classes::string::string_return& string)
					: _allocator(string._allocator), _str(string._str), _size(string._size), _length(string._length)
				{
					const_cast< ::booldog::classes::string::string_return* >(&string)->_str = 0;
				}
				~string_return()
				{
					if(_str)
					{
						int crush = printf("%s, string_return must be copied to string after return, EXCEPT!!!\n", __FILE__);
						printf("%d\n", crush / (crush / 70567));
					}
				}
				void copyto(::booldog::classes::string& string) const
				{
					if(_str)
					{
						if(string._allocator == _allocator)
						{
							if(string._str)
								string._allocator->free(string._str);
							string._str = _str;
							string._length = _length;
							string._size = _size;
						}
						else
						{
							if(_length >= string._size)
							{
								string._size = _length + 1;
								string._str = string._allocator->realloc_array< char >(string._str, string._size, debuginfo_macros);
							}
							::memcpy(string._str, _str, _length + 1);
							string._length = _length;
							_allocator->free(_str);
						}
						const_cast< ::booldog::classes::string::string_return* >(this)->_str = 0;
					}
					else
						string._length = 0;
				}
			};
		public:
			::booldog::allocator* _allocator;///< allocator is used to allocate/deallocate _str member
			char* _str;                      ///< store C string data
			size_t _size;                    ///< the size of the allocated memory
			size_t _length;                  ///< the length of the C string _str member(without including the terminating null character itself)
		private:
			void ctor(const char* string0, const char* string1, size_t string0_length = SIZE_MAX
				, size_t string1_length = SIZE_MAX)
			{
				const char* ptr0 = 0;
				if(string0_length == SIZE_MAX)
				{
					if(string0)
					{
						ptr0 = string0;
						while(*ptr0++ != 0)
							;
						string0_length = ptr0 - string0 - 1;
					}
					else
						string0_length = 0;
				}
				if(string1_length == SIZE_MAX)
				{
					if(string1)
					{
						ptr0 = string1;
						while(*ptr0++ != 0)
							;
						string1_length = ptr0 - string1 - 1;
					}
					else
						string1_length = 0;
				}
				_size = string0_length + string1_length + 1;
				if(_size == 1)
				{
					_size = 0;
					_length = 0;
					_str = 0;
				}
				else
				{
					_str = _allocator->realloc_array< char >(0, _size, debuginfo_macros);
					char* ptr = _str;
					if(string0_length)
					{
						::memcpy(ptr, string0, string0_length);
						ptr += string0_length;
					}
					if(string1_length)
					{
						::memcpy(ptr, string1, string1_length);
						ptr += string1_length;
					}
					*ptr = 0;
					_length = _size - 1;
				}
			}
		public:
			/** Default constructor
			* sets a allocator for the field _allocator
			* sets a null for the fields: _str, _size, _length			
			*/
			explicit string(::booldog::allocator* allocator)
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
			/** Copy constructor
			* @param string0 copy string
			* @param copy if true then _str C string will be copied, if false then string0.mbchar will be detached from string0
			*/
			string(const ::booldog::classes::string::string_return& string0)
				: _allocator(string0._allocator), _str(string0._str), _size(string0._size), _length(string0._length)
			{
				const_cast< ::booldog::classes::string::string_return* >(&string0)->_str = 0;
			}
			/** Copy constructor
			* @param string0 copy string(can be null)
			* @param copy if true then _str C string will be copied, if false then string0.mbchar will be detached from string0
			*/
			explicit string(const ::booldog::results::mbchar& string0, bool copy = true)
				: _allocator(string0)
			{
				if(copy)
					ctor(string0.mbchar, 0, string0.mblen, 0);
				else
				{
					_size = string0.mbsize;
					_length = string0.mblen;
					_str = string0.detach();					
				}
			}
			/** Make C string pointer, size, length null(without free) and return C string pointer
			* @return The C string pointer
			*/
			char* detach()
			{
				char* res = _str;
				_size = _length = 0;
				_str = 0;
				return res;
			}
			/** Copy constructor
			* @param string0 copy string
			* @param copy if true then _str C string will be copied, if false then string0._str will be detached from string0
			*/
			explicit string(const ::booldog::classes::string& string0, bool copy)
				: _allocator(string0)
			{
				if(copy)
					ctor(string0._str, 0, string0._length, 0);
				else
				{
					_size = string0._size;
					_length = string0._length;
					_str = string0._str;
					::booldog::classes::string* str = const_cast< ::booldog::classes::string* >(&string0);
					str->_str = 0;
					str->_size = 0;
					str->_length = 0;
				}
			}
			/** Copy constructor
			* @param string0 copy string
			*/
			string(const ::booldog::classes::string& string0)
				: _allocator(string0)
			{
				ctor(string0._str, 0, string0._length, 0);
			}
			/** Concatenation constructor
			* @param string0 begin concatenation string(can be null)
			* @param string1 end concatenation string(can be null)
			* @param string0_length a string0 length(if equal to SIZE_MAX then it's calculated inside function)
			* @param string1_length a string1 length(if equal to SIZE_MAX then it's calculated inside function)
			*/
			explicit string(::booldog::allocator* allocator, const char* string0, const char* string1
				, size_t string0_length = SIZE_MAX, size_t string1_length = SIZE_MAX)
				: _allocator(allocator)
			{
				ctor(string0, string1, string0_length, string1_length);
			}
			/** Concatenation constructor
			* @param string0 begin concatenation string
			* @param string1 end concatenation string(can be null)
			* @param string1_length a string1 length(if equal to SIZE_MAX then it's calculated inside function)
			*/
			explicit string(const ::booldog::classes::string& string0, const char* string1, size_t string1_length = SIZE_MAX)
				: _allocator(string0._allocator)
			{
				ctor(string0._str, string1, string0._length, string1_length);
			}
			/** Concatenation constructor
			* @param string0 begin concatenation string
			* @param string1 end concatenation string(can be null)
			* @param string1_length a string1 length(if equal to SIZE_MAX then it's calculated inside function)
			*/
			explicit string(const ::booldog::results::mbchar& string0, const char* string1, size_t string1_length = SIZE_MAX)
				: _allocator(string0.mballocator)
			{
				ctor(string0.mbchar, string1, string0.mblen, string1_length);
			}
			/** Concatenation constructor
			* @param string0 begin concatenation string(can be null)
			* @param string1 end concatenation string
			* @param string0_length a string0 length(if equal to SIZE_MAX then it's calculated inside function)
			*/
			explicit string(const char* string0, const ::booldog::classes::string& string1, size_t string0_length = SIZE_MAX)
				: _allocator(string1._allocator)
			{
				ctor(string0, string1._str, string0_length, string1._length);
			}
			/** Concatenation constructor
			* @param string0 begin concatenation string(can be null)
			* @param string1 end concatenation string
			* @param string0_length a string0 length(if equal to SIZE_MAX then it's calculated inside function)
			*/
			explicit string(const char* string0, const ::booldog::results::mbchar& string1, size_t string0_length = SIZE_MAX)
				: _allocator(string1)
			{
				ctor(string0, string1.mbchar, string0_length, string1.mblen);
			}
			/** Concatenation constructor
			* @param string0 begin concatenation string
			* @param string1 end concatenation string
			*/
			explicit string(const ::booldog::classes::string& string0, const ::booldog::classes::string& string1)
				: _allocator(string1._allocator)
			{
				ctor(string0._str, string1._str, string0._length, string1._length);
			}
			/** Concatenation constructor
			* @param string0 begin concatenation string
			* @param string1 end concatenation string
			*/
			explicit string(const ::booldog::results::mbchar& string0, const ::booldog::results::mbchar& string1)
				: _allocator(string1)
			{
				ctor(string0.mbchar, string1.mbchar, string0.mblen, string1.mblen);
			}
			::booldog::classes::string& operator =(const ::booldog::classes::string::string_return& string)
			{
				string.copyto(*this);
				return *this;
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
			/** Assign a new C string 
			* @param str a string object with new C string
			* @return this
			*/
			booinline ::booldog::classes::string& operator =(const ::booldog::classes::string& str)
			{
				::booldog::utils::string::mbs::assign< 16 >(0, _allocator, false, 0, _str, _length, _size, str._str, 0, str._length
					, debuginfo_macros);
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
				return ::booldog::utils::string::mbs::append< step, T >(pres, _allocator, _str, _length, _size, number, debuginfo);
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
			booinline const char* cstr() const
			{
				if(_length)
					return _str;
				else
					return "";
			}
			booinline operator const char*() const
			{
				return cstr();
			}
			/** Return a allocator that is allocating C string _str
			* @return a allocator that is allocating C string _str
			*/
			booinline operator ::booldog::allocator*() const
			{
				return _allocator;
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
#if defined(BOO_UTF8_H)
			/** Convert a C utf8 string to C multibyte string
			* @param pres store the function result or detailed error
			* @param allocator a temporary allocator
			* @param debuginfo a debug information
			* @return The function result
			*/
			template< size_t step >
			bool tombs(::booldog::result* pres, ::booldog::allocator* allocator, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
				::booldog::result locres;
				BOOINIT_RESULT(::booldog::result);
				::booldog::results::mbchar mbchar(allocator);
				size_t srcbyteindex = 0;
				if(::booldog::compile::If< sizeof(wchar_t) == 2 >::test())
				{
					if(::booldog::utf8::toutf16< step >(mbchar, _str, srcbyteindex, _length, debuginfo) == false)
					{
						res->copy(mbchar);
						return false;
					}
				}
				else if(::booldog::compile::If< sizeof(wchar_t) == 4 >::test())
				{
					if(::booldog::utf8::toutf32< step >(mbchar, _str, srcbyteindex, _length, debuginfo) == false)
					{
						res->copy(mbchar);
						return false;
					}
				}
				else
				{
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
					return false;
				}
				return ::booldog::utils::string::wcs::tombs(res, _allocator, _str, _length, _size, (wchar_t*)mbchar.mbchar, 0
					, sizeof(wchar_t) * mbchar.mblen, debuginfo);
			}
#endif
			booinline friend const ::booldog::classes::string::string_return operator +(const ::booldog::results::mbchar& string0
				, const char* string1);
			booinline friend const ::booldog::classes::string::string_return operator +(const ::booldog::classes::string& string0
				, const char* string1)
			{
				::booldog::classes::string result(string0, string1);
				return ::booldog::classes::string::string_return(result);
			}
			booinline friend ::booldog::classes::string::string_return operator +(const ::booldog::classes::string& string0
				, const char string1)
			{
				::booldog::classes::string result(string0, &string1, 1);
				::booldog::classes::string::string_return res(result);
				return res;
			}
			booinline friend const ::booldog::classes::string::string_return operator +(const char* string0
				, const ::booldog::classes::string& string1)
			{
				::booldog::classes::string result(string0, string1);
				::booldog::classes::string::string_return res(result);
				return res;
			}
			booinline friend const ::booldog::classes::string::string_return operator +(const ::booldog::classes::string& string0
				, const ::booldog::classes::string& string1)
			{
				::booldog::classes::string result(string0, string1);
				::booldog::classes::string::string_return res(result);
				return res;
			}
			booinline friend const ::booldog::classes::string::string_return operator +(const ::booldog::classes::string::string_return& string0
				, const char* string1)
			{
				::booldog::classes::string::string_return* str = const_cast< ::booldog::classes::string::string_return* >(&string0);
				::booldog::utils::string::mbs::assign< 16 >(0, str->_allocator, false, str->_length, str->_str, str->_length
					, str->_size, string1, 0, SIZE_MAX, debuginfo_macros);
				return *str;
			}
			booinline friend const ::booldog::classes::string::string_return operator +(const ::booldog::classes::string::string_return& string0
				, ::booldog::int32 string1)
			{
				::booldog::classes::string::string_return* str = const_cast< ::booldog::classes::string::string_return* >(&string0);
				::booldog::utils::string::mbs::append< 16 >(0, str->_allocator, str->_str, str->_length, str->_size, string1, debuginfo_macros);
				return *str;
			}
			booinline friend const ::booldog::classes::string::string_return operator +(const ::booldog::classes::string::string_return& string0
				, ::booldog::uint32 string1)
			{
				::booldog::classes::string::string_return* str = const_cast< ::booldog::classes::string::string_return* >(&string0);
				::booldog::utils::string::mbs::append< 16 >(0, str->_allocator, str->_str, str->_length, str->_size, string1, debuginfo_macros);
				return *str;
			}
			booinline friend const ::booldog::classes::string::string_return operator +(const ::booldog::classes::string::string_return& string0
				, ::booldog::int64 string1)
			{
				::booldog::classes::string::string_return* str = const_cast< ::booldog::classes::string::string_return* >(&string0);
				::booldog::utils::string::mbs::append< 16 >(0, str->_allocator, str->_str, str->_length, str->_size, string1, debuginfo_macros);
				return *str;
			}
			booinline friend const ::booldog::classes::string::string_return operator +(const ::booldog::classes::string::string_return& string0
				, ::booldog::uint64 string1)
			{
				::booldog::classes::string::string_return* str = const_cast< ::booldog::classes::string::string_return* >(&string0);
				::booldog::utils::string::mbs::append< 16 >(0, str->_allocator, str->_str, str->_length, str->_size, string1, debuginfo_macros);
				return *str;
			}
			booinline friend const ::booldog::classes::string::string_return operator +(const ::booldog::classes::string::string_return& string0
				, const char string1)
			{
				::booldog::classes::string::string_return* str = const_cast< ::booldog::classes::string::string_return* >(&string0);
				::booldog::utils::string::mbs::assign< 16 >(0, str->_allocator, false, str->_length, str->_str, str->_length
					, str->_size, &string1, 0, 1, debuginfo_macros);
				return *str;
			}
		};
	}
	booinline const ::booldog::classes::string::string_return operator +(const ::booldog::results::mbchar& string0
		, const char* string1)
	{
		::booldog::classes::string result(string0, string1);
		::booldog::classes::string::string_return res(result);
		return res;
	}
	booinline const ::booldog::classes::string::string_return operator +(const ::booldog::results::mbchar& string0
		, const char string1)
	{
		::booldog::classes::string result(string0, &string1, 1);
		::booldog::classes::string::string_return res(result);
		return res;
	}
	booinline const ::booldog::classes::string::string_return operator +(const char string0
		, const ::booldog::results::mbchar& string1)
	{
		::booldog::classes::string result(&string0, string1, 1);
		::booldog::classes::string::string_return res(result);
		return res;
	}
	booinline const ::booldog::classes::string::string_return operator +(const char* string0
		, const ::booldog::results::mbchar& string1)
	{
		::booldog::classes::string result(string0, string1);
		::booldog::classes::string::string_return res(result);
		return res;
	}
	booinline const ::booldog::classes::string::string_return operator +(const ::booldog::results::mbchar& string0
		, const ::booldog::results::mbchar& string1)
	{
		::booldog::classes::string result(string0, string1);
		::booldog::classes::string::string_return res(result);
		return res;
	}
	booinline const ::booldog::classes::string::string_return operator +(const ::booldog::classes::string::string_return& string0
		, const ::booldog::results::mbchar& string1)
	{
		::booldog::classes::string::string_return* str = const_cast< ::booldog::classes::string::string_return* >(&string0);
		::booldog::utils::string::mbs::assign< 16 >(0, str->_allocator, false, str->_length, str->_str, str->_length
			, str->_size, string1.mbchar, 0, string1.mblen, debuginfo_macros);
		return *str;
	}
}
#endif
