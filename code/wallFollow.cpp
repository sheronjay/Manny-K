#include "wallFollow.h"

// Constants for the distance controller
float KpD = 1.0;  // Proportional gain
float KiD = 0.0;  // Integral gain
float KdD = 0.0;  // Derivative gain

float previousError = 0;
float integral = 0;
int pwmValue = 0;
int motorSpeed = 150;

void wallFollowPidControl(float sensor_left, float sensor_right, float sensor_front) {
  // Calculate error: difference between left and right sensors
  float error = sensor_left - sensor_right;
  integral += error;
  float derivative = error - previousError;

  // Calculate PID output
  pwmValue = KpD * error + KiD * integral + KdD * derivative;

  // If obstacle is detected in front, stop or reverse
  if (sensor_front < 500) {  // Adjust this threshold based on your sensor range
    setMotor(0, 0, PWML, IN1L, IN2L);  // Stop the motors
    setMotor(0, 0, PWMR, IN1R, IN2R); 
  } else {
    // Apply the PID correction to motors
    setMotor(1, motorSpeed + pwmValue, PWML, IN1L, IN2L);
    setMotor(1, motorSpeed - pwmValue, PWMR, IN1R, IN2R);   
  }
  // Update previous error for the next cycle
  previousError = error;
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  pwmVal = constrain(pwmVal, 0, 255);  // Ensure pwmVal is within valid range
  analogWrite(pwm, pwmVal);
  if (dir == 1) {
    // Forward movement
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (dir == -1) {
    // Reverse movement
    digitalWrite(in2, HIGH);
    digitalWrite(in1, LOW);
  } else {
    // Stop motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
  delay(10);
}
