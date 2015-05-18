// ----------------------------------------------------------------------------
// Callbacks.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Callbacks.h"

using namespace ArduinoJson::Parser;

namespace callbacks
{
// Callbacks must be non-blocking (avoid 'delay')
//
// modular_device.getParameterValue must be cast to either:
// char*
// long
// double
// bool
// JsonArray
// JsonObject
//
// For more info read about ArduinoJson v3 JsonParser JsonValues
//
// modular_device.getSavedVariableValue type must match the saved variable default type
// modular_device.setSavedVariableValue type must match the saved variable default type


void getLedsPoweredCallback()
{
  boolean leds_powered = controller.getLedsPowered();
  modular_device.addBooleanToResponse("leds_powered",leds_powered);
}

void getAnalogInputCallback()
{
  long ain = modular_device.getParameterValue(constants::ain_parameter_name);
  uint8_t percent = controller.getAnalogInput(ain);
  modular_device.addToResponse("percent",percent);
}

void getAnalogInputsCallback()
{
  modular_device.addKeyToResponse("percents");
  modular_device.startResponseArray();
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    uint8_t percent = controller.getAnalogInput(ain);
    modular_device.addToResponse(percent);
  }
  modular_device.stopResponseArray();
}

void getAnalogMinValuesCallback()
{
  modular_device.addKeyToResponse("analog_min_values");
  modular_device.startResponseArray();
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    int value = controller.getAnalogMinValue(ain);
    modular_device.addToResponse(value);
  }
  modular_device.stopResponseArray();
}

void getAnalogMaxValuesCallback()
{
  modular_device.addKeyToResponse("analog_max_values");
  modular_device.startResponseArray();
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    int value = controller.getAnalogMaxValue(ain);
    modular_device.addToResponse(value);
  }
  modular_device.stopResponseArray();
}

void setAsAnalogMinValuesCallback()
{
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    controller.setAsAnalogMinValue(ain);
  }
}

void setAsAnalogMaxValuesCallback()
{
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    controller.setAsAnalogMaxValue(ain);
  }
}

// Standalone Callbacks
void executeStandaloneCallbackCallback()
{
  controller.executeStandaloneCallback();
}

void resetDefaultsCallback()
{
  modular_device.resetDefaults();
}
}
