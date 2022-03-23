//= INCLUDE ========================================================================================



//= CONSTANTS ======================================================================================
int CALIBRATION_TIME_MS = 30;  //the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int MOTION_PIN = 4;

int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED

//= VARIABLE =======================================================================================
volatile long pirStateChangeMS  = 0;   // when the state of PIR changed
volatile int pirStateCurrent   = LOW; // current state of pin
volatile int pirStatePrevious  = LOW; // previous state of pin

//==================================================================================================
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  //
  pinMode(LED_INDICATOR_PIN, OUTPUT);    // declare LED as output
  pinMode(MOTION_PIN, INPUT);            // declare sensor as input
  digitalWrite(LED_INDICATOR_PIN, LOW);  //prevents gun firing at powerup
  //give the sensor some time to calibrate
  Serial.print("# calibrating sensor ");
  for (int i = 0; i < CALIBRATION_TIME_MS; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done #");
  delay(50);
  pirStateChangeMS = millis(); // init value
  Serial.println("SENSOR ACTIVE");
}
//==================================================================================================
void loop() {
  pirStatePrevious = pirStateCurrent;          // store old state
  pirStateCurrent = digitalRead(MOTION_PIN);   // read new state
  
  if (pirStatePrevious == LOW && pirStateCurrent == HIGH) {   // pin state change: LOW -> HIGH
    pirStateChangeMS = millis() - pirStateChangeMS; // delta
    Serial.print("State change after [");
    Serial.print(pirStateChangeMS);
    Serial.print(" ms] => ");
    //
    Serial.println("Motion detected!");
    //
    digitalWrite(LED_INDICATOR_PIN, HIGH);
    pirStateChangeMS = millis();
    
  } else if (pirStatePrevious == HIGH && pirStateCurrent == LOW) {   // pin state change: HIGH -> LOW
    pirStateChangeMS = millis() - pirStateChangeMS; // delta
    Serial.print("State change after [");
    Serial.print(pirStateChangeMS);
    Serial.print(" ms] => ");
    //
    Serial.println("Motion stopped!");
    //
    digitalWrite(LED_INDICATOR_PIN, LOW);
    pirStateChangeMS = millis();
    
  }
  
  delay(100);
}
//==================================================================================================
