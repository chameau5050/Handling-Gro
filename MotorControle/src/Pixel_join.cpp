/*********************************************************
Fichier     : Pixel_Join.cpp
Auteur      : Jérémy Giguère
Date        : 27 janvier 2021
Description : fichier qui represente les attribut pour la classe abstraite joint
**********************************************************/

#include "Pixel_Join.h"

Pixel_Join::Pixel_Join(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche) : Join(position, limite, homePosition, LimiteSwitchPinDroit, LimiteSwitchPinGauche) //liste d<initialisation
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
        //mettre le code ici pour le controle des moteur
        position = WantedPosition;
        dxl_wb.goalPosition((int8_t)id, (int32_t) WantedPosition, &log);
        delay(60000);

    }   
    else
    {
        //position = oldPosition;
        position = -1;//faire en sorte que la position retourne une erreur
    }
  
}











/*
void goTo(double newPosition)
{
    
    int newlimite = 281; //a vefifier comment faire

    //double oldPosition = getPosition; //est ce que je peux saver l<ancienne position?

    if (newPosition > newlimite)
    {
         newPosition = -1;//faire en sorte que la position retourne une erreur
    }
    else
    {
        //mettre le code ici pour le controle des moteur
        newPosition = newPosition + 0;

    }
    //a implementé ic le code de controle des moteurs

    
   newPosition = 107.0;
    
}

*/

