#pragma once

// Declare global variables for the gyro and angle tracking
extern float currentAngle;  // Current angle (in degrees)
extern float gyroZ;         // Z-axis rotational velocity (in degrees per second)
extern unsigned long lastTime;  // Last time update

// Function declarations
void initializeGyro();
void updateTurnedAngle();