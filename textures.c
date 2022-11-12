#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "textures.h"
#include "fonctions_fichiers.h"
#include "constante.h"

void init_textures_map(SDL_Texture* blocs, SDL_Rect srcBlocs[], int nbBlocsW, int nbBlocsH, int* blocW, int* blocH) {
    SDL_QueryTexture(blocs, NULL, NULL, blocW, blocH);
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

void afficher_map(SDL_Renderer* renderer, SDL_Texture* blocs, SDL_Rect srcBlocs[], SDL_Rect destBlocs, int* blocW, int* blocH, char** tab, int nbLig, int nbCol) {
    for (int i = 0; i < nbLig; i++) {
        for (int j = 0; j < nbCol; j++) {
            destBlocs.x = j * TAILLE_BLOC;
            destBlocs.y = i * TAILLE_BLOC;
            destBlocs.w = *blocW;
            destBlocs.h = *blocH;

            switch (tab[i][j]){
            case '1':
                SDL_RenderCopy(renderer, blocs, &srcBlocs[9], &destBlocs);
                break;
            case '2':
                SDL_RenderCopy(renderer, blocs, &srcBlocs[11], &destBlocs);
                break;
            case '3':
                SDL_RenderCopy(renderer, blocs, &srcBlocs[2], &destBlocs);
                break;
            case '4':
                SDL_RenderCopy(renderer, blocs, &srcBlocs[3], &destBlocs);
                break;
            default:
                SDL_RenderCopy(renderer, blocs, &srcBlocs[1], &destBlocs);
                break;
            }
        }
    }  
}