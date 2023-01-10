#ifndef PACMAN_H
#define PACMAN_H

#include <iostream>

#include "mingl/mingl.h"

#include "type.h"

using namespace std;

void affichePacman(const unsigned & posX,const unsigned & posY, MinGL &window,bool boucheOuverte, string & direction,bool & pouvoirPacman, CMyParam & Param);

#endif // PACMAN_H
