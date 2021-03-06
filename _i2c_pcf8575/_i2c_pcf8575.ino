//= INCLUDES =======================================================================================
#include <stdio.h> // for function sprintf

#include <Wire.h>
#include "PCF8575.h"

#define NOT_SEQUENTIAL_PINOUT

//= CONSTANTS ======================================================================================
const uint8_t LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED

const uint8_t I2C_ADDRESS = 0x20;

const uint8_t ON = LOW;
const uint8_t OFF = HIGH;

//= VARIABLES ======================================================================================
volatile uint8_t ledState = ON;

// adjust addresses if needed
PCF8575 pcf8575(I2C_ADDRESS);  // add switches to lines  (used as input)

//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  //
  Wire.begin();
  //
  // Set pinMode
  // Side A
  pcf8575.pinMode(P0, OUTPUT);
  pcf8575.pinMode(P1, OUTPUT);
  pcf8575.pinMode(P2, OUTPUT);
  pcf8575.pinMode(P3, OUTPUT);
  pcf8575.pinMode(P4, OUTPUT);
  pcf8575.pinMode(P5, OUTPUT);
  pcf8575.pinMode(P6, OUTPUT);
  pcf8575.pinMode(P7, OUTPUT);
  // Side B
  pcf8575.pinMode(P8, INPUT);
  pcf8575.pinMode(P9, INPUT);
  pcf8575.pinMode(P10, INPUT);
  pcf8575.pinMode(P11, INPUT);
  pcf8575.pinMode(P12, INPUT);
  pcf8575.pinMode(P13, INPUT);
  pcf8575.pinMode(P14, INPUT);
  pcf8575.pinMode(P15, INPUT);

  //..............................
  pcf8575.begin();
  //..............................
  pcf8575.digitalWrite(P0, ledState);
  pcf8575.digitalWrite(P1, ledState);
  digitalWrite(LED_INDICATOR_PIN, ledState);
  //..............................
  delay(5000);
}
//==================================================================================================
void loop()
{
  ledState = (ledState == ON) ? OFF : ON;

  // echos the lines
	PCF8575::DigitalInput io_vals = pcf8575.digitalReadAll();
  // byte io_vals = pcf8575.digitalReadAll();
  // Serial.println(io_vals, BIN);
  char buffer[200];
  sprintf(buffer, "|0=%d|1=%d|2=%d|3=%d|4=%d|5=%d|6=%d|7=%d||||8=%d|9=%d|10=%d|11=%d|12=%d|13=%d|14=%d|15=%d|", io_vals.p0, io_vals.p1, io_vals.p2, io_vals.p3, io_vals.p4, io_vals.p5, io_vals.p6, io_vals.p7, io_vals.p8, io_vals.p9, io_vals.p10, io_vals.p11, io_vals.p12, io_vals.p13, io_vals.p14, io_vals.p15);
  Serial.println(buffer);

  //sprintf(buffer, "|0=%d|1=%d|2=%d|3=%d|4=%d|5=%d|6=%d|7=%d||||", io_vals.p0, io_vals.p1, io_vals.p2, io_vals.p3, io_vals.p4, io_vals.p5, io_vals.p6, io_vals.p7);
  //Serial.println(buffer);
  //sprintf(buffer, "||||8=%d|9=%d|10=%d|11=%d|12=%d|13=%d|14=%d|15=%d|", io_vals.p8, io_vals.p9, io_vals.p10, io_vals.p11, io_vals.p12, io_vals.p13, io_vals.p14, io_vals.p15);
  //Serial.println(buffer);

  pcf8575.digitalWrite(P0, ledState);
  pcf8575.digitalWrite(P1, (ledState == ON) ? OFF : ON);
  digitalWrite(LED_INDICATOR_PIN, ledState);

  delay(500);
}
//==================================================================================================
