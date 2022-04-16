/*
   PIN CONNECTIONS

   GND  --> GND
   VCC  --> 5V
   DATA --> D7

*/
//= INCLUDES =======================================================================================
#include <RCSwitch.h>


//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED


//= VARIABLES ======================================================================================
volatile int ledState = HIGH;
RCSwitch rfTx = RCSwitch();

//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  //
  // Transmitter is connected to Arduino Pin #7
  rfTx.enableTransmit(7);

  // Optional set protocol (default is 1, will work for most outlets)
  // rfTx.setProtocol(2);

  // Optional set pulse length.
  rfTx.setPulseLength(351);

  // Optional set number of transmission repetitions.
  rfTx.setRepeatTransmit(4);
}
//==================================================================================================
void loop() {
  rfTx.send(9468388, 24);
  digitalWrite(LED_INDICATOR_PIN, HIGH);

  delay(10000);

  rfTx.send(9468385, 24);
  digitalWrite(LED_INDICATOR_PIN, LOW);

  delay(10000);
}
//==================================================================================================
