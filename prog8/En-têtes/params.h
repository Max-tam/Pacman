#ifndef PARAMS_H
#define PARAMS_H

#include "En-têtes/type.h"

using namespace nsGraphics;

RGBAcolor ConvertStringRGBAcolor(std::string & text);

void InitParams (CMyParam & Param);

void LoadParams (CMyParam & Param);

#endif // PARAMS_H
