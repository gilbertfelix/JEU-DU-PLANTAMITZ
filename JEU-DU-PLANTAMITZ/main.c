#include "header.h"

int main() {

    srand(time(NULL)); // Initialisation du générateur aléatoire

    char plateau[L][C];
    Curseur curseur = { 0, 0, 0, 0, 0};
    char touche;
    Contrat contrat;
    int choix;

    Joueur joueur;
    int niveau_depart = 1;
    int score_precedent = 0;

    if(charger_progression(joueur.nom,&niveau_depart, &score_precedent)){
        printf("\n Sauvegarde trouvée \n");
        printf("Joueur : %s\n", joueur.nom);
        printf("Niveau atteint : %d\n", niveau_depart);
        printf("Score : %d\n", score_precedent);
        printf("Appuyer sur une touche...");
        getch();
            } else {
                system("cls");
                printf(" Bienvenue dans PLANTAMITZ ! \n");

                printf("Entrez votre nom: ");
                scanf("%49s", joueur.nom);
                niveau_depart = 1;
                score_precedent  = 0;
            }

            joueur.niveau_actuel = niveau_depart;
            joueur.score_total = score_precedent;

    do{
    system("cls");
    printf("    PLANTAMITZ 2026  \n");

    printf("Joueur : %s\n\n", joueur.nom);
    printf("1.Jouer (Niveau %d)\n", joueur.niveau_actuel);
    printf("2.Règles du jeu\n");
    printf("3.Quitter\n");
    printf("Votre choix\n");

    scanf("%d",&choix);
    if(choix == 1){

    // Génération du plateau initial
    // Plateau garanti stable dès la génération
    remplir_plateau(plateau);
    initialiser_contrat(&contrat,1);
    curseur.ligne =0;
    curseur.colonne=0;
    curseur.selectionne= 0;
    int jeu_termine = 0;

    while (!jeu_termine){
            system("cls");
            afficher_contrat(&contrat);

    // Affichage du plateau initial
    afficher_plateau(plateau,&curseur);

    if(contrat_rempli(&contrat)){
        joueur.score_total += contrat.score;

        system("cls");
        afficher_contrat(&contrat);
        afficher_plateau(plateau,&curseur);

        printf("\n NIVEAU TERMINE \n");
        printf("\nScore du niveau : %d pts\n", contrat.score);
        printf("Score total : %d pts\n", joueur.score_total);

        if(joueur.niveau_actuel < 3){
            joueur.niveau_actuel++;
            printf("\n Passage au niveau %d ! \n",joueur.niveau_actuel);
            sauvegarder_progression(joueur.nom,joueur.niveau_actuel,joueur.score_total);
        } else {
            printf(" NIVEAUX TERMINES FELICITATIONS !!! \n");
            supprimer_sauvegarde();
            joueur.niveau_actuel = 1;
        }
    }

     if(temps_contrat(&contrat)<=0){
            contrat.vies--;
            system("cls");
            afficher_contrat(&contrat);
            afficher_plateau(plateau,&curseur);

            printf("\n TEMPS ECOULE \n");
            printf("\nVies : %d\5\n", contrat.vies);

    /* printf("\n\n>>> PLUS DE COUPS ! <<<\n");
            printf("Vies restantes : %d/5\n", contrat.vies);*/

            if(contrat.vies <= 0) {
                printf("\n>>> VOUS AVEZ PERDU ! <<<\n");
                sauvegarder_progression(joueur.nom,joueur.niveau_actuel,joueur.score_total);
                printf("\nAppuie sur une touche...");
                getch();
                jeu_termine = 1;
                continue;
            }

            printf("\n(R)ecommencer le niveau | (Q)uitter\n");
            char choix_timeout = getch();

            if(choix_timeout == 'r' || choix_timeout == 'R') {
                // Recommencer le niveau
                remplir_plateau(plateau);
                initialiser_contrat(&contrat, joueur.niveau_actuel);
                //contrat.vies = contrat.vies; // Garder les vies
                curseur.ligne = 0;
                curseur.colonne = 0;
                curseur.selectionne = 0;
            } else {
                contrat.vies--;
                sauvegarder_progression(joueur.nom,joueur.niveau_actuel,joueur.score_total);
                jeu_termine = 1;
            }
            continue;

        }


        if(contrat.coups_restants <= 0){
            contrat.vies--;

            system("cls");
            afficher_contrat(&contrat);
            afficher_plateau(plateau,&curseur);

            printf("\n PLUS DE COUPS \n");
            printf("\nVies : %d\5\n", contrat.vies);

    /* printf("\n\n>>> PLUS DE COUPS ! <<<\n");
            printf("Vies restantes : %d/5\n", contrat.vies);*/

            if(contrat.vies <= 0) {
                printf("\n>>> VOUS AVEZ PERDU ! <<<\n");
                sauvegarder_progression(joueur.nom,joueur.niveau_actuel,joueur.score_total);
                printf("\nAppuie sur une touche...");
                getch();
                jeu_termine = 1;
                continue;
            }

            printf("\n(R)ecommencer le niveau | (Q)uitter\n");
            char choix_timeout = getch();

            if(choix_timeout == 'r' || choix_timeout == 'R') {
                // Recommencer le niveau
                remplir_plateau(plateau);
                initialiser_contrat(&contrat, joueur.niveau_actuel);
                //contrat.vies = contrat.vies; // Garder les vies
                curseur.ligne = 0;
                curseur.colonne = 0;
                curseur.selectionne = 0;
            } else {
                contrat.vies--;
                sauvegarder_progression(joueur.nom,joueur.niveau_actuel,joueur.score_total);
                jeu_termine = 1;
            }
            continue;

        }

    touche = getch();

    if(touche == 27 ) {
            //contrat.vies--;
            //break;
            sauvegarder_progression(joueur.nom,joueur.niveau_actuel,joueur.score_total);
            system("cls");
            //printf("\n>>> Vous avez quitté le niveau <<<\n");
            //printf("Vies restantes : %d/5\n", contrat.vies);
            printf("\n Progression sauvegardée! ");
            getch();
            jeu_termine = 1;
            continue;
    }
    if (touche == 32) {
        selectionner_item(&curseur);

    } else if (curseur.selectionne){

        int dest_i = curseur.sel_i;
        int dest_j = curseur.sel_j;

        if(touche == 'z' && curseur.sel_i > 0) dest_i--;
        else if(touche == 's' && curseur.sel_i < L-1) dest_i++;
        else if(touche == 'q' && curseur.sel_j > 0) dest_j--;
        else if(touche == 'd' && curseur.sel_j < C-1) dest_j++;
        else {
            curseur.selectionne = 0;
            continue;
        }

        char item1 = plateau[curseur.sel_i][curseur.sel_j];
        char item2 = plateau[dest_i][dest_j];

        plateau[curseur.sel_i][curseur.sel_j]=item2;
         plateau[dest_i][dest_j]=item1;


       // permuter_item(plateau,&curseur, touche);

        int marque[L][C];
        int nb = suppression(plateau,marque);

        if(nb > 0){

        contrat.coups_restants--;
        int total = stabiliser_plateau(plateau,&contrat);


            system("cls");
            afficher_contrat(&contrat);
            afficher_plateau(plateau,&curseur);
            getch();

    } else{
            plateau[curseur.sel_i][curseur.sel_j] = item1;
            plateau[dest_i][dest_j] = item2;
            deplacer_curseur(&curseur, touche);
            curseur.selectionne = 0;

            system("cls");
            afficher_contrat(&contrat);
            afficher_plateau(plateau,&curseur);
            getch();
    }
    } else{
        deplacer_curseur(&curseur,touche);
        }

    }


  }  else if (choix == 2){
    printf("OBJECTIF :\n");
    printf("Colletez les items demandés dans le contrat\n");
    printf("en un nombre limité de coups\n");

    printf("COMMANDES : \n");
    printf("z/q/d/s ou les flèches de direction : Pour déplacer le curseur");
    printf("ESPACE : Sélectionner un item\n");
    printf("z/q/d/s : Permuter avec un autre item\n");
    printf("ESC : Pour quitter(coûte une vie)\n\n");
    }

   } while(choix !=3);
    return 0;
}
