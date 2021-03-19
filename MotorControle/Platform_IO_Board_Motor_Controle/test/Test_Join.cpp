#include <unity.h> 
#include "Test_Join.h"
#include "Pixel_Join.h"
#include "Test_Join.h"
#include "TestJoinDevice.h"

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
    //test if getPosition works
    //test si le getPosition fonctionne
    TestJoinDevice testjoin(69,281,42,0,0);
    TEST_ASSERT_EQUAL(69,testjoin.getPosition());
}

void Test_Join::test_initialisation_getLimite()
{
    //test if the getLimite works
    //test si le getLimite fonctionne
    Pixel_Join Pixel_le_film(69,281,42,0,0);
    TEST_ASSERT_EQUAL(281,Pixel_le_film.getLimite());
}

void Test_Join::test_initialisation_setLimite()
{
    //test if the setLimite works
    //test si le setLimite fonctionne
    Pixel_Join Pixel_le_film(69,281,42,0,0);
    Pixel_le_film.setLimite(181);
    TEST_ASSERT_EQUAL(181,Pixel_le_film.getLimite());
}

void Test_Join::test_initialisation_getHome()
{
    //test if the getHome works
    //test si le getHome fonctionne
    Pixel_Join Pixel_le_film(69,281,42,0,0);
    TEST_ASSERT_EQUAL(42,Pixel_le_film.getHome());
}

void Test_Join::test_initialisation_setHome()
{
    //test if the setHome works
    //test si le setHome fonctionne
    Pixel_Join Pixel_le_film(69,281,42,0,0);
    Pixel_le_film.setHome(3);
    TEST_ASSERT_EQUAL(3,Pixel_le_film.getHome());
}

void Test_Join::test_initialisation_goTo()
{
    //test if the goTo works
    //test si le goTo fonctionne
    Pixel_Join Pixel_le_film(69,281,42,0,0);
    Pixel_le_film.goTo(107);
    TEST_ASSERT_EQUAL(107,Pixel_le_film.getPosition());

    //test if the goTo works with a value greater than the limit
    //test si le goTo fonctionne avec une valeur suppérieur à la limite
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

    //test if the goTo works with a value greater than the limit
    //test si le goTo fonctionne avec une valeur suppérieur à la limite
    Pixel_le_film1.goTo(2048900);
    TEST_ASSERT_EQUAL(-1,Pixel_le_film1.getPosition());
}








