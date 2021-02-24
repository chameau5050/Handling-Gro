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
    this->id = id;
    dxl_wb.init(DEVICE_NAME, baud, &log);
    dxl_wb.ping((int8_t)id, &model_number, &log);
    dxl_wb.currentBasedPositionMode((int8_t)id, 100, &log);
    dxl_wb.ledOn((uint8_t) id, &log);
}
/*
DynamixelMotor::~DynamixelMotor
{
  

}
*/


void DynamixelMotor::SendPosition(double WantedPosition)
{
  dxl_wb.goalPosition((int8_t)id, (int32_t)WantedPosition);
}


#endif
