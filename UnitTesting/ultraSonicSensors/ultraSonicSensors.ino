#include <Ultrasonic.h>

// Define pins for ultrasonic sensors
#define TRIG_PIN1 16
#define ECHO_PIN1 17
#define TRIG_PIN2 18
#define ECHO_PIN2 19
#define TRIG_PIN3 23
#define ECHO_PIN3 22

// Create Ultrasonic objects for each sensor
Ultrasonic ultrasonic1(TRIG_PIN1, ECHO_PIN1);
Ultrasonic ultrasonic2(TRIG_PIN2, ECHO_PIN2);
Ultrasonic ultrasonic3(TRIG_PIN3, ECHO_PIN3);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // Read distance from each sensor
    float distance1 = ultrasonic1.read(CM);
    float distance2 = ultrasonic2.read(CM);
    float distance3 = ultrasonic3.read(CM);

    // Print the distances to the Serial Monitor
    Serial.print("Distance 1: ");
    Serial.print(distance1);
    Serial.println(" cm");

    Serial.print("Distance 2: ");
    Serial.print(distance2);
    Serial.println(" cm");

    Serial.print("Distance 3: ");
    Serial.print(distance3);
    Serial.println(" cm");

    // Wait for a second before the next reading
    delay(1000);
}