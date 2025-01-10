#pragma once // Makes sure the header file is not defined ( conditional define statement )

#include <Arduino.h>

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


// Function prototypes
void wallFollowPidControl(float sensor_left, float sensor_right, float sensor_front);
