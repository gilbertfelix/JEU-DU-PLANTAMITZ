#include "header.h"


void initialiser_contrat(Contrat *c, int niveau){

    c->niveau_actuel = niveau;
    c->soleil_actuel =0;
    c->fraise_actuel =0;
    c->pomme_actuel =0;
    c->oignon_actuel =0;
    c->mandarine_actuel =0;
    c->score = 0;


    c->temps_debut = time(NULL);


    switch(niveau){
    case 1:
        c->soleil_requis = 10;
        c->fraise_requis=9;
        c->pomme_requis= 10;
        c->oignon_requis = 10;
        c->mandarine_requis=10;
        c->coups_max = 20;
        c->coups_restants = c->coups_max;
        c->temps_limite = 340;
        break;

    case 2:
         c->soleil_requis = 55;
        c->fraise_requis=35;
        c->pomme_requis= 30;
        c->oignon_requis = 35;
        c->mandarine_requis=20;
        c->coups_max = 45;
         c->coups_restants = c->coups_max;
         c->temps_limite = 240;
        break;

    case 3:
         c->soleil_requis = 40;
        c->fraise_requis=40;
        c->pomme_requis= 35;
        c->oignon_requis = 45;
        c->mandarine_requis=40;
        c->coups_max = 50;
         c->coups_restants = c->coups_max;
         c->temps_limite = 300;

        break;

    default:
         c->soleil_requis = 25;
        c->fraise_requis=25;
        c->pomme_requis= 25;
        c->oignon_requis = 25;
        c->mandarine_requis=25;
        c->coups_max = 30;
         c->coups_restants = c->coups_max;
         c->temps_limite = 180;
    }
}

void afficher_contrat(Contrat *c){
    gotoligcol(0, 0);
    printf("============== CONTRAT =============");

    gotoligcol(1, 0);

    int temps_restant = temps_contrat(c);
    int minutes = temps_restant / 60;
    int secondes = temps_restant%60;

    if(temps_restant<30) Color(12, 0);
    else if(temps_restant < 60)  Color(14, 0);
    else Color(10, 0);

    printf("== NIVEAU %d == Score: %d pts  vies: %d/5  Temps:%02d:%02d\n",c->niveau_actuel, c->score,c->vies,minutes,secondes);

    gotoligcol(2, 0);

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

        gotoligcol(3, 0);
        printf("Coups : %d / %d\n",c->coups_restants,c->coups_max);

        gotoligcol(4, 0);
        printf("=====================================");

}

int contrat_rempli(Contrat *c){
    int rempli =1 ;

    if(c->soleil_requis > 0 && c->soleil_actuel < c->soleil_requis) rempli = 0;
    if(c->fraise_requis > 0 && c->fraise_actuel < c->fraise_requis) rempli =0;
    if(c->pomme_requis > 0 && c->pomme_actuel < c->pomme_requis) rempli=0;
    if(c->oignon_requis > 0 && c->oignon_actuel < c->oignon_requis) rempli = 0;
    if(c->mandarine_requis > 0 && c->mandarine_actuel < c->mandarine_requis) rempli = 0;
    return rempli;
}

void compter_items_supprime(char tab[L][C], int marque[L][C],Contrat *c ){
    for(int i=0;i<L;i++){
        for(int j = 0;j<C;j++){
            if(marque[i][j] == 1){
                char item = tab[i][j];

               switch(item){
               case 'S':
               if(c->soleil_actuel < c->soleil_requis) c->soleil_actuel++;
               break;
               case 'F':
               if(c->fraise_actuel < c->fraise_requis) c->fraise_actuel++;
               break;
               case 'P':
               if(c->pomme_actuel < c->pomme_requis) c->pomme_actuel++;
               break;
               case 'O':
               if(c->oignon_actuel < c->oignon_requis) c->oignon_actuel++;
               break;
               case 'M':
               if(c->mandarine_actuel < c->mandarine_requis) c->mandarine_actuel++;
               break;
               }
            }
        }
    }
}

int temps_contrat(Contrat *c){
    time_t maintenant = time(NULL);
    int ecoule = (int)difftime(maintenant, c->temps_debut);
    int restant = c->temps_limite - ecoule;
    if(restant < 0) restant = 0;

    return restant;
}


int calculer_points(char tab[L][C], int marque[L][C]){
    int points =0;
    int visite[L][C] = {0};

    for(int i =0;i<L;i++){
        for(int j=0;j<C;j++){
            if(marque[i][j] == 1 && visite[i][j]==0){
                char item = tab[i][j];
                int longueur =0;
                int debut = j;

                while(j+longueur < C && tab[i][j + longueur] == item && marque[i][j+longueur]==1){
                    visite[i][j+longueur]=1;
                    longueur++;
                }

                if(longueur == 6){
                    int total_identique = 0;
                    for(int ii=0;ii<L;ii++){
                        for(int jj=0;jj<C;jj++){
                            if(tab[ii][jj]==item){
                                marque[ii][jj] =1;
                                total_identique++;
                            }
                        }
                    }
                    points+=total_identique;
                }else if (longueur>=3){
                    points +=longueur;
                }
            }
        }
    }

     for(int j =0;j<C;j++){
        for(int i=0;i<L;i++){
            if(marque[i][j] == 1 && visite[i][j]==0){
                char item = tab[i][j];
                int longueur =0;
                int debut = i;

                while(i+longueur < L && tab[i+longueur][j] == item && marque[i+longueur][j]==1){
                    visite[i+longueur][j]=1;
                    longueur++;
                }

                if(longueur == 6){
                    int total_identique = 0;
                    for(int ii=0;ii<L;ii++){
                        for(int jj=0;jj<C;jj++){
                            if(tab[ii][jj]==item){
                                marque[ii][jj] =1;
                                total_identique++;
                            }
                        }
                    }
                    points+=total_identique;
                }else if (longueur>=3){
                    points +=longueur;
                }
            }
        }
    }

    for(int i = 0;i<L-1;i++){
        for(int j=0;j<C-1;j++){
            if(marque[i][j] == 1 && visite[i][j] ==0){
                char item = tab[i][j];

                int hauteur =1;
                while(i+hauteur < L&& tab[i+hauteur][j] == item && marque[i+hauteur][j] ==1){
                    hauteur++;
                }

                int largeur =1;
                while(j+largeur <C && tab[i][j+largeur] == item && marque[i][j+largeur]==1){
                    largeur++;
                }
                int est_rectangle = 1;
                for(int ii=i;ii<i+hauteur && est_rectangle;ii++){
                    for(int jj=j;jj<j+largeur && est_rectangle;jj++){
                        if(tab[ii][jj] != item || marque[ii][jj] !=1){
                            est_rectangle =0;
                        }
                    }
                }

                if(est_rectangle && hauteur >= 2 && largeur >=2){
                    points += 2*(hauteur*largeur);

                    for(int ii =i; ii<i+hauteur;ii++){
                        for(int jj=j; jj <j+largeur;jj++){
                            visite[ii][jj]=1;
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<L-2;i++){
        for(int j=0;j<C-2;j++){
            if(marque[i][j] == 1 && visite[i][j] == 0){
                char item = tab[i][j];

                if(tab[i][j+2] == item && marque[i][j+2] == 1 &&
                   tab[i+1][j] == item && marque[i+1][j] == 1 &&
                   tab[i+1][j+1] == item && marque[i+1][j+1] == 1 &&
                   tab[i+1][j+2] == item && marque[i+1][j+2] == 1 &&
                   tab[i+2][j] == item && marque[i+2][j] == 1 &&
                   tab[i+2][j+2] == item && marque[i+2][j+2] == 1 ){

                    points += 2*7;

                    visite[i][j]=1;
                    visite[i][j+2]=1;
                    visite[i+1][j]=1;
                    visite[i+1][j+1]=1;
                    visite[i+1][j+2]=1;
                    visite[i+2][j]=1;
                    visite[i+2][j+2]=1;
                   }
            }
        }
    }
    return points;
}
