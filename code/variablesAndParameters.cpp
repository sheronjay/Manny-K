#include "variablesAndParameters.h"

int forward_threshold = 100; // Threshold for the front sensor to detect end of the path
int side_threshold = 500; // Threshold for the side sensors to detect a wall
int side_threshold_error = 100; // Error threshold for the side sensors
float K_singlewall_correction = 0.8;

int maze_width = 500; // Width of the maze in mm
int car_width = 150; // Width of the car in mm

float sensor_left = 0;
float sensor_front = 0;
float sensor_right = 0;