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
    RUN_TEST(test_initialisation_getHome);
    RUN_TEST(test_initialisation_setHome);
    //RUN_TEST(test_initialisation_goTo_avec_le_moteur);
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

void Test_Join::test_initialisation_getHome()
{
    //test si le getLimite et le getPosition fonctionne
    Pixel_Join Pixel_le_film(69,281,42,0,0);
    TEST_ASSERT_EQUAL(42,Pixel_le_film.getHome());
}

void Test_Join::test_initialisation_setHome()
{
    //test si le setLimite fonctionne
    Pixel_Join Pixel_le_film(69,281,42,0,0);
    Pixel_le_film.setHome(3);
    TEST_ASSERT_EQUAL(3,Pixel_le_film.getHome());
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

void Test_Join::test_initialisation_goTo_avec_le_moteur()
{
    //test goTo_avec_le_moteur
    Pixel_Join Pixel_le_film1(69,1048576,42,0,0);
    //test pour la position initiale
    Pixel_le_film1.goTo(0);
    TEST_ASSERT_EQUAL(0,Pixel_le_film1.getPosition());
    //test pour 1 tour
    Pixel_le_film1.goTo(4096);
    TEST_ASSERT_EQUAL(4096,Pixel_le_film1.getPosition());

    //si si j'envoie une valeur suppérieur à la limite défini 1048576
    Pixel_le_film1.goTo(20480);
    TEST_ASSERT_EQUAL(20480,Pixel_le_film1.getPosition());

    //retour à 0
    Pixel_le_film1.goTo(0);
    TEST_ASSERT_EQUAL(0,Pixel_le_film1.getPosition());

    //si si j'envoie une valeur suppérieur à la limite défini 281
    Pixel_le_film1.goTo(2048900);
    TEST_ASSERT_EQUAL(-1,Pixel_le_film1.getPosition());
}








