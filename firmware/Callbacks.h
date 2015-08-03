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
#include "IndexedContainer.h"
#include "ModularDevice.h"
#include "Constants.h"
#include "Controller.h"


namespace callbacks
{
struct SetUntilInfo
{
  uint32_t channels;
  uint8_t ain;
  int ain_value_goal;
  bool complete;
  EventController::EventId event_id;
};

void getLedsPoweredCallback();

void getAnalogInputCallback();

void getAnalogInputsCallback();

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

void saveStateCallback();

void recallStateCallback();

void getSavedStatesCallback();

void setChannelsOnUntilCallback();

void setChannelsOffUntilCallback();

void isSetUntilCompleteCallback();

void areAllSetUntilsCompleteCallback();

void removeSetUntilCallback();

void removeAllSetUntilsCallback();

void getAllSetUntilIndexesCallback();

uint32_t arrayToChannels(ArduinoJson::Parser::JsonArray channels_array);

// Standalone Callbacks
void executeStandaloneCallbackCallback();

void toggleChannelStandaloneCallback();

void saveStateStandaloneCallback();

void recallStateStandaloneCallback();

// EventController Callbacks
// void removeIndexedSetUntilCallback(int index);

void setChannelsOnEventCallback(int index);

void setChannelsOffEventCallback(int index);

void setChannelsOffWhenGreaterThanEventCallback(int index);

void setChannelsOffWhenLessThanEventCallback(int index);

void setChannelsOnWhenGreaterThanEventCallback(int index);

void setChannelsOnWhenLessThanEventCallback(int index);

}
#endif
