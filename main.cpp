#include "SD.h"
#define SD_ChipSelectPin 4
#include "TMRpcm.h"
#include "SPI.h"
#include <Arduino.h>

TMRpcm tmrpcm;

int motionStatus = 0;
int pirState = LOW;
int audioFile;

void setup(){
  pinMode(2, INPUT);
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  if(!SD.begin(SD_ChipSelectPin)){
    Serial.println("SD fail");
    return;
  }

  tmrpcm.setVolume(6);


}


void loop(){
  motionStatus = digitalRead(2);
  if(motionStatus == HIGH){
    if(pirState == LOW){
      audioFile = random(1, 12);
      String fileName = String(audioFile) + ".wav";
      tmrpcm.play(fileName.c_str());

      pirState = HIGH;
    }
  } else {
    if(pirState == HIGH){
      pirState = LOW;
    }
  }
  
}
