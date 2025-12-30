#include "header.h"

int main() {

    srand(time(NULL)); // Initialisation du générateur aléatoire

    char plateau[L][C];

    // Génération du plateau initial
    // Plateau garanti stable dès la génération
    remplir_plateau(plateau);

    // Affichage du plateau initial
    printf("\nPlateau initial %dx%d (sans alignement automatique) :\n\n", L, C);
    afficher_plateau(plateau);
    gotoligcol(0,0);

    // --- La logique de jeu viendra ici ---
    // sélection d’items
    // permutation
    // détection des alignements
    // suppression + chute

    return 0;
}
