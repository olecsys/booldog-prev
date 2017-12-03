#ifndef BOO_LOCKABLE_POINTER_H
#define BOO_LOCKABLE_POINTER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
//#include "boo_multimedia_video_frame.h"
//#include "boo_multimedia_enums.h"
#include "boo_types.h"
namespace booldog {
	namespace typedefs {
		typedef void* (*malloc_t)(size_t size, void* udata);
		typedef void* (*realloc_t)(void* pointer, size_t size, void* udata);
		typedef void (*free_t)(void* pointer, void* udata);
	}
	struct allocation
	{
		typedefs::malloc_t _malloc;
		typedefs::realloc_t _realloc;
		typedefs::free_t _free;
	};
}
#endif
