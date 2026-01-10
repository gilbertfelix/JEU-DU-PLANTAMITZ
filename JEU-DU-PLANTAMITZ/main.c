#include "header.h"

int main() {

    srand(time(NULL)); // Initialisation du générateur aléatoire

    // == Déclaration des variables
    char plateau[L][C];
    Curseur curseur = { 0, 0, 0, 0, 0};
    char touche;
    Contrat contrat;
    int choix;

    Joueur joueur;
    int niveau_depart = 1;
    int score_precedent = 0;

    demarrer_musique();

    // == CHARGEMENT DE PROGRESSION ==
    if(charger_progression(joueur.nom,&niveau_depart, &score_precedent)){
        printf("\n Sauvegarde trouvee \n");
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
            // Initialise les données du joueur
            joueur.niveau_actuel = niveau_depart;
            joueur.score_total = score_precedent;

            // == BOUCLE PRINCIPALE DU MENU ==

    do{
    system("cls");
    printf("    PLANTAMITZ 2026  \n");

    printf("Joueur : %s\n\n", joueur.nom);
    printf("1.Jouer (Niveau %d)\n", joueur.niveau_actuel);
    printf("2.Regles du jeu\n");
    printf("3.Quitter\n");
    printf("Votre choix\n");

    scanf("%d",&choix);
    // == OPTION 1: JOUER ==
    if(choix == 1){

    // Initialise le niveau
    remplir_plateau(plateau);
    initialiser_contrat(&contrat,joueur.niveau_actuel);
    contrat.vies = 5;
    curseur.ligne =0;
    curseur.colonne=0;
    curseur.selectionne= 0;
    int jeu_termine = 0;
    int vies_niveau = 5;

    // == BOUCLE DU JEU ==

    while (!jeu_termine){
            system("cls");
            afficher_contrat(&contrat);


    afficher_plateau(plateau,&curseur);

            // == VERIFICATION : CONTRAT REMPLI ===
    if(contrat_rempli(&contrat)){
        joueur.score_total += contrat.score;


        afficher_contrat(&contrat);
        afficher_plateau(plateau,&curseur);

        printf("\n NIVEAU TERMINE \n");
        printf("\nScore du niveau : %d pts\n", contrat.score);
        printf("Score total : %d pts\n", joueur.score_total);

        //Passage au niveau suivant
        if(joueur.niveau_actuel < 3){
            joueur.niveau_actuel++;
            printf("\n Passage au niveau %d ! \n",joueur.niveau_actuel);
            sauvegarder_progression(joueur.nom,joueur.niveau_actuel,joueur.score_total);

            printf("\nAppuyer sur un touche...");
            getch();

            //Réinitialisation du niveau suivant
            remplir_plateau(plateau);
            initialiser_contrat(&contrat, joueur.niveau_actuel);
            vies_niveau = 5;
            contrat.vies = 5;
            curseur.ligne = 0;
            curseur.colonne = 0;
            curseur.selectionne = 0;
            continue;


        } else {
            printf(" NIVEAUX TERMINES FELICITATIONS !!! \n");
            supprimer_sauvegarde();
            joueur.niveau_actuel = 1;
             printf("\nAppuyer sur un touche...");
            getch();
            jeu_termine = 1;
        }
        continue;
    }

    // Vérification du temps écoulé
     if(temps_contrat(&contrat)<=0){
            vies_niveau--;
            contrat.vies = vies_niveau;

            printf("\n TEMPS ECOULE \n");
            printf("\nVies : %d\5\n", contrat.vies);

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
                contrat.vies = vies_niveau;
                curseur.ligne = 0;
                curseur.colonne = 0;
                curseur.selectionne = 0;
            } else {

                sauvegarder_progression(joueur.nom,joueur.niveau_actuel,joueur.score_total);
                jeu_termine = 1;
            }
            continue;

        }

        // verification : plus de coups

        if(contrat.coups_restants <= 0){
            vies_niveau--;
            contrat.vies = vies_niveau;

            /*system("cls");
            afficher_contrat(&contrat);
            afficher_plateau(plateau,&curseur);*/

            printf("\n PLUS DE COUPS \n");
            printf("\nVies : %d\5\n", vies_niveau);


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
                contrat.vies = vies_niveau; // Garder les vies
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

        // GESTION DES TOUCHES
    touche = getch();

     if(touche == 'm' || touche == 'M'){
                toggle_musique();
                getch();
                continue;
            }

    if(touche == 27 ) {
            //contrat.vies--;
            //break;
            sauvegarder_progression(joueur.nom,joueur.niveau_actuel,joueur.score_total);
            system("cls");
            //printf("\n>>> Vous avez quitté le niveau <<<\n");
            //printf("Vies restantes : %d/5\n", contrat.vies);
            printf("\n Progression sauvegardee! ");
            getch();
            jeu_termine = 1;
            continue;
    }
    if (touche == 32) {
        selectionner_item(&curseur);

        // si u item est sélectionné: permutation

    } else if (curseur.selectionne){

        int dest_i = curseur.sel_i;
        int dest_j = curseur.sel_j;

        // calcule la destination selon la touche

        if(touche == 'z' && curseur.sel_i > 0) dest_i--;
        else if(touche == 's' && curseur.sel_i < L-1) dest_i++;
        else if(touche == 'q' && curseur.sel_j > 0) dest_j--;
        else if(touche == 'd' && curseur.sel_j < C-1) dest_j++;
        else {
            curseur.selectionne = 0;
            continue;
        }

        // Récupère les items à échanger
        char item1 = plateau[curseur.sel_i][curseur.sel_j];
        char item2 = plateau[dest_i][dest_j];

        int item1_special = (item1 == BOMBE || item1 == ETOILE || item1 ==  ECLAIR  || item1 == ARC_EN_CIEL);
        int item2_special = (item2 == BOMBE || item2 == ETOILE || item2 ==  ECLAIR  || item2 == ARC_EN_CIEL);

        //Effectue la permutation
        plateau[curseur.sel_i][curseur.sel_j]=item2;
         plateau[dest_i][dest_j]=item1;

    //Vérifie les suppressions
        int marque[L][C];
        int nb = suppression_special(plateau, marque);

        //Actve les items spéciaux échangés

        if(item1_special || item2_special){
            if(item2_special){
                activer_item_special(plateau, marque, curseur.sel_i, curseur.sel_j);
            }
            if(item1_special){
                activer_item_special(plateau, marque, dest_i, dest_j);
            }
            nb = 1  ;
        }

        if(nb > 0){
               // int items_speciaux_trouves = 0;

                for(int i = 0; i<L; i++){
                    for(int j = 0; j< C;j++){
                        //if(marque[i][j] == 1 ){
                            char item = plateau[i][j];
                            if(item == BOMBE || item == ETOILE || item == ECLAIR || item == ARC_EN_CIEL){
                                if((i != curseur.sel_i || j !=curseur.sel_j) && (i != dest_i || j != dest_j)){
                                    activer_item_special(plateau, marque, i, j);
                                }
                                //items_speciaux_trouves = 1;
                            }
                        }
                    }


        contrat.coups_restants--;
        stabiliser_plateau(plateau, &contrat);


    } else{
            plateau[curseur.sel_i][curseur.sel_j] = item1;
            plateau[dest_i][dest_j] = item2;
            //deplacer_curseur(&curseur, touche);
            curseur.selectionne = 0;

    }
    } else{
        deplacer_curseur(&curseur,touche);
        }

    }


  }  else if (choix == 2){
    printf("OBJECTIF :\n");
    printf("Colletez les items demandes dans le contrat\n");
    printf("en un nombre limite de coups\n");

    printf("COMMANDES : \n");
    printf("z/q/d/s ou les fleches de direction : Pour deplacer le curseur\n");
    printf("ESPACE : Selectionner un item\n");
    printf("z/q/d/s : Permuter avec un autre item\n");
    printf("M : pour desactiver la musique\n");
    printf("m : pour activer la musique\n");
    printf("ESC : Pour quitter(coute une vie)\n");

    printf("ITEMS SPECIAUX\n");
    printf("B(Bombe) : Alignez 4 items - Detruit 3*3\n");
     printf("E(ETOILE) : Alignez 5 items  horizontaux- Detruit la ligne\n");
      printf("L(ECLAIR) : Alignez 5 items verticaux- Detruit la colonne\n");
    printf("Appuyer sur une touche...");
    getch();
    }

   } while(choix !=3);
    return 0;
}
