#ifndef BOO_ERROR_H
#define BOO_ERROR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_types.h>
namespace booldog
{
	namespace enums
	{
		namespace result
		{
			enum booerr_type
			{
				booerr_type_no_error ,
				booerr_type_cannot_alloc_memory , 
				booerr_type_path_has_incorrect_format , 
				booerr_type_not_enough_top_level_folders , 
				booerr_type_string_parameter_is_empty ,
				booerr_type_pointer_parameter_is_null ,
				booerr_type_module_not_found_in_the_list ,
				booerr_type_function_not_found_in_module
			};
		};
	};
};
#endif