/*
   PIN CONNECTIONS

   GND  --> GND
   VCC  --> 5V
   DATA --> D7

*/
//= DEFINES ========================================================================================
#define RF_TX_PIN 7 // RF Transmiter on pin D7
#define BTN_PIN 8   // button on pin 8

#if defined(ESP8266)
// interrupt handler and related code must be in RAM on ESP8266,
// according to issue #46.
#define RECEIVE_ATTR ICACHE_RAM_ATTR
#define VAR_ISR_ATTR
#define HIGH 0x0
#define LOW  0x1
#endif

//= INCLUDES =======================================================================================
#include <RCSwitch.h>


//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED

const int pulse_length = 351;
const unsigned int code_length = 24;

const unsigned long code = 9037304; 
//const unsigned long code = 6145633;

//= VARIABLES ======================================================================================
//volatile int ledState = HIGH;
static uint8_t lastBtnState = LOW;

RCSwitch rfTx = RCSwitch();

//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  //
  rfTx.enableTransmit(RF_TX_PIN);

  // Optional set protocol (default is 1, will work for most outlets)
  // rfTx.setProtocol(2);

  // Optional set pulse length.
  rfTx.setPulseLength(pulse_length);

  // Optional set number of transmission repetitions.
  rfTx.setRepeatTransmit(4);

  //
  pinMode(BTN_PIN, INPUT_PULLUP);
  lastBtnState = digitalRead(BTN_PIN);
  //
  delay(100);
}
//==================================================================================================
void loop() {
  uint8_t state = digitalRead(BTN_PIN);
  if (state != lastBtnState) {
    lastBtnState = state;
    if (state == HIGH) {
      Serial.println("Button pressed!");
      transmitCode();
    }
  }

  //Serial.println("*");
  delay(100);
}
//==================================================================================================
void transmitCode() {
  digitalWrite(LED_INDICATOR_PIN, HIGH);
  rfTx.send(code, code_length);
  delay(100);
  digitalWrite(LED_INDICATOR_PIN, LOW);
}
//==================================================================================================
