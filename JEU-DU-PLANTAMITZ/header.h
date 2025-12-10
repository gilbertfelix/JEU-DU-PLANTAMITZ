#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define L 25   // nombre de lignes du plateau
#define C 45   // nombre de colonnes du plateau

// Prototypes des fonctions
char generer_item(void);
void remplir_plateau(char tab[L][C]);
int alignement_existe(char tab[L][C]);
void regenerer_si_alignement(char tab[L][C]);
void afficher_plateau(char tab[L][C]);

#endif
