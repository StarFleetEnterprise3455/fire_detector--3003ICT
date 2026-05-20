#include <Arduino.h>
#include <WiFi.h>

#include "wifi.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";

void initWiFi() {

    Serial.println("Connecting WiFi...");

    WiFi.begin(ssid, password);

    int timeout = 20;

    while (WiFi.status() != WL_CONNECTED && timeout > 0) {
        delay(500);
        Serial.print(".");
        timeout--;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected");
    } else {
        Serial.println("\nWiFi offline mode");
    }
}

void sendFireAlert(FireState state) {

    switch(state) {

        case NORMAL:
            Serial.println("WiFi: System normal");
            break;

        case WARNING:
            Serial.println("WiFi: Warning detected");
            break;

        case CRITICAL:
            Serial.println("🚨 WiFi: CRITICAL ALERT SENT");
            break;

        case EMERGENCY:
            Serial.println("🚨🚨 WiFi: EMERGENCY ALERT SENT");
            break;
    }
}