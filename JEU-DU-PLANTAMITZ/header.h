#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>

// Dimmension du plateau

#define L 25   // nombre de lignes du plateau
#define C 45

//Définition des items spéciaux
#define BOMBE 'B'
#define ETOILE 'E'
#define ECLAIR 'L'
#define ARC_EN_CIEL 'R'


//Structure représentant le contrat(Objectifs du niveau)
typedef struct{
    int ligne;
    int colonne;
    int selectionne;
    int sel_i;
    int sel_j;
}Curseur;

// Structure représentant le contrat(objectifs du niveau)
typedef struct{
    // Objectifs requis pour chaque type d'item
    int soleil_requis;
    int fraise_requis;
    int pomme_requis;
    int oignon_requis;
    int mandarine_requis;

    // Compteurs actuels pour chaque types d'item
    int soleil_actuel;
    int fraise_actuel;
    int pomme_actuel;
    int oignon_actuel;
    int mandarine_actuel;

   // Gestion des coups et du score
    int coups_max;
    int coups_restants;
    int score;
    int vies;

    // Gestion du temps
    time_t temps_debut;
    int temps_limite;
    int niveau_actuel;
} Contrat;

// Structure représentant le joueur
typedef struct{
    char nom[50];
    int niveau_actuel;
    int score_total;
}Joueur;

//====================================
// Prototypes des fonctions - plateau
//====================================


char generer_item(void);
void remplir_plateau(char tab[L][C]);
int alignement_existe(char tab[L][C]);
void afficher_plateau(char tab[L][C], Curseur *c);
void afficher_items(char item);
void Color(int couleurDuTexte, int couleurDeFond);
void gotoligcol( int lig, int col );


//====================================
// Prototypes des fonctions - curseur
//====================================

void deplacer_curseur(Curseur *c, char touche);
void selectionner_item(Curseur *c);
void permuter_item(char tab[L][C], Curseur *c, char direction);

//========================================
// Prototypes des fonctions - suppressions
//========================================

int suppression(char tab[L][C], int marque[L][C]);
void supprimer_marques(char tab[L][C], int marque[L][C]);
void faire_tomber_item(char tab[L][C]);
void remplir_vide(char tab[L][C]);
int stabiliser_plateau(char tab[L][C],Contrat *c);

//====================================
// Prototypes des fonctions - contrat
//====================================

void initialiser_contrat(Contrat *c, int niveau);
void afficher_contrat(Contrat *c);
void compter_items_supprime(char tab[L][C], int marque[L][C],Contrat *c );
int calculer_points(char tab[L][C], int marque[L][C]);
int contrat_rempli(Contrat *c);
int temps_contrat(Contrat *c);

//=======================================
// Prototypes des fonctions - progression
//=======================================

void sauvegarder_progression(const char *nom_joueur,int niveau_atteint,int score);
int charger_progression(char *nom_joueur, int *niveau_atteint, int *score);
void supprimer_sauvegarde();

//====================================
// Prototypes des fonctions - musique
//====================================

void demarrer_musique();
void arreter_musique();
void toggle_musique();

//==========================================
// Prototypes des fonctions - Items spéciaux
//==========================================

void remplir_plateau_speciaux(char tab[L][C]);
char generer_item_special(int longueur , int horizontal);
int suppression_special(char tab[L][C], int marque[L][C]);
void activer_bombe(char tab[L][C], int marque[L][C], int i, int j);
void activer_eclair(char tab[L][C], int marque[L][C], int i, int j );
void activer_etoile(char tab[L][C], int marque[L][C], int i, int j );
void activer_arc_en_ciel(char tab[L][C], int marque[L][C], int i, int j, char item_cible );
void activer_item_special(char tab[L][C], int marque[L][C], int i, int j);
#endif
