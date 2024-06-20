#include "grid.h"

/* Permet d'afficher l'aide sur les options */
void print_help () {
    printf(" -h --help               Affiche ce message d'aide.\n");
}

/* Main du programme qui permet de définir la grille avec une chaine de caractères */
int main(int argc, char * const *argv) {
    int next_option; /* Outils pour l'analyse des options */
    int width = 640, height = 480; /* Résolution de l'écran */
    /* const char * program_name = argv[0]; Nomb du programme */
    MLV_Keyboard_button touche = MLV_KEYBOARD_NONE; /* Variable qui stocke une touche de clavier */

    Snake s = {{{1,3},{1,2},{1,1},{1,0}},RIGHT}; /* Création du serpent avec ses coordonnées de départ*/
    char grid[NBL][NBC+1] = {
        
        "w                                  w",
        "                                    ",
        "               f                    ",
        "                                    ",
        "     f               f              ",
        "                                    ",
        "                                    ",
        "               f                    ",
        "                                    ",
        "                                    ",
        "         wwwwwwwwww                 ",
        "                                    ",
        "                                    ",
        "                                    ",
        "                                    ",
        "                                    ",
        "                  f                 ",
        "                                    ",
        "         f                f         ",
        "                                    ",
        "                 f                  ",
        "w                                  w"
    }; /* Grille de la carte du jeu*/

    /* Permet de décrire les options courtes et longues valides. */
    const char* const short_options = "h";
    const struct option long_options[] = {
        { "help",     0, NULL, 'h' },
        { NULL,       0, NULL, 0   }
    };
    
    /* Si le nombre d'arguments est supérieur à 1*/
    if (argc > 1){
        do {
            next_option = getopt_long (argc, argv, short_options, long_options, NULL);
            switch (next_option) { /* Analyse les options données en ligne de commande */
                case 'h': /* L'utilisateur demande de l'aide */
                    print_help ();
                    return 0;
                case '?': /* L'option saisie n'existe pas dans la liste des options*/
                    printf("Option incorrecte saisie, Voici le guide des commandes ci-dessous\n");
                    print_help ();
                    return 1;
                case -1: /* Fin des options.  */
                    break;
                default: /* Quelque chose d'autre : inattendu.  */
                    printf("FIN DU PROGRAMME, Voici le guide des commandes ci-dessous\n");
                    return 1;
            }
        } while (next_option != -1); /* Continue l'analyse de la liste des options fournies par l'utilisateur */
    }

    /* Ouverture de la fenêtre graphique */
    MLV_create_window( "SNAKE", "3R-IN1B", width, height );
    MLV_change_frame_rate( 24 ); /* Nombre de FPS*/
    
    /* Affiche le serpent sur la grille */
    place_snake(grid, &s);

    /* Vérifie si la touche ECHAP est pressée si oui le programme arrête son exécution */
    while(
        MLV_get_event (
            &touche, NULL, NULL,
            NULL, NULL,
            NULL, NULL, NULL,
            NULL
        ) == MLV_NONE ||
        touche != MLV_KEYBOARD_ESCAPE
    )
    {
        MLV_clear_window( MLV_COLOR_BROWN);

        /* Dessine la grille */
        draw_grid(grid);
        MLV_actualise_window();

        touche = MLV_KEYBOARD_NONE;
        MLV_delay_according_to_frame_rate();

        /* Déplace le serpent dans la direction indiquée dans de la champ dir de sa structure*/
        move_snake(grid, &s);
    }

    /* Libère la fenêtre graphique */
    MLV_free_window();
    return 0;
}