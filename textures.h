#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "world.h"

typedef struct s_textures {
    SDL_Texture* sprite;
    SDL_Texture* blocs;
    SDL_Texture* lave;
    SDL_Texture* vies;
    SDL_Texture* cles;
    SDL_Texture* porteOuverte;
    SDL_Texture* porteFerme;
    SDL_Texture* pad;
} s_textures_t;

void init_textures_map(s_textures_t* textures, SDL_Rect srcBlocs[], int nbBlocsW, int nbBlocsH);
void afficher_map(SDL_Renderer* renderer, s_textures_t* textures, SDL_Rect srcBlocs[], SDL_Rect destBlocs, char** tab, int nbLig, int nbCol);
//void init_textures(SDL_Renderer* renderer, s_textures_t* textures, SDL_Rect srcBlocs[], int nbBlocsW, int nbBlocsH, int* blocW, int* blocH);
void afficher_sprite(SDL_Renderer* renderer, s_textures_t* textures, s_sprite_t* sprite);
void afficher_vies(SDL_Renderer* renderer, s_textures_t* textures, int nbVies);
void refresh_graphics(SDL_Renderer* renderer, s_textures_t* textures, s_world_t* world);
void cleanTextures(s_textures_t* textures);

#endif