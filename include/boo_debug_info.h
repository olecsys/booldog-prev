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
			unsigned int label;
			unsigned char who;
			info( const char* file , int line )
			{
				this->file = file;
				this->line = line;
			};
			info( const char* file , int line , unsigned int label , unsigned char who )
			{
				this->file = file;
				this->line = line;
				this->label = label;
				this->who = who;
			};
			const ::booldog::debug::info& operator = ( const ::booldog::debug::info& ) const
			{
				return *this;
			};
		};
#define debuginfo_macros ::booldog::debug::info( __FILE__ , __LINE__ )
#define debuginfo_macros_label_and_who( label , who ) ::booldog::debug::info( __FILE__ , __LINE__ , label , who )
	};
};
#endif
