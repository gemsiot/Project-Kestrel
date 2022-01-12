/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/schul/Documents/Project-Kestrel/Software/KestrelSleepTest/src/KestrelSleepTest.ino"
/*
 * Project KestrelSleepTest
 * Description:
 * Author:
 * Date:
 */

#include <MCP23018.h>

void setup();
void loop();
#line 10 "c:/Users/schul/Documents/Project-Kestrel/Software/KestrelSleepTest/src/KestrelSleepTest.ino"
MCP23018 ioAlpha(0x20);

const uint8_t RTC_INT = D22; //FIX!
const uint8_t CSA_EN = 14; //FIX!
const uint8_t LED_EN = 13; //FIX!
const uint8_t AUX_EN = 15; //FIX!
// const uint8_t I2C_OB_EN = A6; //FIX!

const uint8_t FRAM_ADR = 0x50; 
const uint8_t ACCEL_ADR = 0x15;

const uint8_t I2C_OB_EN = D21;
const uint8_t I2C_GLOBAL_EN = D23;

SYSTEM_MODE(AUTOMATIC);

void setup() {
  pinMode(I2C_OB_EN, OUTPUT);
  digitalWrite(I2C_OB_EN, HIGH);
  Wire.begin();
  ioAlpha.begin();
  ioAlpha.pinMode(12, OUTPUT); //LOW
  ioAlpha.pinMode(11, OUTPUT); //LOW
  ioAlpha.pinMode(10, OUTPUT); //LOW
  ioAlpha.pinMode(9, INPUT); 
  ioAlpha.pinMode(8, INPUT);
  ioAlpha.pinMode(7, INPUT);
  ioAlpha.pinMode(6, INPUT);
  ioAlpha.pinMode(5, INPUT);
  ioAlpha.pinMode(4, INPUT);
  ioAlpha.pinMode(3, INPUT);
  ioAlpha.pinMode(2, INPUT_PULLUP);
  ioAlpha.pinMode(1, INPUT);
  ioAlpha.pinMode(0, INPUT);

  ioAlpha.pinMode(CSA_EN, OUTPUT);
  ioAlpha.pinMode(LED_EN, OUTPUT);
  ioAlpha.pinMode(AUX_EN, OUTPUT);

  // pinMode(I2C_OB_EN, OUTPUT);
  // digitalWrite(I2C_OB_EN, HIGH); //Enable onboard communication 
}

void loop() {
  //Shutdown Accel
	Wire.beginTransmission(ACCEL_ADR);
	Wire.write(0x0D); //Write to control register
	Wire.write(0x01); //Set power down
	Wire.endTransmission();

  //Shutdown FRAM
	Wire.beginTransmission(0xA0);
	Wire.write((FRAM_ADR << 1) | 0x01); //Shift to add "r/w" bit //FIX!
	Wire.endTransmission(false);
	Wire.beginTransmission(0x43);
	Wire.endTransmission();

  ioAlpha.digitalWrite(CSA_EN, LOW); //Turn off CSAs
  ioAlpha.digitalWrite(LED_EN, HIGH); //Turn off LEDs for ultra low power
  ioAlpha.digitalWrite(AUX_EN, LOW); //Turn off auxiliary power

  // digitalWrite(I2C_OB_EN, LOW);

  // SystemSleepConfiguration config;
	// 	config.mode(SystemSleepMode::ULTRA_LOW_POWER)
	// 	.gpio(RTC_INT, FALLING);

  SystemSleepConfiguration config;
		config.mode(SystemSleepMode::ULTRA_LOW_POWER)
		.gpio(RTC_INT, FALLING);
		SystemSleepResult result = System.sleep(config);
}