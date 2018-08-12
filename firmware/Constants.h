// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "ConstantVariable.h"

namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{SAVED_VARIABLE_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=5};
enum{METHOD_COUNT_MAX=26};

enum{DISPLAY_LABEL_COUNT_MAX=22};
enum{DISPLAY_VARIABLE_COUNT_MAX=20};
enum{INTERACTIVE_VARIABLE_COUNT_MAX=2};
enum {FRAME_COUNT=7};

enum {AIN_COUNT=16};
enum {CHANNEL_COUNT=32};
enum {STATE_COUNT=16};
enum {CHANNELS_DISPLAY_COUNT=4};
enum {INDEXED_SET_UNTILS_COUNT_MAX=1};
enum {FILTER_SAMPLE_COUNT=5};
enum {INDEXED_SET_FORS_COUNT_MAX=8};

extern const unsigned int baudrate;

extern const unsigned int model_number;

extern const unsigned char firmware_major;
extern const unsigned char firmware_minor;
extern const unsigned char firmware_patch;

extern HardwareSerial & display_serial;

extern const int enc_a_pin;
extern const int enc_b_pin;
extern const int enc_btn_pin;
extern const int enc_btn_int;
extern const int btn_pin;
extern const int btn_int;
extern const int lights_pin;
extern const int standalone_update_period;

extern const int ain_pins[AIN_COUNT];

extern const int ain_min;
extern const int ain_max;

extern const int percent_min;
extern const int percent_max;

extern const int ain_value_min;
extern const int ain_value_max;

extern const int set_until_update_period;

extern const int duration_min;
extern const int duration_max;

extern const uint8_t filter_block_ain_count;
extern const uint8_t filter_update_period;
extern const boolean use_filters;

extern const uint8_t ain_dsp_lbl_display_positions[AIN_COUNT];

extern const uint8_t ain_dsp_lbl_width;
extern const uint8_t percent_display_width;

extern const uint8_t ain_dsp_var_display_positions[AIN_COUNT];

extern const int io_pins[CHANNEL_COUNT];

extern const uint32_t states_array_default[STATE_COUNT];

extern const uint8_t channel_dsp_lbl_display_position;
extern const uint8_t channel_int_var_display_position;
extern const uint8_t channels_dsp_lbl_display_positions[CHANNELS_DISPLAY_COUNT];
extern const uint8_t channels_dsp_var_display_positions[CHANNELS_DISPLAY_COUNT];
extern const uint8_t channels_dsp_var_display_width;

extern const uint8_t state_dsp_lbl_display_position;
extern const uint8_t state_int_var_display_position;

extern ConstantString duration_units;

extern ConstantString states_name;

extern ConstantString channel_dsp_lbl_str;

extern ConstantString device_name;

extern ConstantString ain_parameter_name;
extern ConstantString channels_parameter_name;
extern ConstantString state_parameter_name;
extern ConstantString duration_parameter_name;
extern ConstantString ain_value_parameter_name;

extern ConstantString execute_standalone_callback_method_name;
extern ConstantString get_leds_powered_method_name;
extern ConstantString get_analog_inputs_method_name;
extern ConstantString get_analog_inputs_filtered_method_name;

extern ConstantString set_channels_on_method_name;
extern ConstantString set_channels_off_method_name;
extern ConstantString toggle_channels_method_name;
extern ConstantString toggle_all_channels_method_name;
extern ConstantString set_all_channels_on_method_name;
extern ConstantString set_all_channels_off_method_name;
extern ConstantString set_channels_on_all_others_off_method_name;
extern ConstantString set_channels_off_all_others_on_method_name;
extern ConstantString get_channels_on_method_name;
extern ConstantString get_channels_off_method_name;
extern ConstantString get_channel_count_method_name;

extern ConstantString save_state_method_name;
extern ConstantString recall_state_method_name;
extern ConstantString get_saved_states_method_name;

extern ConstantString set_channels_on_until_method_name;
extern ConstantString set_channels_off_until_method_name;
extern ConstantString are_all_set_untils_complete_method_name;
extern ConstantString remove_all_set_untils_method_name;

extern ConstantString set_channels_on_for_method_name;
extern ConstantString set_channels_off_for_method_name;
extern ConstantString are_all_set_fors_complete_method_name;
extern ConstantString remove_all_set_fors_method_name;

extern ConstantString frame0_name;
extern ConstantString frame1_name;
extern ConstantString frame2_name;
extern ConstantString frame5_name;
extern const ConstantString frame_name_array[FRAME_COUNT];

extern ConstantString ain0_dsp_lbl_str;
extern ConstantString ain1_dsp_lbl_str;
extern ConstantString ain2_dsp_lbl_str;
extern ConstantString ain3_dsp_lbl_str;
extern ConstantString ain4_dsp_lbl_str;
extern ConstantString ain5_dsp_lbl_str;
extern ConstantString ain6_dsp_lbl_str;
extern ConstantString ain7_dsp_lbl_str;
extern ConstantString ain8_dsp_lbl_str;
extern ConstantString ain9_dsp_lbl_str;
extern ConstantString ain10_dsp_lbl_str;
extern ConstantString ain11_dsp_lbl_str;
extern ConstantString ain12_dsp_lbl_str;
extern ConstantString ain13_dsp_lbl_str;
extern ConstantString ain14_dsp_lbl_str;
extern ConstantString ain15_dsp_lbl_str;
extern const ConstantString ain_dsp_lbl_strs[AIN_COUNT];
extern ConstantString channels0_dsp_lbl_str;
extern ConstantString channels1_dsp_lbl_str;
extern ConstantString channels2_dsp_lbl_str;
extern ConstantString channels3_dsp_lbl_str;
extern const ConstantString channels_dsp_lbl_strs[CHANNELS_DISPLAY_COUNT];
}
#endif
