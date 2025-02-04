#include "turning.h"
#include <Arduino.h>
#include "motorcontrol.h"
#include "variablesAndParameters.h"
#include "pins.h"
#include "MPU6050.h"

void turn(int ang)
{
  int dir = 1;

  applyBreak();
  if (ang < 0)
  { // Turn left
    dir = -1;
  }

  setMotor(dir, motorSpeed * 0.65, PWML, IN1L, IN2L);
  setMotor(-dir, motorSpeed * 0.65, PWMR, IN1R, IN2R);

  while (abs(currentAngle) < abs(ang))
  { // Ensure we check absolute angles
    updateTurnedAngle();
    delay(10);
  }

  //Stop the motors once the target angle is reached
  setMotor(-dir, 180, PWML, IN1L, IN2L);
  setMotor(dir, 180, PWMR, IN1R, IN2R);
  delay(15);
  setMotor(0, 0, PWML, IN1L, IN2L);
  setMotor(0, 0, PWMR, IN1R, IN2R);

  // Reset the currentAngle to prevent drift between turns
  currentAngle = 0;
}