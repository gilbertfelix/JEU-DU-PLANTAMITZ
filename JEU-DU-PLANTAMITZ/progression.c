#include "header.h"

void sauvegarder_progression(const char *nom_joueur,int niveau_atteint,int score){
    FILE *fichier = fopen("plantamitz.txt", "w");

    if (fichier == NULL){
        printf("Erreur : impossible de sauvegarder la progression.\n");
        return;
    }

    fprintf(fichier, "%s\n", nom_joueur);
    fprintf(fichier, "%d\n", niveau_atteint);
    fprintf(fichier, "%d\n", score);

    fclose(fichier);
    printf("\n Progression sauvegardée ! \n");
}

int charger_progression(char *nom_joueur, int *niveau_atteint, int *score){

    FILE *fichier = fopen("plantamitz.txt", "r");

    if(fichier == NULL){
        return 0;
    }

    if(fscanf(fichier, "%49s\n%d\n%d", nom_joueur, niveau_atteint,score) != 3){
        fclose(fichier);
        return 0;
    }

    fclose(fichier);
    return 1;
}

void supprimer_sauvegarde(){
    remove("plantamitz.txt");
}
