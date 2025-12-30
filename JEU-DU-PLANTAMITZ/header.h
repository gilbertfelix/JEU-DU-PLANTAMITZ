#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define L 25   // nombre de lignes du plateau
#define C 45   // nombre de colonnes du plateau

// =========================
// Prototypes des fonctions
// =========================

// Génération aléatoire d'un item pour le plateau
char generer_item(void);

// Remplissage du plateau avec contrôle des alignements interdits
void remplir_plateau(char tab[L][C]);

// Vérifie si des alignements interdits existent sur le plateau
int alignement_existe(char tab[L][C]);

// Affichage du plateau avec couleurs
void afficher_plateau(char tab[L][C]);

// Affiche un item avec sa couleur correspondante
void afficher_items(char item);

// Changement de couleur du texte et du fond dans la console
void Color(int couleurDuTexte, int couleurDeFond);
void gotoligcol( int lig, int col );

#endif
