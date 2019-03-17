/*
  KhalifNovation
  Speed Encoder Reader

  Created:  3/10/2019 6:08:55 PM
  Author:   syed93uthman
  Hardware Target : Arduino Compatible Board

  This Encoder library only available for External Intterupt pin only.
  For Uno : 2,3

*/

#include "KT_ENCODER.h"

KT_ENCODER MyEncoder(2, 3); //Initial (Left Encoder=2, Right Encoder=3)
//Motor Pin's Initialization

int RIGHT_En=10; //Speed Control
int RIGHT_In1=9; //Rotation Control
int RIGHT_In2=8; 
int LEFT_In3=12; //Speed Control
int LEFT_In4=13; //Rotation Control
int LEFT_En=11;

int pin[] = { 
  RIGHT_En,
  RIGHT_In1,
  RIGHT_In2,
  LEFT_En,
  LEFT_In3,
  LEFT_In4
};

void setup() {
  Serial.begin(9600);

  MyEncoder.begin(CHANGE); //Set external Interrupt to CHANGE Mode
  
  for (int i = 0; i <sizeof(pin) ;i++) {
    pinMode(pin[i],OUTPUT);
  }
  
  motor(255,0,false,true); //Set Motor Speed and direction
}

void loop() {
  
  if (MyEncoder.update(100)) { //Read Inttrupt every 100ms
    unsigned int left = MyEncoder.getSpeed(LEFT, false); //get left speed
    unsigned int right = MyEncoder.getSpeed(RIGHT, true); //get right speed, rise DoneRead flag

    printSpeed(left,right); //print left and right speed to serial
  }
}

void motor(int Lspeed,int Rspeed,bool Ldir,bool Rdir) {
  analogWrite(LEFT_En,Lspeed);
  analogWrite(RIGHT_En,Rspeed);

  digitalWrite(LEFT_In3,Ldir);
  digitalWrite(LEFT_In4,!Ldir);

  digitalWrite(RIGHT_In1, Rdir);
  digitalWrite(RIGHT_In2, !Rdir);

}

void printSpeed(int Lspeed, int Rspeed) {
  Serial.print("LEFT : ");
  Serial.print(Lspeed);
  Serial.print("  \t");
  Serial.print("RIGHT : ");
  Serial.println(Rspeed);
  Serial.print("DIF : ");
  Serial.println(-Lspeed + Rspeed);
}

