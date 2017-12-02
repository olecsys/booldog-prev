#ifndef BOO_IF_H
#define BOO_IF_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_types.h"
namespace booldog
{
	namespace compile
	{
		template< bool condition >
		class If
		{
		public:
			static booinline bool test()
			{
				return true;
			};
		};
		template<>
		class If< false >
		{
		public:
			static booinline bool test()
			{
				return false;
			};
		};
	};
};
#endif
