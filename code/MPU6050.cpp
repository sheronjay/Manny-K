#include "MPU6050.h"

// Initialize global variables
float currentAngle = 0.0;
float gyroZ = 0.0;
unsigned long lastTime = 0;  


void initializeGyro() {
  // Initialize the MPU6050 sensor
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    while (1);
  }

  // Set the range of the gyroscope (optional)
  mpu.setGyroRange(Adafruit_MPU6050::GYRO_RANGE_250_DPS);
  
  // Print the sensor details
  Serial.println("MPU6050 Initialized!");
}

void updateTurnedAngle() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Gyroscope data is in radians per second, convert to degrees per second
  gyroZ = g.gyro.z * 180.0 / 3.14159;  // Convert rad/s to degrees/s

  // Calculate the current angle by integrating the angular velocity over time
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastTime) / 1000.0; // Time in seconds

  // Angle = previous angle + (gyro rate * delta time)
  currentAngle += gyroZ * deltaTime;
  lastTime = currentTime;
}