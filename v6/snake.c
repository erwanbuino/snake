#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "snake.h"
#include "grid.h"

/*
 * Procédure qui affiche la matrice de la carte du jeu pour déboguer facilement
 */
void debug_snake (Snake * serpent){
    Coord * tempo = serpent->segments_list;
    if (tempo == NULL){
        printf("Le serpent est vide\n");
        return;
    }else if(tempo->next == NULL){
        printf("Le serpent n'a qu'un élément\n");
        return;
    }
    printf("Taille du serpent : %d\n", serpent->size);
    printf("Direction du serpent : %c\n", serpent->dir);
    printf("Coordonnées du serpent : \n");

    while (tempo != NULL){
        printf("x = %d, y = %d\n", tempo->x, tempo->y);
        tempo = tempo->next;
    }
}

Snake* new_snake (Direction depart){
    Snake* serpent = (Snake*) malloc(sizeof(Snake));
    if (serpent == NULL){
        fprintf(stderr,"Probleme d'allocation dans new_snake()");
        exit(1);
    }
    serpent->segments_list = NULL;
    serpent->size = 0;
    serpent->dir = depart;
    return serpent;
}

void add_first(Coord **c, int p_x, int p_y){
    Coord* tempo = (Coord*) malloc(sizeof(Coord));
    if(tempo == NULL){
        fprintf(stderr,"Probleme d'allocation dans add_first()");
        exit(1);
    }
    tempo->next = *c;
    tempo->x = p_x;
    tempo->y = p_y;
    *c = tempo;
}

void add_segment(Snake * s, int p_x, int p_y){
    Coord* tempo;
    Coord* save;
    Coord* new_segment = (Coord*) malloc (sizeof(Coord));

    if (s->segments_list == NULL){
        add_first(&(s->segments_list), p_x, p_y);
        s->size++;
        return;
    }

    tempo = s->segments_list;
    save = tempo;

    while (tempo->next != NULL){
        tempo = tempo->next;
    }
    new_segment->next = NULL;
    new_segment->x = p_x;
    new_segment->y = p_y;
    tempo->next = new_segment;
    s->segments_list = save;
    s->size ++;
}

void free_snake (Snake * s){
    Coord * tempo;
    while (s->segments_list != NULL){
        tempo = s->segments_list->next;
        free(s->segments_list);
        s->segments_list=tempo;
    }
    free(s->segments_list);
    free(s);
}

Coord * get_index (Coord * l, int index){
    int i;
    Coord * tempo = l;
    for (i = 0; i<index; i++){
        tempo = tempo->next;
        if (tempo == NULL){
            printf("Depassement\n");
            exit(1);
        }
    }
    return tempo;
}

Coord * get_queue (Coord * l){
    Coord * tempo = l;
    while (tempo->next != NULL){
        tempo = tempo -> next;
    }
    return tempo;
}

void rotate (Coord ** l){
    Coord* tempo = *l;
    Coord* save = *l;
    while (tempo->next->next != NULL){
        tempo = tempo->next;
    }
    tempo->next->next = save;
    *l = tempo->next;
    tempo->next = NULL;
}

/*
 * Procédure qui permet de calculer les positions du corps du serpent après le déplacement dans la direction
 */
void crawl (Snake * s, int NBL, int NBC){
    /*int i;
    Coord ** positions = &(s->segments_list); */
    int xHead = s-> segments_list -> x;
    int yHead = s-> segments_list -> y;
    
    switch (s->dir) {
        case TOP:
            yHead = (yHead-1+NBL)%NBL; /* Calcul à voir sur site du TP3 */
            break;
        case BOTTOM:
            yHead = (yHead+1)%NBL; /* Calcul à voir sur site du TP3 */
            break;
        case LEFT:
            xHead = (xHead-1+NBC)%NBC; /* Calcul à voir sur site du TP3 */
            break;
        case RIGHT:
            xHead = (xHead+1)%NBC; /* Calcul à voir sur site du TP3 */
            break;
    }
    /* Effectue une rotation vers la droite de toute les cases du tableau */
    rotate(&(s->segments_list));

    /* Met à la position de la tête les nouvelles coordonnées calculées */
    s->segments_list->x = xHead;
    s->segments_list->y = yHead;
}

