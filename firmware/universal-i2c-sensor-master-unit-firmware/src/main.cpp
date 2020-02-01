#define SMU_FIRMWARE

//////////////
// Includes //
//////////////

// system libraries
#include <Arduino.h>
#include <inttypes.h>

// global vars
#include "GlobalVars.h"

// logger
#include "Logger.h"

// communication libraries
#include "SMU-Communication-Backend.h"
#include "Communication.h"

// sensor stuff
#include "Sensors.h"


////////////////
// namespaces //
////////////////

using namespace serial_logger;
using namespace smu_types::codes;


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

	writeToLog(INFO_MainLoop);   
}

/////////////////
// "main loop" //
/////////////////

void loop() {

	// check for incomming messages
	if (communication::checkForMessage() == true) {

		writeToLog(STATUS_ReadMsg);
		if (smu_com_backend::readNextMessage(&recMsg) == true) {
			writeToLog(STATUS_ProcessMsg);
			if (communication::processRecMsg(&recMsg, &MySensors) == false) {
				writeToLog(ERR_ComCouldNotProcessCurrentMsg);
			}

			writeToLog(INFO_ProcessMsgDone);
		}
		else {
			writeToLog(WARN_ComCouldNotReadIncommingMsg);
		}
	}
	else {
		writeToLog(INFO_ComNo4BytesRec);
	}

    // perform autoupdate of sensor readings if enabled
	if (MySensors.externAutoUpdateAll == true) {
		writeToLog(STATUS_UpdateSensorReadings);
    	MySensors.updateAllSensors();
    }
	else {
		writeToLog(INFO_AutoUpdateDisables);
	}

	// error led
	if (GlobalVars::SystemError != ERR_NONE || smu_com_backend::lastComErrorInfo != NO_COM_ERROR) {
		hardware::leds::error(1);

		if (smu_com_backend::lastComErrorInfo != NO_COM_ERROR) {
			writeToLog(smu_com_backend::lastComErrorInfo);
		}
	}
}