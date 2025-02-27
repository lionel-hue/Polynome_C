#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "polynome.h"
#define POLYNOME


void InitPolynome(Polynome** polynome)
{   
    *polynome = (Polynome *)malloc( sizeof(Polynome) );
    (*polynome)->premier = NULL;
    (*polynome)->suivant = NULL;
}


void AjouteTerme(Terme* terme, Polynome* polynome)
{
    if(polynome->premier == NULL )
    {
        polynome->premier = terme; 
    }
    else
    {
        Terme* ptr = polynome->premier;
        while( ptr->suivant != NULL )
        {
            ptr = ptr->suivant;
        }
        ptr->suivant = terme;
    }
}

 
void VerifieTermes(Polynome* polynome)
{
    Terme *ptr; //indicateur de position


    //cette verification serait pour fusionner des termes qui auront des memes valuers des differents etats preccedants e.g 30x0 + 1x45 + 30x1 + 2x4 = 2x4 + 3 
    ptr = polynome->premier;
    while( ptr != NULL )
    {
        if(ptr->iexpo == 0)
        {
            ptr->icoef = 1;
            ptr->iexpo = 1;
            sprintf(ptr->ccoef, "%d", ptr->icoef);
            sprintf(ptr->cexpo, "%d", ptr->iexpo ); 
        }

        else if(ptr->icoef == 1 )
        {
            ptr->iexpo = 1; //ceci et pour fusioner avec un terme avec iexpo 0
            sprintf(ptr->cexpo, "%d", ptr->iexpo );
        }

        else if( ptr->icoef  == 0 ) //on va faire malin ici
        {
            ptr->iexpo = 1; //quelquesoit l'exposant, il sera ecrase et ajoute aux termes avec expo etant "1" !
            sprintf(ptr->cexpo, "%d", ptr->iexpo );
        }    

        ptr = ptr->suivant;
    };


    ptr = polynome->premier;
    while( ptr != NULL && ptr->suivant != NULL )
    {
        if( ptr->iexpo == (ptr->suivant)->iexpo ) //Au cas ou on a deux ou plusieurs termes avec meme expo
        {
            ptr->icoef += (ptr->suivant)->icoef; //besoin de fusionner leurs valeurs !
            sprintf(ptr->ccoef, "%d", ptr->icoef); //ok
            
            Terme* temp = ptr->suivant;
            ptr->suivant = ptr->suivant->suivant;
            free(temp);
        }
        ptr = ptr->suivant;
    }
}


Terme* CreerTerme(void)
{
    Terme* terme = (Terme *)malloc( sizeof(Terme) );
    terme->suivant = NULL;

    printf("Entrer la valeur du coefficient du terme : ");
    scanf(" %d", &terme->icoef);
    sprintf(terme->ccoef, "%d", terme->icoef);
    
    printf("Entrer la valeur de l'exposant du terme : ");
    scanf(" %d", &terme->iexpo);
    sprintf(terme->cexpo, "%d", terme->iexpo);

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
        sprintf( polynomeChaine+i, "%c", (ptr->icoef >= 0 )? '+' : '-' );
        i++;
        sprintf(polynomeChaine+i, "%s", ptr->ccoef);
        i+= strlen(ptr->ccoef);
        sprintf(polynomeChaine+i, "%s", ptr->cexpo);
        i+= strlen(ptr->cexpo);
        sprintf(polynomeChaine+i, "%c", ' ');
        i++;

        ptr = ptr->suivant;
    }
 
    return polynomeChaine + 1; // plus 1 pour le jettage de l'operatuer du premier terme
}


void RangePolynome(Polynome* polynome)
{
    //  tri par selection(Ordre decroissante )
    Terme *i, *j, *iMax, *temp; //les indicateurs a utiliser...
 
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
            temp = i;  
            i = iMax;
            iMax = temp;
        }
        i = i->suivant;
    }
}

int NmbrTermes(Polynome* polynome)
{
    Terme* ptr = polynome->premier;
    int compteur = 0;

    while(ptr != NULL )
    {
        compteur++;
        ptr = ptr -> suivant;
    }
    return compteur;
}



void InitListePolynomes( ListePolynomes** liste )
{
    *liste = (ListePolynomes *)malloc(sizeof(ListePolynomes)) ;
    (*liste)->premier= NULL;
}

void AjoutePolynome (Polynome* polynome, ListePolynomes* liste )
{
    if(liste->premier == NULL )
    {
        liste->premier = polynome; 
    }
    else
    {
        Polynome* ptr = liste->premier;
        while( ptr->suivant != NULL )
        {
            ptr = ptr->suivant;
        }
        ptr->suivant = polynome;
    }
}

void AfficherListePolynomes(ListePolynomes* liste)
{
    Polynome* ptr = liste->premier;
    int i = 0;


    if (liste == NULL || liste->premier == NULL)
    {
        printf("\nLa liste de polynomes est vide.\n");
        return;
    }


    while( ptr != NULL )
    {
        printf("\nPolynome numero %d : %s",i+1, CreerPolynome(ptr) );
        i++;
        ptr = ptr->suivant;   
    }
}