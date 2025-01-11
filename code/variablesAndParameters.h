#pragma once

// Thresholds for the sensors and PID constants
extern int forward_threshold; // Threshold for the front sensor to detect end of the path
extern int side_threshold; // Threshold for the side sensors to detect a wall
extern int side_threshold_error; // Error threshold for the side sensors
extern float K_singlewall_correction;

extern int maze_width; // Width of the maze in mm
extern int car_width; // Width of the car in mm


// sensor readings
extern float sensor_left;
extern float sensor_front;
extern float sensor_right;