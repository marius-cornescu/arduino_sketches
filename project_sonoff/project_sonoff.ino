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
//= INCLUDES =======================================================================================
#include <RCSwitch.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>


//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED

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

const unsigned int BUTTON_NO_ACTION = 0;

const unsigned int BUTTON_1_ACTION = 1;
const unsigned int BUTTON_2_ACTION = 2;
const unsigned int BUTTON_3_ACTION = 3;

const unsigned int BUTTON_4_ACTION = 4;


//= VARIABLES ======================================================================================
volatile int ledState = HIGH;
RCSwitch rfRx = RCSwitch();

LiquidCrystal_I2C lcd(0x27, 16, 2);

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
  setupDisplay();
}
//**************************************************************************************************
void setupDisplay() {
  lcd.init();                 // initialise the LCD

  lcd.backlight(); // turn backlight on
  lcd.blink();     // cursor blinks
  //------------- TEST SCREEN -----------------------
  lcd.clear();         // clear the screen
  lcd.home();          // set the cursor to position 0, line 1
  // Numbers are stored but not displayed
  lcd.print("***************#123456789012345678901234***************#123456789012345678901234");  // write on the screen
  lcd.home();
  delay(500);
  //-------------------
  lcd.clear();
  //-------------------------------------------------
  lcd.noBacklight(); // turn backlight off
}
//**************************************************************************************************
//==================================================================================================
void loop() {
  if (rfRx.available()) {
    unsigned long buttonId = rfRx.getReceivedValue();
    if (isButtonValid_FastCheck(buttonId, rfRx.getReceivedBitlength(), rfRx.getReceivedDelay(), rfRx.getReceivedRawdata(), rfRx.getReceivedProtocol())) {

      unsigned int action = computeActionForButton(buttonId);

      if (action != BUTTON_NO_ACTION) {
        lcd.clear();
        lcd.home();
        lcd.print(buttonId);
        lcd.print(" = ");
        lcd.print(action);
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
unsigned int computeActionForButton(unsigned long buttonId) {
  for (byte i = 0; i < BUTTON_1_SIZE; i = i + 1) {
    if (BUTTON_1[i] == buttonId) {
      return BUTTON_1_ACTION;
    }
  }

  for (byte i = 0; i < BUTTON_2_SIZE; i = i + 1) {
    if (BUTTON_2[i] == buttonId) {
      return BUTTON_2_ACTION;
    }
  }

  for (byte i = 0; i < BUTTON_3_SIZE; i = i + 1) {
    if (BUTTON_3[i] == buttonId) {
      return BUTTON_3_ACTION;
    }
  }

  for (byte i = 0; i < BUTTON_4_SIZE; i = i + 1) {
    if (BUTTON_4[i] == buttonId) {
      return BUTTON_4_ACTION;
    }
  }

  return BUTTON_NO_ACTION;
}
//==================================================================================================
//==================================================================================================
