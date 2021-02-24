#ifndef UNIT_TEST

#include <Arduino.h>
#include <ArduinoJson.h>
#include <String.h>

#include "SerialComm.h"
#include "ControlMessage.h"
#include "MessageIO.h"


//#define BAUD 9600 
//#define BAUD 115200 
#define BAUD 57600 

MessageIO IO;
SerialComm SC(&Serial);

#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define STRING_BUF_NUM 64
String cmd[STRING_BUF_NUM];

DynamixelWorkbench dxl_wb;
uint8_t get_id[16];
uint8_t scan_cnt = 0;
uint8_t ping_cnt = 0;

bool isAvailableID(uint8_t id);
void split(String data, char separator, String* temp);
void printInst();


//DÉFINITIONS DES VARIABLES GLOBALE POUR MON CODE
int LimiteMaxA = 81921;
int LimiteMaxB = 8193;
int LimiteMaxC = 8193;
/*
 * ON A PAS BESOIN DE LIMITE MINIMUM
int LimiteMinA = -100;
int LimiteMinB = -5;
int LimiteMinC = -5;
*/

int HomeA = 0;
int HomeB = 0;
int HomeC = 0;



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
    uint8_t index = 4; //pas mettre de chiffre mais bien le nom de la fonction??
    //uint8_t index = 101;
    //uint8_t index = EXTENDED_POSITION_CONTROL_MODE; a essayer
    delay(10000);
    result = dxl_wb.init(DEVICE_NAME, baud);
    result = dxl_wb.ping((int8_t)id, &model_number, &log);

    //result = dxl_wb.jointMode(id, 0, 0, &log);
//Essaie #1
    //result = dxl_wb.setMultiTurnControlMode((int8_t)id,  &log);
    //result = dxl_wb.setOperatingMode((int8_t)id, index, &log);
    if(!result)
      Serial.println("caca");
//Essaie #2
   //result1 = dxl_wb.setExtendedPositionControlMode((int8_t)id,  &log);
    if(!result1)
      Serial.println("pipi");
    else
      Serial.println(result1);
    result = dxl_wb.currentBasedPositionMode((int8_t)id, 100, &log);
    result3 = dxl_wb.ledOn((uint8_t) id, &log);
    if(!result1)
      Serial.println("fuck you lumiere");
   

    if(!result)
      Serial.println("fuck you le goal");
    delay(5000);
    dxl_wb.ledOff((int8_t)id, &log);
    delay(1000);
    dxl_wb.ledOn((int8_t)id, &log);

  };
  
  
  //DynamixelWorkbench dxl_wb;
  int id;
  const char *log;
  
  void gotoa(int32_t pos)
  {
    dxl_wb.goalPosition((int8_t)id, (int32_t)pos, &log);
  };

 };

motor* A;
motor* B;
motor* C;

void setup() {
 
  Serial.begin(BAUD);
  IO.addDevice(&SC);

  
}

/*
 * COMMANDE DE TEST 
{​​"type":7,"PLS":1,"data":[19389]}​​
{​​"type":7,"PLS":1,"data":[19389]}​​
{​​"type":7,"PLS":2,"data":[19389,5000]}​​
{​​"type":11,"PLS":3,"data":[0,0,0]}​​
*/



/*

DEFINITION DES TYPES QUE JE RECOIS

%%%%COMMANTE POUR ENVOYER DE LINFORMATION%%%%
->J'UTILISE JUSTE LES NOMBRES IMPAIRES ET JE RENVOIT QUAND JAI FINI LE NOMBRE PAIR
1:SETLIMITES->SET LA LIMITES POUR CHAQUE MOTEUR
2:RETOUR DE LA COMMANDE 1 RECU
3:SetHomePosition-> set la position home du robot: à faire ce soir
4:RETOUR DE LA COMMANDE 3 RECU
5:RESETpOSITION->RESET LA POSITION DANS LES ENCODEUR POUR LES REMETTRES A ZÉROS
6:RETOUR DE LA COMMANDE 5 RECU
7:SETPOSITION->FAIT DEPLACER LES MOTEURS À LEUR BONNES PLACES
8:RETOUR DE LA COMMANDE 7 RECU
9:GOTOHOME->ENVOIE LE ROBOT A SA POSITION DE REFERENCE
10:RETOUR DE LA COMMANDE 10 RECU

%%%%COMMANTE POUR RECEVOIR DE LINFORMATION%%%%
11:RENVOIT LA LIMITES DES JOINT DU ROBOT
12:RETOUR DE LA COMMANDE 11 RECU
13:RENVOIT LES POSITIONS DU HOME DU ROBOT
14:RETOUR DE LA COMMANDE 13 RECU
15:RENVOIT LES POSITIONS DE REFERENCE DU ROBOT, DONC SI LA COMMANDE 5 A FONCTIONNER = (0,...,0)
16:RETOUR DE LA COMMANDE 15 RECU
17:RENVOIT LES POSITIONS ACTUELLES DU ROBOT
18:RETOUR DE LA COMMANDE 15 RECU
*/



void loop() {
  if (A == 0)
  {
    A = new motor(1);
  }
  if (B == 0)
  {
    B = new motor(2);
  }
  
  
  if (C == 0)
  {
    C = new motor(3);
  }
  
  
  ControlMessage* msg = IO.readMessage(0);
  delay(2000);
  if(msg != 0)
  {
    String caca = "2";
    Serial.println(msg->getType());
    //code pour le set position
    if (msg->getType()== 7)
    {
      A->gotoa(msg->getPayload()[0]);
      
      if (msg->getPayLoadSize()>=2)
      {
        B->gotoa(msg->getPayload()[1]);
        
        if (msg->getPayLoadSize()>=3)
        {
          C->gotoa(msg->getPayload()[2]);
        }
        
      }
      //Serial.print('caca mou');
      delay(5000);      
    }

    //Set limite = 1
    else if (msg->getType()== 1)
    {
      LimiteMaxA = msg->getPayload()[0];
      
      if (msg->getPayLoadSize()>=2)
      {
        LimiteMaxB = msg->getPayload()[1];
        
        if (msg->getPayLoadSize()>=3)
        {
          LimiteMaxC = msg->getPayload()[2];
        }
        
      }
      //Serial.print('caca mou');
      delay(5000);      
    }




    else if (msg->getType()== 3)
    {
      A->gotoa(msg->getPayload()[0]);
      
      if (msg->getPayLoadSize()>=2)
      {
        B->gotoa(msg->getPayload()[1]);
        
        if (msg->getPayLoadSize()>=3)
        {
          C->gotoa(msg->getPayload()[2]);
        }
        
      }
    } 
    //TEST POUR RENVOYER LINFORMATION
    else if (msg->getType()== 11)
    {
      msg->getPayload()[0] = LimiteMaxA;
      
      if (msg->getPayLoadSize()>=2)
      {
        msg->getPayload()[1] = LimiteMaxB;
        
        if (msg->getPayLoadSize()>=3)
        {
          msg->getPayload()[2] = LimiteMaxC;
        }
        
      }
      //Serial.print('caca mou');
      delay(5000);      
    }



    
    ControlMessage responce(msg->getType()+1, msg->getPayLoadSize(), msg->getPayload());
    IO.sendMessage(0,responce);
    delete msg;
    
  }
  else
  {
    //auto responce = ControlMessage(-1);
    //IO.sendMessage(0,responce);
  }
  delay(1000);
  
  // put your main code here, to run repeatedly:
  
}

#endif
