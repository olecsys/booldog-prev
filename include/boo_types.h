#ifndef BOO_TYPES_H
#define BOO_TYPES_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_platform.h)

#ifdef __WINDOWS__
#define boobegin_struct_pack( bytes ) __pragma( pack( push ) )\
	__pragma( pack( bytes ) )\
	__declspec( align( bytes ) )
#define booend_struct_pack( bytes ) ;\
	__pragma( pack( pop ) )
#else
#define boobegin_struct_pack( bytes )
#define booend_struct_pack( bytes ) __attribute__( ( packed , aligned( bytes ) ) );
#endif

#ifdef __cplusplus
#define booexternc extern "C"
#endif
#ifdef __WINDOWS__
#define booexport booexternc __declspec(dllexport)
#define boointernal
#define booinline __forceinline
#define dlsym( handle , name ) GetProcAddress( handle , name )
#elif defined( __UNIX__ )
#ifdef __LINUX__
#if __GNUC__ >= 4
#define booexport booexternc __attribute__ ((visibility ("default")))
#define boointernal  __attribute__ ((visibility ("hidden")))
#else
#define booexport booexternc __declspec( dllexport )
#define boointernal
#endif
#elif defined( __SOLARIS__ )
#define booexport booexternc __symbolic
#define boointernal __hidden
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
	typedef ::booldog::byte uchar;
	typedef ::booldog::uint16 ushort;
	typedef ::booldog::int32* pint32;
	typedef ::booldog::uint32* puint32;
	typedef bool* pbool;
	typedef ::booldog::byte* puchar;
	typedef ::booldog::int16* pshort;
	typedef ::booldog::uint16* pushort;
	typedef ::booldog::int64* pint64;
	typedef ::booldog::uint64* puint64;
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
#ifdef BOOLDOG_NETWORK
#include <WinSock2.h>
#endif
#include <windows.h>
#endif
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#ifdef __WINDOWS__
#if (_MSC_VER >= 1600 )
#include <stdint.h>
#endif
#else
#include <stdint.h>
#endif
#ifndef SIZE_MAX
#ifdef __SIZE_MAX__
#define SIZE_MAX __SIZE_MAX__
#else
#define SIZE_MAX ((size_t) - 1)
#endif
#endif
namespace booldog
{
	namespace io
	{
		namespace mbs
		{
#ifdef __WINDOWS__
			const char slash = '\\';
#else
			const char slash = '/';
#endif
		};
		namespace wcs
		{
#ifdef __WINDOWS__
			const wchar_t slash = '\\';
#else
			const wchar_t slash = '/';
#endif
		};
	};
#ifdef __WINDOWS__	
	typedef HMODULE module_handle;
#else
	typedef void* module_handle;
#endif
};
#endif
