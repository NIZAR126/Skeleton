#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"
#include "fonctions_SDL.h"
#include "constante.h"

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
    SDL_Rect srcBlocs[nbBlocsW * nbBlocsH], destBlocs;
    init_textures_map(blocs, srcBlocs, nbBlocsW, nbBlocsH, &blocW, &blocH);

    while (!terminer) {
        while (SDL_PollEvent(&evenements)) {
            switch (evenements.type) {
                case SDL_QUIT:
                    terminer = true;
                    break;
            }
        }
        SDL_RenderClear(renderer);
        afficher_map(renderer, blocs, srcBlocs, destBlocs, &blocW, &blocH, tab, nbLig, nbCol);  
        SDL_RenderPresent(renderer);  
    }

    SDL_DestroyTexture(blocs);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}