#include "header.h"

void initialiser_contrat(Contrat *c, int niveau){

    c->soleil_actuel =0;
    c->fraise_actuel =0;
    c->pomme_actuel =0;
    c->oignon_actuel =0;
    c->mandarine_actuel =0;
    c->coups_restants = 0;

    switch(niveau){
    case 1:
        c->soleil_requis = 24;
        c->fraise_requis=9;
        c->pomme_requis= 0;
        c->oignon_requis = 50;
        c->mandarine_requis=20;
        c->coups_max = 32;
        break;

    case 2:
         c->soleil_requis = 55;
        c->fraise_requis=35;
        c->pomme_requis= 30;
        c->oignon_requis = 35;
        c->mandarine_requis=20;
        c->coups_max = 45;
        break;

    case 3:
         c->soleil_requis = 40;
        c->fraise_requis=40;
        c->pomme_requis= 35;
        c->oignon_requis = 45;
        c->mandarine_requis=40;
        c->coups_max = 50;
        break;

    default:
         c->soleil_requis = 25;
        c->fraise_requis=25;
        c->pomme_requis= 25;
        c->oignon_requis = 25;
        c->mandarine_requis=25;
        c->coups_max = 30;
    }
}

void afficher_contrat(Contrat *c){
    printf("\n======= CONTRAT =======\n");

    if(c->soleil_requis > 0){
        Color(14,0);
        printf("S:%d/%d ", c->soleil_actuel,c->soleil_requis);
        Color(15,0);
    }

        if(c->fraise_requis > 0){
        Color(12,0);
        printf("F:%d/%d ", c->fraise_actuel,c->fraise_requis);
        Color(15,0);
        }

        if(c->pomme_requis > 0){
        Color(10,0);
        printf("P:%d/%d ", c->pomme_actuel,c->pomme_requis);
        Color(15,0);
        }

        if(c->oignon_requis > 0){
        Color(8,0);
        printf("O:%d/%d ", c->oignon_actuel,c->oignon_requis);
        Color(15,0);
        }

        if(c->mandarine_requis > 0){
        Color(13,0);
        printf("M:%d/%d", c->mandarine_actuel,c->mandarine_requis);
        Color(15,0);
        }

        printf("\nCoups : %d / %d\n",c->coups_restants,c->coups_max);
        printf("=====================================\n");
}
