#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "world.h"

//initialisation de world(sprite, vitesse du sprite et fin de la boucle(jeu))
void init_world(s_world_t* world, int x, int y, int w, int h, int vitesse) {
    world->sprite->x = x;
    world->sprite->y = y;
    world->sprite->w = w;
    world->sprite->h = h;
    world->vitesse = vitesse;
    world->fin = false;
}

//collisions

bool collision_droit(s_sprite_t* sprite, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->h; i++) {
        if(tab[sprite->y + i][sprite->x + sprite->w] != '0' && tab[sprite->y + i][sprite->x + sprite->w] != ' ') {
            col = true;
        }
    }
    return col;
}

bool collision_gauche(s_sprite_t* sprite, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->h; i++) {
        if(tab[sprite->y + i][sprite->x - 1] != '0' && tab[sprite->y + i][sprite->x - 1] != ' ') {
            col = true;
        }
    }
    return col;
}

bool collision_haut(s_sprite_t* sprite, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->w; i++) {
        if(tab[sprite->y-1][sprite->x + i] == '0' && tab[sprite->y-1][sprite->x + i] == ' ') {
            col = true;
        }
    }
    return col;
}

bool collision_bas(s_sprite_t* sprite, char** tab) {
    bool col = false;
    for(int j = 0; j < sprite->w; j++) {
        if(tab[sprite->y + sprite->h][sprite->x + j] == '0' && tab[sprite->y + sprite->h][sprite->x + j] == ' ') {
            col = true;
        }
    }
    return col;
}