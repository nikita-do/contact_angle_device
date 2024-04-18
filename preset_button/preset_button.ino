/*
  Press a button to select the pump volume.

  Transistion between 2 states: S_IDLE and S_PRESET
*/
/* Include libraries---------------------------- */
#include "ui.h"
#include "syringePump.h"
#include "timer.h"
/* Private types ------------------------------- */
// Place your state and external event definition here. Examples:
typedef enum {S_IDLE, S_PRESET} state_t;
typedef enum {E_PRESET, NO_EVENT} event_t;

/* Private macro ------------------------------- */

/* Private global variables ----------------------------*/
// Declare all global variables here. Examples:
state_t currentState = S_PRESET;
state_t nextState = S_PRESET;

// Initial volume is 5uL
uint8_t presetVolume = VOL_5UL;

/* Private function prototypes ------------------*/
event_t checkExternalEvent(void);
void doAction (state_t currentState);
void exitAction  (state_t currentState);
void entryAction (state_t nextState);
void stateMachine(event_t event);

/* Private functions --------- ------------------*/
/*
 * Purpose:       Return an event according to the current state if a condition is met. 
 * Note:          Return NO_EVENT if no condition is met
 * Parameter:     None
 * Return:        Event being triggered. 
 *                Event is E_PRESET
 */
event_t checkExternalEvent(void)
{
  if (digitalRead(BTN_PRESET_PIN)==LOW)
  {
    delay(20);
    while(digitalRead(BTN_PRESET_PIN)==LOW);
    return E_PRESET;
  }
  else return NO_EVENT;
}

/*
 * Purpose:       Run action of the current state. The action is repeatedly executed
 *                if no new event is detected.
 * Parameter:     Current state of the machine. 
 *                currentState is one of S_IDLE and S_PRESET.
 * Return:        None
 */
void doAction(state_t currentState)
{
  switch (currentState) // check the current state
  {
    case S_IDLE:
      if(presetVolume == VOL_5UL){
        digitalWrite(LED_5UL_PIN, HIGH);
      }
      else {
        digitalWrite(LED_10UL_PIN, HIGH);
      }
    break;
    case S_PRESET:
      if(presetVolume == VOL_5UL){
        ui_blinkLED(LED_5UL_PIN, 300);
      }
      else {
        ui_blinkLED(LED_10UL_PIN, 300);
      }
    break;
  }
}

/*
 * Purpose:       Perform exit action of the current state. The action is executed once
 *                when a new transition has happened.
 * Parameter:     Current state of the machine. 
 *                currentState is one of S_IDLE and S_PRESET.
 * Return:        None
 */
void exitAction(state_t currentState)
{
  switch (currentState) // check the current state
  {
    case S_IDLE:
      digitalWrite(LED_5UL_PIN, LOW);
      digitalWrite(LED_10UL_PIN, LOW);
    break;
    case S_PRESET:
      timer_stopTimeOut();
      digitalWrite(LED_5UL_PIN, LOW);
      digitalWrite(LED_10UL_PIN, LOW);
    break;
  }
}

/*
 * Purpose:       Perform entry action of the next state. The action is executed once
 *                when a new transition has happened.
 * Parameter:     Next state of the machine. 
 *                nextState is one of S_IDLE and S_PRESET.
 * Return:        None
 */
void entryAction(state_t nextState)
{
  switch (nextState) // check the current state
  {
    case S_IDLE:
      
    break;
    case S_PRESET:
      // do something here
      switch (presetVolume)
      {
        case VOL_5UL:
          presetVolume = VOL_10UL;
        break;
        case VOL_10UL:
          presetVolume = VOL_5UL;
        break;
      }
      timer_startTimeOut();
    break;
  }
}

/*
 * Purpose:       Implement change if a new event has occured.
 *                If a transition occurs, perform exitAction() of the current state,
 *                entryAction() of the next state and update the current state.
 *                Perform stateAction() according to the current state no matter if 
 *                a transition has occured or not.
 * Parameter:     Event returned from checkExternalEvent() function.
 * Return:        None
 */
void stateMachine(event_t event)
{
  switch (currentState) // check the current state
  {
    case S_IDLE:
    // check for any new event exist
      switch (event)
      {
        case E_PRESET:
          // update the next state according to state machine diagram 
          // or do something here (self-transition event)
          nextState = S_PRESET;
        break;
      }
    break;
    case S_PRESET:
    // check for any new event exist
      switch (event)
      {
        case E_PRESET:
          // update the next state according to state machine diagram
          // or do something here (self-transition event)
          exitAction(S_PRESET);
          entryAction(S_PRESET);
        break;
      }
      if(xSemaphoreTake(timeOutSemaphore, 0) == pdTRUE)
      {
        nextState = S_IDLE;
      }
    break;
  }
  if (currentState != nextState)  // transistion has occurred
  {
    exitAction(currentState); // run exitAction() of the current state
    entryAction(nextState); // run entryAction() of the next state
    currentState = nextState;  // update the state
  }
  doAction(currentState); // run main action of the current state
}

void setup() {
  // Configure GPIO pins, serial monitor and timer here
  ui_initGPIO();
  timer_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  stateMachine(checkExternalEvent());
}
