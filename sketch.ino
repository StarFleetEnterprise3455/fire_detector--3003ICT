#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22

#define MQ2_PIN 34
#define LED_PIN 2
#define BUZZER_PIN 4

const float SAFE_TEMP = 50.0;
const int SMOKE_THRESHOLD = 2000;

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("Fire Detection System Started");
}

void loop() {

  float temperature = dht.readTemperature();

  int smokeLevel = analogRead(MQ2_PIN);

  bool fireDetected = false;

  Serial.println("Temperature: ");
  Serial.println(temperature);
  Serial.println("C");

  Serial.print("Smoke Level: ");
  Serial.println(smokeLevel);

  if (temperature > SAFE_TEMP) {
    fireDetected = true;
  }

  if (smokeLevel > SMOKE_THRESHOLD) {
    fireDetected = true;
  }

  if (fireDetected) {
    digitalWrite(LED_PIN, HIGH);

    tone(BUZZER_PIN, 1000);

    Serial.println("!!! FIRE ALARM ACTIVATED !!!");
  } else {
    digitalWrite(LED_PIN, LOW);

    noTone(BUZZER_PIN);

    Serial.println("System Safe");

    

    
  } 

  Serial.println("---------------");

  delay(1000);
                          
}
