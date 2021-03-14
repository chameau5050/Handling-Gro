/*********************************************************
Fichier     : Pixel_Join.cpp
Auteur      : Jérémy Giguère
Date        : 27 janvier 2021
Description : fichier qui represente les attribut pour la classe abstraite joint
**********************************************************/

#include "Pixel_Join.h"

Pixel_Join::Pixel_Join(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche, uint8_t id) : Join(position, limite, homePosition, LimiteSwitchPinDroit, LimiteSwitchPinGauche) //liste d<initialisation
{
    

}

/*
Pixel_Join::~Pixel_Join()
{

}
*/

void Pixel_Join::goTo(double WantedPosition)
{

   // double oldPosition = position; //est ce que je peux saver l<ancienne position?

    if (WantedPosition <= limite)
    {

        position = WantedPosition;
        //mettre le code ici pour le controle des moteur
    }   
    else
    {
        //position = oldPosition;
        position = -1;//faire en sorte que la position retourne une erreur
    }
  
}

