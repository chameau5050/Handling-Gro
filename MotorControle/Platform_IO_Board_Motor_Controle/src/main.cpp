#ifndef UNIT_TEST

#include <Arduino.h>
#include <ArduinoJson.h>

#include "Comm/SerialComm.h"
#include "Comm/ControlMessage.h"
#include "Comm/MessageIO.h"

#include "DriveManager.h"
#include "StepperJoin.h"

//#define BAUD 9600 
#define BAUD 115200 

MessageIO IO;
SerialComm SC(&Serial);

void setup() {
  Serial.begin(BAUD);
  IO.addDevice(&SC);
}

void loop() {

  // ControlMessage* msg = IO.readMessage(0);
  
  // if(msg != 0)
  // {
  //   ControlMessage responce(msg->getType()+1, msg->getPayLoadSize(), msg->getPayload());
  //   IO.sendMessage(0,responce);
  //   delete msg;
  // }else
  // {
  //   //auto responce = ControlMessage(-1);
  //   //IO.sendMessage(0,responce);
  // }

  // TEST #1
  delay(5000);
  Serial.println("debut de l essaie du test #1");

  DriveManager driveManager; 
  //StepperJoin stepperjoin(0,2810,3,0,0);
  StepperJoin* stepperjoin = new StepperJoin(0,28100,3,0,0);

  driveManager.addJoin(stepperjoin);
  //TestJoinDevice* testjoin = new TestJoinDevice(6000,281000,3,0,0);
  //driveManager.addJoin(testjoin);
  
  Serial.println("Initialisation devrait etre completer, lumiere allumer");  
  delay(5000);

  Vector <int> array_position;
  array_position.add(2048);
  driveManager.goToPosition(array_position);
  Serial.println("Fin de l essaie");

  delay(5000);


  // //TEST #2: FONCTIONELLE!!!
  // delay(5000);
  // Serial.println("debut de l essaie");

  // StepperJoin stepperjoin(0,28800,42,0,0);
  // delay(7000);
  // Serial.println("Initialisation devrait etre completer, lumiere allumer");  
  // delay(5000);

  // stepperjoin.goTo(1000);// a vérifier car je pense qu'il fait juste 1000 tour??
  // Serial.println("Fin de l essaie");

  // delay(5000);
  
  // put your main code here, to run repeatedly:
}

#endif