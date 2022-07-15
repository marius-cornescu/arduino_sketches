/*
   PIN CONNECTIONS

   GND  --> GND
   VCC  --> 5V
   DATA --> D7

   Send Button -> D8
   Program Button -> D9

*/
//= DEFINES ========================================================================================
#define PIN_RF_TX 7 // RF Transmiter on pin D7
#define PIN_BTN_SEND 8   // Send button on pin 8
#define PIN_BTN_PROG 9   // Program button on pin 9

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

const int rf_pulse_length = 351;
const unsigned int rf_code_length = 24;
const unsigned int rf_repeat_count = 4;
const int rf_protocol = 1; // (default is 1, will work for most outlets)

//= VARIABLES ======================================================================================
static uint8_t lastBtnSendState = LOW;
static uint8_t lastBtnProgState = LOW;

unsigned long rf_code = 9037304;
//const unsigned long rf_code = 6145633;

unsigned long lastInterrupt;
bool is_programming = false;

RCSwitch rfTx = RCSwitch();

//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  //----------------------------------------
  //
  rfTx.enableTransmit(PIN_RF_TX);
  //
  rfTx.setProtocol(rf_protocol);
  // set pulse length.
  rfTx.setPulseLength(rf_pulse_length);
  // set number of transmission repetitions.
  rfTx.setRepeatTransmit(rf_repeat_count);
  //----------------------------------------
  //
  pinMode(PIN_BTN_SEND, INPUT_PULLUP);
  lastBtnSendState = digitalRead(PIN_BTN_SEND);
  pinMode(PIN_BTN_PROG, INPUT_PULLUP);
  lastBtnProgState = digitalRead(PIN_BTN_PROG);
  //attachInterrupt(digitalPinToInterrupt(PIN_BTN_PROG), onProgramButtonPressed, FALLING);
  //
  delay(100);
}
//==================================================================================================
void loop() {
  if (isSendButtonPressed()) {
    Serial.println("Send Button pressed!");
    transmitRfCode(rf_code, rf_code_length);
  }

  if(isProgramButtonPressed()) {
    Serial.println("PROGRAM Button pressed!");
    readNewRfCodeFromSerial();
  }

  //Serial.println("*");
  delay(100);
}
//==================================================================================================
bool isSendButtonPressed() {
  uint8_t currentBtnSendState = digitalRead(PIN_BTN_SEND);
  if (currentBtnSendState != lastBtnSendState) {
    lastBtnSendState = currentBtnSendState;
    if (currentBtnSendState == HIGH) {
      return true;
    }
  }
  return false;
}
//==================================================================================================
bool isProgramButtonPressed() {
  uint8_t currentBtnState = digitalRead(PIN_BTN_PROG);
  if (currentBtnState != lastBtnProgState) {
    lastBtnProgState = currentBtnState;
    if (currentBtnState == HIGH) {
      return true;
    }
  }
  return false;
}
//==================================================================================================
void transmitRfCode(unsigned long code, unsigned int code_length) {
  digitalWrite(LED_INDICATOR_PIN, HIGH);
  rfTx.send(code, code_length);
  delay(100);
  digitalWrite(LED_INDICATOR_PIN, LOW);
}
//==================================================================================================
void onProgramButtonPressed() {
  if (millis() - lastInterrupt > 500) { // we set a 100ms no-interrupts window
    Serial.println("PROGRAM Button pressed!");
    //
    readNewRfCodeFromSerial();
    //
    delay(100);
    lastInterrupt = millis();
  }
}
//==================================================================================================
void readNewRfCodeFromSerial() {
    //
    Serial.println("Current config:");
    Serial.println(rf_code);
    Serial.println(rf_pulse_length);
    Serial.println(rf_code_length);
    Serial.println(rf_repeat_count);
    Serial.println(rf_protocol);
    //
    Serial.println("Enter the new RF433 code (e.g. 9037304):");
    //
    delay(100);
    while (Serial.available() == 0) {}
    //
    long new_rf_code = Serial.parseInt();
    //
    Serial.print("New RF433 code = ");
    Serial.println(new_rf_code);
    //
    rf_code = new_rf_code;
}
//==================================================================================================
