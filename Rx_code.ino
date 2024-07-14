//****************************************
/* Stryker - Reciever 
   14.07.2024
   Programme for Radio controlled car with 4 mecanum wheels.
*/
//****************************************

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo R_arm;
Servo L_arm;

int data[5];

RF24 radio(8, 7);  //CE, CSN

const byte password[6] = "00001"; //*enter a security code

const int M = 80;

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

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, password);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
}

void loop() {

//Serial.println("hello");

 while (radio.available()) {

    radio.read(data, sizeof(data));

     Serial.print(data[0]);Serial.print("    "); Serial.print(data[1]);Serial.print("    "); 
     Serial.print(data[2]);Serial.print("    "); Serial.print(data[3]);Serial.print("    ");
     Serial.print(data[4]);Serial.print("    ");


if (data[4]==1){
   R_arm.write(180);
}else if(data[4]==2 ){
   R_arm.write(0);
}else if(data[4]==3 ){
  L_arm.write(180);
}else if(data[4]==4){
  L_arm.write(0);
}else{
  //no move
}

/*
 * R_arm.write(180);   => Right top button
 *  R_arm.write(0);    => Right bottom button
 *   L_arm.write(180);  => Left bottom button
 *   L_arm.write(0);    => Left top button
 */

     

if (data[0] > -M && data[0] < M && data[1] > -M && data[1] < M && data[2] > -M && data[2] < M && data[3] > -M && data[3] < M) {
     stopMotors();
Serial.println("data recv- stop");
      
    }else if (data[0] > M && -M<data[1] && data[1]<M) {
      moveForward();
Serial.println("data recv- forw");

    }else if (data[0] < -M && -M<data[1] && data[1]<M) {
      moveBackward();
Serial.println("data recv- bacck");

    }else if (-M<data[0] && data[0]<M && data[1]< -M) {
    moveRight();
Serial.println("data recv- Right");

    }else if (-M<data[0] && data[0]<M && data[1]>M) {
      moveLeft();
Serial.println("data recv- Left");

    }else if (data[0]>M && data[1]< -M) {
     moveForwardRight();
Serial.println("data recv- R trn");

    }else if (data[0]>M && data[1]>M) {
     moveForwardLeft();
Serial.println("data recv- L trn");

    }else if (-M>data[0] && data[1]<-M) {
          moveBackwardRight();
Serial.println("R trun back");

    }else if (-M>data[0] && data[1]>M) {
      moveBackwardLeft();
Serial.println("L trun back");

    }else if ( data[3]>M) {
      rotateClockwise();
Serial.println("rotate CW");
    }else if (data[3]<-M) {
     rotateCounterclockwise();
Serial.println("rotate CCW");
    }


}

stopMotors();

/*
 moveForward();
delay(1000);
moveBackward();
delay(1000);
moveRight();
delay(1000);
moveLeft();
delay(1000);
moveForwardRight();
delay(1000);
moveForwardLeft();
delay(1000);
moveBackwardRight();
delay(1000);
moveBackwardLeft();
delay(1000);
rotateClockwise();
delay(1000);
rotateCounterclockwise();
delay(1000);

stopMotors();
delay(500);
*/

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

void moveForwardLeft() {
  digitalWrite(RFF, HIGH);
  digitalWrite(RFB, LOW);
  digitalWrite(RBF, LOW);
  digitalWrite(RBB, LOW);
  digitalWrite(LFF, LOW);
  digitalWrite(LFB, LOW);
  digitalWrite(LBF, HIGH);
  digitalWrite(LBB, LOW);
}

void moveForwardRight() {
  digitalWrite(RFF, LOW);
  digitalWrite(RFB, LOW);
  digitalWrite(RBF, HIGH);
  digitalWrite(RBB, LOW);
  digitalWrite(LFF, HIGH);
  digitalWrite(LFB, LOW);
  digitalWrite(LBF, LOW);
  digitalWrite(LBB, LOW);
}

void moveBackwardRight() {
  digitalWrite(RFF, LOW);
  digitalWrite(RFB, HIGH);
  digitalWrite(RBF, LOW);
  digitalWrite(RBB, LOW);
  digitalWrite(LFF, LOW);
  digitalWrite(LFB, LOW);
  digitalWrite(LBF, LOW);
  digitalWrite(LBB, HIGH);
}

void moveBackwardLeft() {
  digitalWrite(RFF, LOW);
  digitalWrite(RFB, LOW);
  digitalWrite(RBF, LOW);
  digitalWrite(RBB, HIGH);
  digitalWrite(LFF, LOW);
  digitalWrite(LFB, HIGH);
  digitalWrite(LBF, LOW);
  digitalWrite(LBB, LOW);
}

void rotateClockwise() {
  digitalWrite(RFF, HIGH);
  digitalWrite(RFB, LOW);
  digitalWrite(RBF, HIGH);
  digitalWrite(RBB, LOW);
  digitalWrite(LFF, LOW);
  digitalWrite(LFB, HIGH);
  digitalWrite(LBF, LOW);
  digitalWrite(LBB, HIGH);
}

void rotateCounterclockwise() {
  digitalWrite(RFF, LOW);
  digitalWrite(RFB, HIGH);
  digitalWrite(RBF, LOW);
  digitalWrite(RBB, HIGH);
  digitalWrite(LFF, HIGH);
  digitalWrite(LFB, LOW);
  digitalWrite(LBF, HIGH);
  digitalWrite(LBB, LOW);
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
