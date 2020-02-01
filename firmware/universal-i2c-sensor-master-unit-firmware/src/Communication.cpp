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
    if (_SMU_COM_BACKEND_SERIAL_INTERFACE.available() >= _SMU_COM_BACKEND_MIN_MSG_LENGHT) {
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
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::PONG);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            //----------------------------------------------------------

            //------ set payload information ---------------------------
            payload[1] = msg->getPayload()[0];
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 2);
            //----------------------------------------------------------
        }
        break;

		case MessageType::G_STATUS :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::G_STATUS);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            //----------------------------------------------------------

            //------ set payload information ---------------------------
            payload[1] = 0; //status
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 2);
            //----------------------------------------------------------
        }
        break;

		case MessageType::G_COM_ERROR :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::G_COM_ERROR);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            //----------------------------------------------------------

            //------ set payload information ---------------------------
            payload[1] = 0; //status
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 2);
            //----------------------------------------------------------
        }
        break;

        case MessageType::G_SMU_ERROR :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::G_SMU_ERROR);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            //----------------------------------------------------------

            //------ set payload information ---------------------------
            payload[1] = 0; //status
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 2);
            //----------------------------------------------------------
        }
        break;

        case MessageType::RESET :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::RESET);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            //----------------------------------------------------------

            //------ set payload information ---------------------------
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 1);
            //----------------------------------------------------------
        }
        break;

        case MessageType::FIRMWARE_V :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::FIRMWARE_V);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            //----------------------------------------------------------

            //------ set payload information ---------------------------
            payload[1] = highByte(SMU_FIRMWARE_VERSION);
            payload[2] = lowByte(SMU_FIRMWARE_VERSION);
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 3);
            //----------------------------------------------------------
        }
        break;

        case MessageType::COM_BACK_V :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::COM_BACK_V);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            //----------------------------------------------------------

            //------ set payload information ---------------------------
            payload[1] = highByte(smu_com_backend::getVersion());
            payload[2] = lowByte(smu_com_backend::getVersion());
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 3);
            //----------------------------------------------------------
        }
        break;

		case MessageType::INIT_SENSOR :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::INIT_SENSOR);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            uint8_t sensorPort = msg->getPayload()[1];
            Sensor_T::SensorType sensorType = static_cast<Sensor_T::SensorType>(msg->getPayload()[0]);
            
            // init a new sensor
            int8_t conRes = mySensors->connectSensor(sensorPort, sensorType);
            //----------------------------------------------------------

            //------ set payload information ---------------------------
            if (conRes < 0) {
                payload[1] = static_cast<uint8_t>(false);
                payload[2] = static_cast<uint8_t>(-1);
            }
            else {
                payload[1] = static_cast<uint8_t>(true);
                payload[2] = static_cast<uint8_t>(conRes);
            }
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 3);
            //----------------------------------------------------------
        }
        break;

        case MessageType::S_SEN_ACTIVE :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::S_SEN_ACTIVE);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            bool res = false;
            if (static_cast<bool>(msg->getPayload()[1]) == true) {
                res = mySensors->activateSensor(static_cast<int8_t>(msg->getPayload()[0]));
            }
            else {
                res = mySensors->deactivateSensor(static_cast<int8_t>(msg->getPayload()[0]));
            }
            //----------------------------------------------------------

            //------ set payload information ---------------------------
            payload[1] = static_cast<uint8_t>(res);
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 2);
            //----------------------------------------------------------
        }
        break;

        case MessageType::G_SEN_ACTIVE :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::G_SEN_ACTIVE);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            //----------------------------------------------------------

            //------ set payload information ---------------------------
            payload[1] = static_cast<uint8_t>(true);
            payload[2] = static_cast<uint8_t>(mySensors->isActive(static_cast<int8_t>(msg->getPayload()[0])));
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 3);
            //----------------------------------------------------------
        }
        break;

		case MessageType::S_AUTO_UPDATE :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::S_AUTO_UPDATE);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            mySensors->externAutoUpdateAll = static_cast<bool>(msg->getPayload()[0]);
            //----------------------------------------------------------

            //------ set payload information ---------------------------
            payload[1] = static_cast<uint8_t>(true);
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 2);
            //----------------------------------------------------------
        }
        break;

        case MessageType::G_AUTO_UPDATE :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::G_AUTO_UPDATE);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            //----------------------------------------------------------

            //------ set payload information ---------------------------
            payload[1] = static_cast<uint8_t>(true);
            payload[2] = static_cast<uint8_t>(mySensors->externAutoUpdateAll);
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 3);
            //----------------------------------------------------------
        }
        break;
        
        case MessageType::MAN_UPDATE :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::MAN_UPDATE);
            //----------------------------------------------------------

            //------ processs the request ------------------------------

            // update all sensors 
            bool res = static_cast<uint8_t>(mySensors->updateAllSensors());

            //----------------------------------------------------------

            //------ set payload information ---------------------------
            payload[1] = static_cast<uint8_t>(res);
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, 2);
            //----------------------------------------------------------
        }
        break;

        case MessageType::READ_SENSOR :
        {
            //----- construct basic msg as answer to the request -------
            answer.setMsgType(MessageType::ACK);
            payload[0] = static_cast<uint8_t>(MessageType::READ_SENSOR);
            //----------------------------------------------------------

            //------ processs the request ------------------------------
            //------ set payload information ---------------------------
            int8_t sensorNo = static_cast<int8_t>(msg->getPayload()[0]);
            bool res = true;

            for (uint8_t i = 0; i < SENSORS_READING_VECT_SIZE; i++) {
                uint8_t temp[4] = {0};
                float reading = mySensors->getReading(sensorNo, i);

                if (arduino_util::bit_op::convFloatToBytes(&reading, temp) == false ) {
                    res = false;
                }

                payload[1 + ((i * 4) + 0)] = temp[0];
                payload[1 + ((i * 4) + 1)] = temp[1];
                payload[1 + ((i * 4) + 2)] = temp[2];
                payload[1 + ((i * 4) + 3)] = temp[3];
            }

            payload[1] = static_cast<uint8_t>(res);
            //----------------------------------------------------------

            //------ assemble msg -------------------------------------- 
            answer.setPayload(payload, (1 + (SENSORS_READING_VECT_SIZE * 4)));
            //----------------------------------------------------------
        }
        break;

        case MessageType::ERROR :
        default:
            return false;
        break;
    }

    // send answer back
    if (answer.getMsgType() != MessageType::NONE && answer.getMsgType() != MessageType::ERROR) {
        sendMessage(&answer);
        return true;
    }
    else {
        return false;
    }
}