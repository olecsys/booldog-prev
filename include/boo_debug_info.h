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
			typedef void (*statement_t)( void* udata , unsigned int& lineid , unsigned int label , int __booline__ );
			typedef unsigned int (*lineid_t)( void* udata , unsigned int label , const char* __boofile__ 
				, const char* __boofunction__ , int __booline__ );
			typedef void (*sleep_t)( void* udata , unsigned int label );
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
			static void statement_empty( void* udata , unsigned int& lineid , unsigned int label , int __booline__ )
			{
				udata = udata;
				lineid = lineid;
				label = label;
				__booline__ = __booline__;
			};
			static void sleep_empty( void* udata , unsigned int label )
			{
				udata = udata;
				label = label;
			};
			const char* file;
			int line;
			unsigned int label;
			::booldog::debug::typedefs::statement_t statement;
			::booldog::debug::typedefs::lineid_t lineid;
			::booldog::debug::typedefs::sleep_t sleep;
			void* udata;
			info( const char* file , int line )
			{
				this->file = file;
				this->line = line;
				this->statement = ::booldog::debug::info::statement_empty;
				this->lineid = ::booldog::debug::info::lineid_empty;
				this->sleep = ::booldog::debug::info::sleep_empty;
			};
			info( const char* file , int line , unsigned int label )
			{
				this->file = file;
				this->line = line;
				this->label = label;
				this->statement = ::booldog::debug::info::statement_empty;
				this->lineid = ::booldog::debug::info::lineid_empty;
				this->sleep = ::booldog::debug::info::sleep_empty;
			};
			info( const char* file , int line , unsigned int label , ::booldog::debug::typedefs::statement_t pstatement 
				, ::booldog::debug::typedefs::lineid_t plineid , ::booldog::debug::typedefs::sleep_t psleep , void* udata )
			{
				this->file = file;
				this->line = line;
				this->label = label;
				this->statement = pstatement;
				this->lineid = plineid;
				this->sleep = psleep;
				this->udata = udata;
			};
			const ::booldog::debug::info& operator = ( const ::booldog::debug::info& ) const
			{
				return *this;
			};
			int version( void )
			{
				return 1;
			};
		};
#define debuginfo_macros ::booldog::debug::info( __FILE__ , __LINE__ )
#define debuginfo_macros_label( label ) ::booldog::debug::info( __FILE__ , __LINE__ , label )
#define debuginfo_macros_statement( label ) \
		{\
			static unsigned int lineid = debuginfo.lineid( debuginfo.udata , label , __FILE__ , __FUNCTION__ , __LINE__ );\
			debuginfo.statement( debuginfo.udata , lineid , label , __LINE__ );\
		}
#define debuginfo_macros_sleep( label ) \
		{\
			debuginfo.sleep( debuginfo.udata , label );\
		}
	};
};
#endif
