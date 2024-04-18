/*
 *  controlLED.c
 *  Purpose: 
 *  Created on: Sept 18, 2023
 *      Author: Tran Ngoc Viet
 *  Note(s): Belong to School of Biomedical Engineering - International University
                                     - Vietnam National University, HCMC
 */
#include "A4988.h"

/*******************************************************************************
* Function Name  : L298N_SetupModePIN
* Description    : 
* Input          : time delay to change the state of LED
* Output         : None
* Return         : None
* Attention     : Modify last time 18/09/2023
*******************************************************************************/
void A4988_initGPIO(void)
{
  pinMode(A4988_STEP_PIN,OUTPUT);
  pinMode(A4988_DIR_PIN,OUTPUT);
}

void A4988_direction(dir_t dir)
{
  if(dir == CLKWISE)
    digitalWrite(A4988_DIR_PIN,LOW);
  else
    digitalWrite(A4988_DIR_PIN,HIGH);
}


