/*********************************************************
Fichier     : TestJoinDevice.h
Auteur      : Jérémy Giguère
Date        : 15 mars 2021
Description : fichier qui set au test unitaire en creant un muck
**********************************************************/

#ifndef TESTJOINDEVICE_H
#define TESTJOINDEVICE_H

#include "Join.h"

class TestJoinDevice : public Join 
{
    public:
        TestJoinDevice(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche);
        void goTo(int WantedPosition);
        //virtual void goTo(int WantedPosition);
};

#endif