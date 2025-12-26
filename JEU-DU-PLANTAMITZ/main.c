#include "header.h"

int main() {
  srand(time(NULL)); // Initialiser le g�n�rateur de nombres al�atoires

    char plateau[L][C];

    // Remplir le plateau initialement
    remplir_plateau(plateau);

    // Regénérer le plateau tant qu'il y a des alignements interdits
    regenerer_si_alignement(plateau);

    // Afficher le plateau final
    afficher_plateau(plateau);
    system("pause");

    return 0;
}
