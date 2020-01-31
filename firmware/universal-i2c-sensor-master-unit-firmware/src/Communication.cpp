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

bool communication::checkForMessage() {

    // check if enought data is in the serial buffer
    if (_SMU_COM_BACKEND_SERIAL_INTERFACE.available() >= 4) {
        return true;
    }
    else {
        return false;
    }
}

bool communication::processRecMsg(Message* msg, Sensors* mySensors) {

    // msgAnswer
    uint8_t payload[25] = {0};
    Message answer;

    // evaluate the received message
    switch(msg->getMsgType()) {
        
        case MessageType::NONE :
            return true;
        break;

		case MessageType::ACK_FAULT :
            return false;
        break;

		case MessageType::ACK :
            return true;
        break;

		case MessageType::PONG :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::PONG);
            payload[1] = (msg->getPayload())[0];
            answer.setPayload(payload, 2);
        break;

		case MessageType::G_STATUS :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::G_STATUS);
            payload[1] = 0; //status
            answer.setPayload(payload, 2);
        break;

		case MessageType::G_COM_ERROR :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::G_COM_ERROR);
            payload[1] = 0; //error
            answer.setPayload(payload, 2);
        break;

        case MessageType::G_SMU_ERROR :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::G_SMU_ERROR);
            payload[1] = 0; //error
            answer.setPayload(payload, 2);
        break;

        case MessageType::RESET :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::RESET);
            answer.setPayload(payload, 1);
        break;

        case MessageType::FIRMWARE_V :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::FIRMWARE_V);
            payload[1] = 0; //firmware
            payload[2] = 0; //firmware
            answer.setPayload(payload, 3);
        break;

        case MessageType::COM_BACK_V :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::COM_BACK_V);
            payload[1] = highByte(smu_com_backend::getVersion());
            payload[2] = lowByte(smu_com_backend::getVersion());;
            answer.setPayload(payload, 3);
        break;

		case MessageType::INIT_SENSOR :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::INIT_SENSOR);
            // init
            answer.setPayload(payload, 2);
        break;

        case MessageType::S_SEN_ACTIVE :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::S_SEN_ACTIVE);
            
            // set the sensor active
            if (static_cast<bool>(msg->getPayload()[1]) == true) {
                payload[1] = static_cast<uint8_t>(mySensors->activateSensor(msg->getPayload()[0]));
            }
            else {
                payload[1] = static_cast<uint8_t>(mySensors->deactivateSensor(msg->getPayload()[0]));
            }
            
            answer.setPayload(payload, 2);
        break;

        case MessageType::G_SEN_ACTIVE :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::G_SEN_ACTIVE);

            // set the sensor active
            if (static_cast<bool>(msg->getPayload()[1]) == true) {
                payload[1] = static_cast<uint8_t>(mySensors->activateSensor(msg->getPayload()[0]));
            }
            else {
                payload[1] = static_cast<uint8_t>(mySensors->deactivateSensor(msg->getPayload()[0]));
            }
            
            answer.setPayload(payload, 2);
        break;

		case MessageType::S_AUTO_UPDATE :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::S_AUTO_UPDATE);
            //
            answer.setPayload(payload, 2);
        break;

        case MessageType::G_AUTO_UPDATE :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::G_AUTO_UPDATE);
            //
            answer.setPayload(payload, 2);
        break;
        
        case MessageType::MAN_UPDATE :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::MAN_UPDATE);
            
            // update all sensors 
            payload[1] = static_cast<uint8_t>(mySensors->updateAllSensors());

            answer.setPayload(payload, 2);
        break;

        case MessageType::READ_SENSOR :
            answer.clear();
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::READ_SENSOR);
            //
            answer.setPayload(payload, 2);
        break;

        case MessageType::ERROR :
        default:
            return false;
        break;
    }

    // send answer back
    if (answer.getMsgType() != MessageType::NONE && answer.getMsgType() != MessageType::ERROR) {
        //sendMessage(msgAnswer);
        return true;
    }
    else {
        return false;
    }
}