/**
 * @file Communication.cpp
 * @brief The source file for communication related stuff.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 21 December 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

// associated header
#include "Communication.h"

// used namespaces
using namespace communication;
using namespace smu_com_backend;

bool communication::checkForMessage() {

    // check if enought data is in the serial buffer
    if (_SMU_COM_BACKEND_SERIAL_INTERFACE.availiable() >= 4) {
        return true;
    }
    else {
        return false;
    }
}

bool communication::processRecMsg(Message* msg, Sensors* mySensors) {

    // msgAnswer
    Message msgAnswer;

    // evaluate the received message
    switch(msg->getMsgType()) {
        
        case MessageType::NONE :
            return true;
        break;

		case MessageType::ACK_FAULT :
            return false;       // @ToDo: impl.
        break;

		case MessageType::ACK :
            return true;        // @ToDo: impl.
        break;

		case MessageType::PONG :

        break;

		case MessageType::G_STATUS :
        
        break;

		case MessageType::G_COM_ERROR :
		
        break;

        case MessageType::G_SMU_ERROR :
		
        break;

        case MessageType::RESET :
            msgAnswer.
        break;

        case MessageType::FIRMWARE_V :
		
        break;

        case MessageType::COM_BACK_V :
		
        break;

		case MessageType::INIT_SENSOR :

        break;

        case MessageType::S_SEN_ACTIVE :

        break;

        case MessageType::G_SEN_ACTIVE :

        break;

		case MessageType::S_AUTO_UPDATE :
		
        break;

        case MessageType::G_AUTO_UPDATE :
		
        break;
        
        case MessageType::MAN_UPDATE :

        break;

        case MessageType::READ_SENSOR :

        break;

        case MessageType::ERROR :
        default:
            return false;
        break;
    }

    // send answer back
    if (msgAnswer.getMsgType() != MessageType::NONE && msgAnswer.getMsgType() != MessageType::ERROR) {
        sendMessage(msgAnswer);
        return true;
    }
    else {
        return false;
    }
}