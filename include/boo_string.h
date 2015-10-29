#ifndef BOO_STRING_H
#define BOO_STRING_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_object.h>
#include <boo_utf8.h>
#include <boo_utf32.h>
#include <boo_utf16.h>
#include <boo_cp1251.h>
namespace booldog
{
#ifndef BOOLDOG_STRING_STEP
#define BOOLDOG_STRING_STEP 32
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
		string( booldog::allocator* allocator = ::booldog::_allocator )
			: ::booldog::object( allocator )
		{
			_utf8str = 0;
			_size = 0;
			_utf8length = 0;
			_bytes = 0;
		};
		string( const char* string , size_t byteindex = 0 , size_t bytes = SIZE_MAX , ::booldog::enums::string::code_page code_page = ::booldog::global::string::default_code_page , booldog::allocator* allocator = ::booldog::_allocator )
			: ::booldog::object( allocator )
		{
			if( string )
			{
				size_t size = bytes , dstbyteindex = 0;
				if( code_page == ::booldog::enums::string::UTF8 )
				{
					const ::booldog::byte* ptr = (::booldog::byte*)&string[ byteindex ];
					_utf8length = 0;
					_bytes = bytes;
					while( *ptr != 0 && _bytes != 0 )
					{
						if( ::booldog::utf8::validate_character_with_length( ptr , &_bytes ) == false )
						{
							code_page = ::booldog::global::string::default_code_page;
							_utf8str = 0;
							_size = 0;
							_utf8length = 0;
							_bytes = 0;
							goto goto_convert_to_utf8;
						}
						_utf8length++;
					};
					_bytes = bytes - _bytes;
					if( _bytes )
					{
						_size = _bytes + BOOLDOG_STRING_STEP + 1;
						_utf8str = (char*)allocator->alloc( _size , __FILE__ , __LINE__ );
						::memcpy( _utf8str , &string[ byteindex ] , _bytes );
						if( _utf8str[ _bytes - 1 ] != 0 )
							_utf8str[ _bytes++ ] = 0;
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
						else if( code_page == ::booldog::enums::string::CP1251 )
							size *= 4;
					}
					_utf8str = 0;
					_size = 0;
					_utf8length = 0;
goto_convert_to_utf8:
					if( _size < size )
					{
						if( size == SIZE_MAX )
							_size += BOOLDOG_STRING_STEP + 1;
						else
							_size += size + BOOLDOG_STRING_STEP + 1;
						_utf8str = (char*)allocator->realloc( _utf8str , _size , __FILE__ , __LINE__ );
					}
					if( _utf8str )
					{
						::booldog::enums::string::conversion_result res = ::booldog::enums::string::conversion_result_OK;
						if( code_page == ::booldog::enums::string::UTF32 )
							res = ::booldog::utf32::to_utf8( string , byteindex , bytes , _utf8str , dstbyteindex , _size , _bytes , _utf8length );
						else if( code_page == ::booldog::enums::string::UTF16 )
							res = ::booldog::utf16::to_utf8( string , byteindex , bytes , _utf8str , dstbyteindex , _size , _bytes , _utf8length );
						else if( code_page == ::booldog::enums::string::CP1251 )
							res = ::booldog::cp1251::to_utf8( string , byteindex , bytes , _utf8str , dstbyteindex , _size , _bytes , _utf8length );
						else if( code_page == ::booldog::enums::string::Unknown )
						{
							//mbstowcs( 
						}
						if( res == ::booldog::enums::string::conversion_result_targetExhausted )
						{
							size = _bytes;
							goto goto_convert_to_utf8;
						}
						else if( res != ::booldog::enums::string::conversion_result_OK )
						{
							_utf8length = 0;
							_bytes = 0;
						}
						else
						{
							if( _utf8str[ _bytes - 1 ] != 0 )
							{
								if( _bytes + 1 > _size )
								{
									_size += BOOLDOG_STRING_STEP;
									_utf8str = (char*)allocator->realloc( _utf8str , _size , __FILE__ , __LINE__ );
								}
								if( _utf8str )
									_utf8str[ _bytes++ ] = 0;
							}
						}
						return;
					}
				}
			}
			_utf8str = 0;
			_size = 0;
			_utf8length = 0;
			_bytes = 0;
		};
		size_t length( void )
		{
			return _utf8length;
		};
		size_t bytes( void )
		{
			return _bytes;
		};
		const char* str( void )
		{
			if( _utf8length )
				return _utf8str;
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
		::booldog::string& operator =( const ::booldog::object& obj )
		{
			::booldog::object* object = this;
			object->operator =( obj );
			return *this;
		};
	};
};
#endif
