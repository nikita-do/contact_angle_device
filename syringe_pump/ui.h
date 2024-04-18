/*
  Control the system indicators and user interface: LEDs, buzzer and buttons
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
#define LED_START_PIN   12
#define LED_STOP_PIN    14
#define LED_5UL_PIN     27
#define LED_10UL_PIN    26
#define BTN_PRESET_PIN  25
#define BTN_START_PIN   32
#define BTN_BWD_PIN     35
#define BTN_FWD_PIN     34
#define BUZZ_PIN        13

#ifdef __cplusplus
extern "C" {
#endif

/* Exported function prototypes */
void ui_initGPIO(void);
void ui_blinkLED(uint8_t led_pin, uint16_t ms);
void ui_buzzer(unsigned int ms);

#ifdef __cplusplus
}
#endif
#endif /*__FILENAME_H*/