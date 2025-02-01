#include "turning.h"
#include <Arduino.h>
#include "motorcontrol.h"
#include "variablesAndParameters.h"
#include "pins.h"
#include "MPU6050.h"

void turn(int ang)
{
  applyBreak();
  if (ang > 0)
  { // Turn right
    setMotor(1, motorSpeed, PWML, IN1L, IN2L);
    setMotor(-1, motorSpeed, PWMR, IN1R, IN2R);
  }
  else if (ang < 0)
  { // Turn left
    setMotor(-1, motorSpeed, PWML, IN1L, IN2L);
    setMotor(1, motorSpeed, PWMR, IN1R, IN2R);
  }

  while (abs(currentAngle) < abs(ang))
  { // Ensure we check absolute angles
    updateTurnedAngle();
    delay(10);
  }

  if (ang < 0)
  { // stop right
    setMotor(1, motorSpeed, PWML, IN1L, IN2L);
    setMotor(-1, motorSpeed, PWMR, IN1R, IN2R);
  }
  else if (ang > 0)
  { // stop left
    setMotor(-1, motorSpeed, PWML, IN1L, IN2L);
    setMotor(1, motorSpeed, PWMR, IN1R, IN2R);
  }

  delay(10);

  // Stop the motors once the target angle is reached
  setMotor(0, 0, PWML, IN1L, IN2L);
  setMotor(0, 0, PWMR, IN1R, IN2R);

  // Reset the currentAngle to prevent drift between turns
  currentAngle = 0;
}