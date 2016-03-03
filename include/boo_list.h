#ifndef BOO_LIST_H
#define BOO_LIST_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_object.h)
#include BOOLDOG_HEADER(boo_mem.h)
namespace booldog
{
#define BOOLDOG_LIST_STEP 32
	template< class T >
	class list : public object
	{
	public:
		typedef T item_type;
		static const ::booldog::uint64 type_hash = ::booldog::hash::compile::times33< 'b','o','o','l','d','o','g','.','l','i','s','t' >::value;
		static const bool use_item_type = true;
	private:
		::booldog::object** _array;
		size_t _size;
		size_t _count;
	public:
		list( booldog::allocator* allocator )
			: ::booldog::object( allocator )
		{
			_array = 0;
			_size = 0;
			_count = 0;
		};
		~list( void )
		{
			if( _array )
			{
				for( size_t index0 = 0 ; index0 < _count ; index0++ )
					_array[ index0 ]->release();
				_allocator->free( _array );
			}
		};
		list< T >& operator ()( void )
		{
			if( _obj )
				return *static_cast< list< T >* >( _obj );
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
			list< T >* _this = &operator()();
			if( _this->_array )
			{
				for( size_t index0 = 0 ; index0 < _this->_count ; index0++ )
					_this->_array[ index0 ]->release();
				_count = 0;
			}
		};
		void remove( size_t index , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			remove( index , 1 , debuginfo );
		};
		void remove( size_t index , size_t items_count , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			debuginfo = debuginfo;
			list< T >* _this = &operator()();
			if( index < _this->_count )
			{
				if( index + items_count > _this->_count )
					items_count = _this->_count - index;
				for( size_t index0 = 0 ; index0 < items_count ; index0++ )
					_this->_array[ index0 + index ]->release();
				::booldog::mem::remove< ::booldog::object* >( index , _this->_array , _this->_count , items_count );
				_this->_count -= items_count;
			}
		};
		size_t add( const T& item , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			return insert( SIZE_MAX , const_cast< T* >( &item ) , debuginfo );
		};
		size_t add( T* item , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			return insert( SIZE_MAX , &item , 1 , debuginfo );
		};
		size_t add( T** items , size_t items_count , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			return insert( SIZE_MAX , items , items_count , 1 , debuginfo );
		};
		size_t insert( size_t index , const T& item , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			return insert( index , const_cast< T* >( &item ) , debuginfo );
		};
		size_t insert( size_t index , T* item , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			return insert( index , &item , 1 , debuginfo );
		};
		size_t insert( size_t index , T** items , size_t items_count , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			list< T >* _this = &operator()();
			if( index > _this->_count )
				index = _this->_count;

			if( _this->_array == 0 || ::booldog::mem::expand< ::booldog::object* >( index , _this->_array , _this->_count 
				, _this->_size , items_count ) == false )
			{
				_this->_size += items_count + BOOLDOG_LIST_STEP;
				_this->_array = (::booldog::object**)_allocator->realloc_array< ::booldog::object* >( _this->_array , _size , debuginfo );
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
		size_t insert( size_t index , ::booldog::object& item , const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			if( ::booldog::compile::If< item_type::type_hash == ::booldog::object::type_hash >::test() )
			{
				const T* itemobj = const_cast< const T* >( (T*)&item );
				return insert( index , *itemobj , debuginfo );
			}
			else
			{
				T object( _allocator );
				if( object.can_try_assign( item ) )
				{
					object = item;
					return insert( index , &object , debuginfo );
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
