#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"
#include "fonctions_SDL.h"

#define TAILLE_BLOC 32

int main(int argc, char *argv[]) {
    int nbLig = 0;
    int nbCol = 0;
    taille_fichier("terrain.txt", &nbLig, &nbCol);
    char** tab = lire_fichier("terrain.txt");
    afficher_tab_2D(tab, nbLig, nbCol);
    
    SDL_Window* fenetre;
    SDL_Event evenements;
    bool terminer = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, nbCol * TAILLE_BLOC, nbLig * TAILLE_BLOC, SDL_WINDOW_RESIZABLE);

    if (fenetre == NULL) {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_Texture* blocs = charger_image("pavage.bmp", renderer);
   
    int blocW, blocH;
    int nbBlocsW = 16;
    int nbBlocsH = 10;
    int nbBlocs = nbBlocsW * nbBlocsH;

    SDL_QueryTexture(blocs, NULL, NULL, &blocW, &blocH);
    blocW = blocW / nbBlocsW;
    blocH = blocH / nbBlocsH;

    SDL_Rect srcBlocs[nbBlocs], destBlocs;
    for (int i = 0; i < nbBlocsW; i++) {
        for (int j = nbBlocsH - 1; j >= 0; j--) {
            srcBlocs[i].x = i * TAILLE_BLOC;
            srcBlocs[i].y = j * TAILLE_BLOC;
            srcBlocs[i].w = blocW;
            srcBlocs[i].h = blocH; 
        }
    }

    while (!terminer) {
        while (SDL_PollEvent(&evenements)) {
            switch (evenements.type) {
                case SDL_QUIT:
                    terminer = true;
                    break;
            }
        }
        SDL_RenderClear(renderer);
        for (int i = 0; i < nbLig; i++) {
            for (int j = 0; j < nbCol; j++) {
                destBlocs.x = j * TAILLE_BLOC;
                destBlocs.y = i * TAILLE_BLOC;
                destBlocs.w = blocW;
                destBlocs.h = blocH;

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
        SDL_RenderPresent(renderer);  
    }
    SDL_DestroyTexture(blocs);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}