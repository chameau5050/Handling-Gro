/*********************************************************
Fichier     : Pixel_Join.cpp
Auteur      : Jérémy Giguère
Date        : 27 janvier 2021
Description : fichier qui represente les attribut pour la classe abstraite joint
**********************************************************/

#include "DynamixelMotor.h"

#ifdef UsingMotorDynamixel
DynamixelMotor::DynamixelMotor(uint8_t id)
{
    
}

DynamixelMotor::~DynamixelMotor
{

}



void DynamixelMotor::SendPosition(double WantedPosition)
{
  dxl_wb.goalPosition((int8_t)id, (int32_t)pos, &log);
}


#endif


