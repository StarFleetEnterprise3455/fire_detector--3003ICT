#include <Arduino.h>

#include "fsm_logic.h"

void setup() {
    Serial.begin(115200);
}

void loop() {

    // TEMPORARY fake sensor values
    float temperature = 60.0;
    int smoke = 350;

    // Update FSM
    updateState(temperature, smoke);

    // Get current state
    FireState current = getState();

    delay(1000);
}