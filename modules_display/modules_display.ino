/*
 * PIN CONNECTIONS
 * 
 * SDA is the serial data
 * SCL is the serial clock
 *
 * GND --> GND white
 * VCC --> 5V  grey
 * SDA --> A4  red
 * SCL --> A5  blue
 * 
 */
//= INCLUDE ========================================================================================
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//= CONSTANTS ======================================================================================
int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED

//= VARIABLE =======================================================================================
volatile long pirStateChangeMS  = 0;   // when the state of PIR changed

/* 
 * Set the correct chip for your LCD
 * Use 0x27 when you have the PCF8574 chip made by NXP
 * Use 0x3F when you have the PCF8574A chip made by Ti (Texas Instruments)
 * The last two digits represent the LCD size
 * e.g. 20x4 or 16x2
 */  
//LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  //
  pinMode(LED_INDICATOR_PIN, OUTPUT);    // declare LED as output
  //
  setupDisplay();
}
//==================================================================================================
void loop() {

  lcd.clear();
  lcd.home();

  delay(10000);
  
  lcd.home();
  lcd.print("Hello!");

  delay(10000);


  lcd.home();
  lcd.print("1234567890");

  delay(10000);


  lcd.setCursor(1, 0);        // set the cursor to position 1, line 1
  lcd.print("1234567890ABCDEFGHIJ1234567890ABCDEFGHIJ1234567890ABCDEFGHIJ");
  lcd.home();
  delay(10000);


  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("AB");
  lcd.home();
  delay(20000);
  
}
//==================================================================================================
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
  delay(100);
  //-------------------
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("$$$$$$$$$$$$$$$#12345678901234567890123#");
  lcd.setCursor(0, 1);
  lcd.print("$$$$$$$$$$$$$$$#12345678901234567890123#");
  lcd.home();
  delay(100);
  //-------------------------------------------------
  lcd.noBacklight(); // turn backlight off
}
//==================================================================================================
