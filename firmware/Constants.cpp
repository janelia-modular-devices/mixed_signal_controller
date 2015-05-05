// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace constants
{
const int baudrate = 9600;

const int model_number = 1120;
const int firmware_number = 1;

HardwareSerial& display_serial = Serial3;

const int enc_a_pin = 18;
const int enc_b_pin = 2;
const int enc_btn_pin = 19;
const int enc_btn_int = 4;
const int btn_pin = 21;
const int btn_int = 2;
const int led_pwr_pin = 17;
const int standalone_update_period = 300;

const int ain_pins[] = {0,1,2,3,4,5,6,7};

const int ain_min = 0;
const int ain_max = 1023;

const int percent_min = 0;
const int percent_max = 100;

const uint8_t ain_dsp_lbl_display_positions[] = {21,28,35,41,48,55,61,68};

const uint8_t ain_dsp_lbl_width = 2;
const uint8_t percent_display_width = 3;

const uint8_t ain_dsp_var_display_positions[] = {23,30,37,43,50,57,63,70};

CONSTANT_STRING(device_name,"mixed_signal_controller");

CONSTANT_STRING(ain_parameter_name,"ain");

CONSTANT_STRING(execute_standalone_callback_method_name,"executeStandaloneCallback");
CONSTANT_STRING(get_leds_powered_method_name,"getLedsPowered");
CONSTANT_STRING(get_analog_input_method_name,"getAnalogInput");
CONSTANT_STRING(get_analog_inputs_method_name,"getAnalogInputs");

CONSTANT_STRING(frame0_name,"getAnalogInputs0-7");
const ConstantString frame_name_array[] =
  {
    frame0_name,
  };

CONSTANT_STRING(ain0_dsp_lbl_string,"0");
CONSTANT_STRING(ain1_dsp_lbl_string,"1");
CONSTANT_STRING(ain2_dsp_lbl_string,"2");
CONSTANT_STRING(ain3_dsp_lbl_string,"3");
CONSTANT_STRING(ain4_dsp_lbl_string,"4");
CONSTANT_STRING(ain5_dsp_lbl_string,"5");
CONSTANT_STRING(ain6_dsp_lbl_string,"6");
CONSTANT_STRING(ain7_dsp_lbl_string,"7");
const ConstantString ain_dsp_lbl_strings[] =
  {
    ain0_dsp_lbl_string,
    ain1_dsp_lbl_string,
    ain2_dsp_lbl_string,
    ain3_dsp_lbl_string,
    ain4_dsp_lbl_string,
    ain5_dsp_lbl_string,
    ain6_dsp_lbl_string,
    ain7_dsp_lbl_string,
  };
}
