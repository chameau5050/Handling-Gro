/*********************************************************
Fichier     : Join.h
Auteur      : Jérémy Giguère
Date        : 27 janvier 2021
Description : fichier qui represente les attribut pour la classe abstraite joint
**********************************************************/

#ifndef JOIN_H
#define JOIN_H

//inclure les libraries que j'ai besoin
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


class Join
{
    public:
        Join(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche);
        ~Join();

        virtual void goTo(int Wantedposition) = 0; 
        void goToHome();
        void resetPosition();
        int getPosition();
        int getLimite();
        void setLimite(int newLimite);
        void setHome(int newHomePosition);
        int getHome();

    protected:
        int position; 
        int limite;
        int homePosition;
        int LimiteSwitchPinDroit;
        int LimiteSwitchPinGauche;
        int Pin; // code pour indiquer les pin du arduino

};
#endif



