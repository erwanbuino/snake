#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "snake.h"
#include "grid.h"

/*
 * Procédure qui quitte proprement le programme en libérant la mémoire 
 */
void quitter (Grid * grille, Snake * serpent, int code){
    free_grid(grille); /* Libère les allocations de mémoire */
    free_snake(serpent);
    exit(code);
}

/*
 * Procédure qui affiche la matrice de la carte du jeu pour déboguer facilement
 */
void debug_grid (Grid * grille){
    int i,j;
    for (i=0; i<grille->NBL; i++){ /* Affiche ligne par ligne */
        for (j=0; j<grille->NBC; j++){ /* Affiche colonne par colonne */
            printf("%c ", grille->grid[i][j]); /* Affiche le caractère représentant chaque élément */
        }
        printf("\n");
    }
}

/*
 * Alloue de l'espace mémoire pour la grille du jeu
 */
Grid * allocate_grid(int n, int m){
    int i;
    Grid * grille = (Grid*) malloc(sizeof(Grid)); /* Alloue en mémoire de l'espace pour la structure de type Grid */
    grille->grid = (char**) malloc(sizeof(char*)*n); /* Alloue en mémoire de l'espace pour le tableau à 2 dimensions */
    
    for (i = 0; i<n; i++){ /* Boucle qui parcourt le tableau ligne par ligne */
        grille->grid[i] = (char*) malloc(sizeof(char)*m); /* Alloue en mémoire de l'espace pour le tableau qui stockera chaque ligne */
    }
    grille->NBL = n; /* Définit le nombre de ligne selon le paramètre */
    grille->NBC = m; /* Définit le nombre de colonnes selon le paramètre */
    return grille;
}

/*
 * Libère l'espace mémoire alloué pour la grille
 */
void free_grid(Grid * grille){
    int i;
    for (i = 0; i<grille->NBL; i++){ /* Libère l'espace mémoire ligne par ligne */
        free(grille->grid[i]);
    }
    free(grille->grid); /* Libère l'espace mémoire de la totalité de la grille */
    free(grille); /* Libère l'espace mémmoire de la totalité de la structure */
}

/* 
 * Calcule la taille d'un côté de carré pour remplir la fenêtre de jeu en totalité 
 * Deux méthodes sont présentes : une qui cherche par tatonnement et l'autre qui réalise directement le calcul
 * L'une n'affiche pas assez de la grille (par tatonnement) et l'autre affiche trop (par le calcul)
 */
int compute_size (Grid * grille, int w, int h){
    /* Cherche par tatonnement la valeur maximale du côté (sans que cela dépasse la fenêtre)
    int a=1;
    while (w >= grille->NBC*a-1 && h >= grille->NBL*a-1){ 
        a++;
    }
    return a;
    */
    float a_w = w/grille->NBC;
    float a_h = h/grille->NBL;
    if (a_h < a_w){
        return (int) a_h;
    }else {
        return (int) a_w;
    }
}

/* Dessine la grille dans la fenêtre graphique en fonction de la matrice fournie en paramètre */
void draw_grid(Grid * grille){
    int h = MLV_get_window_height(); /* Récupère la hauteur de la résolution */
    int w = MLV_get_window_width(); /* Récupère la largeur de la résolution */
    int a = compute_size(grille, w,h); /* Calcule la taille du côté a*/

    int i,j;
    for (i=0; i<grille->NBL; i++){ /* Analyse ligne par ligne */
        for (j=0; j<grille->NBC; j++){ /* Analyse colonne par colonne */
            if (grille->grid[i][j] == WALL){ /* Si un 'w' est rencontré on dessine un carré noir à la position */
                MLV_draw_filled_rectangle(j*a, i*a, a, a, MLV_COLOR_BLACK);
            }
            else if (grille->grid[i][j] == EMPTY){ /* Si un ' ' est rencontré on dessine un carré blanc à la position */
                MLV_draw_filled_rectangle(j*a, i*a, a, a, MLV_COLOR_WHITE);
            }
            else if (grille->grid[i][j] == FRUIT){ /* Si un 'f' est rencontré on dessine un carré rouge à la position */
                MLV_draw_filled_rectangle(j*a, i*a, a, a, MLV_COLOR_RED);
            }
            else if (grille->grid[i][j] == SNAKE){ /* Si un 's' est rencontré on dessine un carré bleu à la position */
                MLV_draw_filled_rectangle(j*a, i*a, a, a, MLV_COLOR_BLUE);
            }
        }
    }
}

/* Fonction qui permet de mettre à jour le compte du nombre de fruits*/
void compte_fruits (Grid * grille, int *nb){
    int i,j;
    for (i=0; i<grille->NBL; i++){
        for (j=0; j<grille->NBC; j++){
            if (grille->grid[i][j] == 'f'){ /* Si l'on rencontre un fruit sur la grille */
                *nb += 1; /* Incrémente le nombre de fruits */
            }
        }
    }
}

/*
 * Compte le nombre de lignes du fichier en paramètre
 */
int compte_nb_lignes (FILE * fichier){
    size_t taille = 0; /* Stocke la taille de la ligne lue */
	char * chaine = NULL; /* Buffer qui stocke la ligne qui est lue */
    int compteur = 0; /* Permet de compter le nombre de lignes */
    while (getline(&chaine,&taille,fichier) != -1){ /* Si la ligne a pu être lue elle renverra au minimum 1 */
        compteur++;
    }
    free(chaine);
    return compteur;
}

/* 
 * Copie une chaine de caractère dans une autre
 */
void copy (char * chaine, char * ligne){
    int i = 0;
    while (chaine[i] != '\0' && chaine[i] != '\n'){ /* Tant que le caractère de fin de ligne ou de retour à la ligne n'est pas rencontré */
        ligne[i] = chaine[i];
        i++;
    }
}

/*
 * Initialise la grille avec le fichier fourni en paramètre
 */
Grid * initialise (FILE * fichier, Snake * serpent){
    int nbl,nbc;
    size_t taille = 0;
    char * chaine = NULL;
    Grid * grille;
    int i;

    nbl = compte_nb_lignes(fichier); /* Compte le nombre de lignes */
    rewind(fichier); /* Remet la position de lecture du fichier au début */
    nbc = getline(&chaine,&taille,fichier); /* Récupère la taille de la première ligne */
    if(nbc == -1){ /* Si la valeur de retour pour la ligne 1 est -1 alors problème sur le fichier */
        fprintf(stderr,"ERREUR : Le fichier est vide\n");
        exit(1);
    }
    else{
        nbc--; /* On enleve 1 car getline() compte le retour à la ligne */
    }

    grille = allocate_grid(nbl,nbc); /* Alloue l'espace mémoire pour une grille */
    copy(chaine,grille->grid[0]); /* Copie la première ligne du fichier dans la grille */

    /* Boucle qui parcourt tout le fichier ligne par ligne */
    for (i=1;i<nbl;i++) {
        int size_tmp = getline(&chaine,&taille,fichier); /* Récupère la taille de la ligne */
        if(size_tmp!=nbc+1){ /* Vérifie si la taille de la ligne est la même que nbc */
            fprintf(stderr,"ERREUR : Toutes les lignes n'ont pas la même taille\n");
            quitter(grille, serpent, 1);
        }
        copy(chaine,grille->grid[i]); /* Copie la i-ème ligne dans la grille*/
    }
    free(chaine); /* Libère l'espace mémoire du buffer */
    return grille;
}

/* 
 * Dessine le serpent sur la grille
 */
void place_snake (Grid * grille, Snake *s){
    int i;
    Coord * positions = s->segments_list;
    for (i = 0; i< s->size; i++){
        grille->grid[positions->y][positions->x] = SNAKE; /* Récupère les positions des cases du serpent et modifie la grille en ajoutant 's'*/
        positions = positions->next;
    }
}

/*
 * Déplace le serpent dans la direction indiquée par son champ dir de sa structure
 */
Element move_snake (Grid * grille, Snake * s){
    Element tete;
    Coord * queue = get_queue(s->segments_list);
    int x = queue->x; /* Récupère la position x de la dernière case */
    int y = queue->y; /* Récupère la position y de la dernière case */
    /*printf("x : %d\ty : %d\n", x, y);*/
    grille->grid[y][x] = EMPTY; /* Efface la dernière case du serpent */
    crawl(s, grille->NBL, grille->NBC); /* Déplace les positions du serpent dans la direction spécifiée */
    tete = grille->grid[s->segments_list->y][s->segments_list->x];

    x = s->segments_list->x; /* Récupère la nouvelle position x de la première case */
    y = s->segments_list->y; /* Récupère la nouvelle position y de la première case */
    grille->grid[y][x] = SNAKE; /* Définit la nouvelle case de la tête comme une case du serpent */
    return tete;
}
