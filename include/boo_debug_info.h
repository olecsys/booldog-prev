#ifndef BOO_DEBUG_INFO_H
#define BOO_DEBUG_INFO_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
namespace booldog
{
	namespace debug
	{
		struct info
		{
			const char* file;
			int line;
			info( const char* file , int line )
			{
				this->file = file;
				this->line = line;
			};
		};
	};
};
#endif
