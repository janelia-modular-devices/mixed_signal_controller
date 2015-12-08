// ----------------------------------------------------------------------------
// Callbacks.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "ArduinoJson.h"
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

struct SetForInfo
{
  uint32_t channels;
  bool complete;
  EventController::EventIdPair event_id_pair;
};

void getLedsPoweredCallback();

void getAnalogInputsCallback();

void getAnalogInputsFilteredCallback();

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

void areAllSetUntilsCompleteCallback();

void removeAllSetUntilsCallback();

void setChannelsOnForCallback();

void setChannelsOffForCallback();

void areAllSetForsCompleteCallback();

void removeAllSetForsCallback();

uint32_t arrayToChannels(ArduinoJson::JsonArray& channels_array);

// Standalone Callbacks
void executeStandaloneCallbackCallback();

void toggleChannelStandaloneCallback();

void saveStateStandaloneCallback();

void recallStateStandaloneCallback();

// EventController Callbacks
// void removeIndexedSetUntilCallback(int index);

void setChannelsOnUntilEventCallback(int index);

void setChannelsOffUntilEventCallback(int index);

void setChannelsOnForEventCallback(int index);

void setChannelsOffForEventCallback(int index);

void completeForEventCallback(int index);

void setChannelsOffWhenGreaterThanEventCallback(int index);

void setChannelsOffWhenLessThanEventCallback(int index);

void setChannelsOnWhenGreaterThanEventCallback(int index);

void setChannelsOnWhenLessThanEventCallback(int index);

void updateFilterBlockCallback(int index);

}
#endif
