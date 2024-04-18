/*
 *  controlLED.h
 *  Purpose: 
 *  Created on: Sept 18, 2023
 *      Author: Tran Ngoc Viet
 *  Note(s): Belong to School of Biomedical Engineering - International University
                                     - Vietnam National University, HCMC
 */
#ifndef A4988_H__ 
#define A4988_H__
#include <Arduino.h>

#define A4988_STEP_PIN    18
#define A4988_DIR_PIN     5

typedef enum {CLKWISE, COUNTER_CLKWISE} dir_t;

#ifdef __cplusplus
extern "C" {
#endif

void A4988_initGPIO(void);
void A4988_direction(dir_t dir);

#ifdef __cplusplus
}
#endif
#endif
