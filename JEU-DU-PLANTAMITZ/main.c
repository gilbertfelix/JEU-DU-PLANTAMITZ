#include "header.h"

int main() {

    srand(time(NULL)); // Initialisation du générateur aléatoire

    char plateau[L][C];
    Curseur curseur = { 0, 0, 0, 0, 0};
    char touche;
    Contrat contrat;

    // Génération du plateau initial
    // Plateau garanti stable dès la génération
    remplir_plateau(plateau);
    initialiser_contrat(&contrat,1);

    while (1){
            system("cls");
            afficher_contrat(&contrat);

    // Affichage du plateau initial
    afficher_plateau(plateau,&curseur);

    touche = getch();

    if(touche == 27 ) break;
    if (touche == 32) {
        selectionner_item(&curseur);

    } else if (curseur.selectionne){
        permuter_item(plateau,&curseur, touche);
        contrat.coups_restants--;

        int total = stabiliser_plateau(plateau);

        if(total > 0) {
            system("cls");
            afficher_contrat(&contrat);
            afficher_plateau(plateau,&curseur);
            getch();
        }
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
