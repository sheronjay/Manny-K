#include "turning.h"
#include <Arduino.h>
#include "motorcontrol.h"
#include "variablesAndParameters.h"
#include "pins.h"
#include "MPU6050.h"
#include "wifiUpdate.h"

void turn(int ang)
{
  int dir = 1;

  applyBreak();
  posL = 0;
  posR = 0;

  if (ang < 0)
  { // Turn left
    dir = -1;
  }

  setMotor(dir, motorSpeed * 1.1, PWML, IN1L, IN2L);
  setMotor(-dir, motorSpeed * 1.1, PWMR, IN1R, IN2R);

  while (abs(currentAngle) < abs(ang))
  { // Ensure we check absolute angles
    updateTurnedAngle();
    delay(10);
  }

  // while (abs(posR) < 160)
  // {
  //   delay(5);
  //   printSerialAndSend(String(posL) + "," + String(posR));
  // }
  

  // Stop the motors once the target angle is reached
  setMotor(-dir, 180, PWML, IN1L, IN2L);
  setMotor(dir, 180, PWMR, IN1R, IN2R);
  delay(15);
  setMotor(0, 0, PWML, IN1L, IN2L);
  setMotor(0, 0, PWMR, IN1R, IN2R);

  // Reset the currentAngle to prevent drift between turns
  currentAngle = 0;
}