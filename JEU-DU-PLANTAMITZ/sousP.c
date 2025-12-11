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

    // --------------------------
    // 1. GROUPES DE 3, 4, ou 5 HORIZONTAUX
    // --------------------------
    for (int i = 0; i < L; i++) {
        int count = 1;
        for (int j = 1; j < C; j++) {
            if (tab[i][j] == tab[i][j-1]) {
                count++;
                if (count >= 3) return 1; // groupe interdit
            } else {
                count = 1;
            }
        }
    }

    // --------------------------
    // 2. GROUPES DE 3, 4 ou 5 VERTICAUX
    // --------------------------
    for (int j = 0; j < C; j++) {
        int count = 1;
        for (int i = 1; i < L; i++) {
            if (tab[i][j] == tab[i-1][j]) {
                count++;
                if (count >= 3) return 1; // groupe interdit
            } else {
                count = 1;
            }
        }
    }

    // --------------------------
    // 3. RECTANGLE 2x2 MINIMUM
    // --------------------------
    for (int i = 0; i < L - 1; i++) {
        for (int j = 0; j < C - 1; j++) {
            char x = tab[i][j];
            if (tab[i][j+1] == x &&
                tab[i+1][j] == x &&
                tab[i+1][j+1] == x)
            {
                return 1; // rectangle interdit
            }
        }
    }

    // --------------------------
    // 4. FIGURE EN H
    // --------------------------
    // forme :
    // x . x
    // x x x
    // x . x
    for (int i = 0; i < L - 2; i++) {
        for (int j = 0; j < C - 2; j++) {

            char x = tab[i][j];

            if ( tab[i][j] == x &&         // haut gauche
                 tab[i][j+2] == x &&       // haut droite
                 tab[i+1][j] == x &&       // centre gauche
                 tab[i+1][j+1] == x &&     // centre milieu
                 tab[i+1][j+2] == x &&     // centre droite
                 tab[i+2][j] == x &&       // bas gauche
                 tab[i+2][j+2] == x )      // bas droite
            {
                return 1; // H interdit
            }
        }
    }

    return 0; // Aucun alignement ni figure spéciale → plateau stable
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
