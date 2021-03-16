/*********************************************************
Fichier     : DriveManager.h
Auteur      : Jérémy Giguère
Date        : 5 mars 2021
Description : fichier qui represente les attribut pour la classe DriveManager
**********************************************************/
#include "Join.h"
#include "Utils/Vector.h"

#ifndef DRIVEMANAGER_H
#define DRIVEMANAGER_H

//class DriveManager : public Join

class DriveManager
{
    public:
        DriveManager(Vector <Join*> *Joins);
        ~DriveManager();
        void goToHome();
        void goToPosition(Vector <int> position);
        int setHome(Vector <int> position);
        int calibrateAllJoin();
    private:
        Vector <Join*> *Joins;
};
#endif