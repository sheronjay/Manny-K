#pragma once

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2);
void encoderSetup();
void readEncoderL();

void readEncoderR();

void moveForward();

void turnLeft();
void turnRight();
void turnBack();
void applyBreak();