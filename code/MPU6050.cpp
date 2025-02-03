#include "MPU6050.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// Initialize global variables
float currentAngle = 0.0;
float gyroZ = 0.0;
unsigned long lastTime = 0;  


void initializeGyro() {
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
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
  if (abs(gyroZ) > 0.8 ) {
    currentAngle += gyroZ * deltaTime;
  }
  lastTime = currentTime;
}