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

void resetAnalogMinMaxDefaultsCallback()
{
  controller.resetAnalogMinMaxDefaults();
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
  EventController::event_controller.removeAllEvents();
  controller.setAllChannelsOn();
}

void setAllChannelsOffCallback()
{
  EventController::event_controller.removeAllEvents();
  controller.setAllChannelsOff();
}

void setChannelsOnAllOthersOffCallback()
{
  JsonArray channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  EventController::event_controller.removeAllEvents();
  controller.setChannelsOnAllOthersOff(channels);
}

void setChannelsOffAllOthersOnCallback()
{
  JsonArray channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  EventController::event_controller.removeAllEvents();
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
    return;
  }
  JsonArray channels_array = modular_device.getParameterValue(constants::channels_parameter_name);
  uint32_t channels = arrayToChannels(channels_array);
  long ain = modular_device.getParameterValue(constants::ain_parameter_name);
  long percent = modular_device.getParameterValue(constants::percent_parameter_name);
  SetUntilInfo set_until_info;
  set_until_info.channels = channels;
  set_until_info.ain = ain;
  set_until_info.percent = percent;
  set_until_index = indexed_set_untils.add(set_until_info);
  uint8_t percent_current = controller.getAnalogInput(ain);
  // controller.setChannelsOn(channels);
  // EventId addInfiniteRecurringEvent(const Callback callback,
  //                                   const uint32_t period_ms,
  //                                   const int arg=-1,
  //                                   const Callback callback_start=NULL);
  if (percent_current < percent)
  {
    set_until_info.event_id = EventController::event_controller.addInfiniteRecurringEvent(setChannelsOffWhenGreaterThanEventCallback,
                                                                                          constants::set_until_update_period,
                                                                                          set_until_index,
                                                                                          setChannelsOnEventCallback);
  }
  else
  {
    set_until_info.event_id = EventController::event_controller.addInfiniteRecurringEvent(setChannelsOffWhenLessThanEventCallback,
                                                                                          constants::set_until_update_period,
                                                                                          set_until_index,
                                                                                          setChannelsOnEventCallback);
  }
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
}
