// associated header
#include <sensor.h>

// sensor libraries
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_VL6180X.h>
#include <SRF08.h>

// i2c mux library
#include <TCA9548A.h>

TCA9548A mux;

Sensor::Sensor() {
    _type = NONE;
    _port = 255;
    _disabled = true;
}

Sensor::Sensor(sensorType type,uint8_t port) {

    _type = type;
    _port = port;
    _disabled = true;
}


bool Sensor::init() {
    
    mux.set_port(_port);

    switch (_type)
    {
        case US:
            /* code */
            break;
        
        case BNO055:
            /* code */
            break;
        
        case VL53L0X:
            /* code */
            break;
        
        case VL6180X:
            /* code */
            break;
        
        case CMPS10:
            /* code */
            break;
    
        default:
            mux.disable();
            return false;
    }

    mux.disable();
    
    return true;
}

bool Sensor::isDisabled() {
    return _disabled;
}

bool Sensor::updateReading() {

    mux.set_port(_port);

    mux.disable();

    return true;
}


void Sensor::enable() {
    _disabled = false;
}

void Sensor::disable() {
    _disabled = true;
}


Reading Sensor::getCurrentReading() {
    return _reading;
}