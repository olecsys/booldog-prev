#ifndef BOO_INTERLOCKED_H
#define BOO_INTERLOCKED_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_types.h)
namespace booldog
{
	namespace interlocked
	{
#ifdef __SOLARIS__
		typedef volatile ::booldog::uint32 atomic;
		typedef ::booldog::uint32 atomic_return;
		const ::booldog::interlocked::atomic_return max = 0xffffffff;
#else
		typedef volatile long atomic;
		typedef long atomic_return;
#ifdef __SIZEOF_LONG__
#if __SIZEOF_LONG__ == 8
		const ::booldog::interlocked::atomic_return max = 0xffffffffffffffff;
#else
		const ::booldog::interlocked::atomic_return max = 0xffffffff;
#endif
#else
		const ::booldog::interlocked::atomic_return max = 0xffffffff;
#endif
#endif
		booinline ::booldog::interlocked::atomic_return increment( ::booldog::interlocked::atomic* lpAddend )
		{
#ifdef __WINDOWS__
			return ::InterlockedIncrement( lpAddend );
#elif defined( __SOLARIS__ )
			return atomic_add_32_nv( lpAddend , 1 );
#elif defined( __LINUX__ )
			return __sync_add_and_fetch( lpAddend , 1 );
#endif
		};
		booinline ::booldog::interlocked::atomic_return decrement( ::booldog::interlocked::atomic* lpAppend )
		{
#ifdef __WINDOWS__
			return ::InterlockedDecrement( lpAppend );
#elif defined( __SOLARIS__ )
			return atomic_dec_32_nv( lpAppend );
#elif defined( __LINUX__ )
			return __sync_sub_and_fetch( lpAppend , 1 );
#endif
		};
		booinline ::booldog::interlocked::atomic_return exchange( ::booldog::interlocked::atomic* lpTarget , ::booldog::interlocked::atomic_return lValue )
		{
#ifdef __WINDOWS__
			return ::InterlockedExchange( lpTarget , lValue );
#elif defined( __LINUX__ )
			return __sync_lock_test_and_set( lpTarget , lValue );
#elif defined( __SOLARIS__ )
			return atomic_swap_32( lpTarget , lValue );
#endif
		};
		booinline ::booldog::interlocked::atomic_return compare_exchange( ::booldog::interlocked::atomic* target , ::booldog::interlocked::atomic_return exchange , ::booldog::interlocked::atomic_return comparand )
		{
#ifdef __WINDOWS__
			return ::InterlockedCompareExchange( target , exchange , comparand );
#elif defined( __LINUX__ )
			return __sync_val_compare_and_swap( target , comparand , exchange );
#elif defined( __SOLARIS__ )
			return atomic_cas_32( target , comparand , exchange );
#endif
		};
		booinline ::booldog::interlocked::atomic_return exchange_add( ::booldog::interlocked::atomic* target , ::booldog::interlocked::atomic_return value )
		{
#ifdef __WINDOWS__
			return ::InterlockedExchangeAdd( target , value );
#elif defined( __SOLARIS__ )
			return atomic_add_32( target , value );
#elif defined( __LINUX__ )
			return __sync_fetch_and_add( target , value );
#endif
		};
		booinline ::booldog::interlocked::atomic_return exchange_subtract( ::booldog::interlocked::atomic* target , ::booldog::interlocked::atomic_return value )
		{
#ifdef __WINDOWS__
			return ::InterlockedExchangeAdd( target , -value );
#elif defined( __SOLARIS__ )
			return atomic_add_32( target , -value );
#elif defined( __LINUX__ )
			return __sync_fetch_and_sub( target , value );
#endif
		};
		booinline void* compare_exchange_pointer( void* volatile* target , void* exchange , void* comparand )
		{
#ifdef __WINDOWS__
			return ::InterlockedCompareExchangePointer( target , exchange , comparand );
#elif defined( __LINUX__ )
			return __sync_val_compare_and_swap( target , comparand , exchange );
#elif defined( __SOLARIS__ )
			return atomic_cas_ptr( *target , comparand , exchange );
#endif
		};
		booinline void* exchange_pointer(void* volatile* target, void* exchange)
		{
#ifdef __WINDOWS__
			return InterlockedExchangePointer(target, exchange);
#elif defined( __LINUX__ )
			return __sync_lock_test_and_set(target, exchange);
#else
			error
#endif
		};
	};
};
#endif

