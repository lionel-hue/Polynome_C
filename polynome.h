#ifndef POLYNOME
#define POLYNOME

#define TAILLE 5 // utilise pour les taille des coef et expo de chq terme.
#define CONST "constant" // nature d'un terme 
#define VAR "variable" //nature d'un terme aussi
#define MONO "monome" //nature d'un polynome 
#define POLY "polynome" //nature d'un polynome aussi

//Struct de donnes terme
typedef struct terme 
{
    //Le coefficient et l'exposant en chaine a convertir
    //en entier...
    int icoef, iexpo; 
    char ccoef[TAILLE], cexpo[TAILLE];
    struct terme* suivant;
    /**************/
    char nature[10]; // constant ou variable (CONST/VAR)
}Terme;


//Le Polynome(combinaisons des termes)
typedef struct polynome
{
    char variable[2];
    Terme* premier;
    /**************/
    char nature[10]; // monome ou polynome (MONO/POLY)
}Polynome;


//Les fonctions utiles :

void InitPolynome(Polynome **); //Nettoyer le polynome(vide)
void AjouteTerme(Terme *, Polynome * ); //Toujours au debut de la liste des polynomes
void VerifieTermes(Polynome *); //E.g 2x6 - 5x6 doit egal a -3x6
char* CreerPolynome(Polynome *); //recuperer le polynome en chaine de caracteres!
void RangePolynome(Polynome *); //organiser le polynome
void StrcpyTerme(Terme*, Terme*); //Copier le contenu d'un terme dans un autre
Terme* CreerTerme(void); //Creer Un terme Standard depuis i/o
void ChangerVariable(Polynome *); //Utiliser les variables en ascii existantes que X
char* CreerExposant(Terme *); //retourne l'ascii equivalent d'un nombre dans sa puissance

#endif