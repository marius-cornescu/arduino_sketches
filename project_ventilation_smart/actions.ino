//= CONSTANTS ======================================================================================
#define ACTION4_DELAY 5

//= VARIABLES ======================================================================================

//==================================================================================================
void actions_SetupInitialState() {
  //
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(RELAY_3_PIN, OUTPUT);
  pinMode(RELAY_4_PIN, OUTPUT);
  //
  actions_SetStateToDefault();
}
//==================================================================================================
void actions_SetStateToDefault() {
    //
    digitalWrite(RELAY_1_PIN, LOW);
    digitalWrite(RELAY_2_PIN, HIGH);
    digitalWrite(RELAY_3_PIN, HIGH);
    digitalWrite(RELAY_4_PIN, HIGH);
}
//==================================================================================================
byte actions_ComputeActionForButton(unsigned long buttonId) {
  for (byte i = 0; i < ACTION_1_BUTTONS_SIZE; i = i + 1) {
    if (ACTION_1_BUTTONS[i] == buttonId) {
      return ACTION_1;
    }
  }

  for (byte i = 0; i < ACTION_2_BUTTONS_SIZE; i = i + 1) {
    if (ACTION_2_BUTTONS[i] == buttonId) {
      return ACTION_2;
    }
  }

  for (byte i = 0; i < ACTION_3_BUTTONS_SIZE; i = i + 1) {
    if (ACTION_3_BUTTONS[i] == buttonId) {
      return ACTION_3;
    }
  }

  for (byte i = 0; i < ACTION_4_BUTTONS_SIZE; i = i + 1) {
    if (ACTION_4_BUTTONS[i] == buttonId) {
      return ACTION_4;
    }
  }

  return ACTION_NOP;
}
//==================================================================================================
void actions_ProcessAction(byte currentAction) {
  switch (currentAction) {
    //-------------------------------------------
    case ACTION_1:
      actions_ACTION1();
      break;
    //-------------------------------------------
    case ACTION_2:
      actions_ACTION2();
      break;
    //-------------------------------------------
    case ACTION_3:
      actions_ACTION3();
      break;
    //-------------------------------------------
    case ACTION_4:
      actions_ACTION4();
      break;
    //-------------------------------------------
    default:
      actions_DEFAULT();
      break;
  }
}
//==================================================================================================
void actions_DEFAULT() {
  // Do Nothing - Unmapped Action - BUG
}
//==================================================================================================
void actions_ACTION1() {
  //
  digitalWrite(RELAY_1_PIN, LOW);
  digitalWrite(RELAY_2_PIN, HIGH);
  digitalWrite(RELAY_3_PIN, HIGH);
  //
  display_Print1stLine("VENT: SPEED", 1);
}
//==================================================================================================
void actions_ACTION2() {
  //
  digitalWrite(RELAY_1_PIN, HIGH);
  digitalWrite(RELAY_2_PIN, LOW);
  digitalWrite(RELAY_3_PIN, HIGH);
  //
  display_Print1stLine("VENT: SPEED", 2);
}
//==================================================================================================
void actions_ACTION3() {
  //
  digitalWrite(RELAY_1_PIN, HIGH);
  digitalWrite(RELAY_2_PIN, HIGH);
  digitalWrite(RELAY_3_PIN, LOW);
  //
  display_Print1stLine("VENT: SPEED", 3);
}
//==================================================================================================
void actions_ACTION4() {
  //
  actions_ACTION3();
  clock_Alarm1_SetInMinutesWithAction(ACTION4_DELAY, ACTION_1);
  //
}
//==================================================================================================
