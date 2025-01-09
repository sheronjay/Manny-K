#include "wallFollow.h"

// Constants for the distance controller
float KpD = 0.5;  // Proportional gain
float KiD = 0.0;  // Integral gain
float KdD = 0.1;  // Derivative gain
float K_follow_wall = 2;

float previousError = 0;
float integral = 0;
int pwmValue = 0;
int motorSpeed = 80;

void wallFollowPidControl(float sensor_left, float sensor_right, float sensor_front) {
  // Calculate error: difference between left and right sensors
  float error;

  //both walls missing
  if (sensor_left>600 && sensor_right>600){
    error = 0;
  }

  //follow right wall
  else if(sensor_left>600){
    // error = 350 - sensor_right * K_follow_wall;
    error = 0;

  }

  //follow left wall
  else if(sensor_right>600){
    // error = -350 + sensor_left * K_follow_wall;
    error = 0;
  }

  else{

    error = sensor_left - sensor_right;
  }
  
  integral += error;
  float derivative = error - previousError;

  // Calculate PID output
  pwmValue = KpD * error + KiD * integral + KdD * derivative;
  Serial.println(pwmValue);

  // If obstacle is detected in front, stop or reverse
  if (sensor_front < 100) {  // Adjust this threshold based on your sensor range
    setMotor(0, 0, PWML, IN1L, IN2L);  // Stop the motors
    setMotor(0, 0, PWMR, IN1R, IN2R); 
  } else {
    // Apply the PID correction to motors
    setMotor(1, motorSpeed - pwmValue, PWML, IN1L, IN2L);
    setMotor(1, motorSpeed + pwmValue, PWMR, IN1R, IN2R);   
  }
  // Update previous error for the next cycle
  previousError = error;
}

// void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
//   pwmVal = constrain(pwmVal, 0, 255);  // Ensure pwmVal is within valid range
//   analogWrite(pwm, pwmVal);
//   if (dir == 1) {
//     // Forward movement
//     digitalWrite(in1, HIGH);
//     digitalWrite(in2, LOW);
//   } else if (dir == -1) {
//     // Reverse movement
//     digitalWrite(in2, HIGH);
//     digitalWrite(in1, LOW);
//   } else {
//     // Stop motors
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, LOW);
//   }
//   delay(10);
// }
