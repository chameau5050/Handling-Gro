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
int LimiteMaxD = 8193;

int LimiteMax[4] = {81921,8193,8193,8193};
/*
 * ON A PAS BESOIN DE LIMITE MINIMUM
int LimiteMinA = -100;
int LimiteMinB = -5;
int LimiteMinC = -5;
*/

int HomeA = 0;
int HomeB = 0;
int HomeC = 0;
int HomeD = 0;
int Home[4]= {0,0,0,0}; 



 
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

    result = dxl_wb.init(DEVICE_NAME, baud);
    result = dxl_wb.ping((int8_t)id, &model_number, &log);

    //result = dxl_wb.jointMode(id, 0, 0, &log);
//Essaie #1
    //result = dxl_wb.setMultiTurnControlMode((int8_t)id,  &log);
    //result = dxl_wb.setOperatingMode((int8_t)id, index, &log);

//Essaie #2
   //result1 = dxl_wb.setExtendedPositionControlMode((int8_t)id,  &log);
    result = dxl_wb.currentBasedPositionMode((int8_t)id, 100, &log);
    result3 = dxl_wb.ledOn((uint8_t) id, &log);
    if(result3==1)
      Serial.println("Lumière active, moteur prêt");
    else
      Serial.println("Lumière NON-active, moteur pas pret");

  };
  
  
  //DynamixelWorkbench dxl_wb;
  int id;
  const char *log;
  
  void gotoa(int32_t pos)
  {
    dxl_wb.goalPosition((int8_t)id, (int32_t)pos, &log);
  };


  int GetPosition()
  {
    int32_t data;
    int reussite;
    dxl_wb.getPresentPositionData((int8_t)id, &data, &log);
    Serial.println(data);
    return data;
  }

 };
 

motor* A;
motor* B;
motor* C;
motor* D;

motor** Reference[4] = {&A,&B,&C,&D};

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

{​​"type":17,"PLS":3,"data":[0,0,0]}​​


{​​"type":3,"PLS":3,"data":[50,500,1500]}​​

{​​"type":5,"PLS":3,"data":[0,1,0]}​​
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

  if (D == 0)
  {
    D = new motor(4);
  }

  
  ControlMessage* msg = IO.readMessage(0);
  //delay(2000);
  if(msg != 0)
  {
    //Serial.println(msg->getType());
    //code pour le set position
    if (msg->getType()== 7)
    {
      if (msg->getPayload()[0] >= LimiteMaxA)
      {
        msg->getPayload()[0] = LimiteMaxA;
      }
      A->gotoa(msg->getPayload()[0]);
      
      if (msg->getPayLoadSize()>=2)
      {
        if (msg->getPayload()[1] >= LimiteMaxB)
        {
          msg->getPayload()[1] = LimiteMaxB;
        }
        B->gotoa(msg->getPayload()[1]);
        
        if (msg->getPayLoadSize()>=3)
        {
          if (msg->getPayload()[2] >= LimiteMaxC)
          {
            msg->getPayload()[2] = LimiteMaxC;
          }
          C->gotoa(msg->getPayload()[2]);

          if (msg->getPayLoadSize()>=4)
          {
            if (msg->getPayload()[3] >= LimiteMaxD)
            {
              msg->getPayload()[3] = LimiteMaxD;
            }
            D->gotoa(msg->getPayload()[3]);
          }
        }
        
      }
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

          if (msg->getPayLoadSize()>=4)
        {
          LimiteMaxD = msg->getPayload()[3];
        }
        }
        
      }   
    }


    //*code pour set les position home du robot
    else if (msg->getType()== 3)
    {
      HomeA = msg->getPayload()[0];
      
      if (msg->getPayLoadSize()>=2)
      {
        HomeB = msg->getPayload()[1];
        
        if (msg->getPayLoadSize()>=3)
        {
         HomeC = msg->getPayload()[2];
         
         if (msg->getPayLoadSize()>=4)
         {
            HomeD = msg->getPayload()[3];
         }
         
        }
        
      }
    } 

    //*code pour zeroter le robot
    else if (msg->getType()== 5)
    {
      if (msg->getPayload()[0] == 1)
      {
        delete A;
         A = new motor(1);
      }
      else
      {
        msg->getPayload()[0] = 0;
      }

      
     
      if (msg->getPayLoadSize()>=2)
      {
        if (msg->getPayload()[1] == 1)
        {
          delete B;
          B = new motor(2);
        }
        else
        {
          msg->getPayload()[1] = 0;
        }

        
        if (msg->getPayLoadSize()>=3)
        {
           if (msg->getPayload()[2] == 1)
           {
            delete C;
             C = new motor(3);
           }
           else
           {
            msg->getPayload()[2] = 0;
           }

           if (msg->getPayLoadSize()>=4)
            {
               if (msg->getPayload()[3] == 1)
               {
                delete D;
                 D = new motor(4);
               }
               else
               {
                msg->getPayload()[3] = 0;
               }
            }
        }
        
      }
    } 
    
    //*code pour envoyer le robot a sa position home
    else if (msg->getType()== 9)
    {
      
      A->gotoa(HomeA);
      msg->getPayload()[0] = HomeA;
      
      if (msg->getPayLoadSize()>=2)
      {
        B->gotoa(HomeB);
        msg->getPayload()[1] = HomeB;
        
        if (msg->getPayLoadSize()>=3)
        {
          C->gotoa(HomeC);
          msg->getPayload()[2] = HomeC;
          
          if (msg->getPayLoadSize()>=4)
          {
          D->gotoa(HomeD);
          msg->getPayload()[3] = HomeD;
          }
        }
        
      }
    } 
    //TEST POUR RENVOYER LINFORMATION

    //renvoyer les limites definie sur les moteurs
    else if (msg->getType()== 11)
    {
      msg->getPayload()[0] = LimiteMaxA;
      
      if (msg->getPayLoadSize()>=2)
      {
        msg->getPayload()[1] = LimiteMaxB;
        
        if (msg->getPayLoadSize()>=3)
        {
          msg->getPayload()[2] = LimiteMaxC;
          
          if (msg->getPayLoadSize()>=4)
          {
            msg->getPayload()[3] = LimiteMaxD;
          } 
        }  
      }
    }
    
    //renvoyer les position home definie sur les moteurs
    else if (msg->getType()== 13)
    {
      msg->getPayload()[0] = HomeA;
      
      if (msg->getPayLoadSize()>=2)
      {
        msg->getPayload()[1] = HomeB;
        
        if (msg->getPayLoadSize()>=3)
        {
          msg->getPayload()[2] = HomeC;
          
          if (msg->getPayLoadSize()>=4)
        {
          msg->getPayload()[3] = HomeD;
        } 
        }  
      }
    }


    
    //renvoyer la position actuelle du robot
    else if (msg->getType()== 17)
    {
      for (int i = 0;i < msg->getPayLoadSize()>=2;i++)
      {
        msg->getPayload()[i] = (*Reference[i])->GetPosition();
        
      }

      /*
      msg->getPayload()[0] = A->GetPosition();
     
      if (msg->getPayLoadSize()>=2)
      {
        msg->getPayload()[1] = B->GetPosition();
        
        if (msg->getPayLoadSize()>=3)
        {
          msg->getPayload()[2] = C->GetPosition();
          
          if (msg->getPayLoadSize()>=4)
          {
            msg->getPayload()[3] = D->GetPosition();
          }
        }
      } 
      */ 
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
