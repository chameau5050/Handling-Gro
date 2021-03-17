/*********************************************************
Fichier     : StepperJoin.h
Auteur      : Jérémy Giguère
Date        : 12 mars 2021
Description : fichier qui represente les attribut pour la classe abstraite joint avec l'utilisation de stepper motor
**********************************************************/

#ifndef STEPPERJOIN_H
#define STEPPERJOIN_H

#include "Join.h"

class StepperJoin : public Join
{
    public:
        StepperJoin(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche, uint8_t id = 1);
        ~StepperJoin();
        void goTo(int position); 

};
#endif



