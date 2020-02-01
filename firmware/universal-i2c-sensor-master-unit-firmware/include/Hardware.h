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

// global vars
#include "GlobalVars.h"

// i2c stuff
#include <Wire.h>
#include "TCA9548A.h"

// software serial stuff
//#include <SoftwareSerial.h>
//extern SoftwareSerial SoftSerial;


/////////////
// Defines //
/////////////

#define I2C_MUX_ADR             //< Defines the i2c address of the mux

#define ERROR_LED_PIN 12        //< Defines the pin number of the error led
#define STATUS_LED_PIN 13       //< Defines the pin number of the status led

#define SERIAL2LOG_BAUD 9200    //< The baudrate of the serial interface whic is used to write the log stuff
#define SERIAL2LOG Serial       //< The Serial interface which is used to write the log stuff


///////////////
// Namespace //
///////////////

/**
 * @namespace hardware
 * 
 * @brief Namspace for hardware related stuff.
 */
namespace hardware {

    ///////////////
    // functions //
    ///////////////

    void initHardware();


    //////////////////////
    // Sub - Namespaces //
    //////////////////////

    /**
     * @namespace i2c_mux
     * 
     * @brief Namespace for a static object of the i2c mux.
     */
    namespace i2c_mux {
        /**
         * @brief Create a static instance of the TCA9548A mux.
         * 
         */
        static TCA9548A Instance = TCA9548A(I2C_MUX_ADR);
    }

    /**
     * @namespace leds
     * 
     * @brief Namespace for the onboard leds.
     */
    namespace leds {
        void error(bool state);         // Toggle the error led.
        void status(bool state);        // Toggle the status led.
    }
}

#endif