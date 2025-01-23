#include "wallFollow.h"
#include "motorcontrol.h"
#include "variablesAndParameters.h"
#include <Arduino.h>
#include "pins.h"

// Constants for the distance controller
float previousError = 0;
float previousLeftError = 0;
float previousRightError = 0;
int pwmValue = 0;

void wallFollowPidControl(float sensor_left, float sensor_right)
{
  float error = sensor_left - sensor_right;
  float derivative = error - previousError;

  // Calculate PID output
  pwmValue = KpD * error + KdD * derivative;
  Serial.println(pwmValue);

  // Apply the PID correction to motors
  setMotor(1, motorSpeed - pwmValue, PWML, IN1L, IN2L);
  setMotor(1, motorSpeed + pwmValue, PWMR, IN1R, IN2R);

  // Update previous error for the next cycle
  previousError = error;
}

void leftWallFollowPidControl(float sensor_left) {
  float error = dist_to_single_wall - sensor_left;
  float derivative = error - previousLeftError;

  // Calculate PID output
  pwmValue = KpD * error + KdD * derivative;
  Serial.println(pwmValue);

  // Apply the PID correction to motors
  setMotor(1, motorSpeed - pwmValue, PWML, IN1L, IN2L);
  setMotor(1, motorSpeed + pwmValue, PWMR, IN1R, IN2R);

  // Update previous error for the next cycle
  previousLeftError = error;
}
void rightWallFollowPidControl(float sensor_right) {
  float error = dist_to_single_wall - sensor_right;
  float derivative = error - previousRightError;

  // Calculate PID output
  pwmValue = KpD * error + KdD * derivative;
  Serial.println(pwmValue);

  // Apply the PID correction to motors
  setMotor(1, motorSpeed - pwmValue, PWML, IN1L, IN2L);
  setMotor(1, motorSpeed + pwmValue, PWMR, IN1R, IN2R);

  // Update previous error for the next cycle
  previousRightError = error;
}
