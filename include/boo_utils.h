#ifndef BOO_UTILS_H
#define BOO_UTILS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_types.h>
namespace booldog
{
	namespace utils
	{
		template< class T >
		booinline bool odd( T val )
		{
			return ( val & 1 );
		};
	};
};
#endif
