// Blocking.pde
// -*- mode: C++ -*-
//
// Shows how to use the blocking call runToNewPosition
// Which sets a new target position and then waits until the stepper has 
// achieved it.
//
// Copyright (C) 2009 Mike McCauley
// $Id: Blocking.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>
#define MAX_SPEED 300
#define ACCEL 50
#define POS 500
 
// Define a stepper and the pins it will use
AccelStepper  stepper1(AccelStepper::FULL4WIRE, 2, 4, 3, 5);
AccelStepper  stepper2(AccelStepper::FULL4WIRE, 6, 8, 7, 9);
AccelStepper  stepper3(AccelStepper::FULL4WIRE, 10, 12, 11, 13);
AccelStepper  stepper4(AccelStepper::FULL4WIRE, A0, A2, A1, A3);

void setup()
{  
    stepper1.setMaxSpeed(MAX_SPEED);
    stepper1.setAcceleration(ACCEL);
    stepper2.setMaxSpeed(MAX_SPEED);
    stepper2.setAcceleration(ACCEL);
    stepper3.setMaxSpeed(MAX_SPEED);
    stepper3.setAcceleration(ACCEL);
    stepper4.setMaxSpeed(MAX_SPEED);
    stepper4.setAcceleration(ACCEL);
}

void loop() {    
    stepper1.runToNewPosition(POS);
    stepper2.runToNewPosition(POS);
    stepper3.runToNewPosition(POS);
    stepper4.runToNewPosition(POS);
}
