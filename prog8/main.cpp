#define FPS_LIMIT 60

//bibliotheque c++
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

//Mingl 2
#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"

//En-tetes
#include "En-têtes/pacman.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;
using namespace chrono;
using namespace this_thread;

Vec2D PacmanPos;

void matriceInit(vector <vector <char>> & matriceMap) /*source: Maxime TAMARIN*/
{
    matriceMap = {{'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',}, // X : mur , 0 : chemin, - : porte fantome
                  {'X','0','0','0','0','0','0','X','0','0','0','0','0','0','X',},
                  {'X','0','X','0','X','X','0','X','0','X','X','0','X','0','X',},
                  {'X','0','0','0','0','0','0','0','0','0','0','0','0','0','X',},
                  {'X','0','X','X','X','X','X','0','X','X','X','X','X','0','X',},
                  {'X','0','0','0','0','0','0','0','0','0','0','0','0','0','X',},
                  {'X','X','0','X','0','X','X','-','X','X','0','X','0','X','X',},
                  {'0','0','0','X','0','X','0','0','0','X','0','X','0','0','0',}, //millieu
                  {'X','0','X','X','0','X','0','0','0','X','0','X','X','0','X',},
                  {'X','0','0','X','0','X','X','X','X','X','0','X','0','0','X',},
                  {'X','X','0','0','0','X','0','0','0','X','0','0','0','X','X',},
                  {'X','X','0','X','0','0','0','X','0','0','0','X','0','X','X',},
                  {'X','X','0','X','X','X','0','X','0','X','X','X','0','X','X',},
                  {'X','X','0','0','0','0','0','0','0','0','0','0','0','X','X',},
                  {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',}};

}

void afficheMat(vector <vector< char>> & mat) /*source: Maxime TAMARIN*/
{
    for (unsigned i = 0; i < mat.size(); ++i)
    {
        for (unsigned j = 0; j < mat[i].size(); ++j)
        {
            cout << mat[i][j];
        }
        cout << endl;
    }
}

void afficheMap(MinGL &window, vector <vector <char>> & mat) /*source: Maxime TAMARIN*/
{
    for (unsigned i = 0; i < mat.size(); ++i)
    {
        for (unsigned j = 0; j < mat[i].size(); ++j)
        {
            if (mat[i][j] == 'X')
                window << Rectangle(Vec2D(j*50, i*50), Vec2D(j*50+50, i*50+50), KBlue);
            else if (mat[i][j] == '0')
                window << Rectangle(Vec2D(j*50, i*50), Vec2D(j*50+50, i*50+50), KBlack);
            else if (mat[i][j] == '-')
                window << Rectangle(Vec2D(j*50, i*50), Vec2D(j*50+50, i*50+20), KPurple);
        }
    }
}

void clavier(MinGL & window, string & direction) /* source: Alain casali + Maxime TAMARIN*/
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

int main()  /* source: Alain casali + Maxime TAMARIN*/
{
    // Initialise le système
    MinGL window("SAE 1.02", Vec2D(750, 750), Vec2D(128, 128), KBlack);
    window.initGlut();
    window.initGraphic();

//=====| Initialisation Map |=====

    vector <vector <char>> map;
    matriceInit(map);
    afficheMat(map);


//=====| Initialisation Pacman |=====

    //Initialise la position du pacman
    PacmanPos.setX(50);
    PacmanPos.setY(50);

        //Initialise la bouche du pacman à false
        bool boucheOuverte = false;

//=====| Autre Initialisation |=====

    //Initialisation direction pacman
    string direction = "droite";

    // frame = nombre d'execution (comme 60FPS alors 60 execution / seconde)
    unsigned frame = 0;

    // Variable qui tient le temps de frame
    microseconds frameTime = microseconds::zero();

//=====| Boucle infini de la fenêtre |=====

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        time_point<steady_clock> start = steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On execute les processus

        afficheMap(window,map);

        clavier(window,direction); //regarde les touches appuyées et si la direction du pacman doit changer ou non

        affichePacman(PacmanPos.getX(),PacmanPos.getY(),window, boucheOuverte,direction); // affiche pacman en fonction d'une position
        if (frame%15 == 0) // toute les 15 execution (1/4 de seconde) on change l'état de la bouche
            boucheOuverte = !boucheOuverte;


        ++frame;

//        nsGui::Sprite doggo("../prog8/pac.si2",Vec2D(0,0));
//        window << doggo;

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        sleep_for(milliseconds(1000 / FPS_LIMIT) - duration_cast<microseconds>(steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = duration_cast<microseconds>(steady_clock::now() - start);
    }

    return 0;
}
