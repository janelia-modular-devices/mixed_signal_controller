// ----------------------------------------------------------------------------
// Controller.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Controller.h"

Controller::Controller() :
  PowerSwitch(constants::cs_pin,constants::in_pin),
  standalone_interface_(Standalone::StandaloneInterface(constants::display_serial,
                                                        constants::enc_a_pin,
                                                        constants::enc_b_pin,
                                                        constants::enc_btn_pin,
                                                        constants::enc_btn_int,
                                                        constants::btn_pin,
                                                        constants::btn_int,
                                                        constants::led_pwr_pin,
                                                        constants::standalone_update_period))
{
}

void Controller::setup()
{
  PowerSwitch::setup(constants::ic_count);
  EventController::event_controller.setup();

  // Pin Setup

  // Device Info
  modular_device.setName(constants::device_name);
  modular_device.setModelNumber(constants::model_number);
  modular_device.setFirmwareNumber(constants::firmware_number);

  // Saved Variables
  modular_device.createSavedVariable(constants::states_name,constants::states_array_default,constants::STATE_COUNT);

  // Parameters
  ModularDevice::Parameter& channel_parameter = modular_device.createParameter(constants::channel_parameter_name);
  channel_parameter.setRange(constants::channel_min,constants::channel_max);

  ModularDevice::Parameter& channels_parameter = modular_device.createParameter(constants::channels_parameter_name);
  channels_parameter.setTypeArray();
  channels_parameter.setRange(constants::channel_min,constants::channel_max);

  ModularDevice::Parameter& state_parameter = modular_device.createParameter(constants::state_parameter_name);
  state_parameter.setRange(0,constants::STATE_COUNT-1);

  ModularDevice::Parameter& delay_parameter = modular_device.createParameter(constants::delay_parameter_name);
  delay_parameter.setRange(constants::duration_min,constants::duration_max);
  delay_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter& on_duration_parameter = modular_device.createParameter(constants::on_duration_parameter_name);
  on_duration_parameter.setRange(constants::duration_min,constants::duration_max);
  on_duration_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter& period_parameter = modular_device.createParameter(constants::period_parameter_name);
  period_parameter.setRange(constants::duration_min,constants::duration_max);
  period_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter& count_parameter = modular_device.createParameter(constants::count_parameter_name);
  count_parameter.setRange(constants::duration_min,constants::duration_max);

  ModularDevice::Parameter& frequency_parameter = modular_device.createParameter(constants::frequency_parameter_name);
  frequency_parameter.setRange(constants::frequency_min,constants::frequency_max);
  frequency_parameter.setUnits(constants::frequency_units_name);

  ModularDevice::Parameter& duty_cycle_parameter = modular_device.createParameter(constants::duty_cycle_parameter_name);
  duty_cycle_parameter.setRange(constants::duty_cycle_min,constants::duty_cycle_max);
  duty_cycle_parameter.setUnits(constants::duty_cycle_units_name);

  ModularDevice::Parameter& pwm_duration_parameter = modular_device.createParameter(constants::pwm_duration_parameter_name);
  pwm_duration_parameter.setRange(constants::duration_min,constants::duration_max);
  pwm_duration_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter& spike_duty_cycle_parameter = modular_device.createParameter(constants::spike_duty_cycle_parameter_name);
  spike_duty_cycle_parameter.setRange(constants::duty_cycle_min,constants::duty_cycle_max);
  spike_duty_cycle_parameter.setUnits(constants::duty_cycle_units_name);

  ModularDevice::Parameter& spike_duration_parameter = modular_device.createParameter(constants::spike_duration_parameter_name);
  spike_duration_parameter.setRange(constants::duration_min,constants::duration_max);
  spike_duration_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter& hold_duty_cycle_parameter = modular_device.createParameter(constants::hold_duty_cycle_parameter_name);
  hold_duty_cycle_parameter.setRange(constants::duty_cycle_min,constants::duty_cycle_max);
  hold_duty_cycle_parameter.setUnits(constants::duty_cycle_units_name);

  ModularDevice::Parameter& hold_duration_parameter = modular_device.createParameter(constants::hold_duration_parameter_name);
  hold_duration_parameter.setRange(constants::duration_min,constants::duration_max);
  hold_duration_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter& pulse_wave_index_parameter = modular_device.createParameter(constants::pulse_wave_index_parameter_name);
  pulse_wave_index_parameter.setRange((int)0,(constants::INDEXED_PULSES_COUNT_MAX-1));

  // Methods
  ModularDevice::Method& execute_standalone_callback_method = modular_device.createMethod(constants::execute_standalone_callback_method_name);
  execute_standalone_callback_method.attachCallback(callbacks::executeStandaloneCallbackCallback);

  ModularDevice::Method& get_leds_powered_method = modular_device.createMethod(constants::get_leds_powered_method_name);
  get_leds_powered_method.attachCallback(callbacks::getLedsPoweredCallback);

  ModularDevice::Method& set_channel_on_method = modular_device.createMethod(constants::set_channel_on_method_name);
  set_channel_on_method.attachCallback(callbacks::setChannelOnCallback);
  set_channel_on_method.addParameter(channel_parameter);

  ModularDevice::Method& set_channel_off_method = modular_device.createMethod(constants::set_channel_off_method_name);
  set_channel_off_method.attachCallback(callbacks::setChannelOffCallback);
  set_channel_off_method.addParameter(channel_parameter);

  ModularDevice::Method& set_channels_on_method = modular_device.createMethod(constants::set_channels_on_method_name);
  set_channels_on_method.attachCallback(callbacks::setChannelsOnCallback);
  set_channels_on_method.addParameter(channels_parameter);

  ModularDevice::Method& set_channels_off_method = modular_device.createMethod(constants::set_channels_off_method_name);
  set_channels_off_method.attachCallback(callbacks::setChannelsOffCallback);
  set_channels_off_method.addParameter(channels_parameter);

  ModularDevice::Method& toggle_channel_method = modular_device.createMethod(constants::toggle_channel_method_name);
  toggle_channel_method.attachCallback(callbacks::toggleChannelCallback);
  toggle_channel_method.addParameter(channel_parameter);

  ModularDevice::Method& toggle_channels_method = modular_device.createMethod(constants::toggle_channels_method_name);
  toggle_channels_method.attachCallback(callbacks::toggleChannelsCallback);
  toggle_channels_method.addParameter(channels_parameter);

  ModularDevice::Method& toggle_all_channels_method = modular_device.createMethod(constants::toggle_all_channels_method_name);
  toggle_all_channels_method.attachCallback(callbacks::toggleAllChannelsCallback);

  ModularDevice::Method& set_all_channels_on_method = modular_device.createMethod(constants::set_all_channels_on_method_name);
  set_all_channels_on_method.attachCallback(callbacks::setAllChannelsOnCallback);

  ModularDevice::Method& set_all_channels_off_method = modular_device.createMethod(constants::set_all_channels_off_method_name);
  set_all_channels_off_method.attachCallback(callbacks::setAllChannelsOffCallback);

  ModularDevice::Method& set_channel_on_all_others_off_method = modular_device.createMethod(constants::set_channel_on_all_others_off_method_name);
  set_channel_on_all_others_off_method.attachCallback(callbacks::setChannelOnAllOthersOffCallback);
  set_channel_on_all_others_off_method.addParameter(channel_parameter);

  ModularDevice::Method& set_channel_off_all_others_on_method = modular_device.createMethod(constants::set_channel_off_all_others_on_method_name);
  set_channel_off_all_others_on_method.attachCallback(callbacks::setChannelOffAllOthersOnCallback);
  set_channel_off_all_others_on_method.addParameter(channel_parameter);

  ModularDevice::Method& set_channels_on_all_others_off_method = modular_device.createMethod(constants::set_channels_on_all_others_off_method_name);
  set_channels_on_all_others_off_method.attachCallback(callbacks::setChannelsOnAllOthersOffCallback);
  set_channels_on_all_others_off_method.addParameter(channels_parameter);

  ModularDevice::Method& set_channels_off_all_others_on_method = modular_device.createMethod(constants::set_channels_off_all_others_on_method_name);
  set_channels_off_all_others_on_method.attachCallback(callbacks::setChannelsOffAllOthersOnCallback);
  set_channels_off_all_others_on_method.addParameter(channels_parameter);

  ModularDevice::Method& get_channels_on_method = modular_device.createMethod(constants::get_channels_on_method_name);
  get_channels_on_method.attachCallback(callbacks::getChannelsOnCallback);

  ModularDevice::Method& get_channels_off_method = modular_device.createMethod(constants::get_channels_off_method_name);
  get_channels_off_method.attachCallback(callbacks::getChannelsOffCallback);

  ModularDevice::Method& get_channel_count_method = modular_device.createMethod(constants::get_channel_count_method_name);
  get_channel_count_method.attachCallback(callbacks::getChannelCountCallback);

  ModularDevice::Method& save_state_method = modular_device.createMethod(constants::save_state_method_name);
  save_state_method.attachCallback(callbacks::saveStateCallback);
  save_state_method.addParameter(state_parameter);

  ModularDevice::Method& recall_state_method = modular_device.createMethod(constants::recall_state_method_name);
  recall_state_method.attachCallback(callbacks::recallStateCallback);
  recall_state_method.addParameter(state_parameter);

  ModularDevice::Method& get_saved_states_method = modular_device.createMethod(constants::get_saved_states_method_name);
  get_saved_states_method.attachCallback(callbacks::getSavedStatesCallback);

  ModularDevice::Method& add_pulse_centered_method = modular_device.createMethod(constants::add_pulse_centered_method_name);
  add_pulse_centered_method.attachCallback(callbacks::addPulseCenteredCallback);
  add_pulse_centered_method.addParameter(channels_parameter);
  add_pulse_centered_method.addParameter(delay_parameter);
  add_pulse_centered_method.addParameter(on_duration_parameter);

  ModularDevice::Method& add_pwm_period_on_duration_method = modular_device.createMethod(constants::add_pwm_period_on_duration_method_name);
  add_pwm_period_on_duration_method.attachCallback(callbacks::addPwmPeriodOnDurationCallback);
  add_pwm_period_on_duration_method.addParameter(channels_parameter);
  add_pwm_period_on_duration_method.addParameter(delay_parameter);
  add_pwm_period_on_duration_method.addParameter(period_parameter);
  add_pwm_period_on_duration_method.addParameter(on_duration_parameter);
  add_pwm_period_on_duration_method.addParameter(count_parameter);

  ModularDevice::Method& add_pwm_frequency_duty_cycle_method = modular_device.createMethod(constants::add_pwm_frequency_duty_cycle_method_name);
  add_pwm_frequency_duty_cycle_method.attachCallback(callbacks::addPwmFrequencyDutyCycleCallback);
  add_pwm_frequency_duty_cycle_method.addParameter(channels_parameter);
  add_pwm_frequency_duty_cycle_method.addParameter(delay_parameter);
  add_pwm_frequency_duty_cycle_method.addParameter(frequency_parameter);
  add_pwm_frequency_duty_cycle_method.addParameter(duty_cycle_parameter);
  add_pwm_frequency_duty_cycle_method.addParameter(pwm_duration_parameter);

  ModularDevice::Method& add_spike_and_hold_method = modular_device.createMethod(constants::add_spike_and_hold_method_name);
  add_spike_and_hold_method.attachCallback(callbacks::addSpikeAndHoldCallback);
  add_spike_and_hold_method.addParameter(channels_parameter);
  add_spike_and_hold_method.addParameter(delay_parameter);
  add_spike_and_hold_method.addParameter(spike_duty_cycle_parameter);
  add_spike_and_hold_method.addParameter(spike_duration_parameter);
  add_spike_and_hold_method.addParameter(hold_duty_cycle_parameter);
  add_spike_and_hold_method.addParameter(hold_duration_parameter);

  ModularDevice::Method& stop_all_pulses_method = modular_device.createMethod(constants::stop_all_pulses_method_name);
  stop_all_pulses_method.attachCallback(callbacks::stopAllPulsesCallback);

  ModularDevice::Method& start_pwm_period_on_duration_method = modular_device.createMethod(constants::start_pwm_period_on_duration_method_name);
  start_pwm_period_on_duration_method.attachCallback(callbacks::startPwmPeriodOnDurationCallback);
  start_pwm_period_on_duration_method.addParameter(channels_parameter);
  start_pwm_period_on_duration_method.addParameter(delay_parameter);
  start_pwm_period_on_duration_method.addParameter(period_parameter);
  start_pwm_period_on_duration_method.addParameter(on_duration_parameter);

  ModularDevice::Method& start_pwm_frequency_duty_cycle_method = modular_device.createMethod(constants::start_pwm_frequency_duty_cycle_method_name);
  start_pwm_frequency_duty_cycle_method.attachCallback(callbacks::startPwmFrequencyDutyCycleCallback);
  start_pwm_frequency_duty_cycle_method.addParameter(channels_parameter);
  start_pwm_frequency_duty_cycle_method.addParameter(delay_parameter);
  start_pwm_frequency_duty_cycle_method.addParameter(frequency_parameter);
  start_pwm_frequency_duty_cycle_method.addParameter(duty_cycle_parameter);

  ModularDevice::Method& start_spike_and_hold_method = modular_device.createMethod(constants::start_spike_and_hold_method_name);
  start_spike_and_hold_method.attachCallback(callbacks::startSpikeAndHoldCallback);
  start_spike_and_hold_method.addParameter(channels_parameter);
  start_spike_and_hold_method.addParameter(delay_parameter);
  start_spike_and_hold_method.addParameter(spike_duty_cycle_parameter);
  start_spike_and_hold_method.addParameter(spike_duration_parameter);
  start_spike_and_hold_method.addParameter(hold_duty_cycle_parameter);

  ModularDevice::Method& stop_pulse_wave_method = modular_device.createMethod(constants::stop_pulse_wave_method_name);
  stop_pulse_wave_method.attachCallback(callbacks::stopPulseWaveCallback);
  stop_pulse_wave_method.addParameter(pulse_wave_index_parameter);

  // Start ModularDevice Server
  modular_device.startServer(constants::baudrate);

  // Standalone Interface
  standalone_interface_.setup(constants::frame_name_array,constants::FRAME_COUNT);

  // Display Labels
  Standalone::DisplayLabel& channel_dsp_lbl = standalone_interface_.createDisplayLabel();
  channel_dsp_lbl.setDisplayPosition(constants::dsp_lbl_display_position);
  channel_dsp_lbl.setConstantString(constants::channel_parameter_name);
  channel_dsp_lbl.setRightJustify();

  Standalone::DisplayLabel& state_dsp_lbl = standalone_interface_.createDisplayLabel();
  state_dsp_lbl.setDisplayPosition(constants::dsp_lbl_display_position);
  state_dsp_lbl.setConstantString(constants::state_parameter_name);
  state_dsp_lbl.setRightJustify();

  Standalone::DisplayLabel& inc_dsp_lbl = standalone_interface_.createDisplayLabel();
  inc_dsp_lbl.setDisplayPosition(constants::inc_dsp_lbl_display_position);
  inc_dsp_lbl.setConstantString(constants::inc_dsp_lbl_str);

  Standalone::DisplayLabel& c_dsp_lbl = standalone_interface_.createDisplayLabel();
  c_dsp_lbl.setDisplayPosition(constants::c_dsp_lbl_display_position);
  c_dsp_lbl.setConstantString(constants::c_dsp_lbl_str);

  Standalone::DisplayLabel& period_dsp_lbl = standalone_interface_.createDisplayLabel();
  period_dsp_lbl.setDisplayPosition(constants::period_dsp_lbl_display_position);
  period_dsp_lbl.setConstantString(constants::period_dsp_lbl_str);

  Standalone::DisplayLabel& on_dsp_lbl = standalone_interface_.createDisplayLabel();
  on_dsp_lbl.setDisplayPosition(constants::on_dsp_lbl_display_position);
  on_dsp_lbl.setConstantString(constants::on_dsp_lbl_str);

  Standalone::DisplayLabel& count_dsp_lbl = standalone_interface_.createDisplayLabel();
  count_dsp_lbl.setDisplayPosition(constants::count_dsp_lbl_display_position);
  count_dsp_lbl.setConstantString(constants::count_dsp_lbl_str);

  Standalone::DisplayLabel& frequency_dsp_lbl = standalone_interface_.createDisplayLabel();
  frequency_dsp_lbl.setDisplayPosition(constants::frequency_dsp_lbl_display_position);
  frequency_dsp_lbl.setConstantString(constants::frequency_dsp_lbl_str);

  Standalone::DisplayLabel& pwm_duty_dsp_lbl = standalone_interface_.createDisplayLabel();
  pwm_duty_dsp_lbl.setDisplayPosition(constants::pwm_duty_dsp_lbl_display_position);
  pwm_duty_dsp_lbl.setConstantString(constants::duty_dsp_lbl_str);

  Standalone::DisplayLabel& pwm_dur_dsp_lbl = standalone_interface_.createDisplayLabel();
  pwm_dur_dsp_lbl.setDisplayPosition(constants::pwm_dur_dsp_lbl_display_position);
  pwm_dur_dsp_lbl.setConstantString(constants::dur_dsp_lbl_str);

  Standalone::DisplayLabel& spike_dsp_lbl = standalone_interface_.createDisplayLabel();
  spike_dsp_lbl.setDisplayPosition(constants::spike_dsp_lbl_display_position);
  spike_dsp_lbl.setConstantString(constants::spike_dsp_lbl_str);

  Standalone::DisplayLabel& hold_dsp_lbl = standalone_interface_.createDisplayLabel();
  hold_dsp_lbl.setDisplayPosition(constants::hold_dsp_lbl_display_position);
  hold_dsp_lbl.setConstantString(constants::hold_dsp_lbl_str);

  Standalone::DisplayLabel& spike_duty_dsp_lbl = standalone_interface_.createDisplayLabel();
  spike_duty_dsp_lbl.setDisplayPosition(constants::spike_duty_dsp_lbl_display_position);
  spike_duty_dsp_lbl.setConstantString(constants::duty_dsp_lbl_str);

  Standalone::DisplayLabel& spike_dur_dsp_lbl = standalone_interface_.createDisplayLabel();
  spike_dur_dsp_lbl.setDisplayPosition(constants::spike_dur_dsp_lbl_display_position);
  spike_dur_dsp_lbl.setConstantString(constants::dur_dsp_lbl_str);

  Standalone::DisplayLabel& hold_duty_dsp_lbl = standalone_interface_.createDisplayLabel();
  hold_duty_dsp_lbl.setDisplayPosition(constants::hold_duty_dsp_lbl_display_position);
  hold_duty_dsp_lbl.setConstantString(constants::duty_dsp_lbl_str);

  Standalone::DisplayLabel& hold_dur_dsp_lbl = standalone_interface_.createDisplayLabel();
  hold_dur_dsp_lbl.setDisplayPosition(constants::hold_dur_dsp_lbl_display_position);
  hold_dur_dsp_lbl.setConstantString(constants::dur_dsp_lbl_str);

  // Display Variables

  // Interactive Variables
  channel_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  channel_int_var_ptr_->setDisplayPosition(constants::int_var_display_position);
  channel_int_var_ptr_->setRange(constants::channel_min,constants::channel_max);
  channel_int_var_ptr_->trimDisplayWidthUsingRange();

  state_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  state_int_var_ptr_->setDisplayPosition(constants::int_var_display_position);
  state_int_var_ptr_->setRange(0,constants::STATE_COUNT-1);
  state_int_var_ptr_->trimDisplayWidthUsingRange();

  Standalone::InteractiveVariable& inc_int_var = standalone_interface_.createIncrementVariable();
  inc_int_var.setDisplayPosition(constants::inc_int_var_display_position);

  c_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  c_int_var_ptr_->setDisplayPosition(constants::c_int_var_display_position);
  c_int_var_ptr_->setRange(constants::channel_min,constants::channel_max);
  c_int_var_ptr_->trimDisplayWidthUsingRange();

  period_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  period_int_var_ptr_->setDisplayPosition(constants::period_int_var_display_position);
  period_int_var_ptr_->setRange(constants::display_period_min,constants::display_period_max);
  period_int_var_ptr_->trimDisplayWidthUsingRange();
  period_int_var_ptr_->setValue(constants::display_period_default);
  period_int_var_ptr_->attachUpdateCallback(callbacks::periodUpdateCallback);

  on_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  on_int_var_ptr_->setDisplayPosition(constants::on_int_var_display_position);
  on_int_var_ptr_->setRange(constants::display_on_min,constants::display_on_max);
  on_int_var_ptr_->trimDisplayWidthUsingRange();
  on_int_var_ptr_->setValue(constants::display_on_default);
  on_int_var_ptr_->attachUpdateCallback(callbacks::onUpdateCallback);

  count_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  count_int_var_ptr_->setDisplayPosition(constants::count_int_var_display_position);
  count_int_var_ptr_->setRange(constants::display_count_min,constants::display_dur_max/constants::display_period_default);
  count_int_var_ptr_->trimDisplayWidthUsingRange();
  count_int_var_ptr_->setValue(constants::display_count_default);
  count_int_var_ptr_->attachUpdateCallback(callbacks::countUpdateCallback);

  frequency_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  frequency_int_var_ptr_->setDisplayPosition(constants::frequency_int_var_display_position);
  frequency_int_var_ptr_->setRange(constants::display_frequency_min,constants::display_frequency_max);
  frequency_int_var_ptr_->trimDisplayWidthUsingRange();
  frequency_int_var_ptr_->setValue(constants::display_frequency_default);
  frequency_int_var_ptr_->attachUpdateCallback(callbacks::frequencyUpdateCallback);

  pwm_duty_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  pwm_duty_int_var_ptr_->setDisplayPosition(constants::pwm_duty_int_var_display_position);
  pwm_duty_int_var_ptr_->setRange(constants::duty_cycle_min,constants::duty_cycle_max);
  pwm_duty_int_var_ptr_->trimDisplayWidthUsingRange();
  pwm_duty_int_var_ptr_->setValue(constants::display_duty_cycle_default);
  pwm_duty_int_var_ptr_->attachUpdateCallback(callbacks::pwmDutyUpdateCallback);

  pwm_dur_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  pwm_dur_int_var_ptr_->setDisplayPosition(constants::pwm_dur_int_var_display_position);
  pwm_dur_int_var_ptr_->setRange(constants::duration_min,constants::display_dur_max);
  pwm_dur_int_var_ptr_->trimDisplayWidthUsingRange();
  pwm_dur_int_var_ptr_->setValue(constants::display_dur_default);
  pwm_dur_int_var_ptr_->attachUpdateCallback(callbacks::pwmDurUpdateCallback);

  spike_duty_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  spike_duty_int_var_ptr_->setDisplayPosition(constants::spike_duty_int_var_display_position);
  spike_duty_int_var_ptr_->setRange(constants::duty_cycle_min,constants::duty_cycle_max);
  spike_duty_int_var_ptr_->trimDisplayWidthUsingRange();
  spike_duty_int_var_ptr_->setValue(constants::display_duty_cycle_default);

  spike_dur_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  spike_dur_int_var_ptr_->setDisplayPosition(constants::spike_dur_int_var_display_position);
  spike_dur_int_var_ptr_->setRange(constants::duration_min,constants::display_dur_max);
  spike_dur_int_var_ptr_->trimDisplayWidthUsingRange();
  spike_dur_int_var_ptr_->setValue(constants::display_spike_dur_default);

  hold_duty_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  hold_duty_int_var_ptr_->setDisplayPosition(constants::hold_duty_int_var_display_position);
  hold_duty_int_var_ptr_->setRange(constants::duty_cycle_min,constants::duty_cycle_max);
  hold_duty_int_var_ptr_->trimDisplayWidthUsingRange();
  hold_duty_int_var_ptr_->setValue(constants::display_duty_cycle_default/2);

  hold_dur_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  hold_dur_int_var_ptr_->setDisplayPosition(constants::hold_dur_int_var_display_position);
  hold_dur_int_var_ptr_->setRange(constants::duration_min,constants::display_dur_max);
  hold_dur_int_var_ptr_->trimDisplayWidthUsingRange();
  hold_dur_int_var_ptr_->setValue(constants::display_hold_dur_default);

  // All Frames

  // Frame 0
  int frame = 0;
  channel_dsp_lbl.addToFrame(frame);
  channel_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::toggleChannelStandaloneCallback,frame);

  // Frame 1
  frame = 1;
  standalone_interface_.attachCallbackToFrame(callbacks::setAllChannelsOffCallback,frame);

  // Frame 2
  frame = 2;
  standalone_interface_.attachCallbackToFrame(callbacks::setAllChannelsOnCallback,frame);

  // Frame 3
  frame = 3;
  state_dsp_lbl.addToFrame(frame);
  state_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::saveStateStandaloneCallback,frame);

  // Frame 4
  frame = 4;
  state_dsp_lbl.addToFrame(frame);
  state_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::recallStateStandaloneCallback,frame);

  // Frame 5
  frame = 5;
  inc_dsp_lbl.addToFrame(frame);
  inc_int_var.addToFrame(frame);
  c_dsp_lbl.addToFrame(frame);
  c_int_var_ptr_->addToFrame(frame);
  period_dsp_lbl.addToFrame(frame);
  on_dsp_lbl.addToFrame(frame);
  count_dsp_lbl.addToFrame(frame);
  frequency_dsp_lbl.addToFrame(frame);
  pwm_duty_dsp_lbl.addToFrame(frame);
  pwm_dur_dsp_lbl.addToFrame(frame);
  period_int_var_ptr_->addToFrame(frame);
  on_int_var_ptr_->addToFrame(frame);
  count_int_var_ptr_->addToFrame(frame);
  frequency_int_var_ptr_->addToFrame(frame);
  pwm_duty_int_var_ptr_->addToFrame(frame);
  pwm_dur_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::pwmStandaloneCallback,frame);

  // Frame 6
  frame = 6;
  inc_dsp_lbl.addToFrame(frame);
  inc_int_var.addToFrame(frame);
  c_dsp_lbl.addToFrame(frame);
  c_int_var_ptr_->addToFrame(frame);
  spike_dsp_lbl.addToFrame(frame);
  hold_dsp_lbl.addToFrame(frame);
  spike_duty_dsp_lbl.addToFrame(frame);
  spike_dur_dsp_lbl.addToFrame(frame);
  hold_duty_dsp_lbl.addToFrame(frame);
  hold_dur_dsp_lbl.addToFrame(frame);
  spike_duty_int_var_ptr_->addToFrame(frame);
  spike_dur_int_var_ptr_->addToFrame(frame);
  hold_duty_int_var_ptr_->addToFrame(frame);
  hold_dur_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::spikeHoldStandaloneCallback,frame);

  // Enable Standalone Interface
  standalone_interface_.enable();
}

void Controller::update()
{
  modular_device.handleServerRequests();
  standalone_interface_.update();
}

void Controller::executeStandaloneCallback()
{
  standalone_interface_.executeCurrentFrameCallback();
}

bool Controller::getLedsPowered()
{
  return digitalRead(constants::led_pwr_pin) == HIGH;
}

void Controller::saveState(int state)
{
  if (state >= constants::STATE_COUNT)
  {
    return;
  }
  uint32_t channels = getChannelsOn();
  states_array_[state] = channels;
  modular_device.setSavedVariableValue(constants::states_name,states_array_,state);
}

void Controller::recallState(int state)
{
  if (state >= constants::STATE_COUNT)
  {
    return;
  }
  modular_device.getSavedVariableValue(constants::states_name,states_array_,state);
  uint32_t channels = states_array_[state];
  setChannels(channels);
}

void Controller::getStatesArray(uint32_t states_array[])
{
  for (int state=0; state<constants::STATE_COUNT; state++)
  {
    modular_device.getSavedVariableValue(constants::states_name,states_array,state);
  }
}

uint8_t Controller::getChannelIntVar()
{
  return channel_int_var_ptr_->getValue();
}

uint8_t Controller::getStateIntVar()
{
  return state_int_var_ptr_->getValue();
}

uint8_t Controller::getCIntVar()
{
  return c_int_var_ptr_->getValue();
}

int Controller::getPeriodIntVar()
{
  return period_int_var_ptr_->getValue();
}

void Controller::setPeriodIntVar(int value)
{
  period_int_var_ptr_->setValue(value);
}

int Controller::getOnIntVar()
{
  return on_int_var_ptr_->getValue();
}

void Controller::setOnIntVar(int value)
{
  on_int_var_ptr_->setValue(value);
}

void Controller::setOnIntVarMax(int value)
{
  if (value <= constants::display_on_max)
  {
    on_int_var_ptr_->setRange(constants::display_on_min,value);
  }
}

int Controller::getCountIntVar()
{
  return count_int_var_ptr_->getValue();
}

void Controller::setCountIntVar(int value)
{
  count_int_var_ptr_->setValue(value);
}

void Controller::setCountIntVarMax(int value)
{
  if (value <= constants::display_count_max)
  {
    count_int_var_ptr_->setRange(constants::display_count_min,value);
  }
}

int Controller::getFrequencyIntVar()
{
  return frequency_int_var_ptr_->getValue();
}

void Controller::setFrequencyIntVar(int value)
{
  frequency_int_var_ptr_->setValue(value);
}

int Controller::getPwmDutyIntVar()
{
  return pwm_duty_int_var_ptr_->getValue();
}

void Controller::setPwmDutyIntVar(int value)
{
  pwm_duty_int_var_ptr_->setValue(value);
}

int Controller::getPwmDurIntVar()
{
  return pwm_dur_int_var_ptr_->getValue();
}

void Controller::setPwmDurIntVar(int value)
{
  pwm_dur_int_var_ptr_->setValue(value);
}

uint8_t Controller::getSpikeDutyIntVar()
{
  return spike_duty_int_var_ptr_->getValue();
}

int Controller::getSpikeDurIntVar()
{
  return spike_dur_int_var_ptr_->getValue();
}

uint8_t Controller::getHoldDutyIntVar()
{
  return hold_duty_int_var_ptr_->getValue();
}

int Controller::getHoldDurIntVar()
{
  return hold_dur_int_var_ptr_->getValue();
}

Controller controller;
