/**
 * @file Communication.h
 * @brief The header file for communication related stuff.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 21 December 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

//////////////
// Includes //
//////////////

// basic Includes
#include <Arduino.h>
#include <inttypes.h>
#include <SoftwareSerial.h>

// communication backend
#include "SMU-Communication-Backend.h"

// global vars
#include "GlobalVars.h"

// sensor stuff
#include "Sensors.h"

// arduino util
#include "arduino-util.h"
#include "bit_op.h"

/////////////
// Defines //
/////////////


///////////////
// Namespace //
///////////////
using namespace smu_com_backend;

/////////////
// Members //
/////////////

/**
 * @namespace communication
 * 
 * @brief Namespace for SMU-Communication related stuff.
 */
namespace communication
{
	bool checkForMessage();

	bool processRecMsg(Message* msg, Sensors* mySensors);
}

#endif