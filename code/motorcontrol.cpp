#include "motorcontrol.h"
#include <Arduino.h>
#include "variablesAndParameters.h"
#include "pins.h"
#include "turning.h"

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

void encoderSetup() {

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
    // for moment have a placeholder
}

void turnLeft()
{
    turn(-90);
}

void turnRight()
{
    turn(90);
}

void turnBack()
{
    turn(180);
}