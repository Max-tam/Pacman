#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <vector>
#include <map>


struct AuthorizedKey
{
    const std::vector <std::string> VParamChar {"KeyUp", "KeyDown", "KeyLeft", "KeyRight"};
    const std::vector <std::string> VParamColorString {"ColorChemin", "ColorMur","ColorPorte","ColorPiece"};
    const std::vector <std::string> VParamConsommableChar {"pièce", "vide","pouvoir","spawn"};
    const std::vector <std::string> VParamCollisionChar {"mur", "porte"};
};

const AuthorizedKey KAuthorizedKey;

struct CMyParam {
std::map <std::string, char> MapParamChar;
std::map <std::string, std::string> MapParamColorString;
std::map <std::string, char> MapParamConsommableChar;
std::map <std::string, char> MapParamCollisionChar;
};



const std::map <std::string, std::string> KColor
{
  {"KReset", "0"},
  {"KBlack", "30"},
  {"KRed", "31"},
  {"KGreen", "32"},
  {"KYellow", "33"},
  {"KBlue", "34"},
  {"KMAgenta", "35"},
  {"KCyan", "36"},

};

#endif // TYPE_H
