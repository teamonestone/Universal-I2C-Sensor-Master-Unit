/**
 * @file SensorWrappers.h
 * @brief The header file for the sensor command wrappers.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 01 November 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

#ifndef SENSORWRAPPERS_h
#define SENSORWRAPPERS_h

//////////////
// Includes //
//////////////

// basic Includes
#include <Arduino.h>
#include <inttypes.h>

// i2c stuff
#include "Hardware.h"

// memory management
#include "ObjectManagementEngine.h"

// sensor types
#include "Sensor_T.h"

// sensor libs
#include "Adafruit_BNO055.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_VL53L0X.h"
#include "Adafruit_VL6180X.h"
#include "SRF08.h"


/////////////
// Defines //
/////////////

#define BNO055_REFRESH_TIMING 100
#define BNO055_I2C_ADDRESS 0x28

#define VL53L0X_REFRESH_TIMING 100
//#define VL53L0X_I2C_ADDRESS 

#define VL6180X_REFRESH_TIMING 100
//#define VL6180X_I2C_ADDRESS 

#define SRF08_REFRESH_TIMING 100
#define SRF08_I2C_ADDRESS 112


///////////////
// Namespace //
///////////////

/**
 * @namespace SensorWrappers
 * 
 * @brief This is the parent namespace for all sensor command wrappers.
 */
namespace SensorWrappers
{
    /**
     * @namespace SW_BNO055
     * 
     * @brief The namespace is dedecated to all commands for the BNO055.
     */
    namespace SW_BNO055 {
        bool init(Sensor_T::SensorCore *sensor);
        bool activate(Sensor_T::SensorCore *sensor);
        bool deactivate(Sensor_T::SensorCore *sensor);
        bool update(Sensor_T::SensorCore *sensor);
    }

    /**
     * @namespace SW_VL53L0X
     * 
     * @brief The namespace is dedecated to all commands for the VL53L0X.
     */
    namespace SW_VL53L0X {
        bool init(Sensor_T::SensorCore *sensor);
        bool activate(Sensor_T::SensorCore *sensor);
        bool deactivate(Sensor_T::SensorCore *sensor);
        bool update(Sensor_T::SensorCore *sensor);
    }

    /**
     * @namespace SW_VL6180X
     * 
     * @brief The namespace is dedecated to all commands for the VL6180X.
     */
    namespace SW_VL6180X {
        bool init(Sensor_T::SensorCore *sensor);
        bool activate(Sensor_T::SensorCore *sensor);
        bool deactivate(Sensor_T::SensorCore *sensor);
        bool update(Sensor_T::SensorCore *sensor);
    }

    /**
     * @namespace SW_SRF08
     * 
     * @brief The namespace is dedecated to all commands for the SRF08.
     */
    namespace SW_SRF08 {
        bool init(Sensor_T::SensorCore *sensor);
        bool activate(Sensor_T::SensorCore *sensor);
        bool deactivate(Sensor_T::SensorCore *sensor);
        bool update(Sensor_T::SensorCore *sensor);
    }
}

#endif
