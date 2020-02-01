#ifndef SENSORS_h
#define SENSORS_h

//////////////
// Includes //
//////////////

// basic Includes
#include <Arduino.h>
#include <inttypes.h>

// smu types
#include "SMU-Types.h"

// logger 
#include "Logger.h"

// the sensor types and warppers
#include "Sensor_T.h"
#include "SensorWrappers.h"
#include "Hardware.h"


/////////////
// Defines //
/////////////

#define SENSORS_POOL_SIZE 8				///< Defines how many different sensors can be connected at any time.


///////////
// Class //
///////////

/**
 * @class Sensors
 * 
 * @brief Class for managing the different sensors
 */
class Sensors
{
// Begin PUBLIC ------------------------------------------------------------------
	public:
        
        // constructor 
        Sensors();
        ~Sensors();

		// public variables
		bool externAutoUpdateAll;

		// public functions 
		int8_t connectSensor(uint8_t port, smu_types::SensorType type);
		bool activateSensor(int8_t sensorNo);
		bool deactivateSensor(int8_t sensorNo);
		bool isActive(int8_t sensorNo);
		bool disconnectSensor(int8_t sensorNo);
		bool updateSensor(int8_t sensorNo);
		bool updateAllSensors();
		float getReading(int8_t sensorNo, uint8_t valueNo);

// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------
	private:

		// private objects
		Sensor_T::SensorCore _sensors[SENSORS_POOL_SIZE];

		// private functions
		int8_t getFreeSensor();
		bool checkForRange(int8_t sensorNo);
		bool resetSensor(int8_t sensorNo);

// End PRIVATE -------------------------------------------------------------------

};

#endif