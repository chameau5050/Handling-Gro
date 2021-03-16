/*********************************************************
Fichier     : DriveManager.cpp
Auteur      : Jérémy Giguère
Date        : 5 mars 2021
Description : fichier qui represente les attribut pour la classe DriveManager
**********************************************************/
#include "DriveManager.h"

DriveManager::DriveManager(Vector <Join*> *Joins)
{
    this->Joins = Joins;
}

DriveManager::~DriveManager()
{

}


void DriveManager::goToHome()
{
    for (int i=0;i < Joins->size();i++)
    {
        Joins->get(i)->goToHome();
    }
}



void  DriveManager::goToPosition(Vector <int> position)
{
    for (int i=0;i < Joins->size();i++)
    {
        Joins->get(i)->goTo(position.get(i));
    }
}



int  DriveManager::setHome(Vector <int> position)
{
    for (int i=0;i < Joins->size();i++)
    {
        Joins->get(i)->setHome(position.get(i));
    }

}

int DriveManager::calibrateAllJoin()
{
    //on est loin detre pret a faire cela 

}