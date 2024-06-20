#define SNAKE_SIZE 4 /* Taille du serpent */
enum direction {TOP = 't', BOTTOM = 'b', LEFT = 'l', RIGHT = 'r'}; /* Enumération des déplacements possibles sur la grille */
typedef enum direction Direction; /* Définit un type Direction pour simplifier la syntaxe */

typedef struct struct_coord Coord; /* Définit un nouveau type Coord */
struct struct_coord /* Structure qui stocke des coordonnées x et y pour le serpent */
{
    int x;
    int y;
};

typedef struct struct_snake Snake; /* Définit un nouveau type Snake */
struct struct_snake /* Structure principale du serpent*/
{
    Coord pos[SNAKE_SIZE]; /* Stocke les positions de chacun des bouts du corps du serpent */
    Direction dir; /* Stocke la direction dans laquelle va le serpent*/
};

void crawl (Snake * s, int NBL, int NBC); /* Signature de la fonction crawl */