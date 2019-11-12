// MultiStepper.pde
// -*- mode: C++ -*-
//
// Shows how to multiple simultaneous steppers
// Runs one stepper forwards and backwards, accelerating and decelerating
// at the limits. Runs other steppers at the same time
//
// Copyright (C) 2009 Mike McCauley
// $Id: MultiStepper.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

#define LOAD_PIN A0
#define CLOCK_PIN A1
#define LATCH A2
#define DATA A3
#define DEBUG_PIN A4

#define DEBUG_DELAY 100

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::FULL4WIRE, 2, 4, 3, 5);
AccelStepper stepper2(AccelStepper::FULL4WIRE, 6, 8, 7, 9);

void setup()
{  
    pinMode(DATA, INPUT);
    pinMode(LATCH, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(LOAD_PIN, OUTPUT);

    stepper1.setMaxSpeed(800.0);
    stepper1.setAcceleration(800.0);
    stepper1.moveTo(100);
    
    stepper2.setMaxSpeed(800.0);
    stepper2.setAcceleration(300.0);
    stepper2.moveTo(1000000);

    Serial.begin(57600);

    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(LOAD_PIN, HIGH);
    digitalWrite(LATCH, LOW);
}

void latch() {
  digitalWrite(DEBUG_PIN, HIGH);
  digitalWrite(LATCH, LOW);
  digitalWrite(LATCH, HIGH);
  digitalWrite(DEBUG_PIN, LOW);
}

void transfer(){
  digitalWrite(LOAD_PIN, LOW);
  digitalWrite(LOAD_PIN, HIGH);
  
  for(int i=0; i < 8; i++) {
    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(CLOCK_PIN, HIGH);
  }

  latch();
}

void loop()
{
    // Change direction at the limits
    if (stepper1.distanceToGo() == 0) {
	    stepper1.moveTo(-stepper1.currentPosition());
    }
    stepper1.run();
    stepper2.run();
    transfer();
}
