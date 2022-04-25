
//==================================================================================================
void defaultActionsState() {
  //
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(RELAY_3_PIN, OUTPUT);
  pinMode(RELAY_4_PIN, OUTPUT);
  //
  digitalWrite(RELAY_1_PIN, LOW);
  digitalWrite(RELAY_2_PIN, HIGH);
  digitalWrite(RELAY_3_PIN, HIGH);
  digitalWrite(RELAY_4_PIN, HIGH);
}
//==================================================================================================
byte computeActionForButton(unsigned long buttonId) {
  for (byte i = 0; i < BUTTON_1_SIZE; i = i + 1) {
    if (BUTTON_1[i] == buttonId) {
      return ACTION_1;
    }
  }

  for (byte i = 0; i < BUTTON_2_SIZE; i = i + 1) {
    if (BUTTON_2[i] == buttonId) {
      return ACTION_2;
    }
  }

  for (byte i = 0; i < BUTTON_3_SIZE; i = i + 1) {
    if (BUTTON_3[i] == buttonId) {
      return ACTION_3;
    }
  }

  for (byte i = 0; i < BUTTON_4_SIZE; i = i + 1) {
    if (BUTTON_4[i] == buttonId) {
      return ACTION_4;
    }
  }

  return ACTION_NOP;
}
//==================================================================================================
void processAction(byte previousAction, byte currentAction) {
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
}
//==================================================================================================
void actions_ACTION2() {
  //
  digitalWrite(RELAY_1_PIN, HIGH);
  digitalWrite(RELAY_2_PIN, LOW);
  digitalWrite(RELAY_3_PIN, HIGH);
}
//==================================================================================================
void actions_ACTION3() {
  //
  digitalWrite(RELAY_1_PIN, HIGH);
  digitalWrite(RELAY_2_PIN, HIGH);
  digitalWrite(RELAY_3_PIN, LOW);
}
//==================================================================================================
void actions_ACTION4() {
  //
  digitalWrite(RELAY_1_PIN, HIGH);
  digitalWrite(RELAY_2_PIN, HIGH);
  digitalWrite(RELAY_3_PIN, HIGH);
}
//==================================================================================================
