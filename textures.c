#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "textures.h"
#include "fonctions_fichiers.h"
#include "constante.h"
#include "world.h"

//initialisation de la taille de chaque rectangle du fichier pavage.bmp
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
                SDL_RenderCopy(renderer, textures->porteFermeB, NULL, &destBlocs);
                break;
            case '5':
                SDL_RenderCopy(renderer, textures->porteFermeH, NULL, &destBlocs);
                break;
            case '6':
                SDL_RenderCopy(renderer, textures->porteOuverteB, NULL, &destBlocs);
                break;
            case '7':
                SDL_RenderCopy(renderer, textures->porteOuverteH, NULL, &destBlocs);
                break;
            case 'h':
                SDL_RenderCopy(renderer,textures->padH, NULL, &destBlocs);
                break;
            case 'g':
                SDL_RenderCopy(renderer,textures->padG, NULL, &destBlocs);
                break;
            case 'd':
                SDL_RenderCopy(renderer,textures->padD, NULL, &destBlocs);
                break;
            default:
                SDL_RenderCopy(renderer, textures->blocs, &srcBlocs[1], &destBlocs);
                break;
            }
        }
    }  
}

//application de la texture du sprite en fonction de sa position
void afficher_sprite(SDL_Renderer* renderer, s_textures_t* textures, s_sprite_t* sprite) {
    SDL_Rect dest;
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

//affichage de la fenetre de fin en fonction de victoire ou defaite
void gagnerOuPerdu(s_world_t* world, s_textures_t* textures) {
    if (world->perdu) {
        init_world(world, 0, 0, 0, 0, "txt/gameover.txt");
        SDL_DestroyTexture(textures->vies);
        SDL_DestroyTexture(textures->sprite);
    }
    if (world->gagner) {
        init_world(world, 0, 0, 0, 0, "txt/goodjob.txt");
        SDL_DestroyTexture(textures->vies);
        SDL_DestroyTexture(textures->sprite);
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
    SDL_DestroyTexture(textures->porteFermeB);
    SDL_DestroyTexture(textures->porteFermeH);
    SDL_DestroyTexture(textures->porteOuverteB);
    SDL_DestroyTexture(textures->porteOuverteH);
    SDL_DestroyTexture(textures->padH);
    SDL_DestroyTexture(textures->padG);
    SDL_DestroyTexture(textures->padD);
    free(textures);
    textures = NULL;
}