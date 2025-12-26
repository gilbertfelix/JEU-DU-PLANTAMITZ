#include "input.h"

void deplacer_curseur(int *lig, int *col, char touche)
{
    switch (touche)
    {
    case 'z': // haut
        if (*lig > 0)
            (*lig)--;
        break;
    case 's': // bas
        if (*lig < LIGNES - 1)
            (*lig)++;
        break;
    case 'q': // gauche
        if (*col > 0)
            (*col)--;
        break;
    case 'd': // droite
        if (*col < COLS - 1)
            (*col)++;
        break;
    default:
        break;
    }
}

int selectionner_item(int *selL, int *selC, int lig, int col)
{
    if (*selL == lig && *selC == col)
    {
        // On clique sur l’item déjà sélectionné : désélection
        *selL = -1;
        *selC = -1;
        return 0;
    }
    else
    {
        // Nouvelle sélection
        *selL = lig;
        *selC = col;
        return 1;
    }
}

int permuter_items(char tab[LIGNES][COLS],
                   int selL, int selC,
                   int newL, int newC)
{
    // Vérification des limites
    if (selL < 0 || selL >= LIGNES || selC < 0 || selC >= COLS)
        return 0;
    if (newL < 0 || newL >= LIGNES || newC < 0 || newC >= COLS)
        return 0;

    // Vérification de l’adjacence
    int dL = selL - newL;
    int dC = selC - newC;
    if (!((dL == 0 && (dC == 1 || dC == -1)) ||
          (dC == 0 && (dL == 1 || dL == -1))))
    {
        return 0;
    }

    // Permutation
    char tmp = tab[selL][selC];
    tab[selL][selC] = tab[newL][newC];
    tab[newL][newC] = tmp;

    return 1;
}
