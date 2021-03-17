#include <stdio.h>

#include "Pixel_Join.h"

Pixel_Join::Pixel_Join(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche, uint8_t id) : Join(position, limite, homePosition, LimiteSwitchPinDroit, LimiteSwitchPinGauche) 
{

}

/*
Pixel_Join::~Pixel_Join()
{

}
*/

void Pixel_Join::goTo(int WantedPosition)
{

    if (WantedPosition <= limite)
    {
        position = WantedPosition;
        //Mettre le code ici pour le controle des moteurs
        //Put the code here for engine control


    }   
    else
    {
        position = -1;
    }

}

