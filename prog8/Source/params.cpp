#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "En-têtes/params.h"
#include "En-têtes/type.h"

using namespace std;


void InitParams (CMyParam & Param) /*Gavril prof correction*/
{
//Move Keys
Param.MapParamChar["KeyUp"] = 'z';
Param.MapParamChar["KeyDown"] = 's';
Param.MapParamChar["KeyLeft"] = 'q';
Param.MapParamChar["KeyRight"] = 'd';

//Display Colors
Param.MapParamColorString["ColorChemin"] = KColor.find("KBlack")->second ;
Param.MapParamColorString["ColorMur"] = KColor.find("KBlue")->second ;
Param.MapParamColorString["ColorPorte"] = KColor.find("KPurple")->second ;
Param.MapParamColorString["ColorPiece"] = KColor.find("KYellow")->second ;
Param.MapParamColorString["ColorPacmanEnerve"] = KColor.find("KRed")->second ;
Param.MapParamColorString["ColorPacman"] = KColor.find("KYellow")->second ;

// Consommable
Param.MapParamConsommableChar["pièce"] = '0';
Param.MapParamConsommableChar["vide"] = ' ';
Param.MapParamConsommableChar["pouvoir"] = '*';
Param.MapParamConsommableChar["pouvoir"] = '.';

//collision
Param.MapParamCollisionChar["mur"] = 'X';
Param.MapParamCollisionChar["porte"] = '-';
//LoadParams(Param); // on verifie si dans le fichier des informations ne sont pas différente
}

void loadparam (CMyParam & Param) /*Sources Gavril / Prof correction prog13*/
{
    ifstream ifs("../prog8/autre fichier/config.yaml");
    if (!ifs)
    {
        cerr << "le fichier de configuration est pas ouvert" << endl ;
        exit(-1);
    }
    cout << "fichier ouvert" << endl;
    for(string cle, poubelle; ifs >> cle;)
    {
        char deuxpoints;
        ifs >> deuxpoints;
        if(*find(KAuthorizedKey.VParamChar.begin(), KAuthorizedKey.VParamChar.end(), cle) == cle)
        {
            char val;
            ifs >> val;
            Param.MapParamChar[cle] = val;
        }
        else if(*find(KAuthorizedKey.VParamColorString.begin(), KAuthorizedKey.VParamColorString.end(), cle) == cle )
        {
            char val;
            ifs >> val;
            Param.MapParamColorString[cle] = val;
        }
        else
            getline(ifs, poubelle);
    }
}
