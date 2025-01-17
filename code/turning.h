#pragma once

float calculatePID(float error, float *integral, float *previousError);

void printConstants();
void turn(int ang);