#include "VL53L0X_Sensors.h"

// Sensor objects
Adafruit_VL53L0X left = Adafruit_VL53L0X();
Adafruit_VL53L0X front = Adafruit_VL53L0X();
Adafruit_VL53L0X right = Adafruit_VL53L0X();

// Measurement variables
VL53L0X_RangingMeasurementData_t measure_left;
VL53L0X_RangingMeasurementData_t measure_front;
VL53L0X_RangingMeasurementData_t measure_right;

void initializeSensors() {
  // Set XSHUT pins as OUTPUT
  pinMode(SHT_LEFT, OUTPUT);
  pinMode(SHT_FRONT, OUTPUT);
  pinMode(SHT_RIGHT, OUTPUT);

  // Reset all sensors
  digitalWrite(SHT_LEFT, LOW);
  digitalWrite(SHT_FRONT, LOW);
  digitalWrite(SHT_RIGHT, LOW);
  delay(10);

  // Bring out of reset all sensors
  digitalWrite(SHT_LEFT, HIGH);
  digitalWrite(SHT_FRONT, HIGH);
  digitalWrite(SHT_RIGHT, HIGH);
  delay(10);

  // Initialize LEFT sensor
  digitalWrite(SHT_LEFT, HIGH);
  digitalWrite(SHT_FRONT, LOW);
  digitalWrite(SHT_RIGHT, LOW);
  
  if (!left.begin(LEFT_ADDRESS)) {
    Serial.println(F("Failed to initialize LEFT sensor"));
    while (1);
  }
  delay(10);

  // Initialize FRONT sensor
  digitalWrite(SHT_FRONT, HIGH);
  if (!front.begin(FRONT_ADDRESS)) {
    Serial.println(F("Failed to initialize FRONT sensor"));
    while (1);
  }
  delay(10);

  // Initialize RIGHT sensor
  digitalWrite(SHT_RIGHT, HIGH);
  if (!right.begin(RIGHT_ADDRESS)) {
    Serial.println(F("Failed to initialize RIGHT sensor"));
    while (1);
  }
  delay(10);
}

void readThreeSensors() {
  // Read LEFT sensor
  left.rangingTest(&measure_left, false);
  Serial.print("Left: ");
  if (measure_left.RangeStatus != 4) {
    Serial.print(measure_left.RangeMilliMeter);
    Serial.print("mm");
  } else {
    Serial.print("Out of range");
  }

  Serial.print(" ");

  // Read FRONT sensor
  front.rangingTest(&measure_front, false);
  Serial.print("Front: ");
  if (measure_front.RangeStatus != 4) {
    Serial.print(measure_front.RangeMilliMeter);
    Serial.print("mm");
  } else {
    Serial.print("Out of range");
  }

  Serial.print(" ");

  // Read RIGHT sensor
  right.rangingTest(&measure_right, false);
  Serial.print("Right: ");
  if (measure_right.RangeStatus != 4) {
    Serial.print(measure_right.RangeMilliMeter);
    Serial.print("mm");
  } else {
    Serial.print("Out of range");
  }

  Serial.println();
}