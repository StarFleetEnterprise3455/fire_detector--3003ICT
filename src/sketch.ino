<<<<<<< HEAD
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
=======
// SENSOR FUNCTIONS

int readTemperature() {

    int value = analogRead(TEMP_SENSOR_PIN);

    // Simulated sensor failure
    if (value < 0 || value > 4095) {
        return INVALID_TEMP;
    }

    return map(value, 0, 4095, 0, 100);
>>>>>>> 6d68c084bf1950f1bb11ea7d17d2cb479be23f6b
}

int readSmoke() {

<<<<<<< HEAD
  handleSimulationInput();

  float temp = getTemperature();
  int smoke = getSmokeLevel();

  if (temp != INVALID_TEMP) {

    tempFiltered =
      (ALPHA * temp) +
      ((1 - ALPHA) * tempFiltered);

    updateState(tempFiltered, smoke);

  } else {
=======
    int value = analogRead(SMOKE_SENSOR_PIN);

    // Simulated sensor failure
    if (value < 0 || value > 4095) {
        return INVALID_SMOKE;
    }

    return value;
}

// SAFETY OUTPUT FUNCTIONS

void activateNormalState() {

    digitalWrite(GREEN_LED_PIN, HIGH);

    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);

    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(SPRINKLER_PIN, LOW);
}

void activateWarningState() {

    digitalWrite(GREEN_LED_PIN, LOW);

    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);

    // Mild warning buzzer
    tone(BUZZER_PIN, 1000);

    delay(200);
>>>>>>> 6d68c084bf1950f1bb11ea7d17d2cb479be23f6b

    updateState(INVALID_TEMP, smoke);
  }

<<<<<<< HEAD
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
=======
    Serial.println("Warning panel activated");
}

void activateCriticalState() {

    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);

    digitalWrite(RED_LED_PIN, HIGH);

    // Loud alarm
    tone(BUZZER_PIN, 2500);

    // Activate sprinkler
    digitalWrite(SPRINKLER_PIN, HIGH);

    Serial.println("Emergency warning panel activated");
    Serial.println("Sprinkler system deployed");

    sendFireAlert(CRITICAL);
}

void activateEmergencyState() {

    digitalWrite(RED_LED_PIN, HIGH);

    // Continuous loud alarm
    tone(BUZZER_PIN, 3000);

    // Keep sprinkler active
    digitalWrite(SPRINKLER_PIN, HIGH);

    Serial.println("FULL EMERGENCY MODE");
    Serial.println("Gas suppression/sprinklers active");

    sendFireAlert(EMERGENCY);
}

void activateFailSafeMode() {

    digitalWrite(YELLOW_LED_PIN, HIGH);

    // Warning buzzer
    tone(BUZZER_PIN, 1500);

    Serial.println("FAIL SAFE MODE");
    Serial.println("Manual inspection required");

    sendFireAlert(FAIL_SAFE);
}

// SETUP

void setup() {

    Serial.begin(115200);

    initWiFi();

    pinMode(BUZZER_PIN, OUTPUT);

    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);

    pinMode(SPRINKLER_PIN, OUTPUT);

    activateNormalState();
}

// MAIN LOOP

void loop() {

    int temperature = readTemperature();
    int smoke = readSmoke();

    bool tempFailed = (temperature == INVALID_TEMP);
    bool smokeFailed = (smoke == INVALID_SMOKE);

    // SENSOR FAILURE LOGIC

    if (tempFailed && smokeFailed) {

        Serial.println("Both sensors failed");

        currentState = FAIL_SAFE;

        activateFailSafeMode();

        delay(2000);
        return;
    }

    if (tempFailed || smokeFailed) {

        Serial.println("One sensor failed");
        Serial.println("Remaining sensors still monitoring");

        sendFireAlert(WARNING);
    }

    // FIRE DETECTION LOGIC

    bool highTemp = temperature > TEMP_THRESHOLD;
    bool highSmoke = smoke > SMOKE_THRESHOLD;

    // NORMAL STATE
    if (!highTemp && !highSmoke) {

        currentState = NORMAL;

        activateNormalState();
    }

    // WARNING STATE
    else if (highTemp || highSmoke) {

        currentState = WARNING;

        activateWarningState();
    }

    // CRITICAL STATE
    if (highTemp && highSmoke) {

        currentState = CRITICAL;

        activateCriticalState();
    }

    // EMERGENCY STATE
    if (temperature > 80 && smoke > 700) {

        currentState = EMERGENCY;

        activateEmergencyState();
    }

    // SERIAL MONITOR OUTPUT

    Serial.print("Temperature: ");
    Serial.println(temperature);

    Serial.print("Smoke: ");
    Serial.println(smoke);

    Serial.print("Current State: ");
    Serial.println(currentState);

    delay(1000);
}
>>>>>>> 6d68c084bf1950f1bb11ea7d17d2cb479be23f6b
