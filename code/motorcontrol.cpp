#include "motorcontrol.h"
#include <Arduino.h>

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
