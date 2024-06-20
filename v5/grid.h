#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "snake.h"

#define DIFFICULTY 4 /* Difficulté du jeu (diminuer ce chiffre fait accélerer le serpent)*/

/* Enumération des éléments trouvables sur la grille*/
enum Element {WALL = 'w', EMPTY = ' ', FRUIT = 'f', SNAKE = 's'};
typedef enum Element Element;

/*
 * Structure qui permet de stocker la grille du jeu ainsi que le nombre de lignes et de colonnes
 */
typedef struct struct_grid Grid;
struct struct_grid{
    char ** grid;
    int NBL;
    int NBC;
};

/* Signatures des fonctions ou procédures */
void quitter (Grid * grille, int code);
void debug (Grid * grille);
Grid * allocate_grid(int n, int m);
void free_grid(Grid * grille);
int compute_size (Grid * grille, int w, int h);
void draw_grid(Grid * grille);
void compte_fruits (Grid * grille, int *nb);
int compte_nb_lignes (FILE * fichier);
void copy (char * chaine, char * ligne);
Grid * initialise (FILE * fichier);
void place_snake (Grid * grille, Snake *s);
Element move_snake (Grid * grille, Snake * s);