// ----------------------------------------------------------------------------
// Controller.cpp
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
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
                                                        constants::lights_pin,
                                                        constants::standalone_update_period))
{
}

void Controller::setup()
{
  EventController::event_controller.setup();

  // Pin Setup
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    pinMode(constants::io_pins[channel],OUTPUT);
  }
  setAllChannelsOff();

  // Device Info
  modular_server_.setName(constants::device_name);
  modular_server_.setModelNumber(constants::model_number);
  modular_server_.setFirmwareVersion(constants::firmware_major,constants::firmware_minor,constants::firmware_patch);

  // Add Server Streams
  modular_server_.addServerStream(Serial);

  // Set Storage
  modular_server_.setSavedVariableStorage(saved_variables_);
  modular_server_.setParameterStorage(parameters_);
  modular_server_.setMethodStorage(methods_);

  // Saved Variables
  modular_server_.createSavedVariable(constants::states_name,constants::states_array_default,constants::STATE_COUNT);

  // Parameters
  ModularDevice::Parameter & ain_parameter = modular_server_.createParameter(constants::ain_parameter_name);
  ain_parameter.setRange(0,constants::AIN_COUNT-1);

  ModularDevice::Parameter & channels_parameter = modular_server_.createParameter(constants::channels_parameter_name);
  channels_parameter.setTypeArray();
  channels_parameter.setRange(0,constants::CHANNEL_COUNT-1);

  ModularDevice::Parameter & state_parameter = modular_server_.createParameter(constants::state_parameter_name);
  state_parameter.setRange(0,constants::STATE_COUNT-1);

  ModularDevice::Parameter & duration_parameter = modular_server_.createParameter(constants::duration_parameter_name);
  duration_parameter.setRange(constants::duration_min,constants::duration_max);
  duration_parameter.setUnits(constants::duration_units);

  ModularDevice::Parameter & ain_value_parameter = modular_server_.createParameter(constants::ain_value_parameter_name);
  ain_value_parameter.setRange(constants::ain_value_min,constants::ain_value_max);

  // Methods
  ModularDevice::Method & execute_standalone_callback_method = modular_server_.createMethod(constants::execute_standalone_callback_method_name);
  execute_standalone_callback_method.attachCallback(callbacks::executeStandaloneCallbackCallback);

  ModularDevice::Method & get_leds_powered_method = modular_server_.createMethod(constants::get_leds_powered_method_name);
  get_leds_powered_method.attachCallback(callbacks::getLedsPoweredCallback);

  ModularDevice::Method & get_analog_inputs_method = modular_server_.createMethod(constants::get_analog_inputs_method_name);
  get_analog_inputs_method.attachCallback(callbacks::getAnalogInputsCallback);

  ModularDevice::Method & get_analog_inputs_filtered_method = modular_server_.createMethod(constants::get_analog_inputs_filtered_method_name);
  get_analog_inputs_filtered_method.attachCallback(callbacks::getAnalogInputsFilteredCallback);

  ModularDevice::Method & set_channels_on_method = modular_server_.createMethod(constants::set_channels_on_method_name);
  set_channels_on_method.attachCallback(callbacks::setChannelsOnCallback);
  set_channels_on_method.addParameter(channels_parameter);

  ModularDevice::Method & set_channels_off_method = modular_server_.createMethod(constants::set_channels_off_method_name);
  set_channels_off_method.attachCallback(callbacks::setChannelsOffCallback);
  set_channels_off_method.addParameter(channels_parameter);

  ModularDevice::Method & toggle_channels_method = modular_server_.createMethod(constants::toggle_channels_method_name);
  toggle_channels_method.attachCallback(callbacks::toggleChannelsCallback);
  toggle_channels_method.addParameter(channels_parameter);

  ModularDevice::Method & toggle_all_channels_method = modular_server_.createMethod(constants::toggle_all_channels_method_name);
  toggle_all_channels_method.attachCallback(callbacks::toggleAllChannelsCallback);

  ModularDevice::Method & set_all_channels_on_method = modular_server_.createMethod(constants::set_all_channels_on_method_name);
  set_all_channels_on_method.attachCallback(callbacks::setAllChannelsOnCallback);

  ModularDevice::Method & set_all_channels_off_method = modular_server_.createMethod(constants::set_all_channels_off_method_name);
  set_all_channels_off_method.attachCallback(callbacks::setAllChannelsOffCallback);

  ModularDevice::Method & set_channels_on_all_others_off_method = modular_server_.createMethod(constants::set_channels_on_all_others_off_method_name);
  set_channels_on_all_others_off_method.attachCallback(callbacks::setChannelsOnAllOthersOffCallback);
  set_channels_on_all_others_off_method.addParameter(channels_parameter);

  ModularDevice::Method & set_channels_off_all_others_on_method = modular_server_.createMethod(constants::set_channels_off_all_others_on_method_name);
  set_channels_off_all_others_on_method.attachCallback(callbacks::setChannelsOffAllOthersOnCallback);
  set_channels_off_all_others_on_method.addParameter(channels_parameter);

  ModularDevice::Method & get_channels_on_method = modular_server_.createMethod(constants::get_channels_on_method_name);
  get_channels_on_method.attachCallback(callbacks::getChannelsOnCallback);

  ModularDevice::Method & get_channels_off_method = modular_server_.createMethod(constants::get_channels_off_method_name);
  get_channels_off_method.attachCallback(callbacks::getChannelsOffCallback);

  ModularDevice::Method & get_channel_count_method = modular_server_.createMethod(constants::get_channel_count_method_name);
  get_channel_count_method.attachCallback(callbacks::getChannelCountCallback);

  ModularDevice::Method & save_state_method = modular_server_.createMethod(constants::save_state_method_name);
  save_state_method.attachCallback(callbacks::saveStateCallback);
  save_state_method.addParameter(state_parameter);

  ModularDevice::Method & recall_state_method = modular_server_.createMethod(constants::recall_state_method_name);
  recall_state_method.attachCallback(callbacks::recallStateCallback);
  recall_state_method.addParameter(state_parameter);

  ModularDevice::Method & get_saved_states_method = modular_server_.createMethod(constants::get_saved_states_method_name);
  get_saved_states_method.attachCallback(callbacks::getSavedStatesCallback);

  ModularDevice::Method & set_channels_on_until_method = modular_server_.createMethod(constants::set_channels_on_until_method_name);
  set_channels_on_until_method.attachCallback(callbacks::setChannelsOnUntilCallback);
  set_channels_on_until_method.addParameter(channels_parameter);
  set_channels_on_until_method.addParameter(ain_parameter);
  set_channels_on_until_method.addParameter(ain_value_parameter);

  ModularDevice::Method & set_channels_off_until_method = modular_server_.createMethod(constants::set_channels_off_until_method_name);
  set_channels_off_until_method.attachCallback(callbacks::setChannelsOffUntilCallback);
  set_channels_off_until_method.addParameter(channels_parameter);
  set_channels_off_until_method.addParameter(ain_parameter);
  set_channels_off_until_method.addParameter(ain_value_parameter);

  ModularDevice::Method & are_all_set_untils_complete_method = modular_server_.createMethod(constants::are_all_set_untils_complete_method_name);
  are_all_set_untils_complete_method.attachCallback(callbacks::areAllSetUntilsCompleteCallback);

  ModularDevice::Method & remove_all_set_untils_method = modular_server_.createMethod(constants::remove_all_set_untils_method_name);
  remove_all_set_untils_method.attachCallback(callbacks::removeAllSetUntilsCallback);

  ModularDevice::Method & set_channels_on_for_method = modular_server_.createMethod(constants::set_channels_on_for_method_name);
  set_channels_on_for_method.attachCallback(callbacks::setChannelsOnForCallback);
  set_channels_on_for_method.addParameter(channels_parameter);
  set_channels_on_for_method.addParameter(duration_parameter);

  ModularDevice::Method & set_channels_off_for_method = modular_server_.createMethod(constants::set_channels_off_for_method_name);
  set_channels_off_for_method.attachCallback(callbacks::setChannelsOffForCallback);
  set_channels_off_for_method.addParameter(channels_parameter);
  set_channels_off_for_method.addParameter(duration_parameter);

  ModularDevice::Method & are_all_set_fors_complete_method = modular_server_.createMethod(constants::are_all_set_fors_complete_method_name);
  are_all_set_fors_complete_method.attachCallback(callbacks::areAllSetForsCompleteCallback);

  ModularDevice::Method & remove_all_set_fors_method = modular_server_.createMethod(constants::remove_all_set_fors_method_name);
  remove_all_set_fors_method.attachCallback(callbacks::removeAllSetForsCallback);

  // Setup Streams
  Serial.begin(constants::baudrate);

  // Start Modular Device Server
  modular_server_.startServer();

  // Standalone Interface

  // Set Storage
  standalone_interface_.setDisplayLabelStorage(display_labels_);
  standalone_interface_.setDisplayVariableStorage(display_variables_);
  standalone_interface_.setInteractiveVariableStorage(interactive_variables_);

  // Setup
  standalone_interface_.setup(constants::frame_name_array);

  // Display Labels
  Standalone::DisplayLabel * ain_dsp_lbl_ptr_array[constants::AIN_COUNT];
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    ain_dsp_lbl_ptr_array[ain] = &(standalone_interface_.createDisplayLabel());
    ain_dsp_lbl_ptr_array[ain]->setDisplayPosition(constants::ain_dsp_lbl_display_positions[ain]);
    ain_dsp_lbl_ptr_array[ain]->setConstantString(constants::ain_dsp_lbl_strs[ain]);
    ain_dsp_lbl_ptr_array[ain]->setRightJustify();
    ain_dsp_lbl_ptr_array[ain]->setDisplayWidth(constants::ain_dsp_lbl_width);
  }

  Standalone::DisplayLabel & channel_dsp_lbl = standalone_interface_.createDisplayLabel();
  channel_dsp_lbl.setDisplayPosition(constants::channel_dsp_lbl_display_position);
  channel_dsp_lbl.setConstantString(constants::channel_dsp_lbl_str);
  channel_dsp_lbl.setRightJustify();

  Standalone::DisplayLabel & state_dsp_lbl = standalone_interface_.createDisplayLabel();
  state_dsp_lbl.setDisplayPosition(constants::state_dsp_lbl_display_position);
  state_dsp_lbl.setConstantString(constants::state_parameter_name);
  state_dsp_lbl.setRightJustify();

  for (int channels=0; channels<constants::CHANNELS_DISPLAY_COUNT; channels++)
  {
    channels_dsp_lbl_ptr_array_[channels] = &(standalone_interface_.createDisplayLabel());
    channels_dsp_lbl_ptr_array_[channels]->setDisplayPosition(constants::channels_dsp_lbl_display_positions[channels]);
    channels_dsp_lbl_ptr_array_[channels]->setConstantString(constants::channels_dsp_lbl_strs[channels]);
  }

  // Display Variables
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    ain_dsp_var_ptr_array_[ain] = &(standalone_interface_.createDisplayVariable());
    ain_dsp_var_ptr_array_[ain]->setDisplayPosition(constants::ain_dsp_var_display_positions[ain]);
    ain_dsp_var_ptr_array_[ain]->setDisplayWidth(constants::percent_display_width);
  }

  for (int channels=0; channels<constants::CHANNELS_DISPLAY_COUNT; channels++)
  {
    channels_dsp_var_ptr_array_[channels] = &(standalone_interface_.createDisplayVariable());
    channels_dsp_var_ptr_array_[channels]->setDisplayPosition(constants::channels_dsp_var_display_positions[channels]);
    channels_dsp_var_ptr_array_[channels]->setRightJustify();
    channels_dsp_var_ptr_array_[channels]->setBaseBin();
    channels_dsp_var_ptr_array_[channels]->setDisplayWidth(constants::channels_dsp_var_display_width);
    channels_dsp_var_ptr_array_[channels]->setPaddingChar(0);
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
  channel_dsp_lbl.addToFrame(frame);
  channel_int_var_ptr_->addToFrame(frame);
  for (int channels=0; channels<constants::CHANNELS_DISPLAY_COUNT; channels++)
  {
    channels_dsp_lbl_ptr_array_[channels]->addToFrame(frame);
    channels_dsp_var_ptr_array_[channels]->addToFrame(frame);
  }
  standalone_interface_.attachCallbackToFrame(callbacks::toggleChannelStandaloneCallback,frame);

  // Frame 3
  frame = 3;
  for (int channels=0; channels<constants::CHANNELS_DISPLAY_COUNT; channels++)
  {
    channels_dsp_lbl_ptr_array_[channels]->addToFrame(frame);
    channels_dsp_var_ptr_array_[channels]->addToFrame(frame);
  }
  standalone_interface_.attachCallbackToFrame(callbacks::setAllChannelsOnCallback,frame);

  // Frame 4
  frame = 4;
  for (int channels=0; channels<constants::CHANNELS_DISPLAY_COUNT; channels++)
  {
    channels_dsp_lbl_ptr_array_[channels]->addToFrame(frame);
    channels_dsp_var_ptr_array_[channels]->addToFrame(frame);
  }
  standalone_interface_.attachCallbackToFrame(callbacks::setAllChannelsOffCallback,frame);

  // Frame 5
  frame = 5;
  state_dsp_lbl.addToFrame(frame);
  state_int_var_ptr_->addToFrame(frame);
  for (int channels=0; channels<constants::CHANNELS_DISPLAY_COUNT; channels++)
  {
    channels_dsp_lbl_ptr_array_[channels]->addToFrame(frame);
    channels_dsp_var_ptr_array_[channels]->addToFrame(frame);
  }
  standalone_interface_.attachCallbackToFrame(callbacks::saveStateStandaloneCallback,frame);

  // Frame 6
  frame = 6;
  state_dsp_lbl.addToFrame(frame);
  state_int_var_ptr_->addToFrame(frame);
  for (int channels=0; channels<constants::CHANNELS_DISPLAY_COUNT; channels++)
  {
    channels_dsp_lbl_ptr_array_[channels]->addToFrame(frame);
    channels_dsp_var_ptr_array_[channels]->addToFrame(frame);
  }
  standalone_interface_.attachCallbackToFrame(callbacks::recallStateStandaloneCallback,frame);

  // Enable Standalone Interface
  standalone_interface_.enable();

  if (constants::use_filters)
  {
    setupFilters();
  }
}

void Controller::update()
{
  modular_server_.handleServerRequests();
  bool updated = standalone_interface_.update();
  if (updated)
  {
    updateDisplayVariables();
  }
}

ModularDevice::ModularServer & Controller::getModularServer()
{
  return modular_server_;
}

void Controller::executeStandaloneCallback()
{
  standalone_interface_.executeCurrentFrameCallback();
}

bool Controller::getLedsPowered()
{
  return digitalRead(constants::lights_pin) == HIGH;
}

int Controller::getAnalogInput(const uint8_t ain)
{
  if (ain >= constants::AIN_COUNT)
  {
    return 0;
  }
  int ain_value = analogRead(constants::ain_pins[ain]);
  return ain_value;
}

uint8_t Controller::getAnalogInputPercent(const uint8_t ain)
{
  int ain_value = getAnalogInput(ain);
  int percent = map(ain_value,
                    constants::ain_value_min,
                    constants::ain_value_max,
                    constants::percent_min,
                    constants::percent_max);
  return percent;
}

void Controller::setChannelOn(const int channel)
{
  digitalWrite(constants::io_pins[channel],HIGH);
  updateChannelsVariable(channel,1);
}

void Controller::setChannelOff(const int channel)
{
  digitalWrite(constants::io_pins[channel],LOW);
  updateChannelsVariable(channel,0);
}

void Controller::setChannels(const uint32_t channels)
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

void Controller::setChannelsOn(const uint32_t channels)
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

void Controller::setChannelsOff(const uint32_t channels)
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

void Controller::toggleChannel(const int channel)
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

void Controller::toggleChannels(const uint32_t channels)
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

void Controller::setChannelOffAllOthersOn(const int channel)
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

void Controller::setChannelsOnAllOthersOff(const uint32_t channels)
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

void Controller::setChannelsOffAllOthersOn(const uint32_t channels)
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

void Controller::saveState(const int state)
{
  if (state >= constants::STATE_COUNT)
  {
    return;
  }
  uint32_t channels = getChannelsOn();
  states_array_[state] = channels;
  modular_server_.setSavedVariableValue(constants::states_name,states_array_,state);
}

void Controller::recallState(const int state)
{
  if (state >= constants::STATE_COUNT)
  {
    return;
  }
  modular_server_.getSavedVariableValue(constants::states_name,states_array_,state);
  uint32_t channels = states_array_[state];
  setChannels(channels);
}

void Controller::getStatesArray(uint32_t states_array[])
{
  for (int state=0; state<constants::STATE_COUNT; state++)
  {
    modular_server_.getSavedVariableValue(constants::states_name,states_array,state);
  }
}

uint8_t Controller::getStateIntVar()
{
  return state_int_var_ptr_->getValue();
}

void Controller::setupFilters()
{
  EventController::EventId event_id;
  event_id = EventController::event_controller.addInfiniteRecurringEventUsingDelay(callbacks::updateFilterBlockCallback,
                                                                                   500,
                                                                                   constants::filter_update_period,
                                                                                   0);
  for (int i=1;i<constants::filter_block_ain_count;++i)
  {
    event_id = EventController::event_controller.addInfiniteRecurringEventUsingOffset(callbacks::updateFilterBlockCallback,
                                                                                      event_id,
                                                                                      1,
                                                                                      constants::filter_update_period,
                                                                                      i);
  }
}

void Controller::updateAnalogInputFilter(const uint8_t ain)
{
  int ain_value = getAnalogInput(ain);
  filters_[ain].addSample(ain_value);
}

int Controller::getAnalogInputFiltered(const uint8_t ain)
{
  if (constants::use_filters)
  {
    if (ain >= constants::AIN_COUNT)
    {
      return 0;
    }
    int ain_value = filters_[ain].getFilteredValue();
    return ain_value;
  }
  else
  {
    return getAnalogInput(ain);
  }
}

void Controller::updateDisplayVariables()
{
  int percent;
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    percent = getAnalogInputPercent(ain);
    ain_dsp_var_ptr_array_[ain]->setValue(percent);
  }
  for (int channels=0; channels<constants::CHANNELS_DISPLAY_COUNT; channels++)
  {
    uint8_t bit_shift = (constants::CHANNELS_DISPLAY_COUNT - 1 - channels)*constants::channels_dsp_var_display_width;
    uint32_t value = channels_ << bit_shift;
    bit_shift = (constants::CHANNELS_DISPLAY_COUNT - 1)*constants::channels_dsp_var_display_width;
    value = value >> bit_shift;
    channels_dsp_var_ptr_array_[channels]->setValue(value);
  }
}

void Controller::updateChannelsVariable(const int channel, const int value)
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
