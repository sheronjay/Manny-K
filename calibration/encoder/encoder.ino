#include <Arduino.h>
#include "../../code/motorcontrol.h"
#include "../../code/wifiUpdate.h"
#include "../../code/variablesAndParameters.h"
#include "../../code/VL53L0X_Sensors.h"

void setup()
{
    Serial.begin(9600);

    encoderSetup();
    wifiSetup();
    initializeSensors();

    xTaskCreate(
        wifiLoop,    // Task function
        "WiFi Task", // Task name
        4096,        // Stack size (in bytes)
        NULL,        // Task parameters
        1,           // Priority
        NULL         // Task handle
    );

    printSerialAndSend("setup complete");

    posL = 0;
    posR = 0;
}

void loop()
{
    readThreeSensors();
    printSerialAndSend(String(posL) + " " + String(posR));
    if (sensor_front > 100)
    {
        moveForward();
    }
}