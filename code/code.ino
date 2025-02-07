#include "ultraSonicSensors.h"
#include "wallFollow.h"
#include "turning.h"
#include "variablesAndParameters.h"
#include "motorcontrol.h"
#include <Arduino.h>
#include "pins.h"
#include "MPU6050.h"

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting setup...");
    while (!Serial)
    {
        delay(1);
    }

    // motor setup
    Serial.println("Initializing motors...");
    encoderSetup();

    Serial.println("Initializing sensors...");
    initializeGyro();
    initializeSensors();

    Serial.println("Setup done");

    delay(4000);
}

void loop()
{
    readThreeSensors();

    if (sensor_front < forward_threshold)
    {
        if (sensor_left < side_threshold && sensor_right < side_threshold)
        {
            turnBack();
        }
        else if (sensor_left < side_threshold)
        {
            turnRight();
        }
        else if (sensor_right < side_threshold)
        {
            turnLeft();
        }
        else
        {
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
            // noWallFollowPidControl();
            setMotor(1, motorSpeed, PWML, IN1L, IN2L);
            setMotor(1, motorSpeed, PWMR, IN1R, IN2R);
        }
    }


}