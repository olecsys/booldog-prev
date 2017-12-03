#ifndef BOO_LOCKABLE_POINTER_H
#define BOO_LOCKABLE_POINTER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_allocation.h"
namespace booldog
{
	namespace lockable
	{
		struct owner;
		struct pointer;
	}
	namespace enums {
		namespace loadable {
			enum events {
				owner_destroying
			};
		}
	}
	namespace typedefs {
		namespace lockable {
			typedef void (*onevent)(::booldog::lockable::owner* owner
				, ::booldog::enums::loadable::events event_type
				, ::booldog::lockable::pointer* pointer);
		}
	}
	namespace lockable
	{
		struct owner
		{


		};
		struct pointer
		{
			owner* _owner;
			pointer(owner* owner)
			{
			}
			~pointer()
			{
			}
			bool lock()
			{
				return false;
			}
			bool unlock()
			{
				return false;
			}
		};
	}
}
#endif
