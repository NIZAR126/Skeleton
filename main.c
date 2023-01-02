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

    //initialisation du premier niveau
    init_world(world, 0, 0, TAILLE_SPRITE, TAILLE_SPRITE, "txt/terrain0.txt");

    //lecture du fichier terrain et retranscription en un tableau
    int nbLig = 0;
    int nbCol = 0;
    taille_fichier("txt/terrain0.txt", &nbLig, &nbCol);

    //initialisation sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    //creation de la fenetre sdl
    fenetre = SDL_CreateWindow("the skeleton trip", SDL_WINDOWPOS_CENTERED,
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
    //chargement des textures des images (fait ici car je n'arrrivais pas à le faire depuis textures.c)
    textures->blocs = charger_image("ressources/pavage.bmp", renderer);
    textures->sprite = charger_image_transparente("ressources/skeleton.bmp", renderer, 0, 0, 0);
    textures->lave = charger_image("ressources/lave.bmp", renderer);
    textures->vies = charger_image_transparente("ressources/vies.bmp", renderer, 255, 255, 255);
    textures->cles = charger_image("ressources/cle.bmp", renderer);
    textures->porteFermeB = charger_image("ressources/porteFermeB.bmp", renderer);
    textures->porteFermeH = charger_image("ressources/porteFermeH.bmp", renderer);
    textures->porteOuverteB = charger_image("ressources/porteOuverteB.bmp", renderer);
    textures->porteOuverteH = charger_image("ressources/porteOuverteH.bmp", renderer);
    textures->padH = charger_image("ressources/padH.bmp", renderer);
    textures->padG = charger_image("ressources/padG.bmp", renderer);
    textures->padD = charger_image("ressources/padD.bmp", renderer);

    //creation des differents sdl rect contenu dans le fichier pavage.bmp
    init_textures_map(textures, srcBlocs, nbBlocsW, nbBlocsH);

    //boucle principale
    while (!world->fin) {
        SDL_RenderClear(renderer);
        afficher_map(renderer, textures, srcBlocs, destBlocs, world->tab, nbLig, nbCol); //affichage de la map en initialisant destBlocs en fonction du tableau cree a partir des fichiers terrains
        evenements(event, world, nbLig, nbCol); //gestion des evenements
        refresh_graphics(renderer, textures, world); //rafraichissement de la fenetre et donc de l'affichage du sprite
        SDL_RenderPresent(renderer);  
        SDL_Delay(30);
        gagnerOuPerdu(world, textures); //affichage de la fenetre de fin en fonction de victoire ou defaite
    }

    //destruction des textures et fin de la sdl et du programme
    free_world(world);
    cleanTextures(textures);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    
    return 0;
}