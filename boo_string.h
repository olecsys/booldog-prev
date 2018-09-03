#ifndef BOO_STRING_H
#define BOO_STRING_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_object.h"
#include "boo_utf8.h"
#include "boo_utf32.h"
#include "boo_utf16.h"
#include "boo_cp1251.h"
#include "boo_mem.h"
#include "boo_if.h"
namespace booldog
{
	namespace global
	{
		namespace string
		{
			static ::booldog::enums::string::code_page default_code_page = BOOLDOG_STRING_CODE_PAGE;
		}
	}
#ifdef BOOLDOG_STRING_TEST
	size_t string_step = 1;
#define BOOLDOG_STRING_STEP ::booldog::string_step
#else
#ifndef BOOLDOG_STRING_STEP
#define BOOLDOG_STRING_STEP 32
#endif
#endif

	class string : public ::booldog::object
	{
	public:
		typedef ::booldog::object item_type;
		static const ::booldog::uint64 type_hash = ::booldog::hash::compile::times33< 'b','o','o','l','d','o','g','.','s','t','r','i','n','g' >::value;
		static const bool use_item_type = false;		
	private:
		char* _utf8str;
		size_t _size;
		size_t _utf8length;
		size_t _bytes;
	public:
		::booldog::string& operator =( const ::booldog::object& obj )
		{
			::booldog::object* object = this;
			object->operator =( obj );
			return *this;
		};
		string( const ::booldog::string& obj )
			: ::booldog::object( obj._allocator ) , _utf8str( 0 ) , _size( 0 ) , _utf8length( 0 ) , _bytes( 0 )
		{
			::booldog::object* object = this;
			object->operator =( obj );
		};
		string( booldog::allocator* allocator )
			: ::booldog::object( allocator ) , _utf8str( 0 ) , _size( 0 ) , _utf8length( 0 ) , _bytes( 0 )
		{
		};
		string( booldog::allocator* allocator , const char* string , size_t byteindex = 0 , size_t bytes = SIZE_MAX , ::booldog::enums::string::code_page code_page = ::booldog::global::string::default_code_page )
			: ::booldog::object( allocator ) , _utf8str( 0 ) , _size( 0 ) , _utf8length( 0 ) , _bytes( 0 )
		{
			insert( SIZE_MAX , string , byteindex , bytes , code_page );
		};
		string( booldog::allocator* allocator , const wchar_t* string , size_t wordindex = 0 , size_t words = SIZE_MAX )
			: ::booldog::object( allocator ) , _utf8str( 0 ) , _size( 0 ) , _utf8length( 0 ) , _bytes( 0 )
		{
			if( ::booldog::compile::If< sizeof( wchar_t ) == 2 >::test() )
				append( (char*)string , 2 * wordindex , words == SIZE_MAX ? SIZE_MAX : 2 * words , ::booldog::enums::string::UTF16 );
			else if( ::booldog::compile::If< sizeof( wchar_t ) == 4 >::test() )
				append( (char*)string , 4 * wordindex ,  words == SIZE_MAX ? SIZE_MAX : 4 * words , ::booldog::enums::string::UTF32 );
		};
		virtual ~string( void )
		{
			if( _utf8str )
				_allocator->free( _utf8str );
		};
		size_t length( void )
		{
			return operator()()._utf8length;
		};
		size_t bytes( void )
		{
			return operator()()._bytes + 1;
		};
		const char* str( void )
		{
			::booldog::string* _this = &operator()();
			if( _this->_utf8length )
				return _this->_utf8str;
			else
				return "";
		};
		string& operator ()( void )
		{
			if( _obj )
				return *static_cast< string* >( _obj );
			else
				return *this;
		};
		virtual ::booldog::uint64 get_type_hash( int , bool ) const
		{
			return type_hash;
		};
		virtual size_t type_size( void ) const
		{
			return sizeof( *this );
		};
		void clear( void )
		{
			::booldog::string* _this = &operator()();
			_this->_bytes = 0;
			_this->_utf8length = 0;
		};
		void append( const char* string , size_t byteindex = 0 , size_t bytes = SIZE_MAX , ::booldog::enums::string::code_page code_page = ::booldog::global::string::default_code_page )
		{
			insert( SIZE_MAX , string , byteindex , bytes , code_page );
		};
		void append( const wchar_t* string , size_t wordindex = 0 , size_t words = SIZE_MAX )
		{
			insert( SIZE_MAX , string , wordindex , words );
		};
		void insert( size_t charindex , const wchar_t* string , size_t wordindex = 0 , size_t words = SIZE_MAX )
		{
			if( ::booldog::compile::If< sizeof( wchar_t ) == 2 >::test() )
				insert( charindex , (char*)string , 2 * wordindex , words == SIZE_MAX ? SIZE_MAX : 2 * words , ::booldog::enums::string::UTF16 );
			else if( ::booldog::compile::If< sizeof( wchar_t ) == 4 >::test() )
				insert( charindex , (char*)string , 4 * wordindex ,  words == SIZE_MAX ? SIZE_MAX : 4 * words , ::booldog::enums::string::UTF32 );
		};
		::booldog::string substring( booldog::allocator* allocator , size_t charindex , size_t charcount = SIZE_MAX )
		{
			::booldog::string res( allocator );
			::booldog::string* _this = &operator()();
			if( charindex < _this->_utf8length )
			{
				size_t byteindex = 0;
				const ::booldog::byte* ptr = (::booldog::byte*)_this->_utf8str;
				for( ; ; )
				{
					if( charindex-- == 0 )
					{
						byteindex = (char*)ptr - _this->_utf8str;
						break;
					}
					::booldog::utf8::validate_character( ptr );
				}
				size_t bytes = charcount;
				if( bytes != SIZE_MAX )
				{
					for( ; ; )
					{
						if( *ptr == 0 || charcount-- == 0 )
						{
							bytes = (char*)ptr - _this->_utf8str;
							break;
						}
						::booldog::utf8::validate_character( ptr );
					}
				}
				res.insert( 0 , _this->_utf8str , byteindex , bytes , ::booldog::enums::string::UTF8 , false );
			}
			return res;
		};
		void replace( size_t startcharindex , const char* oldstring , const char* newstring , size_t max_replace_count = SIZE_MAX 
			, size_t oldbyteindex = 0 , size_t oldbytes = SIZE_MAX , size_t oldlength = SIZE_MAX , ::booldog::enums::string::code_page oldcode_page = ::booldog::global::string::default_code_page 
			, size_t newbyteindex = 0 , size_t newbytes = SIZE_MAX , size_t newlength = SIZE_MAX , ::booldog::enums::string::code_page newcode_page = ::booldog::global::string::default_code_page 
			, bool oldcheck_utf8 = true , bool newcheck_utf8 = true , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			if( oldstring )
			{
				::booldog::string* _this = &operator()();
				if( _this->_utf8length )
				{
					const ::booldog::byte* ptr = 0;
					size_t size = 0;

					::booldog::string oldstr( _this->_allocator );
					const char* utf8oldstring = &oldstring[ oldbyteindex ];
					if( oldcode_page == ::booldog::enums::string::UTF8 )
					{
						if( oldcheck_utf8 || oldlength == SIZE_MAX )
						{
							oldlength = 0;
							ptr = (::booldog::byte*)utf8oldstring;
							size = oldbytes;
							while( *ptr != 0 && size != 0 )
							{
								if( ::booldog::utf8::validate_character_with_length( ptr , &size ) == false )
								{
									oldcode_page = ::booldog::global::string::default_code_page;
									goto goto_old_not_utf8;
								}
								oldlength++;
							};
							oldbytes = oldbytes - size;
						}
					};
goto_old_not_utf8:
					if( oldcode_page != ::booldog::enums::string::UTF8 )
					{
						oldstr.append( oldstring , oldbyteindex , oldbytes , oldcode_page );
						utf8oldstring = oldstr.str();
						oldbytes = oldstr.bytes() - 1;
						oldlength = oldstr.length();
					}

					::booldog::string newstr( _this->_allocator );
					const char* utf8newstring = newstring ? &newstring[ newbyteindex ] : 0;
					if( newstring )
					{
						if( newcode_page == ::booldog::enums::string::UTF8 )
						{
							if( newcheck_utf8 || newlength == SIZE_MAX )
							{
								newlength = 0;
								ptr = (::booldog::byte*)utf8newstring;
								size = newbytes;
								while( *ptr != 0 && size != 0 )
								{
									if( ::booldog::utf8::validate_character_with_length( ptr , &size ) == false )
									{
										newcode_page = ::booldog::global::string::default_code_page;
										goto goto_new_not_utf8;
									}
									newlength++;
								};
								newbytes = newbytes - size;
							}
						};
goto_new_not_utf8:
						if( newcode_page != ::booldog::enums::string::UTF8 )
						{
							newstr.append( newstring , newbyteindex , newbytes , newcode_page );
							utf8newstring = newstr.str();
							newbytes = newstr.bytes() - 1;
							newlength = newstr.length();
						}
					}
					else
					{
						newbytes = 0;
						newlength = 0;
					}
					if( oldbytes )
					{
						size = 0;
						ptr = (::booldog::byte*)_this->_utf8str;
						for( ; ; )
						{
							if( size == startcharindex )
								break;
							::booldog::utf8::validate_character( ptr );
							size++;
						}
						size = 0;
						while( *ptr != 0 )
						{
							if( ( (char*)ptr - _this->_utf8str ) + oldbytes > _this->_bytes )
								break;
							if( ::memcmp( ptr , utf8oldstring , oldbytes ) == 0 )
							{
								if( oldbytes != newbytes )
								{
									if( newbytes )
									{
										if( ::booldog::mem::insert< char >( (char*)ptr - _this->_utf8str , _this->_utf8str , _this->_bytes , _this->_size , oldbytes , utf8newstring , newbytes ) == false )
										{
											size_t index = (char*)ptr - _this->_utf8str;
											_this->_size += newbytes + BOOLDOG_STRING_STEP;
											_this->_utf8str = _this->_allocator->realloc_array< char >( _this->_utf8str , _this->_size , debuginfo );
											if( _this->_utf8str == 0 )
												break;
											else
											{
												ptr = (::booldog::byte*)&_this->_utf8str[ index ];
												::booldog::mem::insert< char >( index , _this->_utf8str , _this->_bytes , _this->_size , oldbytes , utf8newstring , newbytes );
											}
										}
										_this->_bytes += newbytes - oldbytes;
									}
									else
									{
										::booldog::mem::remove< char >( (char*)ptr - _this->_utf8str , _this->_utf8str , _this->_bytes , oldbytes );
										_this->_bytes -= oldbytes;
									}
								}
								else
									::memcpy( (void*)ptr , utf8newstring , newbytes );
								ptr += newbytes;
								_this->_utf8length += newlength - oldlength;
								size++;
								if( size == max_replace_count )
									break;
							}
							else
								::booldog::utf8::validate_character( ptr );
						}
						if( _this->_bytes >= _this->_size )
						{
							_this->_size += 1 + BOOLDOG_STRING_STEP;
							_this->_utf8str = _this->_allocator->realloc_array< char >( _this->_utf8str , _this->_size , debuginfo );
						}
						if( _this->_utf8str )
							_this->_utf8str[ _this->_bytes ] = 0;
					}
				}
			}
		};
		void insert( size_t charindex , const char* string , size_t byteindex = 0 , size_t bytes = SIZE_MAX
			, ::booldog::enums::string::code_page code_page = ::booldog::global::string::default_code_page 
			, bool check_utf8 = true , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			::booldog::string* _this = &operator()();
			size_t oldutf8length = _this->_utf8length;
			size_t oldbytes = _this->_bytes;
			if( string )
			{
				size_t size = bytes , dstbyteindex = _this->_bytes , expand_index = 0 , expand_size = 0;
				if( charindex < _this->_utf8length )
				{
					expand_index = SIZE_MAX;
					dstbyteindex = 0;
					if( charindex )
					{
						const ::booldog::byte* ptr = (::booldog::byte*)_this->_utf8str;
						for( ; ; )
						{
							if( dstbyteindex == charindex )
								break;
							::booldog::utf8::validate_character( ptr );
							dstbyteindex++;
						}
						dstbyteindex = (char*)ptr - _this->_utf8str;
					}
				}
				if( code_page == ::booldog::enums::string::UTF8 )
				{
					const ::booldog::byte* ptr = (::booldog::byte*)&string[ byteindex ];
					size = bytes;
					if( check_utf8 || bytes == SIZE_MAX )
					{
						while( *ptr != 0 && size != 0 )
						{
							if( ::booldog::utf8::validate_character_with_length( ptr , &size ) == false )
							{
								code_page = ::booldog::global::string::default_code_page;
								_this->_utf8length = oldutf8length;
								goto goto_convert_to_utf8;
							}
							_this->_utf8length++;
						};
						size = bytes - size;
					};
					if( size )
					{
						_this->_bytes += size;
						if( _this->_size < _this->_bytes + 1 )
						{
							_this->_size += _this->_bytes + 1 + BOOLDOG_STRING_STEP;
							_this->_utf8str = _this->_allocator->realloc_array< char >( _this->_utf8str , _this->_size , debuginfo );
						}
						if( expand_index )
							::booldog::mem::expand< char >( dstbyteindex , _this->_utf8str , _this->_bytes - size , _this->_size , size );
						::memcpy( &_this->_utf8str[ dstbyteindex ] , &string[ byteindex ] , size );
						if( _this->_utf8str[ _this->_bytes ] != 0 )
							_this->_utf8str[ _this->_bytes ] = 0;
						return;
					}
				}
				else 
				{
					if( bytes != SIZE_MAX )
					{
						bytes += byteindex;
						if( code_page == ::booldog::enums::string::UTF16 )
							size *= 2;
						else if( code_page == ::booldog::enums::string::UTF32 )
							size *= 4;
					}
goto_convert_to_utf8:
					if( _this->_size < size )
					{
						if( size != SIZE_MAX )
							_this->_size += size + BOOLDOG_STRING_STEP + 1;
						else if( _this->_utf8str == 0 )
							_this->_size += BOOLDOG_STRING_STEP;
						_this->_utf8str = _this->_allocator->realloc_array< char >( _this->_utf8str , _this->_size , debuginfo );
					}
					if( _this->_utf8str )
					{
						size_t utf8bytes = 0;
						if( expand_index )
						{
							if( expand_size )
							{
								::booldog::mem::expand< char >( expand_index , _this->_utf8str , expand_size + expand_index , _this->_size , _this->_size - expand_size - expand_index );
								expand_index = _this->_size - expand_size;
							}
							else
							{
								expand_index = 0;
								if( _this->_bytes > dstbyteindex )
								{
									if( _this->_size + dstbyteindex > _this->_bytes )
									{
										expand_index = _this->_size + dstbyteindex - _this->_bytes;								
										expand_size = _this->_bytes - dstbyteindex;
										::booldog::mem::expand< char >( dstbyteindex , _this->_utf8str , _this->_bytes , _this->_size , expand_index - dstbyteindex );
									}
								}
							}
						}
						::booldog::enums::string::conversion_result res = ::booldog::enums::string::conversion_result_OK;
						if( code_page == ::booldog::enums::string::UTF32 )
							res = ::booldog::utf32::to_utf8( string , byteindex , bytes , _this->_utf8str , dstbyteindex , expand_index == 0 ? _this->_size : expand_index , utf8bytes , _this->_utf8length );
						else if( code_page == ::booldog::enums::string::UTF16 )
							res = ::booldog::utf16::to_utf8( string , byteindex , bytes , _this->_utf8str , dstbyteindex , expand_index == 0 ? _this->_size : expand_index , utf8bytes , _this->_utf8length );
						else if( code_page == ::booldog::enums::string::CP1251 )
							res = ::booldog::cp1251::to_utf8( string , byteindex , bytes , _this->_utf8str , dstbyteindex , expand_index == 0 ? _this->_size : expand_index , utf8bytes , _this->_utf8length );
						else if( code_page == ::booldog::enums::string::Unknown )
						{
							//mbstowcs( 
						}
						if( res == ::booldog::enums::string::conversion_result_targetExhausted )
						{
							size = utf8bytes + expand_size;
							goto goto_convert_to_utf8;
						}
						else if( res != ::booldog::enums::string::conversion_result_OK )
						{
							_this->_utf8length = oldutf8length;
							_this->_bytes = oldbytes;
							_this->_utf8str[ _this->_bytes - 1 ] = 0;
						}
						else
						{
							_this->_bytes = utf8bytes + expand_size;
							if( expand_index )
								::booldog::mem::remove< char >( dstbyteindex , _this->_utf8str , _this->_size , expand_index - dstbyteindex );
							if( _this->_bytes + 1 > _this->_size )
							{
								_this->_size += BOOLDOG_STRING_STEP;
								_this->_utf8str = _this->_allocator->realloc_array< char >( _this->_utf8str , _size , debuginfo );
							}
							if( _this->_utf8str )
								_this->_utf8str[ _this->_bytes ] = 0;
						}
						return;
					}
				}
			}
			_this->_utf8length = oldutf8length;
			_this->_bytes = oldbytes;
		};
	};
};
#endif
