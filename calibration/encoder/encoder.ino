#include <Arduino.h>
#include "motorcontrol.h"
#include "wifiUpdate.h"
#include "variablesAndParameters.h"
#include "VL53L0X_Sensors.h"
#include "wallFollow.h"
#include "pins.h"

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

    printSerialAndSend("3");
    delay(1000);
    printSerialAndSend("2");
    delay(1000);
    printSerialAndSend("1");
    delay(1000);
    printSerialAndSend("Go!");
}

void loop()
{
    readThreeSensors();
    printSerialAndSend(String(posL) + " " + String(posR));
    if (sensor_front > 150)
    {
        // moveForward();
        noWallFollowPidControl();
    }
    else
    {
        setMotor(0, 0, PWML, IN1L, IN2L);
        setMotor(0, 0, PWMR, IN1R, IN2R);
        exit(0);
    }
}