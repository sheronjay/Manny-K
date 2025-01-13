#include <Arduino.h>
#include "variablesAndParameters.h"

bool wallLeft()
{
  // Check the left sensor
  return digitalRead(sensor_left) < side_threshold;
}

bool wallRight()
{
  // Check the right sensor
  return digitalRead(sensor_right) < side_threshold;
}

bool wallFront()
{
  // Check the front sensor
  return digitalRead(sensor_front) < forward_threshold;
}
