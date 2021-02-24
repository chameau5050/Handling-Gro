/*********************************************************
Fichier     : Pixel_join.h
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

class Pixel_Join : public Join
{
    public:
        Pixel_Join(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche, uint8_t id = 1);
        //~Pixel_Join();    //pas vraiment nécessaire
        void goTo(double position); 


};
#endif



