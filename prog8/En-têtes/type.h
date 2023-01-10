#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <vector>
#include <map>

#include "mingl/mingl.h"

struct AuthorizedKey
{
    const std::vector <std::string> VParamChar {"KeyUp", "KeyDown", "KeyLeft", "KeyRight"};
    const std::vector <std::string> VParamColorString {"ColorChemin", "ColorMurs","ColorPorte","ColorPiece","ColorPacmanEnerve","ColorPacman"};
    const std::vector <std::string> VParamConsommableChar {"pièce", "vide","pouvoir"};
    const std::vector <std::string> VParamCollisionChar {"mur", "porte"};
};

const AuthorizedKey KAuthorizedKey;

struct CMyParam {
std::map <std::string, char> MapParamChar;
std::map <std::string, nsGraphics::RGBAcolor> MapParamString;
std::map <std::string, char> MapParamConsommableChar;
std::map <std::string, char> MapParamCollisionChar;
};


#endif // TYPE_H
