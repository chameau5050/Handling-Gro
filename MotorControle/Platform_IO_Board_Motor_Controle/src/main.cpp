#ifndef UNIT_TEST

#include <Arduino.h>
#include <ArduinoJson.h>

#include "Comm/SerialComm.h"
#include "Comm/ControlMessage.h"
#include "Comm/MessageIO.h"
#include "StateManager.h"
#include "DriveManager.h"
#include "Pixel_Join.h"

//#define BAUD 9600 
#define BAUD 115200 

#define NbrMotor 5
#define NbrMotorDynamixel 4
#define NbrMotorStepper 1
#define NbrMotor 1

MessageIO IO;
SerialComm SC(&Serial);
StateManager* statemanager;
DriveManager* drivemanager;

void setup() 
{
  Serial.begin(BAUD);
  IO.addDevice(&SC);

//Définitions des différents joins selon les moteurs!
  Pixel_Join* join1 = new Pixel_Join(0,228100,0,0,0);
  drivemanager = new DriveManager();
  drivemanager->addJoin(join1);

  Pixel_Join* join2 = new Pixel_Join(0,228100,0,0,0);
  drivemanager->addJoin(join2);

  statemanager = new StateManager(drivemanager);

}

void loop() {

  ControlMessage* msg = IO.readMessage(0);
    
  if(msg != 0)
  {
    statemanager->updateState(msg);

    ControlMessage responce(msg->getType()+1, msg->getPayLoadSize(), msg->getPayload());
    IO.sendMessage(0,responce);
    delete msg;
  }else
  {
    //auto responce = ControlMessage(-1);
    //IO.sendMessage(0,responce);
  }
  delay(1000);
  
  // put your main code here, to run repeatedly:
}

#endif