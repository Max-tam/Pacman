#ifndef PACMAN_H
#define PACMAN_H

#include <iostream>

#include "mingl/mingl.h"

using namespace std;

void affichePacman(const unsigned & posX,const unsigned & posY, MinGL &window,bool boucheOuverte, string & direction);

#endif // PACMAN_H
