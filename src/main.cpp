#include <Arduino.h>

void setup() {
    Serial.begin(115200);
}

void loop() {

    // fake sensor data
    float temp = 70;
    int smoke = 2500;

    Serial.println(temp);
    Serial.println(smoke);

    delay(1000);
}