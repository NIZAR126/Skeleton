#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_sprite {
    int x;
    int y;
    int w;
    int h;
} s_sprite_t;

typedef struct s_world {
    s_sprite_t* sprite;
    bool fin;
    int vies;
    int cles;
    int clesRecup;
    char** tab;
    int numTerrain;
} s_world_t;

void init_world(s_world_t* world, int x, int y, int w, int h);
bool collision_droit(s_sprite_t* sprite, char** tab, int nbCol);
bool collision_gauche(s_sprite_t* sprite, char** tab);
bool collision_haut(s_sprite_t* sprite, char** tab);
bool collision_bas(s_sprite_t* sprite, char** tab, int nbLig);
bool collision_droit_char(s_sprite_t* sprite, char c, char** tab);
bool collision_gauche_char(s_sprite_t* sprite, char c, char** tab);
bool collision_haut_char(s_sprite_t* sprite, char c, char** tab);
bool collision_bas_char(s_sprite_t* sprite, char c, char** tab);
bool collision_char(s_sprite_t* sprite, char c, char** tab);
void deplacements_map(s_world_t* world, int nbLig, int nbCol);

#endif
