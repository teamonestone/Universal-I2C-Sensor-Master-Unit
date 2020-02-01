// associated header
#include "Sensors.h"

// defines
//#define SENSORS_LOCAL_FINE_DEBUG

// used namespaces
using namespace serial_logger;
using namespace smu_types::codes;


Sensors::Sensors() {
    externAutoUpdateAll = true;

    for (int8_t i = 0; i < SENSORS_POOL_SIZE; i++) {
        resetSensor(i);
    }
}

Sensors::~Sensors() {
    ;
}

int8_t Sensors::connectSensor(uint8_t port, smu_types::SensorType type) {
    // get next free sensor number 
    int8_t sensorNo = getFreeSensor();

    // check for valid sensor number
    if (!checkForRange(sensorNo)) {
        return -1;
    }

    #ifdef SENSORS_LOCAL_FINE_DEBUG
    // "string" for sprintf
    char s[16] = {0};
    #endif

    // set sensor port
    _sensors[sensorNo].port = port;

    bool noError = true;
    // switch sensor type
    switch (type) {

        case smu_types::SensorType::BNO055_T:
            writeToLog(STATUS_Sensors_Init_BNO055);

            // linking pointers
            _sensors[sensorNo].init = &(SensorWrappers::SW_BNO055::init);
            _sensors[sensorNo].activate = &(SensorWrappers::SW_BNO055::activate);
            _sensors[sensorNo].deactivate = &(SensorWrappers::SW_BNO055::deactivate);
            _sensors[sensorNo].update = &(SensorWrappers::SW_BNO055::update);

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(&_sensors[sensorNo]);
            if (noError) {
                noError &= _sensors[sensorNo].activate(&_sensors[sensorNo]);
            }
            if (!noError) {
                return -1;
            }

            #ifdef SENSORS_LOCAL_FINE_DEBUG
            sprintf(s, "%p", _sensors[sensorNo].object);
            SERIAL2LOG.print("Init BNO055 on Port ");
            SERIAL2LOG.print(port);
            SERIAL2LOG.print(" at Sensor No. ");
            SERIAL2LOG.print(sensorNo);
            SERIAL2LOG.print(" and Object Ptr ");
            SERIAL2LOG.println(s);
            #endif

        break;
        
        /*
        case smu_types::SensorType::VL53L0X_T:
            writeToLog(STATUS_Sensors_Init_VL53L0X);

            // linking pointers
            _sensors[sensorNo].init = &(SensorWrappers::SW_VL53L0X::init);
            _sensors[sensorNo].activate = &(SensorWrappers::SW_VL53L0X::activate);
            _sensors[sensorNo].deactivate = &(SensorWrappers::SW_VL53L0X::deactivate);
            _sensors[sensorNo].update = &(SensorWrappers::SW_VL53L0X::update);

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(&_sensors[sensorNo]);
            if (noError) {
                noError &= _sensors[sensorNo].activate(&_sensors[sensorNo]);
            }
            if (!noError) {
                return -1;
            }
           
            #ifdef SENSORS_LOCAL_FINE_DEBUG
            sprintf(s, "%p", _sensors[sensorNo].object);
            SERIAL2LOG.print("Init VL53L0X on Port ");
            SERIAL2LOG.print(port);
            SERIAL2LOG.print(" at Sensor No. ");
            SERIAL2LOG.print(sensorNo);
            SERIAL2LOG.print(" and Object Ptr ");
            SERIAL2LOG.println(s);
            #endif

        break;

        case smu_types::SensorType::VL6180X_T:
            writeToLog(STATUS_Sensors_Init_VL6180X);

            // linking pointers
            _sensors[sensorNo].init = &(SensorWrappers::SW_VL6180X::init);
            _sensors[sensorNo].activate = &(SensorWrappers::SW_VL6180X::activate);
            _sensors[sensorNo].deactivate = &(SensorWrappers::SW_VL6180X::deactivate);
            _sensors[sensorNo].update = &(SensorWrappers::SW_VL6180X::update);

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(&_sensors[sensorNo]);
            if (noError) {
                noError &= _sensors[sensorNo].activate(&_sensors[sensorNo]);
            }
            if (!noError) {
                return -1;
            }

            #ifdef SENSORS_LOCAL_FINE_DEBUG
            sprintf(s, "%p", _sensors[sensorNo].object);
            SERIAL2LOG.print("Init VL6180X on Port ");
            SERIAL2LOG.print(port);
            SERIAL2LOG.print(" at Sensor No. ");
            SERIAL2LOG.print(sensorNo);
            SERIAL2LOG.print(" and Object Ptr ");
            SERIAL2LOG.println(s);
            #endif
            
        break;

        */
        case smu_types::SensorType::SRF08_T:
            writeToLog(STATUS_Sensors_Init_SRF08);

            // linking pointers
            _sensors[sensorNo].init = &(SensorWrappers::SW_SRF08::init);
            _sensors[sensorNo].activate = &(SensorWrappers::SW_SRF08::activate);
            _sensors[sensorNo].deactivate = &(SensorWrappers::SW_SRF08::deactivate);
            _sensors[sensorNo].update = &(SensorWrappers::SW_SRF08::update);

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(&_sensors[sensorNo]);
            if (noError) {
                noError &= _sensors[sensorNo].activate(&_sensors[sensorNo]);
            }
            if (!noError) {
                return -1;
            }
            
            #ifdef SENSORS_LOCAL_FINE_DEBUG
            sprintf(s, "%p", _sensors[sensorNo].object);
            SERIAL2LOG.print("Init SRF08 on Port ");
            SERIAL2LOG.print(port);
            SERIAL2LOG.print(" at Sensor No. ");
            SERIAL2LOG.print(sensorNo);
            SERIAL2LOG.print(" and Object Ptr ");
            SERIAL2LOG.println(s);
            #endif

        break;

        case smu_types::SensorType::NONE:
        default:
            return -1;
        break;
    }
    
    return sensorNo;
}

bool Sensors::activateSensor(int8_t sensorNo) {
    writeToLog(INFO_Sensors_activateSensor);
    if (!checkForRange(sensorNo)) {
        return false;
    }
    return _sensors[sensorNo].activate(&_sensors[sensorNo]);
}

bool Sensors::deactivateSensor(int8_t sensorNo) {
    writeToLog(INFO_Sensors_deactivateSensor);
    if (sensorNo >= SENSORS_POOL_SIZE || sensorNo < 0) {
        return false;
    }
    return _sensors[sensorNo].deactivate(&_sensors[sensorNo]);
}

bool Sensors::isActive(int8_t sensorNo) {
    writeToLog(INFO_Sensors_isActive);
    if (sensorNo >= SENSORS_POOL_SIZE || sensorNo < 0) {
        return false;
    }
    return _sensors[sensorNo].active;
}

bool Sensors::disconnectSensor(int8_t sensorNo) {
    writeToLog(INFO_Sensors_disconnectSensor);
    if (!checkForRange(sensorNo)) {
        return false;
    }
    return resetSensor(sensorNo);
}

bool Sensors::updateSensor(int8_t sensorNo) {
    writeToLog(INFO_Sensors_updateSensor);
     if (!checkForRange(sensorNo)) {
        return false;
    }
    return _sensors[sensorNo].update(&_sensors[sensorNo]);
}

bool Sensors::updateAllSensors() {
    writeToLog(INFO_Sensors_updateAllSensors);
    bool noError = true;
    for (int8_t i = 0; i < SENSORS_POOL_SIZE; i++){
        if (_sensors[i].type != smu_types::SensorType::NONE && _sensors[i].active) {
            noError &= _sensors[i].update(&_sensors[i]);
        }
    }
    return noError;
}

float Sensors::getReading(int8_t sensorNo, uint8_t valueNo) {
    writeToLog(INFO_Sensors_getReading);
    if (!checkForRange(sensorNo) || valueNo >= SENSORS_READING_VECT_SIZE) {
        return -1;
    }
    return _sensors[sensorNo].sensorReadings[valueNo];
}

bool Sensors::checkForRange(int8_t sensorNo) {
    if (sensorNo >= SENSORS_POOL_SIZE || sensorNo < 0) {
        return false;
    }
    else {
        return true;
    }
}

bool Sensors::resetSensor(int8_t sensorNo) {
    if (!checkForRange(sensorNo)) {
        return false;
    }

    _sensors[sensorNo].type = smu_types::SensorType::NONE;

    _sensors[sensorNo].active = false;

    _sensors[sensorNo].object = nullptr;
    _sensors[sensorNo].activate = nullptr;
    _sensors[sensorNo].deactivate = nullptr;
    _sensors[sensorNo].init = nullptr;
    _sensors[sensorNo].update = nullptr;

    _sensors[sensorNo].port = 255;

    _sensors[sensorNo].readingIntervall = 100;
    _sensors[sensorNo].timeOfLastReading = 0;

    _sensors[sensorNo].sensorReadings[0] = 0;
    _sensors[sensorNo].sensorReadings[1] = 0;
    _sensors[sensorNo].sensorReadings[2] = 0;

    return true;
}

int8_t Sensors::getFreeSensor() {
    int8_t res = -1;
    for (int8_t i = 0; i < SENSORS_POOL_SIZE; i++) {
        if (!_sensors[i].type != smu_types::SensorType::NONE) {
            res = i;
            break;
        }
    }
    return res;
}