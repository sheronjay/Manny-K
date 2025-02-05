#include "motorcontrol.h"
#include <Arduino.h>
#include "variablesAndParameters.h"
#include "pins.h"
#include "turning.h"
#include "ultraSonicSensors.h"
#include "wallFollow.h"

// Function to control motor direction and speed
void setMotor(int dir, int pwmVal, int pwm, int in1, int in2)
{
    pwmVal = constrain(pwmVal, 0, 255);
    analogWrite(pwm, pwmVal);

    if (dir == 1)
    { // Clockwise
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    }
    else if (dir == -1)
    { // Anticlockwise
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
    }
    else
    { // Stop
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    }
}

void encoderSetup()
{

    // Encoder pins setup
    pinMode(ENCAL, INPUT);
    pinMode(ENCBL, INPUT);
    pinMode(ENCAR, INPUT);
    pinMode(ENCBR, INPUT);

    // Motor pins setup
    pinMode(PWML, OUTPUT);
    pinMode(IN1L, OUTPUT);
    pinMode(IN2L, OUTPUT);
    pinMode(PWMR, OUTPUT);
    pinMode(IN1R, OUTPUT);
    pinMode(IN2R, OUTPUT);

    // Attach interrupts for encoders
    attachInterrupt(digitalPinToInterrupt(ENCAL), readEncoderL, RISING);
    attachInterrupt(digitalPinToInterrupt(ENCAR), readEncoderR, RISING);
}

void readEncoderL()
{
    encoder_counts++;
    int b = digitalRead(ENCBL);
    if (b > 0)
    {
        posL++;
    }
    else
    {
        posL--;
    }
}

void readEncoderR()
{
    encoder_counts++;
    int b = digitalRead(ENCBR);
    if (b > 0)
    {
        posR++;
    }
    else
    {
        posR--;
    }
}

void moveForward()
{
    encoder_counts = 0;
    while (encoder_counts < encoder_counts_per_cell)
    {
        readThreeSensors();
        if (sensor_left < side_threshold && sensor_right < side_threshold)
        {
            dist_to_single_wall_left = sensor_left;
            dist_to_single_wall_right = sensor_right;
            wallFollowPidControl(sensor_left, sensor_right);
        }
        else if (sensor_right >= side_threshold)
        {
            leftWallFollowPidControl(sensor_left);
        }
        else if (sensor_left >= side_threshold)
        {
            rightWallFollowPidControl(sensor_right);
        }
    }
}

void applyBreak()
{
    setMotor(-1, 200, PWML, IN1L, IN2L);
    setMotor(-1, 200, PWMR, IN1R, IN2R);
    delay(20);
    setMotor(0, 0, PWML, IN1L, IN2L);
    setMotor(0, 0, PWMR, IN1R, IN2R);
}