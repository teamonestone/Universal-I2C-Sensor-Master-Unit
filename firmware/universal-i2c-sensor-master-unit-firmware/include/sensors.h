#ifndef SENSORS_h
#define SENSORS_h

//////////////
// Includes //
//////////////

// basic includes 
#include <inttypes.h>
#include <Arduino.h>

// memory management
#include <ObjectManagementEngine.h>

// sensor libs
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_VL6180X.h>
#include <SRF08.h>

/////////////
// Defines //
/////////////
#define SENSORS_POOL_SIZE 8				///< Defines how many different sensors can be connected at any time.
#define SENSORS_READING_VECT_SIZE 4		///< Defines how many different reading values a sensor can provide.

///////////
// Types //
///////////

enum SensorType {NONE, BNO055_T, VL53L0X_T, VL6180X_T, SRF08_T, CMPS10_T};

//////////////////
// Sensor-Class //
//////////////////

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
		

		// data structur for a sensor
		struct Sensor{

			// general stuff
			uint8_t port;
			SensorType type;

			// sensor object
			void *object;

			// readings
			float sensorReadings[SENSORS_READING_VECT_SIZE];

			// timing
			uint32_t timeOfLastReading;
			uint32_t readingIntervall;
			
			// flags
			bool busy;
			bool active;
			bool used;

			// functions
			bool (*init)(Sensor);
			bool (*activate)(Sensor);
			bool (*deactivate)(Sensor);
			bool (*update)(Sensor);
		};

		// public functiuons 
		int8_t connectSensor(uint8_t port, SensorType type);
		bool activateSensor(int8_t sensorNo);
		bool deactivateSensor(int8_t sensorNo);
		bool disconnectSensor(int8_t sensorNo);
		bool updateSenor(int8_t sensorNo);
		bool updateAllSensors();


// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------
	private:

		// private objects
		Sensor _sensors[SENSORS_POOL_SIZE];

		// private functions
		int8_t getFreeSensor();

// End PRIVATE -------------------------------------------------------------------

};

#endif