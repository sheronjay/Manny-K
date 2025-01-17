#include "VL53L0X_Sensors.h"
#include "wallFollow.h"
#include "turning.h"
#include "variablesAndParameters.h"
#include "algorithm.h"
#include "wifiUpdateParameters.h"
#include "motorcontrol.h"

void setup()
{
  Serial.begin(9600);

  while (!Serial)
  {
    delay(1);
  }

  algorithmSetup();

  // wifi
  wifiSetup();

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

  // Wifi
  wifiLoop();

  if (encoder_counts >= cell_size)
  {
    algorithmLoop();
    encoder_counts = 0;
  }
}