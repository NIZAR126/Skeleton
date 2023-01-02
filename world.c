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
    world->gagner = false;
    world->perdu = false;
}

void free_world(s_world_t* world) {
    free(world->sprite);
    world->sprite = NULL;
    free(world);
    world = NULL;
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
        for (int j = 0; j < SAUT; j++) {
            if (tab[(sprite->y - j) / TAILLE_BLOC][(sprite->x + i) / TAILLE_BLOC] != ' ' || sprite->y <= 0) {
                col = true;
            }
        }
    }
    return col;
}

bool collision_bas(s_sprite_t* sprite, char** tab, int nbLig) {
    bool col = false;
    for (int i = 0; i < sprite->w; i++) {
        for (int j = 0; j < GRAVITE; j++) {
            if (tab[(sprite->y + sprite->h + j) / TAILLE_BLOC][(sprite->x + i) / TAILLE_BLOC] != ' ' || (sprite->y + sprite->h) >= TAILLE_BLOC * nbLig) {
                col = true;
            }
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
    //si collision entre le sprite et la lave, on perd une vie
    if (collision_char(world->sprite, '2', world->tab)) {
        world->sprite->x = 0;
        world->sprite->y = 0;
        world->vies -= 1;
    }
    if (world->vies == 0) {
        world->perdu = true;
    }
}

//gestion des cles a recuperer pour ouvrir la porte
void cles(s_world_t* world, int nbLig, int nbCol) {
    //si il y a collision entre le sprite et une cle, on retire la cle
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

    //si l'on a recupere toutes les cles, les caracteres representant la porte fermee sont changes par ceux representant la porte ouverte
    if (world->clesRecup == NBCLES) {
        world->tab = modifier_caractere(world->tab, nbLig, nbCol, '4', '6');
        world->tab = modifier_caractere(world->tab, nbLig, nbCol, '5', '7');
    }
}

//gestion des pad (pour aller plus loin dans une direction)
void padH(s_world_t* world) {
    if (collision_char(world->sprite, 'h', world->tab)) {
        world->sprite->y -= 20 * VITESSE;
    }
}

void padG(s_world_t* world) {
    if (collision_char(world->sprite, 'g', world->tab)) {
        world->sprite->x -= 20 * VITESSE;
    }
}

void padD(s_world_t* world) {
    if (collision_char(world->sprite, 'd', world->tab)) {
        world->sprite->x += 20 * VITESSE;
    }
}


//gestion de tous les evenements qui modifie le gameplay
void deplacements_map(s_world_t* world, int nbLig, int nbCol) {
    gravite(world, nbLig);
    vies(world);
    cles(world, nbLig, nbCol);
    padH(world);
    padG(world);
    padD(world);

    //si collision entre le sprite et une porte ouverte, on passe au niveau suivant
    if (collision_char(world->sprite, '6', world->tab) || collision_char(world->sprite, '7', world->tab)) {
        world->numTerrain += 1;
        if (world->numTerrain >= NBTERRAINS) {
            world->gagner = true;
        } else {
            char terrain[17];
            sprintf(terrain, "txt/terrain%d.txt", world->numTerrain);
            init_world(world, 0, 0, TAILLE_SPRITE, TAILLE_SPRITE, terrain);
        }
    }
}