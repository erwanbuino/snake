#include "grid.h"

void win(){
    int x = 200;
    int y = 200;
    /* Définition de la police du texte */
    MLV_Font *font1 = MLV_load_font("atlantis-bold.otf", 28);
    MLV_Font *font2 = MLV_load_font("Alegreya-Bold.ttf", 28);

    /* Nettoie la fenêtre graphique et ecrit dedans */
    MLV_clear_window(MLV_COLOR_BROWN);
    MLV_draw_text_with_font(x, y, "Vous avez gagne !", font1, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(x, y+50, "Felicitations", font2, MLV_COLOR_WHITE);

    MLV_actualise_window(); /* Met à jour l'affichage */
    MLV_wait_seconds(2); /* Attend 2 secondes */
    MLV_free_window(); /* Libère la fenêtre graphique */
    exit(0); /* Quitte le programme */
}

void lose(char * chaine){
    int x = 200;
    int y = 200;
    /* Définition de la police du texte */
    MLV_Font *font1 = MLV_load_font("atlantis-bold.otf", 28);
    MLV_Font *font2 = MLV_load_font("Alegreya-Bold.ttf", 28);

    /* Nettoie la fenêtre graphique et ecrit dedans */
    MLV_clear_window(MLV_COLOR_BROWN);
    MLV_draw_text_with_font(x, y, "Vous avez perdu ...", font1, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(x, y+50, chaine, font2, MLV_COLOR_WHITE);

    MLV_actualise_window(); /* Met à jour l'affichage */
    MLV_wait_seconds(2); /* Attend 2 secondes */
    MLV_free_window(); /* Libère la fenêtre graphique */
    exit(0); /* Quitte le programme */
}

/* Fonction qui permet de mettre à jour le compte du nombre de fruits*/
void compte_fruits (char grid[NBL][NBC+1], int *nb){
    int i,j;
    for (i=0; i<NBL; i++){
        for (j=0; j<NBC; j++){
            if (grid[i][j] == 'f'){
                *nb += 1; /* Incrémente le nombre de fruits */
            }
        }
    }
}

/* Permet d'afficher l'aide sur les options */
void print_help (FILE* stream, int exit_code)
{
  fprintf (stream, "Utilisation : /game.out options \n");
  fprintf (stream,
           " -h --help               Affiche ce message.\n"
           " -i --input              Spécifie le fichier d'intialisation de la grille.\n"
           );
  exit (exit_code); /* Quitte le programme avec le code envoyé en paramètre*/
}

/* Initialise la grille avec le fichier d'input */
void initialise (FILE * fichier, char grid[NBL][NBC+1]){
    int i,j;
    char tempo; /* Stocke temporairement le caractère de la grille */
    
    for (i = 0; i<NBL; i++){ /* Evolue ligne par ligne */
        for (j = 0; j<NBC+1; j++){ /* Evolue colonne par colonne */
            tempo = fgetc(fichier); /* Récupère un caractère du fichier (évolue à chaque fois) */
            if (tempo != '\n'){ /* Vérifie si c'est égal au retour de ligne */
                grid[i][j] = tempo; /* Sauvegarde le caractère récupéré */
            }
        }
    }
}

/* Main du programme qui permet de définir la grille avec une chaine de caractères */
int main(int argc, char * const *argv) {
    int next_option; /* Outils pour l'analyse des options */
    int width = 640, height = 480; /* Résolution de l'écran */
    FILE * fichier; /* Fichier de la map avec option -i */
    int nb_fruits = 0; /* Compte le nombre de fruits sur la grille */
    MLV_Keyboard_button touche = MLV_KEYBOARD_NONE; /* Variable qui stocke une touche de clavier */
    Element tete; /* Stocke la case de la tête juste après le déplacement */
    int loop_count=0; /* Compte les tours de boucle */

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
    };
    /* Grille de la carte du jeu*/

    /* Permet de décrire les options courtes et longues valides. */
    const char* const short_options = "hi:";
    const struct option long_options[] = {
        { "help",     0, NULL, 'h' },
        { "input",     1, NULL, 'i' },
        { NULL,       0, NULL, 0   }
    };
    
    /* Si le nombre d'arguments est supérieur à 1*/
    if (argc > 1) {
        do {
            next_option = getopt_long (argc, argv, short_options, long_options, NULL);
            switch (next_option) { /* Analyse les options données en ligne de commande */
                case 'h': /* L'utilisateur demande de l'aide */
                    print_help (stdout, 0);
                    break;
                case 'i': /* */
                    fichier = fopen((char *)argv[optind-1],"r");
                    if (fichier == NULL){
                        fprintf(stderr,"Nom de fichier incorrect\n");
                        exit (1);
                    }
                    initialise(fichier, grid);
                    break;
                case '?': /* L'option saisie n'existe pas dans la liste des options */
                    printf("Option incorrecte saisie, Voici le guide des commandes ci-dessous\n");
                    print_help (stdout, 1);
                    break;
                case -1: /* Fin des options.  */
                    break;
                default: /* Quelque chose d'autre : inattendu.  */
                    printf("FIN DU PROGRAMME, Voici le guide des commandes ci-dessous\n");
                    exit (1);
            } 
        }while (next_option != -1); /* Continue l'analyse de la liste des options fournies par l'utilisateur */
    }
    
    /* Ouverture de la fenêtre graphique */
    MLV_create_window( "SNAKE", "3R-IN1B", width, height );
    MLV_change_frame_rate( 24 ); /* Nombre de FPS*/
    
    /* Affiche le serpent sur la grille */
    place_snake(grid, &s);

    /* Compte le nombre de fruits sur la grille */
    compte_fruits(grid, &nb_fruits);

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
        MLV_clear_window( MLV_COLOR_BROWN); /* Nettoie la fenêtre graphique */

        loop_count = (loop_count+1)%DIFFICULTY; /* Vérifie que l'on a fait un certain nombre de tours de boucle */

        if(loop_count == 0){
            tete = move_snake(grid, &s); /* Déplace le serpent dans la direction indiquée dans de la champ dir de sa structure*/
            switch (tete)
            {
            case FRUIT: /* Si le serpent rencontre un fruit on décrémente le compteur */
                nb_fruits--;
                break;
            case WALL: /* Si le serpent rentre dans un mur on lance la condition de défaite */
                lose("Vous êtes rentré dans un mur !");
                break;
            case SNAKE: /* Si le serpent se mord la queue on lance la condition de défaite */
                lose("Vous vous êtes mangé la queue !");
                break;
            default:
                break;
            }
            if (nb_fruits <= 0){
                win(); /* Lance la condition de victoire */
            }
        }
        
        /* Dessine la grille et actualise la fenêtre */
        draw_grid(grid);
        MLV_actualise_window();

        /* Analyse les touches du clavier pour changer la direction dans laquelle va le serpent */
        switch(touche)
        {
            case MLV_KEYBOARD_UP :
                s.dir = TOP;
                break;
            case MLV_KEYBOARD_DOWN :
                s.dir = BOTTOM;
                break;
            case MLV_KEYBOARD_LEFT :
                s.dir = LEFT;
                break;
            case MLV_KEYBOARD_RIGHT :
                s.dir = RIGHT;
                break;
            default:
                break;
        }
        touche = MLV_KEYBOARD_NONE;
        MLV_delay_according_to_frame_rate();
    }

    /* Libère la fenêtre graphique */
    MLV_free_window();
    return 0;
}