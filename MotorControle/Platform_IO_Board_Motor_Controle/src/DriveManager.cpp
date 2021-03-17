/*********************************************************
Fichier     : DriveManager.cpp
Auteur      : Jérémy Giguère
Date        : 5 mars 2021
Description : fichier qui represente les attribut pour la classe DriveManager
**********************************************************/
#include "DriveManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Arduino.h>

DriveManager::DriveManager(const Vector<Join*>& Joins)
{
    this->Joins = Joins;
    
}

DriveManager::~DriveManager()
{

}


void DriveManager::goToHome()
{
    for (int i=0;i < Joins.size();i++)
    {
        Joins.get(i)->goToHome();
    }
}



void DriveManager::goToPosition(Vector <int> position)
{
    for (int i=0;i < Joins.size();i++)
    {
        Joins.get(i)->goTo(position.get(i));
    }
}



void DriveManager::setHomePosition(Vector <int> newhomeposition)
{
    for (int i=0;i < Joins.size();i++)
    {
        int valeur = newhomeposition.get(i);
        //Joins.get(i)->setHome(newhomeposition.get(i));
        Joins.get(i)->setHome(valeur);

        
    }
}

void DriveManager::calibrateAllJoin()
{
    //on est loin detre pret a faire cela 

}