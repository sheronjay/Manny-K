#pragma once

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2);
void encoderSetup();
void readEncoderL();

void readEncoderR();

void moveForward();

void applyBreak();