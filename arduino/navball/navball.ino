#include <AccelStepper.h>
#include <math.h>

#define HALFSTEP 4
#define PIN_OVERFLOW 3
#define PIN_PROCESS 2
#define PIN_HEADING_1 8
#define PIN_HEADING_2 10
#define PIN_HEADING_3 9
#define PIN_HEADING_4 11

const int internalStepsPerRev = 32;
const float internalGearRatio = 64;
const float externalGearRatio = 1.0;
const float stepsPerRevolution = internalStepsPerRev * internalGearRatio * externalGearRatio;
const int accelRatio = 8;

AccelStepper  headingStepper(AccelStepper::FULL4WIRE, PIN_HEADING_1, PIN_HEADING_2, PIN_HEADING_3, PIN_HEADING_4);

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
  headingStepper.setMaxSpeed(stepsPerRevolution*2);
  headingStepper.setAcceleration(stepsPerRevolution/accelRatio);
  Serial.begin(115200);

}

void rateOk() {
  digitalWrite(PIN_OVERFLOW, LOW);
}

void rateKo() {
  digitalWrite(PIN_OVERFLOW, HIGH);
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

void loop() {
  receiveData();
  parseData();
  headingStepper.run();
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

    // we can let another packet come in
    packetReceived = false;

    process();
    rateOk();
  }
}

void process() {
  moveHeading();
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

void moveHeading() {
  float delta;
  int stepsToMove;

  int deltaSteps;
  float deltaQuantified;
  unsigned long currentTime;
  float secSinceLastMove;
  int speedNeeded = 0;
  int currentPosition, desiredPosition;

  if (headingRequested != heading) {
    currentTime = millis();
    delta = smallestAngle(heading, headingRequested, 360);
    deltaSteps = angleToSteps(delta);
    if (lastTime) {
      secSinceLastMove = (currentTime - lastTime) / 1000.0;
      speedNeeded = abs(round(deltaSteps / secSinceLastMove));
    }
    lastTime = currentTime;
    heading = headingRequested;
    
    currentPosition = fmod(fmod(headingStepper.currentPosition(), stepsPerRevolution) + stepsPerRevolution, stepsPerRevolution);
    desiredPosition = angleToSteps(headingRequested);
    stepsToMove = smallestAngle(currentPosition, desiredPosition, stepsPerRevolution);
    if (speedNeeded) {
      if (speedNeeded > 200) {
        digitalWrite(PIN_PROCESS, HIGH);
        headingStepper.move(stepsToMove*accelRatio);  // predicting where it's going
      } else {
        digitalWrite(PIN_PROCESS, LOW);
        headingStepper.move(stepsToMove);
      }
    }
  }
}
