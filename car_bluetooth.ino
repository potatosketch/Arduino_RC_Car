#include <SoftwareSerial.h>
#include <Wire.h>
int trig = 13;
int echo = 12;
int in1 = 3;
int in2 = 5;
int in3 = 6;
int in4 = 9;
SoftwareSerial I2CBT(10,11); //定義Arduino PIN10及PIN11分別為RX及TX腳位
//請注意Arduino的TX要接藍牙模組的RX, 反之亦然

void setup() {
  Serial.begin(9600);
  I2CBT.begin(9600);//bluetooth baud rate  
  pinMode(trig, OUTPUT);   
  pinMode(echo, INPUT);
  pinMode(in1, OUTPUT);   
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  byte cmmd[20];
  int insize;
  while(1){
    //read message from bluetooth
    if ((insize=(I2CBT.available()))>0){
      Serial.print("input size = "); 
      Serial.println(insize);
      for (int i=0; i<insize; i++){
        Serial.print(cmmd[i]=char(I2CBT.read()));
        Serial.print("\n"); 
      }
    }
    //根據所收到訊號執行對應動作  
    switch (cmmd[0]) {
    case 97:      
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      break;  

    case 98:
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      break;

      case 99:
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      break;

      case 100:
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW); 
      break;

      case 115:
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW); 
      break;

      case 116:
      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);
      delayMicroseconds(5);
      digitalWrite(trig, LOW);
      int duration = pulseIn(echo, HIGH);
      int cm = duration / 29 / 2;
      if(cm>50){
         digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
        } else {
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);    
          }
      break; 
      
      
    } //Switch
  } //while
}
