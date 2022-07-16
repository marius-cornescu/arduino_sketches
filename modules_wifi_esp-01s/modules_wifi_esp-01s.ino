/*
  PIN CONNECTIONS
  -------------------------------
  -------------------------------
  -------------------------------

*/

//= DEFINES ========================================================================================

//= INCLUDES =======================================================================================


//= CONSTANTS ======================================================================================


//= VARIABLES ======================================================================================


//==================================================================================================

//==================================================================================================
// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLbd69Q8M8"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "czTd10GWtBcf_q8FH6oY_EfSNY37c6vA"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

//ESP8266 wifi(&EspSerial);
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
