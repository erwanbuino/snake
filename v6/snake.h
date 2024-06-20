enum direction {TOP = 't', BOTTOM = 'b', LEFT = 'l', RIGHT = 'r'}; /* Enumération des déplacements possibles sur la grille */
typedef enum direction Direction; /* Définit un type Direction pour simplifier la syntaxe */

typedef struct struct_coord Coord; /* Définit un nouveau type Coord */
struct struct_coord /* Structure qui stocke des coordonnées x et y pour le serpent */
{
    int x;
    int y;
    Coord * next;
};


struct struct_snake /* Structure principale du serpent*/
{
    Coord * segments_list; /* Stocke les positions de chacun des bouts du corps du serpent */
    Direction dir; /* Stocke la direction dans laquelle va le serpent*/
    int size;
};
typedef struct struct_snake Snake; /* Définit un nouveau type Snake */

void debug_snake (Snake * serpent);
Snake* new_snake (Direction depart);
void add_first(Coord **c, int p_x, int p_y);
void add_segment(Snake * s, int p_x, int p_y);
void free_snake (Snake * s);
Coord * get_index (Coord * l, int index);
Coord * get_queue (Coord * l);
void crawl (Snake * s, int NBL, int NBC); /* Signature de la fonction crawl */