#include "VL53L0X_Sensors.h"
#include "wallFollow.h"
#include "turning.h"
#include "variablesAndParameters.h"
#include "algorithm.h"
#include "wifiUpdate.h"
#include "motorcontrol.h"
#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting setup...");
  while (!Serial)
  {
    delay(1);
  }

  algorithmSetup();

  // wifi
  wifiSetup();

  Serial.println("Initializing sensors...");
  // initializeSensors();
  encoderSetup();

  Serial.println("Setup done");

  // Create a FreeRTOS task for the WiFi loop
  xTaskCreate(
      wifiLoop,    // Task function
      "WiFi Task", // Task name
      4096,        // Stack size (in bytes)
      NULL,        // Task parameters
      1,           // Priority
      NULL         // Task handle
  );
}

void loop()
{
  // Updates the sensor_left, right, and front variables
  // readThreeSensors();
  // wallFollowPidControl(sensor_left, sensor_right, sensor_front);

  delay(3000);
  turnLeft();
  delay(3000);
  turnRight();
  delay(3000);
  turnBack();
  delay(3000);

  // if (encoder_counts >= cell_size)
  // {
  //   algorithmLoop();
  //   encoder_counts = 0;
  // }
}
