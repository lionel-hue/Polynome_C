#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "polynome.h"

#define POLYNOME


//***MAIN***//
int main(void)
{
    int choix;
    ListePolynomes* liste;
    InitListePolynomes(&liste);
    menu(&choix, &liste);
    return 0;
}
//  made at home :0