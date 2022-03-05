//##################################################################################################
/*
 * (FILE NAME is 8.3 format = max 12 chars)
*/
//##################################################################################################
//= INCLUDES =======================================================================================
#include <SPI.h>
#include <SD.h>

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

//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //
  pinMode(LED_INDICATOR_PIN, OUTPUT);    // declare LED as output
  //
  setupSdDataFile();
}
//==================================================================================================
void loop() {
  iteration += 1;
  //
  dataFileBuffer += iteration;
  dataFileBuffer += ",";
  dataFileBuffer += millis();
  dataFileBuffer += ",";
  dataFileBuffer += (iteration * 2);
  dataFileBuffer += ",";
  dataFileBuffer += (iteration * 4);
  dataFileBuffer += "\n";
  //
  writeBufferToFile(&dataFileBuffer);
  //
  delay(TEN_SEC);
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
  SD.remove(DATA_FILENAME);
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
//##################################################################################################
