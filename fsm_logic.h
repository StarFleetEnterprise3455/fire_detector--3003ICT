#ifndef FSM_LOGIC_H
#define FSM_LOGIC_H

#include "states.h"

// Updates FSM based on sensor values
void updateState(float temperature, int smoke);

// Returns current state
FireState getState();

// Manually set a state
void setState(FireState newState);

#endif