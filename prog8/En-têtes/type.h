/**
 * \file type.h
 * \author {TAMARIN Maxime, ROUBAUD Axel, BOSSO Gavril, JAURAS Maxime, Alain Casali}
 * \version 0.1
 * \date 15 janvier 2023
 */

#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <vector>
#include <map>

#include "mingl/mingl.h"

/**
* \struct AuthorizedKey
*/
struct AuthorizedKey
{
    const std::vector <std::string> VParamChar {"KeyUp", "KeyDown", "KeyLeft", "KeyRight"};
    const std::vector <std::string> VParamString {"ColorChemin", "ColorMurs","ColorPorte","ColorPiece","ColorPacmanEnerve","ColorPacman"};
    const std::vector <std::string> VParamConsommableChar {"pièce", "vide","pouvoir"};
    const std::vector <std::string> VParamCollisionChar {"mur", "porte"};
};

const AuthorizedKey KAuthorizedKey;

/**
* \struct CMyParam
*/
struct CMyParam
{
std::map <std::string, char> MapParamChar;
std::map <std::string, nsGraphics::RGBAcolor> MapParamString;
std::map <std::string, char> MapParamConsommableChar;
std::map <std::string, char> MapParamCollisionChar;
};


#endif // TYPE_H
