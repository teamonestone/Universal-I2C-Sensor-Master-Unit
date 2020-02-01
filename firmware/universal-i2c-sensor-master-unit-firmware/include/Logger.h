/**
 * @file Logger.h
 * @brief The header file for a small serial logger script.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 01 February 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

#ifndef LOGGER_H
#define LOGGER_H

//////////////
// Includes //
//////////////

// basic Includes
#include <Arduino.h>
#include <inttypes.h>

// global vars
#include "GlobalVars.h"

// i2c stuff
#include "Hardware.h"

// smu communication backend
#include "SMU-Communication-Backend.h"

// smu types
#include "SMU-Types.h"


///////////////
// Namespace //
///////////////

/**
 * @namespace serial_logger
 * 
 * @brief This is the namespae for all functions associated with the serial logging tool. 
 */
namespace serial_logger {

    void writeToLog(smu_types::codes::Status code);
    void writeToLog(smu_types::codes::Error code);
    void writeToLog(smu_com_backend::ComErrorInfo code);
}

#endif
