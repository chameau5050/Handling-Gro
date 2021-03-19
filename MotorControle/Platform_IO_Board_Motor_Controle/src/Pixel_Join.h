#ifndef Pixel_Join_H
#define Pixel_Join_H

#include <stdio.h>


#include "Join.h"

class Pixel_Join : public Join
{
    public:
        Pixel_Join(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche, uint8_t id = 1);
        //~Pixel_Join();  
        void goTo(int position); 
};
#endif



