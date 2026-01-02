#include "detect_groupes.h"

/* Vérifie si une case est déjà dans la liste */
static int case_presente(const Groupes *g, int lig, int col) {
    int i;
    for (i = 0; i < g->nb; i++) {
        if (g->tab[i].lig == lig && g->tab[i].col == col) {
            return 1;
        }
    }
    return 0;
}

void ajouter_case(Groupes *g, int lig, int col)
{
    if (g == NULL) return;
    if (lig < 0 || lig >= LIGNES || col < 0 || col >= COLS) return;
    if (case_presente(g, lig, col)) return;
    if (g->nb < MAX_SUPP) {
        g->tab[g->nb].lig = lig;
        g->tab[g->nb].col = col;
        g->nb++;
    }
}

/* Détecte la longueur d’un groupe horizontal à partir de (lig,col) */
int detecter_ligne(char plateau[LIGNES][COLS], int lig, int col) {
    char c;
    int j, len = 1;

    if (lig < 0 || lig >= LIGNES || col < 0 || col >= COLS) return 0;
    c = plateau[lig][col];
    if (c == ' ') return 0;

    for (j = col + 1; j < COLS && plateau[lig][j] == c; j++) {
        len++;
    }
    return len;
}

/* Détecte la longueur d’un groupe vertical à partir de (lig,col) */
int detecter_colonne(char plateau[LIGNES][COLS], int lig, int col) {
    char c;
    int i, len = 1;

    if (lig < 0 || lig >= LIGNES || col < 0 || col >= COLS) return 0;
    c = plateau[lig][col];
    if (c == ' ') return 0;

    for (i = lig + 1; i < LIGNES && plateau[i][col] == c; i++) {
        len++;
    }
    return len;
}

/* Vérifie un rectangle L x l à partir de (lig,col) */
int detecter_rectangle(char plateau[LIGNES][COLS], Groupes *groupes,
                       int lig, int col, int L, int l) {
    int i, j;
    char c;

    if (lig < 0 || col < 0) return 0;
    if (lig + L > LIGNES || col + l > COLS) return 0;

    c = plateau[lig][col];
    if (c == ' ') return 0;

    for (i = lig; i < lig + L; i++) {
        for (j = col; j < col + l; j++) {
            if (plateau[i][j] != c) {
                return 0;
            }
        }
    }

    /* Rectangle valide : ajoute toutes les cases */
    for (i = lig; i < lig + L; i++) {
        for (j = col; j < col + l; j++) {
            ajouter_case(groupes, i, j);
        }
    }
    return 1;
}


int detecter_H(char plateau[LIGNES][COLS], Groupes *groupes, int lig, int col) {
    char c;
    int i;

    /* On vérifie une H de taille 3x3 pour l’exemple */
    if (lig - 1 < 0 || lig + 1 >= LIGNES || col + 2 >= COLS) return 0;

    c = plateau[lig][col];
    if (c == ' ') return 0;

    /* Barre horizontale haute */
    for (i = 0; i < 3; i++) {
        if (plateau[lig - 1][col + i] != c) return 0;
    }
    /* Barre horizontale basse */
    for (i = 0; i < 3; i++) {
        if (plateau[lig + 1][col + i] != c) return 0;
    }
    /* Barre verticale centrale */
    if (plateau[lig][col + 1] != c) return 0;

    /* Ajout des cases du H */
    for (i = 0; i < 3; i++) {
        ajouter_case(groupes, lig - 1, col + i);
        ajouter_case(groupes, lig + 1, col + i);
    }
    ajouter_case(groupes, lig, col + 1);

    return 1;
}

/* Détection globale de tous les groupes (>=3 en ligne ou colonne) + figures */
int detecter_groupes(char plateau[LIGNES][COLS], Groupes *groupes) {
    int lig, col;
    int len;
    int trouve = 0;

    if (groupes == NULL) return 0;
    groupes->nb = 0;

    for (lig = 0; lig < LIGNES; lig++) {
        for (col = 0; col < COLS; col++) {
            char c = plateau[lig][col];
            int k;

            if (c == ' ') continue;

            /* Groupes horizontaux */
            len = detecter_ligne(plateau, lig, col);
            if (len >= 3) {
                trouve = 1;
                for (k = 0; k < len; k++) {
                    ajouter_case(groupes, lig, col + k);
                }
            }

            /* Groupes verticaux */
            len = detecter_colonne(plateau, lig, col);
            if (len >= 3) {
                trouve = 1;
                for (k = 0; k < len; k++) {
                    ajouter_case(groupes, lig + k, col);
                }
            }

            /* Rectangles possibles (exemple 2x2, 3x2, 4x3 etc.) */
            detecter_rectangle(plateau, groupes, lig, col, 2, 2);
            detecter_rectangle(plateau, groupes, lig, col, 3, 2);
            detecter_rectangle(plateau, groupes, lig, col, 4, 3);

            /* Forme en H */
            detecter_H(plateau, groupes, lig, col);
        }
    }

    return (trouve || groupes->nb > 0);
}
