#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "world.h"
#include "constante.h"

//initialisation de world(sprite, vitesse du sprite et fin de la boucle(jeu))
void init_world(s_world_t* world, int x, int y, int w, int h) {
    world->sprite = malloc(sizeof(s_sprite_t));
    world->sprite->x = x;
    world->sprite->y = y;
    world->sprite->w = w;
    world->sprite->h = h;
    world->vitesse = VITESSE;
    world->fin = false;
}

//collisions

bool collision_droit(s_sprite_t* sprite, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->h; i++) {
        if (tab[(sprite->y + i) / TAILLE_BLOC][(sprite->x + sprite->w) / TAILLE_BLOC] != ' ' && (sprite->y + i) / TAILLE_BLOC !=  (sprite->x + sprite->w) / TAILLE_BLOC] != ) {
            col = true;
        }
    }
    return col;
}

bool collision_gauche(s_sprite_t* sprite, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->h; i++) {
        if (tab[(sprite->y + i) / TAILLE_BLOC][(sprite->x - 1) / TAILLE_BLOC] != ' ') {
            col = true;
        }
    }
    return col;
}

bool collision_haut(s_sprite_t* sprite, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->w; i++) {
        if (tab[(sprite->y) / TAILLE_BLOC][(sprite->x + i) / TAILLE_BLOC] != ' ') {
            col = true;
        }
    }
    return col;
}

bool collision_bas(s_sprite_t* sprite, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->w; i++) {
        if (tab[(sprite->y + sprite->h) / TAILLE_BLOC][(sprite->x + i) / TAILLE_BLOC] != ' ') {
            col = true;
        }
    }
    return col;
}