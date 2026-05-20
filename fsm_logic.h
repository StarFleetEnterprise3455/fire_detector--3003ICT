#pragma once

#include "states.h"

void updateState(float temperature, int smoke);

FireState getState();

void setState(FireState newState);