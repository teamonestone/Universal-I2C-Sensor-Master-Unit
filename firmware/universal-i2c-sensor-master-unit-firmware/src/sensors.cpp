// associated header
#include <Sensors.h>

// include
#include <SensorWrappers.h>

// namespaces
using namespace SensorWrappers;


Sensors::Sensors() {
    ;
}

Sensors::~Sensors() {
    ;
}

int8_t Sensors::connectSensor(uint8_t port, SensorType type) {
    int8_t sensorNo = getFreeSensor();
    if (sensorNo >= SENSORS_POOL_SIZE || sensorNo < 0) {
        return -1;
    }

    bool noError = true;
    switch (type) {

        case BNO055_T:

            // create the new sensor object 
            Adafruit_BNO055 *_BNO055 = (Adafruit_BNO055*) OME::GetFreeObjPrt(nullptr);
            *_BNO055 = Adafruit_BNO055();

            // linking pointers
            _sensors[sensorNo].object = _BNO055;
            _sensors[sensorNo].init = &(SW_BNO055::init);
            _sensors[sensorNo].activate = &(SW_BNO055::activate);
            _sensors[sensorNo].deactivate = &(SW_BNO055::deactivate);
            _sensors[sensorNo].update = &(SW_BNO055::update);

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(_sensors[sensorNo]);
            noError &= _sensors[sensorNo].activate(_sensors[sensorNo]);
            if (!noError) {
                return -1;
            }

            break;

        case VL53L0X_T:

            // create the new sensor object 
            Adafruit_VL53L0X *_VL53L0X = (Adafruit_VL53L0X*) OME::GetFreeObjPrt(nullptr);
            *_VL53L0X = Adafruit_VL53L0X();

            // linking pointers
            _sensors[sensorNo].object = _VL53L0X;
            _sensors[sensorNo].init = &(SW_VL53L0X::init);
            _sensors[sensorNo].activate = &(SW_VL53L0X::activate);
            _sensors[sensorNo].deactivate = &(SW_VL53L0X::deactivate);
            _sensors[sensorNo].update = &(SW_VL53L0X::update);

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(_sensors[sensorNo]);
            noError &= _sensors[sensorNo].activate(_sensors[sensorNo]);
            if (!noError) {
                return -1;
            }
           
            break;

        case VL6180X_T:

            // create the new sensor object 
            Adafruit_VL6180X *_VL6180X = (Adafruit_VL6180X*) OME::GetFreeObjPrt(nullptr);
            *_VL6180X = Adafruit_VL6180X();

            // linking pointers
            _sensors[sensorNo].object = _VL6180X;
            _sensors[sensorNo].init = &(SW_VL6180X::init);
            _sensors[sensorNo].activate = &(SW_VL6180X::activate);
            _sensors[sensorNo].deactivate = &(SW_VL6180X::deactivate);
            _sensors[sensorNo].update = &(SW_VL6180X::update);

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(_sensors[sensorNo]);
            noError &= _sensors[sensorNo].activate(_sensors[sensorNo]);
            if (!noError) {
                return -1;
            }
            
            break;

        case SRF08_T:

            // create the new sensor object 
            SRF08 *_SRF08 = (SRF08*) OME::GetFreeObjPrt(nullptr);
            *_SRF08 = SRF08();

            // linking pointers
            _sensors[sensorNo].object = _SRF08;
            _sensors[sensorNo].init = &(SW_SRF08::init);
            _sensors[sensorNo].activate = &(SW_SRF08::activate);
            _sensors[sensorNo].deactivate = &(SW_SRF08::deactivate);
            _sensors[sensorNo].update = &(SW_SRF08::update);

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(_sensors[sensorNo]);
            noError &= _sensors[sensorNo].activate(_sensors[sensorNo]);
            if (!noError) {
                return -1;
            }
            
            break;

        case CMPS10_T:
        case NONE:
        default:
            return -1;
            break;
    }

    return sensorNo;
}

bool Sensors::activateSensor(int8_t sensorNo) {
    if (sensorNo >= SENSORS_POOL_SIZE || sensorNo < 0) {
        return false;
    }

    return _sensors[sensorNo].activate(_sensors[sensorNo]);
}

bool Sensors::deactivateSensor(int8_t sensorNo) {
    if (sensorNo >= SENSORS_POOL_SIZE || sensorNo < 0) {
        return false;
    }

    return _sensors[sensorNo].deactivate(_sensors[sensorNo]);
}

bool Sensors::disconnectSensor(int8_t sensorNo) {
    if (sensorNo >= SENSORS_POOL_SIZE || sensorNo < 0) {
        return false;
    }

    // @ToDo
}

bool Sensors::updateSenor(int8_t sensorNo) {
    if (sensorNo >= SENSORS_POOL_SIZE || sensorNo < 0) {
        return false;
    }

    return _sensors[sensorNo].update(_sensors[sensorNo]);
}

bool Sensors::updateAllSensors() {
    bool noError = true;
    for (int8_t i = 0; i < SENSORS_POOL_SIZE; i++){
        if (_sensors[i].used && _sensors[i].active && !_sensors[i].busy) {
            noError &= _sensors[i].update(_sensors[i]);
        }
    }
    return noError;
}


int8_t Sensors::getFreeSensor() {
    // @ToDo
    return 0;
}