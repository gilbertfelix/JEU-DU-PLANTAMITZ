#include "header.h"

int main() {
    srand(time(NULL)); // initialisation de rand()

    char plateau[L][C];

    // Remplir le plateau au hasard
    remplir_plateau(plateau);

    // Vérifier et régénérer si des alignements interdits existent
    if (alignement_existe(plateau)) {
        printf("Alignements détectés, régénération du plateau...\n");
        regenerer_si_alignement(plateau);
    }

    // Affichage du plateau final
    printf("\nPlateau initial %dx%d sans alignement automatique :\n\n", L, C);
    afficher_plateau(plateau);

    return 0;
}
