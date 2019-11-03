#define A_PIN 2
#define CLOCK_PIN 10
#define LATCH_PIN 11
#define DATA_PIN 12

void setup() {
  for (int i=0; i<8; i++){
    pinMode(A_PIN+i, INPUT);
  }
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  Serial.begin(9600);
}

void check(int data) {
  digitalWrite(LATCH_PIN, LOW);
  digitalWrite(CLOCK_PIN, LOW);

  Serial.println("Writing data ");
  for (int i=0; i<8; i++){
    Serial.print((data >> i) & 1);
    digitalWrite(DATA_PIN, (data >> i) & 1);
    digitalWrite(CLOCK_PIN, HIGH);
    delay(10);
    digitalWrite(CLOCK_PIN, LOW);
    delay(10);
  }
  Serial.println("");

  // RELEASE
  digitalWrite(LATCH_PIN, HIGH);

  delay(1000);

  Serial.println("Reading data");
  for (int i=0; i<8; i++){
    int b = digitalRead(A_PIN+i);
    Serial.println(b);
  }
  delay(3000);
}

void loop() {
  check(B01010101);
  check(B11111111);
  check(B10101010);
}
