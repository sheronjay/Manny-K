#include <Arduino.h>

// define the pins here like below.
//
// Sensor pins
// Defining addresses for the sensors
#define LEFT_ADDRESS 0x30
#define FRONT_ADDRESS 0x31
#define RIGHT_ADDRESS 0x32

// We can't use the three sensors at once
// So we have to disable two while we use one. For that we need to connect XSHUT pins
#define SHT_LEFT 7
#define SHT_FRONT 6
#define SHT_RIGHT 5

// Motor pins
// We are going to be using digit interuptable pins for the encoders (pins 2, 3, 19 and 18)
#define ENCA 2
#define ENCB 3

// Defining the input pins for the motor
#define PWM 5
#define IN1 6
#define IN2 7



// initializing pins
void initializePins() {
  // Sensor pins
  pinMode(SHT_LEFT, OUTPUT);
  pinMode(SHT_FRONT, OUTPUT);
  pinMode(SHT_RIGHT, OUTPUT);


  // Motor pins
  pinMode(PWM, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}