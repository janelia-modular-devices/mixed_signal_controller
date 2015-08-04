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
#include "FilterSmooth.h"
#include "Constants.h"
#include "Callbacks.h"


typedef FilterMean<constants::FILTER_SAMPLE_COUNT> Filter;

class Controller
{
public:
  Controller();
  void setup();
  void update();
  void executeStandaloneCallback();
  bool getLedsPowered();
  int getAnalogInput(const uint8_t ain);
  uint8_t getAnalogInputPercent(const uint8_t ain);
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
  void setupFilters();
  void updateAnalogInputFilter(const uint8_t ain);
  int getAnalogInputFiltered(const uint8_t ain);
private:
  Standalone::StandaloneInterface standalone_interface_;
  Standalone::DisplayVariable* ain_dsp_var_ptr_array_[constants::AIN_COUNT];
  Standalone::InteractiveVariable *channel_int_var_ptr_;
  Standalone::InteractiveVariable *state_int_var_ptr_;
  Standalone::DisplayLabel* channels_dsp_lbl_ptr_array_[constants::CHANNELS_DISPLAY_COUNT];
  Standalone::DisplayVariable* channels_dsp_var_ptr_array_[constants::CHANNELS_DISPLAY_COUNT];
  uint32_t channels_;
  uint32_t states_array_[constants::STATE_COUNT];
  Filter filters_[constants::AIN_COUNT];
  void updateDisplayVariables();
  void updateChannelsVariable(const int channel, const int value);
};

extern Controller controller;

#endif
