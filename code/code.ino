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

  // algorithmSetup();

  // wifi
  wifiSetup();

  Serial.println("Initializing sensors...");
  // initializeSensors();
  // encoderSetup();

  // wifi loop
  // wifiLoop(NULL);

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

  // printSerialAndSend("Setup done");
}

void loop()
{
  // readThreeSensors();
  // algorithmLoop();
  printSerialAndSend("Looping...");
  delay(1000);
}
