/*
  ui.c -- See ui.h for info
*/
	
/* Include header file and application specific libraries */
#include "ui.h"

/* Private macros, constants, types and global variables */
#define LED_STATE1    0
#define LED_STATE2    1

/* Private function prototypes*/

/* Private function implementations*/

/* Exported function implementations*/
/*
  Purpose: Configure the LEDs as output, button as input
  Input:  none
  Output: none
*/
void ui_initGPIO(void)
{
  pinMode (LED1_PIN, OUTPUT);
  pinMode (LED2_PIN, OUTPUT);
  pinMode (LED3_PIN, OUTPUT);
  pinMode (LED4_PIN, OUTPUT);
  pinMode (BTN_PRESET_PIN, INPUT);
  pinMode (BTN_START_PIN, INPUT);
  pinMode (BTN_FWD_PIN, INPUT);
  pinMode (BTN_BWD_PIN, INPUT);
}

void ui_blinkLED(unsigned int ms){
  //private variables but stored in global scope
  static uint16_t cnt = 0, stateOfLED = LED_STATE1; 
  switch(stateOfLED){ 
    case LED_STATE1:
    //turn LEDs off
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, LOW);
    digitalWrite(LED4_PIN, LOW);
    delay(1);
    cnt++; //count the time until it equals the input delay duration
    if (cnt == ms){
      cnt = 0;
      stateOfLED = LED_STATE2;
    }
    break;
    // unfinished code
    case LED_STATE2:
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, HIGH);
    digitalWrite(LED4_PIN, HIGH);
    delay(1);
    cnt++;
    if (cnt == ms){
      cnt = 0;
      stateOfLED = LED_STATE1;
    }
    break;
  }
}

void ui_alternateLED(unsigned int ms){
  //private variables but stored in global scope
  static uint16_t cnt = 0, stateOfLED = LED_STATE1; 
  switch(stateOfLED){
    case LED_STATE1:
    //turn LEDs off
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, LOW);
    digitalWrite(LED4_PIN, HIGH);
    delay(1);
    cnt++; //count the time until it equals the input delay duration
    if (cnt == ms){
      cnt = 0;
      stateOfLED = LED_STATE2;
    }
    break;
    // unfinished code
    case LED_STATE2:
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, HIGH);
    digitalWrite(LED4_PIN, LOW);
    delay(1);
    cnt++;
    if (cnt == ms){
      cnt = 0;
      stateOfLED = LED_STATE1;
    }
    break;
  }
}

