#include "header.h"

/**
*Sauvegarde la progression du joueur dans un fichier
*stocke : nom du joueur, niveau, score total
    */
void sauvegarder_progression(const char *nom_joueur,int niveau_atteint,int score){
    //ouvre lle fichoer en mode écriture
    FILE *fichier = fopen("plantamitz.txt", "w");

    if (fichier == NULL){
        printf("Erreur : impossible de sauvegarder la progression.\n");
        return;
    }
    //Ecrit les données dans le fichier
    fprintf(fichier, "%s\n", nom_joueur);
    fprintf(fichier, "%d\n", niveau_atteint);
    fprintf(fichier, "%d\n", score);

    fclose(fichier);
    printf("\n Progression sauvegardée ! \n");
}
/**
*charge la progression du joueur depuis un fichier
    */

int charger_progression(char *nom_joueur, int *niveau_atteint, int *score){
    //ouvre lle fichoer en mode lecture
    FILE *fichier = fopen("plantamitz.txt", "r");

    if(fichier == NULL){
        return 0;
    }
    //lit les 3 informations depuis le fichier

    if(fscanf(fichier, "%49s\n%d\n%d", nom_joueur, niveau_atteint,score) != 3){
        fclose(fichier);
        return 0;
    }

    fclose(fichier);
    return 1;
}
/**
*su^pprime le fichier de sauvegarde*/
void supprimer_sauvegarde(){
    remove("plantamitz.txt");
}
