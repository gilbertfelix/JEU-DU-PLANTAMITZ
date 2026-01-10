#include "header.h"

/**
*Génère un item spécial selon la longueur de l'alignement
*@param longueur : nombre d'items alignés
*@param horizontal: 1 si l'alignement horizontal, 0 si vertical
*@return : caractère reprèsentant l'tem spécial créé
*/

char generer_item_special(int longueur , int horizontal){

    if(longueur == 4){
        return BOMBE;
    } else if (longueur == 5){
        return horizontal ? ETOILE : ECLAIR;
    } else if (longueur >= 6){
        return ARC_EN_CIEL;
    }
    return ' ';
}
/**
*Détecte les alignements et crée des items spéciaux
*Version améliorée de suppression() qui gère les items spéciaux
*@param tab : plateau de jeu
*@param marque : tableau indiquant les cases à supprimer
*@return : nombre total d'items marqués pour suppression
*/

int suppression_special (char tab[L][C], int marque[L][C]){
    int total = 0;
    memset(marque, 0, sizeof(int)*L*C);

    int item_special_i = -1, item_special_j = -1;
    char type_special = ' ';

    //== VERIFICATION HORIZONTALE ==

    for(int i=0; i<L; i++){
        for(int j =0; j<C-2;j++){
            char item = tab[i][j];
            if(item == ' ') continue;
             if(item == BOMBE || item == ETOILE || item == ECLAIR || item == ARC_EN_CIEL) continue;

            int longueur = 1;
            while(j + longueur < C && tab[i][j + longueur] == item){
                longueur++;
            }

            if (longueur >= 3){
                for(int k = 0; k< longueur; k++){
                        if(!(longueur >= 4 && k == longueur/2)){
                    marque[i][j+k] =1;
                    total++;
                        }
                }

                if(longueur >= 4){
                    item_special_i = i;
                    item_special_j = j + longueur/2;
                    type_special = generer_item_special(longueur, 1);
                    marque[item_special_i][item_special_j] = 0;
                }
            }
            j += longueur -1;

        }
    }

    // == VERIFICATION VERTICALE ==
    for(int j = 0; j<C;j++){
        for(int i = 0; i< L-2;i++){
            char item = tab[i][j];
            if(item == ' ') continue;

            int longueur = 1;
            while(i + longueur < L && tab[i + longueur][j] == item){
                longueur++;
            }

            if(longueur >= 3){
                for(int k = 0;k< longueur; k++){
                    if(!(longueur >= 4 && k == longueur/2)){
                            if(marque[i + k][j] == 0){
                    marque[i + k][j] = 1;
                    total++;
                    }
                   }
                }


                if(longueur >= 4 && type_special == ' '){
                    item_special_i = i + longueur/2;
                    item_special_j = j;
                    type_special = generer_item_special(longueur, 0);

                    marque[item_special_i][item_special_j] = 0;
                }
            }
            i += longueur -1;
        }
    }
    // placer l'item spécial sur le plateau

    if(type_special != ' ' && item_special_i >=0){
        marque[item_special_i][item_special_j] = 0;
        tab[item_special_i][item_special_j] = type_special;
    }

    return total;
}

/**
*Active l'effet bombe : détruit 3*3 cases retour
*/


void activer_bombe(char tab[L][C], int marque[L][C], int i, int j){
    for(int di = -1; di <=1 ; di++){
        for(int dj = -1; dj <= 1; dj++){
            int ni = i + di;
            int nj = j + dj;
            if(ni >= 0 && ni < L && nj >= 0 && nj < C){
                marque[ni][nj] = 1;
            }
        }
    }
}
/**
*Active l'effet étoile : détruit toute la ligne
*/


void activer_etoile(char tab[L][C], int marque[L][C], int i, int j ){
    for (int jj =0 ; jj < C; jj++){
        marque[i][jj] = 1;
    }
}

/**
*Active l'effet éclair : détruit toute la colonne
*/



void activer_eclair(char tab[L][C], int marque[L][C], int i, int j ){
    for (int ii =0 ; ii < L; ii++){
        marque[ii][j] = 1;
    }
}

/**
*Active l'effet arc-en-ciel : détruit tous les items du même type
*/


void activer_arc_en_ciel(char tab[L][C], int marque[L][C], int i, int j, char item_cible ){
    for (int ii =0 ; ii < L; ii++){
            for(int jj = 0; jj < C; jj++){
                if(tab[ii][jj] == item_cible){
                    marque[ii][jj] = 1;
                }
            }
    }
}

/**
*Fonction principale d'activation des items spéciaux
*Détermine quel type d'item spécial est utilisé et active à son effet
*/


void activer_item_special(char tab[L][C], int marque[L][C], int i, int j){

    char item = tab[i][j];

    switch(item){
        case BOMBE:
            activer_bombe(tab, marque, i, j);
            marque[i][j] = 1;
            break;

              case ETOILE:
            activer_etoile(tab, marque, i, j);
            break;

              case ECLAIR:
            activer_eclair(tab , marque, i, j );
            break;

              case ARC_EN_CIEL:
                char cible= ' ';
                if(j>0 && tab[i][j-1] != ' ' && strchr("BELR", tab[i][j-1]) == NULL){
                    cible = tab[i][j-1];
                } else if(j< C-1 && tab[i][j+1] != ' ' && strchr("BELR", tab[i][j+1]) == NULL){
                    cible = tab[i][j+1];
                } else if(i< L-1 && tab[i+1][j] != ' ' && strchr("BELR", tab[i+1][j]) == NULL){
                    cible = tab[i+1][j];
                } else if(j > 0 && tab[i-1][j] != ' ' && strchr("BELR", tab[i-1][j]) == NULL){
                    cible = tab[i-1][j];
                }
                // Active l'effet si une cible valide est trouvée
                if (cible != ' '){
                    activer_arc_en_ciel(tab, marque, i, j, cible );
                }
                marque[i][j] = 1;
                break;
    }
}


