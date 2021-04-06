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

  ControlMessage* msg = IO.readMessage(0);
  
  if(msg != 0)
  {
    ControlMessage responce(msg->getType()+1, msg->getPayLoadSize(), msg->getPayload());
    IO.sendMessage(0,responce);
    delete msg;
  }else
  {
    //auto responce = ControlMessage(-1);
    //IO.sendMessage(0,responce);
  }
  
  // put your main code here, to run repeatedly:
}

#endif