// mixed_signal_controller
#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "JsonParser.h"
#include "Array.h"
#include "MemoryFree.h"
#include "ConstantVariable.h"
#include "SavedVariable.h"
#include "BetterMap.h"
#include "GenericSerial.h"
#include "ModularDevice.h"
#include "NewhavenDisplay.h"
#include "Encoder.h"
#include "StandaloneInterface.h"
#include "EventController.h"
#include "Constants.h"
#include "Callbacks.h"
#include "Controller.h"

#include "IndexedContainer.h"
#include "FilterSmooth.h"


// See README.md for more information

void setup()
{
  controller.setup();
}

void loop()
{
  controller.update();
}
