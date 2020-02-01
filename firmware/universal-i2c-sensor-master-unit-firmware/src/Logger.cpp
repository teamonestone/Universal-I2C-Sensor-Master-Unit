/**
 * @file Logger.cpp
 * @brief The source file for a small serial logger script.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 01 February 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

// associated header
#include "Logger.h"


// defines
#define LOGGER_STATIC_TEXT_1 "]: "
#define LOGGER_STATIC_TEXT_2 "SMU-STAT @["


// functions

void serial_logger::writeToLog(smu_types::codes::Status code) {

    if (static_cast<uint16_t>(code) > 1000) {
        #ifdef DEBUG 
            #ifndef DEBUG_FINE
                SERIAL2LOG.print(LOGGER_STATIC_TEXT_2);
                SERIAL2LOG.print(millis());
                SERIAL2LOG.print(LOGGER_STATIC_TEXT_1);
                SERIAL2LOG.println(static_cast<uint16_t>(code));
            #endif
        #endif
    }
    else {
        #ifdef DEBUG 
            SERIAL2LOG.print(LOGGER_STATIC_TEXT_2);
            SERIAL2LOG.print(millis());
            SERIAL2LOG.print(LOGGER_STATIC_TEXT_1);
            SERIAL2LOG.println(static_cast<uint16_t>(code));
        #endif

        GlobalVars::SystemStatus = code;
    }
}

void serial_logger::writeToLog(smu_types::codes::Error code) {
    
    #ifdef DEBUG
        if (static_cast<int16_t>(code) <= 0) {
            SERIAL2LOG.print("SMU-ERR @[");
        } 
        else {
            SERIAL2LOG.print("SMU-WARN @[");
        }

        SERIAL2LOG.print(millis());
        SERIAL2LOG.print(LOGGER_STATIC_TEXT_1);
        SERIAL2LOG.println(static_cast<int16_t>(code));
    #endif

    GlobalVars::SystemError = code;
}

void serial_logger::writeToLog(smu_com_backend::ComErrorInfo code) {
    #ifdef DEBUG
        SERIAL2LOG.print("COM-ERR @[");
        SERIAL2LOG.print(millis());
        SERIAL2LOG.print(LOGGER_STATIC_TEXT_1);
        SERIAL2LOG.println(static_cast<uint8_t>(code));
    #endif
}