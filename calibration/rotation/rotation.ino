#include <Arduino.h>
#include "../../code/variablesAndParameters.h"
#include "../../code/pins.h"
#include "../../code/motorcontrol.h"
#include "../../code/wifiUpdate.h"
#include "../../code/VL53L0X_Sensors.h"
#include "../../code/turning.cpp"

int initial_front_sensor;
bool turning_completed = false;

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

    posL = 0;
    posR = 0;
    readThreeSensors();
    printSerialAndSend(String(sensor_front));
    initial_front_sensor = sensor_front;

    turn(270);
}

void loop()
{
    printSerialAndSend(String(posL) + String(" ") + String(posR));

    readThreeSensors();
    if (sensor_front < initial_front_sensor - 10)
    {
        turning_completed = true;
    }

    if (!turning_completed)
    {
        turn(5);
    }
}