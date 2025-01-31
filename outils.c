#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "polynome.h"
#define POLYNOME


void InitPolynome(Polynome * polynome)
{   
    polynome->premier = NULL;
    sprintf( polynome->variable, "%c", 'x' ); // variable des termes par defaut est 'X'
}


void AjouteTerme(Terme* terme, Polynome* polynome)
{
    terme->suivant = polynome->premier;
    polynome->premier = terme;
}

 
void VerifieTermes(Polynome* polynome)
{
    Terme *ptr; //indicateur de position

    ptr = polynome->premier;
    while( ptr->suivant != NULL )
    {
        if( ptr->iexpo == (ptr->suivant)->iexpo ) //Au cas ou on a deux ou plusieurs termes avec meeme expo
        {
            ptr->icoef += (ptr->suivant)->icoef; //besoin de fusionner leurs valeurs !
            sprintf(ptr->ccoef, "%d", ptr->icoef);
            if ( (ptr->suivant)->suivant == NULL ) ptr->suivant = 0; //Verification si c'est le dernier terme!
            else ptr->suivant = (ptr->suivant)->suivant;   //Suppression du terme rendu inutile
        }

        ptr = ptr->suivant;
    }

}


Terme* CreerTerme(void)
{
    Terme* terme = (Terme *)malloc( sizeof(Terme) );

    printf("Entrer la valeur du coefficient du terme : ");
    scanf(" %d", &terme->icoef);
    sprintf(terme->ccoef, "%d", terme->icoef);
    
    printf("Entrer la valeur de l'exposant du terme : ");
    scanf(" %d", &terme->iexpo);
    sprintf(terme->cexpo, "%d", terme->iexpo);

    (terme->iexpo == 0 )? sprintf(terme->nature, "%s", CONST ): sprintf(terme->nature, "%s", VAR); 
    printf("\n");
    return terme;
}

char* CreerPolynome(Polynome* polynome)
{
    Terme* ptr; //Indicateur de position
    int nmbr_termes = 0; //Necessaire pour le calcul de l'allocation de memoire du polynome chaine 
    char* polynomeChaine;
    int i=0; //index pour la creation du chaine du polynome...

    ptr = polynome->premier;
    while( ptr != NULL )
    {
        //D'ou le nmbr '3' se compose du signe du terme, sa variable(polynome->variable[0]) et
        // le nombre espace ' '. 
        nmbr_termes += strlen(ptr->ccoef) + strlen(ptr->cexpo) + 3; //ok  
        ptr = ptr->suivant;
    }

    ptr = polynome->premier;
    polynomeChaine = (char *)malloc( sizeof(char) * nmbr_termes ); 

    while( ptr != NULL)  
    {
        if( strncmp(ptr->ccoef, "0", 1 ) == 0 || strncmp(ptr->ccoef, "-0", 2 ) == 0 );

        else if( strncmp(ptr->ccoef, "1", 1 ) == 0 || ptr->iexpo == 0 )
        {
            sprintf( polynomeChaine+i, "%s", "+1" );
            i++;
            sprintf(polynomeChaine+i, "%d", 1);
            i++;
            sprintf(polynomeChaine+i, "%c", ' ');
            i++;
        }

        else if( strncmp(ptr->ccoef, "-1", 2 ) == 0 )
        {
            sprintf( polynomeChaine+i, "%s", "-1" );
            i++;
            sprintf(polynomeChaine+i, "%d", -1);
            i++;
            sprintf(polynomeChaine+i, "%c", ' ');
            i++;
        }

        else if( ptr->iexpo == 1 )
        {
            sprintf( polynomeChaine+i, "%c", (ptr->icoef > 0 )? '+' : '-' );
            i++;
            sprintf(polynomeChaine+i, "%s", ptr->ccoef);
            i+= strlen(ptr->ccoef);
            sprintf(polynomeChaine+i, "%c", ' ');
            i++;
        } 

        else
        {
            sprintf( polynomeChaine+i, "%c", (ptr->icoef > 0 )? '+' : '-' );
            i++;
            sprintf(polynomeChaine+i, "%s", ptr->ccoef);
            i+= strlen(ptr->ccoef);
            sprintf(polynomeChaine+i, "%c", polynome->variable[0] );
            i++;
            sprintf(polynomeChaine+i, "%s", ptr->cexpo);
            i+= strlen(ptr->cexpo);
            sprintf(polynomeChaine+i, "%c", ' ');
            i++;
        }


        ptr = ptr->suivant;
    }
 
    return polynomeChaine + 1; // plus 1 pour le jettage de l'operatuer du premier termw
}


void RangePolynome(Polynome* polynome)
{
    //  tri par selection(Ordre decroissante )
    Terme *i, *j, *iMax, *temp; //les indicateurs a utiliser...
    temp = (Terme *)malloc(sizeof(Terme) );
 
    i = polynome->premier;
    while( i->suivant != NULL )
    {
        iMax = i;
        j = i->suivant;

        while( j != NULL )
        {
            if( iMax->iexpo < j->iexpo ) iMax = j; 
            j = j->suivant;
        }

        if( iMax != i )
        { 
            StrcpyTerme(temp,i);  
            StrcpyTerme(i,iMax);
            StrcpyTerme(iMax,temp);
        }
        i = i->suivant;
    }
}


void StrcpyTerme(Terme* dest, Terme* src)
{
    memset(dest->ccoef,'\0', sizeof dest->ccoef );
    sprintf(dest->ccoef,"%s",src->ccoef);

    dest->icoef = src->icoef;

    memset(dest->cexpo,'\0', sizeof dest->cexpo );
    sprintf(dest->cexpo,"%s",src->cexpo);
    dest->iexpo = src->iexpo;

    memset(dest->nature,'\0', sizeof dest->nature );
    sprintf(dest->nature,"%s",src->nature);
}