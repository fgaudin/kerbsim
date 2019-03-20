#include <AccelStepper.h>
#include <math.h>

#define PIN_HEADING_1 2
#define PIN_HEADING_2 3
#define PIN_HEADING_3 4
#define PIN_HEADING_4 5
#define PIN_PITCH_1 6
#define PIN_PITCH_2 7
#define PIN_PITCH_3 8
#define PIN_PITCH_4 9

#define DATA 10
#define LATCH 11
#define LOAD 12
#define CLOCK 13

const int internalStepsPerRev = 64;  // 32 for fullstep, 64 for halfstep
const float internalGearRatio = 64;
const float externalGearRatio = 1.0;
const float stepsPerRevolution = internalStepsPerRev * internalGearRatio * externalGearRatio;
const int accelRatio = 4;

AccelStepper  headingStepper(AccelStepper::HALF4WIRE, PIN_HEADING_1, PIN_HEADING_3, PIN_HEADING_2, PIN_HEADING_4);
//AccelStepper  headingStepper(AccelStepper::FULL2WIRE, PIN_HEADING_1, PIN_HEADING_2);
AccelStepper  pitchStepper(AccelStepper::HALF4WIRE, PIN_PITCH_1, PIN_PITCH_3, PIN_PITCH_2, PIN_PITCH_4);
//AccelStepper  pitchStepper(AccelStepper::FULL2WIRE, PIN_PITCH_1, PIN_PITCH_2);

const byte numChars = 32;
char receivedChars[numChars];
const char startMarker = '[';
const char endMarker = ']';
boolean packetReceived = false;

float pitch = 0, heading = 0, roll = 0;
float pitchRequested = 0, headingRequested = 0, rollRequested = 0;

int testDelay = 0;

unsigned long lastTimeHeading = 0, lastTimePitch = 0, lastTimeRoll = 0;

unsigned long lastHeadingCalibration = 0, lastPitchCalibration = 0, lastRollCalibration = 0;

int data = 0;

void setup() {
  pinMode(DATA, INPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(LOAD, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  //pinMode(PIN_OVERFLOW, OUTPUT);
  pinMode(A0, OUTPUT);
  dataTest();
  headingStepper.setMaxSpeed(stepsPerRevolution/2);
  headingStepper.setAcceleration(stepsPerRevolution/accelRatio);
  pitchStepper.setMaxSpeed(stepsPerRevolution/2);
  pitchStepper.setAcceleration(stepsPerRevolution/accelRatio);
  Serial.begin(115200);
}

void rateOk() {
  //digitalWrite(PIN_OVERFLOW, LOW);
}

void rateKo() {
  //digitalWrite(PIN_OVERFLOW, HIGH);
}

void dataTest() {
  rateOk();
  for (int i = 0; i < 3; i++) {
    rateKo();
    delay(200);
    rateOk();
    delay(200);
  }
}

void loadRegister() {
  digitalWrite(LOAD, LOW);
  digitalWrite(LOAD, HIGH);
}

void transferAndLatch() {
  int dataBit = B0;
  data = B00000000;
  for (int i=0; i<8; i++){
    dataBit = digitalRead(DATA);
    data = data | (dataBit << (7 - i));
    digitalWrite(CLOCK, LOW);
    digitalWrite(CLOCK, HIGH);
  }
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
}

void calibrate() {
  unsigned long currentTime = millis();

  if ((! (data & B1)) && (currentTime - lastHeadingCalibration) > 200) {
    heading = 0;
    headingStepper.setCurrentPosition(0);
    digitalWrite(A0, HIGH);
    lastHeadingCalibration = currentTime;
  }
  if ((!(data & B10)) && (currentTime - lastPitchCalibration) > 200) {
    pitch = 0;
    pitchStepper.setCurrentPosition(0);
    digitalWrite(A0, HIGH);
    lastPitchCalibration = currentTime;
  }
  if ((currentTime - lastHeadingCalibration) > 1000 && (currentTime - lastPitchCalibration) > 1000) {
    digitalWrite(A0, LOW);
  }
}

void testData(){
  float step = 0.05;
  packetReceived = true;
  headingRequested = fmod(heading + step, 360);
  pitchRequested = fmod(pitch + step, 360);
  rollRequested = fmod(roll + step, 360);
}

void loop() {
  //receiveData();
  //parseData();
  testData();
  process();
  headingStepper.run();
  pitchStepper.run();
  loadRegister();
  transferAndLatch();
  calibrate();
}

void receiveData() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char rc;

  while (Serial.available() > 0) {
    if (packetReceived) {
      // first packet hasn't be handled yet
      // and we're already receiving another one
      // discarding the previous one
      rateKo();
      packetReceived = false;
    }
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      } else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        packetReceived = true;
      }
    } else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void parseData() {
  if (packetReceived) {
    char tempChars[numChars];
    char * strtokIndx; // this is used by strtok() as an index

    strcpy(tempChars, receivedChars);

    strtokIndx = strtok(tempChars, "|");     // get the first part - the string
    headingRequested = atof(strtokIndx);

    strtokIndx = strtok(NULL, "|"); // this continues where the previous call left off
    pitchRequested = atof(strtokIndx);

    strtokIndx = strtok(NULL, "|");
    rollRequested = atof(strtokIndx);
  }
}

void process() {
  if (packetReceived) {
    // we can let another packet come in
    packetReceived = false;
    rateOk();
    moveMotor(&headingStepper, headingRequested, &heading, &lastTimeHeading);
    moveMotor(&pitchStepper, pitchRequested, &pitch, &lastTimePitch);
  }
}

float smallestAngle(float origin, float target, int revolution) {
  float delta;
  delta = target - origin;
  if (delta > revolution / 2) {
    delta -= revolution ;
  } else if (delta < -revolution / 2) {
    delta += revolution;
  }
  return delta;
}

int angleToSteps(float angle) {
  return round(angle * stepsPerRevolution / 360);
}

float stepsToAngle(int steps) {
  return steps * 360.0 / stepsPerRevolution;
}

float rpm(float angle, float duration_sec) {
  return abs((angle * 60 / duration_sec) / 360);
}

void moveMotor(AccelStepper* stepper, float requested, float * current, unsigned long *lastTime) {
  float delta;
  int stepsToMove;

  int deltaSteps;
  float deltaQuantified;
  unsigned long currentTime;
  float secSinceLastMove;
  int speedNeeded = 0;
  int currentPosition, desiredPosition;

  if (requested != *current) {
    currentTime = millis();
    delta = smallestAngle(*current, requested, 360);
    deltaSteps = angleToSteps(delta);
    if (*lastTime) {
      secSinceLastMove = (currentTime - *lastTime) / 1000.0;
      speedNeeded = abs(round(deltaSteps / secSinceLastMove));
    }
    *lastTime = currentTime;
    *current = requested;
    
    currentPosition = fmod(fmod(stepper->currentPosition(), stepsPerRevolution) + stepsPerRevolution, stepsPerRevolution);
    desiredPosition = angleToSteps(requested);
    stepsToMove = smallestAngle(currentPosition, desiredPosition, stepsPerRevolution);
    if (speedNeeded and speedNeeded > 8*internalStepsPerRev) {
      stepper->move(stepsToMove*accelRatio);  // predicting where it's going
    } else {
      stepper->move(stepsToMove);
    }
  }
}
