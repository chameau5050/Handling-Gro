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
#include "TinyStepper_28BYJ_48.h"

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
#define NbrMotor 5
#define NbrMotorDynamixel 4
#define NbrMotorStepper 1

int defineID[NbrMotor]= {1,2,3,4,5};

int LimiteMax[NbrMotor] = {81921,8193,8193,8193,50000};
int LimiteMin[NbrMotor] = {0,0,0,0,0};
int Home[NbrMotor]= {0,0,0,0,0}; 

// Definition de la classe moteur pour les moteurs STEP
// Definition of the motor class for dynamixel STEP
TinyStepper_28BYJ_48 stepper;

class motorstepper
{
  public:
  motorstepper(int id)
  {
    const int LED_PIN = 13;
    const int MOTOR_IN1_PIN = 8;
    const int MOTOR_IN2_PIN = 9;
    const int MOTOR_IN3_PIN = 10;
    const int MOTOR_IN4_PIN = 11;
    const int STEPS_PER_REVOLUTION = 2048;
    //this->ids = ids;//si sa marche sans, enlever cette ligne
    
    stepper.connectToPins(MOTOR_IN1_PIN, MOTOR_IN2_PIN, MOTOR_IN3_PIN, MOTOR_IN4_PIN);
    
    //Code for setting motors in different modes   
    //Code pour le réglage des moteurs dans differents modes
    stepper.setSpeedInStepsPerSecond(500);
    stepper.setAccelerationInStepsPerSecondPerSecond(1000);
    
    Serial.println("");
    Serial.print("If light On, steppermotor ");
    Serial.print(id);
    Serial.print(" ready. If light OFF, this steppermotor is NOR ready");
    Serial.println("");
   };
  
  void gotoa(int32_t pos)
  {
    //stepper.moveRelativeInSteps(pos);
    stepper.moveToPositionInSteps(pos);
  };

  void setHomingOffset(int32_t pos)
  {
    Serial.println("Fonction not working at 100%: Error");
    Serial.println("Maybe, not avalable with this motor.");
    stepper.setCurrentPositionInSteps(pos);
  }
  
  int32_t GetPosition1()
  {
    long actualPos = stepper.getCurrentPositionInSteps();
    return actualPos;
  }

  int32_t GetReferencePosition1()
  {
    Serial.println("Maybe, not avalable with this motor.");
    return -1;
  }
 };



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


motor* Reference[NbrMotorDynamixel];
motorstepper* ReferenceStepper[NbrMotorStepper];


void setup() 
{
  Serial.begin(BAUD);
  IO.addDevice(&SC);
  delay(10);

  
  delay(7000); // A ENLEVER C JUSTE POUR TEST
}

void loop() 
{
  ControlMessage* msg = IO.readMessage(0);

  for (int m=0;m<NbrMotor;m++)
  {
    if ((Reference[m] == 0)&& (m < NbrMotorDynamixel))
    {
        Reference[m] = new motor(defineID[m]);
        Serial.println("Je set un motor");
    }
    else if((ReferenceStepper[m] == 0) && (m >= NbrMotorDynamixel))
    {
        ReferenceStepper[m] = new motorstepper(defineID[m]);
        Serial.println("Je set un steppermotor");
    }
  }


//    for (int m=0;m<NbrMotor;m++)
//  {
//    if (Reference[m] == 0)
//    {
//      if (m < NbrMotorDynamixel)
//      {
//        Reference[m] = new motor(defineID[m]);
//        Serial.print("Je set un motor");
//      }
//    }
//    else if(ReferenceStepper[m] == 0)
//    {
//      if (m >= NbrMotorDynamixel)
//      {
//        ReferenceStepper[m] = new motorstepper(defineID[m]);
//        Serial.print("Je set un steppermotor");
//      } 
//    }
//  }
      
  if(msg != 0)
  {
    for (int i=0;i<msg->getPayLoadSize();i++)
    {
//CODE POUR INITIALISER LES MOTEURS
//CODE TO INITIALIZE THE MOTORS      
      if ((Reference[i] == 0)&& (i < NbrMotorDynamixel))
      {
          Reference[i] = new motor(defineID[i]);
          Serial.println("Motor");
          Serial.println(i);
          Serial.println("activer");
      }
      else if((ReferenceStepper[i] == 0) && (i >= NbrMotorDynamixel))
      {
          ReferenceStepper[i] = new motorstepper(defineID[i]);
          Serial.println("StepperMotor");
          Serial.println(i);
          Serial.println("activer");
      }

//      if (Reference[i] == 0)
//      {
//        if (i < NbrMotorDynamixel)
//        {
//          Reference[i] = new motor(defineID[i]);
//          Serial.println("Motor");
//          Serial.println(i);
//          Serial.println("activer");
//        }
//      }
//      else if(ReferenceStepper[i] == 0)
//      {
//        if (i >= NbrMotorDynamixel)
//        {
//          ReferenceStepper[i] = new motorstepper(defineID[i]);
//          Serial.println("StepperMotor");
//          Serial.println(i);
//          Serial.println("activer");
//        } 
//      }

// APPLIQUER LA MEME METONDE POUR TOUTES LES FONCTIONS SI LE TEST DE DRIVE FONCTIONNE
/*
if (i < NbrMotorDynamixel)
{
  //exemple:Reference[i]->gotoa(msg->getPayload()[i]);
  //FONCTION A ENVOYER AVEC LE REFERENCE
}
else if(i >= NbrMotorDynamixel)
{
  //exemple:ReferenceStepper[i]->gotoa(msg->getPayload()[i]);
   //FONCTION A ENVOYER AVEC LE REFERENCEStepper
}
*/    

//CODE POUR LES DIFFERENTES OPERATIONS A EFFECTUER PAR LE MOTEURS
//CODE FOR THE DIFFERENT OPERATIONS TO BE CARRIED OUT BY THE ENGINES
      
      //Set position = 7 
      if (msg->getType()== GO_TO_POSITION_INDEX)
      {
        if (msg->getPayload()[i] >= LimiteMax[i])
        {
          msg->getPayload()[i] = LimiteMax[i];
        }

        if (i < NbrMotorDynamixel)
        {
          Reference[i]->gotoa(msg->getPayload()[i]);
        }
        else if(i >= NbrMotorDynamixel)
        {
          ReferenceStepper[i]->gotoa(msg->getPayload()[i]);
        }
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
