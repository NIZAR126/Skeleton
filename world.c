#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "world.h"
#include "constante.h"
#include "fonctions_fichiers.h"

//initialisation de world(sprite, vitesse du sprite et fin de la boucle(jeu))
void init_world(s_world_t* world, int x, int y, int w, int h, char* terrain) {
    world->sprite = malloc(sizeof(s_sprite_t));
    world->sprite->x = x;
    world->sprite->y = y;
    world->sprite->w = w;
    world->sprite->h = h;
    world->fin = false;
    world->vies = NBVIES;
    world->clesRecup = 0;
    world->tab = lire_fichier(terrain);
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

//gestion de la gravite
void gravite(s_world_t* world, int nbLig) {
    if (!collision_bas(world->sprite, world->tab, nbLig)) {
        world->sprite->y += GRAVITE;
    }
}

//gestion du nombre de vie et donc fin du jeu
void vies(s_world_t* world) {
    if (collision_char(world->sprite, '2', world->tab)) {
        world->sprite->x = 0;
        world->sprite->y = 0;
        world->vies -= 1;
    }
    if (world->vies == 0) {
        world->fin = true;
    }
}

//gestion des cles a recuperer pour ouvrir la porte
void cles(s_world_t* world, int nbLig, int nbCol) {
    if (collision_droit_char(world->sprite, '3', world->tab)) {
        world->tab[(world->sprite->y + world->sprite->h / 2) / TAILLE_BLOC][(world->sprite->x + world->sprite->w) / TAILLE_BLOC] = ' ';
        world->clesRecup += 1;
    } else if (collision_bas_char(world->sprite, '3', world->tab)) {
        world->tab[(world->sprite->y + world->sprite->h) / TAILLE_BLOC][(world->sprite->x + world->sprite->w / 2) / TAILLE_BLOC] = ' ';
        world->clesRecup += 1;
    } else if (collision_gauche_char(world->sprite, '3', world->tab)) {
        world->tab[(world->sprite->y + world->sprite->h / 2) / TAILLE_BLOC][(world->sprite->x - world->sprite->w / 2) / TAILLE_BLOC] = ' ';
        world->clesRecup += 1;
    }

    if (world->clesRecup == NBCLES) {
        world->tab = modifier_caractere(world->tab, nbLig, nbCol, '4', '5');
    }
    //printf("nbCles: %d\n", world->clesRecup);
}

//gestion des pad (pour sauter plus haut)
void pad(s_world_t* world) {
    if (collision_char(world->sprite, 'a', world->tab)) {
        world->sprite->y -= 20 * VITESSE;
    }
}

//gestion de tous les evenements qui modifie le gameplay
void deplacements_map(s_world_t* world, int nbLig, int nbCol) {
    gravite(world, nbLig);
    vies(world);
    cles(world, nbLig, nbCol);
    pad(world);

    if (collision_char(world->sprite, '5', world->tab)) {
        world->numTerrain += 1;
        char terrain[13];
        sprintf(terrain, "terrain%d.txt", world->numTerrain);
        printf("%s\n", terrain);
        init_world(world, 0, 0, TAILLE_SPRITE, TAILLE_SPRITE, terrain);
    }
}