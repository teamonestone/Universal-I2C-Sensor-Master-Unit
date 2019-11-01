/**
 * @file SensorWrappers.cpp
 * @brief The sours file for the sensor command wrappers.
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
#include <SensorWrappers.h>

////////////
// BNO055 //
////////////

bool SensorWrappers::SW_BNO055::init(Sensor_T::SensorCore *sensor) {

    bool noError = true;

    // timing settigns
    sensor->readingIntervall = BNO055_REFRESH_TIMING;
    sensor->timeOfLastReading = 0;

    // reset readings
    sensor->sensorReadings[0] = -1;
    sensor->sensorReadings[1] = -1;
    sensor->sensorReadings[2] = -1;

    // set i2c mux port 
    Hardware::I2C_MUX::Instance.set_port(sensor->port);

    // create the new sensor object 
    sensor->object = OME::GetFreeObjPrt(nullptr);
    *static_cast<Adafruit_BNO055*>(sensor->object) = Adafruit_BNO055(-1, BNO055_I2C_ADDRESS);

    // sensor specific init
    noError &= static_cast<Adafruit_BNO055*>(sensor->object)->begin();
    /*noError &=*/ static_cast<Adafruit_BNO055*>(sensor->object)->setExtCrystalUse(true);

    if (!noError) {
        // LED
        Hardware::LEDs::error(1);

        // Log
        Hardware::SoftSerial::Instance.begin(9600);
        Hardware::SoftSerial::Instance.println("[Error]: BNO055 init faild!");
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
        // set busy flag 
        sensor->busy = true;
        return false;
    }
    else {
        // set busy flag 
        sensor->busy = false;

        // LED
        Hardware::LEDs::status(1);

        // set i2c mux port 
        Hardware::I2C_MUX::Instance.set_port(sensor->port);

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
    Hardware::LEDs::status(0);

    return true;
}

/////////////
// VL53L0X //
/////////////

bool SensorWrappers::SW_VL53L0X::init(Sensor_T::SensorCore *sensor) {

    bool noError = true;

    // timing settigns
    sensor->readingIntervall = VL53L0X_REFRESH_TIMING;
    sensor->timeOfLastReading = 0;

    // reset readings
    sensor->sensorReadings[0] = -1;
    sensor->sensorReadings[1] = -1;
    sensor->sensorReadings[2] = -1;

    // set i2c mux port 
    Hardware::I2C_MUX::Instance.set_port(sensor->port);

    // create the new sensor object 
    sensor->object = OME::GetFreeObjPrt(nullptr);
    *static_cast<Adafruit_VL53L0X*>(sensor->object) = Adafruit_VL53L0X();

    // sensor specific init
    noError &= static_cast<Adafruit_VL53L0X*>(sensor->object)->begin();

    if (!noError) {
        // LED
        Hardware::LEDs::error(1);

        // Log
        Hardware::SoftSerial::Instance.begin(9600);
        Hardware::SoftSerial::Instance.println("[Error]: VL53L0X init faild!");
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
        // set busy flag 
        sensor->busy = true;
        return false;
    }
    else {
        // set busy flag 
        sensor->busy = false;

        // LED
        Hardware::LEDs::status(1);

        // set i2c mux port 
        Hardware::I2C_MUX::Instance.set_port(sensor->port);

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
            Hardware::LEDs::status(0);
            Hardware::LEDs::error(1);

            // Log
            Hardware::SoftSerial::Instance.begin(9600);
            Hardware::SoftSerial::Instance.println("[Error]: VL53L0X reading faild!");

            return false;
        }
        
        // reset time of last reading
        sensor->timeOfLastReading = millis();
    }

    // LED
    Hardware::LEDs::status(0);

    return true;
}

/////////////
// VL6180X //
/////////////

bool SensorWrappers::SW_VL6180X::init(Sensor_T::SensorCore*sensor) {

    bool noError = true;

    // timing settigns
    sensor->readingIntervall = VL6180X_REFRESH_TIMING;
    sensor->timeOfLastReading = 0;

    // reset readings
    sensor->sensorReadings[0] = -1;
    sensor->sensorReadings[1] = -1;
    sensor->sensorReadings[2] = -1;

    // set i2c mux port 
    Hardware::I2C_MUX::Instance.set_port(sensor->port);

    // create the new sensor object 
    sensor->object = OME::GetFreeObjPrt(nullptr);
    *static_cast<Adafruit_VL6180X*>(sensor->object) = Adafruit_VL6180X();

    // sensor specific init
    noError &= static_cast<Adafruit_VL6180X*>(sensor->object)->begin();

    if (!noError) {
        // LED
        Hardware::LEDs::error(1);

        // Log
        Hardware::SoftSerial::Instance.begin(9600);
        Hardware::SoftSerial::Instance.println("[Error]: VL6180X init faild!");
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
        // set busy flag 
        sensor->busy = true;
        return false;
    }
    else {
        // set busy flag 
        sensor->busy = false;

        // LED
        Hardware::LEDs::status(1);

        // set i2c mux port 
        Hardware::I2C_MUX::Instance.set_port(sensor->port);

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
            Hardware::LEDs::status(0);
            Hardware::LEDs::error(1);

            // Log
            Hardware::SoftSerial::Instance.begin(9600);
            Hardware::SoftSerial::Instance.println("[Error]: VL6180X reading faild!");

            return false;
        }
        
        // reset time of last reading
        sensor->timeOfLastReading = millis();
    }

    // LED
    Hardware::LEDs::status(0);

    return true;
}

///////////
// SRF08 //
///////////

bool SensorWrappers::SW_SRF08::init(Sensor_T::SensorCore*sensor) {

    bool noError = true;

    // timing settigns
    sensor->readingIntervall = SRF08_REFRESH_TIMING;
    sensor->timeOfLastReading = 0;

    // reset readings
    sensor->sensorReadings[0] = -1;
    sensor->sensorReadings[1] = -1;
    sensor->sensorReadings[2] = -1;

    // set i2c mux port 
    Hardware::I2C_MUX::Instance.set_port(sensor->port);

    // create the new sensor object 
    sensor->object = OME::GetFreeObjPrt(nullptr);
    *static_cast<SRF08*>(sensor->object) = SRF08(SRF08_I2C_ADDRESS);

    // sensor specific init
    /*noError &=*/ static_cast<SRF08*>(sensor->object)->init();

    return noError;
}
bool SensorWrappers::SW_SRF08::activate(Sensor_T::SensorCore*sensor) {

    // set i2c mux port 
    Hardware::I2C_MUX::Instance.set_port(sensor->port);

    // an initial measurment
    static_cast<SRF08*>(sensor->object)->readRangeUNSAFE();

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
    
    if (!sensor->active) {
        return false;
    }
    else if (millis() < sensor->timeOfLastReading + sensor->readingIntervall) {
        // set busy flag 
        sensor->busy = true;
        return false;
    }
    else {
        // set busy flag 
        sensor->busy = false;

        // LED
        Hardware::LEDs::status(1);

        // set i2c mux port 
        Hardware::I2C_MUX::Instance.set_port(sensor->port);

        // read the sensor
        // update readings
        sensor->sensorReadings[0] = static_cast<SRF08*>(sensor->object)->getDistance();

        // start new measure cycle
        static_cast<SRF08*>(sensor->object)->readRangeUNSAFE();
        
        // reset time of last reading
        sensor->timeOfLastReading = millis();
    }

    // LED
    Hardware::LEDs::status(0);

    return true;
}