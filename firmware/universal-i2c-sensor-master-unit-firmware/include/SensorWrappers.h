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

// Includes
#include <inttypes.h>
#include <Sensors.h>

// sensor libs
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_VL6180X.h>
#include <SRF08.h>

// Defines
#define OME_OBJ_SIZE 64			///< Define for object size (in bytes).
#define OME_OBJ_POOL_SIZE 8		///< Definie for pool size.

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
        bool init(Sensors::Sensor sensor);
        bool activate(Sensors::Sensor sensor);
        bool deactivate(Sensors::Sensor sensor);
        bool update(Sensors::Sensor sensor);
    }

    /**
     * @namespace SW_VL53L0X
     * 
     * @brief The namespace is dedecated to all commands for the VL53L0X.
     */
    namespace SW_VL53L0X {
        bool init(Sensors::Sensor sensor);
        bool activate(Sensors::Sensor sensor);
        bool deactivate(Sensors::Sensor sensor);
        bool update(Sensors::Sensor sensor);
    }

    /**
     * @namespace SW_VL6180X
     * 
     * @brief The namespace is dedecated to all commands for the VL6180X.
     */
    namespace SW_VL6180X {
        bool init(Sensors::Sensor sensor);
        bool activate(Sensors::Sensor sensor);
        bool deactivate(Sensors::Sensor sensor);
        bool update(Sensors::Sensor sensor);
    }

    /**
     * @namespace SW_SRF08
     * 
     * @brief The namespace is dedecated to all commands for the SRF08.
     */
    namespace SW_SRF08 {
        bool init(Sensors::Sensor sensor);
        bool activate(Sensors::Sensor sensor);
        bool deactivate(Sensors::Sensor sensor);
        bool update(Sensors::Sensor sensor);
    }
}

#endif
