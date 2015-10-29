#ifndef BOO_TYPES_H
#define BOO_TYPES_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_platform.h>
#ifdef __WINDOWS__
#define modinternal
#define booinline __forceinline
#elif defined( __UNIX__ )
#ifdef __LINUX__
#if __GNUC__ >= 4
#define modinternal  __attribute__ ((visibility ("hidden")))
#else
#define modinternal
#endif
#elif defined( __SOLARIS__ )
#define modinternal __hidden
#endif
#define booinline inline
#endif
namespace booldog
{	
	typedef signed char int8;
	typedef unsigned char uint8;
	typedef short int16;
	typedef unsigned short uint16;
	typedef int int32;
	typedef unsigned int uint32;
	typedef unsigned char byte;
	typedef uint32 pid_t;
#ifdef __WINDOWS__
	typedef __int64 int64;
	typedef unsigned __int64 uint64;
#else
	typedef long long int int64;
	typedef unsigned long long int uint64;
#endif
};
#ifdef __WINDOWS__
#define I64d "%I64d"
#define I64x "%I64x"
#define I64u "%I64u"
#define lld "%I64d"
#define llx "%I64x"
#define llu "%I64u"
#else
#define I64d "%lld"
#define I64x "%llx"
#define I64u "%llu"
#define lld "%lld"
#define llx "%llx"
#define llu "%llu"
#endif
#ifdef __WINDOWS__
#include <WinSock2.h>
#include <windows.h>
#endif
#endif
