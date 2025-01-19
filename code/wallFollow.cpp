#include "wallFollow.h"
#include "motorcontrol.h"
#include "variablesAndParameters.h"
#include <Arduino.h>

// Constants for the distance controller
float previousError = 0;
float integral = 0;
int pwmValue = 0;
int motorSpeed = 80;

void wallFollowPidControl(float sensor_left, float sensor_right, float sensor_front)
{
  // Calculate error: difference between left and right sensors
  float error;

  // both walls missing
  if (sensor_left > (side_threshold + side_threshold_error) && sensor_right > (side_threshold + side_threshold_error))
  {
    error = 0;
  }

  // follow right wall
  else if (sensor_left > (side_threshold + side_threshold_error))
  {
    error = (maze_width - car_width - 2 * sensor_right) * K_singlewall_correction;
    // error = 0;
  }

  // follow left wall
  else if (sensor_right > (side_threshold + side_threshold_error))
  {
    error = (-maze_width + car_width + 2 * sensor_left) * K_singlewall_correction;
    // error = 0;
  }

  else
  {

    error = sensor_left - sensor_right;
  }

  integral += error;
  float derivative = error - previousError;

  // Calculate PID output
  pwmValue = KpD * error + KiD * integral + KdD * derivative;
  Serial.println(pwmValue);

  // Apply the PID correction to motors
  setMotor(1, motorSpeed - pwmValue, PWML, IN1L, IN2L);
  setMotor(1, motorSpeed + pwmValue, PWMR, IN1R, IN2R);

  // Update previous error for the next cycle
  previousError = error;
}
