#include <MLV/MLV_all.h>
#include <stdio.h>

#define NBL 8
#define NBC 6

enum cell {WALL, EMPTY, FRUIT};
void debug (char matrice[NBL][NBC+1], int nb_lignes, int nb_colonnes);
void draw_grid(char matrice[NBL][NBC+1], int nb_lignes, int nb_colonnes);