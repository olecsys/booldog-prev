#ifndef BOO_ARRAY_H
#define BOO_ARRAY_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_object.h>
#include <boo_mem.h>
namespace booldog
{
#define BOOLDOG_ARRAY_STEP 32
	template< class T >
	class array : public object
	{
	public:
		typedef T item_type;
		static const ::booldog::uint64 type_hash = ::booldog::hash::compile::times33< 'b','o','o','l','d','o','g','.','a','r','r','a','y' >::value;
		static const bool use_item_type = true;
	private:
		::booldog::object** _array;
		size_t _size;
		size_t _count;
	public:
		array( booldog::allocator* allocator = ::booldog::_allocator )
			: ::booldog::object( allocator )
		{
			_ref = 1;
			_allocator = allocator;
			_obj = 0;
			_array = 0;
			_size = 0;
			_count = 0;
		};
		~array( void )
		{
			if( _array )
			{
				for( size_t index0 = 0 ; index0 < _count ; index0++ )
					_array[ index0 ]->release();
				_allocator->free( _array );
			}
		};
		array< T >& operator ()( void )
		{
			if( _obj )
				return *static_cast< array< T >* >( _obj );
			else
				return *this;
		};
		virtual ::booldog::uint64 get_type_hash( int level , bool ) const
		{
			switch( level )
			{
				case 0:
					return type_hash;
				case 1:
					return T::type_hash;
				case 2:
					return T::item_type::type_hash;
				case 3:
					return T::item_type::item_type::type_hash;
				case 4:
					return T::item_type::item_type::item_type::type_hash;
				case 5:
					return T::item_type::item_type::item_type::item_type::type_hash;
				case 6:
					return T::item_type::item_type::item_type::item_type::item_type::type_hash;
			};
			return type_hash;
		};
		virtual bool get_use_item_type( int level ) const
		{
			switch( level )
			{
				case 0:
					return use_item_type;
				case 1:
					return T::use_item_type;
				case 2:
					return T::item_type::use_item_type;
				case 3:
					return T::item_type::item_type::use_item_type;
				case 4:
					return T::item_type::item_type::item_type::use_item_type;
				case 5:
					return T::item_type::item_type::item_type::item_type::use_item_type;
				case 6:
					return T::item_type::item_type::item_type::item_type::item_type::use_item_type;
			};
			return use_item_type;
		};
		virtual size_t type_size( void ) const
		{
			return sizeof( *this );
		};
		size_t count( void )
		{
			return operator()()._count;
		};
		size_t size( void )
		{
			return operator()()._size;
		};
		void clear( void )
		{
			array< T >* _this = &operator()();
			if( _this->_array )
			{
				for( size_t index0 = 0 ; index0 < _this->_count ; index0++ )
					_this->_array[ index0 ]->release();
				_count = 0;
			}
		};
		void remove( size_t index , const char* file = __FILE__ , int line = __LINE__ )
		{
			remove( index , 1 , file , line );
		};
		void remove( size_t index , size_t items_count , const char* file = __FILE__ , int line = __LINE__ )
		{
			file = file;
			line = line;
			array< T >* _this = &operator()();
			if( index < _this->_count )
			{
				if( index + items_count > _this->_count )
					items_count = _this->_count - index;
				for( size_t index0 = 0 ; index0 < items_count ; index0++ )
					_this->_array[ index0 + index ]->release();
				::booldog::mem::remove( index * sizeof( T* ) , _this->_array , _this->_count * sizeof( T* ) , items_count * sizeof( T* ) );
				_this->_count -= items_count;
			}
		};
		size_t add( const T& item , const char* file = __FILE__ , int line = __LINE__ )
		{
			return insert( SIZE_MAX , const_cast< T* >( &item ) , file , line );
		};
		size_t add( T* item , const char* file = __FILE__ , int line = __LINE__ )
		{
			return insert( SIZE_MAX , &item , 1 , file , line );
		};
		size_t add( T** items , size_t items_count , const char* file = __FILE__ , int line = __LINE__ )
		{
			return insert( SIZE_MAX , items , items_count , 1 , file , line );
		};
		size_t insert( size_t index , const T& item , const char* file = __FILE__ , int line = __LINE__ )
		{
			return insert( index , const_cast< T* >( &item ) , file , line );
		};
		size_t insert( size_t index , T* item , const char* file = __FILE__ , int line = __LINE__ )
		{
			return insert( index , &item , 1 , file , line );
		};
		size_t insert( size_t index , T** items , size_t items_count , const char* file = __FILE__ , int line = __LINE__ )
		{
			array< T >* _this = &operator()();
			if( index > _this->_count )
				index = _this->_count;

			if( _this->_array == 0 || ::booldog::mem::expand( index * sizeof( T* ) , _this->_array , _this->_count * sizeof( T* ) , _this->_size * sizeof( T* ) , items_count * sizeof( T* ) ) == false )
			{
				_this->_size += items_count + BOOLDOG_ARRAY_STEP;
				_this->_array = (::booldog::object**)_allocator->realloc( _this->_array , sizeof( T* ) * _size , file , line );
			}
			T object( _allocator );
			for( size_t index0 = 0 ; index0 < items_count ; index0++ )
			{
				object = *items[ index0 ];
				_this->_array[ index0 + index ] = object.detach();
			}
			_this->_count += items_count;
			return index;
		};
		size_t insert( size_t index , ::booldog::object& item , const char* file = __FILE__ , int line = __LINE__ )
		{
			if( ::booldog::compile::If< item_type::type_hash == ::booldog::object::type_hash >::test() )
			{
				const T* itemobj = const_cast< const T* >( (T*)&item );
				return insert( index , *itemobj , file , line );
			}
			else
			{
				T object( _allocator );
				if( object.can_try_assign( item ) )
				{
					object = item;
					return insert( index , &object , file , line );
				}
				else if( item.get_type_hash( 0 , false ) == type_hash )
				{
				
				}
			}
			return index;
		};
		T& operator[] ( size_t index )
		{
			return *(T*)operator()()._array[ index ];
		};
	};
};
#endif
