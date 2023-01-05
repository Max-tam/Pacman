#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;

Vec2D PacmanPos;

void pacman(const unsigned & posX,const unsigned & posY, MinGL &window,bool boucheOuverte, string & direction) // affiche un pacman au coordonnée donnée
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

//void dessiner(MinGL &window, bool boucheOuverte)
//{

//}

void clavier(MinGL & window, string & direction)
{
    // On vérifie si ZQSD est pressé, et met a jour la position et la direction
    if (window.isPressed({'z', false}))
    {
        PacmanPos.setY(PacmanPos.getY() - 2);
        direction = "haut";
    }
    else if (window.isPressed({'s', false}))
    {
        PacmanPos.setY(PacmanPos.getY() + 2);
        direction = "bas";
    }
    else if (window.isPressed({'q', false}))
    {
        PacmanPos.setX(PacmanPos.getX() - 2);
        direction = "gauche";
    }
    else if (window.isPressed({'d', false}))
    {
        PacmanPos.setX(PacmanPos.getX() + 2);
        direction = "droite";
    }
    // si pas de touche pressé on continue à aller dans la même direction
    else if (direction == "haut")
        PacmanPos.setY(PacmanPos.getY() - 2);
    else if (direction == "bas")
        PacmanPos.setY(PacmanPos.getY() + 2);
    else if (direction == "gauche")
        PacmanPos.setX(PacmanPos.getX() - 2);
    else if (direction == "droite")
        PacmanPos.setX(PacmanPos.getX() + 2);
}

int main()
{
    // Initialise le système
    MinGL window("SAE 1.02", Vec2D(1280, 720), Vec2D(128, 128), KBlack);
    window.initGlut();
    window.initGraphic();

    //Initialise la position du pacman
    PacmanPos.setX(50);
    PacmanPos.setY(50);

    //Initialise la bouche du pacman à true
    bool boucheOuverte = false;
    unsigned frame = 0;

    //Initialisation direction pacman
    string direction = "droite";

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On execute les processus

        //positionnement pacman

        clavier(window,direction);

        pacman(PacmanPos.getX(),PacmanPos.getY(),window, boucheOuverte,direction);
        if (frame%15 == 0)
            boucheOuverte = !boucheOuverte;
        ++frame;


        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }

    return 0;
}
