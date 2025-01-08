#include <Arduino.h>
#pragma once // Makes sure the header file is not defined ( conditional define statement )

// Motor Left
#define ENCAL 2
#define ENCBL 3
#define PWML 4
#define IN1L 5
#define IN2L 6

// Motor Right
#define ENCAR 18
#define ENCBR 19
#define PWMR 8
#define IN1R 9
#define IN2R 10

// Constants for the distance controller
extern float KpD;  // Proportional gain
extern float KiD;  // Integral gain
extern float KdD;  // Derivative gain

extern float previousError;
extern float integral;
extern int pwmValue;
extern int motorSpeed;

// Function prototypes
void wallFollowPidControl(float sensor_left, float sensor_right, float sensor_front);
void setMotor(int dir, int pwmVal, int pwm, int in1, int in2);