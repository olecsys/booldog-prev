#ifndef BOO_STRING_ENUMS_H
#define BOO_STRING_ENUMS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_types.h)
namespace booldog
{
#define BOOLDOG_STRING_CODE_PAGE ::booldog::enums::string::UTF8
	namespace enums
	{
		namespace string
		{
			enum conversion_result
			{
				conversion_result_sourceIllegal = 0 ,           /* source sequence is illegal/malformed */
				conversion_result_OK = 1,           /* conversion successful */
				conversion_result_sourceExhausted = 2,        /* partial character in source, but hit end */
				conversion_result_targetExhausted = 3        /* insuff. room in target for conversion */
			};
			enum code_page
			{
				Unknown = 0 ,
				UTF16 = 1200 ,
				CP1251 = 1251 ,		
				UTF8 = 65001 ,
				UTF32 = 12000
                        };
                }
        }
	namespace global
	{
		namespace string
		{
			static ::booldog::enums::string::code_page default_code_page = BOOLDOG_STRING_CODE_PAGE;
                }
        }
}
#endif
