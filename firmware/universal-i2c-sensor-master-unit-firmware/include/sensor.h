#ifndef sensor_h
#define sensor_h

//////////////
// Includes //
//////////////

// basic includes 
#include <inttypes.h>
#include <Arduino.h>

/////////////
// Defines //
/////////////


///////////
// Types //
///////////

enum sensorType {US, BNO055, VL53L0X, VL6180X, CMPS10};

typedef struct Reading
{
    uint8_t bytes[10];
    uint64_t timeOfLastReading;
    bool errorFlag;
};


//////////////////
// Sensor-Class //
//////////////////

class Sensor
{
// Begin PUBLIC ------------------------------------------------------------------
	public:
        
        // constructor 
        Sensor(sensorType type,uint8_t port);
        ~Sensor();

        // public functiuons 

// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------
	private:

        // basics 
        uint8_t _port;

        Reading _reading;


// End PRIVATE -------------------------------------------------------------------
};

#endif