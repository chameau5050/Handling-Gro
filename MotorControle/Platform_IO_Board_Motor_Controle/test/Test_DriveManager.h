/*********************************************************
Fichier     : test_DriveManager.h
Auteur      : Jérémy Giguère
Date        : 1 mars 2021
Description : Fichier qui represente les tests pour 
              le fichier DriveManager
**********************************************************/

#ifndef TEST_DRIVEMANAGER_H
#define TEST_DRIVEMANAGER_H

#include "abstractTest.h"

class Test_DriveManager : public abstractTest
{
    public:
        void test();
        static void test_goToHome();
        static void test_goToPosition();
        static void test_setHome();
        static void test_calibrateAllJoin();
};
#endif