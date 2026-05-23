#include <Arduino.h>

#include "fsm.h"
#include "config.h"
#include "wifi.h"

// ================= CURRENT STATE =================
FireState state = NORMAL;

// ================= CRITICAL TIMER =================
unsigned long criticalStartTime = 0;

const unsigned long CRITICAL_TIMEOUT = 10000;

// ================= GET CURRENT STATE =================
FireState getState() {

  return state;
}

// ================= SET STATE =================
void setState(FireState newState) {

  if (state != newState) {

    // Start timer when entering CRITICAL
    if (newState == CRITICAL &&
        state != CRITICAL) {

      criticalStartTime = millis();
    }

    // Reset timer when leaving CRITICAL
    if (newState != CRITICAL) {

      criticalStartTime = 0;
    }

    state = newState;

    Serial.print("STATE CHANGED TO: ");
    Serial.println((state));

    // Send WiFi alert once per state change
    sendFireAlert(state);
  }
}

// ================= FSM UPDATE =================
void updateState(float temp, int smoke) {

  bool tempFailed = (temp == INVALID_TEMP);
  bool smokeFailed = (smoke == INVALID_SMOKE);

  // ================= FAIL SAFE =================
  if (tempFailed && smokeFailed) {

    setState(FAIL_SAFE);
    return;
  }

  // ================= EMERGENCY LATCH =================
  if (state == EMERGENCY) {

    // Stay in EMERGENCY until conditions are safe
    if (temp < SAFE_TEMP &&
        smoke < SAFE_SMOKE) {

      setState(NORMAL);
    }

    return;
  }

  // ================= EMERGENCY =================
  else if (

      // Extreme fire conditions
      (temp > EXTREME_TEMP &&
       smoke > EXTREME_SMOKE)

      ||

      // Critical state lasting too long
      (state == CRITICAL &&
       temp > TEMP_THRESHOLD &&
       smoke > SMOKE_THRESHOLD &&
       millis() - criticalStartTime > CRITICAL_TIMEOUT)
  ) {

    setState(EMERGENCY);
  }

  // ================= CRITICAL =================
  else if (temp > TEMP_THRESHOLD &&
           smoke > SMOKE_THRESHOLD) {

    setState(CRITICAL);
  }

  // ================= WARNING =================
  else if (temp > TEMP_THRESHOLD ||
           smoke > SMOKE_THRESHOLD) {

    setState(WARNING);
  }

  // ================= NORMAL =================
  else {

    setState(NORMAL);
  }
}