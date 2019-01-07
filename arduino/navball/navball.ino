#include <Stepper.h>
#include <math.h>

#define PIN_OVERFLOW 3
#define PIN_PROCESS 2

const float maxRpm = 15;
const int internalStepsPerRev = 32;
//const float internalGearRatio = 25792.0/405;
const float internalGearRatio = 64;
const float externalGearRatio = 1.0;
// const float externalGearRatio = 1.0 / 4;
const float stepsPerRevolution = internalStepsPerRev * internalGearRatio * externalGearRatio;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(internalStepsPerRev * internalGearRatio, 8, 10, 9, 11);

const byte numChars = 32;
char receivedChars[numChars];
const char startMarker = '[';
const char endMarker = ']';
boolean packetReceived = false;

float pitch = 0, heading = 0, roll = 0;
float pitchRequested = 0, headingRequested = 0, rollRequested = 0;

unsigned long lastTime;

void setup() {
  pinMode(PIN_OVERFLOW, OUTPUT);
  pinMode(PIN_PROCESS, OUTPUT);
  dataTest();
  myStepper.setSpeed(15);
  Serial.begin(9600);
    
}

void rateOk() {
  digitalWrite(PIN_OVERFLOW, LOW);
}

void rateKo() {
  digitalWrite(PIN_OVERFLOW, HIGH);
}

void dataTest() {
  rateOk();
  for(int i = 0; i<3; i++) {
    rateKo();
    delay(200);
    rateOk();
    delay(200);
  }
}

void loop() {
  receiveData();
  parseData();
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

    strtokIndx = strtok(tempChars,"|");      // get the first part - the string
    headingRequested = atof(strtokIndx);
 
    strtokIndx = strtok(NULL, "|"); // this continues where the previous call left off
    pitchRequested = atof(strtokIndx);

    strtokIndx = strtok(NULL, "|");
    rollRequested = atof(strtokIndx);

    // we can let another packet come in
    packetReceived = false;

    process();
    rateOk();
  }
}

void process() {
  digitalWrite(PIN_PROCESS, HIGH);
  moveHeading();
  digitalWrite(PIN_PROCESS, LOW);
}

float smallestAngle(float origin, float target) {
  float delta;
  delta = target - origin;
  if (delta > 180) {
    delta -= 360 ;
  } else if (delta < -180) {
    delta += 360;
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

void moveHeading() {
  float delta;
  int stepsToMove;
  float deltaQuantified;
  unsigned long currentTime;
  float secSinceLastMove;
  int rpmNeeded;

  if (headingRequested != heading) {
    currentTime = millis();
    secSinceLastMove = (currentTime - lastTime) / 1000;
    lastTime = currentTime;

    delta = smallestAngle(heading, headingRequested);
    stepsToMove = angleToSteps(delta);
    deltaQuantified = stepsToAngle(stepsToMove);
    heading = fmod(heading + deltaQuantified + 360, 360);
    rpmNeeded = rpm(deltaQuantified, secSinceLastMove);
    rpmNeeded = 15;
    if (rpmNeeded > maxRpm) {
      rateKo();
    } else {
      rateOk();
    }
    rpmNeeded = constrain(1, rpmNeeded, maxRpm);
    myStepper.setSpeed(rpmNeeded);
    myStepper.step(stepsToMove);
  }
}
