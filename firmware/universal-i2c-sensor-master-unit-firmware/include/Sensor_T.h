/**
 * @file Sensor_T.h
 * @brief The header file for the sensor types.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 01 November 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

#ifndef SENSORS_TYPE_h
#define SENSORS_TYPE_h

//////////////
// Includes //
//////////////

// basic Includes
#include <inttypes.h>

/////////////
// Defines //
/////////////

#define SENSORS_READING_VECT_SIZE 4		///< Defines how many different reading values a sensor can provide.


///////////////
// Namespace //
///////////////

/**
 * @namespace Sensor_T
 * 
 * @brief Namspace for the complex sensor objects.
 */
namespace Sensor_T {

    /**
     * @enum SensorType
     * 
     * @brief Enum of all supportet sensor model names.
     */
    enum SensorType {NONE, BNO055_T, VL53L0X_T, VL6180X_T, SRF08_T, CMPS10_T};

    /**
     * @struct SensorCore
     * 
     * @brief The complex sensor object that represents a real sensor.
     */
    struct SensorCore{

        // general stuff
        uint8_t port;           ///< The physical port (0-7) where the sensor is connected.
        SensorType type;        ///< The model of the sensor.

        // sensor object
        void *object;           ///< Pointer to the sensor object.

        // readings
        float sensorReadings[SENSORS_READING_VECT_SIZE];        ///< Array to store the readings of the sensor.

        // timing
        uint32_t timeOfLastReading;             ///< The system time at which the sensor was last read.
        uint32_t readingIntervall;              ///< The minimum time interval for a reading cycle.
        
        // flags
        bool busy;                              ///< Flag that indicates if the sensor is busy.
        bool active;                            ///< Flag that indicates if the sensor is active.
        bool used;                              ///< Flag that indicates if the sensor object is used.

        // functions
        bool (*init)(SensorCore*);              ///< Function pointer for the init function.
        bool (*activate)(SensorCore*);          ///< Function pointer for the activate function.
        bool (*deactivate)(SensorCore*);        ///< Function pointer for the deactivate function.
        bool (*update)(SensorCore*);            ///< Function pointer for the update function.
    };
}

#endif