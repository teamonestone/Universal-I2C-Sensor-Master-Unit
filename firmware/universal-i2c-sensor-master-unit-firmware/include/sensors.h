#ifndef SENSORS_h
#define SENSORS_h

//////////////
// Includes //
//////////////

// basic includes 
#include <inttypes.h>
#include <Arduino.h>

// include the sensor types and warppers
#include "Sensor_T.h"
#include "SensorWrappers.h"


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

		// public functiuons 
		int8_t connectSensor(uint8_t port, Sensor_T::SensorType type);
		bool activateSensor(int8_t sensorNo);
		bool deactivateSensor(int8_t sensorNo);
		bool disconnectSensor(int8_t sensorNo);
		bool updateSenor(int8_t sensorNo);
		bool updateAllSensors();


// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------
	private:

		// private objects
		Sensor_T::SensorCore _sensors[SENSORS_POOL_SIZE];

		// private functions
		int8_t getFreeSensor();

// End PRIVATE -------------------------------------------------------------------

};

#endif