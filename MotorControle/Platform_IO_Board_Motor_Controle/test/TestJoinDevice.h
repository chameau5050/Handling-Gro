#include "Join.h"

#ifndef TESTJOINDEVICE_H
#define TESTJOINDEVICE_H

class TestJoinDevice : public Join 
{
    public:
        TestJoinDevice(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche);
        virtual void goTo(int WantedPosition);
};

TestJoinDevice::TestJoinDevice(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche):Join(position, limite, homePosition, LimiteSwitchPinDroit, LimiteSwitchPinGauche)
{


}

void TestJoinDevice::goTo(int WantedPosition)
{
        if (WantedPosition <= limite)
    {
        position = WantedPosition;
    }   
    else
    {
        position = -1;
    }    
}
#endif