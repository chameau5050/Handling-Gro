#include "StateManager.h"
#include "Comm/ControlMessage.h"
#include "Utils/Vector.h"

// Definition des defines pour la communication
// Definition of define for communication
#define SET_LIMITES_INDEX 1
#define SET_HOME_POSITION_INDEX 3
#define SET_REFERENCE_POSITION_INDEX 5
#define GO_TO_POSITION_INDEX 7
#define GO_TO_HOME_INDEX 9
#define RETURN_LIMITES_INDEX 11
#define RETURN_HOME_POSITION_INDEX 13
#define RETURN_REFERENCE_POSITION_INDEX 15
#define RETURN_ACTUAL_POSITION_INDEX 17

#define NbrMotor 5
#define NbrMotorDynamixel 4
#define NbrMotorStepper 1


StateManager::StateManager(DriveManager* drivemanager)
{
    this->drivemanager = drivemanager;
}

StateManager::~StateManager()
{

}


void StateManager::updateState(ControlMessage* reponse)
{
    
    if (reponse->getType() == GO_TO_POSITION_INDEX)
    {
        goTo(reponse->getPayload(),reponse->getPayLoadSize());
    } 
    //faire unitest pour cette fonction

    //reproduire pour les autres fonctions  
}

void StateManager::goTo(int payload[], int payloadsize)
{
    drivemanager->goToPosition(payload, payloadsize);  
}

void StateManager::callGoToHome()
{
    

}

void StateManager::callibrateDrive(int nbrmotorAInitialiser)
{

}