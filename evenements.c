#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "world.h"
#include "evenements.h"
#include "constante.h"

//gestion des evenements
void evenements(SDL_Event event, s_world_t* world) {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                world->fin = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) { //evenements de type clavier
                    case SDLK_ESCAPE:
                        world->fin = true;
                        break; 
                   case SDLK_RIGHT: 
                        world->sprite->x += VITESSE;
                        break;  
                    case SDLK_LEFT:
                        world->sprite->x -= VITESSE;
                        break; 
                    case SDLK_UP:
                        world->sprite->y -= 2 * VITESSE;                    
                        break;
                    case SDLK_DOWN:
                        world->sprite->y += VITESSE;
                        break;
                    default:
                        break;
                }
            default:
            break;
        }
    }
}
