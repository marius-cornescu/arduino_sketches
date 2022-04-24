/*
   PIN CONNECTIONS

   GND  --> GND
   VCC  --> 5V
   DATA --> D2

*/
//= INCLUDES =======================================================================================
#include <RCSwitch.h>


//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED


//= VARIABLES ======================================================================================
volatile int ledState = HIGH;
RCSwitch rfRx = RCSwitch();

//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  //
  rfRx.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}
//==================================================================================================
void loop() {
  if (rfRx.available()) {
    output(rfRx.getReceivedValue(), rfRx.getReceivedBitlength(), rfRx.getReceivedDelay(), rfRx.getReceivedRawdata(), rfRx.getReceivedProtocol());
    rfRx.resetAvailable();
  }
}
//==================================================================================================
