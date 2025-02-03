#include <Arduino.h>

#define TRIG_PIN_1 2
#define ECHO_PIN_1 3
#define TRIG_PIN_2 4
#define ECHO_PIN_2 5
#define TRIG_PIN_3 6
#define ECHO_PIN_3 7

void setup() {
    Serial.begin(9600);
    pinMode(TRIG_PIN_1, OUTPUT);
    pinMode(ECHO_PIN_1, INPUT);
    pinMode(TRIG_PIN_2, OUTPUT);
    pinMode(ECHO_PIN_2, INPUT);
    pinMode(TRIG_PIN_3, OUTPUT);
    pinMode(ECHO_PIN_3, INPUT);
}

void loop() {
    long duration1, distance1;
    long duration2, distance2;
    long duration3, distance3;

    // Sensor 1
    digitalWrite(TRIG_PIN_1, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN_1, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN_1, LOW);
    duration1 = pulseIn(ECHO_PIN_1, HIGH);
    distance1 = duration1 * 0.034 / 2;

    // Sensor 2
    digitalWrite(TRIG_PIN_2, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN_2, LOW);
    duration2 = pulseIn(ECHO_PIN_2, HIGH);
    distance2 = duration2 * 0.034 / 2;

    // Sensor 3
    digitalWrite(TRIG_PIN_3, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN_3, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN_3, LOW);
    duration3 = pulseIn(ECHO_PIN_3, HIGH);
    distance3 = duration3 * 0.034 / 2;

    Serial.print("Distance1: ");
    Serial.print(distance1);
    Serial.print(" cm, Distance2: ");
    Serial.print(distance2);
    Serial.print(" cm, Distance3: ");
    Serial.print(distance3);
    Serial.println(" cm");

    delay(1000);
}