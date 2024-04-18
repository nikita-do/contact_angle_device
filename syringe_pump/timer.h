/*
 *  timer.h
 *  Purpose: 
 *  Created on: Sept 18, 2023
 *      Author: Tran Ngoc Viet
 *  Note(s): Belong to School of Biomedical Engineering - International University
                                     - Vietnam National University, HCMC
 */
#ifndef TIMER_H__ 
#define TIMER_H__
#include <Arduino.h>
#include "syringePump.h"

extern volatile SemaphoreHandle_t timeOutSemaphore;

//extern bool TimeOut;
// define macro
void timer_init();
void timer_beginInject();
void timer_stopInject(void);
void timer_contInject(void);
bool timer_doneInject(void);

void timer_startTimeOut();
void timer_stopTimeOut(void);

#endif
