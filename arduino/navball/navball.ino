
/*
  Stepper Motor Control - one revolution

  This program drives a unipolar or bipolar stepper motor.
  The motor is attached to digital pins 8 - 11 of the Arduino.

  The motor should revolve one revolution in one direction, then
  one revolution in the other direction.


  Created 11 Mar. 2007
  Modified 30 Nov. 2009
  by Tom Igoe

*/

#include <Stepper.h>
#include <math.h>

const char sep = '|';
const int internalStepsPerRev = 32;
//const float internalGearRatio = 25792.0/405;
const float internalGearRatio = 64;
const float externalGearRatio = 1.0;
// const float externalGearRatio = 1.0 / 4;
const float stepsPerRevolution = internalStepsPerRev * internalGearRatio * externalGearRatio;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(internalStepsPerRev * internalGearRatio, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(15);
  // initialize the serial port:
  Serial.begin(9600);
  Serial.println(internalStepsPerRev);
  Serial.println(internalGearRatio);
  Serial.println(externalGearRatio);
  Serial.println(stepsPerRevolution, 6);
}

void loop() {

  char msg[17] = "";
  char pitchStr[7] = "";
  char rpmStr[6] = "";
  int byte_read = 0;
  float pitchCurrent = 0, pitchRequested, pitchDelta, pitchDeltaForward, pitchDeltaBackward, pitchDeltaAdjusted;
  int stepsCurrent = 0, stepsAdjusted;
  const int lf = 10;
  float rpm;
  

  while (1) {
    memset(msg, 0, sizeof(msg));
    memset(pitchStr, 0, sizeof(pitchStr));
    memset(rpmStr, 0, sizeof(rpmStr));
    int sepIndex = -1;

    if (Serial.available() > 0) {
      // read the incoming byte:
      byte_read = Serial.readBytesUntil(lf, msg, 17);
      for(int i = 0; i < byte_read; i++) {
        if (msg[i] == sep) {
          sepIndex = i;
        } else if (sepIndex > -1) {
          rpmStr[i-sepIndex-1] = msg[i];
        } else {
          pitchStr[i] = msg[i];
        }
      }
      pitchRequested = atof(pitchStr);
      rpm = atof(rpmStr);

      Serial.print("received msg: ");
      Serial.println(msg);
      Serial.print("received angle: ");
      Serial.println(pitchStr);
      Serial.print("received rpm: ");
      Serial.println(rpmStr);
      myStepper.setSpeed(max(round(rpm), 1));

      pitchDeltaForward = fmod(pitchRequested - pitchCurrent + 360, 360);
      pitchDeltaBackward = pitchDeltaForward - 360;
      if (abs(pitchDeltaForward) < abs(pitchDeltaBackward)) {
        pitchDelta = pitchDeltaForward;
      } else {
        pitchDelta = pitchDeltaBackward;
      }
      // Serial.print("pitchRequested: ");
      // Serial.println(pitchRequested, 2);
      // Serial.print("pitchDelta: ");
      // Serial.println(pitchDelta, 2);

      stepsAdjusted = round(pitchDelta * stepsPerRevolution / 360);
      // Serial.print("stepsAdjusted: ");
      // Serial.println(stepsAdjusted);
      stepsCurrent += stepsAdjusted;
      // Serial.print("stepsCurrent: ");
      // Serial.println(stepsCurrent);
      pitchDeltaAdjusted = stepsAdjusted * 360.0 / stepsPerRevolution;
      pitchCurrent = fmod(pitchCurrent + pitchDeltaAdjusted + 360, 360);
      // Serial.print("pitchDeltaAdjusted: ");
      // Serial.println(pitchDeltaAdjusted, 6);

      // Serial.print("pitchCurrent: ");
      // Serial.println(pitchCurrent, 6);

      myStepper.step(stepsAdjusted);
    }
  }
}
