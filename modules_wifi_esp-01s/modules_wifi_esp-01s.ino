/*
  PIN CONNECTIONS
  -------------------------------
  -------------------------------
  -------------------------------

*/

//= DEFINES ========================================================================================

//= INCLUDES =======================================================================================
#include <SoftwareSerial.h>


//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED


//= VARIABLES ======================================================================================
volatile int ledState = HIGH;

// Connect the TX line from the ESP module to the Arduino's pin 2
// and the RX line from the ESP module to the Arduino's pin 3
// Emulate espSerial on pins 2/3 if not present
const byte rxPin = 2;
const byte txPin = 3;

byte baudIndex = 0;
byte baudsCnt = 14;
unsigned long bauds[] = { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 74880, 76800, 115200 };

//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);

}
//==================================================================================================
void loop() {
  //
  SoftwareSerial espSerial (rxPin, txPin); // RX, TX
  //
  unsigned long baudRate = bauds[baudIndex];
  //
  Serial.print("BAUD = "); Serial.print(baudRate);Serial.print(" index = "); Serial.println(baudIndex);
  //
  delay(2000);
  espSerial.begin(baudRate); // your esp's baud rate might be different 9600, 57600, 76800 or 115200
  delay(2000);
  Serial.println("Trying to send AT+GMR ...");
  espSerial.println("AT+GMR");
  //
  // put your main code here, to run repeatedly
  ledState = HIGH;
  digitalWrite(LED_INDICATOR_PIN, ledState);
  delay(1000);

  if(espSerial.available()) // check if the ESP module is sending a message 
  {
    while(espSerial.available())
    {
      // The esp has data so display its output to the serial window 
      char c = espSerial.read(); // read the next character.
      Serial.write(c);
    }  
  }
  
  if(Serial.available()) // check if connection through Serial Monitor from computer is available
  {
    // the following delay is required because otherwise the arduino will read the first letter of the command but not the rest
    // In other words without the delay if you use AT+RST, for example, the Arduino will read the letter A send it, then read the rest and send it
    // but we want to send everything at the same time.
    delay(1000); 
    
    String command="";
    
    while(Serial.available()) // read the command character by character
    {
        // read one character
      command+=(char)Serial.read();
    }
    espSerial.println(command); // send the read character to the Esp module
  }

  ledState = LOW;
  digitalWrite(LED_INDICATOR_PIN, ledState);
  delay(4000);
  //
  baudIndex = baudIndex + 1;
  if(baudIndex == baudsCnt) {
    baudIndex = 0;
  }
}
//==================================================================================================
