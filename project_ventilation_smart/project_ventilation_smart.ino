/*
  PIN CONNECTIONS
  -------------------------------
  RF-433 RX
    GND  --> GND
    VCC  --> 5V
    DATA --> D2
  -------------------------------
  DISPLAY
    SDA is the serial data
    SCL is the serial clock

    GND --> GND
    VCC --> 5V
    SDA --> A4
    SCL --> A5
  -------------------------------
  RELAY
    D5  --> Relay1
    D6  --> Relay2
    D7  --> Relay3
    D8  --> Relay4
  -------------------------------

*/
//= DEFINES =======================================================================================
//#define DEBUG
#define UseDisplay      // Log information and actions to the Display // uses 18% of memory
//#define RfLogsToSerial  // Print RF messages to Serial Terminal       // uses 9% of memory
//#define I2CLogsToSerial  // Print I2C messages to Serial Terminal       // uses ??% of memory

//= INCLUDES =======================================================================================
#if defined(DEBUG) || defined(RfLogsToSerial) || defined(I2CLogsToSerial)
#include <stdio.h> // for function sprintf
#endif

#include <Wire.h>   // using I2C
#include "PCF8575.h"
#include <RCSwitch.h>

#ifdef UseDisplay
#include <LiquidCrystal_I2C.h>
#endif

//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED
//------------------------------------------------
#ifdef DEBUG
const byte TIME_TICK = 500;
#else
const byte TIME_TICK = 10;
#endif
//------------------------------------------------
// MANUAL MODE BUTTON
const char MANUAL_MODE_PIN = 4;
const bool IS_PRESSED = false;

//------------------------------------------------
// Fast Check
const unsigned int TARGET_PROTOCOL = 1;
const unsigned int TARGET_BIT_COUNT = 24;
//------------------------------------------------
/*
   TELECOMANDA PATRATA (123)    => A
   TELECOMANDA 4 butoane (ABCD) => B
   TELECOMANDA 3 butoane (123)  => C
*/
const unsigned int BUTTON_1_SIZE = 3;
const unsigned int BUTTON_2_SIZE = 3;
const unsigned int BUTTON_3_SIZE = 3;

const unsigned int BUTTON_4_SIZE = 1;

const unsigned long BUTTON_1[BUTTON_1_SIZE] = {/*A*/9094708, /*B*/6145640, /*C*/9468385};
const unsigned long BUTTON_2[BUTTON_2_SIZE] = {/*A*/9094705, /*B*/6145636, /*C*/9468386};
const unsigned long BUTTON_3[BUTTON_3_SIZE] = {/*A*/9094706, /*B*/6145634, /*C*/9468388};

const unsigned long BUTTON_4[BUTTON_4_SIZE] = {/*B*/6145633};

//------------------------------------------------
const byte ACTION_MAX_VALID = 90; // any action with higher value will be ignored
const byte ACTION_UNKNOWN = 99;
const byte ACTION_NOP = 100;
//
const byte ACTION_1 = 1;
const byte ACTION_2 = 2;
const byte ACTION_3 = 3;
//
const byte ACTION_4 = 4;
//
const byte ACTION_5 = 5;
const byte ACTION_6 = 6;
//--------------------------------------------------------------------------------------------------
// RELEE
const unsigned int RELAY_1_PIN = 5; // DIGITAL PORT 5
const unsigned int RELAY_2_PIN = 6; // DIGITAL PORT 6
const unsigned int RELAY_3_PIN = 7; // DIGITAL PORT 7
const unsigned int RELAY_4_PIN = 8; // DIGITAL PORT 8
//
//= VARIABLES ======================================================================================
volatile int ledState = HIGH;
RCSwitch rfRx = RCSwitch();

byte previousAction = ACTION_UNKNOWN;

//==================================================================================================
//**************************************************************************************************
void setup() {
#ifdef DEBUG
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
#endif
  // Button port is in PullUp mode
  pinMode(MANUAL_MODE_PIN, INPUT_PULLUP);
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  //
  setupActionsState();
  //
  rfRx.enableReceive(0);  // RF Receiver on INT0 => pin D2
  //
  menu_Setup();
  //
#ifdef UseDisplay
  display_Setup();
  display_Print1stLine("START-UP", ACTION_1);
#endif
}
//==================================================================================================
void loop() {
  if (rfRx.available()) {
    unsigned long buttonId = rfRx.getReceivedValue();
    if (isButtonValid_FastCheck(buttonId, rfRx.getReceivedBitlength(), rfRx.getReceivedDelay(), rfRx.getReceivedRawdata(), rfRx.getReceivedProtocol())) {

      unsigned int currentAction = computeActionForButton(buttonId);

      if (currentAction < ACTION_MAX_VALID) {
        if (currentAction != previousAction) {
          display_Print1stLine(buttonId, currentAction);

          processAction(previousAction, currentAction);

          previousAction = currentAction;
        }

        display_ShowProgress();
      }
    }

    rfRx.resetAvailable();

  } else {
    // GETS EXECUTED CONTINUOUSLY WHEN NO MESSAGE
    menu_ActIfActivity();
    delay(TIME_TICK * 50);
  }
}
//==================================================================================================
bool isButtonValid_FastCheck(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int* raw, unsigned int protocol) {
  printRxToSerial(decimal, length, delay, raw, protocol);

  if ((protocol == TARGET_PROTOCOL) && (length == TARGET_BIT_COUNT)) {
    return true;
  } else {
    #ifdef DEBUG
      Serial.println("XXXX");
    #endif
    return false;
  }
}
//==================================================================================================
//==================================================================================================
