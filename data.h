#include <stdbool.h>

typedef struct sprite_s
{
    int x;
    int y;
    int w;
    int h;
}sprite_t;


typedef struct world_s
{
    sprite_t Personnage;
    
    int vitesse;
}world_t;

void init_sprite(sprite_t *sprite, int x, int y, int w, int h);

bool collision_haut(sprite_t *sprite, char** tab);
bool collision_bas(sprite_t *sprite, char** tab);
bool collision_droit(sprite_t *sprite, char** tab);
bool collision_gauche(sprite_t *sprite, char** tab);