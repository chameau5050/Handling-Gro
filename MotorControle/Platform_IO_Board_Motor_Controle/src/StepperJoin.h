/*********************************************************
Fichier     : StepperJoin.h
Auteur      : Jérémy Giguère
Date        : 12 mars 2021
Description : fichier qui represente les attribut pour la classe abstraite joint avec l'utilisation de stepper motor
**********************************************************/

#ifndef STEPPERJOIN_H
#define STEPPERJOIN_H

#include "Join.h"
#include "TinyStepper_28BYJ_48-master/src/TinyStepper_28BYJ_48.h"

class StepperJoin : public Join
{
    public:
        StepperJoin(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche, int MOTOR_IN1_PIN = 8, int MOTOR_IN2_PIN = 9, int MOTOR_IN3_PIN = 10, int MOTOR_IN4_PIN = 11);
        ~StepperJoin();
        void goTo(int position); 

    protected:
        TinyStepper_28BYJ_48 stepmotor;


};
#endif



