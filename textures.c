#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "textures.h"
#include "fonctions_fichiers.h"
#include "constante.h"
#include "world.h"

//initialisation de la taille de chaque rectangle 
void init_textures_map(SDL_Rect srcBlocs[], int nbBlocsW, int nbBlocsH) {
    for (int i = 0; i < nbBlocsW; i++) {
        for (int j = nbBlocsH - 1; j >= 0; j--) {
            srcBlocs[i].x = i * TAILLE_BLOC;
            srcBlocs[i].y = j * TAILLE_BLOC;
            srcBlocs[i].w = TAILLE_BLOC;
            srcBlocs[i].h = TAILLE_BLOC; 
        }
    }
}

//affichage de la map en initialisant destBlocs en fonction du tableau cree a partir du terrain.txt
void afficher_map(SDL_Renderer* renderer, s_textures_t* textures, SDL_Rect srcBlocs[], SDL_Rect destBlocs, char** tab, int nbLig, int nbCol) {
    for (int i = 0; i < nbLig; i++) {
        for (int j = 0; j < nbCol; j++) {
            destBlocs.x = j * TAILLE_BLOC;
            destBlocs.y = i * TAILLE_BLOC;
            destBlocs.w = TAILLE_BLOC;
            destBlocs.h = TAILLE_BLOC;

            switch (tab[i][j]) {    //affichage des textures (srcBlocs[]) en fonction des caracteres du tableau
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

//application de la texture du sprite en fonction de sa position
void apply_sprite(SDL_Renderer* renderer, s_textures_t* textures, s_sprite_t* sprite) {
    //SDL_Rect src;
    //src.x = 0;
    //src.y = 0;
    //src.w = sprite->w;
    //src.h = sprite->h;

    SDL_Rect dest;
    SDL_QueryTexture(textures->sprite, NULL, NULL, &dest.w, &dest.h);
    dest.x = sprite->x;
    dest.y = sprite->y;
    //dest.w = sprite->w;
    //dest.h = sprite->h;
    SDL_RenderCopy(renderer, textures->sprite, NULL, &dest);
}

//rafraichissement de la fenetre et donc de l'affichage du sprite
void refresh_graphics(SDL_Renderer* renderer, s_textures_t* textures, s_world_t* world) {
    apply_sprite(renderer, textures, world->sprite);
}