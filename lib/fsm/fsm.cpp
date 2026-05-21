#include <Arduino.h>

#include "fsm.h"

// THRESHOLDS

const float TEMP_THRESHOLD = 50.0;
const int SMOKE_THRESHOLD = 300;

const float EXTREME_TEMP = 70.0;
const int EXTREME_SMOKE = 500;

const float SAFE_TEMP = 40.0;
const int SAFE_SMOKE = 200;


// CURRENT STATE

static FireState currentState = NORMAL;

// SET STATE

void setState(FireState newState) {

  if (newState != currentState) {

    currentState = newState;

    Serial.print("STATE CHANGED TO: ");

    switch(currentState) {

      case NORMAL:
        Serial.println("NORMAL");
        break;

      case WARNING:
        Serial.println("WARNING");
        break;

      case CRITICAL:
        Serial.println("CRITICAL");
        break;

      case EMERGENCY:
        Serial.println("EMERGENCY");
        break;
    }
  }
}

// GET CURRENT STATE

FireState getState() {
  return currentState;
}

// FSM TRANSITION LOGIC

void updateState(float temperature, int smoke) {

  switch(currentState) {
    // NORMAL STATE

    case NORMAL:
      // Move to WARNING

      if (temperature > TEMP_THRESHOLD ||
          smoke > SMOKE_THRESHOLD) {

        setState(WARNING);
      }

      break;

    // WARNING STATE

    case WARNING:
      // Move to CRITICAL

      if (temperature > TEMP_THRESHOLD &&
          smoke > SMOKE_THRESHOLD) {

        setState(CRITICAL);
      }

      // Return to NORMAL

      else if (temperature < SAFE_TEMP &&
               smoke < SAFE_SMOKE) {

        setState(NORMAL);
      }

      break;

    // CRITICAL STATE

    case CRITICAL:
      // Move to EMERGENCY

      if (temperature > EXTREME_TEMP ||
          smoke > EXTREME_SMOKE) {

        setState(EMERGENCY);
      }

      // Return to WARNING

      else if (temperature < TEMP_THRESHOLD &&
               smoke < SMOKE_THRESHOLD) {

        setState(WARNING);
      }

      break;


    // EMERGENCY STATE
    case EMERGENCY:

      // Optional recovery logic

      if (temperature < SAFE_TEMP &&
          smoke < SAFE_SMOKE) {

        setState(NORMAL);
      }

      break;
  }
}