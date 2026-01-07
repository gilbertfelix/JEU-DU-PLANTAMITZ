#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define L 25   // nombre de lignes du plateau
#define C 45   // nombre de colonnes du plateau

typedef struct{
    int ligne;
    int colonne;
    int selectionne;
    int sel_i;
    int sel_j;
}Curseur;

typedef struct{
    int soleil_requis;
    int fraise_requis;
    int pomme_requis;
    int oignon_requis;
    int mandarine_requis;

    int soleil_actuel;
    int fraise_actuel;
    int pomme_actuel;
    int oignon_actuel;
    int mandarine_actuel;

    int coups_max;
    int coups_restants;

    int score;
    int vies;

    time_t temps_debut;
    int temps_limite;
} Contrat;

typedef struct{
    char nom[50];
    int niveau_actuel;
    int score_total;
}Joueur;

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
void afficher_plateau(char tab[L][C], Curseur *c);

// Affiche un item avec sa couleur correspondante
void afficher_items(char item);

// Changement de couleur du texte et du fond dans la console
void Color(int couleurDuTexte, int couleurDeFond);
void gotoligcol( int lig, int col );
void deplacer_curseur(Curseur *c, char touche);
void selectionner_item(Curseur *c);
void permuter_item(char tab[L][C], Curseur *c, char direction);
int suppression(char tab[L][C], int marque[L][C]);
void supprimer_marques(char tab[L][C], int marque[L][C]);
void faire_tomber_item(char tab[L][C]);
void remplir_vide(char tab[L][C]);
int stabiliser_plateau(char tab[L][C],Contrat *c);
void initialiser_contrat(Contrat *c, int niveau);
void afficher_contrat(Contrat *c);
void compter_items_supprime(char tab[L][C], int marque[L][C],Contrat *c );
int calculer_points(char tab[L][C], int marque[L][C]);
int contrat_rempli(Contrat *c);
int temps_contrat(Contrat *c);
void sauvegarder_progression(const char *nom_joueur,int niveau_atteint,int score);
int charger_progression(char *nom_joueur, int *niveau_atteint, int *score);
void supprimer_sauvegarde();

#endif
