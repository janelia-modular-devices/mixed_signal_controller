// ----------------------------------------------------------------------------
// Controller.h
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "ModularDevice.h"
#include "StandaloneInterface.h"
#include "BetterMap.h"
#include "Constants.h"
#include "Callbacks.h"

class Controller
{
public:
  Controller();
  void setup();
  void update();
  void executeStandaloneCallback();
  bool getLedsPowered();
  uint8_t getAnalogInput(const uint8_t ain);
  int getAnalogMinValue(const uint8_t ain);
  int getAnalogMaxValue(const uint8_t ain);
  void setAsAnalogMinValue(const uint8_t ain);
  void setAsAnalogMaxValue(const uint8_t ain);
  void resetAnalogMinMaxDefaults();
  void setChannelOn(const int channel);
  void setChannelOff(const int channel);
  void setChannels(const uint32_t channels);
  void setChannelsOn(const uint32_t channels);
  void setChannelsOff(const uint32_t channels);
  void toggleChannel(const int channel);
  void toggleChannels(const uint32_t channels);
  void toggleAllChannels();
  void setAllChannelsOn();
  void setAllChannelsOff();
  void setChannelOnAllOthersOff(const int channel);
  void setChannelOffAllOthersOn(const int channel);
  void setChannelsOnAllOthersOff(const uint32_t channels);
  void setChannelsOffAllOthersOn(const uint32_t channels);
  uint32_t getChannelsOn();
  int getChannelCount();
  uint8_t getChannelIntVar();
  void saveState(const int state);
  void recallState(const int state);
  void getStatesArray(uint32_t states_array[]);
  uint8_t getStateIntVar();
private:
  int ain_min_array_[constants::AIN_COUNT];
  int ain_max_array_[constants::AIN_COUNT];
  SavedVariable* ain_min_svd_var_ptr_;
  SavedVariable* ain_max_svd_var_ptr_;
  Standalone::StandaloneInterface standalone_interface_;
  Standalone::DisplayVariable* ain_dsp_var_ptr_array_[constants::AIN_COUNT];
  Standalone::InteractiveVariable *channel_int_var_ptr_;
  Standalone::InteractiveVariable *state_int_var_ptr_;
  Standalone::DisplayLabel* channels_dsp_lbl_ptr_array_[constants::CHANNELS_DISPLAY_COUNT];
  Standalone::DisplayVariable* channels_dsp_var_ptr_array_[constants::CHANNELS_DISPLAY_COUNT];
  uint32_t channels_;
  uint32_t states_array_[constants::STATE_COUNT];
  void updateDisplayVariables();
  void updateChannelsVariable(const int channel, const int value);
};

extern Controller controller;

#endif
