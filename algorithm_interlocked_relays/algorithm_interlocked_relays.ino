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
