//****************************************
/* Stryker - Receiver 
   14.07.2024
   Programme for Radio controlled car with 4 mecanum wheels.
*/
//****************************************

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <SoftPWM.h>

Servo R_arm;
Servo L_arm;

int data[5];

RF24 radio(8, 7);  // CE, CSN

const byte password[6] = "00001"; //*enter a security code

const int M = 60;

#define RFF 2
#define RFB 3
#define RBF 5
#define RBB 4
#define LFF A0
#define LFB 6
#define LBF A1
#define LBB A2
#define R_arm_pin 9
#define L_arm_pin 10

void setup() {
  pinMode(RFF, OUTPUT);
  pinMode(RFB, OUTPUT);
  pinMode(RBF, OUTPUT);
  pinMode(RBB, OUTPUT);
  pinMode(LFF, OUTPUT);
  pinMode(LFB, OUTPUT);
  pinMode(LBF, OUTPUT);
  pinMode(LBB, OUTPUT);
  digitalWrite(RFF, LOW);
  digitalWrite(RFB, LOW);
  digitalWrite(RBF, LOW);
  digitalWrite(RBB, LOW);
  digitalWrite(LFF, LOW);
  digitalWrite(LFB, LOW);
  digitalWrite(LBF, LOW);
  digitalWrite(LBB, LOW);

  R_arm.attach(R_arm_pin);
  L_arm.attach(L_arm_pin);
  R_arm.write(180);
  L_arm.write(0);

  SoftPWMBegin();
  SoftPWMSet(RFF, 0);
  SoftPWMSet(RFB, 0);
  SoftPWMSet(RBB, 0);
  SoftPWMSet(LFF, 0);
  SoftPWMSet(LFB, 0);
  SoftPWMSet(LBF, 0);
  SoftPWMSet(LBB, 0);

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, password);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  while (radio.available()) {
    radio.read(data, sizeof(data));

    // Serial.print(data[0]); Serial.print("    "); Serial.print(data[1]); Serial.print("    "); 
    // Serial.print(data[2]); Serial.print("    "); Serial.print(data[3]); Serial.print("    ");
    // Serial.print(data[4]); Serial.print("    ");

    int ySpeed = abs(data[0])*(1.0);
    int xSpeed = abs(data[1])*(1.0);
    int rotationSpeed = abs(data[3])*(0.8);

     int hasB1 = data[4] % 2;
     int hasB2 = data[4] % 3;
     int hasB3 = data[4] % 5;
     int hasB4 = data[4] % 7;
     
    if (B1 == 0) {
      R_arm.write(180);
    } else if (B2 == 0) {
      R_arm.write(0);
    } 
     
   if (B3 == 0) {
      L_arm.write(180);
    } else if (B4 == 0) {
      L_arm.write(0);
    }

    if (abs(data[0]) < M && abs(data[1]) < M && abs(data[2]) < M && abs(data[3]) < M) {
      stopMotors();
      //Serial.println("data recv- stop");
    } else if (data[0] > M && abs(data[1]) < M) {
      moveForward(ySpeed);
      //Serial.println("data recv- forw");
    } else if (data[0] < -M && abs(data[1]) < M) {
      moveBackward(ySpeed);
      //Serial.println("data recv- bacck");
    } else if (abs(data[0]) < M && data[1] < -M) {
      moveRight(xSpeed);
      //Serial.println("data recv- Right");
    } else if (abs(data[0]) < M && data[1] > M) {
      moveLeft(xSpeed);
      //Serial.println("data recv- Left");
    } else if (data[0] > M && data[1] < -M) {
      moveForwardRight(xSpeed, ySpeed);
      //Serial.println("data recv- R trn");
    } else if (data[0] > M && data[1] > M) {
      moveForwardLeft(xSpeed, ySpeed);
      //Serial.println("data recv- L trn");
    } else if (data[0] < -M && data[1] < -M) {
      moveBackwardRight(xSpeed, ySpeed);
      //Serial.println("R trun back");
    } else if (data[0] < -M && data[1] > M) {
      moveBackwardLeft(xSpeed, ySpeed);
      //Serial.println("L trun back");
    } else if (data[3] > M) {
      rotateClockwise(rotationSpeed);
      //Serial.println("rotate CW");
    } else if (data[3] < -M) {
      rotateCounterclockwise(rotationSpeed);
      //Serial.println("rotate CCW");
    }
  }
}

void moveForward(int speed) {
  SoftPWMSet(RFF, speed);
  SoftPWMSet(RFB, 0);
  SoftPWMSet(RBF, speed);
  SoftPWMSet(RBB, 0);
  SoftPWMSet(LFF, speed);
  SoftPWMSet(LFB, 0);
  SoftPWMSet(LBF, speed);
  SoftPWMSet(LBB, 0);
}

void moveBackward(int speed) {
  SoftPWMSet(RFF, 0);
  SoftPWMSet(RFB, speed);
  SoftPWMSet(RBF, 0);
  SoftPWMSet(RBB, speed);
  SoftPWMSet(LFF, 0);
  SoftPWMSet(LFB, speed);
  SoftPWMSet(LBF, 0);
  SoftPWMSet(LBB, speed);
}

void moveRight(int speed) {
  SoftPWMSet(RFF, 0);
  SoftPWMSet(RFB, speed);
  SoftPWMSet(RBF, speed);
  SoftPWMSet(RBB, 0);
  SoftPWMSet(LFF, speed);
  SoftPWMSet(LFB, 0);
  SoftPWMSet(LBF, 0);
  SoftPWMSet(LBB, speed);
}

void moveLeft(int speed) {
  SoftPWMSet(RFF, speed);
  SoftPWMSet(RFB, 0);
  SoftPWMSet(RBF, 0);
  SoftPWMSet(RBB, speed);
  SoftPWMSet(LFF, 0);
  SoftPWMSet(LFB, speed);
  SoftPWMSet(LBF, speed);
  SoftPWMSet(LBB, 0);
}

void moveForwardLeft(int xSpeed, int ySpeed) {
  int speed = (xSpeed + ySpeed) / 2;
  SoftPWMSet(RFF, speed);
  SoftPWMSet(RFB, 0);
  SoftPWMSet(RBF, 0);
  SoftPWMSet(RBB, 0);
  SoftPWMSet(LFF, 0);
  SoftPWMSet(LFB, 0);
  SoftPWMSet(LBF, speed);
  SoftPWMSet(LBB, 0);
}

void moveForwardRight(int xSpeed, int ySpeed) {
  int speed = (xSpeed + ySpeed) / 2;
  SoftPWMSet(RFF, 0);
  SoftPWMSet(RFB, 0);
  SoftPWMSet(RBF, speed);
  SoftPWMSet(RBB, 0);
  SoftPWMSet(LFF, speed);
  SoftPWMSet(LFB, 0);
  SoftPWMSet(LBF, 0);
  SoftPWMSet(LBB, 0);
}

void moveBackwardRight(int xSpeed, int ySpeed) {
  int speed = (xSpeed + ySpeed) / 2;
  SoftPWMSet(RFF, 0);
  SoftPWMSet(RFB, speed);
  SoftPWMSet(RBF, 0);
  SoftPWMSet(RBB, 0);
  SoftPWMSet(LFF, 0);
  SoftPWMSet(LFB, 0);
  SoftPWMSet(LBF, 0);
  SoftPWMSet(LBB, speed);
}

void moveBackwardLeft(int xSpeed, int ySpeed) {
  int speed = (xSpeed + ySpeed) / 2;
  SoftPWMSet(RFF, 0);
  SoftPWMSet(RFB, 0);
  SoftPWMSet(RBF, 0);
  SoftPWMSet(RBB, speed);
  SoftPWMSet(LFF, 0);
  SoftPWMSet(LFB, speed);
  SoftPWMSet(LBF, 0);
  SoftPWMSet(LBB, 0);
}

void rotateClockwise(int speed) {
  SoftPWMSet(RFF, speed);
  SoftPWMSet(RFB, 0);
  SoftPWMSet(RBF, speed);
  SoftPWMSet(RBB, 0);
  SoftPWMSet(LFF, 0);
  SoftPWMSet(LFB, speed);
  SoftPWMSet(LBF, 0);
  SoftPWMSet(LBB, speed);
}

void rotateCounterclockwise(int speed) {
  SoftPWMSet(RFF, 0);
  SoftPWMSet(RFB, speed);
  SoftPWMSet(RBF, 0);
  SoftPWMSet(RBB, speed);
  SoftPWMSet(LFF, speed);
  SoftPWMSet(LFB, 0);
  SoftPWMSet(LBF, speed);
  SoftPWMSet(LBB, 0);
}

void stopMotors() {
  SoftPWMSet(RFF, 0);
  SoftPWMSet(RFB, 0);
  SoftPWMSet(RBF, 0);
  SoftPWMSet(RBB, 0);
  SoftPWMSet(LFF, 0);
  SoftPWMSet(LFB, 0);
  SoftPWMSet(LBF, 0);
  SoftPWMSet(LBB, 0);
}
