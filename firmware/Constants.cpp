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

const int model_number = 1110;
const int firmware_number = 1;

const int cs_pin = 49;
const int in_pin = 48;

HardwareSerial& display_serial = Serial3;

const int enc_a_pin = 18;
const int enc_b_pin = 2;
const int enc_btn_pin = 19;
const int enc_btn_int = 4;
const int btn_pin = 21;
const int btn_int = 2;
const int led_pwr_pin = 17;
const int standalone_update_period = 300;

const uint8_t ic_count = 4;
const uint8_t channel_count = 32;

const uint8_t channel_min = 0;
const uint8_t channel_max = channel_count-1;

const uint32_t duration_min = 1;
const uint32_t duration_max = 0x7FFFFFFF;

const float frequency_min = 0.00001;
const float frequency_max = 500.0;

const uint8_t duty_cycle_min = 1;
const uint8_t duty_cycle_max = 99;
const uint8_t display_duty_cycle_default = 50;

const uint32_t states_array_default[STATE_COUNT] = {0};

const uint8_t dsp_lbl_display_position = 48;
const uint8_t int_var_display_position = 51;

const uint8_t inc_dsp_lbl_display_position = 11;
const uint8_t inc_int_var_display_position = 15;
const uint8_t c_dsp_lbl_display_position = 37;
const uint8_t c_int_var_display_position = 38;

const uint8_t period_dsp_lbl_display_position = 20;
const uint8_t on_dsp_lbl_display_position = 40;
const uint8_t count_dsp_lbl_display_position = 60;
const uint8_t frequency_dsp_lbl_display_position = 29;
const uint8_t pwm_duty_dsp_lbl_display_position = 49;
const uint8_t pwm_dur_dsp_lbl_display_position = 71;

const uint8_t period_int_var_display_position = 24;
const uint8_t on_int_var_display_position = 44;
const uint8_t count_int_var_display_position = 64;
const uint8_t frequency_int_var_display_position = 33;
const uint8_t pwm_duty_int_var_display_position = 53;
const uint8_t pwm_dur_int_var_display_position = 75;

const uint8_t spike_dsp_lbl_display_position = 20;
const uint8_t hold_dsp_lbl_display_position = 31;
const uint8_t spike_duty_dsp_lbl_display_position = 40;
const uint8_t spike_dur_dsp_lbl_display_position = 60;
const uint8_t hold_duty_dsp_lbl_display_position = 51;
const uint8_t hold_dur_dsp_lbl_display_position = 71;

const int display_period_min = 2;
const int display_period_max = 1000;
const int display_period_default = 100;
const int display_on_min = 1;
const int display_on_max = display_period_max-1;
const int display_on_default = display_period_default/2;
const int display_count_min = 1;
const int display_count_max = 32767;
const int display_count_default = 10;
const int display_frequency_min = 1;
const int display_frequency_max = 500;
const int display_frequency_default = 10;
const int display_dur_max = 0x7FFF;
const int display_dur_default = 1000;

const uint8_t spike_duty_int_var_display_position = 44;
const uint8_t spike_dur_int_var_display_position = 64;
const uint8_t hold_duty_int_var_display_position = 55;
const uint8_t hold_dur_int_var_display_position = 75;

const int display_spike_dur_default = 10;
const int display_hold_dur_default = 1000;

CONSTANT_STRING(inc_dsp_lbl_str,"inc");
CONSTANT_STRING(c_dsp_lbl_str,"c");

CONSTANT_STRING(period_dsp_lbl_str,"per");
CONSTANT_STRING(on_dsp_lbl_str,"on");
CONSTANT_STRING(count_dsp_lbl_str,"cnt");
CONSTANT_STRING(frequency_dsp_lbl_str,"frq");

CONSTANT_STRING(spike_dsp_lbl_str,"spike");
CONSTANT_STRING(hold_dsp_lbl_str,"hold");
CONSTANT_STRING(duty_dsp_lbl_str,"dc%");
CONSTANT_STRING(dur_dsp_lbl_str,"dur");

CONSTANT_STRING(device_name,"mixed_signal_controller");

CONSTANT_STRING(duration_units_name,"ms");
CONSTANT_STRING(frequency_units_name,"Hz");
CONSTANT_STRING(duty_cycle_units_name,"%");

CONSTANT_STRING(channels_parameter_name,"channels");
CONSTANT_STRING(channel_parameter_name,"channel");
CONSTANT_STRING(state_parameter_name,"state");
CONSTANT_STRING(delay_parameter_name,"delay");
CONSTANT_STRING(on_duration_parameter_name,"on_duration");
CONSTANT_STRING(period_parameter_name,"period");
CONSTANT_STRING(count_parameter_name,"count");
CONSTANT_STRING(frequency_parameter_name,"frequency");
CONSTANT_STRING(duty_cycle_parameter_name,"duty_cycle");
CONSTANT_STRING(pwm_duration_parameter_name,"pwm_duration");
CONSTANT_STRING(spike_duty_cycle_parameter_name,"spike_duty_cycle");
CONSTANT_STRING(spike_duration_parameter_name,"spike_duration");
CONSTANT_STRING(hold_duty_cycle_parameter_name,"hold_duty_cycle");
CONSTANT_STRING(hold_duration_parameter_name,"hold_duration");
CONSTANT_STRING(pulse_wave_index_parameter_name,"pulse_wave_index");

CONSTANT_STRING(execute_standalone_callback_method_name,"executeStandaloneCallback");
CONSTANT_STRING(get_leds_powered_method_name,"getLedsPowered");
CONSTANT_STRING(set_channel_on_method_name,"setChannelOn");
CONSTANT_STRING(set_channel_off_method_name,"setChannelOff");
CONSTANT_STRING(set_channels_on_method_name,"setChannelsOn");
CONSTANT_STRING(set_channels_off_method_name,"setChannelsOff");
CONSTANT_STRING(toggle_channel_method_name,"toggleChannel");
CONSTANT_STRING(toggle_channels_method_name,"toggleChannels");
CONSTANT_STRING(toggle_all_channels_method_name,"toggleAllChannels");
CONSTANT_STRING(set_all_channels_on_method_name,"setAllChannelsOn");
CONSTANT_STRING(set_all_channels_off_method_name,"setAllChannelsOff");
CONSTANT_STRING(set_channel_on_all_others_off_method_name,"setChannelOnAllOthersOff");
CONSTANT_STRING(set_channel_off_all_others_on_method_name,"setChannelOffAllOthersOn");
CONSTANT_STRING(set_channels_on_all_others_off_method_name,"setChannelsOnAllOthersOff");
CONSTANT_STRING(set_channels_off_all_others_on_method_name,"setChannelsOffAllOthersOn");
CONSTANT_STRING(get_channels_on_method_name,"getChannelsOn");
CONSTANT_STRING(get_channels_off_method_name,"getChannelsOff");
CONSTANT_STRING(get_channel_count_method_name,"getChannelCount");
CONSTANT_STRING(save_state_method_name,"saveState");
CONSTANT_STRING(recall_state_method_name,"recallState");
CONSTANT_STRING(get_saved_states_method_name,"getSavedStates");
CONSTANT_STRING(add_pulse_centered_method_name,"addPulseCentered");
CONSTANT_STRING(add_pwm_period_on_duration_method_name,"addPwmPeriodOnDuration");
CONSTANT_STRING(add_pwm_frequency_duty_cycle_method_name,"addPwmFrequencyDutyCycle");
CONSTANT_STRING(add_spike_and_hold_method_name,"addSpikeAndHold");
CONSTANT_STRING(stop_all_pulses_method_name,"stopAllPulses");
CONSTANT_STRING(start_pwm_period_on_duration_method_name,"startPwmPeriodOnDuration");
CONSTANT_STRING(start_pwm_frequency_duty_cycle_method_name,"startPwmFrequencyDutyCycle");
CONSTANT_STRING(start_spike_and_hold_method_name,"startSpikeAndHold");
CONSTANT_STRING(stop_pulse_wave_method_name,"stopPulseWave");

CONSTANT_STRING(pwm_state_method_name,"pwm");
CONSTANT_STRING(spike_hold_state_method_name,"spikeHold");
CONSTANT_STRING(states_name,"states");
const ConstantString frame_name_array[] =
  {
    toggle_channel_method_name,
    set_all_channels_off_method_name,
    set_all_channels_on_method_name,
    save_state_method_name,
    recall_state_method_name,
    pwm_state_method_name,
    spike_hold_state_method_name,
  };
}
