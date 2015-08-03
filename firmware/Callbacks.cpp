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


IndexedContainer<SetUntilInfo,constants::INDEXED_SET_UNTILS_COUNT_MAX> indexed_set_untils;
CONSTANT_STRING(indexed_set_untils_full_error,"No more available space for a new set_until, remove some to make more room.");
CONSTANT_STRING(set_until_index_invalid_error,"Invalid set_until_index, it never existed or has been removed.");

void getLedsPoweredCallback()
{
  bool leds_powered = controller.getLedsPowered();
  modular_device.addBoolToResponse("leds_powered",leds_powered);
}

void getAnalogInputCallback()
{
  long ain = modular_device.getParameterValue(constants::ain_parameter_name);
  int ain_value = controller.getAnalogInput(ain);
  modular_device.addToResponse("ain_value",ain_value);
}

void getAnalogInputsCallback()
{
  modular_device.addKeyToResponse("ain_values");
  modular_device.startResponseArray();
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    int ain_value = controller.getAnalogInput(ain);
    modular_device.addToResponse(ain_value);
  }
  modular_device.stopResponseArray();
}

void setChannelsOnCallback()
{
  JsonArray channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  controller.setChannelsOn(channels);
}

void setChannelsOffCallback()
{
  JsonArray channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  controller.setChannelsOff(channels);
}

void toggleChannelsCallback()
{
  JsonArray channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
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
  controller.setAllChannelsOn();
}

void setAllChannelsOffCallback()
{
  removeAllSetUntilsCallback();
  controller.setAllChannelsOff();
}

void setChannelsOnAllOthersOffCallback()
{
  JsonArray channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  removeAllSetUntilsCallback();
  controller.setChannelsOnAllOthersOff(channels);
}

void setChannelsOffAllOthersOnCallback()
{
  JsonArray channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  removeAllSetUntilsCallback();
  controller.setChannelsOffAllOthersOn(channels);
}

void getChannelsOnCallback()
{
  uint32_t channels_on = controller.getChannelsOn();
  uint32_t bit = 1;
  modular_device.addKeyToResponse("channels_on");
  modular_device.startResponseArray();
  for (int channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    if (channels_on & (bit << channel))
    {
      modular_device.addToResponse(channel);
    }
  }
  modular_device.stopResponseArray();
}

void getChannelsOffCallback()
{
  uint32_t channels_on = controller.getChannelsOn();
  uint32_t channels_off = ~channels_on;
  uint32_t bit = 1;
  modular_device.addKeyToResponse("channels_off");
  modular_device.startResponseArray();
  for (int channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    if (channels_off & (bit << channel))
    {
      modular_device.addToResponse(channel);
    }
  }
  modular_device.stopResponseArray();
}

void getChannelCountCallback()
{
  int channel_count = controller.getChannelCount();
  modular_device.addToResponse("channel_count",channel_count);
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
  modular_device.addKeyToResponse("saved_states");
  modular_device.startResponseArray();
  for (int state=0; state<constants::STATE_COUNT; state++)
  {
    modular_device.startResponseArray();
    for (int channel=0; channel<=(constants::CHANNEL_COUNT-1); channel++)
    {
      if ((bit<<channel) & states_array[state])
      {
        modular_device.addToResponse("on");
      }
      else
      {
        modular_device.addToResponse("off");
      }
    }
    modular_device.stopResponseArray();
  }
  modular_device.stopResponseArray();
}

void setChannelsOnUntilCallback()
{
  if (indexed_set_untils.full())
  {
    modular_device.sendErrorResponse(indexed_set_untils_full_error);
    return;
  }
  JsonArray channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
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
  int ain_value_current = controller.getAnalogInput(ain);
  if (ain_value_current < ain_value_goal)
  {
    event_id = EventController::event_controller.addInfiniteRecurringEvent(setChannelsOffWhenGreaterThanEventCallback,
                                                                           constants::set_until_update_period,
                                                                           set_until_index,
                                                                           setChannelsOnEventCallback);
  }
  else
  {
    event_id = EventController::event_controller.addInfiniteRecurringEvent(setChannelsOffWhenLessThanEventCallback,
                                                                           constants::set_until_update_period,
                                                                           set_until_index,
                                                                           setChannelsOnEventCallback);
  }
  indexed_set_untils[set_until_index].event_id =  event_id;
  modular_device.addToResponse("set_until_index",set_until_index);
}

void setChannelsOffUntilCallback()
{
  if (indexed_set_untils.full())
  {
    modular_device.sendErrorResponse(indexed_set_untils_full_error);
    return;
  }
  JsonArray channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
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
  int ain_value_current = controller.getAnalogInput(ain);
  if (ain_value_current < ain_value_goal)
  {
    event_id = EventController::event_controller.addInfiniteRecurringEvent(setChannelsOnWhenGreaterThanEventCallback,
                                                                           constants::set_until_update_period,
                                                                           set_until_index,
                                                                           setChannelsOffEventCallback);
  }
  else
  {
    event_id = EventController::event_controller.addInfiniteRecurringEvent(setChannelsOnWhenLessThanEventCallback,
                                                                           constants::set_until_update_period,
                                                                           set_until_index,
                                                                           setChannelsOffEventCallback);
  }
  indexed_set_untils[set_until_index].event_id =  event_id;
  modular_device.addToResponse("set_until_index",set_until_index);
}

void isSetUntilCompleteCallback()
{
  long set_until_index = modular_device.getParameterValue(constants::set_until_index_parameter_name);
  if (indexed_set_untils.indexHasValue(set_until_index))
  {
    modular_device.addBoolToResponse("complete",indexed_set_untils[set_until_index].complete);
  }
  else
  {
    modular_device.sendErrorResponse(set_until_index_invalid_error);
  }
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
  modular_device.addBoolToResponse("complete",complete);
}

void removeSetUntilCallback()
{
  long set_until_index = modular_device.getParameterValue(constants::set_until_index_parameter_name);
  if (!indexed_set_untils[set_until_index].complete)
  {
    EventController::event_controller.removeEvent(indexed_set_untils[set_until_index].event_id);
  }
  indexed_set_untils.remove(set_until_index);
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

void getAllSetUntilIndexesCallback()
{
  uint32_t channels_on = controller.getChannelsOn();
  uint32_t bit = 1;
  modular_device.addKeyToResponse("set_until_indexes");
  modular_device.startResponseArray();
  for (int i=0; i<indexed_set_untils.max_size(); ++i)
  {
    if (indexed_set_untils.indexHasValue(i))
    {
      modular_device.addToResponse(i);
    }
  }
  modular_device.stopResponseArray();
}

uint32_t arrayToChannels(JsonArray channels_array)
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  for (JsonArrayIterator channels_it=channels_array.begin();
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
void setChannelsOnEventCallback(int index)
{
  controller.setChannelsOn(indexed_set_untils[index].channels);
}

void setChannelsOffEventCallback(int index)
{
  controller.setChannelsOff(indexed_set_untils[index].channels);
}

void setChannelsOffWhenGreaterThanEventCallback(int index)
{
  SetUntilInfo& set_until_info = indexed_set_untils[index];
  int ain_value_current = controller.getAnalogInput(set_until_info.ain);
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
  int ain_value_current = controller.getAnalogInput(set_until_info.ain);
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
  int ain_value_current = controller.getAnalogInput(set_until_info.ain);
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
  int ain_value_current = controller.getAnalogInput(set_until_info.ain);
  if (ain_value_current <= set_until_info.ain_value_goal)
  {
    controller.setChannelsOn(set_until_info.channels);
    EventController::event_controller.removeEvent(set_until_info.event_id);
    set_until_info.complete = true;
  }
}

}
