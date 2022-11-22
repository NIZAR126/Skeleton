#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "world.h"
#include "constante.h"

//initialisation de world(sprite, vitesse du sprite et fin de la boucle(jeu))
void init_world(s_world_t* world, int x, int y, int w, int h) {
    world->sprite = malloc(sizeof(s_sprite_t));
    world->sprite->x = x;
    world->sprite->y = y;
    world->sprite->w = w;
    world->sprite->h = h;
    world->fin = false;
    world->vies = NBVIES;
}

//collisions

bool collision_droit(s_sprite_t* sprite, char** tab, int nbCol) {
    bool col = false;
    for (int i = 0; i < sprite->h; i++) {
        if (tab[(sprite->y + i) / TAILLE_BLOC][(sprite->x + sprite->w) / TAILLE_BLOC] != ' ' || (sprite->x + sprite->w) >= TAILLE_BLOC * nbCol) {
            col = true;
        }
    }
    return col;
}

bool collision_gauche(s_sprite_t* sprite, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->h; i++) {
        if (tab[(sprite->y + i) / TAILLE_BLOC][(sprite->x - 1) / TAILLE_BLOC] != ' ' || sprite->x <= 0) {
            col = true;
        }
    }
    return col;
}

bool collision_haut(s_sprite_t* sprite, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->w; i++) {
        if (tab[(sprite->y) / TAILLE_BLOC][(sprite->x + i) / TAILLE_BLOC] != ' ' || sprite->y <= 0) {
            col = true;
        }
    }
    return col;
}

bool collision_bas(s_sprite_t* sprite, char** tab, int nbLig) {
    bool col = false;
    for (int i = 0; i < sprite->w; i++) {
        if (tab[(sprite->y + sprite->h) / TAILLE_BLOC][(sprite->x + i) / TAILLE_BLOC] != ' ' || (sprite->y + sprite->h) >= TAILLE_BLOC * nbLig) {
            col = true;
        }
    }
    return col;
}



bool collision_droit_char(s_sprite_t* sprite, char c, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->h; i++) {
        if (tab[(sprite->y + i) / TAILLE_BLOC][(sprite->x + sprite->w) / TAILLE_BLOC] == c) {
            col = true;
        }
    }
    return col;
}

bool collision_gauche_char(s_sprite_t* sprite, char c, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->h; i++) {
        if (tab[(sprite->y + i) / TAILLE_BLOC][(sprite->x - 1) / TAILLE_BLOC] == c) {
            col = true;
        }
    }
    return col;
}

bool collision_haut_char(s_sprite_t* sprite, char c, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->w; i++) {
        if (tab[(sprite->y) / TAILLE_BLOC][(sprite->x + i) / TAILLE_BLOC] == c) {
            col = true;
        }
    }
    return col;
}

bool collision_bas_char(s_sprite_t* sprite, char c, char** tab) {
    bool col = false;
    for (int i = 0; i < sprite->w; i++) {
        if (tab[(sprite->y + sprite->h) / TAILLE_BLOC][(sprite->x + i) / TAILLE_BLOC] == c) {
            col = true;
        }
    }
    return col;
}

bool collision_char(s_sprite_t* sprite, char c, char** tab) {
    bool col = false; 
    if (collision_bas_char(sprite, c, tab) || collision_droit_char(sprite, c, tab) || collision_gauche_char(sprite, c, tab) || collision_haut_char(sprite, c, tab)) {
        col = true;
    }
    return col;
}

void deplacements_map(s_world_t* world, char** tab, int nbLig) {
    if (!collision_bas(world->sprite, tab, nbLig)) {
        world->sprite->y += GRAVITE;
    }

    if (collision_char(world->sprite, '2', tab)) {
        world->sprite->x = 0;
        world->sprite->y = 0;
        world->vies -= 1;
    }

    if (world->vies == 0) {
        world->fin = true;
    }
}