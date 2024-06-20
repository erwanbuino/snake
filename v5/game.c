#include "grid.h"

/*
 * Affichage de l'écran de victoire
 */
void win(){
    int x = 200;
    int y = 200;
    /* Définition de la police du texte */
    MLV_Font *font1 = MLV_load_font("fonts/atlantis.ttf", 28);
    MLV_Font *font2 = MLV_load_font("fonts/alegreya.ttf", 28);

    /* Nettoie la fenêtre graphique et ecrit dedans */
    MLV_clear_window(MLV_COLOR_BROWN);
    MLV_draw_text_with_font(x, y, "Vous avez gagne !", font1, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(x, y+50, "Felicitations", font2, MLV_COLOR_WHITE);

    MLV_actualise_window(); /* Met à jour l'affichage */
    MLV_wait_seconds(2); /* Attend 2 secondes */
    MLV_free_window(); /* Libère la fenêtre graphique */
}

/*
 * Affichage de l'écran de défaite
 */
void lose(char * chaine){
    int x = 200;
    int y = 200;
    /* Définition de la police du texte */
    MLV_Font *font1 = MLV_load_font("fonts/atlantis.ttf", 28);
    MLV_Font *font2 = MLV_load_font("fonts/alegreya.ttf", 28);

    /* Nettoie la fenêtre graphique et ecrit dedans */
    MLV_clear_window(MLV_COLOR_BROWN);
    MLV_draw_text_with_font(x, y, "Vous avez perdu ...", font1, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(x, y+50, chaine, font2, MLV_COLOR_WHITE);

    MLV_actualise_window(); /* Met à jour l'affichage */
    MLV_wait_seconds(2); /* Attend 2 secondes */
    MLV_free_window(); /* Libère la fenêtre graphique */
}

/* 
 * Affiche l'aide sur les options en renvoyant sur la sortie standard
 */
void print_help ()
{
    fprintf (stdout, "Options du programme : /game.out\n");
    fprintf (stdout,
    " -h --help          Affiche le message d'aide (celui-ci).\n"
    " -i --input         Spécifie le fichier d'intialisation de la grille.\n\n"
    "Exemples d'utilisation : ./game.out -h\n"
    "                          ./game.out -i map.txt\n"
    "                          ./game.out --input map.txt\n"
    );
}

/* 
 * Main du programme qui lit les options puis initialise la grille et fait tourner le jeu en continu
 */
int main(int argc, char * const *argv) {
    int next_option; /* Outils pour l'analyse des options */
    int width = 640, height = 480; /* Résolution de l'écran */
    int nb_fruits = 0; /* Compte le nombre de fruits sur la grille */
    int loop_count = 0; /* Compte les tours de boucle pour ralentir la fréquence de déplacement du serpent */
    char optionI = 0; /* Booléen qui vérifie s'il y a eu une option -i lors de la saisie du programme */
    MLV_Keyboard_button touche = MLV_KEYBOARD_NONE; /* Variable qui stocke une touche de clavier */
    FILE * fichier; /* Fichier qui ouvre la carte pour initialiser le jeu */    
    Element tete; /* Stocke la case de la tête juste après le déplacement */
    Grid * grille; /* Grille de jeu (structure qui stocke la carte et ses dimensions en longueur et largeur)*/
    Snake s = {{{1,4},{1,3},{1,2},{1,1}},RIGHT}; /* Création du serpent avec ses coordonnées de départ*/

    /* Structure qui enregistre les options courtes et longues valides */
    const char* const short_options = "hi:";
    const struct option long_options[] = {
        { "help",     0, NULL, 'h' },
        { "input",     1, NULL, 'i' },
        { NULL,       0, NULL, 0   }
    };

    /* Vérifie s'il y a plusieurs arguments ou non */
    if (argc > 1) {
        do {
            next_option = getopt_long (argc, argv, short_options, long_options, NULL); /* Récupère la première option - */
            switch (next_option) { /* Analyse les options données en ligne de commande */
                case 'h': /* L'utilisateur demande de l'aide */
                    print_help ();
                    exit(0);
                    break;
                case 'i': /* L'utilisateur entre un fichier de carte en paramètre */
                    fichier = fopen((char *)argv[optind-1],"r");
                    if (fichier == NULL){
                        fprintf(stderr,"Nom de fichier incorrect\n");
                        exit (1);
                    }
                    grille = initialise(fichier); /* Initialise la grille avec le fichier fourni */
                    optionI = 1; /* Met le "booléen" à 1 pour stocker le fait que la grille est déja intialisée */
                    break;
                case '?': /* L'option saisie n'existe pas dans la liste des options */
                    printf("Option incorrecte saisie, Voici le guide des commandes ci-dessous\n\n");
                    print_help ();
                    exit (1);
                    break;
                case -1: /* Fin des options */
                    break;
                default: /* Quelque chose d'autre : inattendu */
                    printf("FIN DU PROGRAMME, Voici le guide des commandes ci-dessous\n");
                    print_help();
                    exit (1);
            } 
        }while (next_option != -1); /* Continue l'analyse de la liste des options fournies par l'utilisateur */
    }
    
    if (optionI  == 0){  /*Vérifie s'il n'y a pas eu d'option -i*/
        fichier = fopen("./levels/default.txt","r");
        grille = initialise(fichier); /* Initialise la grille avec celle par défaut */
    }

    /* Ouverture de la fenêtre graphique */
    MLV_create_window( "SNAKE", "3R-IN1B", width, height );
    MLV_change_frame_rate( 24 ); /* Nombre de FPS*/
    
    /* Affiche le serpent sur la grille */
    place_snake(grille, &s);

    /* Compte le nombre de fruits sur la grille */
    compte_fruits(grille, &nb_fruits);

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
            tete = move_snake(grille, &s); /* Déplace le serpent dans la direction indiquée dans de la champ dir de sa structure*/
            switch (tete)
            {
            case FRUIT: /* Si le serpent rencontre un fruit on décrémente le compteur */
                nb_fruits--;
                break;
            case WALL: /* Si le serpent rentre dans un mur on lance la condition de défaite */
                lose("Vous êtes rentré dans un mur !");
                quitter(grille,0);
                break;
            case SNAKE: /* Si le serpent se mord la queue on lance la condition de défaite */
                lose("Vous vous êtes mangé la queue !");
                quitter(grille,0);
                break;
            default:
                break;
            }
            if (nb_fruits <= 0){
                win(); /* Lance la condition de victoire */
                quitter(grille,0);
            }
        }
        
        /* Dessine la grille et actualise la fenêtre */
        draw_grid(grille);
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
    quitter(grille, 0);
    return 0;
}