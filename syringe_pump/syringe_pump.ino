// /*
//   Control the Syringe Pump - SM template

//   Created on 1/4/24
//   by Ngoc Do
//   Version: 2.0.0

//   This code is belong to Capstone Course - BMEIU
// */

// /* Include libraries---------------------------- */


// /* Private types ------------------------------- */
// // Place your state and external event definition here.
// typedef enum {S_BLINK_ALL, S_BLINK_ALTER} state_t;
// typedef enum {E_BLINK_ALL, E_BLINK_ALTER, NO_EVENT} event_t;

// /* Private macro ------------------------------- */

// /* Private variables ----------------------------*/
// state_t currentState = S_BLINK_ALL;
// state_t nextState = S_BLINK_ALL;

// /* Private function prototypes ------------------*/
// event_t checkEvent(void);
// void doAction (state_t currentState);
// void exitAction  (state_t currentState);
// void entryAction (state_t nextState);
// void stateMachine(event_t event);

// /* Private functions --------- ------------------*/
// /*
//  * Purpose:       Return an event if a condition is met. 
//  * Note:          Return NO_EVENT if no condition is met
//  * Parameter:     None
//  * Return:        Event being triggered. 
//  *                Event is one of E_BLINK_ALL and E_BLINK_ALTER.
//  */
// event_t checkEvent(void)
// {
//   if(digitalRead(BUTTON_PIN)==0)
//   {
//     delay(20);
//     while(digitalRead(BUTTON_PIN)==0);
//     switch (currentState)
//     {
//       case S_BLINK_ALL:
//         return E_BLINK_ALTER;
//         break;
//       case S_BLINK_ALTER:
//         return E_BLINK_ALL;
//         break;
//     }
//   }
//   else return NO_EVENT;
// }

// /*
//  * Purpose:       Run action of the current state. The action is repeatedly executed
//  *                if no new event is detected.
//  * Parameter:     Current state of the machine. 
//  *                currentState is one of S_BLINK_ALL and S_BLINK_ALTER.
//  * Return:        None
//  */
// void doAction(state_t currentState)
// {
//   switch (currentState) // check the current state
//   {
//     case S_BLINK_ALL:
//       system_blinkLED(1000);
//     break;
//     case S_BLINK_ALTER:
//       system_alternateLED(500);
//     break;
//   }
// }

// /*
//  * Purpose:       Perform exit action of the current state. The action is executed once
//  *                when a new transition has happened.
//  * Parameter:     Current state of the machine. 
//  *                currentState is one of S_BLINK_ALL and S_BLINK_ALTER.
//  * Return:        None
//  */
// void exitAction(state_t currenState)
// {
//   switch (currentState) // check the current state
//   {
//      case S_BLINK_ALL:
//          // doing nothing
//      break;
//      case S_BLINK_ALTER:
//          // doing nothing
//      break;
//   }
// }

// /*
//  * Purpose:       Perform entry action of the next state. The action is executed once
//  *                when a new transition has happened.
//  * Parameter:     Next state of the machine. 
//  *                nextState is one of S_BLINK_ALL and S_BLINK_ALTER.
//  * Return:        None
//  */
// void entryAction(state_t nextState)
// {
//   switch (nextState) // check the next state
//   {
//      case S_BLINK_ALL:
//          // doing nothing
//      break;
//      case S_BLINK_ALTER:
//          // doing nothing
//      break;
//   }
// }

// /*
//  * Purpose:       Implement change if a new event has occured.
//  *                If a transition occurs, perform exitAction() of the current state,
//  *                entryAction() of the next state and update the current state.
//  *                Perform stateAction() according to the current state no matter if 
//  *                a transition has occured or not.
//  * Parameter:     Event returned from checkEvent() function.
//  * Return:        None
//  */
// void stateMachine(event_t event)
// {
//   switch (currentState) // check the current state
//   {
//     case S_BLINK_ALL:
//     // check for any new event exist
//       switch (event)
//       {
//         case E_BLINK_ALTER:
//           nextState = S_BLINK_ALTER;
//         break;
//       }
//     break;
//     case S_BLINK_ALTER:
//     // check for any new event exist
//       switch (event)
//       {
//         case E_BLINK_ALL:
//           nextState = S_BLINK_ALL;
//         break;
//       }
//     break;
//   }
//     if (currentState != nextState)  // transistion has occurred
//     {
//       exitAction(currentState); // run exitAction() of the current state
//       entryAction(nextState); // run entryAction() of the next state
//       currentState = nextState;  // update the state
//     }
//     doAction(currentState); // run main action of the current state
// }

#include "timer.h"
#include "ui.h"
#include "syringePump.h"
#include "A4988.h"

void setup() {
  // Configure GPIO pins, serial monitor and baud rate here
  Serial.begin(9600);
  A4988_initGPIO();
  ui_initGPIO();
  timer_init();

  pulse_time_us = SP_timeOnePulse_us(SIZE_1CC, VOL_5UL,1);

  Serial.println (pulse_time_us);
  Serial.println (microsteps);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BTN_START_PIN)==LOW)
  {
    delay(20);
    while(digitalRead(BTN_START_PIN)==LOW);
    Serial.println("detect button");
    timer_beginInject();
  }

  if(timer_doneInject())
  Serial.println("Done inject");  
}

