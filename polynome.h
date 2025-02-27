#ifndef POLYNOME

    #define POLYNOME
    #define TAILLE 5 // utilise pour les taille des coef et expo de chq terme.


    //Struct de donnes terme
    typedef struct terme 
    {
        //Le coefficient et l'exposant en chaine a convertir
        //en entier...
        int icoef, iexpo; 
        char ccoef[TAILLE], cexpo[TAILLE];
        struct terme* suivant;
    }Terme;


    //Le Polynome(combinaisons des termes)
    typedef struct polynome
    {
        Terme* premier; //pour tous les termes d'un polynome 
        struct polynome* suivant; //pour tous les polynomes existants
    }Polynome;


    //Les Polynomes;
    typedef struct listePolynomes
    {
        Polynome* premier;
    }ListePolynomes;


    //Les fonctions utiles :

    void InitPolynome(Polynome **); //Nettoyer le polynome(vide)

    void AjouteTerme(Terme *, Polynome * ); //Ajouter un terme a la fin du polynome

    void VerifieTermes(Polynome *); //E.g 2x6 - 5x6 doit egal a -3x6

    char* CreerPolynome(Polynome *); //recuperer le polynome en chaine de caracteres!

    void RangePolynome(Polynome *); //organiser le polynome

    Terme* CreerTerme(void); //Creer Un terme Standard depuis i/o

    int NmbrTermes(Polynome*); //retourne le nombre de termes du polynome

    void SupprimerTerme(Polynome *, int); //Supprimer un terme a une position preccise


    /*************/
    void InitListePolynomes(ListePolynomes **); //Nettoyer la liste des polynomes

    void AjoutePolynome(Polynome *, ListePolynomes *); //Ajouter un polynome a la fin de la liste des polynomes

    void SupprimePolynome(ListePolynomes*, int); //Supprimer un polynome dans la liste des polynomes

    void AfficherListePolynomes(ListePolynomes*); //afficher la liste des polynomes avec les foncs printf...

    /************* */
    void menu(int*, ListePolynomes** ); //le menu
    
#endif