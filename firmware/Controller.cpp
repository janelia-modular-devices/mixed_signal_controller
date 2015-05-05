// ----------------------------------------------------------------------------
// Controller.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Controller.h"

Controller::Controller() :
  standalone_interface_(Standalone::StandaloneInterface(constants::display_serial,
                                                        constants::enc_a_pin,
                                                        constants::enc_b_pin,
                                                        constants::enc_btn_pin,
                                                        constants::enc_btn_int,
                                                        constants::btn_pin,
                                                        constants::btn_int,
                                                        constants::led_pwr_pin,
                                                        constants::standalone_update_period))
{
}

void Controller::setup()
{
  // Pin Setup

  // Device Info
  modular_device.setName(constants::device_name);
  modular_device.setModelNumber(constants::model_number);
  modular_device.setFirmwareNumber(constants::firmware_number);

  // Saved Variables

  // Parameters
  ModularDevice::Parameter& ain_parameter = modular_device.createParameter(constants::ain_parameter_name);
  ain_parameter.setRange(0,constants::AIN_COUNT-1);

  // Methods
  ModularDevice::Method& execute_standalone_callback_method = modular_device.createMethod(constants::execute_standalone_callback_method_name);
  execute_standalone_callback_method.attachCallback(callbacks::executeStandaloneCallbackCallback);

  ModularDevice::Method& get_leds_powered_method = modular_device.createMethod(constants::get_leds_powered_method_name);
  get_leds_powered_method.attachCallback(callbacks::getLedsPoweredCallback);

  ModularDevice::Method& get_analog_input_method = modular_device.createMethod(constants::get_analog_input_method_name);
  get_analog_input_method.attachCallback(callbacks::getAnalogInputCallback);
  get_analog_input_method.addParameter(ain_parameter);

  ModularDevice::Method& get_analog_inputs_method = modular_device.createMethod(constants::get_analog_inputs_method_name);
  get_analog_inputs_method.attachCallback(callbacks::getAnalogInputsCallback);

  // Start Server
  modular_device.startServer(constants::baudrate);

  // Standalone Interface
  standalone_interface_.setup(constants::frame_name_array,constants::FRAME_COUNT);

  // Display Labels
  Standalone::DisplayLabel* ain_dsp_lbl_ptr_array[constants::AIN_COUNT];
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    ain_dsp_lbl_ptr_array[ain] = &(standalone_interface_.createDisplayLabel());
    ain_dsp_lbl_ptr_array[ain]->setDisplayPosition(constants::ain_dsp_lbl_display_positions[ain]);
    ain_dsp_lbl_ptr_array[ain]->setConstantString(constants::ain_dsp_lbl_strings[ain]);
    ain_dsp_lbl_ptr_array[ain]->setRightJustify();
    ain_dsp_lbl_ptr_array[ain]->setDisplayWidth(constants::ain_dsp_lbl_width);
  }

  // Display Variables
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    ain_dsp_var_ptr_array_[ain] = &(standalone_interface_.createDisplayVariable());
    ain_dsp_var_ptr_array_[ain]->setDisplayPosition(constants::ain_dsp_var_display_positions[ain]);
    ain_dsp_var_ptr_array_[ain]->setDisplayWidth(constants::percent_display_width);
  }

  // Interactive Variables

  // All Frames

  // Frame 0
  int frame = 0;
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    ain_dsp_lbl_ptr_array[ain]->addToFrame(frame);
    ain_dsp_var_ptr_array_[ain]->addToFrame(frame);
  }

  // Enable Standalone Interface
  standalone_interface_.enable();
}

void Controller::update()
{
  modular_device.handleServerRequests();
  boolean updated = standalone_interface_.update();
  if (updated)
  {
    updateDisplayVariables();
  }
}

void Controller::executeStandaloneCallback()
{
  standalone_interface_.executeCurrentFrameCallback();
}

bool Controller::getLedsPowered()
{
  return digitalRead(constants::led_pwr_pin) == HIGH;
}

uint8_t Controller::getAnalogInput(const uint8_t ain)
{
  if (ain >= constants::AIN_COUNT)
  {
    return 0;
  }
  int ain_value = analogRead(constants::ain_pins[ain]);
  int percent = betterMap(ain_value,
                          constants::ain_min,
                          constants::ain_max,
                          constants::percent_min,
                          constants::percent_max);
  return percent;
}

void Controller::updateDisplayVariables()
{
  int percent;
  for (int ain=0; ain<constants::AIN_COUNT; ain++)
  {
    percent = getAnalogInput(ain);
    ain_dsp_var_ptr_array_[ain]->setValue(percent);
  }
}

Controller controller;
