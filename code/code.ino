#include "VL53L0X_Sensors.h"
#include "wallFollow.h"
#include "turning.h"
#include "variablesAndParameters.h"
#include "bluetooth_update.h"

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    delay(1);
  }

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

  if (sensor_front < forward_threshold)
  {
    // Serial.println("Turning");
    if (sensor_left > side_threshold)
    {
      turn(-90);
    }

    else if (sensor_right > side_threshold)
    {
      turn(90);
    }

    else
    {
      turn(180);
    }
  }
}