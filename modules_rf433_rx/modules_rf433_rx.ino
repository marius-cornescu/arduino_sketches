/*
   PIN CONNECTIONS

   GND  --> GND
   VCC  --> 5V
   DATA --> D2

*/
//= DEFINES ========================================================================================
#define RfLogsToSerial   // Print RF messages to Serial Terminal       // uses 9% of memory
//= INCLUDES =======================================================================================
#if defined(DEBUG) || defined(RfLogsToSerial) || defined(I2CLogsToSerial)
#include <stdio.h> // for function sprintf
#endif

#include <RCSwitch.h>


//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED
//------------------------------------------------
const char RF_INTERRUPT_D2_PIN = 0;  // RF Receiver on INT0 => pin D2
//------------------------------------------------

//= VARIABLES ======================================================================================
volatile int ledState = HIGH;
RCSwitch rfRx = RCSwitch();

//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("START-UP >>>");
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  //
  rfRx.enableReceive(RF_INTERRUPT_D2_PIN);
  //
  Serial.println(">>> START-UP");
}
//==================================================================================================
void loop() {
  if (rfRx.available()) {
    digitalWrite(LED_INDICATOR_PIN, HIGH);

    printRxToSerial(rfRx.getReceivedValue(), rfRx.getReceivedBitlength(), rfRx.getReceivedDelay(), rfRx.getReceivedRawdata(), rfRx.getReceivedProtocol());
    rfRx.resetAvailable();

    digitalWrite(LED_INDICATOR_PIN, LOW);
  }
}
//==================================================================================================