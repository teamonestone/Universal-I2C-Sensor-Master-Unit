// associated header
#include <Sensors.h>

Sensors::Sensors() {
    ;
}

Sensors::~Sensors() {
    ;
}

int8_t Sensors::connectSensor(uint8_t port, Sensor_T::SensorType type) {
    int8_t sensorNo = getFreeSensor();
    if (sensorNo >= SENSORS_POOL_SIZE || sensorNo < 0) {
        return -1;
    }

    bool noError = true;
    switch (type) {

        case Sensor_T::SensorType::BNO055_T:
            
            // linking pointers
            _sensors[sensorNo].object = nullptr;
            _sensors[sensorNo].init = &(SensorWrappers::SW_BNO055::init);
            _sensors[sensorNo].activate = &(SensorWrappers::SW_BNO055::activate);
            _sensors[sensorNo].deactivate = &(SensorWrappers::SW_BNO055::deactivate);
            _sensors[sensorNo].update = &(SensorWrappers::SW_BNO055::update);

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(&_sensors[sensorNo]);
            noError &= _sensors[sensorNo].activate(&_sensors[sensorNo]);
            if (!noError) {
                return -1;
            }

            break;

        case Sensor_T::SensorType::VL53L0X_T:

            // linking pointers
            _sensors[sensorNo].object = nullptr;
            _sensors[sensorNo].init = &(SensorWrappers::SW_VL53L0X::init);
            _sensors[sensorNo].activate = &(SensorWrappers::SW_VL53L0X::activate);
            _sensors[sensorNo].deactivate = &(SensorWrappers::SW_VL53L0X::deactivate);
            _sensors[sensorNo].update = &(SensorWrappers::SW_VL53L0X::update);

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(&_sensors[sensorNo]);
            noError &= _sensors[sensorNo].activate(&_sensors[sensorNo]);
            if (!noError) {
                return -1;
            }
           
            break;

        case Sensor_T::SensorType::VL6180X_T:

            // linking pointers
            _sensors[sensorNo].object = nullptr;
            _sensors[sensorNo].init = &(SensorWrappers::SW_VL6180X::init);
            _sensors[sensorNo].activate = &(SensorWrappers::SW_VL6180X::activate);
            _sensors[sensorNo].deactivate = &(SensorWrappers::SW_VL6180X::deactivate);
            _sensors[sensorNo].update = &(SensorWrappers::SW_VL6180X::update);

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(&_sensors[sensorNo]);
            noError &= _sensors[sensorNo].activate(&_sensors[sensorNo]);
            if (!noError) {
                return -1;
            }
            
            break;

        case Sensor_T::SensorType::SRF08_T:
            
            // linking pointers
            _sensors[sensorNo].object = nullptr;
            _sensors[sensorNo].init = &(SensorWrappers::SW_SRF08::init);
            _sensors[sensorNo].activate = &(SensorWrappers::SW_SRF08::activate);
            _sensors[sensorNo].deactivate = &(SensorWrappers::SW_SRF08::deactivate);
            _sensors[sensorNo].update = &(SensorWrappers::SW_SRF08::update);

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(&_sensors[sensorNo]);
            noError &= _sensors[sensorNo].activate(&_sensors[sensorNo]);
            if (!noError) {
                return -1;
            }
            
            break;

        case Sensor_T::SensorType::CMPS10_T:
        case Sensor_T::SensorType::NONE:
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

    return _sensors[sensorNo].activate(&_sensors[sensorNo]);
}

bool Sensors::deactivateSensor(int8_t sensorNo) {
    if (sensorNo >= SENSORS_POOL_SIZE || sensorNo < 0) {
        return false;
    }

    return _sensors[sensorNo].deactivate(&_sensors[sensorNo]);
}

bool Sensors::disconnectSensor(int8_t sensorNo) {
    if (sensorNo >= SENSORS_POOL_SIZE || sensorNo < 0) {
        return false;
    }

    // @ToDo
    return true;
}

bool Sensors::updateSenor(int8_t sensorNo) {
    if (sensorNo >= SENSORS_POOL_SIZE || sensorNo < 0) {
        return false;
    }

    return _sensors[sensorNo].update(&_sensors[sensorNo]);
}

bool Sensors::updateAllSensors() {
    bool noError = true;
    for (int8_t i = 0; i < SENSORS_POOL_SIZE; i++){
        if (_sensors[i].used && _sensors[i].active && !_sensors[i].busy) {
            noError &= _sensors[i].update(&_sensors[i]);
        }
    }
    return noError;
}


int8_t Sensors::getFreeSensor() {
    // @ToDo
    return 0;
}