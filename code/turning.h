
// Motor Left
#define ENCAL 2
#define ENCBL 3
#define PWML 4
#define IN1L 5
#define IN2L 6

// Motor Right
#define ENCAR 18
#define ENCBR 19
#define PWMR 8
#define IN1R 9
#define IN2R 10

// Robot constants
float l = 17.5; // Wheelbase length (cm)
float r = 3.3;  // Wheel radius (cm)
int ratio = (75*823.1)/360; // Gear ratio

// Global Variables for PID
float KpA = 1.0;  // Proportional gain
float KiA = 0.01;  // Integral gain
float KdA = 2.5;  // Derivative gain

float p;
float i;
float d;

float errorL = 0, errorR = 0; // Error values for left and right motors
float integralL = 0, integralR = 0; // Integral terms
float previousErrorL = 0, previousErrorR = 0; // Previous errors for derivative calculation

volatile int posL = 0; // Encoder position for left motor
volatile int posR = 0; // Encoder position for right motor

void setup() {
  Serial.begin(9600);

  //BTSerial.begin(9600);  // Start communication with Bluetooth module
  Serial.println("Bluetooth HC-05 Module Started");


  // Encoder pins setup
  pinMode(ENCAL, INPUT);
  pinMode(ENCBL, INPUT);
  pinMode(ENCAR, INPUT);
  pinMode(ENCBR, INPUT);

  // Motor pins setup
  pinMode(PWML, OUTPUT);
  pinMode(IN1L, OUTPUT);
  pinMode(IN2L, OUTPUT);
  pinMode(PWMR, OUTPUT);
  pinMode(IN1R, OUTPUT);
  pinMode(IN2R, OUTPUT);

  // Attach interrupts for encoders
  attachInterrupt(digitalPinToInterrupt(ENCAL), readEncoderL, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCAR), readEncoderR, RISING);
}

void loop() {

  if (Serial.available()) {
    p = Serial.parseFloat();  // Read the first float (kP)
    d = Serial.parseFloat();  // Read the second float (kI)
    i = Serial.parseFloat();  // Read the third float (kD)

    if (p != 0) {
      KpA = p;
      KiA = i;
      KdA = d;

      Serial.println(KpA);
      Serial.println(KiA);
      Serial.println(KdA);
    }
  }

  // Test turning
  Serial.println("Turning 90 degrees:");
  turn(90);
  delay(3000);

  Serial.println("Turning -90 degrees:");
  turn(180);
  delay(1000);

  Serial.println("Turning 180 degrees:");
  turn(360);
  delay(1000);
}

void turn(int ang) {
  // Calculate target counts for the given angle
  float targetCounts = (abs(ang) * l * ratio) / (720 * r);
  posL = 0;
  posR = 0;

  Serial.print("Target Counts: ");
  Serial.println(targetCounts);

  // Turn logic
  while ((abs(posL) < targetCounts) && (abs(posR) < targetCounts)) {
    // Calculate errors
    errorL = targetCounts - abs(posL);
    errorR = targetCounts - abs(posR);

    // Calculate PID outputs
    float controlL = calculatePID(errorL, &integralL, &previousErrorL);
    float controlR = calculatePID(errorR, &integralR, &previousErrorR);

    // Limit control output to valid PWM range
    controlL = constrain(controlL, 0, 255);
    controlR = constrain(controlR, 0, 255);

    // Set motor directions based on turning angle
    if (ang > 0) { // Turn right
      setMotor(1, controlL, PWML, IN1L, IN2L);
      setMotor(-1, controlR, PWMR, IN1R, IN2R);
    } else if (ang <0 ) { // Turn left
      setMotor(-1, controlL, PWML, IN1L, IN2L);
      setMotor(1, controlR, PWMR, IN1R, IN2R);
    }
  }

  // Stop motors after completing the turn
  setMotor(0, 0, PWML, IN1L, IN2L);
  setMotor(0, 0, PWMR, IN1R, IN2R);

  delay(1000); // Allow time to stabilize
  return;
}

void readEncoderL() {
  int b = digitalRead(ENCBL);
  if (b > 0) {
    posL++;
  } else {
    posL--;
  }
}

void readEncoderR() {
  int b = digitalRead(ENCBR);
  if (b > 0) {
    posR++;
  } else {
    posR--;
  }
}

// Function to control motor direction and speed
void setMotor(int dir, int pwmVal, int pwm, int in1, int in2) {
  pwmVal = constrain(pwmVal, 0, 255);
  analogWrite(pwm, pwmVal);

  if (dir == 1) { // Clockwise
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (dir == -1) { // Anticlockwise
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else { // Stop
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

// Function to calculate PID output
float calculatePID(float error, float *integral, float *previousError) {
  if (int(error) == 0) {
    return 0;
  }
  // Proportional term
  float proportional = KpA * error;

  // Integral term
  *integral += error;
  float integralTerm = KiA * (*integral);

  // Derivative term
  float derivative = KdA * (error - *previousError);

  // Update previous error
  *previousError = error;

  // Combine terms
  return proportional + integralTerm + derivative;
}
