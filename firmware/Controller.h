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
  void setChannelOn(int channel);
  void setChannelOff(int channel);
  void setChannelsOn(uint32_t channels);
  void setChannelsOff(uint32_t channels);
  void toggleChannel(int channel);
  void toggleChannels(uint32_t channels);
  void toggleAllChannels();
  void setAllChannelsOn();
  void setAllChannelsOff();
  void setChannelOnAllOthersOff(int channel);
  void setChannelOffAllOthersOn(int channel);
  void setChannelsOnAllOthersOff(uint32_t channels);
  void setChannelsOffAllOthersOn(uint32_t channels);
  uint32_t getChannelsOn();
  int getChannelCount();
  uint8_t getChannelIntVar();
private:
  int ain_min_array_[constants::AIN_COUNT];
  int ain_max_array_[constants::AIN_COUNT];
  SavedVariable* ain_min_svd_var_ptr_;
  SavedVariable* ain_max_svd_var_ptr_;
  Standalone::StandaloneInterface standalone_interface_;
  Standalone::DisplayVariable* ain_dsp_var_ptr_array_[constants::AIN_COUNT];
  Standalone::InteractiveVariable *channel_int_var_ptr_;
  uint32_t channels_;
  void updateDisplayVariables();
  void updateChannelsVariable(int channel, int value);
};

extern Controller controller;

#endif
