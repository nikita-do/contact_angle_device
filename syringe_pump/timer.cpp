/*
 *  controlLED.c
 *  Purpose: 
 *  Created on: Sept 18, 2023
 *      Author: Tran Ngoc Viet
 *  Note(s): Belong to School of Biomedical Engineering - International University
                                     - Vietnam National University, HCMC
 */
#include "timer.h"
#include "A4988.h"

volatile uint32_t half_microsteps = 0;
uint32_t startMillis, pumpMillis, pauseMillis, pauseDuration;
//bool TimeOut = false;
//bool motorRun = false;

hw_timer_t *timer1 = NULL;
hw_timer_t *timer2 = NULL;
volatile SemaphoreHandle_t timer1Semaphore;
volatile SemaphoreHandle_t timeOutSemaphore;
SemaphoreHandle_t motorPauseSemaphore;
portMUX_TYPE timer1Mux = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE timer2Mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR stepPulseOnTimer1()
{
  portENTER_CRITICAL_ISR(&timer1Mux);
  digitalWrite(A4988_STEP_PIN, !digitalRead(A4988_STEP_PIN));
  half_microsteps++;
  // Give a semaphore that we can check in the loop
  if((half_microsteps/2) >= microsteps) 
  xSemaphoreGiveFromISR(timer1Semaphore, NULL);
  portEXIT_CRITICAL_ISR(&timer1Mux);
}

void IRAM_ATTR timeOutOnTimer2()
{
  xSemaphoreGiveFromISR(timeOutSemaphore, NULL);
  // portENTER_CRITICAL_ISR(&timer1Mux);
  // TimeOut = true;
  // portEXIT_CRITICAL_ISR(&timer1Mux);
}

void timer_init()
{
  timer1Semaphore = xSemaphoreCreateBinary();
  timeOutSemaphore = xSemaphoreCreateBinary();
  motorPauseSemaphore = xSemaphoreCreateBinary();

  timer1 = timerBegin(1, 80, true);              // 80 MHz / 80 = 1 MHz hardware clock for easy figuring
  timerStop(timer1);
  timerAttachInterrupt(timer1, &stepPulseOnTimer1, true);  // edge (not level) triggered

  timer2 = timerBegin(2,80,true);   //1: timer 1, 80000: prescaler, true: count up
  timerStop(timer2);
  timerAttachInterrupt(timer2, &timeOutOnTimer2, true); //timer1: timer variable
  timerAlarmWrite(timer2, 1500000, true); //3000: timer ticks, true: auto reload. Alarm time = 3000 x 1000/1MHz = 3s
  timerAlarmEnable(timer2); //Enable timer
}
/*
  Run the motor 
*/
void timer_beginInject()
{
  A4988_direction(CLKWISE);
  
  pulse_time_us = SP_timeOnePulse_us(SIZE_1CC, presetVolume, 1);
  
  Serial.print("Start pumping with preset volume = ");
  Serial.println(presetVolume);
  Serial.print("pulse time = ");
  Serial.println(pulse_time_us);
  Serial.print("microsteps = ");
  Serial.println(microsteps);

  timerAlarmWrite(timer1, pulse_time_us, true);
  timerAlarmEnable(timer1);
  timerRestart(timer1);
  timerStart(timer1);

  startMillis = millis();
  pumpMillis = startMillis;
}

/*
  Check the event when the pump is finished
  return false if the pump is still running, else if finish
*/
bool timer_doneInject()
{
  if(xSemaphoreTake(timer1Semaphore, 0) == pdTRUE)
  {
    timerStop(timer1);

    Serial.println("Finish pumping");
    Serial.print("pump duration: ");
    Serial.println(millis()-pumpMillis);
    Serial.print("time duration: ");
    Serial.println(millis()-startMillis);

    half_microsteps = 0;
    return 1;
  }
  else return 0;
}

void timer_pauseInject(void)
{
  timerStop(timer1);

  pauseMillis = millis();
  Serial.println("Pause");
  Serial.print("time duration: ");
  Serial.println(pauseMillis-startMillis);

  xSemaphoreGive(motorPauseSemaphore);
}

void timer_contInject(void)
{
  timerStart(timer1);
  
  pauseDuration = millis() - pauseMillis;
  Serial.print("Continue after pausing for ");
  Serial.println(pauseDuration);
  pumpMillis += pauseDuration;
}

void timer_startTimeOut()
{
  timerRestart(timer2);
  timerStart(timer2);
}

void timer_stopTimeOut()
{
  timerStop(timer2);
}