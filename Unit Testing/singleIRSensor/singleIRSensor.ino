// This line imports the Adafruit VL53L0X library, which simplifies the interfacing and control of the VL53L0X IR time-of-flight sensor.
// The library provides functions to initialize the sensor, perform ranging measurements, and handle other related operations.

#include "Adafruit_VL53L0X.h"

// This creates an instance of the Adafruit_VL53L0X class named sensor.
Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

void setup() {
  // Sets the baud rate for serial communication to 115200 bits per second.
  Serial.begin(115200);

  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  // Checking if sensor boots
  if (!sensor.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    // We use this to create an infinite loop to halt the execution of the code
    while(1);
  }
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


void loop() {

  // Declares a VL53L0X_RangingMeasurementData_t object named measure.
  // This object will hold the ranging data (e.g., distance) obtained from the sensor.
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");

  // &measure is to pass in the address of measure, second argument specifies if we need a debug output or not
  sensor.rangingTest(&measure, false);

  // Checks the RangeStatus field of the measurement data.
  // A value of 4 indicates a phase failure (invalid measurement). If the value is not 4, the program proceeds to print the distance.
  if (measure.RangeStatus != 4) {
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println("Out of Range ");
  }
  // Making a short delay so we can see the output nicely
  delay(100);
}
