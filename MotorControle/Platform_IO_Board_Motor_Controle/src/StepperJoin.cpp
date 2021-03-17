/*********************************************************
Fichier     : StepperJoin.cpp
Auteur      : Jérémy Giguère
Date        : 12 mars 2021
Description : fichier qui represente les attribut pour la classe abstraite joint avec l'utilisation de stepper motor
**********************************************************/

#include "StepperJoin.h"
#include "TinyStepper_28BYJ_48-master/src/TinyStepper_28BYJ_48.h"

StepperJoin::StepperJoin(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche, uint8_t id) : Join(position, limite, homePosition, LimiteSwitchPinDroit, LimiteSwitchPinGauche) 
{
    //TinyStepper_28BYJ_48 stepmotor;
    stepmotor.connectToPins(2,3,4,5);
}

StepperJoin::~StepperJoin()
{

}


void StepperJoin::goTo(int WantedPosition)
{
    TinyStepper_28BYJ_48 stepmotor;
    // stepmotor.connectToPins(2,3,4,5);
    //determiner une rotation correspond a une déplacement de combien??
    int facteur_distance = 1;

    if (WantedPosition <= limite)
    {
        int nb_rotation =  facteur_distance *WantedPosition;
        stepmotor.moveToPositionInSteps(2048*nb_rotation);

        bool done = stepmotor.motionComplete();
        while (done == false)
        {
            delay(100);
            done = stepmotor.motionComplete();
        }

        position = WantedPosition;
    }   
    else
    {
        position = -1;//faire en sorte que la position retourne une erreur
    }
  
}

