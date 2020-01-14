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
using namespace SMU_Com_Backend;

bool communication::processRecMsg(Message* msg, Sensors* mySensors) {

    // msgAnswer
    Message msgAnswer;

    switch(msg->getMsgType()) {
        
        case MessageType::NONE :
            break;
        break;

		case MessageType::ACK_FAULT :
        
        break;

		case MessageType::ACK :

        break;

		case MessageType::PONG :

        break;

		case MessageType::GET_STATUS :
        
        break;

		case MessageType::GET_ERROR :
		
        break;

        case MessageType::RESET :

        break;

		case MessageType::INIT_SENSOR :

        break;

        case MessageType::SET_ACTIVE :

        break;

		case MessageType::AUTO_UPDATE :
		
        break;
        
        case MessageType::MAN_UPDATE :

        break;

        default:

        break;
    }

    if (msgAnswer.getMsgType() != MessageType::NONE) {
        sendMessage(msgAnswer);
        return true;
    }
    else {
        return false;
    }
}