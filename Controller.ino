// Define joystick pins
int joy1X = A0;
int joy1Y = A1;
int joy2X = A2;

//motor driver pins
#define RFF 2
#define RFB 3
#define RBF 4
#define RBB 5
#define LFF 6
#define LFB 7
#define LBF 8
#define LBB 9

int xValue1, yValue1, xValue2;

// Center values 
const int xCenter = 512;
const int yCenter = 512;
const int tolerance = 50;  // Deadzone tolerance

void setup() {
  Serial.begin(9600);

  // Initialize motor pins as outputs
  pinMode(RFF, OUTPUT);
  pinMode(RFB, OUTPUT);
  pinMode(RBF, OUTPUT);
  pinMode(RBB, OUTPUT);
  pinMode(LFF, OUTPUT);
  pinMode(LFB, OUTPUT);
  pinMode(LBF, OUTPUT);
  pinMode(LBB, OUTPUT);
}

void loop() {
  // Read joystick values
  xValue1 = analogRead(joy1X);
  yValue1 = analogRead(joy1Y);
  xValue2 = analogRead(joy2X);

  // Calculate deviation from center for joystick 1
  int xDeviation1 = xValue1 - xCenter;
  int yDeviation1 = yValue1 - yCenter;

  // Apply deadzone for joystick 1
  if (abs(xDeviation1) < tolerance) xDeviation1 = 0;
  if (abs(yDeviation1) < tolerance) yDeviation1 = 0;

  // Calculate deviation from center for joystick 2
  int xDeviation2 = xValue2 - xCenter;

  // Apply deadzone for joystick 2
  if (abs(xDeviation2) < tolerance) xDeviation2 = 0;

  // Control motors based on joystick 1 values
  if (yDeviation1 > 0) {  // Forward
    moveForward();
  } else if (yDeviation1 < 0) {  // Backward
    moveBackward();
  } else if (xDeviation1 > 0) {  // Slide Right
    moveRight();
  } else if (xDeviation1 < 0) {  // Slide Left
    moveLeft();
  } else if (xDeviation1 > 0 && yDeviation1 > 0) {  // Forward-Right diagonal
    moveForwardRight();
  } else if (xDeviation1 < 0 && yDeviation1 > 0) {  // Forward-Left diagonal
    moveForwardLeft();
  } else if (xDeviation1 > 0 && yDeviation1 < 0) {  // Backward-Right diagonal
    moveBackwardRight();
  } else if (xDeviation1 < 0 && yDeviation1 < 0) {  // Backward-Left diagonal
    moveBackwardLeft();
  } else {
    stopMotors();
  }

  // Control motors based on joystick 2 values (rotation)
  if (xDeviation2 > 0) {  // Rotate Clockwise
    rotateClockwise();
  } else if (xDeviation2 < 0) {  // Rotate Counterclockwise
    rotateCounterclockwise();
  }

  delay(100);  // Short delay for stability
}

void moveForward() {
  digitalWrite(RFF, HIGH);
  digitalWrite(RFB, LOW);
  digitalWrite(RBF, HIGH);
  digitalWrite(RBB, LOW);
  digitalWrite(LFF, HIGH);
  digitalWrite(LFB, LOW);
  digitalWrite(LBF, HIGH);
  digitalWrite(LBB, LOW);
}

void moveBackward() {
  digitalWrite(RFF, LOW);
  digitalWrite(RFB, HIGH);
  digitalWrite(RBF, LOW);
  digitalWrite(RBB, HIGH);
  digitalWrite(LFF, LOW);
  digitalWrite(LFB, HIGH);
  digitalWrite(LBF, LOW);
  digitalWrite(LBB, HIGH);
}

void moveRight() {
  digitalWrite(RFF, LOW);
  digitalWrite(RFB, HIGH);
  digitalWrite(RBF, HIGH);
  digitalWrite(RBB, LOW);
  digitalWrite(LFF, HIGH);
  digitalWrite(LFB, LOW);
  digitalWrite(LBF, LOW);
  digitalWrite(LBB, HIGH);
}

void moveLeft() {
  digitalWrite(RFF, HIGH);
  digitalWrite(RFB, LOW);
  digitalWrite(RBF, LOW);
  digitalWrite(RBB, HIGH);
  digitalWrite(LFF, LOW);
  digitalWrite(LFB, HIGH);
  digitalWrite(LBF, HIGH);
  digitalWrite(LBB, LOW);
}

void moveForwardRight() {
  digitalWrite(RFF, HIGH);
  digitalWrite(RFB, LOW);
  digitalWrite(RBF, HIGH);
  digitalWrite(RBB, LOW);
  digitalWrite(LFF, LOW);
  digitalWrite(LFB, HIGH);
  digitalWrite(LBF, LOW);
  digitalWrite(LBB, HIGH);
}

void moveForwardLeft() {
  digitalWrite(RFF, LOW);
  digitalWrite(RFB, HIGH);
  digitalWrite(RBF, LOW);
  digitalWrite(RBB, HIGH);
  digitalWrite(LFF, HIGH);
  digitalWrite(LFB, LOW);
  digitalWrite(LBF, HIGH);
  digitalWrite(LBB, LOW);
}

void moveBackwardRight() {
  digitalWrite(RFF, LOW);
  digitalWrite(RFB, HIGH);
  digitalWrite(RBF, LOW);
  digitalWrite(RBB, HIGH);
  digitalWrite(LFF, HIGH);
  digitalWrite(LFB, LOW);
  digitalWrite(LBF, LOW);
  digitalWrite(LBB, HIGH);
}

void moveBackwardLeft() {
  digitalWrite(RFF, HIGH);
  digitalWrite(RFB, LOW);
  digitalWrite(RBF, HIGH);
  digitalWrite(RBB, LOW);
  digitalWrite(LFF, LOW);
  digitalWrite(LFB, HIGH);
  digitalWrite(LBF, HIGH);
  digitalWrite(LBB, LOW);
}

void rotateClockwise() {
  digitalWrite(RFF, HIGH);
  digitalWrite(RFB, LOW);
  digitalWrite(RBF, LOW);
  digitalWrite(RBB, HIGH);
  digitalWrite(LFF, LOW);
  digitalWrite(LFB, HIGH);
  digitalWrite(LBF, HIGH);
  digitalWrite(LBB, LOW);
}

void rotateCounterclockwise() {
  digitalWrite(RFF, LOW);
  digitalWrite(RFB, HIGH);
  digitalWrite(RBF, HIGH);
  digitalWrite(RBB, LOW);
  digitalWrite(LFF, HIGH);
  digitalWrite(LFB, LOW);
  digitalWrite(LBF, LOW);
  digitalWrite(LBB, HIGH);
}

void stopMotors() {
  digitalWrite(RFF, LOW);
  digitalWrite(RFB, LOW);
  digitalWrite(RBF, LOW);
  digitalWrite(RBB, LOW);
  digitalWrite(LFF, LOW);
  digitalWrite(LFB, LOW);
  digitalWrite(LBF, LOW);
  digitalWrite(LBB, LOW);
}
