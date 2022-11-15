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
    int vitesse;
    bool fin;
} s_world_t;

void init_world(s_world_t* world, int x, int y, int w, int h);
bool collision_droit(s_sprite_t* sprite, char** tab);
bool collision_gauche(s_sprite_t* sprite, char** tab);
bool collision_haut(s_sprite_t* sprite, char** tab);
bool collision_bas(s_sprite_t* sprite, char** tab);

#endif
