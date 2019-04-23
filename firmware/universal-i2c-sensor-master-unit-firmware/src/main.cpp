//////////////
// Includes //
//////////////

// system libraries
#include <Arduino.h>

// sensor libraries
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_VL6180X.h>
#include <SRF08.h>

// i2c mux library
#include <TCA9548A.h>

// communication libraries
#include <Wire.h>
#include <communication.h>

// utility
#include <utility.h>

/////////////
// Defines //
/////////////

// i2c stuff
#define SMU_MAIN_ADDRESS 10
//#define SMU_SOFT_ADDRESS 0

// serial stuff
#define SMU_MAIN_BAUD 115200
//#define SMU_SFOT_BAUD 115200

/////////////
// "setup" //
/////////////

void setup() {

  // hardware serial
  Serial.begin(SMU_MAIN_BAUD);

  // hardware i2c
  Wire.begin(SMU_MAIN_ADDRESS);

}

/////////////////
// "main loop" //
/////////////////

void loop() {

}