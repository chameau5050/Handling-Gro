/*********************************************************
Fichier     : DriveManager.h
Auteur      : Jérémy Giguère
Date        : 5 mars 2021
Description : fichier qui represente les attributs pour la classe DriveManager
**********************************************************/
#include "Join.h"
#include "Utils/Vector.h"

#ifndef DRIVEMANAGER_H
#define DRIVEMANAGER_H

class DriveManager
{
    public:
        DriveManager();
        ~DriveManager();
        void addJoin(Join* newJoin);
        void deleteJointAt(int index);
        void goToHome();
        void goToPosition(Vector <int> position);
        void setHomePosition(Vector <int> position);
        void calibrateAllJoin();
    private:
        Vector <Join*> Joins;
};
#endif