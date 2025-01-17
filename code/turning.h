#pragma once

float calculatePID(float error, float *integral, float *previousError);

void encoderSetup();

void printConstants();
void turn(int ang);