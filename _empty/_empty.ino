/*
  PIN CONNECTIONS
  -------------------------------
  -------------------------------
  -------------------------------

*/

//= DEFINES ========================================================================================
#if defined(ESP8266)
  // interrupt handler and related code must be in RAM on ESP8266,
  // according to issue #46.
  #define RECEIVE_ATTR ICACHE_RAM_ATTR
  #define VAR_ISR_ATTR
  #define HIGH 0x0
  #define LOW  0x1
#endif

//= INCLUDES =======================================================================================



//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED


//= VARIABLES ======================================================================================
volatile int ledState = HIGH;


//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
}
//==================================================================================================
void loop() {
  // put your main code here, to run repeatedly
  ledState = HIGH;
  digitalWrite(LED_INDICATOR_PIN, ledState);
  delay(1000);

  ledState = LOW;
  digitalWrite(LED_INDICATOR_PIN, ledState);
  delay(4000);
}
//==================================================================================================
