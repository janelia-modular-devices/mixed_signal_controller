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
const unsigned int baudrate = 9600;

const unsigned int model_number = 1120;

// Use semantic versioning http://semver.org/
const unsigned char firmware_major = 0;
const unsigned char firmware_minor = 1;
const unsigned char firmware_patch = 0;

HardwareSerial & display_serial = Serial3;

const int enc_a_pin = 18;
const int enc_b_pin = 2;
const int enc_btn_pin = 19;
const int enc_btn_int = 4;
const int btn_pin = 21;
const int btn_int = 2;
const int lights_pin = 17;
const int standalone_update_period = 300;

const int ain_pins[] = {7,3,6,2,5,1,4,0,15,11,14,10,13,9,12,8};

const int ain_min = 0;
const int ain_max = 1023;

const int percent_min = 0;
const int percent_max = 100;

const int ain_value_min = 0;
const int ain_value_max = 1023;

const int set_until_update_period = 250;

const int duration_min = 1;
const int duration_max = 30000;

const uint8_t filter_block_ain_count = 4;
const uint8_t filter_update_period = 10;
const boolean use_filters = false;

const uint8_t ain_dsp_lbl_display_positions[] = {21,28,35,41,48,55,61,68,
                                                 21,28,35,41,48,55,61,68};

const uint8_t ain_dsp_lbl_width = 2;
const uint8_t percent_display_width = 3;

const uint8_t ain_dsp_var_display_positions[] = {23,30,37,43,50,57,63,70,
                                                 23,30,37,43,50,57,63,70};

const int io_pins[] = {29,28,27,26,25,24,23,22,
                       37,36,35,34,33,32,31,30,
                       45,44,43,42,41,40,39,38,
                       53,52,51,50,49,48,47,46};

const uint32_t states_array_default[STATE_COUNT] = {0};

const uint8_t channel_dsp_lbl_display_position = 68;
const uint8_t channel_int_var_display_position = 71;
const uint8_t channels_dsp_lbl_display_positions[] = {38,20,58,40};
const uint8_t channels_dsp_var_display_positions[] = {37,29,57,49};
const uint8_t channels_dsp_var_display_width = 8;

const uint8_t state_dsp_lbl_display_position = 68;
const uint8_t state_int_var_display_position = 71;

CONSTANT_STRING(duration_units,"ms");

CONSTANT_STRING(states_name,"states");

CONSTANT_STRING(channel_dsp_lbl_str,"channel");

CONSTANT_STRING(device_name,"mixed_signal_controller");

CONSTANT_STRING(ain_parameter_name,"ain");
CONSTANT_STRING(channels_parameter_name,"channels");
CONSTANT_STRING(state_parameter_name,"state");
CONSTANT_STRING(duration_parameter_name,"duration");
CONSTANT_STRING(ain_value_parameter_name,"ain_value");

CONSTANT_STRING(execute_standalone_callback_method_name,"executeStandaloneCallback");
CONSTANT_STRING(get_leds_powered_method_name,"getLedsPowered");
CONSTANT_STRING(get_analog_inputs_method_name,"getAnalogInputs");
CONSTANT_STRING(get_analog_inputs_filtered_method_name,"getAnalogInputsFiltered");

CONSTANT_STRING(set_channels_on_method_name,"setChannelsOn");
CONSTANT_STRING(set_channels_off_method_name,"setChannelsOff");
CONSTANT_STRING(toggle_channels_method_name,"toggleChannels");
CONSTANT_STRING(toggle_all_channels_method_name,"toggleAllChannels");
CONSTANT_STRING(set_all_channels_on_method_name,"setAllChannelsOn");
CONSTANT_STRING(set_all_channels_off_method_name,"setAllChannelsOff");
CONSTANT_STRING(set_channels_on_all_others_off_method_name,"setChannelsOnAllOthersOff");
CONSTANT_STRING(set_channels_off_all_others_on_method_name,"setChannelsOffAllOthersOn");
CONSTANT_STRING(get_channels_on_method_name,"getChannelsOn");
CONSTANT_STRING(get_channels_off_method_name,"getChannelsOff");
CONSTANT_STRING(get_channel_count_method_name,"getChannelCount");

CONSTANT_STRING(save_state_method_name,"saveState");
CONSTANT_STRING(recall_state_method_name,"recallState");
CONSTANT_STRING(get_saved_states_method_name,"getSavedStates");

CONSTANT_STRING(set_channels_on_until_method_name,"setChannelsOnUntil");
CONSTANT_STRING(set_channels_off_until_method_name,"setChannelsOffUntil");
CONSTANT_STRING(are_all_set_untils_complete_method_name,"areAllSetUntilsComplete");
CONSTANT_STRING(remove_all_set_untils_method_name,"removeAllSetUntils");

CONSTANT_STRING(set_channels_on_for_method_name,"setChannelsOnFor");
CONSTANT_STRING(set_channels_off_for_method_name,"setChannelsOffFor");
CONSTANT_STRING(are_all_set_fors_complete_method_name,"areAllSetForsComplete");
CONSTANT_STRING(remove_all_set_fors_method_name,"removeAllSetFors");

CONSTANT_STRING(frame0_name,"getAnalogInputs00-07");
CONSTANT_STRING(frame1_name,"getAnalogInputs08-15");
CONSTANT_STRING(frame2_name,"toggleChannel");
const ConstantString frame_name_array[] =
  {
    frame0_name,
    frame1_name,
    frame2_name,
    set_all_channels_on_method_name,
    set_all_channels_off_method_name,
    save_state_method_name,
    recall_state_method_name,
  };

CONSTANT_STRING(ain0_dsp_lbl_str,"0");
CONSTANT_STRING(ain1_dsp_lbl_str,"1");
CONSTANT_STRING(ain2_dsp_lbl_str,"2");
CONSTANT_STRING(ain3_dsp_lbl_str,"3");
CONSTANT_STRING(ain4_dsp_lbl_str,"4");
CONSTANT_STRING(ain5_dsp_lbl_str,"5");
CONSTANT_STRING(ain6_dsp_lbl_str,"6");
CONSTANT_STRING(ain7_dsp_lbl_str,"7");
CONSTANT_STRING(ain8_dsp_lbl_str,"8");
CONSTANT_STRING(ain9_dsp_lbl_str,"9");
CONSTANT_STRING(ain10_dsp_lbl_str,"10");
CONSTANT_STRING(ain11_dsp_lbl_str,"11");
CONSTANT_STRING(ain12_dsp_lbl_str,"12");
CONSTANT_STRING(ain13_dsp_lbl_str,"13");
CONSTANT_STRING(ain14_dsp_lbl_str,"14");
CONSTANT_STRING(ain15_dsp_lbl_str,"15");
const ConstantString ain_dsp_lbl_strs[] =
  {
    ain0_dsp_lbl_str,
    ain1_dsp_lbl_str,
    ain2_dsp_lbl_str,
    ain3_dsp_lbl_str,
    ain4_dsp_lbl_str,
    ain5_dsp_lbl_str,
    ain6_dsp_lbl_str,
    ain7_dsp_lbl_str,
    ain8_dsp_lbl_str,
    ain9_dsp_lbl_str,
    ain10_dsp_lbl_str,
    ain11_dsp_lbl_str,
    ain12_dsp_lbl_str,
    ain13_dsp_lbl_str,
    ain14_dsp_lbl_str,
    ain15_dsp_lbl_str,
  };
CONSTANT_STRING(channels0_dsp_lbl_str,"00");
CONSTANT_STRING(channels1_dsp_lbl_str,"15");
CONSTANT_STRING(channels2_dsp_lbl_str,"16");
CONSTANT_STRING(channels3_dsp_lbl_str,"31");
const ConstantString channels_dsp_lbl_strs[] =
  {
    channels0_dsp_lbl_str,
    channels1_dsp_lbl_str,
    channels2_dsp_lbl_str,
    channels3_dsp_lbl_str,
  };
}
