#pragma once

#include <Arduino.h>
#include "motorcontrol.h"
#include "variablesAndParameters.h"
#include "pins.h"

// Robot constants
float l = 17.5; // Wheelbase length (cm)
float r = 3.3;  // Wheel radius (cm)
int ratio = (75*823.1)/360; // Gear ratio

// Global Variables for PID
float KpA = 2.0;  // Proportional gain
float KiA = 0.00;  // Integral gain
float KdA = 0.0;  // Derivative gain

float p;
float i;
float d;

float errorL = 0, errorR = 0; // Error values for left and right motors
float integralL = 0, integralR = 0; // Integral terms
float previousErrorL = 0, previousErrorR = 0; // Previous errors for derivative calculation

// Function to calculate PID output
float calculatePID(float error, float *integral, float *previousError) {
  if (int(error) == 0) {
    return 0;
  }
  // Proportional term
  float proportional = KpA * error;

  // Integral term
  *integral += error;
  float integralTerm = KiA * (*integral);

  // Derivative term
  float derivative = KdA * (error - *previousError);

  // Update previous error
  *previousError = error;

  // Combine terms
  return proportional + integralTerm + derivative;
}


void encoderSetup() {

  // Encoder pins setup
  pinMode(ENCAL, INPUT);
  pinMode(ENCBL, INPUT);
  pinMode(ENCAR, INPUT);
  pinMode(ENCBR, INPUT);

  // Motor pins setup
  pinMode(PWML, OUTPUT);
  pinMode(IN1L, OUTPUT);
  pinMode(IN2L, OUTPUT);
  pinMode(PWMR, OUTPUT);
  pinMode(IN1R, OUTPUT);
  pinMode(IN2R, OUTPUT);



  // Attach interrupts for encoders
  attachInterrupt(digitalPinToInterrupt(ENCAL), readEncoderL, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCAR), readEncoderR, RISING);
}

void printConstants() {

  if (Serial.available()) {
    p = Serial.parseFloat();  // Read the first float (kP)
    d = Serial.parseFloat();  // Read the second float (kI)
    i = Serial.parseFloat();  // Read the third float (kD)

    if (p != 0) {
      KpA = p;
      KiA = i;
      KdA = d;

      Serial.println(KpA);
      Serial.println(KiA);
      Serial.println(KdA);
    }
  }
}

void turn(int ang) {
  // Calculate target counts for the given angle
  float targetCounts = (abs(ang) * l * ratio) / (720 * r);
  posL = 0;
  posR = 0;

  Serial.print("Target Counts: ");
  Serial.println(targetCounts);

  // Turn logic
  while ((abs(posL) < targetCounts) && (abs(posR) < targetCounts)) {
    // Calculate errors
    errorL = targetCounts - abs(posL);
    errorR = targetCounts - abs(posR);

    // Calculate PID outputs
    float controlL = calculatePID(errorL, &integralL, &previousErrorL);
    float controlR = calculatePID(errorR, &integralR, &previousErrorR);

    // Limit control output to valid PWM range
    controlL = constrain(controlL, 0, 255);
    controlR = constrain(controlR, 0, 255);

    // Set motor directions based on turning angle
    if (ang > 0) { // Turn right
      setMotor(1, controlL, PWML, IN1L, IN2L);
      setMotor(-1, controlR, PWMR, IN1R, IN2R);
    } else if (ang <0 ) { // Turn left
      setMotor(-1, controlL, PWML, IN1L, IN2L);
      setMotor(1, controlR, PWMR, IN1R, IN2R);
    }
  }

  // Stop motors after completing the turn
  setMotor(0, 0, PWML, IN1L, IN2L);
  setMotor(0, 0, PWMR, IN1R, IN2R);

  delay(1000); // Allow time to stabilize

  // reset the encoderCount which used to call the algorithm at each new cell
  encoder_counts = 0;

  return;
}

