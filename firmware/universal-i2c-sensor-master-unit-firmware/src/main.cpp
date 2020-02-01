//////////////
// Includes //
//////////////

// system libraries
#include <Arduino.h>
#include <inttypes.h>

// global vars
#include "GlobalVars.h"

// communication libraries
#include "SMU-Communication-Backend.h"
#include "Communication.h"

// sensor stuff
#include "Sensors.h"


////////////////////
// global objects //
////////////////////

// array of sensors
Sensors MySensors;

// received message
uint8_t recMsgPayloadBuffer[25] = {0};
Message recMsg(MessageType::NONE, recMsgPayloadBuffer, 25);

/////////////
// "setup" //
/////////////

void setup() {

    // init hardware
    hardware::initHardware();

	// init global vars
	MySensors.externAutoUpdateAll = true;    
}

/////////////////
// "main loop" //
/////////////////

void loop() {
    
	// check for incomming messages
	if (communication::checkForMessage() == true) {
		communication::processRecMsg(&recMsg, &MySensors);
	}

    // perform autoupdate of sensor readings if enabled
	if (MySensors.externAutoUpdateAll == true) {
		hardware::leds::status(1);
    	MySensors.updateAllSensors();
		hardware::leds::status(0);
    }
}