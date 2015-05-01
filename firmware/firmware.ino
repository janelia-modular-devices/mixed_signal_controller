// mixed_signal_controller
#ifdef __AVR__
#include "Flash.h"
#include <EEPROM.h>
#endif
#include "Streaming.h"
#include "JsonParser.h"
#include "Array.h"
#include "MemoryFree.h"
#include "ConstantVariable.h"
#include "SavedVariable.h"
#include "BetterMap.h"
#include "ModularDevice.h"
#include "NewhavenDisplay.h"
#include "Encoder.h"
#include "StandaloneInterface.h"
#include "EventController.h"
#include "Constants.h"
#include "Callbacks.h"
#include "Controller.h"

#include "SPI.h"
#include "PowerSwitch.h"
#include "IndexedContainer.h"


// See README.md for more information

void setup()
{
  controller.setup();
}

void loop()
{
  controller.update();
}