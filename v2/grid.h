#include <MLV/MLV_all.h>
#include <stdio.h>

#define NBL 22
#define NBC 36
enum Element {WALL = 'w', EMPTY = ' ', FRUIT = 'f'};

void debug (char matrice[NBL][NBC+1]);
int compute_size (int w, int h);
void draw_grid(char matrice[NBL][NBC+1]);