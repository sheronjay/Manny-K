#include "VL53L0X_Sensors.h"
#include "wallFollow.h"
#include "turning.h"
#include "variablesAndParameters.h"

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    delay(1);
  }

  Serial.println("Initializing sensors...");
  initializeSensors();
  encoderSetup();
}

void loop()
{
  // Updates the sensor_left, right, and front variables
  float sensors[3];
  readThreeSensors(sensors);
  wallFollowPidControl(sensors[0], sensors[2], sensors[1]); // sensor[0]=sensor left   sensors[2]=sensors right    sensors[1]=sensors front
  delay(100);

  printConstants();

  if (sensors[1] < forward_threshold)
  {
    // Serial.println("Turning");
    if (sensors[0] > side_threshold)
    {
      turn(-90);
    }

    else if (sensors[2] > side_threshold)
    {
      turn(90);
    }

    else
    {
      turn(180);
    }
  }
}