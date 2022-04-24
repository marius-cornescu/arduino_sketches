#ifdef UseDisplay

LiquidCrystal_I2C lcd(0x27, 16, 2);
byte progress = 0;                  // used to indicate progress on display

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
  lcd.noBlink();
}
//**************************************************************************************************

#endif

//==================================================================================================
void printActionOnDisplay(unsigned long buttonId, byte currentAction) {
  #ifdef UseDisplay
  
  lcd.home();
  lcd.print("_______:        ");
  lcd.home();
  lcd.print(buttonId);
  lcd.print(": ");
  lcd.print(currentAction);

  #endif
}
//==================================================================================================
void printProgressOnDisplay() {
  #ifdef UseDisplay
  
  lcd.setCursor(DISPLAY_STATUS_POS, 1);        // set the cursor to position 15, line 2
  progress = progress + 1;
  if (progress == 1) {
    lcd.print("+");
  } else if (progress == 2) {
    lcd.print("-");
  } else if (progress == 3) {
    lcd.print("#");
  } else if (progress == 4) {
    lcd.print("|");
  } else {
    lcd.print("*");
    progress = 0;
  }

  #endif
}
//==================================================================================================
