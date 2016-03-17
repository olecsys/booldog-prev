#ifndef BOO_DEBUG_INFO_H
#define BOO_DEBUG_INFO_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
namespace booldog
{
	namespace debug
	{
		namespace typedefs
		{
			typedef void (*statement_t)( void* udata , unsigned int& lineid , unsigned int label , const char* __boofile__ 
				, const char* __boofunction__ , int __booline__ );
			typedef unsigned int (*lineid_t)( void* udata , unsigned int label , const char* __boofile__ 
				, const char* __boofunction__ , int __booline__ );
		};
		struct info
		{
			static unsigned int lineid_empty( void* udata , unsigned int label , const char* __boofile__ 
				, const char* __boofunction__ , int __booline__ )
			{
				udata = udata;
				label = label;
				__boofile__ = __boofile__;
				__boofunction__ = __boofunction__;
				__booline__ = __booline__;
				return 0;
			};
			static void statement_empty( void* udata , unsigned int& lineid , unsigned int label , const char* __boofile__ 
				, const char* __boofunction__ , int __booline__ )
			{
				udata = udata;
				lineid = lineid;
				label = label;
				__boofile__ = __boofile__;
				__boofunction__ = __boofunction__;
				__booline__ = __booline__;
			};
			const char* file;
			int line;
			unsigned int label;
			::booldog::debug::typedefs::statement_t statement;
			::booldog::debug::typedefs::lineid_t lineid;
			void* udata;
			info( const char* file , int line )
			{
				this->file = file;
				this->line = line;
				this->statement = ::booldog::debug::info::statement_empty;
				this->lineid = ::booldog::debug::info::lineid_empty;
			};
			info( const char* file , int line , unsigned int label )
			{
				this->file = file;
				this->line = line;
				this->label = label;
				this->statement = ::booldog::debug::info::statement_empty;
				this->lineid = ::booldog::debug::info::lineid_empty;
			};
			info( const char* file , int line , unsigned int label , ::booldog::debug::typedefs::statement_t pstatement 
				, ::booldog::debug::typedefs::lineid_t plineid , void* udata )
			{
				this->file = file;
				this->line = line;
				this->label = label;
				this->statement = pstatement;
				this->lineid = plineid;
				this->udata = udata;
			};
			const ::booldog::debug::info& operator = ( const ::booldog::debug::info& ) const
			{
				return *this;
			};
		};
#define debuginfo_macros ::booldog::debug::info( __FILE__ , __LINE__ )
#define debuginfo_macros_label( label ) ::booldog::debug::info( __FILE__ , __LINE__ , label )
#define debuginfo_macros_statement( label ) \
		{\
			static unsigned int lineid = debuginfo.lineid( debuginfo.udata , label , __FILE__ , __FUNCTION__ , __LINE__ );\
			debuginfo.statement( debuginfo.udata , lineid , label , __FILE__ , __FUNCTION__ , __LINE__ );\
		}
	};
};
#endif
