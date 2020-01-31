//////////////
// Includes //
//////////////

// system libraries
#include <Arduino.h>

// global vars
#include "GlobalVars.h"

// communication libraries
#include <Wire.h>
#include "Communication.h"

// utility stuff
#include "arduino-util.h"

// sensor stuff
#include "Sensors.h"

/////////////
// Defines //
/////////////



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
  hardware::initHardware();
  
  // hardware i2c
  Wire.begin(SMU_MAIN_I2C_ADDRESS);
  delay(10000);

  //BNO055_No = MySensors.connectSensor(0, Sensor_T::SensorType::BNO055_T);
  //VL53L0X_No = MySensors.connectSensor(1, Sensor_T::SensorType::VL53L0X_T);
  VL6180X_No = MySensors.connectSensor(2, Sensor_T::SensorType::VL6180X_T);
  //SRF08_No = MySensors.connectSensor(3, Sensor_T::SensorType::SRF08_T);
  
}

/////////////////
// "main loop" //
/////////////////

void loop() {
    

    if (GlobalVars::autoUpdateActivationStatus == true) {
      MySensors.updateAllSensors();
    }


  hardware::leds::status(1); //Serial.println("an");
  //uint32_t time = millis();
  MySensors.updateAllSensors();
  //Serial.print("dT="); Serial.println(millis() - time);

  //Serial.print("US-Sensor Reading: "); Serial.println(MySensors.getReading(SRF08_No, 0));
  //Serial.print("BNO-Sensor Reading: "); Serial.println(MySensors.getReading(BNO055_No, 0));
  SERIAL2LOG.print("LASER-Sensor Reading: "); Serial.println(MySensors.getReading(VL6180X_No, 0));

  delay(100);
  hardware::leds::status(0); //Serial.println("aus");

  delay(100);
}