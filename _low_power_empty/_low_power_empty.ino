//= INCLUDES =======================================================================================
#include "LowPower.h"


//= CONSTANTS ======================================================================================
const int LED_INDICATOR_PIN = LED_BUILTIN;  // choose the pin for the LED


//= VARIABLES ======================================================================================
volatile int ledState = HIGH;


//==================================================================================================
void setup() {
  // Enter idle state for 8 s with the rest of peripherals turned off
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                SPI_OFF, USART0_OFF, TWI_OFF);
  
  // initialize digital pin LED_INDICATOR_PIN as an output.
  pinMode(LED_INDICATOR_PIN, OUTPUT);
}
//==================================================================================================
void loop() {
  // put your main code here, to run repeatedly
  ledState = HIGH;
  digitalWrite(LED_INDICATOR_PIN, ledState);
  // Enter idle state for 1s with the rest of peripherals turned off
  LowPower.idle(SLEEP_4S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                SPI_OFF, USART0_OFF, TWI_OFF);

  ledState = LOW;
  digitalWrite(LED_INDICATOR_PIN, ledState);
  // Enter idle state for 8s with the rest of peripherals turned off
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                SPI_OFF, USART0_OFF, TWI_OFF);
}
//==================================================================================================
