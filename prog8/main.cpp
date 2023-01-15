#define FPS_LIMIT 60

//bibliotheque c++
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <cstdlib>
#include <ctime>

//Mingl 2
#include "mingl/mingl.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/rectangle.h"
#include "mingl/gui/sprite.h"

//En-tetes
#include "En-têtes/params.h"
#include "En-têtes/pacman.h"
#include "En-têtes/type.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;
using namespace chrono;
using namespace this_thread;
using namespace nsGui;

Vec2D PacmanPos;
CMyParam Param;

//=====| Initialisation struct des fantomes |=====

struct fantome
{
    string direction;
    bool peutChangeDeDir;
    int reposAvantChangeDir;
};

//===============================| Map |============================

void matriceInitPacman(vector <vector <char>> & matriceMap) /*source: Maxime TAMARIN*/
{
    matriceMap = {{'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',}, // X : mur , 0 : chemin avec pièce, - : porte fantome, ' ' : chemin sans pièce
                  {'X','0','0','0','0','0','0','X','0','0','0','0','0','0','X',}, // * : pouvoir parcman sur 10s
                  {'X','0','X','0','X','X','0','X','0','X','X','*','X','0','X',}, // / : intersection
                  {'X','0','*','0','0','0','0','0','0','*','0','0','0','0','X',},
                  {'X','0','X','X','X','X','X','0','X','X','X','X','X','0','X',},
                  {'X','0','0','0','0','*','0','0','0','0','0','0','0','0','X',},
                  {'X','X','0','X','0','X','X','-','X','X','0','X','0','X','X',},
                  {'0','0','0','X','0','X',' ',' ',' ','X','0','X','0','0','0',}, //millieu
                  {'X','0','X','X','0','X',' ',' ',' ','X','*','X','X','0','X',},
                  {'X','0','0','X','0','X','X','X','X','X','0','X','0','0','X',},
                  {'X','X','0','0','*','X','0','0','0','X','0','0','0','X','X',},
                  {'X','X','0','X','0','0','*','X','0','0','0','X','*','X','X',},
                  {'X','X','*','X','X','X','0','X','0','X','X','X','0','X','X',},
                  {'X','X','0','0','0','0','0','0','0','0','0','0','0','X','X',},
                  {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',}};

}

void matriceInitFantome(vector <vector <char>> & matriceMap) /*source: Maxime TAMARIN*/
{
    matriceMap = {{'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',}, // X : mur , - : porte fantome, ' ' : chemin sans pièce
                  {'X','/',' ','/',' ',' ','/','X','/',' ',' ','/',' ','/','X',}, // / : intersection
                  {'X',' ','X',' ','X','X',' ','X',' ','X','X',' ','X',' ','X',}, // , : sorti de la cage (direction mise à "haut")
                  {'X','/',' ','/',' ',' ','/','/','/',' ',' ','/',' ','/','X',},
                  {'X',' ','X','X','X','X','X',' ','X','X','X','X','X',' ','X',},
                  {'X','/','/',' ','/',' ',' ','/',' ',' ','/',' ','/','/','X',},
                  {'X','X',' ','X',' ','X','X','-','X','X',' ','X',' ','X','X',},
                  {' ','/','/','X',' ','X',' ','.',' ','X',' ','X','/','/',' ',}, //millieu
                  {'X',' ','X','X',' ','X',' ',' ',' ','X',' ','X','X',' ','X',},
                  {'X','/','/','X',' ','X','X','X','X','X',' ','X','/','/','X',},
                  {'X','X','/',' ','/','X','/',' ','/','X','/',' ','/','X','X',},
                  {'X','X',' ','X','/',' ','/','X','/',' ','/','X',' ','X','X',},
                  {'X','X',' ','X','X','X',' ','X',' ','X','X','X',' ','X','X',},
                  {'X','X','/',' ',' ',' ','/',' ','/',' ',' ',' ','/','X','X',},
                  {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X',}};

}

void afficheMat(vector <vector< char>> & mat) /*source: Maxime TAMARIN*/
{
    for (unsigned y = 0; y < mat.size(); ++y)
    {
        for (unsigned x = 0; x < mat[y].size(); ++x)
        {
            cout << mat[y][x];
        }
        cout << endl;
    }
}

void afficheMap(MinGL &window, vector <vector <char>> & mat,unsigned & pointMap) /*source: Maxime TAMARIN*/
{
    pointMap = 0;
    for (unsigned y = 0; y < mat.size(); ++y)
    {
        for (unsigned x = 0; x < mat[y].size(); ++x)
        {
            if (mat[y][x] == 'X')
            {
                window << Rectangle(Vec2D(x*50, y*50), Vec2D(x*50+50, y*50+50), Param.MapParamString.find("ColorMur")->second);
            }

            else if (mat[y][x] == '0')
            {
                window << Rectangle(Vec2D(x*50, y*50), Vec2D(x*50+50, y*50+50), Param.MapParamString.find("ColorChemin")->second);
                window << Circle(Vec2D(x*50+25,y*50+25), 5, Param.MapParamString.find("ColorPiece")->second);

                ++pointMap;
            }
            else if (mat[y][x] == '-')
            {
                window << Rectangle(Vec2D(x*50, y*50), Vec2D(x*50+50, y*50+50), Param.MapParamString.find("ColorChemin")->second);
                window << Rectangle(Vec2D(x*50, y*50), Vec2D(x*50+50, y*50+20), Param.MapParamString.find("ColorPorte")->second);

            }
            else if (mat[y][x] == ' ')
            {
                window << Rectangle(Vec2D(x*50, y*50), Vec2D(x*50+50, y*50+50), Param.MapParamString.find("ColorChemin")->second);
            }

            else if (mat[y][x] == '*')
            {
                window << Rectangle(Vec2D(x*50, y*50), Vec2D(x*50+50, y*50+50), Param.MapParamString.find("ColorChemin")->second);
                window << Circle(Vec2D(x*50+25,y*50+25), 13, Param.MapParamString.find("ColorPiece")->second);

                ++pointMap;
            }
        }
    }
}

//===============================| Pacman |============================

bool verificationCollision(vector <vector <char>> & mat, string & direction) /*Source: Maxime TAMARIN*/
{
    // regarde le haut
    if (direction == "haut")
    {
        if (mat[(PacmanPos.getY()-24)/50][PacmanPos.getX()/50] == 'X')
            return false;
        if (mat[(PacmanPos.getY()-24)/50][PacmanPos.getX()/50] == '-')
            return false;
        return true;
    }

    //regarde le bas
    if (direction == "bas")
    {
        if (mat[(PacmanPos.getY()+24)/50][PacmanPos.getX()/50] == 'X')
            return false;
        if (mat[(PacmanPos.getY()+24)/50][PacmanPos.getX()/50] == '-')
            return false;
        return true;
    }

    //regarde la droite
    if (direction == "droite")
    {
        if (mat[PacmanPos.getY()/50][(PacmanPos.getX()+25)/50] == 'X')
            return false;
        if (mat[PacmanPos.getY()/50][(PacmanPos.getX()+25)/50] == '-')
            return false;
        return true;
    }

    //regarde la droite
    if (direction == "gauche")
    {
        if (mat[PacmanPos.getY()/50][(PacmanPos.getX()-24)/50] == 'X')
            return false;
        if (mat[PacmanPos.getY()/50][(PacmanPos.getX()-24)/50] == '-')
            return false;
        return true;
    }
    return false; // au cas normalement non possible ou direction a une autre valeur
}

void deplacementPacman(MinGL & window, string & direction,vector <vector <char>> & mat,bool & pouvoirPacman) /* source: Alain casali + Maxime TAMARIN*/
{
    if (mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] == '*')
        pouvoirPacman = true;

    if ((PacmanPos.getX()+55)/50 == 0) // téléporte le pacman à droite
        PacmanPos.setX(800);

    if ((PacmanPos.getX()-55)/50 == 15) // téléporte le pacman à gauche
        PacmanPos.setX(0);

    if (verificationCollision(mat,direction))
    {

        // On vérifie si ZQSD est pressé, et met a jour la position et la direction
        if (window.isPressed({Param.MapParamChar.find("KeyUp")->second, false})) // regarde si prochaine case n'est pas interdite
        {
            direction = "haut";
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setY(PacmanPos.getY() - 3);
            else
                PacmanPos.setY(PacmanPos.getY() - 2);
        }
        else if (window.isPressed({Param.MapParamChar.find("KeyDown")->second, false}))
        {
            direction = "bas";
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setY(PacmanPos.getY() + 3);
            else
                PacmanPos.setY(PacmanPos.getY() + 2);
        }
        else if (window.isPressed({Param.MapParamChar.find("KeyLeft")->second, false}))
        {
            direction = "gauche";
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setX(PacmanPos.getX() - 3);
            else
                PacmanPos.setX(PacmanPos.getX() - 2);
        }
        else if (window.isPressed({Param.MapParamChar.find("KeyRight")->second, false}))
        {
            direction = "droite";
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setX(PacmanPos.getX() + 3);
            else
                PacmanPos.setX(PacmanPos.getX() + 2);
        }
        // si pas de touche pressé on continue à aller dans la même direction
        else if (direction == "haut")
        {
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setY(PacmanPos.getY() - 3);
            else
                PacmanPos.setY(PacmanPos.getY() - 2);
        }
        else if (direction == "bas" )
        {
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setY(PacmanPos.getY() + 3);
            else
                PacmanPos.setY(PacmanPos.getY() + 2);
        }
        else if (direction == "gauche")
        {
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setX(PacmanPos.getX() - 3);
            else
                PacmanPos.setX(PacmanPos.getX() - 2);
        }
        else if (direction == "droite")
        {
            mat[(PacmanPos.getY()/50)][PacmanPos.getX()/50] = ' ';
            if (pouvoirPacman)
                PacmanPos.setX(PacmanPos.getX() + 3);
            else
                PacmanPos.setX(PacmanPos.getX() + 2);
        }
    }
    else
    {
        //si bloqué dans un mur
        if (direction == "haut")
        {
            PacmanPos.setY(PacmanPos.getY() + 1);
        }
        else if (direction == "bas")
        {
            PacmanPos.setY(PacmanPos.getY() - 1);
        }
        else if (direction == "droite")
        {
            PacmanPos.setX(PacmanPos.getX() - 1);
        }
        else if (direction == "gauche")
        {
            PacmanPos.setX(PacmanPos.getX() + 1);
        }
    }
}
//===============================| Fantome |============================

void changementDirectionFantome(fantome & fantome, vector <vector <char>> & matFantome, Vec2D & fantomePos,bool & peutChangeDeDirection)
{

    int fantPosX = (fantomePos.getX())/50;
    int fantPosY = (fantomePos.getY())/50;
    if ((fantomePos.getX()+55)/50 == 0) // téléporte le fantome à droite
        fantomePos.setX(800);
    else if ((fantomePos.getX()-55)/50 == 15) // téléporte le fantome à gauche
        fantomePos.setX(0);

    if (matFantome[fantPosY][fantPosX] == '.' && peutChangeDeDirection) // cas particulié ou on est dans la cage des fantomes et donc pour les faire sortir
        fantome.direction = "haut";

    if (matFantome[fantPosY][fantPosX] == '/' && peutChangeDeDirection) // si c'est une intersection
    {
        char haut = matFantome[fantPosY-1][fantPosX];
        char bas = matFantome[fantPosY+1][fantPosX];
        char droite = matFantome[fantPosY][fantPosX+1];
        char gauche = matFantome[fantPosY][fantPosX-1];
        if(matFantome[fantPosY+1][fantPosX] == '-') //cas particulier quand on sort de la cage
        {
            if (rand()%3 == 0)
                fantome.direction = "gauche";
            else if (rand()%2 == 0)
                fantome.direction = "haut";
            else
                fantome.direction = "droite";
        }
        // si un mur en haut mais ouvert bas / droit / gauche
        else if (haut == 'X' && (bas == ' ' || bas == '/' ) && (droite == ' ' || droite == '/') && (gauche == ' ' || gauche == '/'))
        {
            if (rand()%3 == 0)
                fantome.direction = "gauche";
            else if (rand()%2 == 0)
                fantome.direction = "bas";
            else
                fantome.direction = "droite";
        }
        // si mur en bas mais ouvert haut / droite / gauche
        else if (bas == 'X' && (haut == ' ' || haut == '/' ) && (droite == ' ' || droite == '/') && (gauche == ' ' || gauche == '/'))
        {
            if (rand()%3 == 0)
                fantome.direction = "gauche";
            else if (rand()%2 == 0)
                fantome.direction = "haut";
            else
                fantome.direction = "droite";
        }
        // si mur à droite mais ouvert haut / bas / gauche
        else if (droite == 'X' && (haut == ' ' || haut == '/' ) && (bas == ' ' || bas == '/') && (gauche == ' ' || gauche == '/'))
        {
            if (rand()%3 == 0)
                fantome.direction = "gauche";
            else if (rand()%2 == 0)
                fantome.direction = "haut";
            else
                fantome.direction = "bas";
        }
        // si mur à gauche mais ouvert haut / bas / droite
        else if (gauche == 'X' && (haut == ' ' || haut == '/' ) && (bas == ' ' || bas == '/') && (droite == ' ' || droite == '/'))
        {
            if (rand()%3 == 0)
                fantome.direction = "droite";
            else if (rand()%2 == 0)
                fantome.direction = "haut";
            else
                fantome.direction = "bas";
        }
        // si mur haut / droite mais bas / gauche
        else if (droite == 'X' && haut == 'X' && (bas == ' ' || bas == '/') && (gauche == ' ' || gauche == '/'))
        {
            if (rand()%2 == 0)
                fantome.direction = "gauche";
            else
                fantome.direction = "bas";
        }
        // si mur haut / gauche mais bas / droite
        else if (gauche == 'X' && haut == 'X' && (bas == ' ' || bas == '/') && (droite == ' ' || droite == '/'))
        {
            if (rand()%2 == 0)
                fantome.direction = "droite";
            else
                fantome.direction = "bas";
        }
        // si mur bas / gauche mais haut / droite
        else if (bas == 'X' && gauche == 'X' && (haut == ' ' || haut == '/') && (droite == ' ' || droite == '/'))
        {
            if (rand()%2 == 0)
                fantome.direction = "droite";
            else
                fantome.direction = "haut";
        }
        // si mur bas / droite mais haut / gauche
        else if (droite == 'X' && bas == 'X' && (haut == ' ' || haut == '/') && (gauche == ' ' || gauche == '/'))
        {
            if (rand()%2 == 0)
                fantome.direction = "gauche";
            else
                fantome.direction = "haut";
        }
    }
    peutChangeDeDirection = false;
}

void deplacementFantome(fantome & fantome,Vec2D & fantomePos)
{
    if (fantome.direction == "haut")
        fantomePos.setY(fantomePos.getY()-1);
    if (fantome.direction == "droite")
        fantomePos.setX(fantomePos.getX()+1);
    if (fantome.direction == "gauche")
        fantomePos.setX(fantomePos.getX()-1);
    if (fantome.direction == "bas")
        fantomePos.setY(fantomePos.getY()+1);
}

//===============================| relation pacman et fantome|============================

int pacmanCollisionFantome(Vec2D & fantomePos, unsigned & point,bool & pacmanPouvoir,fantome & fantome)
{
    if (PacmanPos.getX()/30 == fantomePos.getX()/30 && PacmanPos.getY()/30 == fantomePos.getY()/30 && !pacmanPouvoir)
    {
        cout << "fin de la parti pacman a perdu" << endl;
        return 0; // si perdu
    }
    else if (PacmanPos.getX()/25 == fantomePos.getX()/25 && PacmanPos.getY()/25 == fantomePos.getY()/25 && pacmanPouvoir)
    {
        fantome.direction = "haut";
        fantomePos.setX(375);
        fantomePos.setY(425);
    }
    else if (point == 0)
    {
        cout << "fin de la parti pacman a gagné" << endl;
        return 1;
    }
    return -1;
}

//===============================| main() |============================


int main()  /* source: Alain casali + Maxime TAMARIN*/
{
    // Initialise le système
    MinGL window("SAE 1.02", Vec2D(750, 750), Vec2D(128, 128), KBlack);
    window.initGlut();
    window.initGraphic();

//=====| Initialisation Map |=====

    vector <vector <char>> mapPacman;
    vector <vector <char>> mapFantome;
    matriceInitPacman(mapPacman);
    matriceInitFantome(mapFantome);
    afficheMat(mapPacman);

//=====| Initialisation Pacman |=====

    //Initialise la position du pacman
    PacmanPos.setX(75);
    PacmanPos.setY(75);

    //Initialise la bouche du pacman à false
    bool boucheOuverte = false;

    //Initialisation direction pacman
    string direction = "droite";

    //Initialisation pouvoir pacman à false
    bool pouvoirPacman = false;
    unsigned PouvoirTemp = 1;

//=====| Initialisation Fantome |=====

    //initialisation des fantomes via le struct
    fantome fantome1;
    fantome fantome2;
    fantome fantome3;

    //initialisation vec2D
    Vec2D fantome1Pos;
    Vec2D fantome2Pos;
    Vec2D fantome3Pos;

    //Initialise la position du fantome
    fantome1Pos.setX(375);
    fantome1Pos.setY(425);

    fantome2Pos.setX(325);
    fantome2Pos.setY(375);

    fantome3Pos.setX(425);
    fantome3Pos.setY(375);

    //Initialise la directionc
    fantome1.direction = "haut";
    fantome2.direction = "droite";
    fantome3.direction = "gauche";

    //Initialisation variable de tempo après un changement de direction
    fantome1.peutChangeDeDir = true;
    fantome1.reposAvantChangeDir = 1;

    fantome2.peutChangeDeDir = true;
    fantome2.reposAvantChangeDir = 1;

    fantome3.peutChangeDeDir = true;
    fantome3.reposAvantChangeDir = 1;

//=====| Autre Initialisation |=====

    // fin du jeux
    int finDeJeu;
    //initialisation paramètre
    InitParams(Param);

    // nombre de point sur la map (quand = 0 fin)
    unsigned pointMap;

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

        afficheMap(window,mapPacman,pointMap); //affiche le visuel de la map


        // direction des fantomes
        srand(time(NULL)); // génère une graine différente à chaque execution pour avoir un nombre réellement aléatoire.
        //fantome 1
        changementDirectionFantome(fantome1,mapFantome,fantome1Pos,fantome1.peutChangeDeDir); //regarde si le fantome peut changer de direction
        if (fantome1.reposAvantChangeDir%50 == 0) // permet de ne pas bloqué le fantome sur une case
            fantome1.peutChangeDeDir = true;
        ++fantome1.reposAvantChangeDir;
        deplacementFantome(fantome1,fantome1Pos); //fonction qui gère le déplacement du fantome

        srand(rand()); // génère une graine différente à chaque execution pour avoir un nombre réellement aléatoire.
        //fantome 2
        changementDirectionFantome(fantome2,mapFantome,fantome2Pos,fantome2.peutChangeDeDir); //regarde si le fantome peut changer de direction
        if (fantome2.reposAvantChangeDir%50 == 0) // permet de ne pas bloqué le fantome sur une case
            fantome2.peutChangeDeDir = true;
        ++fantome2.reposAvantChangeDir;
        deplacementFantome(fantome2,fantome2Pos); //fonction qui gère le déplacement du fantome

        srand(rand()); // génère une graine différente à chaque execution pour avoir un nombre réellement aléatoire.
        // fantome 3
        changementDirectionFantome(fantome3,mapFantome,fantome3Pos,fantome3.peutChangeDeDir); //regarde si le fantome peut changer de direction
        if (fantome3.reposAvantChangeDir%50 == 0) // permet de ne pas bloqué le fantome sur une case
            fantome3.peutChangeDeDir = true;
        ++fantome3.reposAvantChangeDir;
        deplacementFantome(fantome3,fantome3Pos); //fonction qui gère le déplacement du fantome


        deplacementPacman(window,direction,mapPacman,pouvoirPacman); //regarde les touches appuyées et si la direction du pacman doit changer ou non

        affichePacman(PacmanPos.getX(),PacmanPos.getY(),window, boucheOuverte,direction,pouvoirPacman,Param); // affiche pacman en fonction d'une position
        if (frame%15 == 0) // toute les 15 execution (1/4 de seconde) on change l'état de la bouche
            boucheOuverte = !boucheOuverte;

        if (pointMap == 0) //quand plus de point sur la map à manger
            matriceInitPacman(mapPacman);

        if (pouvoirPacman)
        {
            if (PouvoirTemp%360 == 0) // 360 images = 6 secondes
            {
                pouvoirPacman = false;
                PouvoirTemp = 1;
            }
            else
                ++PouvoirTemp;
        }

        //affichage console
        cout << "point restant: " <<pointMap << endl; // point restant sur la map à manger
        cout << "statut pouvoir pacman: " <<pouvoirPacman << endl << endl;

        //instancie sprite
        Sprite fant1("../prog8/autre fichier/fantome4.si2", Vec2D(fantome1Pos.getX()-25,fantome1Pos.getY()-25));
        Sprite fant2("../prog8/autre fichier/fantome3.si2", Vec2D(fantome2Pos.getX()-25,fantome2Pos.getY()-25 ));
        Sprite fant3("../prog8/autre fichier/fantome2.si2", Vec2D(fantome3Pos.getX()-25,fantome3Pos.getY()-25 ));
        window << fant1 << fant2 << fant3;

        ++frame;

        finDeJeu = pacmanCollisionFantome(fantome1Pos, pointMap,pouvoirPacman,fantome1);
        if (finDeJeu == 0 || finDeJeu == 1)
            exit(finDeJeu);
        finDeJeu = pacmanCollisionFantome(fantome2Pos, pointMap,pouvoirPacman,fantome2);
        if (finDeJeu == 0 || finDeJeu == 1)
            exit(finDeJeu);
        finDeJeu = pacmanCollisionFantome(fantome3Pos, pointMap,pouvoirPacman,fantome3);
        if (finDeJeu == 0 || finDeJeu == 1)
            exit(finDeJeu);

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
