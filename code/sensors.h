#include "pins.h"
// Importing the adafruit sensor library
#include "Adafruit_VL53L0X.h"


// Objects to store the sensors (type: Adafruit_VL53L0X)
Adafruit_VL53L0X left = Adafruit_VL53L0X();
Adafruit_VL53L0X front = Adafruit_VL53L0X();
Adafruit_VL53L0X right = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure_left;
VL53L0X_RangingMeasurementData_t measure_front;
VL53L0X_RangingMeasurementData_t measure_right;

void setID() {
  // When XSHUT pin is set to HIGH, the sensor works and does not when set to LOW

  // Reset all sensors
  digitalWrite(SHT_LEFT, LOW);
  digitalWrite(SHT_FRONT, LOW);
  digitalWrite(SHT_RIGHT, LOW);
  delay(10);

  // Unreset all sensors
  digitalWrite(SHT_LEFT, HIGH);
  digitalWrite(SHT_FRONT, HIGH);
  digitalWrite(SHT_RIGHT, HIGH);
  delay(10);

  // Activate LEFT and reset others
  digitalWrite(SHT_LEFT, HIGH);
  digitalWrite(SHT_FRONT, LOW);
  digitalWrite(SHT_RIGHT, LOW);

  // Initialize left sensors
  if (!left.begin(LEFT_ADDRESS)) {
    Serial.println(F("Failed to boot left VL53L0X"));
    while (1);
  }
  delay(10);

  // Activate FRONT and reset others
  digitalWrite(SHT_FRONT, HIGH);
  digitalWrite(SHT_RIGHT, LOW);

  // Initialize FRONT
  if (!front.begin(FRONT_ADDRESS)) {
    Serial.println(F("Failed to boot front VL53L0X"));
    while (1);
  }
  delay(10);

  // Activate RIGHT
  digitalWrite(SHT_RIGHT, HIGH);
  delay(10);

  // initialize RIGHT
  if (!right.begin(RIGHT_ADDRESS)) {
    Serial.println(F("Failed to boot right VL53L0X"));
    while (1);
  }
}

void read_three_sensors() {
  left.rangingTest(&measure_left, false); // read sensor 1
  front.rangingTest(&measure_front, false); // read sensor 2
  right.rangingTest(&measure_right, false); // read sensor 3

  // print left sensor reading
  Serial.print("Left: ");
  if (measure_left.RangeStatus != 4) {
    sensor_left = measure_left.RangeMilliMeter;
    Serial.print(sensor_left);
    Serial.print("mm");
  } else {
    Serial.print("Out of range");
  }

  Serial.print(" ");

  // print front sensor reading
  Serial.print("Front: ");
  if (measure_front.RangeStatus != 4) {
    sensor_front = measure_front.RangeMilliMeter;
    Serial.print(sensor_front);
    Serial.print("mm");
  } else {
    Serial.print("Out of range");
  }

  Serial.print(" ");

  // print right sensor reading
  Serial.print("Right: ");
  if (measure_right.RangeStatus != 4) {
    sensor_right = measure_right.RangeMilliMeter;
    Serial.print(sensor_right);
    Serial.print("mm");
  } else {
    Serial.print("Out of range");
  }

  Serial.println();
}

void setupSensors() {
  Serial.begin(115200);

  while (!Serial) {
    delay(1);
  }

  Serial.println("Shutdown pins inited...");

  digitalWrite(SHT_LEFT, LOW);
  digitalWrite(SHT_FRONT, LOW);
  digitalWrite(SHT_RIGHT, LOW);

  Serial.println("All sensors in reset mode...(pins are low)");

  Serial.println("Starting...");
  // SetID function is responsible for assigning addresses to each sensor
  setID();
}
