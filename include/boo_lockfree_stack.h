#ifndef BOO_LOCKFREE_STACK_H
#define BOO_LOCKFREE_STACK_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_types.h"
#include "boo_interlocked.h"
#include "boo_threading_utils.h"

namespace booldog
{
	namespace data
	{
		namespace lockfree
		{
			namespace intrusive
			{
				template < class T > class stack;
				class stack_item
				{
					template < class T1 >
					friend class ::booldog::data::lockfree::intrusive::stack;
				protected:
					void* volatile _next;
					::booldog::interlocked::atomic _writer_readers;
					stack_item()
						: _next(0), _writer_readers(0)
					{
					}
				};
				template< class T >
				class stack
				{
				public:
					static const ::booldog::int32 WRITER_BIT = 1L << (sizeof(::booldog::int32) * 8 - 2);
				private:				
					void* volatile _top;
					::booldog::interlocked::atomic _count;
				public:
					stack()
						: _top(0), _count(0)
					{
					}
					::booldog::interlocked::atomic_return count()
					{
						return ::booldog::interlocked::compare_exchange(&_count, 0, 0);
					}
					booinline void push(::booldog::data::lockfree::intrusive::stack_item* item)
					{
						::booldog::byte tries = 0;
						while(::booldog::interlocked::compare_exchange(&item->_writer_readers, WRITER_BIT, 0) != 0)
						{
							if(tries++ == 5)
							{
								::booldog::threading::sleep(1);
								tries = 0;
							}
						}

						void* top = _top;
						for(;;)
						{
							item->_next = top;
							void* curtop = ::booldog::interlocked::compare_exchange_pointer(&_top, (void*)item, top);
							if(curtop != top)
							{
								top = (T*)curtop;
								continue;
							}

							::booldog::interlocked::exchange_add(&item->_writer_readers, -WRITER_BIT);

							::booldog::interlocked::increment(&_count);
							break;
						}
					}
					booinline T* pop()
					{
						::booldog::data::lockfree::intrusive::stack_item* top 
							= (::booldog::data::lockfree::intrusive::stack_item*)::booldog::interlocked::compare_exchange_pointer(&_top, (void*)0, (void*)0);
						for(;;)
						{
							if(top == 0)
								break;

							if(::booldog::interlocked::increment(&top->_writer_readers) >= WRITER_BIT)
							{
								::booldog::byte tries = 0;
								while(::booldog::interlocked::compare_exchange(&top->_writer_readers, 0, 0) >= WRITER_BIT)
								{
									if(tries++ == 5)
									{
										::booldog::threading::sleep(1);
										tries = 0;
									}
								}
							}

							void* curtop = ::booldog::interlocked::compare_exchange_pointer(&_top, top->_next, (void*)top);

							::booldog::interlocked::decrement(&top->_writer_readers);

							if(curtop != top)
							{
								top = (T*)curtop;
								continue;
							}							
							::booldog::interlocked::decrement(&_count);
							break;
						}
						return (T*)top;
					}
				};
			}
        }
    }
}
#endif
