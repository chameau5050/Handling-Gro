/*********************************************************
Fichier     : Join.cpp
Auteur      : Jérémy Giguère
Date        : 27 janvier 2021
Description : fichier qui represente les attribut pour la classe abstraite joint
**********************************************************/

#include "Join.h"

Join::Join(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche)
{
    this->position = position;
    this->limite = limite;
    this->homePosition = homePosition;
    this->LimiteSwitchPinDroit = LimiteSwitchPinDroit;
    this->LimiteSwitchPinGauche = LimiteSwitchPinGauche;    
}

Join::~Join()
{

}

void Join::goToHome()
{
    goTo(homePosition);
}

void Join::resetPosition()
{
    //goTo() : attendre l'ajout des bumper
    position = 0;
}

int Join::getPosition()
{
    return position;
}

int Join::getLimite()
{
    return limite;
}

void Join::setLimite(int newLimite)
{
    limite = newLimite;
}

void Join::setHome(int newHomePosition)
{
    homePosition = newHomePosition;
}

int Join::getHome()
{
    return homePosition;
}