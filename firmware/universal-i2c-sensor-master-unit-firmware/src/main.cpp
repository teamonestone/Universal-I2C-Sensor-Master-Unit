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
  Serial.begin(9600);

  // hardware i2c
  Wire.begin(SMU_MAIN_ADDRESS);
	Hardware::LEDs::status(1);
  delay(5000);
	Hardware::LEDs::status(0);
	delay(100);

  Serial.println("Hallo1");

  MySensors.connectSensor(0, Sensor_T::SensorType::BNO055_T);
  //MySensors.connectSensor(1, Sensor_T::SensorType::VL53L0X_T);
  MySensors.connectSensor(2, Sensor_T::SensorType::VL6180X_T);
  MySensors.connectSensor(3, Sensor_T::SensorType::SRF08_T);

}

/////////////////
// "main loop" //
/////////////////

void loop() {
    
    //MySensors.updateAllSensors();
	Hardware::LEDs::status(1);
	Serial.println("an");
    delay(100);
    Hardware::LEDs::status(0);
	Serial.println("aus");
    delay(100);
}