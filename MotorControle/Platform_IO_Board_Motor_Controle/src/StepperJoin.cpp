/*********************************************************
Fichier     : StepperJoin.cpp
Auteur      : Jérémy Giguère
Date        : 12 mars 2021
Description : fichier qui represente les attribut pour la classe abstraite joint avec l'utilisation de stepper motor
**********************************************************/

#include "StepperJoin.h"

StepperJoin::StepperJoin(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche, uint8_t id) : Join(position, limite, homePosition, LimiteSwitchPinDroit, LimiteSwitchPinGauche) 
{
    

}

StepperJoin::~StepperJoin()
{

}


void StepperJoin::goTo(int WantedPosition)
{

    if (WantedPosition <= limite)
    {

        position = WantedPosition;
        //mettre le code ici pour le controle des moteur
    }   
    else
    {
        position = -1;//faire en sorte que la position retourne une erreur
    }
  
}

