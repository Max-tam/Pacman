/**
 * \file params.h
 * \brief Initialisation paramètre
 * \author {TAMARIN Maxime, ROUBAUD Axel, BOSSO Gavril, JAURAS Maxime, Alain Casali}
 * \version 0.1
 * \date 15 janvier 2023
 */
#ifndef PARAMS_H
#define PARAMS_H

#include "En-têtes/type.h"

using namespace nsGraphics;

/**
 * \brief ConvertStringRGBAcolor : convertir un texte en une couleur
 * \param[in] text
 */
RGBAcolor ConvertStringRGBAcolor(std::string & text);

/**
 * \brief InitParams
 * \param[out] Param
 */
void InitParams (CMyParam & Param);

/**
 * \brief LoadParams
 * \param[out] Param
 */
void LoadParams (CMyParam & Param);

#endif // PARAMS_H
