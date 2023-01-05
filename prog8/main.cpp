#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

#include "mingl/mingl.h"

#include "En-têtes/pacman.h"

using namespace std;
using namespace nsGraphics;

Vec2D PacmanPos;


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
    MinGL window("SAE 1.02", Vec2D(750, 750), Vec2D(128, 128), KBlack);
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

        clavier(window,direction);

        affichePacman(PacmanPos.getX(),PacmanPos.getY(),window, boucheOuverte,direction);
        if (frame%15 == 0)
            boucheOuverte = !boucheOuverte;
        ++frame;

//        nsGui::Sprite doggo("../prog8/pac.si2",Vec2D(0,0));
//        window << doggo;

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
