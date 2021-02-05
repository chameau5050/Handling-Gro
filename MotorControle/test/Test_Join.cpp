/*********************************************************
Fichier     : test_Join.cpp
Auteur      : Jérémy Giguère
Date        : 04 Février 2021
Description : Fichier qui represente les tests pour les fichier Join
**********************************************************/

#include <unity.h> //library de base pour faire du unite testing
#include "Test_Join.h"
#include "Pixel_Join.h"
#include "Test_Join.h"

void Test_Join::test()
{
    
    RUN_TEST(test_initialisation);
    //RUN_TEST(test_two);
}

void Test_Join::test_initialisation()
{
    Pixel_Join Pixel_le_film(69,281,42,0,0);
    TEST_ASSERT_EQUAL(69,Pixel_le_film.getPosition());
    TEST_ASSERT_EQUAL(281,Pixel_le_film.getLimite());
    //test si le setLimite fonctionne
    Pixel_le_film.setLimite(65);
    TEST_ASSERT_EQUAL(65,Pixel_le_film.getLimite());

}
