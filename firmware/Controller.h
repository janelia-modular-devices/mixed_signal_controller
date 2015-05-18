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
private:
  int ain_min_array_[constants::AIN_COUNT];
  int ain_max_array_[constants::AIN_COUNT];
  Standalone::StandaloneInterface standalone_interface_;
  Standalone::DisplayVariable* ain_dsp_var_ptr_array_[constants::AIN_COUNT];
  void updateDisplayVariables();
};

extern Controller controller;

#endif
