#ifndef BOO_DOUBLY_LINKED_LIST_H
#define BOO_DOUBLY_LINKED_LIST_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_types.h)
namespace booldog
{
	namespace data
	{
		template< class T >
		class doubly_linked_list
		{
		public:
		private:
			T* _first;
			T* _last;
			size_t _count;
		public:
			doubly_linked_list( void )
				: _first( 0 ) , _last( 0 ) , _count( 0 )
			{
			};
			size_t count( void )
			{
				return _count;
			};
			void clear( void )
			{
				_last = 0;
				_first = 0;
				_count = 0;
			};
			bool exists(T* item)
			{
#ifdef BOOLDOG_DOUBLY_LINKED_PARENT_ENABLE
				return item->_doubly_linked_list_parent == this;
#else
				T* next = _first;
				for(;;)
				{
					if(next == 0 || next == item)
						break;
					next = next->_doubly_linked_list_next;
				}
				return next != 0;
#endif
			};
			void remove( T* item )
			{
				if( item == _first )
					_first = item->_doubly_linked_list_next;
				else
					item->_doubly_linked_list_prev->_doubly_linked_list_next = item->_doubly_linked_list_next;
				if( item == _last )
					_last = item->_doubly_linked_list_prev;
				else
					item->_doubly_linked_list_next->_doubly_linked_list_prev = item->_doubly_linked_list_prev;	
#ifdef BOOLDOG_DOUBLY_LINKED_PARENT_ENABLE
				item->_doubly_linked_list_parent = 0;
#endif
				_count--;
			};
			void insert_before(T* item, T* insertion_item)
			{
				if(_first == item)
					_first = insertion_item;
				else
					item->_doubly_linked_list_prev->_doubly_linked_list_next = insertion_item;
				insertion_item->_doubly_linked_list_prev = item->_doubly_linked_list_prev;
				insertion_item->_doubly_linked_list_next = item;
				item->_doubly_linked_list_prev = insertion_item;
#ifdef BOOLDOG_DOUBLY_LINKED_PARENT_ENABLE
				insertion_item->_doubly_linked_list_parent = this;
#endif
				++_count;
			};
			size_t add(T* item)
			{
				if( _first == 0 )
					_first = item;
				else
					_last->_doubly_linked_list_next = item;
				item->_doubly_linked_list_prev = _last;
				item->_doubly_linked_list_next = 0;
				_last = item;
#ifdef BOOLDOG_DOUBLY_LINKED_PARENT_ENABLE
				item->_doubly_linked_list_parent = this;
#endif
				return _count++;
			};
			void remove(T& item)
			{
				remove(&item);
			};
			size_t add(T& item)
			{
				return add(&item);
			};
			T* first( void )
			{
				return _first;
			};
			T* last( void )
			{
				return _last;
			};
			T* operator[] ( size_t index )
			{
				T* find = 0;
				if( index < _count )
				{
					if( index > _count / 2 )
					{
						index = _count - index - 1;
						find = _last;
						while( index-- != 0 )
							find = find->_doubly_linked_list_prev;
					}
					else
					{
						find = _first;
						while( index-- != 0 )
							find = find->_doubly_linked_list_next;
					}
				}
				return find;
			};
		};
	};
};
#endif
