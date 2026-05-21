#include <Arduino.h>

#include "config.h"
#include "outputs.h"

void initOutputs() {

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(SPRINKLER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void applyOutputs(FireState state) {

  switch(state) {

    case NORMAL:

      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, LOW);
      digitalWrite(SPRINKLER_PIN, LOW);
      noTone(BUZZER_PIN);

      break;

    case WARNING:

      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_YELLOW, HIGH);
      digitalWrite(LED_RED, LOW);
      digitalWrite(SPRINKLER_PIN, LOW);
      tone(BUZZER_PIN, 700);

      break;

    case CRITICAL:

      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, HIGH);
      digitalWrite(SPRINKLER_PIN, HIGH);
      tone(BUZZER_PIN, 1500);

      break;

    case EMERGENCY:

      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, HIGH);
      digitalWrite(SPRINKLER_PIN, HIGH);
      tone(BUZZER_PIN, 2500);

      break;

    case FAIL_SAFE:

      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_YELLOW, HIGH);
      digitalWrite(LED_RED, HIGH);
      digitalWrite(SPRINKLER_PIN, LOW);
      tone(BUZZER_PIN, 1200);

      break;
  }
}