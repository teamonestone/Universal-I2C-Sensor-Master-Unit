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

/**
 * @protocol Serail Message Format.
 * @brief The forat for all messages send over the serial port to controll the SMU board.
 * 
 * |-----------------|-------------|-----------------------|----------|-----------------|
 * | '~' as Preambel | MessageType | 0 - 251 Bytes of Data | Checksum | '#' as End-Sign |
 * |      1 Char     |   1 Byte    |     0 - 251 Bytes     |  1 Byte  |      1 Char     |
 * |-----------------|-------------|-----------------------|----------|-----------------|
 * 
 */

//////////////
// Includes //
//////////////

// basic Includes
#include <inttypes.h>
#include <Arduino.h>

class Communication
{
// Begin PUBLIC ------------------------------------------------------------------
	public:
		uint8_t getChecksum(uint8_t* dataArray, uint8_t lenght);

// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------
	private:

// End PRIVATE -------------------------------------------------------------------
};

#endif