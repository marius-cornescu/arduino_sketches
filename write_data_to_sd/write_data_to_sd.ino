//##################################################################################################
/*
*/
//##################################################################################################
//= INCLUDES =======================================================================================
#include <SPI.h>
#include <SD.h>

//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED

const int SD_CHIP_SELECT = 4;

// file name to use for writing
const char DATA_FILENAME[] = "measurements.txt";

const unsigned long TEN_SEC = 10000;

//= VARIABLES ======================================================================================
// File object to represent file
File sdDataFile;
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
  //
  dataFileBuffer = iteration;
  dataFileBuffer += ",";
  dataFileBuffer += (iteration*2);
  dataFileBuffer += ",";
  dataFileBuffer += (iteration*4);
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
    Serial.println("Card failed, or not present");
    while (1); // don't do anything more
  }

  Serial.println("SD-Card:SETUP: initialized.");

  // start with an empty file
  // SD.remove(DATA_FILENAME);

  digitalWrite(LED_INDICATOR_PIN, HIGH);
  // try to open the file for writing
//  sdDataFile = SD.open(DATA_FILENAME, FILE_WRITE);
//  if (!sdDataFile) {
//    Serial.print("SD-Card:SETUP: error opening file ");
//    Serial.println(DATA_FILENAME);
//    //while (1); // don't do anything more
//  }

  digitalWrite(LED_INDICATOR_PIN, LOW);
}
//==================================================================================================
void writeBufferToFile(String *fileBuffer) {
  digitalWrite(LED_INDICATOR_PIN, HIGH);
  // only one file can be open at a time
  File dataFile = SD.open(DATA_FILENAME, FILE_WRITE);
  //
  if (dataFile) {
    dataFile.println((*fileBuffer));
    dataFile.close();
    // print to the serial port too:
    Serial.println((*fileBuffer));
  } else {
    Serial.print("SD-Card:WRITE: error opening file ");
    Serial.println(DATA_FILENAME);
  }
  //
  digitalWrite(LED_INDICATOR_PIN, LOW);
}
//==================================================================================================
//void writeBufferToFileNonBlock(String *fileBuffer) {
//  // check if the SD card is available to write data without blocking
//  // and if the buffered data is enough for the full chunk size
//  unsigned int chunkSize = dataFile.availableForWrite();
//  if (chunkSize && (*fileBuffer).length() >= chunkSize) {
//    // write to file and blink LED
//    digitalWrite(LED_INDICATOR_PIN, HIGH);
//    dataFile.write((*fileBuffer).c_str(), chunkSize);
//    digitalWrite(LED_INDICATOR_PIN, LOW);
//
//    // remove written data from buffer
//    (*fileBuffer).remove(0, chunkSize);
//  }
//}
//==================================================================================================
//##################################################################################################
