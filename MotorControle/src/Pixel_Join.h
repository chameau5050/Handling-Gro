/*********************************************************
Fichier     : Pixel_join.cpp
Auteur      : Jérémy Giguère
Date        : 27 janvier 2021
Description : fichier qui represente les attribut pour la classe abstraite joint
**********************************************************/

#ifndef Pixel_Join_H
#define Pixel_Join_H

//inclure les libraries que j'ai besoin
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Join.h"

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



class Pixel_Join : public Join
{
    public:
        Pixel_Join(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche, uint8_t id);
        //~Pixel_Join();    //pas vraiment nécessaire
        void goTo(double position); 


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
#endif





//les variables que je vais avoir besoin:
/*

-position
-limite
-homePosition
-LimiteSwitchPin

*/

//les fonctions que je vais devoir faire:
/*

+goTo(position) =0 (virtuelle pure)
+goToHome()
+resetPosition()
+getPosition()

*/

