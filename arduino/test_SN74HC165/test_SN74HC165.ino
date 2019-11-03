
#define CLOCK_PIN 2
#define LATCH_PIN 3
#define A_PIN 4
#define B_PIN 5
#define C_PIN 6
#define D_PIN 7
#define E_PIN 8
#define F_PIN 9
#define G_PIN 10
#define H_PIN 11

void setup() {
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(A_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  pinMode(C_PIN, OUTPUT);
  pinMode(D_PIN, OUTPUT);
  pinMode(E_PIN, OUTPUT);
  pinMode(F_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(H_PIN, OUTPUT);
}

void check(int data) {
  digitalWrite(LATCH_PIN, LOW);
  digitalWrite(CLOCK_PIN, LOW);

  for (int i=0; i<8; i++){
    digitalWrite(A_PIN+i, data & (1 << i));
  }

  // LOAD
  digitalWrite(LATCH_PIN, LOW);
  delay(10);
  digitalWrite(LATCH_PIN, HIGH);

  for(int i=0; i < 8; i++) {
    digitalWrite(CLOCK_PIN, HIGH);
    delay(500);
    digitalWrite(CLOCK_PIN, LOW);
    delay(10);
  }
}

void loop() {
  check(B01010101);
  check(B11111111);
  check(B10101010);
}
