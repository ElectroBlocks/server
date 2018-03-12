
/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe
 
 Port to Seeed Motor Shield
 by Loovee 14 Mar. 2016

 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8,11,12,13);

void step(int steps)
{
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    myStepper.step(steps);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
}

void setup() {
    // set the speed at 60 rpm:
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);

    myStepper.setSpeed(60);
    // initialize the serial port:
    Serial.begin(9600);
}

void loop() {
    // step one revolution  in one direction:
    Serial.println("clockwise");
    setp(stepsPerRevolution);
    delay(500);

    // step one revolution in the other direction:
    Serial.println("counterclockwise");
    step(-stepsPerRevolution);
    delay(500);
}

