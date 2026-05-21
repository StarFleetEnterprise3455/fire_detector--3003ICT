
// OUTPUT PINS (ACTUATORS)

const int GREEN_LED = 2;
const int YELLOW_LED = 4;
const int RED_LED = 5;

const int BUZZER_PIN = 18;
const int FAN_RELAY = 19;


// INITIALIZE OUTPUTS


void initOutputs() {

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(FAN_RELAY, OUTPUT);
}


// OUTPUT CONTROL FUNCTION

void updateOutputs(FireState state) {

  // Turn everything OFF first

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(FAN_RELAY, LOW);


  switch(state) {

    // NORMAL STATE

    case NORMAL:

      digitalWrite(GREEN_LED, HIGH);

      break;


    // WARNING STATE

    case WARNING:

      digitalWrite(YELLOW_LED, HIGH);

      // Turn ventilation fan ON

      digitalWrite(FAN_RELAY, HIGH);

      break;


    // CRITICAL STATE

    case CRITICAL:

      digitalWrite(RED_LED, HIGH);

      // Turn fan ON

      digitalWrite(FAN_RELAY, HIGH);

      // Activate buzzer

      digitalWrite(BUZZER_PIN, HIGH);

      break;


    // EMERGENCY STATE

    case EMERGENCY:

      digitalWrite(RED_LED, HIGH);

      // Fan stays ON

      digitalWrite(FAN_RELAY, HIGH);

      // Continuous alarm

      digitalWrite(BUZZER_PIN, HIGH);

      break;
  }
}