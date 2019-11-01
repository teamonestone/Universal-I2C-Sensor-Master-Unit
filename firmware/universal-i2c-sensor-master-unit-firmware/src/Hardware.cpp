/**
 * @file Hardware.cpp
 * @brief The source file for hardware related stuff.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 01 November 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

// associated header
#include <Hardware.h>

/**
 * @brief Toggel the error led.
 * 
 * @param state 1 = led on, 0 = led off
 */
void Hardware::LEDs::error(bool state) {
    digitalWrite(12, state);
}

/**
 * @brief Toggel the status led.
 * 
 * @param state 1 = led on, 0 = led off
 */
void Hardware::LEDs::status(bool state) {
    digitalWrite(13, state);
}