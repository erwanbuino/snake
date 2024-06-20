#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "snake.h"

#define NBL 22 /* Nombre de lignes de la grille */
#define NBC 36 /* Nombre de colonnes de la grille */
#define DIFFICULTY 4 /* Difficulté du jeu (diminue)*/
enum Element {WALL = 'w', EMPTY = ' ', FRUIT = 'f', SNAKE = 's'}; /* Enumération des éléments trouvables sur la grille*/
typedef enum Element Element;

/* Signatures des fonctions ou procédures */
void debug (char matrice[NBL][NBC+1]);
int compute_size (int w, int h);
void draw_grid(char matrice[NBL][NBC+1]);
void print_help ();
void place_snake (char grid[NBL][NBC+1], Snake *s);
Element move_snake (char grid[NBL][NBC+1], Snake *s);