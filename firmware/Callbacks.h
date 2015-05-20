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
#include "EventController.h"
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

void resetAnalogMinMaxDefaultsCallback();

void setChannelsOnCallback();

void setChannelsOffCallback();

void toggleChannelsCallback();

void toggleAllChannelsCallback();

void setAllChannelsOnCallback();

void setAllChannelsOffCallback();

void setChannelsOnAllOthersOffCallback();

void setChannelsOffAllOthersOnCallback();

void getChannelsOnCallback();

void getChannelsOffCallback();

void getChannelCountCallback();

uint32_t arrayToChannels(ArduinoJson::Parser::JsonArray channels_array);

// Standalone Callbacks
void executeStandaloneCallbackCallback();

void toggleChannelStandaloneCallback();

}
#endif
