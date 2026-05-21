#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "wifi.h"

void initWiFi() {

  Serial.print("Connecting to WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());
}

void sendFireAlert(FireState state) {

  Serial.print("WIFI ALERT -> ");

  switch(state) {

    case NORMAL:
      Serial.println("SYSTEM NORMAL");
      break;

    case WARNING:
      Serial.println("WARNING DETECTED");
      break;

    case CRITICAL:
      Serial.println("CRITICAL FIRE DETECTED");
      break;

    case EMERGENCY:
      Serial.println("EMERGENCY FIRE DETECTED");
      break;

    case FAIL_SAFE:
      Serial.println("FAIL SAFE ACTIVATED");
      break;
  }
}