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
    TestJoinDevice testjoin(69,281,3,0,0);
    Vector <Join*> joins;
    joins.add(&testjoin);
    DriveManager driveManager(joins);

    driveManager.goToHome();
    TEST_ASSERT_EQUAL(3,testjoin.getPosition());
}

// void Test_DriveManager::test_goToPosition()
// {
//     TestJoinDevice testjoin(6000,281000,3,0,0);
//     Vector <Join*> joins;
//     joins.add(&testjoin);
//     DriveManager driveManager(joins);
    
//     Vector <int> array_position;
//     array_position.add(2048);
//     driveManager.goToPosition(array_position);
//     TEST_ASSERT_EQUAL(2048,testjoin.getPosition());
// }

void Test_DriveManager::test_setHome()
{
    TestJoinDevice testjoinss(3000,254111,50,0,0);
    Vector <Join*> joins;
    joins.add(&testjoinss);
    DriveManager driveManager(joins);

    Vector <int> array_home;
    array_home.add(7);
    driveManager.setHomePosition(array_home);
    TEST_ASSERT_EQUAL(7,testjoinss.getHome());
    
}

void Test_DriveManager::test_calibrateAllJoin()
{
    TEST_ASSERT_EQUAL(1,1);
}