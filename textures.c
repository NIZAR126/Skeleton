#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "textures.h"
#include "fonctions_fichiers.h"
#include "constante.h"
#include "world.h"

//initialisation de la taille de chaque rectangle 
void init_textures_map(s_textures_t* textures, SDL_Rect srcBlocs[], int nbBlocsW, int nbBlocsH) {
    int blocW = 0, blocH = 0;
    SDL_QueryTexture(textures->blocs, NULL, NULL, &blocW, &blocH);
    blocW /= nbBlocsW;
    blocH /= nbBlocsH;
    for (int i = 0; i < nbBlocsW; i++) {
        for (int j = nbBlocsH - 1; j >= 0; j--) {
            srcBlocs[i].x = i * blocW;
            srcBlocs[i].y = j * blocH;
            srcBlocs[i].w = blocW;
            srcBlocs[i].h = blocH; 
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

            switch (tab[i][j]) {    //affichage des textures en fonction des caracteres du tableau
            case '1':
                SDL_RenderCopy(renderer, textures->blocs, &srcBlocs[9], &destBlocs);
                break;
            case '2':
                SDL_RenderCopy(renderer, textures->lave, NULL, &destBlocs);
                break;
            case '3':
                SDL_RenderCopy(renderer, textures->cles, NULL, &destBlocs);
                break;
            case '4':
                SDL_RenderCopy(renderer, textures->porteFerme, NULL, &destBlocs);
                break;
            case '5':
                SDL_RenderCopy(renderer, textures->porteOuverte, NULL, &destBlocs);
                break;
            case 'a':
                SDL_RenderCopy(renderer,textures->pad, NULL, &destBlocs);
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
void afficher_sprite(SDL_Renderer* renderer, s_textures_t* textures, s_sprite_t* sprite) {
    //SDL_Rect src;
    //src.x = 0;
    //src.y = 0;
    //src.w = sprite->w;
    //src.h = sprite->h;

    SDL_Rect dest;
    //SDL_QueryTexture(textures->sprite, NULL, NULL, &dest.w, &dest.h);
    dest.x = sprite->x;
    dest.y = sprite->y;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_RenderCopy(renderer, textures->sprite, NULL, &dest);
}

void afficher_vies(SDL_Renderer* renderer, s_textures_t* textures, int nbVies) {
    SDL_Rect dest;
    dest.w = TAILLE_VIE;
    dest.h = TAILLE_VIE;
    for (int i = 0; i < nbVies; i++) {
        dest.x = i * dest.w;
        dest.y = 0;
        SDL_RenderCopy(renderer, textures->vies, NULL, &dest);
    }
}

//rafraichissement de la fenetre et donc de l'affichage du sprite
void refresh_graphics(SDL_Renderer* renderer, s_textures_t* textures, s_world_t* world) {
    afficher_sprite(renderer, textures, world->sprite);
    afficher_vies(renderer, textures, world->vies);
}

//destruction des textures
void cleanTextures(s_textures_t* textures) {
    SDL_DestroyTexture(textures->blocs);
    SDL_DestroyTexture(textures->sprite);
    SDL_DestroyTexture(textures->lave);
    SDL_DestroyTexture(textures->vies);
    SDL_DestroyTexture(textures->cles);
    SDL_DestroyTexture(textures->porteFerme);
    SDL_DestroyTexture(textures->porteOuverte);
    SDL_DestroyTexture(textures->pad);
}