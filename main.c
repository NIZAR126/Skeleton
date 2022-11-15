#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"
#include "fonctions_SDL.h"
#include "constante.h"
#include "textures.h"
#include "world.h"
#include "evenements.h"

int main(int argc, char *argv[]) {
    s_world_t* world = malloc(sizeof(s_world_t));
    s_textures_t* textures = malloc(sizeof(s_textures_t));
    SDL_Window* fenetre;
    SDL_Event event;

    //lecture du fichier terrain et retranscription en un tableau
    int nbLig = 0;
    int nbCol = 0;
    taille_fichier("terrain.txt", &nbLig, &nbCol);
    char** tab = lire_fichier("terrain.txt");
    afficher_tab_2D(tab, nbLig, nbCol);

    //initialisation sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    //creation de la fenetre sdl
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, nbCol * TAILLE_BLOC, nbLig * TAILLE_BLOC, SDL_WINDOW_RESIZABLE);

    if (fenetre == NULL) {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    //creation du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    
    int nbBlocsW = 16;
    int nbBlocsH = 10;
    //creation d'un tableau de rectangle de la taille du nombre de blocs du fichier bmp et d'un rectangle pour la destination
    SDL_Rect srcBlocs[nbBlocsW * nbBlocsH], destBlocs; 
    //chargement des textures des images
    textures->blocs = charger_image("pavage.bmp", renderer);
    textures->sprite = charger_image("skeleton.bmp", renderer);
    init_textures_map(srcBlocs, nbBlocsW, nbBlocsH);
    //init_textures(renderer, textures, srcBlocs, nbBlocsW, nbBlocsH, &blocW, &blocH);
    init_world(world, 50, 50, 50, 50);

    while (!world->fin) {
        evenements(event, world);
        refresh_graphics(renderer, textures, world);
        afficher_map(renderer, textures, srcBlocs, destBlocs, tab, nbLig, nbCol);  
        SDL_RenderPresent(renderer);  
    }

    SDL_DestroyTexture(textures->blocs);
    SDL_DestroyTexture(textures->sprite);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}