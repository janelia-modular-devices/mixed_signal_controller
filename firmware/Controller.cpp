// ----------------------------------------------------------------------------
// Controller.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Controller.h"

Controller::Controller() :
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
  // Pin Setup
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    pinMode(constants::io_pins[channel],OUTPUT);
  }
  setAllChannelsOff();

  // Device Info
  modular_device.setName(constants::device_name);
  modular_device.setModelNumber(constants::model_number);
  modular_device.setFirmwareNumber(constants::firmware_number);

  // Saved Variables
  ain_min_svd_var_ptr_ = &(modular_device.createSavedVariable(constants::ain_min_array_name,constants::ain_min_array_default,constants::AIN_COUNT));
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    modular_device.getSavedVariableValue(constants::ain_min_array_name,ain_min_array_,ain);
  }

  ain_max_svd_var_ptr_ = &(modular_device.createSavedVariable(constants::ain_max_array_name,constants::ain_max_array_default,constants::AIN_COUNT));
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    modular_device.getSavedVariableValue(constants::ain_max_array_name,ain_max_array_,ain);
  }

  modular_device.createSavedVariable(constants::states_name,constants::states_array_default,constants::STATE_COUNT);

  // Parameters
  ModularDevice::Parameter& ain_parameter = modular_device.createParameter(constants::ain_parameter_name);
  ain_parameter.setRange(0,constants::AIN_COUNT-1);

  ModularDevice::Parameter& channels_parameter = modular_device.createParameter(constants::channels_parameter_name);
  channels_parameter.setTypeArray();
  channels_parameter.setRange(0,constants::CHANNEL_COUNT-1);

  ModularDevice::Parameter& state_parameter = modular_device.createParameter(constants::state_parameter_name);
  state_parameter.setRange(0,constants::STATE_COUNT-1);

  // Methods
  ModularDevice::Method& execute_standalone_callback_method = modular_device.createMethod(constants::execute_standalone_callback_method_name);
  execute_standalone_callback_method.attachCallback(callbacks::executeStandaloneCallbackCallback);

  ModularDevice::Method& get_leds_powered_method = modular_device.createMethod(constants::get_leds_powered_method_name);
  get_leds_powered_method.attachCallback(callbacks::getLedsPoweredCallback);

  ModularDevice::Method& get_analog_input_method = modular_device.createMethod(constants::get_analog_input_method_name);
  get_analog_input_method.attachCallback(callbacks::getAnalogInputCallback);
  get_analog_input_method.addParameter(ain_parameter);

  ModularDevice::Method& get_analog_inputs_method = modular_device.createMethod(constants::get_analog_inputs_method_name);
  get_analog_inputs_method.attachCallback(callbacks::getAnalogInputsCallback);

  ModularDevice::Method& get_analog_min_values_method = modular_device.createMethod(constants::get_analog_min_values_method_name);
  get_analog_min_values_method.attachCallback(callbacks::getAnalogMinValuesCallback);

  ModularDevice::Method& get_analog_max_values_method = modular_device.createMethod(constants::get_analog_max_values_method_name);
  get_analog_max_values_method.attachCallback(callbacks::getAnalogMaxValuesCallback);

  ModularDevice::Method& set_as_analog_min_values_method = modular_device.createMethod(constants::set_as_analog_min_values_method_name);
  set_as_analog_min_values_method.attachCallback(callbacks::setAsAnalogMinValuesCallback);

  ModularDevice::Method& set_as_analog_max_values_method = modular_device.createMethod(constants::set_as_analog_max_values_method_name);
  set_as_analog_max_values_method.attachCallback(callbacks::setAsAnalogMaxValuesCallback);

  ModularDevice::Method& reset_analog_min_max_defaults_method = modular_device.createMethod(constants::reset_analog_min_max_defaults_method_name);
  reset_analog_min_max_defaults_method.attachCallback(callbacks::resetAnalogMinMaxDefaultsCallback);

  ModularDevice::Method& set_channels_on_method = modular_device.createMethod(constants::set_channels_on_method_name);
  set_channels_on_method.attachCallback(callbacks::setChannelsOnCallback);
  set_channels_on_method.addParameter(channels_parameter);

  ModularDevice::Method& set_channels_off_method = modular_device.createMethod(constants::set_channels_off_method_name);
  set_channels_off_method.attachCallback(callbacks::setChannelsOffCallback);
  set_channels_off_method.addParameter(channels_parameter);

  ModularDevice::Method& toggle_channels_method = modular_device.createMethod(constants::toggle_channels_method_name);
  toggle_channels_method.attachCallback(callbacks::toggleChannelsCallback);
  toggle_channels_method.addParameter(channels_parameter);

  ModularDevice::Method& toggle_all_channels_method = modular_device.createMethod(constants::toggle_all_channels_method_name);
  toggle_all_channels_method.attachCallback(callbacks::toggleAllChannelsCallback);

  ModularDevice::Method& set_all_channels_on_method = modular_device.createMethod(constants::set_all_channels_on_method_name);
  set_all_channels_on_method.attachCallback(callbacks::setAllChannelsOnCallback);

  ModularDevice::Method& set_all_channels_off_method = modular_device.createMethod(constants::set_all_channels_off_method_name);
  set_all_channels_off_method.attachCallback(callbacks::setAllChannelsOffCallback);

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

  // Start Server
  modular_device.startServer(constants::baudrate);

  // Standalone Interface
  standalone_interface_.setup(constants::frame_name_array,constants::FRAME_COUNT);

  // Display Labels
  Standalone::DisplayLabel* ain_dsp_lbl_ptr_array[constants::AIN_COUNT];
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    ain_dsp_lbl_ptr_array[ain] = &(standalone_interface_.createDisplayLabel());
    ain_dsp_lbl_ptr_array[ain]->setDisplayPosition(constants::ain_dsp_lbl_display_positions[ain]);
    ain_dsp_lbl_ptr_array[ain]->setConstantString(constants::ain_dsp_lbl_strings[ain]);
    ain_dsp_lbl_ptr_array[ain]->setRightJustify();
    ain_dsp_lbl_ptr_array[ain]->setDisplayWidth(constants::ain_dsp_lbl_width);
  }

  Standalone::DisplayLabel& channel_dsp_lbl = standalone_interface_.createDisplayLabel();
  channel_dsp_lbl.setDisplayPosition(constants::channel_dsp_lbl_display_position);
  channel_dsp_lbl.setConstantString(constants::channel_dsp_lbl_str);
  channel_dsp_lbl.setRightJustify();

  Standalone::DisplayLabel& state_dsp_lbl = standalone_interface_.createDisplayLabel();
  state_dsp_lbl.setDisplayPosition(constants::state_dsp_lbl_display_position);
  state_dsp_lbl.setConstantString(constants::state_parameter_name);
  state_dsp_lbl.setRightJustify();

  // Display Variables
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    ain_dsp_var_ptr_array_[ain] = &(standalone_interface_.createDisplayVariable());
    ain_dsp_var_ptr_array_[ain]->setDisplayPosition(constants::ain_dsp_var_display_positions[ain]);
    ain_dsp_var_ptr_array_[ain]->setDisplayWidth(constants::percent_display_width);
  }

  // Interactive Variables
  channel_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  channel_int_var_ptr_->setDisplayPosition(constants::channel_int_var_display_position);
  channel_int_var_ptr_->setRange(0,constants::CHANNEL_COUNT-1);
  channel_int_var_ptr_->trimDisplayWidthUsingRange();

  state_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  state_int_var_ptr_->setDisplayPosition(constants::state_int_var_display_position);
  state_int_var_ptr_->setRange(0,constants::STATE_COUNT-1);
  state_int_var_ptr_->trimDisplayWidthUsingRange();

  // All Frames

  // Frame 0
  int frame = 0;
  for (int ain=0; ain<8; ain++)
  {
    ain_dsp_lbl_ptr_array[ain]->addToFrame(frame);
    ain_dsp_var_ptr_array_[ain]->addToFrame(frame);
  }

  // Frame 1
  frame = 1;
  for (int ain=8; ain<constants::AIN_COUNT; ain++)
  {
    ain_dsp_lbl_ptr_array[ain]->addToFrame(frame);
    ain_dsp_var_ptr_array_[ain]->addToFrame(frame);
  }

  // Frame 2
  frame = 2;
  standalone_interface_.attachCallbackToFrame(callbacks::resetAnalogMinMaxDefaultsCallback,frame);

  // Frame 3
  frame = 3;
  standalone_interface_.attachCallbackToFrame(callbacks::setAsAnalogMinValuesCallback,frame);

  // Frame 4
  frame = 4;
  standalone_interface_.attachCallbackToFrame(callbacks::setAsAnalogMaxValuesCallback,frame);

  // Frame 5
  frame = 5;
  channel_dsp_lbl.addToFrame(frame);
  channel_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::toggleChannelStandaloneCallback,frame);

  // Frame 6
  frame = 6;
  state_dsp_lbl.addToFrame(frame);
  state_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::saveStateStandaloneCallback,frame);

  // Frame 7
  frame = 7;
  state_dsp_lbl.addToFrame(frame);
  state_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::recallStateStandaloneCallback,frame);

  // Enable Standalone Interface
  standalone_interface_.enable();
}

void Controller::update()
{
  modular_device.handleServerRequests();
  boolean updated = standalone_interface_.update();
  if (updated)
  {
    updateDisplayVariables();
  }
}

void Controller::executeStandaloneCallback()
{
  standalone_interface_.executeCurrentFrameCallback();
}

bool Controller::getLedsPowered()
{
  return digitalRead(constants::led_pwr_pin) == HIGH;
}

uint8_t Controller::getAnalogInput(const uint8_t ain)
{
  if (ain >= constants::AIN_COUNT)
  {
    return 0;
  }
  int ain_value = analogRead(constants::ain_pins[ain]);
  int percent = betterMap(ain_value,
                          getAnalogMinValue(ain),
                          getAnalogMaxValue(ain),
                          constants::percent_min,
                          constants::percent_max);
  return percent;
}

int Controller::getAnalogMinValue(const uint8_t ain)
{
  if (ain >= constants::AIN_COUNT)
  {
    return 0;
  }
  modular_device.getSavedVariableValue(constants::ain_min_array_name,ain_min_array_,ain);
  return ain_min_array_[ain];
}

int Controller::getAnalogMaxValue(const uint8_t ain)
{
  if (ain >= constants::AIN_COUNT)
  {
    return 0;
  }
  modular_device.getSavedVariableValue(constants::ain_max_array_name,ain_max_array_,ain);
  return ain_max_array_[ain];
}

void Controller::setAsAnalogMinValue(const uint8_t ain)
{
  if (ain < constants::AIN_COUNT)
  {
    ain_min_array_[ain] = analogRead(constants::ain_pins[ain]);
    modular_device.setSavedVariableValue(constants::ain_min_array_name,ain_min_array_,ain);
  }
}

void Controller::setAsAnalogMaxValue(const uint8_t ain)
{
  if (ain < constants::AIN_COUNT)
  {
    ain_max_array_[ain] = analogRead(constants::ain_pins[ain]);
    modular_device.setSavedVariableValue(constants::ain_max_array_name,ain_max_array_,ain);
  }
}

void Controller::resetAnalogMinMaxDefaults()
{
  ain_min_svd_var_ptr_->setDefaultValue();
  ain_max_svd_var_ptr_->setDefaultValue();
}

void Controller::setChannelOn(int channel)
{
  digitalWrite(constants::io_pins[channel],HIGH);
  updateChannelsVariable(channel,1);
}

void Controller::setChannelOff(int channel)
{
  digitalWrite(constants::io_pins[channel],LOW);
  updateChannelsVariable(channel,0);
}

void Controller::setChannels(uint32_t channels)
{
  uint32_t bit;
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    bit = 1;
    bit = bit << channel;
    if (bit & channels)
    {
      setChannelOn(channel);
    }
    else
    {
      setChannelOff(channel);
    }
  }
}

void Controller::setChannelsOn(uint32_t channels)
{
  uint32_t bit;
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    bit = 1;
    bit = bit << channel;
    if (bit & channels)
    {
      setChannelOn(channel);
    }
  }
}

void Controller::setChannelsOff(uint32_t channels)
{
  uint32_t bit;
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    bit = 1;
    bit = bit << channel;
    if (bit & channels)
    {
      setChannelOff(channel);
    }
  }
}

void Controller::toggleChannel(int channel)
{
  uint32_t bit = 1;
  bit = bit << channel;
  if (bit & channels_)
  {
    setChannelOff(channel);
  }
  else
  {
    setChannelOn(channel);
  }
}

void Controller::toggleChannels(uint32_t channels)
{
  uint32_t bit;
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    bit = 1;
    bit = bit << channel;
    if (bit & channels)
    {
      toggleChannel(channel);
    }
  }
}

void Controller::toggleAllChannels()
{
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    toggleChannel(channel);
  }
}

void Controller::setAllChannelsOn()
{
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    setChannelOn(channel);
  }
}

void Controller::setAllChannelsOff()
{
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    setChannelOff(channel);
  }
}

void Controller::setChannelOnAllOthersOff(int channel)
{
  for (int c=0; c<constants::CHANNEL_COUNT; ++c)
  {
    if (c == channel)
    {
      setChannelOn(c);
    }
    else
    {
      setChannelOff(c);
    }
  }
}

void Controller::setChannelOffAllOthersOn(int channel)
{
  for (int c=0; c<constants::CHANNEL_COUNT; ++c)
  {
    if (c == channel)
    {
      setChannelOff(c);
    }
    else
    {
      setChannelOn(c);
    }
  }
}

void Controller::setChannelsOnAllOthersOff(uint32_t channels)
{
  uint32_t bit;
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    bit = 1;
    bit = bit << channel;
    if (bit & channels)
    {
      setChannelOn(channel);
    }
    else
    {
      setChannelOff(channel);
    }
  }
}

void Controller::setChannelsOffAllOthersOn(uint32_t channels)
{
  uint32_t bit;
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    bit = 1;
    bit = bit << channel;
    if (bit & channels)
    {
      setChannelOff(channel);
    }
    else
    {
      setChannelOn(channel);
    }
  }
}

uint32_t Controller::getChannelsOn()
{
  return channels_;
}

int Controller::getChannelCount()
{
  return constants::CHANNEL_COUNT;
}

uint8_t Controller::getChannelIntVar()
{
  return channel_int_var_ptr_->getValue();
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

uint8_t Controller::getStateIntVar()
{
  return state_int_var_ptr_->getValue();
}

void Controller::updateDisplayVariables()
{
  int percent;
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    percent = getAnalogInput(ain);
    ain_dsp_var_ptr_array_[ain]->setValue(percent);
  }
}

void Controller::updateChannelsVariable(int channel, int value)
{
  uint32_t bit = 1;
  bit = bit << channel;
  if (value)
  {
    channels_ |= bit;
  }
  else
  {
    channels_ &= ~bit;
  }
}

Controller controller;
