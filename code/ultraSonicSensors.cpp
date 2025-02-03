#include "Ultrasonic.h"
#include "ultraSonicSensors.h"
#include "variablesAndParameters.h"

// Define pins for ultrasonic sensors
#define TRIG_LEFT 2
#define ECHO_LEFT 3
#define TRIG_FRONT 4
#define ECHO_FRONT 5
#define TRIG_RIGHT 6
#define ECHO_RIGHT 7

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
  sensor_left = left.Ranging(CM);

  // Read FRONT sensor
  sensor_front = front.Ranging(CM);

  // Read RIGHT sensor
  sensor_right = right.Ranging(CM);
}