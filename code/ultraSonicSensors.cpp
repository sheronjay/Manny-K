#include "Ultrasonic.h"
#include "ultraSonicSensors.h"
#include "variablesAndParameters.h"
#include <Arduino.h>
#include "pins.h"

// Sensor objects
Ultrasonic left(TRIG_LEFT, ECHO_LEFT);
Ultrasonic front(TRIG_FRONT, ECHO_FRONT);
Ultrasonic right(TRIG_RIGHT, ECHO_RIGHT);

void initializeSensors()
{
  // Initialize pins for ultrasonic sensors
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
}

void readThreeSensors()
{
  // Read LEFT sensor
  sensor_left = left.read(CM);

  // Read FRONT sensor
  sensor_front = front.read(CM);

  // Read RIGHT sensor
  sensor_right = right.read(CM);
}