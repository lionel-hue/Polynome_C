#include "polynome.h"
#include <stdio.h>

void menu(int* choix, ListePolynomes** liste)
{
    do
    {
        printf("\n\n================\n");
        printf("Bienvenue a L'editeur du polynome");
        printf("\nEntrer");
        printf("\n1 Creer un polynome");
        printf("\n2 Voir mes polynomes");
        printf("\n3 Ajouter un terme a un polynome");
        printf("\n4 Supprimer un terme d'un polynome");
        printf("\n5 A propos");
        printf("\n6 Quiitter");

        printf("\nMon choix : ");
        scanf(" %d", choix);
        printf("\n================\n");

        switch(*choix)
        {
            case 1:

            int continuer = 1;
            Polynome* polynome;
            Terme* terme = CreerTerme();
            Terme* ptr;

            InitPolynome(&polynome); 
            AjouteTerme(terme, polynome);
            ptr = polynome->premier;

            printf("\nVoulez-vous continuer ? 1 pour oui et 0 pour non : ");
            scanf(" %d", &continuer);

            while( continuer == 1 )
            {
                ptr->suivant = CreerTerme();
                ptr = ptr->suivant;
                printf("\nVoulez-vous continuer ? 1 pour oui et 0 pour non : ");
                scanf(" %d", &continuer);
            }
            
            AjoutePolynome(polynome, *liste);
            menu(choix, liste);
            break;

            case 2:
            AfficherListePolynomes(*liste);
            menu(choix, liste);
            break;
        }

    }while( *choix < 1 || *choix > 6 );
}