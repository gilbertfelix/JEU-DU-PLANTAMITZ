
#ifndef DETECT_GROUPES_H
#define DETECT_GROUPES_H

#define LIGNES 25
#define COLS   45
#define MAX_SUPP (LIGNES*COLS)

/* Structure pour stocker une case à supprimer */
typedef struct {
    int lig; /* IN: ligne de la case */
    int col; /* IN: colonne de la case */
} Case;

/* Structure pour la liste des cases à supprimer */
typedef struct {
    Case tab[MAX_SUPP];
    int nb; /* IN/OUT: nombre de cases stockées */
} Groupes;

/* Ajoute une case dans la liste si absente */
void ajouter_case(Groupes *g, int lig, int col);

/* Détection globale de tous les groupes à supprimer */
int detecter_groupes(char plateau[LIGNES][COLS], Groupes *groupes);

/* Détecte un groupe horizontal à partir (lig,col) et renvoie sa longueur */
int detecter_ligne(char plateau[LIGNES][COLS], int lig, int col);

/* Détecte un groupe vertical à partir (lig,col) et renvoie sa longueur */
int detecter_colonne(char plateau[LIGNES][COLS], int lig, int col);

/* Détecte un rectangle d’items identiques de taille L x l
   Renvoie 1 si trouvé et ajoute les cases dans groupes, sinon 0 */
int detecter_rectangle(char plateau[LIGNES][COLS], Groupes *groupes,
                       int lig, int col, int L, int l);

/* Détecte une forme en H centrée (approximativement) sur (lig,col)
   Renvoie 1 si un H complet est trouvé et ajoute les cases dans groupes */
int detecter_H(char plateau[LIGNES][COLS], Groupes *groupes, int lig, int col);

#endif
