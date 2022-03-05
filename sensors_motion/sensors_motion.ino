//= INCLUDE ========================================================================================



//= CONSTANTS ======================================================================================
int CALIBRATION_TIME_MS = 10;  //the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int MOTION_PIN = 8;

int LED_INDICATOR_PIN = 2;  // choose the pin for the LED

//= VARIABLE =======================================================================================
volatile int pirState = LOW;  // we start, assuming no motion detected
volatile int val = 0;         // variable for reading the pin status


//==================================================================================================
void setup() {
  pinMode(LED_INDICATOR_PIN, OUTPUT);    // declare LED as output
  pinMode(MOTION_PIN, INPUT);            // declare sensor as input
  digitalWrite(LED_INDICATOR_PIN, LOW);  //prevents gun firing at powerup
  Serial.begin(9600);
  //give the sensor some time to calibrate
  Serial.print("# calibrating sensor ");
  for (int i = 0; i < CALIBRATION_TIME_MS; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done #");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}
//==================================================================================================
void loop() {
  val = digitalRead(MOTION_PIN);      // read input value
  if (val == HIGH) {                // check if the input is HIGH
    digitalWrite(LED_INDICATOR_PIN, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(LED_INDICATOR_PIN, LOW);  // turn LED OFF
    if (pirState == HIGH) {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
//==================================================================================================
