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

void setID()
{
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
  if (!left.begin(LEFT_ADDRESS))
  {
    Serial.println(F("Failed to boot left VL53L0X"));
    while (1)
      ;
  }
  delay(10);

  // Activate FRONT and reset others
  digitalWrite(SHT_FRONT, HIGH);
  digitalWrite(SHT_RIGHT, LOW);

  // Initialize FRONT
  if (!front.begin(FRONT_ADDRESS))
  {
    Serial.println(F("Failed to boot front VL53L0X"));
    while (1)
      ;
  }
  delay(10);

  // Activate RIGHT
  digitalWrite(SHT_RIGHT, HIGH);
  delay(10);

  // initialize RIGHT
  if (!right.begin(RIGHT_ADDRESS))
  {
    Serial.println(F("Failed to boot right VL53L0X"));
    while (1)
      ;
  }
}

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    delay(1);
  }

  pinMode(SHT_LEFT, OUTPUT);
  pinMode(SHT_FRONT, OUTPUT);
  pinMode(SHT_RIGHT, OUTPUT);

  Serial.println("Shutdown pins inited...");

  digitalWrite(SHT_LEFT, LOW);
  digitalWrite(SHT_FRONT, LOW);
  digitalWrite(SHT_RIGHT, LOW);

  Serial.println("All sensors in reset mode...(pins are low)");

  Serial.println("Starting...");
  // SetID function is responsible for assigning addresses to each sensor
  setID();

  Serial.println("SetID function called...");

  // left.setMeasurementTimingBudgetMicroSeconds(200);
  // front.setMeasurementTimingBudgetMicroSeconds(200);
  // right.setMeasurementTimingBudgetMicroSeconds(200);

  left.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY);
  front.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY);
  right.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY);

  Serial.println("Measurement timing budget set to 200000...");
}

void loop()
{
  while (readIndex < numReadings)
  {
    front.rangingTest(&measure_left, false); // Perform a ranging test (no debug output)
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