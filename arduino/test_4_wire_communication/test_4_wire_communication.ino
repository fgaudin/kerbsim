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

#define A_PIN 2

#define LOAD_PIN A0
#define CLOCK_PIN A1
#define LATCH A2
#define DATA A3
#define DEBUG_PIN A4
#define DEBUG_DELAY 100

void setup()
{
    for (int i=0; i<8; i++){
      pinMode(A_PIN+i, OUTPUT);
    }
    pinMode(DATA, INPUT);
    pinMode(LATCH, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(LOAD_PIN, OUTPUT);
    pinMode(DEBUG_PIN, OUTPUT);

    Serial.begin(57600);
    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(LOAD_PIN, HIGH);
    digitalWrite(LATCH, LOW);
}

void latch() {
  digitalWrite(DEBUG_PIN, HIGH);
  digitalWrite(LATCH, LOW);
  delay(DEBUG_DELAY);
  digitalWrite(LATCH, HIGH);
  digitalWrite(DEBUG_PIN, LOW);
  delay(DEBUG_DELAY);
}

void transfer(int data){
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

  for(int i=0; i < 8; i++) {
    digitalWrite(CLOCK_PIN, HIGH);
    delay(DEBUG_DELAY);
    digitalWrite(CLOCK_PIN, LOW);
    delay(DEBUG_DELAY);
  }

  latch();
}

void loop()
{
    transfer(B10101010);
    transfer(B01010101);
}
