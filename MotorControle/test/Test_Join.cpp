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
    RUN_TEST(test_initialisation_getPosition);
    RUN_TEST(test_initialisation_getLimite);
    RUN_TEST(test_initialisation_setLimite);
    RUN_TEST(test_initialisation_goTo);
    //RUN_TEST(test_initialisation);    
    //RUN_TEST(test_two);
}

void Test_Join::test_initialisation_getPosition()
{
    //test si le getLimite et le getPosition fonctionne
    Pixel_Join Pixel_le_film(69,281,42,0,0);
    TEST_ASSERT_EQUAL(69,Pixel_le_film.getPosition());
}

void Test_Join::test_initialisation_getLimite()
{
    //test si le getLimite et le getPosition fonctionne
    Pixel_Join Pixel_le_film(69,281,42,0,0);
    TEST_ASSERT_EQUAL(281,Pixel_le_film.getLimite());
}

void Test_Join::test_initialisation_setLimite()
{
    //test si le setLimite fonctionne
    Pixel_Join Pixel_le_film(69,281,42,0,0);
    Pixel_le_film.setLimite(181);
    TEST_ASSERT_EQUAL(181,Pixel_le_film.getLimite());
}

void Test_Join::test_initialisation_goTo()
{
    //test goTo
    Pixel_Join Pixel_le_film(69,281,42,0,0);
    Pixel_le_film.goTo(107);
    TEST_ASSERT_EQUAL(107,Pixel_le_film.getPosition());

    //si si j'envoie une valeur suppérieur à la limite défini 281
    Pixel_le_film.goTo(1000);
    TEST_ASSERT_EQUAL(-1,Pixel_le_film.getPosition());
}








