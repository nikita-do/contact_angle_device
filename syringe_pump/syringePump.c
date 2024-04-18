#include <math.h>
#include "syringePump.h"

#define MICROSTEP_PER_REVOLUTION  (MICROSTEP_RESOLUTION * STEP_PER_REVOLUTION)

uint32_t microsteps = 0;
uint32_t pulse_time_us = 0;

/*
  Return number of microsteps for one injection from syringe size and volume,
  based on given rod pitch and microstep/revolution
  Input: 
    - size: 1cc, 3cc or 5cc
    - volume: 5uL or 10uL
  Output: number of microsteps
*/
uint32_t SP_microstepsOneInjection(s_size_t size, volume_t volume)
{
  float area_mm2;
  switch (size)
  {
    case SIZE_1CC:
      area_mm2 = (DIA_1CC/2)*(DIA_1CC/2)*M_PI;
    break;
    case SIZE_3CC:
      area_mm2 = (DIA_3CC/2)*(DIA_3CC/2)*M_PI;
    break;
    case SIZE_5CC:
      area_mm2 = (DIA_5CC/2)*(DIA_5CC/2)*M_PI;
    break;
  }
  return rintf(volume/((area_mm2 * ROD_PITCH)/MICROSTEP_PER_REVOLUTION));
}

/*
  Return time/pulse from syringe size, flow rate and volume
  Input: 
    - size: 1cc, 3cc or 5cc
    - flow rate: 1uL/s, 5uL/s (in uL/s, <= 4 mL/s)
    - volume: 5uL or 10uL
  Output: time (in us)/pulse
*/
uint32_t SP_timeOnePulse_us(s_size_t size, volume_t volume, uint16_t flow_rate)
{
  microsteps = SP_microstepsOneInjection(size, volume);
  uint32_t timeOneInjection_us = (volume/flow_rate) * 1000000;
  uint32_t timeOneMicrostep_us = timeOneInjection_us/microsteps;
  return timeOneMicrostep_us/2;
}


