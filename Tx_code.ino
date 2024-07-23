/* Stryker - Transmitter 
   14.07.2024
   Programme for Radio controlled car with 4 mecanum wheels.
*/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <I2Cdev.h>
#include <Wire.h>

#define Rx A1
#define Ry A0
#define Lx A3
#define Ly A2
#define Rbutton1 7
#define Rbutton2 6
#define Lbutton1 A5
#define Lbutton2 5
#define shootButton A4

int data[6];
int lx; int ly;
int rx; int ry;

RF24 radio(9, 10); //CE, CSN //MSOI-11, MISO-12, CLK-13

const byte password[6] = "00001"; //*enter a security code //


void setup() {
 
Serial.begin(9600);
  Wire.begin();

  radio.begin();
  radio.openWritingPipe(password);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  
}

void loop() {

int slx=0;
int sly=0;
int srx=0;
int sry=0;
bool ButtonR1 = false;
bool ButtonR2 = false;
bool ButtonL1 = false;
bool ButtonL2 = false;
bool shoot = false;
   
for(int i=0; i<10; i++){
  lx = analogRead(Lx);
  ly = analogRead(Ly);
  rx = analogRead(Rx);
  ry = analogRead(Ry);
  
  slx=slx+lx;
  sly=sly+ly;
  srx=srx+rx;
  sry=sry+ry;
  
}
data[0]=srx/10;
data[1]=sry/10;
data[2]=slx/10;
data[3]=sly/10;

data[0] = map(data[0], 0,1024, 255, -255); 
data[1] = map(data[1], 0, 1024, 255, -255);
data[2] = map(data[2], 0,1024, 255, -255); 
data[3] = map(data[3], 0, 1024, 255, -255);

if(data[0]>255){
  data[0]=255;
}
if(data[1]>255){
  data[1]=255;
}
if(data[2]>255){
  data[2]=255;
}
if(data[3]>255){
  data[3]=255;
}

 ButtonR1 = digitalRead(Rbutton1);
 ButtonR2 = digitalRead(Rbutton2);
 ButtonL1 = digitalRead(Lbutton1);
 ButtonL2 = digitalRead(Lbutton2);

data[4] = 0;
data[4] += (ButtonR1)? 1 : 0 ;
data[4] += (ButtonR2)? 2 : 0 ;
data[4] += (ButtonL1)? 3 : 0 ;
data[4] += (ButtonL2)? 4 : 0 ;

 shoot = digitalRead(shootButton);
 data[5] = shoot;
   
 radio.write(data, sizeof(data));
Serial.print(data[0]); Serial.print("    ");Serial.print(data[1]);Serial.print("    ");
Serial.print(data[2]); Serial.print("    ");Serial.print(data[3]);Serial.print("    ");
Serial.println(data[4]);
delay(20);
 
}
