//////////////
// Includes //
//////////////

// system libraries
#include <Arduino.h>

// communication libraries
#include <Wire.h>
#include <communication.h>

// utility stuff
#include "utility.h"

// sensor stuff
#include "Sensors.h"

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
uint8_t BNO055_No = -1;
uint8_t VL53L0X_No = -1;
uint8_t VL6180X_No = -1;
uint8_t SRF08_No = -1;

/////////////
// "setup" //
/////////////

void setup() {

  // hardware serial
  Serial.begin(9600);

  // hardware i2c
  Wire.begin(SMU_MAIN_ADDRESS);
	Hardware::LEDs::status(1);
  delay(10000);
	Hardware::LEDs::status(0);
	delay(100);

  delay(2000);

  Serial.println("Hallo1");

  BNO055_No = MySensors.connectSensor(0, Sensor_T::SensorType::BNO055_T);
  //VL53L0X_No = MySensors.connectSensor(1, Sensor_T::SensorType::VL53L0X_T);
  VL6180X_No = MySensors.connectSensor(2, Sensor_T::SensorType::VL6180X_T);
  SRF08_No = MySensors.connectSensor(3, Sensor_T::SensorType::SRF08_T);

}

/////////////////
// "main loop" //
/////////////////

void loop() {
    
  Hardware::LEDs::status(1); Serial.println("an");
  uint32_t time = millis();
  MySensors.updateAllSensors();
  Serial.print("dT="); Serial.println(millis() - time);

  Serial.print("US-Sensor Reading: "); Serial.println(MySensors.getReading(SRF08_No, 0));

  delay(500);
  Hardware::LEDs::status(0); Serial.println("aus");

  delay(100);
}