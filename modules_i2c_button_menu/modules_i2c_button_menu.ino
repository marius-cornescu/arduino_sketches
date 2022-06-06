/*
  PIN CONNECTIONS
  -------------------------------
  I2C 16bit expansion board
    GND  --> GND
    VCC  --> 5V
    D1 --> SDA
    D2 --> SCL
  -------------------------------

*/
//= DEFINES =======================================================================================
//#define DEBUG
//#define UseDisplay      // Log information and actions to the Display // uses 18% of memory
#define I2CLogsToSerial  // Print I2C messages to Serial Terminal       // uses ??% of memory

//= INCLUDES =======================================================================================
#ifdef I2CLogsToSerial
#include <stdio.h> // for function sprintf
#endif

#include <Wire.h>
#include "PCF8575.h"

//#define NOT_SEQUENTIAL_PINOUT

//= CONSTANTS ======================================================================================
const uint8_t LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED

const uint8_t I2C_ADDRESS = 0x20;

const uint8_t ON = LOW;
const uint8_t OFF = HIGH;

//----------------------------------
const uint8_t BTN_NONE = 0;
//----------------------------------
const uint8_t BTN_VENTILATION_1 = 1;
const uint8_t BTN_VENTILATION_2 = 2;
const uint8_t BTN_VENTILATION_3 = 3;
//----------------------------------
const uint8_t BTN_UP = 4;
const uint8_t BTN_DOWN = 5;
const uint8_t BTN_BACK = 6;
const uint8_t BTN_FWARD = 7;
const uint8_t BTN_ENTER = 8;
//----------------------------------

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

  // pcf8575.digitalWrite(P0, ledState);
  // pcf8575.digitalWrite(P1, (ledState == ON) ? OFF : ON);
  digitalWrite(LED_INDICATOR_PIN, ledState);

  uint8_t button = get_button(pcf8575);

  if(button == BTN_ENTER) {
    menu_print();
    menu_process_loop(pcf8575);
  }

  delay(5000);
}
//==================================================================================================
uint8_t get_button(PCF8575 &io) {
  uint8_t response = BTN_NONE;
  PCF8575::DigitalInput io_values = io.digitalReadAll();

  if(io_values.p8 == 1) {
    response = BTN_VENTILATION_1;
  } else if(io_values.p9 == 1) {
    response = BTN_VENTILATION_2;
  } else if(io_values.p10 == 1) {
    response = BTN_VENTILATION_3;
  } else if(io_values.p11 == 1) {
    response = BTN_UP;
  } else if(io_values.p12 == 1) {
    response = BTN_DOWN;
  } else if(io_values.p13 == 1) {
    response = BTN_BACK;
  } else if(io_values.p14 == 1) {
    response = BTN_FWARD;
  } else if(io_values.p15 == 1) {
    response = BTN_ENTER;
  } else {
    response = BTN_NONE;
  }

#ifdef I2CLogsToSerial
  char buffer[200];
  sprintf(buffer, "|8=%d|9=%d|10=%d|11=%d|12=%d|13=%d|14=%d|15=%d| => %d", io_values.p8, io_values.p9, io_values.p10, io_values.p11, io_values.p12, io_values.p13, io_values.p14, io_values.p15, response);
  Serial.println(buffer);
#endif

  return response;
}
//==================================================================================================
void menu_print() {

}
//==================================================================================================
void menu_process_loop(PCF8575 &io) {
  uint8_t button = get_button(io);

  while(button != BTN_BACK) {
    // indication of activity
    ledState = (ledState == ON) ? OFF : ON;
    io.digitalWrite(P0, ledState);
    io.digitalWrite(P1, ledState);
    //
    if (button != BTN_NONE) {
      menu_process_button_action(button);
    }
    //
    delay(500);
    button = get_button(io);
  }


}
//==================================================================================================
void menu_process_button_action(uint8_t &button) {
  switch (button) {
    case BTN_VENTILATION_1:
      Serial.println("VENTILATION SPEED 1"); // FIXME
      break;
    case BTN_VENTILATION_2:
      Serial.println("VENTILATION SPEED 2"); // FIXME
      break;
    case BTN_VENTILATION_3:
      Serial.println("VENTILATION SPEED 3"); // FIXME
      break;
    case BTN_UP:
      // statements
      break;
    case BTN_DOWN:
      // statements
      break;
    case BTN_BACK:
      // statements
      break;
    case BTN_FWARD:
      // statements
      break;
    case BTN_ENTER:
      // statements
      break;
    default:
      // statements
      break;
  }
}
//==================================================================================================