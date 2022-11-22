#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "world.h"

typedef struct s_textures {
    SDL_Texture* sprite;
    SDL_Texture* blocs;
} s_textures_t;

void init_textures_map(SDL_Rect srcBlocs[], int nbBlocsW, int nbBlocsH);
void afficher_map(SDL_Renderer* renderer, s_textures_t* textures, SDL_Rect srcBlocs[], SDL_Rect destBlocs, char** tab, int nbLig, int nbCol);
//void init_textures(SDL_Renderer* renderer, s_textures_t* textures, SDL_Rect srcBlocs[], int nbBlocsW, int nbBlocsH, int* blocW, int* blocH);
void apply_sprite(SDL_Renderer* renderer, s_textures_t* textures, s_sprite_t* sprite);
void refresh_graphics(SDL_Renderer* renderer, s_textures_t* textures, s_world_t* world);

#endif