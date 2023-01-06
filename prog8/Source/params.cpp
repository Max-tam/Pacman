#include <string>
#include <iostream>
#include <fstream>

#include "En-têtes/params.h"
#include "En-têtes/type.h"

//cree le docier si il le faut (game.h)

using namespace std;


void InitParams (CMyParam & Param) /*Gavril prof correction*/
{
//Move Keys
Param.MapParamChar["KeyUp"] = 'z';
Param.MapParamChar["KeyDown"] = 's';
Param.MapParamChar["KeyLeft"] = 'q';
Param.MapParamChar["KeyRight"] = 'd';

//Display Colors
Param.MapParamColorString["Colorfond1"] = KColor.find("KRed")->second ;
Param.MapParamColorString["Colorfond2"] = KColor.find("KCyan")->second ;

}

void loadparam (CMyParam & Param) /*Sources Gavril / Prof correction prog13*/
{
    ifstream ifs("../prog8/Nos_fichiers/config.yaml");
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
        if(find(KAuthorizedKey.VParamChar.begin(), KAuthorizedKey.VParamChar.endl(), cle) != KAuthorizedKey.VParamChar.endl())
        {
            char val;
            ifs >> val;
            Param.MapParamChar[cle] = val;
        }
        else if(find(KAuthorizedKey.VParamColorString.begin(), KAuthorizedKey.VParamColorString.endl(), cle))
        {
            char val;
            ifs >> val;
            Param.MapParamColorString[cle] = val;
        }
        else
            getline(ifs, poubelle);
    }
}
