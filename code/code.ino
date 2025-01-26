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

    // Create a FreeRTOS task for the WiFi loop
    xTaskCreate(
        wifiLoop,    // Task function
        "WiFi Task", // Task name
        4096,        // Stack size (in bytes)
        NULL,        // Task parameters
        1,           // Priority
        NULL         // Task handle
    );

    // motor setup
    Serial.println("Initializing motors...");
    motorSetup();
    encoderSetup();

    Serial.println("Initializing sensors...");
    initializeSensors();

    Serial.println("Setup done");

    printSerialAndSend("Setup done");
}

void loop()
{
    readThreeSensors();

    if (sensor_front < forward_threshold)
    {
        if (sensor_left < side_threshold && sensor_right < side_threshold)
        {
            printSerialAndSend("Turning back");
            turnBack();
        }
        else if (sensor_left < side_threshold)
        {
            printSerialAndSend("Turning right");
            turnRight();
        }
        else if (sensor_right < side_threshold)
        {
            printSerialAndSend("Turning left");
            turnLeft();
        }
        else
        {
            printSerialAndSend("both sides available, turnning left");
            turnLeft();
        }
    }
    else
    {
        if (sensor_left < side_threshold && sensor_right < side_threshold)
        {
            dist_to_single_wall_left = sensor_left;
            dist_to_single_wall_right = sensor_right;
            wallFollowPidControl(sensor_left, sensor_right);
        }
        else if (sensor_left < side_threshold)
        {
            leftWallFollowPidControl(sensor_left);
        }
        else if (sensor_right < side_threshold)
        {
            rightWallFollowPidControl(sensor_right);
        }
        else
        {
            noWallFollowPidControl();
        }
    }
    // algorithmLoop();
    printSerialAndSend(String(sensor_left) + "," + String(sensor_front) + "," + String(sensor_right));
}
