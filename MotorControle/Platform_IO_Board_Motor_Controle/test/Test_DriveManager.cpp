/*********************************************************
Fichier     : test_DriveManager.cpp
Auteur      : Jérémy Giguère
Date        : 1 mars 2021
Description : Fichier qui represente les tests pour 
              le fichier DriveManager
**********************************************************/
#include <unity.h> //library de base pour faire du unite testing
#include "Test_DriveManager.h"
#include "DriveManager.h"
#include "Utils/Vector.h"
#include "Pixel_Join.h"

void Test_DriveManager::test()
{
    RUN_TEST(test_goToHome);
    RUN_TEST(test_goToPosition);
    RUN_TEST(test_setHome);
    RUN_TEST(test_calibrateAllJoin);
}


void Test_DriveManager::test_goToHome()
{
    Pixel_Join pixel_le_film(69,281,3,0,0);
    Vector <Join*> joins;
    joins.add(&pixel_le_film);
    DriveManager driveManager(&joins);

    driveManager.goToHome();
    pixel_le_film.goToHome();
    TEST_ASSERT_EQUAL(3,pixel_le_film.getPosition());
}




void Test_DriveManager::test_goToPosition()
{
    Pixel_Join pixel_le_film(6000,281000,3,0,0);
    Vector <Join*> joins;
    joins.add(&pixel_le_film);
    DriveManager driveManager(&joins);
    Vector <int> array_position;
    array_position.add(2048);
    driveManager.goToPosition(array_position);
    TEST_ASSERT_EQUAL(2048,pixel_le_film.getPosition());
}


void Test_DriveManager::test_setHome()
{
    TEST_ASSERT_EQUAL(1,1);
}

void Test_DriveManager::test_calibrateAllJoin()
{
    TEST_ASSERT_EQUAL(1,1);
}