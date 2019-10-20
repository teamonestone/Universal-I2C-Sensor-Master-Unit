#ifndef sensors_h
#define sensors_h

//////////////
// Includes //
//////////////

// basic includes 
#include <inttypes.h>
#include <Arduino.h>

// sensor libs
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_VL6180X.h>
#include <SRF08.h>

/////////////
// Defines //
/////////////

#define BNO055_SAMPLERATE_DELAY_MS (100)

///////////
// Types //
///////////

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
        void activateBno055(uint8_t port, bool status);
        void activateVl53l0x(uint8_t port, bool status);
        void activateVl6180x(uint8_t port, bool status);
        void activateSrf08(uint8_t port, bool status);

        void forceUpdate();

        int getBno055Reading(uint8_t port);
        int getVl53l0xReading(uint8_t port);
        int getVl6180xReading(uint8_t port);
        int getSrf08Reading(uint8_t port);


// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------
	private:

        Adafruit_BNO055 bno055[8];
        Adafruit_VL53L0X vl53l0x[8];
        Adafruit_VL6180X vl6180x[8];
        SRF08 srf08[8];

        bool bno055Ports[8];
        bool vl53l0xPorts[8];
        bool vl6180xPorts[8];
        bool srf08Ports[8];

        bool bno055ActiveSensors[8];
        bool vl53l0xActiveSensors[8];
        bool vl6180xActiveSensors[8];
        bool srf08ActiveSensors[8];

        int bno055Readings[8];
        int vl53l0xReadings[8];
        int vl6180xReadings[8];
        int srf08Readings[8];

        void initSensors();

        void updateBno055();
        void updateVl53l0x();
        void updateVl6180x();
        void updateSrf08();

// End PRIVATE -------------------------------------------------------------------
};

#endif