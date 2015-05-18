// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "ConstantVariable.h"

namespace constants
{
enum {FRAME_COUNT=4};
enum {AIN_COUNT=8};

extern const int baudrate;

extern const int model_number;
extern const int firmware_number;

extern HardwareSerial& display_serial;

extern const int enc_a_pin;
extern const int enc_b_pin;
extern const int enc_btn_pin;
extern const int enc_btn_int;
extern const int btn_pin;
extern const int btn_int;
extern const int led_pwr_pin;
extern const int standalone_update_period;

extern const int ain_pins[AIN_COUNT];

extern const int ain_min;
extern const int ain_max;
extern const int ain_min_array_default[AIN_COUNT];
extern const int ain_max_array_default[AIN_COUNT];

extern const int percent_min;
extern const int percent_max;

extern const uint8_t ain_dsp_lbl_display_positions[AIN_COUNT];

extern const uint8_t ain_dsp_lbl_width;
extern const uint8_t percent_display_width;

extern const uint8_t ain_dsp_var_display_positions[AIN_COUNT];

extern ConstantString device_name;

extern ConstantString ain_parameter_name;

extern ConstantString execute_standalone_callback_method_name;
extern ConstantString get_leds_powered_method_name;
extern ConstantString get_analog_input_method_name;
extern ConstantString get_analog_inputs_method_name;
extern ConstantString get_analog_min_values_method_name;
extern ConstantString get_analog_max_values_method_name;
extern ConstantString set_as_analog_min_values_method_name;
extern ConstantString set_as_analog_max_values_method_name;

extern ConstantString ain_min_array_name;
extern ConstantString ain_max_array_name;

extern ConstantString frame0_name;
extern ConstantString frame1_name;
extern const ConstantString frame_name_array[FRAME_COUNT];

extern ConstantString ain0_dsp_lbl_string;
extern ConstantString ain1_dsp_lbl_string;
extern ConstantString ain2_dsp_lbl_string;
extern const ConstantString ain_dsp_lbl_strings[AIN_COUNT];
}
#endif
