#include "pins.h"
#include "variables.h"

int pos = 0;

void setupMotors() {
  Serial.begin(9600);
  // Set the pins to input mode
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  // Attach interrupt takes 3 arguments, the pin to interrupt, the function to be called when interrupt is triggered and the mode
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

void readEncoder() {
  // Here since we used ENCA to catch the interrupt we need to now check the STATE of ENCB to determine the position
  int b = digitalRead(ENCB);
  if (b > 0) {
    pos++;
  } else {
    pos--;
  }
}

// This function is responsible for driving any motor at given speed and direction
void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  // Analog write function takes the pin number, and then the pwmValue
  pwmVal = constrain(pwmVal, 0, 255);
  analogWrite(pwm, pwmVal);
  if (dir == 1) {
    // Probably clockwise
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (dir == -1) {
    // Anticlockwise
    digitalWrite(in2, HIGH);
    digitalWrite(in1, LOW);
  } else {
    // Not rotating
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}
