#pragma once // Makes sure the header file is not defined ( conditional define statement )

// Sensor I2C addresses
#define LEFT_ADDRESS 0x30
#define FRONT_ADDRESS 0x31
#define RIGHT_ADDRESS 0x32

// XSHUT pins
#define SHT_LEFT 13
#define SHT_FRONT 11
#define SHT_RIGHT 12

// Function prototypes
void initializeSensors();
void readThreeSensors();


