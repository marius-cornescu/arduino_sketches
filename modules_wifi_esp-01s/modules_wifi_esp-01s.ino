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
const char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASSWORD;

//= VARIABLES ======================================================================================
ESP8266 wifi(&Serial);

//==================================================================================================
//**************************************************************************************************
void setup()
{
  // Debug console
  Serial.begin(115200);

  // Set ESP8266 baud rate
  //EspSerial.begin(ESP8266_BAUD);
  Serial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);
}
//**************************************************************************************************
//==================================================================================================
void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
//==================================================================================================
