/*********************************************************
Fichier     : test_Join.h
Auteur      : Jérémy Giguère
Date        : 04 Février 2021
Description : Fichier qui represente les tests pour les fichier Join
**********************************************************/

#ifndef TEST_JOIN_H
#define TEST_JOIN_H

#include "abstractTest.h"

class Test_Join : public abstractTest //c'est de l'héritage de ?
{
    public:
        void test();
        static void test_initialisation_getPosition();
        static void test_initialisation_getLimite();
        static void test_initialisation_setLimite();
        static void test_initialisation_goTo();
        static void test_initialisation_goTo_avec_le_moteur();

};
#endif