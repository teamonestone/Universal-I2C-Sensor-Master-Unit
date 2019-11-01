//////////////
// Includes //
//////////////

// system libraries
#include <Arduino.h>

// communication libraries
#include <Wire.h>
#include <communication.h>

// utility stuff
#include <utility.h>

// sensor stuff
#include <Sensors.h>

/////////////
// Defines //
/////////////

// i2c stuff
#define SMU_MAIN_ADDRESS 10
//#define SMU_SOFT_ADDRESS 0

// serial stuff
#define SMU_MAIN_BAUD 115200
//#define SMU_SFOT_BAUD 115200

////////////////////
// global objects //
////////////////////
Sensors MySensors;

/////////////
// "setup" //
/////////////

void setup() {

  // hardware serial
  Serial.begin(SMU_MAIN_BAUD);

  // hardware i2c
  Wire.begin(SMU_MAIN_ADDRESS);

  MySensors.connectSensor(0, Sensor_T::SensorType::BNO055_T);
  MySensors.connectSensor(1, Sensor_T::SensorType::VL53L0X_T);
  MySensors.connectSensor(2, Sensor_T::SensorType::VL6180X_T);
  MySensors.connectSensor(3, Sensor_T::SensorType::SRF08_T);
  MySensors.connectSensor(4, Sensor_T::SensorType::SRF08_T);
  MySensors.connectSensor(5, Sensor_T::SensorType::SRF08_T);
  MySensors.connectSensor(6, Sensor_T::SensorType::SRF08_T);
  MySensors.connectSensor(7, Sensor_T::SensorType::SRF08_T);

}

/////////////////
// "main loop" //
/////////////////

void loop() {
    Hardware::LEDs::status(1);
    MySensors.updateAllSensors();
    delay(100);
    Hardware::LEDs::status(0);
    delay(100);
}