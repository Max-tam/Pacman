#include <iostream>
#include <iomanip>
#include "../prog8/En-têtes/gridmanagement.h"

#include "../prog8/En-têtes/type.h"


using namespace std;


void ClearScreen() /*prof correction*/
{
    cout << "\033[H\033[2J";
}// ClearScreen ()

void Color (const string & Col)
{
    cout << "\033[" << Col.c_str () <<"m";
} // Color ()
