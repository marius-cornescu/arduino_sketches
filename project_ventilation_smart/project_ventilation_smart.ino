/*
  PIN CONNECTIONS

  RF-433 RX
    GND  --> GND
    VCC  --> 5V
    DATA --> D2

  DISPLAY
    SDA is the serial data
    SCL is the serial clock

    GND --> GND
    VCC --> 5V
    SDA --> A4
    SCL --> A5

*/
//= DEFINES =======================================================================================
#define UseDisplay      // Log information and actions to the Display // uses 18% of memory
#define RfLogsToSerial  // Print RF messages to Serial Terminal       // uses 9% of memory

//= INCLUDES =======================================================================================
#include <RCSwitch.h>

#ifdef UseDisplay
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
#endif

//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED

//--------------------------------------------------------------------------------------------------
const unsigned int DISPLAY_STATUS_POS = 15;

//--------------------------------------------------------------------------------------------------
// Fast Check
const unsigned int TARGET_PROTOCOL = 1;
const unsigned int TARGET_BIT_COUNT = 24;

/*
   TELECOMANDA PATRATA => A
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


const byte MAX_VALID_ACTION = 90; // any action with higher value will be ignored
const byte UNKNOWN_ACTION = 99;
const byte NO_ACTION = 100;

const byte BUTTON_1_ACTION = 1;
const byte BUTTON_2_ACTION = 2;
const byte BUTTON_3_ACTION = 3;

const byte BUTTON_4_ACTION = 4;
//--------------------------------------------------------------------------------------------------
// RELEE
const unsigned int RELEU_1 = 5; // DIGITAL PORT 5
const unsigned int RELEU_2 = 6;
const unsigned int RELEU_3 = 7;
const unsigned int RELEU_4 = 8;

//= VARIABLES ======================================================================================
volatile int ledState = HIGH;
RCSwitch rfRx = RCSwitch();

byte previousAction = UNKNOWN_ACTION;

//==================================================================================================
//**************************************************************************************************
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  //
  rfRx.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  //
  #ifdef UseDisplay
  setupDisplay();
  printActionOnDisplay(1234567, UNKNOWN_ACTION);
  #endif
}
//==================================================================================================
void loop() {
  if (rfRx.available()) {
    unsigned long buttonId = rfRx.getReceivedValue();
    if (isButtonValid_FastCheck(buttonId, rfRx.getReceivedBitlength(), rfRx.getReceivedDelay(), rfRx.getReceivedRawdata(), rfRx.getReceivedProtocol())) {

      unsigned int currentAction = computeActionForButton(buttonId);

      if (currentAction < MAX_VALID_ACTION) {
        if (currentAction != previousAction) {
          printActionOnDisplay(buttonId, currentAction);

          processAction(previousAction, currentAction);

          previousAction = currentAction;
        }

        printProgressOnDisplay();
      }
    }

    rfRx.resetAvailable();
  }
}
//==================================================================================================
bool isButtonValid_FastCheck(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int* raw, unsigned int protocol) {
  printRxToSerial(decimal, length, delay, raw, protocol);

  if ((protocol == TARGET_PROTOCOL) && (length == TARGET_BIT_COUNT)) {
    return true;
  } else {
    Serial.println("XXXX");
    return false;
  }
}
//==================================================================================================
//==================================================================================================