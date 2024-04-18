/*
  Control the LEDs and button for user interface
  Created on:
  by
  Version: 
*/  
/* Define to prevent recursive inclusion */
#ifndef UI_H__
#define UI_H__

/* Include system library */
#include <Arduino.h>

/* Exported macros, constants, types and global variables */
#define LED1_PIN        12
#define LED2_PIN        14
#define LED3_PIN        27
#define LED4_PIN        26
#define BTN_PRESET_PIN  25
#define BTN_START_PIN   32
#define BTN_BWD_PIN     35
#define BTN_FWD_PIN     34

#ifdef __cplusplus
extern "C" {
#endif

/* Exported function prototypes */
void ui_initGPIO(void);
void ui_blinkLED(unsigned int ms);
void ui_alternateLED(unsigned int ms);

#ifdef __cplusplus
}
#endif
#endif /*__FILENAME_H*/