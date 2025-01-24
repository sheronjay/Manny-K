#include "variablesAndParameters.h"

int forward_threshold = 100;  // Threshold for the front sensor to detect end of the path
int side_threshold = 200;     // Threshold for the side sensors to detect a wall


int dist_to_single_wall = 65; // Distance to be maintained when following a single wall
int dist_to_single_wall_right = 65;
int dist_to_single_wall_left = 65;


float sensor_left = dist_to_single_wall;
float sensor_front = dist_to_single_wall;
float sensor_right = dist_to_single_wall;

int encoder_counts = 0;
int encoder_counts_per_cell = 7000;

int posL = 0; // Encoder position for left motor
int posR = 0; // Encoder position for right motor

float KpD = 0.5; // Proportional gain for distance controller
float KdD = 0.5;   // Derivative gain for distance controller

float KpA = 0.5; // Proportional gain for angle controller
float KiA = 0.0; // Integral gain for angle controller
float KdA = 0.0; // Derivative gain for angle controller

float KpR = 0.4; // Proportional gain for right distance controller
float KdR = 0.2; // Derivative gain for right distance controller

float KpL = 0.4; // Proportional gain for left distance controller
float KdL = 0.2; // Derivative gain for left distance controller

float KpLR = 0.5; // Proportional gain for no wall follow controller
float KdLR = 0.5; // Derivative gain for no wall follow controller

float KpF = 0.5; // Proportional gain for front sensor controller
float KdF = 0.5; // Derivative gain for front sensor controller

int motorSpeed = 80;

// Constants for the distance controller
float previousError = 0;
float previousEncoderError = 0;
float previousLeftError = 0;
float previousRightError = 0;
float previousFrontError = 0;
int pwmValue = 0;