#include <Arduino.h>
#include <DHT.h>

#include "config.h"
#include "sensors.h"

DHT dht(DHTPIN, DHTTYPE);

float simulatedTemp = 25;
int simulatedSmoke = 10;

void initSensors() {
  dht.begin();
}

float getTemperature() {

#if SIM_MODE

  if (simulatedTemp < 0) {
    return INVALID_TEMP;
  }

  return simulatedTemp;

#else

  float temp = dht.readTemperature();

  if (isnan(temp)) {
    return INVALID_TEMP;
  }

  return temp;

#endif
}

int getSmokeLevel() {

#if SIM_MODE

  if (simulatedSmoke < 0) {
    return INVALID_SMOKE;
  }

  return simulatedSmoke;

#else

  int raw = analogRead(MQ2_PIN);

  if (raw < 0 || raw > 4095) {
    return INVALID_SMOKE;
  }

  return map(raw, 0, 4095, 0, 100);

#endif
}

void handleSimulationInput() {

#if SIM_MODE

  if (Serial.available()) {

    char c = Serial.read();

    switch(c) {

      case '1':
        simulatedTemp = 25;
        simulatedSmoke = 10;
        Serial.println("SIM -> NORMAL");
        break;

      case '2':
        simulatedTemp = 60;
        simulatedSmoke = 30;
        Serial.println("SIM -> WARNING");
        break;

      case '3':
        simulatedTemp = 65;
        simulatedSmoke = 70;
        Serial.println("SIM -> CRITICAL");
        break;

      case '4':
        simulatedTemp = 90;
        simulatedSmoke = 95;
        Serial.println("SIM -> EMERGENCY");
        break;

      case '5':
        simulatedTemp = -1;
        simulatedSmoke = -1;
        Serial.println("SIM -> FAIL SAFE");
        break;
    }
  }

#endif
}