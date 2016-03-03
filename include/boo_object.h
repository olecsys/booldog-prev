#ifndef BOO_OBJECT_H
#define BOO_OBJECT_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_allocator.h)
#include BOOLDOG_HEADER(boo_interlocked.h)
#include BOOLDOG_HEADER(boo_hash_times33.h)

#include <string.h>
namespace booldog
{
	class object
	{	
	public:
		typedef ::booldog::object item_type;
		static const ::booldog::uint64 type_hash = ::booldog::hash::compile::times33< 'b','o','o','l','d','o','g','.','o','b','j','e','c','t' >::value;
		static const bool use_item_type = false;
	public:
		::booldog::interlocked::atomic _ref;
		booldog::allocator* _allocator;
		object* _obj;
		object( booldog::allocator* allocator )
		{
			_ref = 1;
			_allocator = allocator;
			_obj = 0;
		};
		object( booldog::allocator* allocator , ::booldog::object& obj )
		{
			_ref = 1;
			_allocator = allocator;
			_obj = 0;
			operator=( obj );
		};
		virtual ~object( void )
		{
			if( _obj && _obj != this )
				_obj->release();
		};
		void addref( void ) const
		{
			::booldog::interlocked::increment( const_cast< ::booldog::interlocked::atomic* >( &_ref ) );
		};
		void release( void ) const
		{
			if( ::booldog::interlocked::decrement( const_cast< ::booldog::interlocked::atomic* >( &_ref ) ) == 0 )
				_allocator->destroy< ::booldog::object >( const_cast< ::booldog::object* >( this ) );
		};
		object& operator ()( void )
		{
			if( _obj )
				return *_obj;
			else
				return *this;
		};
		virtual ::booldog::uint64 get_type_hash( int level , bool owner ) const
		{
			if( owner == false )
			{
				if( _obj && _obj != this )
					return _obj->get_type_hash( level , false );
			}
			return type_hash;
		};
		virtual bool get_use_item_type( int level ) const
		{
			if( _obj && _obj != this )
				return _obj->get_use_item_type( level );
			return false;
		};
		virtual size_t type_size( void ) const
		{
			return sizeof( *this );
		};
		bool is_equal_classes( const ::booldog::object& dst ) const
		{
			if( _obj && _obj != this )
				return _obj->is_equal_classes( dst );
			bool dst_use_item_type = false;
			for( int level = 0 ; level < 6 ; level++ )
			{
				dst_use_item_type = dst.get_use_item_type( level );
				if( dst_use_item_type != get_use_item_type( level ) )
					return false;
				if( dst.get_type_hash( level , false ) != get_type_hash( level , false ) )
					return false;
				if( dst_use_item_type == false )
					return true;
			}
			return false;
		};
		bool can_try_assign( const ::booldog::object& dst ) const
		{
			if( _obj && _obj != this )
				return _obj->can_try_assign( dst );
			::booldog::uint64 dst_type_hash = 0 , src_type_hash = 0;
			bool dst_use_item_type = false;
			for( int level = 0 ; level < 6 ; level++ )
			{
				dst_type_hash = dst.get_type_hash( level , true );

				if( dst_type_hash == ::booldog::object::type_hash )
					return true;
				src_type_hash = get_type_hash( level , false );
				if( dst_type_hash != src_type_hash )
				{
					if( level != 0 && src_type_hash == ::booldog::object::type_hash )
						return true;
					return false;
				}
				dst_use_item_type = dst.get_use_item_type( level );
				if( dst_use_item_type != get_use_item_type( level ) )
					return false;
				if( dst_use_item_type == false )
					return true;
			}
			return false;
		};
		::booldog::object* detach( void ) const
		{
			::booldog::object* _obj_ = const_cast< ::booldog::object* >( this );
			if( _obj == 0 )
			{
				size_t size = _obj_->type_size();
				::booldog::allocator* new_allocator = _allocator;
				::booldog::object* new_obj = (::booldog::object*)_obj_->_allocator->alloc( size );
				::memcpy( new_obj , _obj_ , size );
				
				char* zero = (char*)&_obj_->_ref;
				zero += sizeof( _obj_->_ref );
				size -= zero - (char*)_obj_;
				::memset( zero , 0 , size );

				new_obj->_ref = 1;
				new_obj->_allocator = new_allocator;
				new_obj->_obj = new_obj;

				_obj_->_obj = new_obj;
			}
			::booldog::object* res = _obj;
			_obj_->_ref = 1;
			_obj_->_obj = 0;
			return res;
		};
		::booldog::object& operator =( const ::booldog::object& obj )
		{
			if( _obj )
			{
				_obj->release();
				_obj = 0;
			}
			if( obj._obj )
			{
				if( get_type_hash( 0 , true ) == ::booldog::object::type_hash
					|| is_equal_classes( obj ) )
				{
					_obj = obj._obj;
					_obj->addref();
				}
			}
			else
			{
				if( obj.get_type_hash( 0 , false ) != ::booldog::object::type_hash )
				{
					if( get_type_hash( 0 , true ) == ::booldog::object::type_hash
						|| is_equal_classes( obj ) )
					{
						::booldog::object* _obj_ = const_cast< ::booldog::object* >( &obj );

						size_t size = _obj_->type_size();
						::booldog::allocator* new_allocator = _allocator;
						::booldog::object* new_obj = (::booldog::object*)new_allocator->alloc( size );
						::memcpy( new_obj , _obj_ , size );

						char* zero = (char*)&_obj_->_ref;
						zero += sizeof( _obj_->_ref );
						size -= zero - (char*)_obj_;
						::memset( zero , 0 , size );

						new_obj->_ref = 1;
						new_obj->_allocator = new_allocator;
						new_obj->_obj = new_obj;

						_obj_->_obj = new_obj;
						return operator =( obj );
					}
				}
			}
			return *this;
		};
	};
};
#endif
