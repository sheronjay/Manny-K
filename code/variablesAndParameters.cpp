#include "variablesAndParameters.h"

int forward_threshold =
    100; // Threshold for the front sensor to detect end of the path
int side_threshold = 500; // Threshold for the side sensors to detect a wall
int dist_to_single_wall =
    50; // Distance to be maintained when following a single wall

int maze_width = 500; // Width of the maze in mm
int car_width = 100;  // Width of the car in mm

float sensor_left = (maze_width - car_width) * 0.5;
float sensor_front = (maze_width - car_width) * 0.5;
float sensor_right = (maze_width - car_width) * 0.5;

int encoder_counts = 0;
int encoder_counts_per_cell = 7000;

int posL = 0; // Encoder position for left motor
int posR = 0; // Encoder position for right motor

float KpD = 1; // Proportional gain for distance controller
float KdD = 0; // Derivative gain for distance controller

float KpA = 1.0; // Proportional gain for angle controller
float KiA = 0.0; // Integral gain for angle controller
float KdA = 0.0; // Derivative gain for angle controller

float KpR = 1.0; // Proportional gain for right distance controller
float KdR = 0.0; // Derivative gain for right distance controller

float KpL = 1.0; // Proportional gain for left distance controller
float KdL = 0.0; // Derivative gain for left distance controller

int motorSpeed = 80;
