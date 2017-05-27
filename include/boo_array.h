#ifndef BOO_ARRAY_H
#define BOO_ARRAY_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_object.h"
#include "boo_mem.h"
#include "boo_result.h"
#include "boo_error.h"
namespace booldog
{
#define BOOLDOG_ARRAY_STEP 32
	template< class T, size_t step = BOOLDOG_ARRAY_STEP >
	class array
	{
	public:
	private:
		booldog::allocator* _allocator;
		T* _array;
		size_t _size;
		size_t _count;
	public:
		array(::booldog::allocator* allocator)
			: _array(0), _size(0), _count(0), _allocator(allocator)
		{
		}
		~array()
		{
			if(_array)
				_allocator->free(_array);
		}
		size_t count()
		{
			return _count;
		}
		size_t size()
		{
			return _size;
		}
		void clear()
		{
			_count = 0;
		}
		void remove(size_t index, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			remove(index, 1, debuginfo);
		}
		void remove(size_t index, size_t items_count, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			debuginfo = debuginfo;
			if(index < _count)
			{
				if(index + items_count > _count)
					items_count = _count - index;
				::booldog::mem::remove< T >(index, _array, _count, items_count);
				_count -= items_count;
			}
		}
		size_t add(const T& item, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			return insert(SIZE_MAX, const_cast< T* >(&item), 1, debuginfo);
		}
		size_t add(T* items, size_t items_count, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			return insert(SIZE_MAX, items, items_count, debuginfo);
		}
		size_t add(const ::booldog::array< T >& array, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{	
			return insert(SIZE_MAX, array._array, array._count, debuginfo);
		}
		size_t insert(size_t index, const T& item, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			return insert(index, const_cast< T* >(&item), 1, debuginfo);
		}
		size_t insert(size_t index, T* items, size_t items_count, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			if(items && items_count)
			{
				if(index > _count)
					index = _count;
				if(_array == 0 || ::booldog::mem::expand< T >(index, _array, _count, _size, items_count) == false)
				{
					_size += items_count + step;
					_array = _allocator->realloc_array< T >(_array, _size, debuginfo);
				}
				if(items_count == 1)
					_array[index] = *items;
				else
					::memcpy(&_array[index], items, items_count * sizeof(T));
				_count += items_count;
			}
			else
				return SIZE_MAX;
			return index;
		}
		T& operator[] ( size_t index )
		{
			return _array[ index ];
		};
		const T* raw( void )
		{
			return _array;
		};
		bool resize( ::booldog::result* pres , size_t newsize , bool only_increase 
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			::booldog::result locres;
			BOOINIT_RESULT( ::booldog::result );
			if( newsize > _size )
			{
				_size = newsize;
				_array = _allocator->realloc_array< T >( _array , _size , debuginfo );
			}
			else if( newsize < _size && only_increase == false )
			{
				_size = newsize;
				_array = _allocator->realloc_array< T >( _array , _size , debuginfo );
				if( _size > _count )
					_count = _size;
			}
			else
				goto goto_return;
			if( _array == 0 )
			{
				_count = 0;
				_size = 0;
				res->booerr( ::booldog::enums::result::booerr_type_cannot_alloc_memory );
			}
goto_return:
			return res->succeeded();
		};
	};
};
#endif
