/*********************************************************
Fichier     : test_DriveManager.cpp
Auteur      : Jérémy Giguère
Date        : 5 mars 2021
Description : Fichier qui represente les tests pour 
              le fichier DriveManager
**********************************************************/
#include <unity.h> //library de base pour faire du unite testing
#include "Test_DriveManager.h"
#include "DriveManager.h"
#include "Utils/Vector.h"
//#include "Pixel_Join.h"
#include "TestJoinDevice.h"

void Test_DriveManager::test()
{
    RUN_TEST(test_goToHome);
    // RUN_TEST(test_goToPosition);
    RUN_TEST(test_setHome);
    RUN_TEST(test_calibrateAllJoin);
}

void Test_DriveManager::test_goToHome()
{
    DriveManager driveManager;
    TestJoinDevice* testjoin = new TestJoinDevice(69,281,3,0,0);
    driveManager.addJoin(testjoin);

    driveManager.goToHome();
    TEST_ASSERT_EQUAL(3,testjoin->getPosition());
}

 void Test_DriveManager::test_goToPosition()
{    
    DriveManager driveManager; 
    TestJoinDevice* testjoin = new TestJoinDevice(6000,281000,3,0,0);
    driveManager.addJoin(testjoin);
    
     Vector <int> array_position;
     array_position.add(2048);
     driveManager.goToPosition(array_position);

     TEST_ASSERT_EQUAL(2048,testjoin->getPosition());
}

void Test_DriveManager::test_setHome()
{
    DriveManager driveManager;
    TestJoinDevice* testjoin = new TestJoinDevice(3000,254111,50,0,0);
    driveManager.addJoin(testjoin);

    Vector <int> array_home;
    array_home.add(7);
    driveManager.setHomePosition(array_home);
    TEST_ASSERT_EQUAL(7,testjoin->getHome());
    
}

void Test_DriveManager::test_calibrateAllJoin()
{
    TEST_ASSERT_EQUAL(1,1);
    //fonction pour calibrer les moteurs et definir leur parametres
    // a faire
}