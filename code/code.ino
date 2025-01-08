#include "VL53L0X_Sensors.h"
#include "wallFollow.h"
#include "turning.h"

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
  wallFollowPidControl(sensors[0], sensors[1], sensors[2]);
  delay(100);

  printConstants();

  if (sensors[1] < 500)
  {

    if (sensors[0] < 500)
    {
      turn(90);
    }
    else if (sensors[2] < 500)
    {
      turn(-90);
    }
    else
    {
      turn(180);
    }
  }
}