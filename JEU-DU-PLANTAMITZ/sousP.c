#include "header.h"

// =========================
// Fonction 1 : Générer un item aléatoire
// =========================
char generer_item(void) {
    char items[] = {'S', 'F', 'P', 'O', 'M'}; // Soleil, Fraise, Pomme, Oignon, Mandarine
    int index = rand() % 5;  // choisir un index aléatoire
    return items[index];
}

// =========================
// Fonction 2 : Remplir le plateau au hasard
// =========================
void remplir_plateau(char tab[L][C]) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            tab[i][j] = generer_item();
        }
    }
}

// =========================
// Fonction 3 : Vérifier alignement de 3 items
// =========================
int alignement_existe(char tab[L][C]) {
    // Vérifie les lignes
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C - 2; j++) {
            if (tab[i][j] == tab[i][j+1] && tab[i][j] == tab[i][j+2])
                return 1; // alignement trouvé
        }
    }

    // Vérifie les colonnes
    for (int j = 0; j < C; j++) {
        for (int i = 0; i < L - 2; i++) {
            if (tab[i][j] == tab[i+1][j] && tab[i][j] == tab[i+2][j])
                return 1; // alignement trouvé
        }
    }

    return 0; // pas d'alignement
}

// =========================
// Fonction 4 : Régénérer le plateau tant qu'il y a des alignements
// =========================
void regenerer_si_alignement(char tab[L][C]) {
    while (alignement_existe(tab)) {
        remplir_plateau(tab);
    }
}

// =========================
// Fonction utilitaire : afficher le plateau
// =========================
void afficher_plateau(char tab[L][C]) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
}
