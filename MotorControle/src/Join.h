/*********************************************************
Fichier     : join.cpp
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
        ~Join();//pas vraiment nécessaire

        virtual void goTo(double position) = 0; // =0; //(virtuelle pure)
        void goToHome();
        void resetPosition();
        int getPosition();
        int getLimite();
        void setLimite(int newLimite);

    private:
        int position; // c'est mon compteur
        int limite;
        int homePosition;
        int LimiteSwitchPinDroit;
        int LimiteSwitchPinGauche;

};
#endif

//les variables que je vais avoir besoin:
/*

-position
-limite
-homePosition
-LimiteSwitchPin

*/

//les fonctions que je vais devoir faire:
/*

+goTo(position) =0 (virtuelle pure)
+goToHome()
+resetPosition()
+getPosition()

*/

