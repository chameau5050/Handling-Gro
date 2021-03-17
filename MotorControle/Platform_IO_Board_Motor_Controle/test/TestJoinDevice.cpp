/*********************************************************
Fichier     : TestJoinDevice.h
Auteur      : Jérémy Giguère
Date        : 15 mars 2021
Description : fichier qui set au test unitaire en creant un muck
**********************************************************/

#include "TestJoinDevice.h"

TestJoinDevice::TestJoinDevice(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche) : Join(position, limite, homePosition, LimiteSwitchPinDroit, LimiteSwitchPinGauche) 
{
    
}

void TestJoinDevice::goTo(int WantedPosition)
{
    if (WantedPosition <= limite)
    {
        position = WantedPosition;
    }   
    else
    {
        position = -1;
    }    
}