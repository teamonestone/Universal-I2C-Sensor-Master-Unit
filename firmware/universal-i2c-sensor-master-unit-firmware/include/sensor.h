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

enum sensorType {NONE, US, BNO055, VL53L0X, VL6180X, CMPS10};

typedef struct Reading_t
{
    uint8_t bytes[10];
    uint64_t timeOfLastReading;
    bool errorFlag;
} Reading;


//////////////////
// Sensor-Class //
//////////////////

class Sensor
{
// Begin PUBLIC ------------------------------------------------------------------
	public:
        
        // constructor 
        Sensor();
        Sensor(sensorType type,uint8_t port);
        //~Sensor();

        // public functiuons 
        bool init();
        bool isDisabled();
        bool updateReading();

        void enable();
        void disable();
        
        Reading getCurrentReading();


// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------
	private:

        // basics 
        sensorType _type;
        uint8_t _port;
        bool _disabled;

        Reading _reading;


// End PRIVATE -------------------------------------------------------------------
};

#endif