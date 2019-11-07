

#define A_PIN 2

#define LOAD_PIN A0
#define CLOCK_PIN A1

void setup() {
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LOAD_PIN, OUTPUT);
  for (int i=0; i<8; i++){
    pinMode(A_PIN+i, OUTPUT);
  }
  Serial.begin(57600);

  digitalWrite(CLOCK_PIN, LOW);
  digitalWrite(LOAD_PIN, HIGH);
}

void check(int data) {
  Serial.println("Setting pins:");
  for (int i=0; i<8; i++){
    int val = (data >> i) & 1;
    Serial.print(val);
    digitalWrite(A_PIN+i, val);
  }
  Serial.println("");

  // LOAD
  delay(1);
  digitalWrite(LOAD_PIN, LOW);
  delay(1);
  digitalWrite(LOAD_PIN, HIGH);

  Serial.println("Starting clocking");
  
  for(int i=0; i < 8; i++) {
    Serial.print("LED  ");
    Serial.println((data >> (7 - i)) & 1);
    Serial.flush();
    delay(2000);
    digitalWrite(CLOCK_PIN, LOW);
    delay(1);
    digitalWrite(CLOCK_PIN, HIGH);
  }

  delay(2000);
}

void loop() {
  check(B10100000);
  check(B00000101);
}
