#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "textures.h"
#include "fonctions_fichiers.h"
#include "constante.h"
#include "world.h"

void init_textures_map(s_textures_t* textures, SDL_Rect srcBlocs[], int nbBlocsW, int nbBlocsH, int* blocW, int* blocH) {
    SDL_QueryTexture(textures->blocs, NULL, NULL, blocW, blocH);
    *blocW = *blocW / nbBlocsW;
    *blocH = *blocH / nbBlocsH;

    for (int i = 0; i < nbBlocsW; i++) {
        for (int j = nbBlocsH - 1; j >= 0; j--) {
            srcBlocs[i].x = i * TAILLE_BLOC;
            srcBlocs[i].y = j * TAILLE_BLOC;
            srcBlocs[i].w = *blocW;
            srcBlocs[i].h = *blocH; 
        }
    }
}

void afficher_map(SDL_Renderer* renderer, s_textures_t* textures, SDL_Rect srcBlocs[], SDL_Rect destBlocs, int* blocW, int* blocH, char** tab, int nbLig, int nbCol) {
    for (int i = 0; i < nbLig; i++) {
        for (int j = 0; j < nbCol; j++) {
            destBlocs.x = j * TAILLE_BLOC;
            destBlocs.y = i * TAILLE_BLOC;
            destBlocs.w = *blocW;
            destBlocs.h = *blocH;

            switch (tab[i][j]){
            case '1':
                SDL_RenderCopy(renderer, textures->blocs, &srcBlocs[9], &destBlocs);
                break;
            case '2':
                SDL_RenderCopy(renderer, textures->blocs, &srcBlocs[11], &destBlocs);
                break;
            case '3':
                SDL_RenderCopy(renderer, textures->blocs, &srcBlocs[2], &destBlocs);
                break;
            case '4':
                SDL_RenderCopy(renderer, textures->blocs, &srcBlocs[3], &destBlocs);
                break;
            default:
                SDL_RenderCopy(renderer, textures->blocs, &srcBlocs[1], &destBlocs);
                break;
            }
        }
    }  
}

/*void init_textures(SDL_Renderer* renderer, s_textures_t* textures, SDL_Rect srcBlocs[], int nbBlocsW, int nbBlocsH, int* blocW, int* blocH) {
    init_textures_map(textures, srcBlocs, nbBlocsW, nbBlocsH, blocW, blocH);
    textures->sprite = charger_image_transparente("skeleton.bmp", renderer, 0, 0, 0);
}*/

void apply_sprite(SDL_Renderer* renderer, s_textures_t* textures, s_sprite_t* sprite) {
    SDL_Rect dest = {0, 0, 0, 0};
    SDL_QueryTexture(textures->sprite, NULL, NULL, &dest.w, &dest.h);
    dest.x = sprite->x;
    dest.y = sprite->y;
    SDL_RenderCopy(renderer, textures->sprite, NULL, &dest);
}

void refresh_graphics(SDL_Renderer* renderer, s_textures_t* textures, s_world_t* world) {
    SDL_RenderClear(renderer);
    apply_sprite(renderer, textures, world->sprite);
}