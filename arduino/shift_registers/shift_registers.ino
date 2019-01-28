#define MOTOR1_1 2
#define MOTOR1_2 3
#define MOTOR1_3 4
#define MOTOR1_4 5
#define MOTOR2_1 6
#define MOTOR2_2 7
#define MOTOR2_3 8
#define MOTOR2_4 9

#define LATCH 11
#define LOAD 12
#define CLOCK 13

int value = 0;

void setup() {
  pinMode(MOTOR1_1, OUTPUT);
  pinMode(MOTOR1_2, OUTPUT);
  pinMode(MOTOR1_3, OUTPUT);
  pinMode(MOTOR1_4, OUTPUT);
  pinMode(MOTOR2_1, OUTPUT);
  pinMode(MOTOR2_2, OUTPUT);
  pinMode(MOTOR2_3, OUTPUT);
  pinMode(MOTOR2_4, OUTPUT);

  pinMode(LATCH, OUTPUT);
  pinMode(LOAD, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("start loop");
  Serial.println(value);

  int reg = value;
  for (int i=0; i<8; i++){
    digitalWrite(i + 2, reg & 1);
    reg = reg >> 1;
  }
  digitalWrite(LOAD, LOW);
  digitalWrite(LOAD, HIGH);
  
  for (int i=0; i<8; i++){
    digitalWrite(CLOCK, LOW);
    digitalWrite(CLOCK, HIGH);
  }

  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
  delay(100);
  value++;
}
