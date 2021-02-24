/*********************************************************
Fichier     : Pixel_join.cpp
Auteur      : Jérémy Giguère
Date        : 27 janvier 2021
Description : fichier qui represente les attribut pour la classe abstraite joint
**********************************************************/

#ifndef DYNAMIXELMOTOT_H
#define DYNAMIXELMOTOT_H

//inclure les libraries que j'ai besoin
//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <DynamixelWorkbench.h>

//#include "Pixel_Join.h"

#define UsingMotorDynamixel

#ifdef UsingMotorDynamixel


#if defined(__OPENCM904__)
#define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
#define DEVICE_NAME ""
#endif   

#define STRING_BUF_NUM1 64
String cmd[STRING_BUF_NUM1];


//uint8_t get_id[16];
//uint8_t scan_cnt = 0;
//uint8_t ping_cnt = 0;

bool isAvailableID(uint8_t id);
void split(String data, char separator, String* temp);
void printInst();



class DynamixelMotor
{
    public:
      DynamixelWorkbench dxl_wb;
        DynamixelMotor(uint8_t id = 1);
        //~Pixel_Join();    //pas vraiment nécessaire
        void SendPosition(double position); 
        uint16_t model_number;
        int actualPosition;
        int goal = 100;
        int32_t data;
        int baud = 57600;
        uint8_t id;
        const char *log;
        
};

#else
class DynamixelMotor
{
    public:
        DynamixelMotor(uint8_t id = 1){};
        void SendPosition(double WantedPosition){};
};




#endif
#endif
