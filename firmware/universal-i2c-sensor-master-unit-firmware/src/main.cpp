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

// DEBUG-MODE
#define DEBUG

// i2c stuff
#define SMU_MAIN_I2C_ADDRESS 0				// i2c address @ the hardware i2c port
#define SMU_SOFT_I2C_ADDRESS 10				// i2c address @ the software i2c port

// serial stuff
#define SMU_MAIN_SERIAL_BAUD 115200			// baud-rate @ the hardware serial port
#define SMU_SFOT_SERIAL_BAUD 115200			// baud-rate @ the software serial port

////////////////////
// global objects //
////////////////////

// array of sensors
Sensors MySensors;

uint8_t BNO055_No = -1;
uint8_t VL53L0X_No = -1;
uint8_t VL6180X_No = -1;
uint8_t SRF08_No = -1;

/////////////
// "setup" //
/////////////

void setup() {

  // init hardware
  Hardware::initHardwarePins();
  
  // hardware serial
  Serial.begin(SMU_MAIN_SERIAL_BAUD);
  
  // software serial
  Hardware::SoftSerial::Instance.begin(SMU_SFOT_SERIAL_BAUD);
  
  // hardware i2c
  Wire.begin(SMU_MAIN_I2C_ADDRESS);
  delay(10000);

  BNO055_No = MySensors.connectSensor(0, Sensor_T::SensorType::BNO055_T);
  //VL53L0X_No = MySensors.connectSensor(1, Sensor_T::SensorType::VL53L0X_T);
  //VL6180X_No = MySensors.connectSensor(2, Sensor_T::SensorType::VL6180X_T);
  SRF08_No = MySensors.connectSensor(3, Sensor_T::SensorType::SRF08_T);
  
}

/////////////////
// "main loop" //
/////////////////

void loop() {
    
  Hardware::LEDs::status(1); //Serial.println("an");
  //uint32_t time = millis();
  MySensors.updateAllSensors();
  //Serial.print("dT="); Serial.println(millis() - time);

  Serial.print("US-Sensor Reading: "); Serial.println(MySensors.getReading(SRF08_No, 0));

  delay(100);
  Hardware::LEDs::status(0); //Serial.println("aus");

  delay(100);
}