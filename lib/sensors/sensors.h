#pragma once

void initSensors();

float getTemperature();

int getSmokeLevel();

void handleSimulationInput();

extern float simulatedTemp;
extern int simulatedSmoke;