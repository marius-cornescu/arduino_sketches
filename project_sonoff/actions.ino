

//==================================================================================================
byte computeActionForButton(unsigned long buttonId) {
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

  return NO_ACTION;
}
//==================================================================================================
byte processAction(byte previousAction, byte currentAction) {
  
}
//==================================================================================================
