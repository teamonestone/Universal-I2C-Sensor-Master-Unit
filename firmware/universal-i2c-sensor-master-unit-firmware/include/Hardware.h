/**
 * @file Hardware.h
 * @brief The header file for hardware related stuff.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 01 November 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

#ifndef HARDWARE_h
#define HARDWARE_h

//////////////
// Includes //
//////////////

// basic Includes
#include <Arduino.h>
#include <inttypes.h>

// i2c stuff
#include <Wire.h>
#include "TCA9548A.h"

// serial stuff
#include <SoftwareSerial.h>


/////////////
// Defines //
/////////////

#define I2C_MUX_ADR             //< Defines the i2c address of the mux

#define ERROR_LED_PIN 12        //< Defines the pin number of the error led
#define STATUS_LED_PIN 13       //< Defines the pin number of the status led


///////////////
// Namespace //
///////////////

/**
 * @namespace Sensor_T
 * 
 * @brief Namspace for hardware related stuff.
 */
namespace Hardware {

    ///////////////
    // functions //
    ///////////////

    void initHardwarePins();


    //////////////////////
    // Sub - Namespaces //
    //////////////////////

    /**
     * @namespace I2C_MUX
     * 
     * @brief Namespace for a static object of the i2c mux.
     */
    namespace I2C_MUX {
        /**
         * @brief Create a static instance of the TCA9548A mux.
         * 
         */
        static TCA9548A Instance = TCA9548A(I2C_MUX_ADR);
    }

    /**
     * @namespace LEDs
     * 
     * @brief Namespace for the onboard leds.
     */
    namespace LEDs {
        void error(bool state);         // Toggle the error led.
        void status(bool state);        // Toggle the status led.
    }

    /**
     * @namespace SoftSerial
     * 
     * @brief Namespace for a static object of the SoftwareSerial class.
     */
    namespace SoftSerial {

        /**
         * @brief Create a static instance of the SoftwareSerial class.
         * 
         */
        static SoftwareSerial Instance = SoftwareSerial(9, 10);
    }
}

#endif