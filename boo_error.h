#ifndef BOO_ERROR_H
#define BOO_ERROR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_platform.h"
namespace booldog
{
	namespace enums
	{
		namespace result
		{
			typedef enum
			{
				booerr_type_no_error ,
				booerr_type_cannot_alloc_memory , 
				booerr_type_path_has_incorrect_format , 
				booerr_type_not_enough_top_level_folders , 
				booerr_type_string_parameter_is_empty ,
				booerr_type_pointer_parameter_is_null ,
				booerr_type_module_not_found_in_the_list ,
				booerr_type_function_not_found_in_module ,
				booerr_type_json_expecting_string_in_object_name , 
				booerr_type_json_expecting_name_separator ,
				booerr_type_json_expecting_value_separator ,
				booerr_type_json_expecting_end_of_string ,
				booerr_type_json_unexpected_symbol ,
				booerr_type_json_unexpected_end_of_string ,
				booerr_type_json_unexpected_value_separator ,
				booerr_type_json_expecting_null ,
				booerr_type_json_expecting_true ,
				booerr_type_json_expecting_false ,
				booerr_type_json_unexpected_escaped_symbol ,
				booerr_type_json_expecting_hex_symbol ,
				booerr_type_json_cannot_convert_from_utf16_to_utf8 ,
				booerr_type_json_expecting_decimal_point_or_exponent_part_in_number ,
				booerr_type_json_unexpected_minus_in_number ,
				booerr_type_json_expecting_digit_after_minus ,
				booerr_type_json_unexpected_second_decimal_point_in_number ,
				booerr_type_json_expecting_digit_after_decimal_point ,
				booerr_type_json_unexpected_decimal_point_in_number ,
				booerr_type_json_unexpected_second_exponent_part_symbol_in_number ,
				booerr_type_json_expecting_digit_after_exponent_part_symbol ,
				booerr_type_json_unexpected_plus_in_number ,
				booerr_type_json_not_utf8_symbol , 
				booerr_type_conversion_result_source_illegal ,
				booerr_type_conversion_result_source_exhausted ,
				booerr_type_unknown_wchar_t_size ,
				booerr_type_handle_is_executable ,
				booerr_type_insufficient_memory ,
				booerr_type_object_is_already_initialized , 
				booerr_type_base64_decoded_length_is_equal_0 ,
				booerr_type_base64_incorrect_encoded_length ,
				booerr_type_base64_decoded_data_pointer_is_NULL ,
				booerr_type_base64_decoded_data_pointer_size_is_equal_0 ,
				booerr_type_base64_encoded_data_pointer_size_is_equal_0 , 
				booerr_type_sqlite3_error ,
				booerr_type_json_object_has_not_node , 
				booerr_type_json_it_is_root_object ,
				booerr_type_json_parent_is_not_object ,
				booerr_type_module_is_deinitialized_and_must_be_unloaded ,
				booerr_type_file_does_not_exist,
				booerr_type_method_is_not_implemented_yet,
				booerr_type_file_is_not_character_device,
				booerr_type_file_is_not_video_capture_device,
				booerr_type_video_capture_device_does_not_support_neither_streaming_nor_io,
				booerr_type_map_failed,
				booerr_type_video_format_is_not_supported,
				booerr_type_video_capture_device_has_not_frame_yet,
				booerr_type_windows_has_not_fifo,
				booerr_type_select_except,
				booerr_type_incorrect_packet_size,
				booerr_type_json_parent_is_not_array,
				booerr_type_all_frames_locked
			} booerr_type;
		}
	}
}
#endif