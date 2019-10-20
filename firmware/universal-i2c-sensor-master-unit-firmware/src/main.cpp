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
#include <sensors.h>

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
Sensors Sensors;

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