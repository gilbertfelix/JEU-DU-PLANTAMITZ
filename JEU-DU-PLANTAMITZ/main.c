#include "header.h"

int main() {

    srand(time(NULL)); // Initialisation du générateur aléatoire

    char plateau[L][C];
    Curseur curseur = {0, 0, 0, 0, 0};
    char touche;

    // Génération du plateau initial
    // Plateau garanti stable dès la génération
    remplir_plateau(plateau);
    while (1){
            system("cls");

    // Affichage du plateau initial
    printf("\nPlateau initial %dx%d (sans alignement automatique) :\n\n", L, C);
    afficher_plateau(plateau,&curseur);

    touche = getch();
    if(touche == 27 ) break;
    if (touche == 32) {
        selectionner_item(&curseur);
    } else if (curseur.selectionne){
        permuter_item(plateau,&curseur, touche);

        int total = stabiliser_plateau(plateau);
        int marque[L][C];
        int nbr_supprime = suppression(plateau,marque);
        if(nbr_supprime > 0){
            supprimer_marques(plateau,marque);
        }
        system("cls");
        afficher_plateau(plateau,&curseur);
        getch();

        faire_tomber_item(plateau);

          system("cls");
        afficher_plateau(plateau,&curseur);
        getch();

        remplir_vide(plateau);

          system("cls");
        afficher_plateau(plateau,&curseur);
        getch();

    }
    else{
        deplacer_curseur(&curseur, touche);
    }

    // --- La logique de jeu viendra ici ---
    // sélection d’items
    // permutation
    // détection des alignements
    // suppression + chute
    }
    return 0;
}
