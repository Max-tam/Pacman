/**
 * \file params.cpp
 * \brief Initialisation paramètre
 * \author {TAMARIN Maxime, ROUBAUD Axel, BOSSO Gavril, JAURAS Maxime}
 * \version 0.1
 * \date 15 janvier 2023
 */

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <mingl/mingl.h>

#include "En-têtes/params.h"
#include "En-têtes/type.h"

using namespace std;
using namespace nsGraphics;

/**
 * \brief ConvertStringRGBAcolor : convertir un texte en une couleur
 * \param[in] text
 */
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

/**
 * \brief LoadParams
 * \param[out] Param
 */
void LoadParams (CMyParam & Param)
{
    ifstream ifs("../prog8/autre fichier/config.yaml");
    if (!ifs)
    {
        cerr << "le fichier de configuration est pas ouvert" << endl ;
        exit(-1);
    }
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
        else if(*find(KAuthorizedKey.VParamString.begin(), KAuthorizedKey.VParamString.end(), cle) == cle)
        {
            string valFichier;
            ifs >> valFichier;
            RGBAcolor val = ConvertStringRGBAcolor(valFichier);
            Param.MapParamString[cle] = val;
        }
        else
            getline(ifs, poubelle);
    }
}

/**
 * \brief InitParams
 * \author {TAMARIN Maxime, ROUBAUD Axel, BOSSO Gavril, JAURAS Maxime, Alain Casali}
 * \param[out] Param
 */
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

    //collision
    Param.MapParamCollisionChar["mur"] = 'X';
    Param.MapParamCollisionChar["porte"] = '-';

    LoadParams(Param); // on verifie si dans le fichier des informations ne sont pas différente
}

// faire fonction qui avec
