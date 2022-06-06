//= CONSTANTS ======================================================================================
const byte LED_MENU = P8;     // 

#define BUTTONS_I2C_ADDRESS 0x20

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
// adjust addresses if needed
PCF8575 buttons(BUTTONS_I2C_ADDRESS);  // add switches to lines  (used as input)


//**************************************************************************************************
void menu_Setup() {
  Wire.begin();
  //
  // Set pinMode
  // Side A
  buttons.pinMode(P0, INPUT);
  buttons.pinMode(P1, INPUT);
  buttons.pinMode(P2, INPUT);
  buttons.pinMode(P3, INPUT);
  buttons.pinMode(P4, INPUT);
  buttons.pinMode(P5, INPUT);
  buttons.pinMode(P6, INPUT);
  buttons.pinMode(P7, INPUT);
  // Side B
  buttons.pinMode(P8, OUTPUT);
  buttons.pinMode(P9, OUTPUT);
  buttons.pinMode(P10, OUTPUT);
  buttons.pinMode(P11, OUTPUT);
  buttons.pinMode(P12, OUTPUT);
  buttons.pinMode(P13, OUTPUT);
  buttons.pinMode(P14, OUTPUT);
  buttons.pinMode(P15, OUTPUT);
  //..............................
  buttons.begin();
  //..............................
  buttons.digitalWrite(LED_MENU, OFF);
  //..............................
  delay(TIME_TICK * 10);
}
//**************************************************************************************************
//==================================================================================================
void menu_ActIfActivity() {
  byte button = get_button(buttons);

  if(button == BTN_ENTER) {
    digitalWrite(LED_INDICATOR_PIN, HIGH);
    //
    display_Print2ndLine("<MANUAL>");
    display_ShowProgress();
    //
    menu_print();
    menu_process_loop(buttons);
    //
    display_Print2ndLine("");
    digitalWrite(LED_INDICATOR_PIN, LOW);
  }
}
//==================================================================================================
byte get_button(PCF8575 &io) {
  byte response = BTN_NONE;
  PCF8575::DigitalInput io_vals = io.digitalReadAll();

  if(io_vals.p7 == 1) {
    response = BTN_VENTILATION_1;
  } else if(io_vals.p6 == 1) {
    response = BTN_VENTILATION_2;
  } else if(io_vals.p5 == 1) {
    response = BTN_VENTILATION_3;
  } else if(io_vals.p5 == 1) {
    response = BTN_UP;
  } else if(io_vals.p3 == 1) {
    response = BTN_DOWN;
  } else if(io_vals.p2 == 1) {
    response = BTN_BACK;
  } else if(io_vals.p1 == 1) {
    response = BTN_FWARD;
  } else if(io_vals.p0 == 1) {
    response = BTN_ENTER;
  } else {
    response = BTN_NONE;
  }

#ifdef I2CLogsToSerial
  char buffer[200];
  sprintf(buffer, "|0=%d|1=%d|2=%d|3=%d|4=%d|5=%d|6=%d|7=%d| => %d", io_vals.p0, io_vals.p1, io_vals.p2, io_vals.p3, io_vals.p4, io_vals.p5, io_vals.p6, io_vals.p7, response);
  Serial.println(buffer);
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
      actions_ACTION1();
      break;
    case BTN_VENTILATION_2:
      actions_ACTION2();
      break;
    case BTN_VENTILATION_3:
      actions_ACTION3();
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