#ifndef BOO_LOCKFREE_QUEUE_H
#define BOO_LOCKFREE_QUEUE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER(header) <header>
#endif
#include BOOLDOG_HEADER(boo_types.h)
#include BOOLDOG_HEADER(boo_interlocked.h)
#include BOOLDOG_HEADER(boo_if.h)
namespace booldog
{
	namespace data
	{
		namespace lockfree
		{
			template< class T >
			class queue
			{
			public:
			private:
				void* volatile _head;
				void* volatile _tail;
				::booldog::interlocked::atomic _count;
			public:
				queue(void)
					: _head(0), _tail(0), _count(0)
				{
				};
				::booldog::interlocked::atomic_return count(void)
				{
					return ::booldog::interlocked::compare_exchange(&_count, 0, 0);
				};
				booinline void enqueue(T* item)
				{
					item->_next = 0;
					void* max = (void*)0xffffffff;
					if(::booldog::compile::If<sizeof(void*) == 8>::test())
						max = (void*)0xffffffffffffffff;
					for(;;)
					{
						T* head = (T*)::booldog::interlocked::compare_exchange_pointer(&_head, max, 0);
						if(head == max)
							continue;
						T* tail = (T*)::booldog::interlocked::exchange_pointer(&_tail, max);
						if(tail == max)
						{
							if(head == 0)
								::booldog::interlocked::exchange_pointer(&_head, (void*)0);
							continue;
						}
						if(tail)
							tail->_next = item;
						::booldog::interlocked::exchange_pointer(&_tail, (void*)item);
						if(head == 0)
							::booldog::interlocked::exchange_pointer(&_head, (void*)item);
						::booldog::interlocked::increment(&_count);
						break;
					}
				};
				booinline T* dequeue(void)
				{
					T* item = 0;
					void* max = (void*)0xffffffff;
					if(::booldog::compile::If<sizeof(void*) == 8>::test())
						max = (void*)0xffffffffffffffff;
					for(;;)
					{
						T* head = (T*)::booldog::interlocked::exchange_pointer(&_head, max);
						if(head == max)
							continue;
						else if(head == 0)
						{
							::booldog::interlocked::exchange_pointer(&_head, (void*)0);
							break;
						}
						T* tail = (T*)::booldog::interlocked::compare_exchange_pointer(&_tail, max, head);
						if(tail == max)
						{
							::booldog::interlocked::exchange_pointer(&_head, head);
							continue;
						}
						item = head;
						if(head == tail)
							::booldog::interlocked::exchange_pointer(&_tail, (void*)0);
						::booldog::interlocked::exchange_pointer(&_head, item->_next);
						::booldog::interlocked::decrement(&_count);
						break;
					}
					return item;
				};
			};
		};
	};
};
#endif
