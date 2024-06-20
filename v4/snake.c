#include "grid.h"

/* Procédure qui permet de calculer les positions du corps du serpent après le déplacement dans la direction */
void crawl (Snake *s){
    int i;
    char dir = s->dir; /* Définit la direction dans laquelle aller */
    int newX;
    int newY;
    switch (dir) {
        case TOP:
            newX = s->pos[0].x; /* Conserve la position x actuelle */
            newY = ((s->pos[0].y)-1+NBL)%NBL; /* Calcul à voir sur site du TP3 */
            break;
        case BOTTOM:
            newX = s->pos[0].x; /* Conserve la position x actuelle */
            newY = ((s->pos[0].y)+1)%NBL; /* Calcul à voir sur site du TP3 */
            break;
        case LEFT:
            newX = ((s->pos[0].x)-1+NBC)%NBC; /* Calcul à voir sur site du TP3 */
            newY = s->pos[0].y; /* Conserve la position y actuelle */
            break;
        case RIGHT:
            newX = ((s->pos[0].x)+1)%NBC; /* Calcul à voir sur site du TP3 */
            newY = s->pos[0].y; /* Conserve la position y actuelle */
            break;
        default:
            newX = s->pos[0].x; /* Conserve la position x actuelle */
            newY = s->pos[0].y; /* Conserve la position y actuelle */
            break;
    }
    /* Effectue une rotation vers la droite de toute les cases du tableau */
    for (i = SNAKE_SIZE-1; i>0; i--){
        s->pos[i].x = s->pos[i-1].x;
        s->pos[i].y = s->pos[i-1].y;
    }
    /* Met à la position de la tête les nouvelles coordonnées calculées */
    s->pos[0].x = newX;
    s->pos[0].y = newY;
}