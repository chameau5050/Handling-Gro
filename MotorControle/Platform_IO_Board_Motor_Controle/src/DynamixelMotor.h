/*********************************************************
Fichier     : Pixel_join.cpp
Auteur      : Jérémy Giguère
Date        : 27 janvier 2021
Description : fichier qui represente les attribut pour la classe abstraite joint
**********************************************************/

#ifndef DYNAMIXELMOTOT_H
#define DYNAMIXELMOTOT_H

//inclure les libraries que j'ai besoin
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Pixel_Join.h"


#ifdef UsingMotorDynamixel
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



class DynamixelMotor
{
    public:
        DynamixelMotor(uint8_t id = 1);
        //~Pixel_Join();    //pas vraiment nécessaire
        void SendPosition(double position); 


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

        delay(10000);
        result = dxl_wb.init(DEVICE_NAME, baud);
        result = dxl_wb.ping((int8_t)id, &model_number, &log);

        result = dxl_wb.currentBasedPositionMode((int8_t)id, 100, &log);
        result3 = dxl_wb.ledOn((uint8_t) id, &log);
        //dxl_wb.ledOff((int8_t)id, &log);
        //delay(1000);
        //dxl_wb.ledOn((int8_t)id, &log);

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





