// ----------------------------------------------------------------------------
// Controller.h
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "PowerSwitch.h"
#include "ModularDevice.h"
#include "StandaloneInterface.h"
#include "EventController.h"
#include "Constants.h"
#include "Callbacks.h"

class Controller : public PowerSwitch
{
public:
  Controller();
  void setup();
  void update();
  void executeStandaloneCallback();
  bool getLedsPowered();
  void saveState(int state);
  void recallState(int state);
  void getStatesArray(uint32_t states_array[]);
  uint8_t getChannelIntVar();
  uint8_t getStateIntVar();
  uint8_t getCIntVar();
  int getPeriodIntVar();
  void setPeriodIntVar(int value);
  int getOnIntVar();
  void setOnIntVar(int value);
  void setOnIntVarMax(int value);
  int getCountIntVar();
  void setCountIntVar(int value);
  void setCountIntVarMax(int value);
  int getFrequencyIntVar();
  void setFrequencyIntVar(int value);
  int getPwmDutyIntVar();
  void setPwmDutyIntVar(int value);
  int getPwmDurIntVar();
  void setPwmDurIntVar(int value);
  uint8_t getSpikeDutyIntVar();
  int getSpikeDurIntVar();
  uint8_t getHoldDutyIntVar();
  int getHoldDurIntVar();
private:
  uint32_t states_array_[constants::STATE_COUNT];
  Standalone::StandaloneInterface standalone_interface_;
  Standalone::InteractiveVariable *channel_int_var_ptr_;
  Standalone::InteractiveVariable *state_int_var_ptr_;
  Standalone::InteractiveVariable *c_int_var_ptr_;

  Standalone::InteractiveVariable *period_int_var_ptr_;
  Standalone::InteractiveVariable *on_int_var_ptr_;
  Standalone::InteractiveVariable *count_int_var_ptr_;
  Standalone::InteractiveVariable *frequency_int_var_ptr_;
  Standalone::InteractiveVariable *pwm_duty_int_var_ptr_;
  Standalone::InteractiveVariable *pwm_dur_int_var_ptr_;

  Standalone::InteractiveVariable *spike_duty_int_var_ptr_;
  Standalone::InteractiveVariable *spike_dur_int_var_ptr_;
  Standalone::InteractiveVariable *hold_duty_int_var_ptr_;
  Standalone::InteractiveVariable *hold_dur_int_var_ptr_;
};

extern Controller controller;

#endif
