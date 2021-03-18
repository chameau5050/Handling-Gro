#ifndef UNIT_TEST

#include <Arduino.h>
#include <ArduinoJson.h>
#include <String.h>
#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define STRING_BUF_NUM 64
String cmd[STRING_BUF_NUM];

#include "SerialComm.h"
#include "ControlMessage.h"
#include "MessageIO.h"

#define BAUD 57600 

MessageIO IO;
SerialComm SC(&Serial);

// Definition des defines pour la communication
// Definition of define for communication
#define SET_LIMITES_INDEX 1
#define SET_HOME_POSITION_INDEX 3
#define SET_REFERENCE_POSITION_INDEX 5
#define GO_TO_POSITION_INDEX 7
#define GO_TO_HOME_INDEX 9
#define RETURN_LIMITES_INDEX 11
#define RETURN_HOME_POSITION_INDEX 13
#define RETURN_REFERENCE_POSITION_INDEX 15
#define RETURN_ACTUAL_POSITION_INDEX 17

DynamixelWorkbench dxl_wb;
uint8_t get_id[16];
uint8_t scan_cnt = 0;
uint8_t ping_cnt = 0;

bool isAvailableID(uint8_t id);
void split(String data, char separator, String* temp);
void printInst();


// Definition des defines pour les parametres des moteurs
// Definition of defines for engine parameters
#define NbrMotor 4
int defineID[NbrMotor]= {1,2,3,4};

int LimiteMax[NbrMotor] = {81921,8193,8193,8193};
int LimiteMin[NbrMotor] = {0,0,0,0};
int Home[NbrMotor]= {0,0,0,0}; 


// Definition de la classe moteur pour les moteurs dynamixel
// Definition of the motor class for dynamixel motors
class motor
{
  public:
  motor(int id)
  {
    int result;
    int result1;
    int result3;
    int actualPosition;
    int goal = 100;
    int32_t data;
    uint16_t model_number;
    const char *log;
    int baud = 57600;
    this->id = id;
    result = dxl_wb.init(DEVICE_NAME, baud);
    result = dxl_wb.ping((int8_t)id, &model_number, &log);
    
//Code for setting motors in different modes   
//Code pour le réglage des moteurs dans differents modes
//Essaie #1
    //result = dxl_wb.jointMode(id, 0, 0, &log);
//Essaie #2
    //result = dxl_wb.setMultiTurnControlMode((int8_t)id,  &log);
//Essaie #3
   //result1 = dxl_wb.setExtendedPositionControlMode((int8_t)id,  &log);
//Essaie #4   
    result = dxl_wb.currentBasedPositionMode((int8_t)id, 100, &log);
    result3 = dxl_wb.ledOn((uint8_t) id, &log);
    if(result3==1)
    {
      Serial.println("");
      Serial.print("Light On, motor ");
      Serial.print(id);
      Serial.print(" ready");
      Serial.println("");
    }
    else
    {
      Serial.println("");
      Serial.print("Light Off, motor ");
      Serial.print(id);
      Serial.print(" not ready");
      Serial.println("");
    }
  };
  
  int id;
  const char *log;
  
  void gotoa(int32_t pos)
  {
    dxl_wb.goalPosition((int8_t)id, (int32_t)pos, &log);
  };

  void setHomingOffset(int32_t pos)
  {
    Serial.println("Fonction not working at 100%: Error");
    bool resultss = false;
    resultss =  dxl_wb.itemWrite(id, "Homing_Offset", pos, &log);
    if (resultss == false)
    {
      Serial.println(log);
      Serial.println("Failed to set Homing_Offset");
    }
    else
    {
      Serial.print("Succeed to set Homing_Offset");
    }
  }
  
  int32_t GetPosition1()
  {
    bool results;
    int32_t get_data = 0;
    results = dxl_wb.itemRead(id, "Present_Position", &get_data, &log);
    if (results == false)
    {
      Serial.println(log);
      Serial.println("Failed to get present position");
    }
    else
    {
      Serial.print("Succeed to get present position(value : ");
      Serial.print(get_data);
      Serial.println(")");
    }
    return get_data;
  }

  int32_t GetReferencePosition1()
  {
    bool results;
    int32_t get_data = 0;
    results = dxl_wb.itemRead(id, "Homing_Offset", &get_data, &log);
    if (results == false)
    {
      Serial.println(log);
      Serial.println("Failed to get Homing_Offset position");
    }
    else
    {
      Serial.print("Succeed to get Homing_Offset position(value : ");
      Serial.print(get_data);
      Serial.println(")");
    }
    return get_data;
  }
 };


motor* Reference[4];

void setup() 
{
  Serial.begin(BAUD);
  IO.addDevice(&SC);
  delay(10);
}

void loop() 
{
  ControlMessage* msg = IO.readMessage(0);

  for (int m=0;m<NbrMotor;m++)
  {
    if (Reference[m] == 0)
    {
      Reference[m] = new motor(defineID[m]);
    }
  }
      
  if(msg != 0)
  {
    for (int i=0;i<msg->getPayLoadSize();i++)
    {
//CODE POUR INITIALISER LES MOTEURS
//CODE TO INITIALIZE THE MOTORS      
      if (Reference[i] == 0)
      {
        Reference[i] = new motor(defineID[i]);
        Serial.println("Motor");
        Serial.println(i);
        Serial.println("activer");
      }

//CODE POUR LES DIFFERENTES OPERATIONS A EFFECTUER PAR LE MOTEURS
//CODE FOR THE DIFFERENT OPERATIONS TO BE CARRIED OUT BY THE ENGINES
      
      //Set position = 7 
      if (msg->getType()== GO_TO_POSITION_INDEX)
      {
        if (msg->getPayload()[i] >= LimiteMax[i])
        {
          msg->getPayload()[i] = LimiteMax[i];
        }
        Reference[i]->gotoa(msg->getPayload()[i]);
      }

      //Set limite = 1
      else if (msg->getType()== SET_LIMITES_INDEX)
      {
        LimiteMax[i] = msg->getPayload()[i];
      }
  
      //Set Home Position = 3
      else if (msg->getType()== SET_HOME_POSITION_INDEX)
      {
        Home[i] = msg->getPayload()[i];
      } 
  
      //Set reference position = 5 
      else if (msg->getType()== SET_REFERENCE_POSITION_INDEX)
      {
        if (msg->getPayload()[i] == 1)
        {
          delete Reference[i];
          Reference[i] = new motor(defineID[i]);
        }
          Reference[i]->setHomingOffset(msg->getPayload()[i]); 
          Serial.println("Fonction not working at 100%: Error");     
      }
              
      //Go to HOME = 9
      else if (msg->getType()== GO_TO_HOME_INDEX)
      {
        Home[i] = msg->getPayload()[i];
        Reference[i]->gotoa(Home[i]);
      }
//CODE POUR RENVOYER LINFORMATION
//CODE TO RETURN INFORMATION

      //return limites = 11
      else if (msg->getType()== RETURN_LIMITES_INDEX)
      {
        msg->getPayload()[i] = LimiteMax[i];
      }
  
      //return HOME position = 13
      else if (msg->getType()== RETURN_HOME_POSITION_INDEX)
      {
        msg->getPayload()[i] = Home[i];
      }

      //return reference position = 15
      else if (msg->getType()== RETURN_REFERENCE_POSITION_INDEX)
      {
        Serial.println("Fonction not complete: Error");
        msg->getPayload()[i] = (Reference[i])->GetReferencePosition1();
      }

      //return actual position = 17
      else if (msg->getType()== RETURN_ACTUAL_POSITION_INDEX)
      {
         msg->getPayload()[i] = (Reference[i])->GetPosition1();
      }
    }
    delay(1000);
    ControlMessage responce(msg->getType()+1, msg->getPayLoadSize(), msg->getPayload());
    IO.sendMessage(0,responce);
    delete msg;
  }
  else
  {
    //auto responce = ControlMessage(-1);
    //IO.sendMessage(0,responce);
  }
  delay(100);
  
}
#endif

/*
 * COMMANDE DE TEST 
{​​"type":7,"PLS":1,"data":[19389]}​​
{​​"type":7,"PLS":1,"data":[19389]}​​
{​​"type":7,"PLS":3,"data":[10389,5000,0]}​​
{​​"type":11,"PLS":3,"data":[0,0,0]}​​
{​​"type":17,"PLS":3,"data":[0,0,0]}​​

{​​"type":17,"PLS":3,"data":[0,0,0]}​​

{​​"type":17,"PLS":2,"data":[0,0]}​​
{​​"type":3,"PLS":3,"data":[50,500,1500]}​​

{​​"type":5,"PLS":3,"data":[0,1,0]}​​
*/
