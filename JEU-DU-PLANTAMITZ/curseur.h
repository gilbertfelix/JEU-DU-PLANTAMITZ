#ifndef CURSEUR_H_INCLUDED
#define CURSEUR_H_INCLUDED


#include "plateau.h"   // pour LIGNES, COLS et le type du tableau

/* Déplace le curseur en fonction de la touche z/q/s/d */
void deplacer_curseur(int *lig, int *col, char touche);

/* Gère la sélection/désélection d’un item
   Retourne 1 si un item est sélectionné, 0 s’il est désélectionné */
int selectionner_item(int *selL, int *selC, int lig, int col);

/* Permute deux items du plateau si la permutation est possible
   Retourne 1 si la permutation a eu lieu, 0 sinon */
int permuter_items(char tab[LIGNES][COLS],
                   int selL, int selC,
                   int newL, int newC);



#endif // CURSEUR_H_INCLUDED
