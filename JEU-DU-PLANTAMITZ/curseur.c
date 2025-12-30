#include "header.h"

void deplacer_curseur(Curseur *c, char touche){
    switch(touche){
    case 'z':
        if (c ->  ligne > 0) c -> ligne--;
        break;
    case 's':
        if (c ->ligne < L-1) c->ligne++;
        break;
    case 'q':
        if (c->colonne > 0 ) c->colonne--;
        break;
        case 'd':
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
