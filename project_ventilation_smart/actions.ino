
//==================================================================================================
void defaultActionsState() {
  //
  pinMode(RELEU_1_PIN, OUTPUT);
  pinMode(RELEU_2_PIN, OUTPUT);
  pinMode(RELEU_3_PIN, OUTPUT);
  pinMode(RELEU_4_PIN, OUTPUT);
  //
  digitalWrite(RELEU_1_PIN, LOW);
  digitalWrite(RELEU_2_PIN, HIGH);
  digitalWrite(RELEU_3_PIN, HIGH);
  digitalWrite(RELEU_4_PIN, HIGH);
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
  digitalWrite(RELEU_1_PIN, LOW);
  digitalWrite(RELEU_2_PIN, HIGH);
  digitalWrite(RELEU_3_PIN, HIGH);
}
//==================================================================================================
void actions_ACTION2() {
  //
  digitalWrite(RELEU_1_PIN, HIGH);
  digitalWrite(RELEU_2_PIN, LOW);
  digitalWrite(RELEU_3_PIN, HIGH);
}
//==================================================================================================
void actions_ACTION3() {
  //
  digitalWrite(RELEU_1_PIN, HIGH);
  digitalWrite(RELEU_2_PIN, HIGH);
  digitalWrite(RELEU_3_PIN, LOW);
}
//==================================================================================================
void actions_ACTION4() {
  //
  digitalWrite(RELEU_1_PIN, HIGH);
  digitalWrite(RELEU_2_PIN, HIGH);
  digitalWrite(RELEU_3_PIN, HIGH);
}
//==================================================================================================
