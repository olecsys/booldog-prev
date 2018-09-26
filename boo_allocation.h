#ifndef BOO_ALLOCATION_H
#define BOO_ALLOCATION_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_platform.h"
#include <stdlib.h>
typedef void* (*boo_malloc_t)(size_t size, void* udata);
typedef void* (*boo_realloc_t)(void* pointer, size_t size, void* udata);
typedef void (*boo_free_t)(void* pointer, void* udata);
inline void* boo_default_malloc(size_t size, void*) {
	return malloc(size);
}
inline void* boo_default_realloc(void* pointer, size_t size, void*) {
	return realloc(pointer, size);
}
inline void boo_default_free(void* pointer, void*) {
	free(pointer);
}
typedef struct boo_allocation
{
	boo_malloc_t malloc;
	boo_realloc_t realloc;
	boo_free_t free;
	void* udata;
} boo_allocation;

#ifdef BOO_WINDOWS_OS
#else
#include <pthread.h>
static pthread_key_t boo_allocation_tls;
static pthread_once_t boo_allocation_key_once = PTHREAD_ONCE_INIT;
static void boo_allocation_make_tls() {
	(void)pthread_key_create(&boo_allocation_tls, NULL);
}
#endif

inline int boo_set_allocation(struct boo_allocation* allocation
	, struct boo_allocation** prev_allocation) {
	int result = -1;
#ifdef BOO_WINDOWS_OS
#else
	(void)pthread_once(&boo_allocation_key_once, boo_allocation_make_tls);
	if(prev_allocation) {
		*prev_allocation = (struct boo_allocation*)pthread_getspecific(boo_allocation_tls);
	}
	result = pthread_setspecific(boo_allocation_tls, allocation);
#endif
	return result;
}
inline struct boo_allocation* boo_get_allocation() {
	struct boo_allocation* allocation = NULL;
#ifdef BOO_WINDOWS_OS
#else
	(void)pthread_once(&boo_allocation_key_once, boo_allocation_make_tls);
	allocation = (struct boo_allocation*)pthread_getspecific(boo_allocation_tls);
#endif
	return allocation;
}

#endif
