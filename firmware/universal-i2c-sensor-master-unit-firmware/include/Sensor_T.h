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

namespace Sensor_T {

    enum SensorType {NONE, BNO055_T, VL53L0X_T, VL6180X_T, SRF08_T, CMPS10_T};

    // data structur for a sensor
    typedef struct SensorCore{

        // general stuff
        uint8_t port;
        SensorType type;

        // sensor object
        void *object;

        // readings
        float sensorReadings[SENSORS_READING_VECT_SIZE];

        // timing
        uint32_t timeOfLastReading;
        uint32_t readingIntervall;
        
        // flags
        bool busy;
        bool active;
        bool used;

        // functions
        bool (*init)(SensorCore*);
        bool (*activate)(SensorCore*);
        bool (*deactivate)(SensorCore*);
        bool (*update)(SensorCore*);
    };
}

#endif