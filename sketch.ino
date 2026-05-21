#include <Arduino.h>

#include "config.h"
#include "sensors.h"
#include "fsm.h"
#include "outputs.h"
#include "wifi.h"

float tempFiltered = 25;

void setup() {

  Serial.begin(115200);

  initWiFi();

  initSensors();

  initOutputs();

  Serial.println("FIRE DETECTION SYSTEM");
}

void loop() {

  handleSimulationInput();

  float temp = getTemperature();
  int smoke = getSmokeLevel();

  if (temp != INVALID_TEMP) {

    tempFiltered =
      (ALPHA * temp) +
      ((1 - ALPHA) * tempFiltered);

    updateState(tempFiltered, smoke);

  } else {

    updateState(INVALID_TEMP, smoke);
  }

  FireState state = getState();

  applyOutputs(state);

  Serial.print("Temp: ");
  Serial.print(tempFiltered);

  Serial.print(" | Smoke: ");
  Serial.print(smoke);

  Serial.print(" | State: ");
  Serial.println(state);

  delay(1000);
}