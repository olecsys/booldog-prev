#ifndef BOO_ATOMIC_H
#define BOO_ATOMIC_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_platform.h"

#ifdef BOO_WINDOWS_OS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

#ifdef BOO_SOLARIS_OS
typedef volatile unsigned int boo_atomic;
typedef unsigned int boo_atomic_return;
const boo_atomic_return boo_atomic_max = 0xffffffff;
#else
typedef volatile long boo_atomic;
typedef long boo_atomic_return;
#ifdef __SIZEOF_LONG__
#if __SIZEOF_LONG__ == 8
const boo_atomic_return boo_atomic_max = 0xffffffffffffffff;
#else
const boo_atomic_return boo_atomic_max = 0xffffffff;
#endif
#else
const boo_atomic_return boo_atomic_max = 0xffffffff;
#endif
#endif
inline boo_atomic_return boo_increment(boo_atomic* addend) {
#ifdef __WINDOWS__
  return InterlockedIncrement(addend);
#elif defined(__SOLARIS__)
  return atomic_add_32_nv(addend, 1);
#elif defined(__LINUX__)
  return __sync_add_and_fetch(addend, 1);
#endif
}
inline boo_atomic_return boo_decrement(boo_atomic* addend) {
#ifdef __WINDOWS__
  return InterlockedDecrement(addend);
#elif defined(__SOLARIS__)
  return atomic_dec_32_nv(addend);
#elif defined(__LINUX__)
  return __sync_sub_and_fetch(addend, 1);
#endif
}
inline boo_atomic_return boo_exchange(boo_atomic* target, boo_atomic_return value) {
#ifdef __WINDOWS__
  return InterlockedExchange(target, value);
#elif defined(__LINUX__)
  return __sync_lock_test_and_set(target, value);
#elif defined(__SOLARIS__)
  return atomic_swap_32(target, value);
#endif
}
inline boo_atomic_return boo_compare_exchange(boo_atomic* target, boo_atomic_return exchange,
                                              boo_atomic_return comparand) {
#ifdef __WINDOWS__
  return InterlockedCompareExchange(target, exchange, comparand);
#elif defined(__LINUX__)
  return __sync_val_compare_and_swap(target, comparand, exchange);
#elif defined(__SOLARIS__)
  return atomic_cas_32(target, comparand, exchange);
#endif
}
inline boo_atomic_return boo_exchange_add(boo_atomic* target, boo_atomic_return value) {
#ifdef __WINDOWS__
  return InterlockedExchangeAdd(target, value);
#elif defined(__SOLARIS__)
  return atomic_add_32(target, value);
#elif defined(__LINUX__)
  return __sync_fetch_and_add(target, value);
#endif
}
inline boo_atomic_return boo_exchange_subtract(boo_atomic* target, boo_atomic_return value) {
#ifdef __WINDOWS__
  return InterlockedExchangeAdd(target, -value);
#elif defined(__SOLARIS__)
  return atomic_add_32(target, -value);
#elif defined(__LINUX__)
  return __sync_fetch_and_sub(target, value);
#endif
}
inline void* boo_compare_exchange_pointer(void* volatile* target, void* exchange, void* comparand) {
#ifdef __WINDOWS__
  return InterlockedCompareExchangePointer(target, exchange, comparand);
#elif defined(__LINUX__)
  return __sync_val_compare_and_swap(target, comparand, exchange);
#elif defined(__SOLARIS__)
  return atomic_cas_ptr(*target, comparand, exchange);
#endif
}
inline void* boo_exchange_pointer(void* volatile* target, void* exchange) {
#ifdef __WINDOWS__
  return InterlockedExchangePointer(target, exchange);
#elif defined(__LINUX__)
  return __sync_lock_test_and_set(target, exchange);
#else
#error "boo_atomic.h, cannot boo_exchange_pointer OS implementation"
#endif
}

#ifndef BDOG_ATOM
#define BDOG_ATOM boo_atomic
#endif
#ifndef BDOG_ATOM_RETURN
#define BDOG_ATOM_RETURN boo_atomic_return
#endif
#ifndef BDOG_ATOM_MAX
#define BDOG_ATOM_MAX boo_atomic_max
#endif

#ifndef BDOG_ATOM_INC
#define BDOG_ATOM_INC(addend) boo_increment(addend)
#endif

#ifndef BDOG_ATOM_DEC
#define BDOG_ATOM_DEC(addend) boo_decrement(addend)
#endif

#ifndef BDOG_ATOM_EXCH
#define BDOG_ATOM_EXCH(target, value) boo_exchange(target, value)
#endif

#ifndef BDOG_ATOM_CMP_EXCH
#define BDOG_ATOM_CMP_EXCH(target, exchange, comparand)                                            \
  boo_compare_exchange(target, exchange, comparand)
#endif

#ifndef BDOG_ATOM_EXCH_ADD
#define BDOG_ATOM_EXCH_ADD(target, value) boo_exchange_add(target, value)
#endif

#ifndef BDOG_ATOM_EXCH_SUB
#define BDOG_ATOM_EXCH_SUB(target, value) boo_exchange_subtract(target, value)
#endif

#ifndef BDOG_ATOM_CMP_EXCH_PTR
#define BDOG_ATOM_CMP_EXCH_PTR(target, exchange, comparand)                                        \
  boo_compare_exchange_pointer(target, exchange, comparand)
#endif

#ifndef BDOG_ATOM_EXCH_PTR
#define BDOG_ATOM_EXCH_PTR(target, exchange) boo_exchange_pointer(target, exchange)
#endif
#endif