#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "polynome.h"

#define POLYNOME


//***MAIN***//
int main(void)
{
    int nmbr_termes;
    int continuer = 0;
 
        system("clear");
        printf("Bienvenue!,vous voulez creer un polynome avec combien de termes ? : ");
        scanf(" %d", &nmbr_termes);
        printf("\n");

        Polynome* polynome = (Polynome *)malloc( sizeof(Polynome *) ); //polynome
        Terme* terme; //le premier terme
        Terme* ptr; //pointeur sur le premier terme

        InitPolynome(polynome);
        terme = CreerTerme();
        AjouteTerme(terme, polynome);
        ptr = polynome->premier;


        for(int i=0;i< nmbr_termes-1; i++)
        {
            ptr->suivant = CreerTerme();
            ptr = ptr->suivant;
        }

        RangePolynome(polynome);
        VerifieTermes(polynome); 
        printf("Votre Eqn de base : %s\n", CreerPolynome(polynome) );
        printf("VOulez-vous continuer? 1 pour oui et 0 pour non ? >>> ");
        fscanf(stdin, " %d", &continuer);
        ( continuer == 1 )? main():(void)0;

    return 0;
}
//  made at home :0