/**
 * @file SensorWrappers.cpp
 * @brief The source file for the sensor command wrappers.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 01 November 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

// associated header
#include "SensorWrappers.h"

////////////////
// namespaces //
////////////////

using namespace serial_logger;
using namespace smu_types::codes;


////////////
// BNO055 //
////////////

bool SensorWrappers::SW_BNO055::init(Sensor_T::SensorCore *sensor) {

    bool noError = true;

    // set i2c mux port 
    hardware::i2c_mux::Instance.set_port(sensor->port);

    // create the new sensor object 
    sensor->object = OME::GetFreeObjPrt(BNO055_OBJ_SIZE, nullptr);

    // nullptr check
    if (sensor->object == nullptr) {
        return false;
    }

    *static_cast<Adafruit_BNO055*>(sensor->object) = Adafruit_BNO055(-1, BNO055_I2C_ADDRESS);

    // timing settings
    sensor->readingIntervall = BNO055_REFRESH_TIMING;

    // set sensor type
    sensor->type = smu_types::SensorType::BNO055_T;

    // sensor specific init
    noError &= static_cast<Adafruit_BNO055*>(sensor->object)->begin();
    // noError &= ... 
    static_cast<Adafruit_BNO055*>(sensor->object)->setExtCrystalUse(true);

    if (!noError) {
        // Log
        writeToLog(ERR_SensorInitBNO055);
    }

    return noError;
}
bool SensorWrappers::SW_BNO055::activate(Sensor_T::SensorCore *sensor) {

    // set the flag
    sensor->active = true;

    return true;
}
bool SensorWrappers::SW_BNO055::deactivate(Sensor_T::SensorCore *sensor) {
    
    // set the flag
    sensor->active = false;

    return true;
}
bool SensorWrappers::SW_BNO055::update(Sensor_T::SensorCore *sensor) {
    
    if (!sensor->active) {
        return false;
    }
    else if (millis() < sensor->timeOfLastReading + sensor->readingIntervall) {
        return false;
    }
    else {
        // LED
        hardware::leds::status(1);

        // set i2c mux port 
        hardware::i2c_mux::Instance.set_port(sensor->port);

        // read the sensor
        imu::Vector<3> euler = static_cast<Adafruit_BNO055*>(sensor->object)->getVector(Adafruit_BNO055::VECTOR_EULER);

        // update readings
        sensor->sensorReadings[0] = euler.x();
        sensor->sensorReadings[1] = euler.y();
        sensor->sensorReadings[2] = euler.z();

        // reset time of last reading
        sensor->timeOfLastReading = millis();
    }
    
    // LED
    hardware::leds::status(0);

    return true;
}

/*

/////////////
// VL53L0X //
/////////////

bool SensorWrappers::SW_VL53L0X::init(Sensor_T::SensorCore *sensor) {

    bool noError = true;

    // set i2c mux port 
    hardware::i2c_mux::Instance.set_port(sensor->port);

    // create the new sensor object 
    sensor->object = OME::GetFreeObjPrt(VL53L0X_OBJ_SIZE, nullptr);

    // nullptr check
    if (sensor->object == nullptr) {
        return false;
    }

    *static_cast<Adafruit_VL53L0X*>(sensor->object) = Adafruit_VL53L0X();   // <- hier geht es nicht mehr weiter mit diesem Sensor 

    // timing settings
    sensor->readingIntervall = VL53L0X_REFRESH_TIMING;

    // set sensor type
    sensor->type = smu_types::SensorType::VL53L0X_T;

    // sensor specific init
    noError &= static_cast<Adafruit_VL53L0X*>(sensor->object)->begin();

    if (!noError) {
        // Log
        writeToLog(SensorInitVL53L0X);
    }

    return noError;
}
bool SensorWrappers::SW_VL53L0X::activate(Sensor_T::SensorCore*sensor) {

    // set the flag
    sensor->active = true;

    return true;
}
bool SensorWrappers::SW_VL53L0X::deactivate(Sensor_T::SensorCore*sensor) {
    
    // set the flag
    sensor->active = false;

    return true;
}
bool SensorWrappers::SW_VL53L0X::update(Sensor_T::SensorCore*sensor) {
    
    if (!sensor->active) {
        return false;
    }
    else if (millis() < sensor->timeOfLastReading + sensor->readingIntervall) {
        return false;
    }
    else {
        // LED
        hardware::leds::status(1);

        // set i2c mux port 
        hardware::i2c_mux::Instance.set_port(sensor->port);

        // read the sensor
        VL53L0X_RangingMeasurementData_t measure;
        static_cast<Adafruit_VL53L0X*>(sensor->object)->rangingTest(&measure, false); // pass in 'true' to get debug data printout!

        // update readings
        sensor->sensorReadings[1] = measure.RangeStatus;
        if (measure.RangeStatus != 4) {  // phase failures have incorrect data
            sensor->sensorReadings[0] = measure.RangeMilliMeter;
        }
        else {
            sensor->sensorReadings[0] = -1;

            // LED
            hardware::leds::status(0);
            hardware::leds::error(1);

            // Log
            SERIAL2LOG.print("W");
            SERIAL2LOG.println(WARNINGS::Code::SensorReadingVL53L0X);

            return false;
        }
        
        // reset time of last reading
        sensor->timeOfLastReading = millis();
    }

    // LED
    hardware::leds::status(0);

    return true;
}

/////////////
// VL6180X //
/////////////

bool SensorWrappers::SW_VL6180X::init(Sensor_T::SensorCore*sensor) {

    bool noError = true;

    // set i2c mux port 
    hardware::i2c_mux::Instance.set_port(sensor->port);

    // create the new sensor object 
    sensor->object = OME::GetFreeObjPrt(VL6180X_OBJ_SIZE, nullptr);

    // nullptr check
    if (sensor->object == nullptr) {
        return false;
    }

    *static_cast<Adafruit_VL6180X*>(sensor->object) = Adafruit_VL6180X();

    // timing settings
    sensor->readingIntervall = VL6180X_REFRESH_TIMING;

    // set sensor type
    sensor->type = smu_types::SensorType::VL6180X_T;

    // sensor specific init
    noError &= static_cast<Adafruit_VL6180X*>(sensor->object)->begin();

    if (!noError) {
        // LED
        hardware::leds::error(1);

        // Log
        SERIAL2LOG.print("E");
        SERIAL2LOG.println(ERRORS::Code::SensorInitVL6180X);
    }

    return noError;
}
bool SensorWrappers::SW_VL6180X::activate(Sensor_T::SensorCore*sensor) {

    // set the flag
    sensor->active = true;

    return true;
}
bool SensorWrappers::SW_VL6180X::deactivate(Sensor_T::SensorCore*sensor) {
    
    // set the flag
    sensor->active = false;
    
    return true;
}
bool SensorWrappers::SW_VL6180X::update(Sensor_T::SensorCore*sensor) {
    
    if (!sensor->active) {
        return false;
    }
    else if (millis() < sensor->timeOfLastReading + sensor->readingIntervall) {
        return false;
    }
    else {
        // LED
        hardware::leds::status(1);

        // set i2c mux port 
        hardware::i2c_mux::Instance.set_port(sensor->port);

        // read the sensor
        uint8_t range = static_cast<Adafruit_VL6180X*>(sensor->object)->readRange();
        uint8_t status = static_cast<Adafruit_VL6180X*>(sensor->object)->readRangeStatus();

        // update readings
        sensor->sensorReadings[1] = status;
        if (status == VL6180X_ERROR_NONE) {
            sensor->sensorReadings[0] = range;
        }
        else {
            sensor->sensorReadings[0] = -1;

            // LED
            hardware::leds::status(0);
            hardware::leds::error(1);

            // Log
            SERIAL2LOG.print("W");
            SERIAL2LOG.println(WARNINGS::Code::SensorReadingVL6180X);

            return false;
        }
        
        // reset time of last reading
        sensor->timeOfLastReading = millis();
    }

    // LED
    hardware::leds::status(0);

    return true;
}

*/

///////////
// SRF08 //
///////////

bool SensorWrappers::SW_SRF08::init(Sensor_T::SensorCore*sensor) {
    bool noError = true;

    // set i2c mux port 
    hardware::i2c_mux::Instance.set_port(sensor->port);

    // create the new sensor object 
    sensor->object = OME::GetFreeObjPrt(SRF08_OBJ_SIZE, nullptr);

    // nullptr check
    if (sensor->object == nullptr) {
        return false;
    }

    // init new sensor object
    *static_cast<SRF08*>(sensor->object) = SRF08(SRF08_I2C_ADDRESS);

    // timing settings
    sensor->readingIntervall = SRF08_REFRESH_TIMING;

    // set sensor type
    sensor->type = smu_types::SensorType::SRF08_T;

    // sensor specific init
    //noError &= ...
    static_cast<SRF08*>(sensor->object)->init();

    return noError;
}
bool SensorWrappers::SW_SRF08::activate(Sensor_T::SensorCore*sensor) {
    // set i2c mux port 
    hardware::i2c_mux::Instance.set_port(sensor->port);

    // an initial measurement
    static_cast<SRF08*>(sensor->object)->init();

    // reset time of last reading
    sensor->timeOfLastReading = millis();

    // set the flag
    sensor->active = true;

    return true;
}
bool SensorWrappers::SW_SRF08::deactivate(Sensor_T::SensorCore*sensor) {
    // set the flag
    sensor->active = false;
    
    return true;
}
bool SensorWrappers::SW_SRF08::update(Sensor_T::SensorCore*sensor) {
    // check if sensor is active
    if (!sensor->active) {
        return false;
    }
    // check if reading interval is reached
    else if (millis() < sensor->timeOfLastReading + sensor->readingIntervall) {
        return false;
    }
    else {
        // LED
        hardware::leds::status(1);

        // set i2c mux port 
        hardware::i2c_mux::Instance.set_port(sensor->port);

        // read the sensor
        static_cast<SRF08*>(sensor->object)->readRangeUNSAFE();
        // update readings
        sensor->sensorReadings[0] = static_cast<SRF08*>(sensor->object)->getDistance();

        // start new measure cycle
        static_cast<SRF08*>(sensor->object)->startRangeReadingUNSAFE();
        
        // reset time of last reading
        sensor->timeOfLastReading = millis();
    }

    // LED
    hardware::leds::status(0);

    return true;
}