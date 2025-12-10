#include "header.h"

int main() {
    srand(time(NULL)); // initialisation de rand()

    char plateau[L][C];

    // Remplir et vérifier le plateau
    remplir_plateau(plateau);
    regenerer_si_alignement(plateau);

    printf("Plateau initial 25x45 sans alignement automatique :\n");
    afficher_plateau(plateau);

    return 0;
}
