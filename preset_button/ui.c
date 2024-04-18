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
  pinMode (LED_START_PIN, OUTPUT);
  pinMode (LED_STOP_PIN, OUTPUT);
  pinMode (LED_5UL_PIN, OUTPUT);
  pinMode (LED_10UL_PIN, OUTPUT);
  pinMode (BTN_PRESET_PIN, INPUT);
  pinMode (BTN_START_PIN, INPUT);
  pinMode (BTN_FWD_PIN, INPUT);
  pinMode (BTN_BWD_PIN, INPUT);
}

void ui_blinkLED(uint8_t led_pin, uint16_t ms){
  //private variables but stored in global scope
  static uint16_t cnt = 0, stateOfLED = LED_STATE1; 
  switch(stateOfLED){ 
    case LED_STATE1:
    //turn led off
    digitalWrite(led_pin, LOW);
    delay(1);
    cnt++; //count the time until it equals the input delay duration
    if (cnt == ms){
      cnt = 0;
      stateOfLED = LED_STATE2;
    }
    break;
    //turn led on
    case LED_STATE2:
    digitalWrite(led_pin, HIGH);
    delay(1);
    cnt++;
    if (cnt == ms){
      cnt = 0;
      stateOfLED = LED_STATE1;
    }
    break;
  }
}

