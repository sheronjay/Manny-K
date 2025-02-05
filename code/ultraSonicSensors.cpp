#include "ultraSonicSensors.h"
#include "variablesAndParameters.h"
#include "pins.h"
#include <Arduino.h>

// Speed of sound in cm/us
#define SOUND_SPEED 0.34

void initializeSensors()
{
  // Initialize pins for ultrasonic sensors
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  Serial.println("Initializing sensors...");
}

long readUltrasonicDistance(int trigPin, int echoPin)
{
  // Send a 10us pulse to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  long distance = duration * SOUND_SPEED / 2;

  return distance;
}

void readThreeSensors()
{
  // Read LEFT sensor
  sensor_left = readUltrasonicDistance(TRIG_LEFT, ECHO_LEFT);

  // Read FRONT sensor
  sensor_front = readUltrasonicDistance(TRIG_FRONT, ECHO_FRONT);

  // Read RIGHT sensor
  sensor_right = readUltrasonicDistance(TRIG_RIGHT, ECHO_RIGHT);
}

void readLeftSensor(void *parameter)
{

  for (;;)
  {
    // Infinite loop
    sensor_left = readUltrasonicDistance(TRIG_LEFT, ECHO_LEFT);
    vTaskDelay(100 / portTICK_PERIOD_MS); // Non-blocking delay
  }
}

void readFrontSensor(void *parameter)
{

  for (;;)
  {
    // Infinite loop
    sensor_front = readUltrasonicDistance(TRIG_FRONT, ECHO_FRONT);
    vTaskDelay(100 / portTICK_PERIOD_MS); // Non-blocking delay
  }
}

void readRightSensor(void *parameter)
{
  for (;;)
  {
    // Infinite loop
    sensor_right = readUltrasonicDistance(TRIG_RIGHT, ECHO_RIGHT);
    vTaskDelay(100 / portTICK_PERIOD_MS); // Non-blocking delay
  }
}