#pragma once

// Thresholds for the sensors and PID constants
extern int forward_threshold; // Threshold for the front sensor to detect end of the path
extern int side_threshold;    // Threshold for the side sensors to detect a wall
extern int dist_to_single_wall;
extern int dist_to_single_wall_right;
extern int dist_to_single_wall_left;

// sensor readings
extern float sensor_left;
extern float sensor_front;
extern float sensor_right;

// run algorithm at encoder counts
extern int encoder_counts;          // this is used to call the algorithm at each new cell
extern int encoder_counts_per_cell; // size of each cell wrt encoder counts

// encoder values
extern int posL; // Encoder position for left motor
extern int posR; // Encoder position for right motor

extern float KpD; // Proportional gain for distance controller
extern float KdD; // Derivative gain for distance controller

extern float KpR; // Proportional gain for right distance controller
extern float KdR; // Derivative gain for right distance controller

extern float KpL; // Proportional gain for left distance controller
extern float KdL; // Derivative gain for left distance controller

extern float KpLR; // Proportional gain for no wall follow controller
extern float KdLR; // Derivative gain for no wall follow controller

extern float KpF; // Proportional gain for front sensor controller
extern float KdF; // Derivative gain for front sensor controller

extern float KpA; // Proportional gain for angle controller
extern float KiA; // Integral gain for angle controller
extern float KdA; // Derivative gain for angle controller

extern int motorSpeed; // base motor speed for motor control

// Constants for the distance controller
extern float previousError;
extern float previousEncoderError;
extern float previousLeftError;
extern float previousRightError;
extern float previousFrontError;
extern int pwmValue;


// Constants for the angle controller
extern float previousAngleError;
extern float currentAngle;