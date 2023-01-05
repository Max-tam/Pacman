#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

#include "mingl/mingl.h"
#include "mingl/gui/sprite.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/triangle.h"

#include "En-têtes/pacman.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;

void affichePacman(const unsigned & posX,const unsigned & posY, MinGL &window,bool boucheOuverte, string & direction) // affiche un pacman au coordonnée donnée
{
    // Si pacman va vers la droite
    if (direction == "droite")
    {
        //si pacman a la bouche ouverte
        if (boucheOuverte)
        {
            window << Circle(Vec2D(posX,posY), 20, KYellow); // corp du pacman
            window << Circle(Vec2D(posX,posY-10), 2, KBlack); // oeil du pacman
            window << Triangle(Vec2D(posX,posY), Vec2D(posX+15,posY-14), Vec2D(posX+20,posY-7), KBlack); // partie de bouche 1
            window << Triangle(Vec2D(posX,posY), Vec2D(posX+20,posY-7), Vec2D(posX+22,posY), KBlack); // partie de bouche 2
            window << Triangle(Vec2D(posX,posY), Vec2D(posX+22,posY), Vec2D(posX+20,posY+7), KBlack); // partie de bouche 3
            window << Triangle(Vec2D(posX,posY), Vec2D(posX+20,posY+7), Vec2D(posX+15,posY+14), KBlack); // partie de bouche 4
        }
        //si pacman à la bouche fermée
        else
        {
            window << Circle(Vec2D(posX,posY), 20, KYellow); // corp du pacman
            window << Circle(Vec2D(posX,posY-10), 2, KBlack); // oeil du pacman
        }
    }
    // si pacman va vers la gauche
    else if (direction == "gauche")
    {
        // si pacman a la bouche ouverte
        if (boucheOuverte)
        {
            window << Circle(Vec2D(posX,posY), 20, KYellow); // corp du pacman
            window << Circle(Vec2D(posX,posY-10), 2, KBlack); // oeil du pacman
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-15,posY-14), Vec2D(posX-20,posY-7), KBlack); // partie de bouche 1
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-20,posY-7), Vec2D(posX-22,posY), KBlack); // partie de bouche 2
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-22,posY), Vec2D(posX-20,posY+7), KBlack); // partie de bouche 3
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-20,posY+7), Vec2D(posX-15,posY+14), KBlack); // partie de bouche 4
        }
        // si pacman a la bouche fermée
        else
        {
            window << Circle(Vec2D(posX,posY), 20, KYellow); // corp du pacman
            window << Circle(Vec2D(posX,posY-10), 2, KBlack); // oeil du pacman
        }
    }
    // si pacman va vers le bas
    else if (direction == "bas")
    {
        // si pacman a la bouche ouverte
        if (boucheOuverte)
        {
            window << Circle(Vec2D(posX,posY), 20, KYellow); // corp du pacman
            window << Circle(Vec2D(posX+10,posY), 2, KBlack); // oeil du pacman
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-14,posY+15), Vec2D(posX-7,posY+20), KBlack); // partie de bouche 1
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-7,posY+20), Vec2D(posX,posY+22), KBlack); // partie de bouche 2
            window << Triangle(Vec2D(posX,posY), Vec2D(posX,posY+22), Vec2D(posX+7,posY+20), KBlack); // partie de bouche 3
            window << Triangle(Vec2D(posX,posY), Vec2D(posX+7,posY+20), Vec2D(posX+14,posY+15), KBlack); // partie de bouche 4
        }
        // si pacman a la bouche fermée
        else
        {
            window << Circle(Vec2D(posX,posY), 20, KYellow); // corp du pacman
            window << Circle(Vec2D(posX+10,posY), 2, KBlack); // oeil du pacman
        }
    }
    // si pacman va vers le haut
    else if (direction == "haut")
    {
        // si pacman a la bouche ouverte
        if (boucheOuverte)
        {
            window << Circle(Vec2D(posX,posY), 20, KYellow); // corp du pacman
            window << Circle(Vec2D(posX-10,posY), 2, KBlack); // oeil du pacman
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-14,posY-15), Vec2D(posX-7,posY-20), KBlack); // partie de bouche 1
            window << Triangle(Vec2D(posX,posY), Vec2D(posX-7,posY-20), Vec2D(posX,posY-22), KBlack); // partie de bouche 2
            window << Triangle(Vec2D(posX,posY), Vec2D(posX,posY-22), Vec2D(posX+7,posY-20), KBlack); // partie de bouche 3
            window << Triangle(Vec2D(posX,posY), Vec2D(posX+7,posY-20), Vec2D(posX+14,posY-15), KBlack); // partie de bouche 4
        }
        // si pacman a la bouche fermée
        else
        {
            window << Circle(Vec2D(posX,posY), 20, KYellow); // corp du pacman
            window << Circle(Vec2D(posX-10,posY), 2, KBlack); // oeil du pacman
        }
    }
}
