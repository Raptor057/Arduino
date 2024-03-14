#define TRIGGER_PIN   4

#define INPUT_BIT_0_PIN   8
#define INPUT_BIT_1_PIN   9
#define INPUT_BIT_2_PIN  11

#define OUTPUT_BIT_0_PIN 12
#define OUTPUT_BIT_1_PIN 13
#define OUTPUT_BIT_2_PIN 17

void ioSetup() {
  // trigger signal
  pinMode(TRIGGER_PIN , INPUT_PULLUP);

  // configuration code
  pinMode(INPUT_BIT_0_PIN , INPUT_PULLUP);
  pinMode(INPUT_BIT_1_PIN , INPUT_PULLUP);
  pinMode(INPUT_BIT_2_PIN, INPUT_PULLUP);

  // error code
  pinMode(OUTPUT_BIT_0_PIN, OUTPUT);
  pinMode(OUTPUT_BIT_1_PIN, OUTPUT);
  pinMode(OUTPUT_BIT_2_PIN, OUTPUT);
}

bool ioTriggerIsActive() {
  return digitalRead(TRIGGER_PIN) == LOW;
  
} 


void ioResponse(uint8_t response) {
  digitalWrite(OUTPUT_BIT_0_PIN, LOW);
  digitalWrite(OUTPUT_BIT_1_PIN, LOW);
  digitalWrite(OUTPUT_BIT_2_PIN, LOW);
  if (response == 0) {
    digitalWrite(OUTPUT_BIT_0_PIN, HIGH);
  }
  else {
    digitalWrite(OUTPUT_BIT_1_PIN, HIGH);
  }
  
}

////////////////////////// STATE ///////////////////////////////////
// byte value with each bite representing the correspnding digital
// pin in little endian sequence
uint8_t ioState() {
  uint8_t data = 0;
  if (digitalRead(INPUT_BIT_0_PIN) == LOW) data |= 1;
  if (digitalRead(INPUT_BIT_1_PIN) == LOW) data |= 2;
  if (digitalRead(INPUT_BIT_2_PIN) == LOW) data |= 4;
  return data;
 
}
