#pragma once // Makes sure the header file is not defined ( conditional define statement )

// Sensor I2C addresses
#define LEFT_ADDRESS 0x30
#define FRONT_ADDRESS 0x31
#define RIGHT_ADDRESS 0x32

// Function prototypes
void initializeSensors();
void readThreeSensors();
