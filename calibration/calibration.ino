#include <Wire.h>
#include <Adafruit_VL53L0X.h>

// Sensor I2C addresses
#define LEFT_ADDRESS 0x30
#define FRONT_ADDRESS 0x31
#define RIGHT_ADDRESS 0x32

// XSHUT pins
#define SHT_LEFT 23
#define SHT_FRONT 26
#define SHT_RIGHT 25

// Create an instance of the VL53L0X sensor
Adafruit_VL53L0X left = Adafruit_VL53L0X();
Adafruit_VL53L0X front = Adafruit_VL53L0X();
Adafruit_VL53L0X right = Adafruit_VL53L0X();

// Measurement variables
VL53L0X_RangingMeasurementData_t measure_left;
VL53L0X_RangingMeasurementData_t measure_front;
VL53L0X_RangingMeasurementData_t measure_right;

const int numReadings = 20; // Number of readings to average
int readIndex = 0;          // Index of the current reading
int total = 0;              // Sum of readings
int distance;

void setup()
{

  Serial.begin(115200); // Initialize serial communication for debugging
  Serial.println("VL53L0X Distance Sensor Setup");

  pinMode(SHT_LEFT, OUTPUT);
  pinMode(SHT_FRONT, OUTPUT);
  pinMode(SHT_RIGHT, OUTPUT);
  Serial.println("XSHUT pins set as OUTPUT");

  delay(2000);
  // // Reset all sensors
  // digitalWrite(SHT_LEFT, LOW);
  // digitalWrite(SHT_FRONT, LOW);
  // digitalWrite(SHT_RIGHT, LOW);
  // delay(10);

  // // Bring out of reset all sensors
  // digitalWrite(SHT_LEFT, HIGH);
  // digitalWrite(SHT_FRONT, HIGH);
  // digitalWrite(SHT_RIGHT, HIGH);
  // delay(10);

  // // Initialize LEFT sensor
  // digitalWrite(SHT_LEFT, HIGH);
  // digitalWrite(SHT_FRONT, LOW);
  // digitalWrite(SHT_RIGHT, LOW);

  if (!left.begin(LEFT_ADDRESS))
  {
    Serial.println(F("Failed to initialize LEFT sensor"));
    while (1)
      ;
  }

  if (!right.begin(RIGHT_ADDRESS))
  {
    Serial.println(F("Failed to initialize LEFT sensor"));
    while (1)
      ;
  }
  if (!front.begin(FRONT_ADDRESS))
  {
    Serial.println(F("Failed to initialize LEFT sensor"));
    while (1)
      ;
  }
  delay(2000);

  left.setMeasurementTimingBudgetMicroSeconds(200000);
  front.setMeasurementTimingBudgetMicroSeconds(200000);
  right.setMeasurementTimingBudgetMicroSeconds(200000);
}

void loop()
{
  while (readIndex < numReadings)
  {
    left.rangingTest(&measure_left, false); // Perform a ranging test (no debug output)
    if (measure_left.RangeStatus != 4)
    {
      distance = measure_left.RangeMilliMeter;
      if (distance >= 30 && distance < 200)
      {
        total += distance;
        readIndex++;
      }
    }
  }

  Serial.println(total / numReadings);
  readIndex = 0;
  total = 0;
  delay(1000); // Delay for 1 second between readings
}