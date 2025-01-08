#include "VL53L0X_Sensors.h"

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    delay(1);
  }

  Serial.println("Initializing sensors...");
  initializeSensors();
}

void loop() {
  // Updates the sensor_left, right, and front variables
  readThreeSensors();
  delay(100);
}