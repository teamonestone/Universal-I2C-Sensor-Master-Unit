#ifndef sensors_h
#define sensors_h

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

///////////
// Types //
///////////

enum SensorType {NONE, BNO055_T, VL53L0X_T, VL6180X_T, SRF08_T, CMPS10_T};

//////////////////
// Sensor-Class //
//////////////////

class Sensors
{
// Begin PUBLIC ------------------------------------------------------------------
	public:
        
        // constructor 
        Sensors();
        ~Sensors();

		// public functiuons 
		bool initNewSensor(uint8_t port, SensorType type);


// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------
	private:

		// private data structur
		union Readings {
			uint8_t byteValues[3];
			int16_t intValues[3];
			float floatVealues[3];
		};

		struct Sensor{

			// general stuff
			uint8_t port;
			SensorType type;

			// sensor object
			void *object;

			// readings
			Readings readings;

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

		// private objects
		Sensor _sensors[8];

		// private functions
		uint8_t getFreeSensor();

// End PRIVATE -------------------------------------------------------------------

};

#endif