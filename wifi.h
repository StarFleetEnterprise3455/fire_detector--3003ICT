#pragma once

#include <Arduino.h>
#include "fsm_logic.h"   // IMPORTANT: single source of truth

void initWiFi();
void sendFireAlert(FireState state);