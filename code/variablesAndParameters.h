#pragma once

// Thresholds for the sensors and PID constants
extern int forward_threshold; // Threshold for the front sensor to detect end of the path
extern int side_threshold; // Threshold for the side sensors to detect a wall
extern int dist_to_single_wall;

extern int maze_width; // Width of the maze in mm
extern int car_width; // Width of the car in mm


// sensor readings
extern float sensor_left;
extern float sensor_front;
extern float sensor_right;


// run algorithm at encoder counts
extern int encoder_counts;  // this is used to call the algorithm at each new cell
extern int cell_size; // size of each cell wrt encoder counts


// encoder values
extern int posL; // Encoder position for left motor
extern int posR; // Encoder position for right motor


extern float KpD; // Proportional gain for distance controller
extern float KdD; // Derivative gain for distance controller

extern float KpR; // Proportional gain for right distance controller
extern float KdR; // Derivative gain for right distance controller

extern float KpL; // Proportional gain for left distance controller
extern float KdL; // Derivative gain for left distance controller

extern float KpA; // Proportional gain for angle controller
extern float KiA; // Integral gain for angle controller
extern float KdA; // Derivative gain for angle controller