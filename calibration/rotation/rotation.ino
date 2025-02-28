#include <Arduino.h>
#include "variablesAndParameters.h"
#include "pins.h"
#include "motorcontrol.h"
#include "wifiUpdate.h"
#include "VL53L0X_Sensors.h"
#include "turning.h"

int initial_front_sensor;
bool turning_completed = false;
int angle = 0;

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting setup...");
    while (!Serial)
    {
        delay(1);
    }

    // wifi
    wifiSetup();

    Serial.println("Initializing sensors...");
    initializeSensors();
    encoderSetup();

    // Create a FreeRTOS task for the WiFi loop
    xTaskCreate(
        wifiLoop,    // Task function
        "WiFi Task", // Task name
        4096,        // Stack size (in bytes)
        NULL,        // Task parameters
        1,           // Priority
        NULL         // Task handle
    );

    printSerialAndSend("Setup done");
    readThreeSensors();
    printSerialAndSend(String(sensor_front));
    initial_front_sensor = sensor_front;

    turn(270);
    angle += 270;
}

void loop()
{
    printSerialAndSend(String(angle));

    readThreeSensors();
    if (sensor_front < initial_front_sensor - 10)
    {
        turning_completed = true;
    }

    if (!turning_completed)
    {
        turn(5);
        angle += 5;
    }
}