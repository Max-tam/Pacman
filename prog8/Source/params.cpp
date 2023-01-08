#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <mingl/mingl.h>

#include "En-têtes/params.h"
#include "En-têtes/type.h"

using namespace std;
using namespace nsGraphics;


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
                nsGraphics::RGBAcolor valeur;
                while (true)
                {
                    if (i == line.size())
                    {
                        break;
                    }
                    valeur = valeur + line[i];
                    ++i;
                }
                Param.MapParamString[cle] = valeur ;
            }
        }
        ifs.close();

    }

}

// faire fonction qui avec
