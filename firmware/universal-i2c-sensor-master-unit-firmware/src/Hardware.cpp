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
#include "Hardware.h"

/**
 * @brief Initializes the pin-modes.
 * 
 */
void hardware::initHardware() {

    // init serial interface for logging
    SERIAL2LOG.begin(SERIAL2LOG_BAUD);

    // init i2c interface
    Wire.begin(SMU_MAIN_I2C_ADDRESS);

    // setup pins
    pinMode(ERROR_LED_PIN, OUTPUT);
    pinMode(STATUS_LED_PIN, OUTPUT);
}

/**
 * @brief Toggel the error led.
 * 
 * @param state 1 = led on, 0 = led off
 */
void hardware::leds::error(bool state) {
    digitalWrite(ERROR_LED_PIN, state);
}

/**
 * @brief Toggel the status led.
 * 
 * @param state 1 = led on, 0 = led off
 */
void hardware::leds::status(bool state) {
    digitalWrite(STATUS_LED_PIN, state);
}