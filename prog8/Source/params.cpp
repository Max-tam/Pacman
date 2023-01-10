#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <mingl/mingl.h>

#include "En-têtes/params.h"
#include "En-têtes/type.h"

using namespace std;
using namespace nsGraphics;

RGBAcolor ConvertStringRGBAcolor(string & text)
{
    if (text == "KBlack")
        return KBlack;
    if (text == "KYellow")
        return KYellow;
    if (text == "KGreen")
        return KGreen;
    if (text == "KBlue")
        return KBlue;
    if (text == "KRed")
        return KRed;
    if (text == "KPurple")
        return KPurple;
    if (text == "KWhite")
        return KWhite;
    return KBlack; // pas défaut
}

void LoadParams (CMyParam & Param)
{
    string line;
    string cle;
    ifstream ifs("../PacMan/Nos_fichiers/config.yaml");

    if(ifs.is_open())
    {
        while (true)
        {
            getline (ifs, line);
            if (ifs.eof ()) break;

            unsigned i = 0;
            cle = "";
            while (true)
            {
                if (line[i] == ' ')
                {
                    break;
                }
                cle = cle + line[i];
                ++i;
            }
            i = i + 3; // on passe de l'autre côté du ':'

            // on cherche la clé
            if (*find(KAuthorizedKey.VParamChar.begin(),KAuthorizedKey.VParamChar.end(),cle) == cle) //pour valeur char
            {
                char valeur = line[i];
                Param.MapParamChar[cle] = valeur;
            }
            else if (*find(KAuthorizedKey.VParamColorString.begin(),KAuthorizedKey.VParamColorString.end(),cle) == cle)
            {
                string valeurString;
                while (true)
                {
                    if (i == line.size())
                    {
                        break;
                    }
                    valeurString = valeurString + line[i];
                    ++i;
                }
                RGBAcolor valeur = ConvertStringRGBAcolor(valeurString);
                Param.MapParamString[cle] = valeur ;
            }
        }
        ifs.close();

    }

}

void InitParams (CMyParam & Param) /*Gavril prof correction*/
{
//Move Keys
Param.MapParamChar["KeyUp"] = 'z';
Param.MapParamChar["KeyDown"] = 's';
Param.MapParamChar["KeyLeft"] = 'q';
Param.MapParamChar["KeyRight"] = 'd';

//Display Colors
Param.MapParamString["ColorChemin"] = KBlack;
Param.MapParamString["ColorMur"] = KBlue;
Param.MapParamString["ColorPorte"] = KPurple;
Param.MapParamString["ColorPiece"] = KYellow;
Param.MapParamString["ColorPacmanEnerve"] = KRed;
Param.MapParamString["ColorPacman"] = KYellow;

// Consommable
Param.MapParamConsommableChar["pièce"] = '0';
Param.MapParamConsommableChar["vide"] = ' ';
Param.MapParamConsommableChar["pouvoir"] = '*';
Param.MapParamConsommableChar["spawn"] = '.';

//collision
Param.MapParamCollisionChar["mur"] = 'X';
Param.MapParamCollisionChar["porte"] = '-';
//LoadParams(Param); // on verifie si dans le fichier des informations ne sont pas différente
}

// faire fonction qui avec
