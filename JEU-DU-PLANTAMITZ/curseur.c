#include "header.h"

void deplacer_curseur(Curseur *c, char touche){
    switch(touche){
    case 'z':
    case 72:
        if (c ->  ligne > 0) c -> ligne--;
        break;
    case 's':
         case 80:
        if (c ->ligne < L-1) c->ligne++;
        break;
    case 'q':
         case 75:
        if (c->colonne > 0 ) c->colonne--;
        break;
        case 'd':
             case 77:
        if (c->colonne < C-1) c->colonne++;
        break;
    }
}

void selectionner_item(Curseur *c){
    if (c->selectionne ){
        c-> selectionne = 0;
    } else {
          c-> selectionne = 1;
            c-> sel_i = c -> ligne;
             c-> sel_j = c -> colonne;
    }
}

void permuter_item(char tab[L][C], Curseur *c, char direction){
    if(!c->selectionne) return ;

    int position_i = c->sel_i;
    int position_j = c->sel_j;

    switch(direction){
        case 'z':
        if(c->sel_i > 0) position_i--;
        else return;
        break;
        case 's':
        if(c->sel_i < L-1) position_i++;
        else return;
        break;
        case 'q':
        if(c->sel_j > 0) position_j--;
        else return;
        break;
        case 'd':
        if(c->sel_j < C-1) position_j++;
        else return;
        break;
        default:
            return;

    }

    char temp = tab[c->sel_i][c->sel_j];
    tab[c->sel_i][c->sel_j] = tab[position_i][position_j];
    tab[position_i][position_j] = temp;

    /*c->colonne = position_j;
    c->sel_i = position_i;
    c->sel_j = position_j;*/

    c->selectionne =0;

}

int suppression(char tab[L][C], int marque[L][C]){
    int total = 0;
    for(int i =0 ; i<L;i++){
            for(int j =0 ; j< C; j++){
        marque[i][j  ] = 0;
            }
    }

    for(int i =0 ; i<L;i++){
             for(int j =0 ; j< C; j++){
                char item = tab[i][j];
                int longueur = 1;

                while(j + longueur < C && tab[i][j + longueur] == item){
                    longueur++;
                }

                if (longueur >= 3) {
                    for (int k = 0; k< longueur; k++){
                        marque[i][j+k]= 1;
                        total++;
                    }
                    j += longueur -1;
                }
             }
    }

    for (int j =0 ; j<C;j++){
        for(int i =0; i< L-2; i++){
            char item = tab[i][j];
            int longueur = 1;

            while(i + longueur < L && tab[i + longueur][j] == item){
                longueur ++;
            }

            if (longueur >= 3){
                    for(int k =0; k< longueur; k++){
                        if(marque[i +k][j] == 0) total++;
                        marque[i+k][j] =1;
                    }
                i += longueur -1;
            }
        }
    }

    for (int i = 0; i<L-1; i++){
        for(int j =0 ; j< C-1;j++){
            char item = tab[i][j];
            if (tab[i][j+1] == item && tab[i+1][j] == item && tab[i+1][j+1] == item ){

                if (marque[i][j] == 0) total++;
                if (marque[i][j+1] == 0) total++;
                if (marque[i+1][j] == 0) total++;
                if (marque[i+1][j+1] == 0) total++;

                marque[i][j] = 1;
                marque[i][j+1] = 1;
                marque[i +1][j] = 1;
                marque[i+1][j+1] = 1;
            }
        }
    }

     for (int i = 0; i<L-2; i++){
        for(int j =0 ; j< C-2;j++){
            char item = tab[i][j];
            if (tab[i][j+2] == item && tab[i + 1][j] == item && tab[i+1][j+1] == item && tab[i+1][j+2] == item && tab[i+2][j] == item && tab[i+2][j+2] == item  ){

                if (marque[i][j] == 0) total++;
                if (marque[i][j+2] == 0) total++;
                if (marque[i+1][j] == 0) total++;
                if (marque[i+1][j+1] == 0) total++;
                if (marque[i+1][j+2] == 0) total++;
                if (marque[i+2][j] == 0) total++;
                if (marque[i+2][j+2] == 0) total++;

                marque[i][j] = 1;
                marque[i][j+2] = 1;
                marque[i +1][j] = 1;
                marque[i+1][j+1] = 1;
                marque[i+1][j+2] = 1;
                marque[i+2][j] = 1;
                marque[i+2][j+2] = 1;
            }
        }
    }
    return total;
}

void supprimer_marques(char tab[L][C], int marque[L][C]){
    for(int i= 0; i<L;i++){
        for(int j=0;j<C;j++){
            if(marque[i][j]== 1){
                tab[i][j] = ' ';
            }
        }
    }
}

 void faire_tomber_item(char tab[L][C]){
     for(int j = 0;j<C;j++){
        int destination = L -1;

        for(int i = L-1; i>=0; i--){
            if(tab[i][j] !=' '){
                if(i != destination){
                    tab[destination][j]=tab[i][j];
                    tab[i][j] = ' ';
                }
                destination--;
            }
        }
     }
 }

 void remplir_vide(char tab[L][C]){
     for(int i =0; i< L; i++){
        for(int j = 0; j<C; j++){
            if (tab[i][j] == ' '){
                tab[i][j]= generer_item();
            }
        }
     }
 }

int stabiliser_plateau(char tab[L][C],Contrat *c){
     int total_supprime = 0;
     int marque[L][C];
      int nb;

      while((nb = suppression(tab,marque)) >0 ){
            int points = calculer_points(tab,marque);
                c->score += points;
            compter_items_supprime(tab,marque,c);
        total_supprime += nb;

        supprimer_marques(tab,marque);
        faire_tomber_item(tab);
        remplir_vide(tab);
      }
      return total_supprime;
 }
