#ifndef BOO_LOCKFREE_QUEUE_H
#define BOO_LOCKFREE_QUEUE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_types.h"
#include "boo_interlocked.h"
namespace booldog
{
	namespace data
	{
		namespace lockfree
		{
			static const void* queue_max = (void*)SIZE_MAX;
			template< class T >
			class queue
			{
			public:
			private:				
				void* volatile _head;
				void* volatile _tail;
				::booldog::interlocked::atomic _count;
			public:
                queue()
					: _head(0), _tail(0), _count(0)
				{
                }
                ::booldog::interlocked::atomic_return count()
				{
					return ::booldog::interlocked::compare_exchange(&_count, 0, 0);
                }
				booinline void enqueue(T* item)
				{
					T* volatile* item_next = &item->_next;
					item->_next = (T*)::booldog::data::lockfree::queue_max;
					for(;;)
					{	
						T* tail = (T*)::booldog::interlocked::exchange_pointer(&_tail, (void*)::booldog::data::lockfree::queue_max);
						if(tail == ::booldog::data::lockfree::queue_max)
							continue;
						else if(tail)
						{
							T* volatile* tail_next = &tail->_next;

							if(::booldog::interlocked::exchange_pointer((void* volatile*)tail_next
								, (void*)::booldog::data::lockfree::queue_max) == ::booldog::data::lockfree::queue_max)
							{
								::booldog::interlocked::exchange_pointer(&_tail, (void*)tail);
								continue;
							}
							::booldog::interlocked::exchange_pointer(&_tail, (void*)item);
							::booldog::interlocked::exchange_pointer((void* volatile*)tail_next, (void*)item);
						}
						else
						{
							if(::booldog::interlocked::compare_exchange_pointer(&_head, (void*)item, 0) != 0)
							{
								::booldog::interlocked::exchange_pointer(&_tail, (void*)tail);
								continue;
							}
							::booldog::interlocked::exchange_pointer(&_tail, (void*)item);
						}
						::booldog::interlocked::increment(&_count);
						break;
					}
					::booldog::interlocked::exchange_pointer((void* volatile*)item_next, (void*)0);
                }
                booinline T* dequeue()
				{
					T* item = 0;
					for(;;)
					{
						T* head = (T*)::booldog::interlocked::exchange_pointer(&_head, (void*)::booldog::data::lockfree::queue_max);
						if(head == ::booldog::data::lockfree::queue_max)
							continue;
						else if(head == 0)
						{
							::booldog::interlocked::exchange_pointer(&_head, (void*)0);
							break;
						}						
						T* volatile* head_next = &head->_next;

						void* next = ::booldog::interlocked::exchange_pointer((void* volatile*)head_next
							, (void*)::booldog::data::lockfree::queue_max);
						if(next == ::booldog::data::lockfree::queue_max)
						{
							::booldog::interlocked::exchange_pointer(&_head, head);
							continue;
						}
						else if(next == 0)
						{
							if(::booldog::interlocked::compare_exchange_pointer(&_tail, (void*)0, head) != head)
							{
								::booldog::interlocked::exchange_pointer((void* volatile*)head_next, next);
								::booldog::interlocked::exchange_pointer(&_head, head);
								continue;
							}
						}
						::booldog::interlocked::exchange_pointer(&_head, next);
						::booldog::interlocked::exchange_pointer((void* volatile*)head_next, next);
						item = head;
						::booldog::interlocked::decrement(&_count);
						break;
					}
					return item;
                }
			};
        }
    }
}
#endif
