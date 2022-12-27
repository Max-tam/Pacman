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

void pacman(const unsigned & posX,const unsigned & posY, MinGL &window) // affiche un pacman au coordonnée donnée
{
    window << Circle(Vec2D(posX,posY), 20, KYellow); //( coordonée (largeur,hauteur) , radius )
    window << Circle(Vec2D(posX,posY-10), 2, KBlack);
    window << Triangle(Vec2D(posX,posY), Vec2D(posX+15,posY-14), Vec2D(posX+20,posY-7), KBlack); // (coordonée centre pacman ,point supérieur, point inférieur droit)
    window << Triangle(Vec2D(posX,posY), Vec2D(posX+20,posY-7), Vec2D(posX+22,posY), KBlack);
    window << Triangle(Vec2D(posX,posY), Vec2D(posX+22,posY), Vec2D(posX+20,posY+7), KBlack);
    window << Triangle(Vec2D(posX,posY), Vec2D(posX+20,posY+7), Vec2D(posX+15,posY+14), KBlack);
}

void dessiner(MinGL &window)
{
    // Pour dessiner quelque chose avec minGL 2, vous pouvez soit instancier l'objet dans une variable et l'injecter dans la fenêtre...
    Rectangle rect1(Vec2D(20, 20), Vec2D(120, 120), KBlue);
    window << rect1;

    // ...ou l'injecter directement dans la fenêtre!
    window << Rectangle(Vec2D(50, 50), Vec2D(60, 60), KPurple);

    // (Vous voyez par ailleurs que l'ordre d'affichage est important, le rectangle violet masque maintenant une partie du rectangle bleu.)
    // Vous pouvez combiner les différentes formes disponibles pour faire des choses plus complexes.

    // un cercle

    window << Circle(Vec2D(300, 300), 150, KRed); //( coordonée , radius )

    // Voilà un bouton de fermeture.
    window << Circle(Vec2D(100, 320), 50, KRed);
    window << Line(Vec2D(70, 290), Vec2D(130, 350), KWhite, 3.f);
    window << Line(Vec2D(130, 290), Vec2D(70, 350), KWhite, 3.f);

    // Et voilà la triforce.
    window << Triangle(Vec2D(500, 150), Vec2D(400, 620), Vec2D(300, 420), KRed); // (coordonée point inféieur gauche,point supérieur, point inférieur droit)
    window << Triangle(Vec2D(400, 620), Vec2D(600, 620), Vec2D(500, 420), KRed);


    //pac man

    window << Circle(Vec2D(300,300), 20, KYellow); //( coordonée (largeur,hauteur) , radius )
    window << Circle(Vec2D(300,290), 2, KBlack);
    window << Triangle(Vec2D(300,300), Vec2D(315,286), Vec2D(320,293), KBlack); // (coordonée centre pacman ,point supérieur, point inférieur droit)
    window << Triangle(Vec2D(300,300), Vec2D(320,293), Vec2D(322,300), KBlack);
    window << Triangle(Vec2D(300,300), Vec2D(322,300), Vec2D(320,307), KBlack);
    window << Triangle(Vec2D(300,300), Vec2D(320,307), Vec2D(315,314), KBlack);

    //test fonction pacman

    pacman(450,200,window);

    // N'hésitez pas a lire la doc pour plus de détails.
}


void initVect (vector<unsigned> & V, const size_t & _size, const unsigned & min, const unsigned & max)
{
    V.resize(_size);
    for (unsigned & val : V)
        val = min + rand() % (max - min);
}

unsigned maxElemem (const vector<unsigned> & V)
{
    return *max_element (V.begin(), V.end());
}

template <typename T>
void histogrammeVector (const vector <T> & V, MinGL & window)
{
    vector <T> triedV = V;
    for (size_t i (0); i < V.size(); ++i )
    {
        unsigned max = maxElemem(triedV);
        window << Rectangle (Vec2D(30*i, 200), Vec2D(30*(i)+25, 200-(max*10)), KWhite);
        triedV.erase(max_element(triedV.begin(), triedV.end()));
    }
}


//int exo2()
//{
//    srand (time(nullptr));

//    vector <unsigned> V;
//    unsigned maxAGenerer (20);
//    initVect (V, 10, 1, maxAGenerer);
//    affichVector(V);
//    // Initialise le système
//    MinGL window("prog8", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
//    window.initGlut();
//    window.initGraphic();

//    // Variable qui tient le temps de frame
//    chrono::microseconds frameTime = chrono::microseconds::zero();

//    // On fait tourner la boucle tant que la fenêtre est ouverte
//    while (window.isOpen())
//    {
//        // Récupère l'heure actuelle
//        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

//        // On efface la fenêtre
//        window.clearScreen();

//        // On dessine les formes géométriques
////        window << nsShape::Rectangle (nsGraphics::Vec2D(0, 200), nsGraphics::Vec2D(25, 190), nsGraphics::KRed);
////        window << nsShape::Rectangle (nsGraphics::Vec2D(30+0, 200), nsGraphics::Vec2D(30+25, 180), nsGraphics::KRed);
//        histogrammeVector(V, window);

//        // On finit la frame en cours
//        window.finishFrame();

//        // On vide la queue d'évènements
//        window.getEventManager().clearEvents();

//        // On attend un peu pour limiter le framerate et soulager le CPU
//        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

//        // On récupère le temps de frame
//        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
//    }
//    return 0;
//}


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

        // On dessine les formes géométriques
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
