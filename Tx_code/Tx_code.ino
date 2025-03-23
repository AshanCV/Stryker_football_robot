/* Stryker - Transmitter 
   24.03.2025
   Programme for Radio controlled car with 4 mecanum wheels.
*/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <I2Cdev.h>
#include <Wire.h>

#define Rx A0
#define Ry A1
//#define swR 8
#define Lx A4
#define Ly A5
//#define swL 7
#define Rbutton1 2
#define Rbutton2 3
#define Lbutton1 4
#define Lbutton2 5
#define shootButton 6
//#define sw_v1 A3
//define sw_v2 A2

int data[6];
int lx; int ly;
int rx; int ry;

RF24 radio(9, 10); //CE, CSN //MSOI-11, MISO-12, CLK-13

const byte password[6] = "00001"; //*enter a security code //


void setup() {

pinMode(Rbutton1,INPUT);
pinMode(Rbutton2,INPUT);
pinMode(Lbutton1,INPUT);
pinMode(Lbutton2,INPUT);
pinMode(shootButton,INPUT);
//pinMode(swL,INPUT);
//pinMode(swR,INPUT);

 
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

data[4] = 1;
data[4] = data[4] * ((ButtonR1)? 2 : 1 );
data[4] = data[4] * ((ButtonR2)? 3 : 1 );
data[4] = data[4] * ((ButtonL1)? 5 : 1 );
data[4] = data[4] * ((ButtonL2)? 7 : 1 );

 shoot = digitalRead(shootButton);
 data[5] = shoot;
   
 radio.write(data, sizeof(data));
Serial.print(data[0]); Serial.print("    ");Serial.print(data[1]);Serial.print("    ");
Serial.print(data[2]); Serial.print("    ");Serial.print(data[3]);Serial.print("    ");
Serial.println(data[4]);
delay(20);
 
}
