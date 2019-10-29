// associated header
#include <Sensors.h>

Sensors::Sensors() {
}

Sensors::~Sensors() {
}

bool Sensors::initNewSensor(uint8_t port, SensorType type) {
    uint8_t sensorNo = getFreeSensor();

    if (sensorNo == 255) {
        return false;
    }

    bool noError = true;
    switch (type) {

        case BNO055_T:

            // create the new sensor object 
            Adafruit_BNO055 *_BNO055 = (Adafruit_BNO055*) OME::GetFreeObjPrt(nullptr);
            *_BNO055 = Adafruit_BNO055();

            // linking pointers
            _sensors[sensorNo].object = _BNO055;
            _sensors[sensorNo].init = nullptr;
            _sensors[sensorNo].activate = nullptr;
            _sensors[sensorNo].deactivate = nullptr;
            _sensors[sensorNo].update = nullptr;

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(_sensors[sensorNo]);
            noError &= _sensors[sensorNo].activate(_sensors[sensorNo]);
            if (!noError) {
                return false;
            }

            break;

        case VL53L0X_T:

            // create the new sensor object 
            Adafruit_VL53L0X *_VL53L0X = (Adafruit_VL53L0X*) OME::GetFreeObjPrt(nullptr);
            *_VL53L0X = Adafruit_VL53L0X();

            // linking pointers
            _sensors[sensorNo].object = _VL53L0X;
            _sensors[sensorNo].init = nullptr;
            _sensors[sensorNo].activate = nullptr;
            _sensors[sensorNo].deactivate = nullptr;
            _sensors[sensorNo].update = nullptr;

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(_sensors[sensorNo]);
            noError &= _sensors[sensorNo].activate(_sensors[sensorNo]);
            if (!noError) {
                return false;
            }
           
            break;

        case VL6180X_T:

            // create the new sensor object 
            Adafruit_VL6180X *_VL6180X = (Adafruit_VL6180X*) OME::GetFreeObjPrt(nullptr);
            *_VL6180X = Adafruit_VL6180X();

            // linking pointers
            _sensors[sensorNo].object = _VL6180X;
            _sensors[sensorNo].init = nullptr;
            _sensors[sensorNo].activate = nullptr;
            _sensors[sensorNo].deactivate = nullptr;
            _sensors[sensorNo].update = nullptr;

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(_sensors[sensorNo]);
            noError &= _sensors[sensorNo].activate(_sensors[sensorNo]);
            if (!noError) {
                return false;
            }
            
            break;

        case SRF08_T:

            /*
            // create the new sensor object 
            SRF08 *_SRF08 = (SRF08*) OME::GetFreeObjPrt(nullptr);
            *_SRF08 = SRF08();

            // linking pointers
            _sensors[sensorNo].object = _SRF08;
            _sensors[sensorNo].init = nullptr;
            _sensors[sensorNo].activate = nullptr;
            _sensors[sensorNo].deactivate = nullptr;
            _sensors[sensorNo].update = nullptr;

            // running the setup
            noError = true;
            noError &= _sensors[sensorNo].init(_sensors[sensorNo]);
            noError &= _sensors[sensorNo].activate(_sensors[sensorNo]);
            if (!noError) {
                return false;
            }
            
            break;
            */
        case CMPS10_T:
        case NONE:
        default:
            return false;
            break;
    }

    return true;
}

uint8_t Sensors::getFreeSensor() {
    return 0;
}