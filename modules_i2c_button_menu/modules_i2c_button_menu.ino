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
//#define UseDisplay      // Log information and actions to the Display // uses ??% of memory
//#define I2CLogsToSerial  // Print I2C messages to Serial Terminal       // uses ??% of memory

//= INCLUDES =======================================================================================
#ifdef I2CLogsToSerial
#include <stdio.h> // for function sprintf
#endif

#include <Wire.h>
#include "PCF8575.h"

//= CONSTANTS ======================================================================================
const byte LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED
const byte LED_MENU = P0;     // 

#ifdef DEBUG
const byte TIME_TICK = 500;
#else
const byte TIME_TICK = 10;
#endif

const byte I2C_ADDRESS = 0x20;

const byte ON = LOW;
const byte OFF = HIGH;

//----------------------------------
const byte BTN_NONE = 0;
//----------------------------------
const byte BTN_VENTILATION_1 = 1;
const byte BTN_VENTILATION_2 = 2;
const byte BTN_VENTILATION_3 = 3;
//----------------------------------
const byte BTN_UP = 4;
const byte BTN_DOWN = 5;
const byte BTN_BACK = 6;
const byte BTN_FWARD = 7;
const byte BTN_ENTER = 8;
//----------------------------------

//= VARIABLES ======================================================================================
volatile byte ledState = ON;

// adjust addresses if needed
PCF8575 buttons(I2C_ADDRESS);  // add switches to lines  (used as input)


//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  digitalWrite(LED_INDICATOR_PIN, ledState);
  //
  menu_Setup();
  //..............................
  delay(TIME_TICK * 10);
}
//==================================================================================================
void loop()
{
  ledState = (ledState == ON) ? OFF : ON;
  digitalWrite(LED_INDICATOR_PIN, ledState);

  menu_ActIfActivity();

  delay(TIME_TICK * 10);
}
//**************************************************************************************************
void menu_Setup() {
  Wire.begin();
  //
  // Set pinMode
  // Side A
  buttons.pinMode(P0, OUTPUT);
  buttons.pinMode(P1, OUTPUT);
  buttons.pinMode(P2, OUTPUT);
  buttons.pinMode(P3, OUTPUT);
  buttons.pinMode(P4, OUTPUT);
  buttons.pinMode(P5, OUTPUT);
  buttons.pinMode(P6, OUTPUT);
  buttons.pinMode(P7, OUTPUT);
  // Side B
  buttons.pinMode(P8, INPUT);
  buttons.pinMode(P9, INPUT);
  buttons.pinMode(P10, INPUT);
  buttons.pinMode(P11, INPUT);
  buttons.pinMode(P12, INPUT);
  buttons.pinMode(P13, INPUT);
  buttons.pinMode(P14, INPUT);
  buttons.pinMode(P15, INPUT);
  //..............................
  buttons.begin();
  //..............................
  buttons.digitalWrite(LED_MENU, OFF);
  //..............................
}
//**************************************************************************************************
//==================================================================================================
void menu_ActIfActivity() {
  byte button = get_button(buttons);

  if(button == BTN_ENTER) {
    menu_print();
    menu_process_loop(buttons);
  }
}
//==================================================================================================
byte get_button(PCF8575 &io) {
  byte response = BTN_NONE;
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
  //Serial.println(buffer);
#endif

  return response;
}
//==================================================================================================
void menu_print() {

}
//==================================================================================================
void menu_process_loop(PCF8575 &io) {
  byte prevs_button = BTN_NONE;
  byte button = get_button(io);

  while(button != BTN_BACK) {
    //
    if (button != BTN_NONE) {
      io.digitalWrite(LED_MENU, ON);// indication of activity
      menu_process_button_action(button, prevs_button);
    }
    //
    delay(TIME_TICK);
    io.digitalWrite(LED_MENU, OFF);// indication of activity
    prevs_button = button;
    button = get_button(io);
  }

  io.digitalWrite(LED_MENU, OFF);
}
//==================================================================================================
void menu_process_button_action(byte &button, byte &prevs_button) {
  if(button == prevs_button) {
    return; // ignore phake multi-press
  }

  #ifdef I2CLogsToSerial
    char buffer[200];
    sprintf(buffer, "|button=%d|prevs_button=%d|", button, prevs_button);
    Serial.println(buffer);
  #endif

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