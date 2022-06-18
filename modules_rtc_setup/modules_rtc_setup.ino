/*

Sets the time from input and prints back time stamps for 5 seconds



*/

//= DEFINES ========================================================================================

//= INCLUDES =======================================================================================
#include <DS3231.h>
#include <Wire.h>

//= CONSTANTS ======================================================================================
const int BUTTON_PIN = D8;  // the number of the pushbutton pin

//= VARIABLES ======================================================================================
DS3231 rtcClock;
RTClib myRTC;

byte year;
byte month;
byte date;
byte dow;
byte hour;
byte minute;
byte second;

bool century = false;
bool h12Flag;
bool pmFlag;

byte lastState = HIGH;  // the previous state from the input pin
byte currentState;      // the current reading from the input pin

#if defined(ESP8266)
  ICACHE_RAM_ATTR void buttonWasPressed();
#endif

//==================================================================================================
/***************************************************
 * Setup
 *  - Open Serial and Wire connection
 *  - Explain to the user how to use the program
***************************************************/
//**************************************************************************************************
void setup() {
  // Start the serial port
  Serial.begin(57600);

  // initialize the pushbutton pin as an pull-up input
  // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonWasPressed, RISING);

  // Start the I2C interface
  Wire.begin();

  // Request the time correction on the Serial
  delay(4000);
  Serial.println("Format YYMMDDwhhmmssx");
  Serial.println("Where YY = Year (ex. 20 for 2020)");
  Serial.println("      MM = Month (ex. 04 for April)");
  Serial.println("      DD = Day of month (ex. 09 for 9th)");
  Serial.println("      w  = Day of week from 1 to 7, 1 = Sunday (ex. 5 for Thursday)");
  Serial.println("      hh = hours in 24h format (ex. 09 for 9AM or 21 for 9PM)");
  Serial.println("      mm = minutes (ex. 02)");
  Serial.println("      ss = seconds (ex. 42)");
  Serial.println("Example for input : 2004095090242x");
  Serial.println("-----------------------------------------------------------------------------");
  Serial.println("Please enter the current time to set on DS3231 ended by 'x':");
}
//**************************************************************************************************
//==================================================================================================
/***************************************************
 * Loop
 *  - Each time we receive the time correction on the Serial
 *  - Set the rtcClock of the DS3231
 *  - Echo the value from the DS3231 during 5 seconds
***************************************************/
void loop() {
  for (uint8_t i = 0; i < 5; i++) {
    // If something is coming in on the serial line, it's
    // a time correction so set the rtcClock accordingly.
    if (Serial.available()) {
      inputDateFromSerial();

      rtcClock.setClockMode(false);  // false = set to 24h

      rtcClock.setYear(year);
      rtcClock.setMonth(month);
      rtcClock.setDate(date);
      rtcClock.setDoW(dow);
      rtcClock.setHour(hour);
      rtcClock.setMinute(minute);
      rtcClock.setSecond(second);

      // Give time at next five seconds
      for (uint8_t i = 0; i < 5; i++) {
        delay(1000);
        DateTime now = myRTC.now();

        printTheTime();

        Serial.print(" since midnight 1/1/1970 = ");
        Serial.print(now.unixtime());
        Serial.print("s = ");
        Serial.print(now.unixtime() / 86400L);
        Serial.println("d");
      }

      // Notify that we are ready for the next input
      Serial.println("Please enter the current time to set on DS3231 ended by 'x':");
    }
    delay(1000);
  }

  delay(1000);
  printTheTime();

  Serial.println("====================================================");

//  if (wasButtonPressed()) {
//    setAlarm1();
//  }

  if (rtcClock.checkIfAlarm(1)) {
    Serial.println("Alarm 1 triggered");
  }
}
//==================================================================================================
/***************************************************
 * inputDateFromSerial
 *  - Read and interpret the data from the Serial input
 *  - Store the data in global variables
***************************************************/
void inputDateFromSerial() {
  // Call this if you notice something coming in on
  // the serial port. The stuff coming in should be in
  // the order YYMMDDwHHMMSS, with an 'x' at the end.
  boolean isStrComplete = false;
  char inputChar;
  byte temp1, temp2;
  char inputStr[20];

  uint8_t currentPos = 0;
  while (!isStrComplete) {
    if (Serial.available()) {
      inputChar = Serial.read();
      inputStr[currentPos] = inputChar;
      currentPos += 1;

      // Check if string complete (end with "x")
      if (inputChar == 'x') {
        isStrComplete = true;
      }
    }
  }
  Serial.println(inputStr);

  // Find the end of char "x"
  int posX = -1;
  for (uint8_t i = 0; i < 20; i++) {
    if (inputStr[i] == 'x') {
      posX = i;
      break;
    }
  }

  // Consider 0 character in ASCII
  uint8_t zeroAscii = '0';

  // Read Year first
  temp1 = (byte)inputStr[posX - 13] - zeroAscii;
  temp2 = (byte)inputStr[posX - 12] - zeroAscii;
  year = temp1 * 10 + temp2;

  // now month
  temp1 = (byte)inputStr[posX - 11] - zeroAscii;
  temp2 = (byte)inputStr[posX - 10] - zeroAscii;
  month = temp1 * 10 + temp2;

  // now date
  temp1 = (byte)inputStr[posX - 9] - zeroAscii;
  temp2 = (byte)inputStr[posX - 8] - zeroAscii;
  date = temp1 * 10 + temp2;

  // now Day of Week
  dow = (byte)inputStr[posX - 7] - zeroAscii;

  // now Hour
  temp1 = (byte)inputStr[posX - 6] - zeroAscii;
  temp2 = (byte)inputStr[posX - 5] - zeroAscii;
  hour = temp1 * 10 + temp2;

  // now Minute
  temp1 = (byte)inputStr[posX - 4] - zeroAscii;
  temp2 = (byte)inputStr[posX - 3] - zeroAscii;
  minute = temp1 * 10 + temp2;

  // now Second
  temp1 = (byte)inputStr[posX - 2] - zeroAscii;
  temp2 = (byte)inputStr[posX - 1] - zeroAscii;
  second = temp1 * 10 + temp2;
}
//==================================================================================================
void printTheTime() {
  DateTime now = myRTC.now();
  char timestamp[20];

  //Updated now.day to now.date
  sprintf(timestamp, "%02d/%02d/%02d %02d:%02d:%02d", now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());

  Serial.print(F("Date/Time: "));
  Serial.println(timestamp);
}
//==================================================================================================
void buttonWasPressed() {
  Serial.println("#");
  
  // read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);

  if (lastState == LOW && currentState == HIGH) {
    setAlarm1();
    Serial.println("State changed from LOW to HIGH");
  }

  // save the last state
  lastState = currentState;
}
//==================================================================================================
void setAlarm1() {
  DateTime now = myRTC.now();
  // set A2 to two minutes past, on current day of month.
  rtcClock.setA1Time(now.day(), now.hour(), now.minute() + 1,
                     now.second(),
                     0x0, false, false, false);
  // Turn on alarm, with external interrupt
  rtcClock.turnOnAlarm(1);
}

void setAlarm2ToRunInMinutes(byte extraMinutes) {
  DateTime now = myRTC.now();
  // set A2 to two minutes past, on current day of month.
  rtcClock.setA2Time(now.day(), now.hour(), now.minute() + extraMinutes,
                     0x0, false, false, false);
  // Turn on alarm, with external interrupt
  rtcClock.turnOnAlarm(2);
}
//==================================================================================================
