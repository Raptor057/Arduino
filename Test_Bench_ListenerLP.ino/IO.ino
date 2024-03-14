#define TRIGGER_PIN_1   4
#define TRIGGER_PIN_2   8


#define OUTPUT_BIT_0_PIN 12
#define OUTPUT_BIT_1_PIN 13
#define OUTPUT_BIT_2_PIN 17

void ioSetup() {
  // trigger signal
  pinMode(TRIGGER_PIN_1 , INPUT_PULLUP);
  pinMode(TRIGGER_PIN_2 , INPUT_PULLUP);

  // configuration code

  // error code
  pinMode(OUTPUT_BIT_0_PIN, OUTPUT);
  pinMode(OUTPUT_BIT_1_PIN, OUTPUT);
  pinMode(OUTPUT_BIT_2_PIN, OUTPUT);
}

bool ioTriggerIsActive1() {
  return digitalRead(TRIGGER_PIN_1) == LOW;
  
} 
bool ioTriggerIsActive2() {
  return digitalRead(TRIGGER_PIN_2) == LOW;
  
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
