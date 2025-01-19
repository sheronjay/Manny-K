// This is a little side note
// Watch this video to understand how the encoder works https://www.youtube.com/watch?v=dTGITLnYAY0
// Basically either of the ENCA or ENCB pins will be triggered first when the motor rotates and completes a encoding count
// Depending on what pin is triggered first we can decide as to what direction our motor rotates. We will be using the serial plotter to check it out.

// We are going to be using digit interuptable pins for the encoders (pins 2, 3, 19 and 18)
#define ENCA 2
#define ENCB 3

// Defining the input pins for the motor
#define PWM 13
#define IN1 12
#define IN2 14

// setting the starting position to zero
int pos = 0;

void setup() {
  Serial.begin(9600);
  // Set the pins to input mode
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(PWM, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  // Attach interrupt takes 3 arguments, the pin to interrupt, the function to be called when interrupt is triggered and the mode
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

void loop() {
  Serial.println(pos);
  setMotor(-1, 255, PWM, IN1, IN2);
  delay(2000);
  setMotor(1, 125, PWM, IN1, IN2);
  delay(2000);
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
