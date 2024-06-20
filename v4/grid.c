#include "grid.h"

/* Permet d'afficher la matrice du jeu pour déboger plus facilement */
void debug (char matrice[NBL][NBC+1]){
    int i,j;
    for (i=0; i<NBL; i++){ /* Affiche ligne par ligne */
        for (j=0; j<NBC; j++){ /* Affiche colonne par colonne */
            printf("%c ", matrice[i][j]); /* Affiche le caractère représentant chaque élément */
        }
        printf("\n");
    }
}

/* Calcule la taille d'un côté de carré pour remplir la fenêtre de jeu en totalité */
int compute_size (int w, int h){
    int a=1;
    while (w >= NBC*a && h >= NBL*a){ /* Cherche par tatonnement la valeur maximale du côté (sans que cela dépasse la fenêtre)*/
        a++;
    }
    return a;
}

/* Dessine la grille dans la fenêtre graphique en fonction de la matrice fournie par game.c*/
void draw_grid(char matrice[NBL][NBC+1]){
    int h = MLV_get_window_height(); /* Récupère la hauteuur de la résolution */
    int w = MLV_get_window_width(); /* Récupère la largeur de la résolution */
    int a = compute_size(w,h); /* Calcule la taille du côté a*/

    int i,j;
    for (i=0; i<NBL; i++){ /* Analyse ligne par ligne */
        for (j=0; j<NBC; j++){ /* Analyse colonne par colonne */
            if (matrice[i][j] == WALL){ /* Si un 'w' est rencontré on dessine un carré noir à la position */
                MLV_draw_filled_rectangle(j*a, i*a, a, a, MLV_COLOR_BLACK);
            }
            else if (matrice[i][j] == EMPTY){ /* Si un ' ' est rencontré on dessine un carré blanc à la position */
                MLV_draw_filled_rectangle(j*a, i*a, a, a, MLV_COLOR_WHITE);
            }
            else if (matrice[i][j] == FRUIT){ /* Si un 'f' est rencontré on dessine un carré rouge à la position */
                MLV_draw_filled_rectangle(j*a, i*a, a, a, MLV_COLOR_RED);
            }
            else if (matrice[i][j] == SNAKE){ /* Si un 's' est rencontré on dessine un carré bleu à la position */
                MLV_draw_filled_rectangle(j*a, i*a, a, a, MLV_COLOR_BLUE);
            }
        }
    }
}

/* Dessine le serpent sur la grille */
void place_snake (char grid[NBL][NBC+1], Snake *s){
    int i;
    for (i = 0; i< SNAKE_SIZE; i++){
        grid[s->pos[i].y][s->pos[i].x] = SNAKE; /* Récupère les positions des cases du serpent et modifie la grille en ajoutant 's'*/
    }
}

/* Déplace le serpent dans la direction indiquée par son champ dir de sa structure*/
Element move_snake (char grid[NBL][NBC+1], Snake *s){
    Element tete;

    int x = s->pos[SNAKE_SIZE-1].x; /* Récupère la position x de la dernière case */
    int y = s->pos[SNAKE_SIZE-1].y; /* Récupère la position y de la dernière case */
    grid[y][x] = EMPTY; /* Efface la dernière case du serpent */
    crawl(s); /* Déplace les positions du serpent dans la direction spécifiée */
    tete = grid[s->pos[0].y][s->pos[0].x];

    x = s->pos[0].x; /* Récupère la nouvelle position x de la première case */
    y = s->pos[0].y; /* Récupère la nouvelle position y de la première case */
    grid[y][x] = SNAKE; /* Définit la nouvelle case de la tête comme une case du serpent */
    return tete;
}