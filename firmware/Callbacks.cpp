// ----------------------------------------------------------------------------
// Callbacks.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Callbacks.h"


namespace callbacks
{
// Callbacks must be non-blocking (avoid 'delay')
//
// modular_device.getParameterValue must be cast to either:
// const char*
// long
// double
// bool
// ArduinoJson::JsonArray&&
// ArduinoJson::JsonObject&
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_device.getSavedVariableValue type must match the saved variable default type
// modular_device.setSavedVariableValue type must match the saved variable default type


IndexedContainer<SetUntilInfo,constants::INDEXED_SET_UNTILS_COUNT_MAX> indexed_set_untils;
CONSTANT_STRING(indexed_set_untils_full_error,"No more available space for a new set_until, remove some to make more room.");

IndexedContainer<SetForInfo,constants::INDEXED_SET_FORS_COUNT_MAX> indexed_set_fors;
CONSTANT_STRING(indexed_set_fors_full_error,"No more available space for a new set_for, wait until they have completed and try again.");

void getLedsPoweredCallback()
{
  bool leds_powered = controller.getLedsPowered();
  modular_device.writeToResponse("leds_powered",leds_powered);
}

void getAnalogInputsCallback()
{
  modular_device.writeKeyToResponse("ain_values");
  modular_device.beginResponseArray();
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    int ain_value = controller.getAnalogInput(ain);
    modular_device.writeToResponse(ain_value);
  }
  modular_device.endResponseArray();
}

void getAnalogInputsFilteredCallback()
{
  modular_device.writeKeyToResponse("ain_values");
  modular_device.beginResponseArray();
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    int ain_value = controller.getAnalogInputFiltered(ain);
    modular_device.writeToResponse(ain_value);
  }
  modular_device.endResponseArray();
}

void setChannelsOnCallback()
{
  ArduinoJson::JsonArray& channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  controller.setChannelsOn(channels);
}

void setChannelsOffCallback()
{
  ArduinoJson::JsonArray& channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  controller.setChannelsOff(channels);
}

void toggleChannelsCallback()
{
  ArduinoJson::JsonArray& channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  controller.toggleChannels(channels);
}

void toggleAllChannelsCallback()
{
  controller.toggleAllChannels();
}

void setAllChannelsOnCallback()
{
  removeAllSetUntilsCallback();
  removeAllSetForsCallback();
  controller.setAllChannelsOn();
}

void setAllChannelsOffCallback()
{
  removeAllSetUntilsCallback();
  removeAllSetForsCallback();
  controller.setAllChannelsOff();
}

void setChannelsOnAllOthersOffCallback()
{
  ArduinoJson::JsonArray& channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  removeAllSetUntilsCallback();
  removeAllSetForsCallback();
  controller.setChannelsOnAllOthersOff(channels);
}

void setChannelsOffAllOthersOnCallback()
{
  ArduinoJson::JsonArray& channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  removeAllSetUntilsCallback();
  removeAllSetForsCallback();
  controller.setChannelsOffAllOthersOn(channels);
}

void getChannelsOnCallback()
{
  uint32_t channels_on = controller.getChannelsOn();
  uint32_t bit = 1;
  modular_device.writeKeyToResponse("channels_on");
  modular_device.beginResponseArray();
  for (int channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    if (channels_on & (bit << channel))
    {
      modular_device.writeToResponse(channel);
    }
  }
  modular_device.endResponseArray();
}

void getChannelsOffCallback()
{
  uint32_t channels_on = controller.getChannelsOn();
  uint32_t channels_off = ~channels_on;
  uint32_t bit = 1;
  modular_device.writeKeyToResponse("channels_off");
  modular_device.beginResponseArray();
  for (int channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    if (channels_off & (bit << channel))
    {
      modular_device.writeToResponse(channel);
    }
  }
  modular_device.endResponseArray();
}

void getChannelCountCallback()
{
  int channel_count = controller.getChannelCount();
  modular_device.writeToResponse("channel_count",channel_count);
}

void saveStateCallback()
{
  long state = modular_device.getParameterValue(constants::state_parameter_name);
  controller.saveState(state);
}

void recallStateCallback()
{
  long state = modular_device.getParameterValue(constants::state_parameter_name);
  controller.recallState(state);
}

void getSavedStatesCallback()
{
  uint32_t states_array[constants::STATE_COUNT];
  controller.getStatesArray(states_array);
  uint32_t bit = 1;
  modular_device.writeKeyToResponse("saved_states");
  modular_device.beginResponseArray();
  for (int state=0; state<constants::STATE_COUNT; state++)
  {
    modular_device.beginResponseArray();
    for (int channel=0; channel<=(constants::CHANNEL_COUNT-1); channel++)
    {
      if ((bit<<channel) & states_array[state])
      {
        modular_device.writeToResponse("on");
      }
      else
      {
        modular_device.writeToResponse("off");
      }
    }
    modular_device.endResponseArray();
  }
  modular_device.endResponseArray();
}

void setChannelsOnUntilCallback()
{
  if (indexed_set_untils.full())
  {
    modular_device.sendErrorResponse(indexed_set_untils_full_error);
    return;
  }
  ArduinoJson::JsonArray& channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  long ain = modular_device.getParameterValue(constants::ain_parameter_name);
  long ain_value_goal = modular_device.getParameterValue(constants::ain_value_parameter_name);
  SetUntilInfo set_until_info;
  set_until_info.channels = channels;
  set_until_info.ain = ain;
  set_until_info.ain_value_goal = ain_value_goal;
  set_until_info.complete = false;
  int set_until_index = indexed_set_untils.add(set_until_info);
  EventController::EventId event_id;
  int ain_value_current = controller.getAnalogInputFiltered(ain);
  if (ain_value_current < ain_value_goal)
  {
    event_id = EventController::event_controller.addInfiniteRecurringEvent(setChannelsOffWhenGreaterThanEventCallback,
                                                                           constants::set_until_update_period,
                                                                           set_until_index,
                                                                           setChannelsOnUntilEventCallback);
  }
  else
  {
    event_id = EventController::event_controller.addInfiniteRecurringEvent(setChannelsOffWhenLessThanEventCallback,
                                                                           constants::set_until_update_period,
                                                                           set_until_index,
                                                                           setChannelsOnUntilEventCallback);
  }
  indexed_set_untils[set_until_index].event_id =  event_id;
  modular_device.writeToResponse("set_until_index",set_until_index);
}

void setChannelsOffUntilCallback()
{
  if (indexed_set_untils.full())
  {
    modular_device.sendErrorResponse(indexed_set_untils_full_error);
    return;
  }
  ArduinoJson::JsonArray& channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  long ain = modular_device.getParameterValue(constants::ain_parameter_name);
  long ain_value_goal = modular_device.getParameterValue(constants::ain_value_parameter_name);
  SetUntilInfo set_until_info;
  set_until_info.channels = channels;
  set_until_info.ain = ain;
  set_until_info.ain_value_goal = ain_value_goal;
  set_until_info.complete = false;
  int set_until_index = indexed_set_untils.add(set_until_info);
  EventController::EventId event_id;
  int ain_value_current = controller.getAnalogInputFiltered(ain);
  if (ain_value_current < ain_value_goal)
  {
    event_id = EventController::event_controller.addInfiniteRecurringEvent(setChannelsOnWhenGreaterThanEventCallback,
                                                                           constants::set_until_update_period,
                                                                           set_until_index,
                                                                           setChannelsOffUntilEventCallback);
  }
  else
  {
    event_id = EventController::event_controller.addInfiniteRecurringEvent(setChannelsOnWhenLessThanEventCallback,
                                                                           constants::set_until_update_period,
                                                                           set_until_index,
                                                                           setChannelsOffUntilEventCallback);
  }
  indexed_set_untils[set_until_index].event_id =  event_id;
  modular_device.writeToResponse("set_until_index",set_until_index);
}

void areAllSetUntilsCompleteCallback()
{
  bool complete = true;
  for (int i=0; i<indexed_set_untils.max_size(); ++i)
  {
    if (indexed_set_untils.indexHasValue(i))
    {
      complete = complete && indexed_set_untils[i].complete;
    }
  }
  modular_device.writeToResponse("complete",complete);
}

void removeAllSetUntilsCallback()
{
  for (int i=0; i<indexed_set_untils.max_size(); ++i)
  {
    if (indexed_set_untils.indexHasValue(i))
    {
      if (!indexed_set_untils[i].complete)
      {
        EventController::event_controller.removeEvent(indexed_set_untils[i].event_id);
      }
      indexed_set_untils.remove(i);
    }
  }
}

void setChannelsOnForCallback()
{
  if (indexed_set_fors.full())
  {
    modular_device.sendErrorResponse(indexed_set_fors_full_error);
    return;
  }
  ArduinoJson::JsonArray& channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  long duration = modular_device.getParameterValue(constants::duration_parameter_name);
  SetForInfo set_for_info;
  set_for_info.channels = channels;
  set_for_info.complete = false;
  int set_for_index = indexed_set_fors.add(set_for_info);
  EventController::EventIdPair event_id_pair;
  event_id_pair = EventController::event_controller.addPwmUsingDelayPeriodOnDuration(setChannelsOnForEventCallback,
                                                                                     setChannelsOffForEventCallback,
                                                                                     200,
                                                                                     duration*2,
                                                                                     duration,
                                                                                     1,
                                                                                     set_for_index,
                                                                                     NULL,
                                                                                     completeForEventCallback);
  indexed_set_fors[set_for_index].event_id_pair =  event_id_pair;
  modular_device.writeToResponse("set_for_index",set_for_index);
}

void setChannelsOffForCallback()
{
  if (indexed_set_fors.full())
  {
    modular_device.sendErrorResponse(indexed_set_fors_full_error);
    return;
  }
  ArduinoJson::JsonArray& channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  long duration = modular_device.getParameterValue(constants::duration_parameter_name);
  SetForInfo set_for_info;
  set_for_info.channels = channels;
  set_for_info.complete = false;
  int set_for_index = indexed_set_fors.add(set_for_info);
  EventController::EventIdPair event_id_pair;
  event_id_pair = EventController::event_controller.addPwmUsingDelayPeriodOnDuration(setChannelsOffForEventCallback,
                                                                                     setChannelsOnForEventCallback,
                                                                                     200,
                                                                                     duration*2,
                                                                                     duration,
                                                                                     1,
                                                                                     set_for_index,
                                                                                     NULL,
                                                                                     completeForEventCallback);
  indexed_set_fors[set_for_index].event_id_pair =  event_id_pair;
  modular_device.writeToResponse("set_for_index",set_for_index);
}

void areAllSetForsCompleteCallback()
{
  bool complete = true;
  for (int i=0; i<indexed_set_fors.max_size(); ++i)
  {
    if (indexed_set_fors.indexHasValue(i))
    {
      complete = complete && indexed_set_fors[i].complete;
    }
  }
  modular_device.writeToResponse("complete",complete);
}

void removeAllSetForsCallback()
{
  for (int i=0; i<indexed_set_fors.max_size(); ++i)
  {
    if (indexed_set_fors.indexHasValue(i))
    {
      if (!indexed_set_fors[i].complete)
      {
        EventController::event_controller.removeEventPair(indexed_set_fors[i].event_id_pair);
      }
      indexed_set_fors.remove(i);
    }
  }
}

uint32_t arrayToChannels(ArduinoJson::JsonArray& channels_array)
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  for (ArduinoJson::JsonArray::iterator channels_it=channels_array.begin();
       channels_it != channels_array.end();
       ++channels_it)
  {
    long channel = *channels_it;
    channels |= bit << channel;
  }
  return channels;
}

// Standalone Callbacks
void executeStandaloneCallbackCallback()
{
  controller.executeStandaloneCallback();
}

void toggleChannelStandaloneCallback()
{
  uint8_t channel = controller.getChannelIntVar();
  controller.toggleChannel(channel);
}

void saveStateStandaloneCallback()
{
  uint8_t state = controller.getStateIntVar();
  controller.saveState(state);
}

void recallStateStandaloneCallback()
{
  uint8_t state = controller.getStateIntVar();
  controller.recallState(state);
}

// EventController Callbacks
void setChannelsOnUntilEventCallback(int index)
{
  controller.setChannelsOn(indexed_set_untils[index].channels);
}

void setChannelsOffUntilEventCallback(int index)
{
  controller.setChannelsOff(indexed_set_untils[index].channels);
}

void setChannelsOnForEventCallback(int index)
{
  controller.setChannelsOn(indexed_set_fors[index].channels);
}

void setChannelsOffForEventCallback(int index)
{
  controller.setChannelsOff(indexed_set_fors[index].channels);
}

void completeForEventCallback(int index)
{
  indexed_set_fors[index].complete = true;
}

void setChannelsOffWhenGreaterThanEventCallback(int index)
{
  SetUntilInfo& set_until_info = indexed_set_untils[index];
  int ain_value_current = controller.getAnalogInputFiltered(set_until_info.ain);
  if (ain_value_current >= set_until_info.ain_value_goal)
  {
    controller.setChannelsOff(set_until_info.channels);
    EventController::event_controller.removeEvent(set_until_info.event_id);
    set_until_info.complete = true;
  }
}

void setChannelsOffWhenLessThanEventCallback(int index)
{
  SetUntilInfo& set_until_info = indexed_set_untils[index];
  int ain_value_current = controller.getAnalogInputFiltered(set_until_info.ain);
  if (ain_value_current <= set_until_info.ain_value_goal)
  {
    controller.setChannelsOff(set_until_info.channels);
    EventController::event_controller.removeEvent(set_until_info.event_id);
    set_until_info.complete = true;
  }
}

void setChannelsOnWhenGreaterThanEventCallback(int index)
{
  SetUntilInfo& set_until_info = indexed_set_untils[index];
  int ain_value_current = controller.getAnalogInputFiltered(set_until_info.ain);
  if (ain_value_current >= set_until_info.ain_value_goal)
  {
    controller.setChannelsOn(set_until_info.channels);
    EventController::event_controller.removeEvent(set_until_info.event_id);
    set_until_info.complete = true;
  }
}

void setChannelsOnWhenLessThanEventCallback(int index)
{
  SetUntilInfo& set_until_info = indexed_set_untils[index];
  int ain_value_current = controller.getAnalogInputFiltered(set_until_info.ain);
  if (ain_value_current <= set_until_info.ain_value_goal)
  {
    controller.setChannelsOn(set_until_info.channels);
    EventController::event_controller.removeEvent(set_until_info.event_id);
    set_until_info.complete = true;
  }
}

void updateFilterBlockCallback(int index)
{
  uint8_t start = index*constants::filter_block_ain_count;
  uint8_t stop = (index+1)*constants::filter_block_ain_count;
  for (uint8_t ain=start;ain<stop;++ain)
  {
    controller.updateAnalogInputFilter(ain);
  }
}

}
