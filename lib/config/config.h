#pragma once

// ================= PINS =================
#define DHTPIN 15
#define DHTTYPE DHT22
#define MQ2_PIN 34

#define LED_GREEN 18
#define LED_YELLOW 19
#define LED_RED 21

#define BUZZER_PIN 4
#define SPRINKLER_PIN 22

// ================= SENSOR FAILURE =================
#define INVALID_TEMP -999
#define INVALID_SMOKE -999

// ================= MODES =================
#define SIM_MODE true

// ================= WIFI =================
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// ================= THRESHOLDS =================
const float TEMP_THRESHOLD = 50.0;
const float SAFE_TEMP = 40.0;
const float EXTREME_TEMP = 80.0;

const int SMOKE_THRESHOLD = 55;
const int SAFE_SMOKE = 25;
const int EXTREME_SMOKE = 80;

const float ALPHA = 0.2;