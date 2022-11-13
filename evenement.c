#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "fonctions_fichiers.h"
#include "fonctions_SDL.h"
#include "Constante.h"
#include "data.h"
#include "textures.h"
#include "evenement.h"

void evenement_jeu(SDL_Event event){
    //Evenement du clavier
    while (SDL_PollEvent(&evenement)) {
        switch (evenement.type){
        case SDL_QUIT:
            terminer = true;
            break;

        case SDL_KEYDOWN:
            switch (evenement.key.keysym.sym){
            case SDLK_ESCAPE:
                terminer = true;
                break;

            case SDLK_UP:
                Dest.y -= 2;                    
                break;

            case SDLK_DOWN:
                Dest.y += 1;
                break;

            case SDLK_LEFT:
                Dest.x -= 1;
                break; 
            
            case SDLK_RIGHT: 
                Dest.x += 1;
                break;

            default:
                break;
            }
        
        default:
            break;
        }
    }
}
