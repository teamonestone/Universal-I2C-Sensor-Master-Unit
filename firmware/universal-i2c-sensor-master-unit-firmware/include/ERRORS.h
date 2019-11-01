/**
 * @file ERRORS.h
 * @brief The header file for error codes.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 01 November 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

#ifndef ERRORS_H
#define ERRORS_H

//////////////
// Includes //
//////////////


/////////////
// Defines //
/////////////


///////////////
// Namespace //
///////////////

/**
 * @namespace ERRORS
 * 
 * @brief Namspace for error codes.
 */
namespace ERRORS {

    /**
     * @enum Code
     * 
     * @brief The Error-Code Enum.
     */
    enum Code {
        None = 0,
        Fatal = 1,
        SensorInit = 100,
        SensorInitBNO055 = 101,
        SensorInitVL53L0X = 102,
        SensorInitVL6180X = 103,
        SensorInitSRF08 = 104,
        SensorReading = 110,
        SensorReadingBNO055 = 111,
        SensorReadingVL53L0X = 112,
        SensorReadingVL6180X = 113,
        SensorReadingSRF08 = 114
    };
}

/**
 * @namespace WARNINGS
 * 
 * @brief Namspace for error codes.
 */
namespace WARNINGS {

    /**
     * @enum Code
     * 
     * @brief The Error-Code Enum.
     */
    enum Code {
        None = 0,
        SensorInit = 100,
        SensorInitBNO055 = 101,
        SensorInitVL53L0X = 102,
        SensorInitVL6180X = 103,
        SensorInitSRF08 = 104,
        SensorReading = 110,
        SensorReadingBNO055 = 111,
        SensorReadingVL53L0X = 112,
        SensorReadingVL6180X = 113,
        SensorReadingSRF08 = 114
    };
}

#endif