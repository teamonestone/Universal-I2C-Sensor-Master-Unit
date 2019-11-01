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

// includes 
#include <SensorWrappers.h>

// Defines
#define BNO055_REFRESH_TIMING 100
#define BNO055_I2C_ADDRESS 0x28

#define VL53L0X_REFRESH_TIMING 100
//#define VL53L0X_I2C_ADDRESS 

#define VL6180X_REFRESH_TIMING 100
//#define VL6180X_I2C_ADDRESS 

#define SRF08_REFRESH_TIMING 100
#define SRF08_I2C_ADDRESS 112

// namesapce
using namespace SensorWrappers;

////////////
// BNO055 //
////////////

bool SW_BNO055::init(Sensor_T::SensorCore *sensor) {

    bool noError = true;

    // timing settigns
    sensor->readingIntervall = BNO055_REFRESH_TIMING;
    sensor->timeOfLastReading = 0;

    // create the new sensor object 
    sensor->object = OME::GetFreeObjPrt(nullptr);
    *static_cast<Adafruit_BNO055*>(sensor->object) = Adafruit_BNO055(-1, BNO055_I2C_ADDRESS);

    // sensor specific init
    noError &= static_cast<Adafruit_BNO055*>(sensor->object)->begin();

    return noError;
}
bool SW_BNO055::activate(Sensor_T::SensorCore *sensor){

    return true;
}
bool SW_BNO055::deactivate(Sensor_T::SensorCore *sensor) {

    return true;
}
bool SW_BNO055::update(Sensor_T::SensorCore *sensor) {

    return true;
}

/////////////
// VL53L0X //
/////////////

bool SW_VL53L0X::init(Sensor_T::SensorCore *sensor) {

    bool noError = true;

    // timing settigns
    sensor->readingIntervall = VL53L0X_REFRESH_TIMING;
    sensor->timeOfLastReading = 0;

    // create the new sensor object 
    sensor->object = OME::GetFreeObjPrt(nullptr);
    *static_cast<Adafruit_VL53L0X*>(sensor->object) = Adafruit_VL53L0X();

    // sensor specific init
    noError &= static_cast<Adafruit_VL53L0X*>(sensor->object)->begin();

    return noError;
}
bool SW_VL53L0X::activate(Sensor_T::SensorCore*sensor) {

    return true;
}
bool SW_VL53L0X::deactivate(Sensor_T::SensorCore*sensor) {

    return true;
}
bool SW_VL53L0X::update(Sensor_T::SensorCore*sensor) {

    return true;
}

/////////////
// VL6180X //
/////////////

bool SW_VL6180X::init(Sensor_T::SensorCore*sensor) {

    bool noError = true;

    // timing settigns
    sensor->readingIntervall = VL6180X_REFRESH_TIMING;
    sensor->timeOfLastReading = 0;

    // create the new sensor object 
    sensor->object = OME::GetFreeObjPrt(nullptr);
    *static_cast<Adafruit_VL6180X*>(sensor->object) = Adafruit_VL6180X();

    // sensor specific init
    noError &= static_cast<Adafruit_VL6180X*>(sensor->object)->begin();

    return noError;
}
bool SW_VL6180X::activate(Sensor_T::SensorCore*sensor) {

    return true;
}
bool SW_VL6180X::deactivate(Sensor_T::SensorCore*sensor) {

    return true;
}
bool SW_VL6180X::update(Sensor_T::SensorCore*sensor) {

    return true;
}

///////////
// SRF08 //
///////////

bool SW_SRF08::init(Sensor_T::SensorCore*sensor) {

    bool noError = true;

    // timing settigns
    sensor->readingIntervall = SRF08_REFRESH_TIMING;
    sensor->timeOfLastReading = 0;

    // create the new sensor object 
    sensor->object = OME::GetFreeObjPrt(nullptr);
    *static_cast<SRF08*>(sensor->object) = SRF08(SRF08_I2C_ADDRESS);

    // sensor specific init
    /*noError &=*/ static_cast<SRF08*>(sensor->object)->init();

    return noError;
}
bool SW_SRF08::activate(Sensor_T::SensorCore*sensor) {

    return true;
}
bool SW_SRF08::deactivate(Sensor_T::SensorCore*sensor) {

    return true;
}
bool SW_SRF08::update(Sensor_T::SensorCore*sensor) {

    return true;
}