#include <MLV/MLV_all.h>
#include <stdio.h>

#define NBL 8
#define NBC 6

void debug (char matrice[NBL][NBC+1], int nb_lignes, int nb_colonnes){
    int i,j;
    for (i=0; i<nb_lignes; i++){
        for (j=0; j<nb_colonnes; j++){
            printf("%c ", matrice[i][j]);
        }
        printf("\n");
    }
}

int compute_size (int w, int h){
    int a=1;
    while (w >= NBC*a && h >= NBL*a){
        a++;
    }
    return a;
}

void draw_grid(char matrice[NBL][NBC+1], int nb_lignes, int nb_colonnes){
    int h = MLV_get_window_height();
    int w = MLV_get_window_width();
    int a = compute_size(w,h);

    int i,j;
    for (i=0; i<nb_lignes; i++){
        for (j=0; j<nb_colonnes; j++){
            if (matrice[i][j] == 'b'){
                MLV_draw_filled_rectangle(j*a, i*a, a, a, MLV_COLOR_BLACK);
            }
            else if (matrice[i][j] == 'w'){
                MLV_draw_filled_rectangle(j*a, i*a, a, a, MLV_COLOR_WHITE);
            }
            else if (matrice[i][j] == 'r'){
                MLV_draw_filled_rectangle(j*a, i*a, a, a, MLV_COLOR_RED);
            }
        }
    }
}