// ----------------------------------------------------------------------------
// Callbacks.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "JsonParser.h"
#include "ModularDevice.h"
#include "Constants.h"
#include "Controller.h"


namespace callbacks
{
void getLedsPoweredCallback();

void getAnalogInputCallback();

void getAnalogInputsCallback();

void getAnalogMinValuesCallback();

void getAnalogMaxValuesCallback();

void setAsAnalogMinValuesCallback();

void setAsAnalogMaxValuesCallback();

// Standalone Callbacks
void executeStandaloneCallbackCallback();

void resetDefaultsCallback();
}
#endif
