/*
  PIN CONNECTIONS
  -------------------------------
  -------------------------------
  -------------------------------

*/

//= DEFINES ========================================================================================
// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

//= INCLUDES =======================================================================================
#include "Secrets.h"

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED
const char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASSWORD;

//= VARIABLES ======================================================================================
ESP8266 wifi(&Serial);
BlynkTimer timer;

int uptimeCounter;
String someStaticData = "SomeStaticData";

//==================================================================================================
// This function will run every time Blynk connection is established
BLYNK_CONNECTED() {
  Blynk.sendInternal("meta", "set", "Device Model", "ArduinoNano-ESP8266");
  //Blynk.sendInternal("meta", "set", "Model", "ArduinoNano-ESP8266");
  //Blynk.sendInternal("meta", "set", "Serial Number", "AdruNano-SmartVent-001");
  Blynk.sendInternal("meta", "set", "Serial Number", "AdruNano-Blynk-001");
  //
  //get data stored in virtual pin V0 from server
  //Blynk.syncVirtual(V0);
  
  // Request Blynk server to re-send latest values for all pins
  Blynk.syncAll();
}
//==================================================================================================
// restoring counter from server
BLYNK_WRITE(V0) {
  //restoring int value
  uptimeCounter = param.asInt();
}
//==================================================================================================
void timer_OnTrigger() {
  uptimeCounter++;

  //storing int and string in V0 pin on server
  Blynk.virtualWrite(V0, uptimeCounter);

  //updating value display with uptimeCounter
  //Blynk.virtualWrite(V1, uptimeCounter);
}
//==================================================================================================
//**************************************************************************************************
void setup()
{
  // Debug console
  //Serial.begin(115200);

  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
  digitalWrite(LED_INDICATOR_PIN, HIGH);

  // Set ESP8266 baud rate
  //EspSerial.begin(ESP8266_BAUD);
  Serial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  timer.setInterval(1000L, timer_OnTrigger);

  digitalWrite(LED_INDICATOR_PIN, LOW);
}
//**************************************************************************************************
//==================================================================================================
void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!

  delay(30*1000);
}
//==================================================================================================
