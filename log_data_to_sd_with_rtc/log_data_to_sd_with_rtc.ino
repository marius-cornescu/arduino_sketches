//##################################################################################################
/*
 * (FILE NAME is 8.3 format = max 12 chars)
*/
//##################################################################################################
//= INCLUDES =======================================================================================
#include <LowPower.h> // power management

#include <RTClib.h>   // RT clock

#include <SD.h>       // SD card

//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN; // choose the pin for the LED
//
const int SD_CHIP_SELECT = 10;
//
const char DATA_FILENAME[] = "/raw_data.txt";
//
const unsigned long TEN_SEC = 10000;

//= VARIABLES ======================================================================================
// string to buffer output
volatile String dataFileBuffer;
//
volatile int iteration = 0;
//
RTC_DS3231 rtc;
char timestamp[20];

//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  //
  pinMode(LED_INDICATOR_PIN, OUTPUT);    // declare LED as output
  //
  setupRTCModule();
  //
  setupSdDataFile();
  //
}
//==================================================================================================
void loop() {
  iteration += 1;
  //
  updateTimestamp();

  dataFileBuffer += timestamp;
  dataFileBuffer += ",";
  dataFileBuffer += iteration;
  dataFileBuffer += ",";
  dataFileBuffer += (iteration * 2);
  dataFileBuffer += ",";
  dataFileBuffer += (iteration * 4);
  dataFileBuffer += "\n";
  //
  writeBufferToFile(&dataFileBuffer);
  //
  LowPower.idle(SLEEP_10S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                SPI_OFF, USART0_OFF, TWI_OFF);
}
//==================================================================================================
// RTC setup
//==================================================================================================
void setupRTCModule() {
  // SETUP RTC MODULE
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1);
  }

  // automatically sets the RTC to the date & time on PC this sketch was compiled
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
//==================================================================================================
// LOG FILE UTILS
//==================================================================================================
void setupSdDataFile() {
  // reserve 1kB for String used as a buffer
  dataFileBuffer.reserve(1024);
  // init the SD card
  if (!SD.begin(SD_CHIP_SELECT)) {
    Serial.println("SD-Card:SETUP: Card failed, or not present");
    while (1); // don't do anything more
  }
  //
  Serial.println("SD-Card:SETUP: initialized.");
  // start with an empty file
  //SD.remove(DATA_FILENAME);
}
//==================================================================================================
void writeBufferToFile(String *fileBuffer) {
  digitalWrite(LED_INDICATOR_PIN, HIGH);
  //
  Serial.print((*fileBuffer));
  // only one file can be open at a time
  File dataFile = SD.open(DATA_FILENAME, FILE_WRITE);
  //
  if (dataFile) {
    dataFile.print((*fileBuffer));
    dataFile.close();
    // remove written data from buffer
    (*fileBuffer).remove(0);
  } else {
    Serial.print("SD-Card:WRITE: error opening file ");
    Serial.println(DATA_FILENAME);
  }
  //
  digitalWrite(LED_INDICATOR_PIN, LOW);
}
//==================================================================================================
// RTC UTILS
//==================================================================================================
void updateTimestamp() {
  DateTime now = rtc.now();
  sprintf(timestamp, "%02d/%02d/%02d_%02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second()); 
  Serial.print(F("Date/Time: "));
  Serial.println(timestamp);
}
//==================================================================================================
//##################################################################################################
