#include "VL53L0X_Sensors.h"
#include "wallFollow.h"


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
  float sensors[3];
  readThreeSensors(sensors);
  wallFollowPidControl(sensors[0], sensors[1], sensors[2]);
  delay(100);
}