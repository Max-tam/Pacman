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

void pacman(const unsigned & posX,const unsigned & posY, MinGL &window) // affiche un pacman au coordonnée donnée
{
    window << Circle(Vec2D(posX,posY), 20, KYellow); //( coordonée (centre pacman sur X, centre parcman sur Y) , radius )
    window << Circle(Vec2D(posX,posY-10), 2, KBlack);
    window << Triangle(Vec2D(posX,posY), Vec2D(posX+15,posY-14), Vec2D(posX+20,posY-7), KBlack); // (coordonée centre pacman ,point supérieur droit, point inférieur droit)
    window << Triangle(Vec2D(posX,posY), Vec2D(posX+20,posY-7), Vec2D(posX+22,posY), KBlack);
    window << Triangle(Vec2D(posX,posY), Vec2D(posX+22,posY), Vec2D(posX+20,posY+7), KBlack);
    window << Triangle(Vec2D(posX,posY), Vec2D(posX+20,posY+7), Vec2D(posX+15,posY+14), KBlack);
}

void dessiner(MinGL &window)
{

    //positionnement pacman

    pacman(PacmanPos.getX(),PacmanPos.getY(),window);


    // N'hésitez pas a lire la doc pour plus de détails.
}

void clavier(MinGL & window)
{
    // On vérifie si ZQSD est pressé, et met a jour la position
    if (window.isPressed({'z', false}))
        PacmanPos.setY(PacmanPos.getY() - 1);
    if (window.isPressed({'s', false}))
        PacmanPos.setY(PacmanPos.getY() + 1);
    if (window.isPressed({'q', false}))
        PacmanPos.setX(PacmanPos.getX() - 1);
    if (window.isPressed({'d', false}))
        PacmanPos.setX(PacmanPos.getX() + 1);
}

int main()
{
    // Initialise le système
    MinGL window("SAE 1.02", Vec2D(1280, 720), Vec2D(128, 128), KBlack);
    window.initGlut();
    window.initGraphic();

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
        clavier(window);
        dessiner(window);

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
