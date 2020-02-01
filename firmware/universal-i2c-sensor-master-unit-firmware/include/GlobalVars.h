/**
 * @file GlobalVars.h
 * @brief The header file for global variables & defines.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 31 January 2020
 * @copyright This project is released under the GNU General Public License v3.0
 */

#ifndef GLOBALVARS_H
#define GLOBALVARS_H

//////////////
// Includes //
//////////////

// basic Includes
#include <inttypes.h>

// smu types
#include "SMU-Types.h"

/////////////
// Defines //
/////////////

// Software type
#define SMU_FIRMWARE

// DEBUG-MODE
#define DEBUG
//#define DEBUG_FINE

// Firmware version
#define SMU_FIRMWARE_VERSION 10000

// i2c stuff
#define SMU_MAIN_I2C_ADDRESS 0				// i2c address @ the hardware i2c port
#define SMU_SOFT_I2C_ADDRESS 10				// i2c address @ the software i2c port


///////////////
// Namespace //
///////////////

/**
 * @namespace GlobalVars
 * 
 * @brief Namspace for global variables.
 */
namespace GlobalVars {
    static smu_types::codes::Status SystemStatus = smu_types::codes::Status::STATUS_NONE;
    static smu_types::codes::Error SystemError = smu_types::codes::Error::ERR_NONE;
}

#endif