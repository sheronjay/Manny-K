#include "check.h"
#include <Arduino.h>
#include "variablesAndParameters.h"

bool checkLeft()
{
  // Check the left sensor
  return digitalRead(sensor_left) < side_threshold;
}

bool checkRight()
{
  // Check the right sensor
  return digitalRead(sensor_right) < side_threshold;
}

bool checkfront()
{
  // Check the front sensor
  return digitalRead(sensor_front) < forward_threshold;
}
