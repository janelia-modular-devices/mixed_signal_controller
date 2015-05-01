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

#include "Streaming.h"

namespace callbacks
{
struct PulseInfo
{
  EventController::EventIdPair event_id_pair;
  int channel_index;
};

void getLedsPoweredCallback();

void setChannelOnCallback();

void setChannelOffCallback();

void setChannelsOnCallback();

void setChannelsOffCallback();

void toggleChannelCallback();

void toggleChannelsCallback();

void toggleAllChannelsCallback();

void setAllChannelsOnCallback();

void setAllChannelsOffCallback();

void setChannelOnAllOthersOffCallback();

void setChannelOffAllOthersOnCallback();

void setChannelsOnAllOthersOffCallback();

void setChannelsOffAllOthersOnCallback();

void getChannelsOnCallback();

void getChannelsOffCallback();

void getChannelCountCallback();

void saveStateCallback();

void recallStateCallback();

void getSavedStatesCallback();

void addPulseCenteredCallback();

void addPwmPeriodOnDurationCallback();

void addPwmFrequencyDutyCycleCallback();

void addSpikeAndHoldCallback();

void stopAllPulsesCallback();

void startPwmPeriodOnDurationCallback();

void startPwmFrequencyDutyCycleCallback();

void startSpikeAndHoldCallback();

void stopPulseWaveCallback();

uint32_t arrayToChannels(ArduinoJson::Parser::JsonArray channels_array);

PulseInfo spikeAndHold(int index,
                       uint32_t delay,
                       uint32_t spike_duty_cycle,
                       uint32_t spike_duration,
                       uint32_t hold_duty_cycle,
                       long hold_duration);

// Standalone Callbacks
void executeStandaloneCallbackCallback();

void toggleChannelStandaloneCallback();

void saveStateStandaloneCallback();

void recallStateStandaloneCallback();

void pwmStandaloneCallback();

void spikeHoldStandaloneCallback();

// EventController Callbacks
void removeIndexedChannelCallback(int index);

void setChannelsOnEventCallback(int index);

void setChannelsOffEventCallback(int index);

//Interactive Variable Update Callbacks
void periodUpdateCallback();

void onUpdateCallback();

void countUpdateCallback();

void frequencyUpdateCallback();

void pwmDutyUpdateCallback();

void pwmDurUpdateCallback();
}
#endif
