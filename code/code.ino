#include "VL53L0X_Sensors.h"
#include "wallFollow.h"
#include "turning.h"
#include "variablesAndParameters.h"
#include "bluetooth_update.h"
#include "algorithm.h"

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    delay(1);
  }

  algorithmSetup();

  Serial.println("Bluetooth initialization...");
  setupBluetooth();

  Serial.println("Initializing sensors...");
  initializeSensors();
  encoderSetup();
}

void loop()
{
  // Updates the sensor_left, right, and front variables
  readThreeSensors();
  wallFollowPidControl(sensor_left, sensor_right, sensor_front);
  delay(100);

  printConstants();

  if (encoder_counts >= cell_size)
  {
    algorithmLoop();
    encoder_counts = 0;
  }
}