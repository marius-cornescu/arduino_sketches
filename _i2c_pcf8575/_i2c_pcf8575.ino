//= INCLUDES =======================================================================================
#include <Wire.h>
#include "PCF8575.h"

#define NOT_SEQUENTIAL_PINOUT

//= CONSTANTS ======================================================================================
const uint8_t LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED

const uint8_t OUT_PIN = P0;

const uint8_t I2C_ADDRESS = 0x20;

//= VARIABLES ======================================================================================
volatile uint8_t ledState = HIGH;


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
  // pcf8575.pinMode(P0, INPUT);
  // pcf8575.pinMode(P1, INPUT);
  // pcf8575.pinMode(P2, INPUT);
  // pcf8575.pinMode(P3, INPUT);
  // pcf8575.pinMode(P4, INPUT);
  // pcf8575.pinMode(P5, INPUT);
  // pcf8575.pinMode(P6, INPUT);
  // pcf8575.pinMode(P7, INPUT);
  pcf8575.pinMode(P8, INPUT);
  pcf8575.pinMode(P9, INPUT);
  pcf8575.pinMode(P10, INPUT);
  pcf8575.pinMode(P11, INPUT);
  pcf8575.pinMode(P12, INPUT);
  pcf8575.pinMode(P13, INPUT);
  pcf8575.pinMode(P14, INPUT);
  pcf8575.pinMode(P15, INPUT);

  //pcf8575.pinMode(OUT_PIN, OUTPUT);

  pcf8575.begin();

  delay(1000);
}
//==================================================================================================
void loop()
{
  ledState = (ledState == HIGH) ? LOW : HIGH;

  

  // echos the lines
	PCF8575::DigitalInput di = pcf8575.digitalReadAll();
  // byte di = pcf8575.digitalReadAll();
  // Serial.println(di, BIN);
	Serial.print(di.p0);
	Serial.print(" - ");
	Serial.print(di.p1);
	Serial.print(" - ");
	Serial.print(di.p2);
	Serial.print(" - ");
	Serial.print(di.p3);
	Serial.print(" - ");
	Serial.print(di.p4);
	Serial.print(" - ");
	Serial.print(di.p5);
	Serial.print(" - ");
	Serial.print(di.p6);
	Serial.print(" - ");
	Serial.print(di.p7);
	Serial.print(" == ");
	Serial.print(di.p8);
	Serial.print(" - ");
	Serial.print(di.p9);
	Serial.print(" - ");
	Serial.print(di.p10);
	Serial.print(" - ");
	Serial.print(di.p11);
  Serial.print(" - ");
	Serial.print(di.p12);
  Serial.print(" - ");
	Serial.print(di.p13);
  Serial.print(" - ");
	Serial.print(di.p14);
  Serial.print(" - ");
	Serial.print(di.p15);
	Serial.println("");

  //pcf8575.digitalWrite(OUT_PIN, ledState);
  digitalWrite(LED_INDICATOR_PIN, ledState);

  delay(500);
}
//==================================================================================================
