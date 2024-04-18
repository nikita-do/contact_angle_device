/*
  Control the system LEDs and button
  Created on:
  by
  Version: 
*/  
/* Define to prevent recursive inclusion */
#ifndef SYRINGEPUMP_H__
#define SYRINGEPUMP_H__

/* Include system library */
#include <Arduino.h>

#define MICROSTEP_RESOLUTION      16 
#define STEP_PER_REVOLUTION       200
#define ROD_PITCH                 2 

#define DIA_1CC                   4.78
#define DIA_3CC                   8.66
#define DIA_5CC                   12.06

typedef enum {SIZE_1CC, SIZE_3CC, SIZE_5CC} s_size_t;
typedef enum {VOL_5UL=5, VOL_10UL=10} volume_t;

extern uint32_t microsteps;
extern uint32_t pulse_time_us;
extern volume_t presetVolume;

#ifdef __cplusplus
extern "C" {
#endif

uint32_t SP_microstepsOneInjection(s_size_t size, volume_t volume);
uint32_t SP_timeOnePulse_us(s_size_t size, volume_t volume, uint16_t flow_rate);

#ifdef __cplusplus
}
#endif
#endif