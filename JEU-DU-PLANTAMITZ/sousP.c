#include "header.h"

// =========================
// Fonction 1 : Générer un item aléatoire parmi S,F,P,O,M
// =========================
char generer_item(void) {
    char item[] = {'S', 'F', 'P', 'O', 'M'};
    return item[rand() % 5];
}

// =========================
// Fonction 2 : Remplir le plateau
// Génération contrôlée : plateau stable dès le départ
// =========================
void remplir_plateau(char tab[L][C]) {

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {

            char c;
            int valide = 0;

            // Boucle jusqu'à trouver un item qui ne crée pas d'alignement

            while (!valide) {
                c = generer_item();
                valide = 1;

                // Alignement horizontal interdit
                if (j >= 2 &&
                    tab[i][j-1] == c &&
                    tab[i][j-2] == c)
                    valide = 0;

                // Alignement vertical interdit
                if (valide && i >= 2 &&
                    tab[i-1][j] == c &&
                    tab[i-2][j] == c)
                    valide = 0;

                // Rectangle 2x2 interdit
                if (valide && i >= 1 && j >= 1 &&
                    tab[i-1][j] == c &&
                    tab[i][j-1] == c &&
                    tab[i-1][j-1] == c)
                    valide = 0;

                // Figure en H interdite
                if (valide && i >= 2 && j >= 2 &&
                    tab[i][j-2] == c &&
                    tab[i-1][j-2] == c &&
                    tab[i-1][j-1] == c &&
                    tab[i-1][j]   == c &&
                    tab[i-2][j-2] == c &&
                    tab[i-2][j]   == c)
                    valide = 0;
            }

            tab[i][j] = c;
        }
    }
}

// =========================
// Fonction 3 : Détection des alignements
// Utilisée PENDANT le jeu
// =========================
int alignement_existe(char tab[L][C]) {

    // Horizontaux
    for (int i = 0; i < L; i++) {
        int count = 1;
        for (int j = 1; j < C; j++) {
            if (tab[i][j] == tab[i][j-1]) {
                count++;
                if (count >= 3) return 1;
            } else count = 1;
        }
    }

    // Verticaux
    for (int j = 0; j < C; j++) {
        int count = 1;
        for (int i = 1; i < L; i++) {
            if (tab[i][j] == tab[i-1][j]) {
                count++;
                if (count >= 3) return 1;
            } else count = 1;
        }
    }

    // Rectangle 2x2
    for (int i = 0; i < L - 1; i++)
        for (int j = 0; j < C - 1; j++) {
            char x = tab[i][j];
            if (tab[i][j+1] == x &&
                tab[i+1][j] == x &&
                tab[i+1][j+1] == x)
                return 1;
        }

    // Figure en H
    for (int i = 0; i < L - 2; i++)
        for (int j = 0; j < C - 2; j++) {
            char x = tab[i][j];
            if (tab[i][j+2] == x &&
                tab[i+1][j] == x &&
                tab[i+1][j+1] == x &&
                tab[i+1][j+2] == x &&
                tab[i+2][j] == x &&
                tab[i+2][j+2] == x)
                return 1;
        }

    return 0;
}

// =========================
// Gestion des couleurs et affichage
// =========================
void Color(int couleurDuTexte, int couleurDeFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}
/**
*Affiche un item avec sa couleur correspondante
*/

void afficher_items(char item) {
    switch(item) {
        case BOMBE:
            Color(4, 0);
            printf("B");
            break;

            case ETOILE:
            Color(11, 0);
            printf("E");
            break;

            case ECLAIR:
            Color(14, 0);
            printf("L");
            break;

            case ARC_EN_CIEL:
            Color(13, 0);
            printf("R");
            break;
        case 'S':
             Color(14,0);
             printf("S");
              break;
        case 'F':
            Color(12,0);
            printf("F");
             break;
        case 'P':
            Color(10,0);
            printf("P");
             break;
        case 'O':
            Color(8,0);
            printf("O");
              break;
        case 'M':
             Color(13,0);
             printf("M");
              break;
        default:
            Color(15,0);
            printf("  ");
            break;
    }
    Color(15,0);
}

/**
*Affiche le plateau  complet avec le curseur
*/

void afficher_plateau(char tab[L][C], Curseur *c) {
    for (int i = 0; i < L; i++) {

        for (int j = 0; j < C; j++) {
            gotoligcol(5 + i , 2+ (j*2));

            char  item = tab[i][j];

            //Item sélctionné : affichage en minuscule
            if (c->selectionne && i == c->sel_i && j == c->sel_j){
                item = tolower(item);
            }

            //positionnement du curseur : fond blanc
            if(i== c->ligne && j == c-> colonne ){
                Color(0,15);
                printf("%c ",item);
                Color(0,15);
            }else {
                 afficher_items(tab[i][j]);
            }

        }
    }
}
/**
*Positionne le curseur console à une position donnée
*/

void gotoligcol( int lig, int col )
{
COORD mycoord;
mycoord.X = col;
mycoord.Y = lig;
SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}


