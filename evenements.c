#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "world.h"
#include "evenements.h"
#include "constante.h"

//gestion des evenements
void evenements(SDL_Event event, s_world_t* world, int nbLig, int nbCol) {
    Uint8 *state = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&event)) {
        //SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                world->fin = true;
                break;
        }
        if (state[SDL_SCANCODE_RIGHT] && !collision_droit(world->sprite, world->tab, nbCol)) {
            world->sprite->x += VITESSE;
        }
        if (state[SDL_SCANCODE_LEFT] && !collision_gauche(world->sprite, world->tab)) {
            world->sprite->x -= VITESSE;
        }
        if (state[SDL_SCANCODE_SPACE] && !collision_haut(world->sprite, world->tab) && collision_bas(world->sprite, world->tab, nbLig)) {
            world->sprite->y -= 10 * VITESSE;
        }
        /*if (state[SDL_SCANCODE_UP] && !collision_haut(world->sprite, tab) && state[SDL_SCANCODE_RIGHT] && !collision_droit(world->sprite, tab, nbCol)) {
            world->sprite->y -= 5 * VITESSE;
            world->sprite->x += VITESSE;
        }*/     
        if (state[SDL_SCANCODE_ESCAPE]) {
            world->fin = true;
        }
            /* case SDL_KEYDOWN:
                switch (event.key.keysym.sym) { //evenements de type clavier
                    case SDLK_ESCAPE:
                        world->fin = true;
                        break; 
                   case SDLK_RIGHT: 
                        if (!collision_droit(world->sprite, tab, nbCol)) {
                            world->sprite->x += VITESSE;
                        }
                        break;  
                    case SDLK_LEFT:
                        if (!collision_gauche(world->sprite, tab)) {
                            world->sprite->x -= VITESSE;
                        }
                        break; 
                    case SDLK_UP:
                        if (!collision_haut(world->sprite, tab)) {
                            world->sprite->y -= 10 * VITESSE;
                        }                    
                        break;
                    case SDLK_DOWN:
                        if (!collision_bas(world->sprite, tab, nblig)) {
                            world->sprite->y += VITESSE;
                        }
                        break;
                    default:
                        break;
                }
            default:
            break;
        } */
    }
    deplacements_map(world, nbLig, nbCol);
}

/*void evenements(SDL_Event event, s_world_t* world, char** tab, int nblig, int nbCol) {
    bool droit = false, gauche = false, haut = false;
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
                        droit = true;
                        if (haut && !collision_droit(world->sprite, tab, nbCol) && !collision_haut(world->sprite, tab)) {
                            world->sprite->x += VITESSE;
                            world->sprite->y -= 10 * VITESSE;
                        } else if (!collision_droit(world->sprite, tab, nbCol)) {
                            world->sprite->x += VITESSE;
                        }
                        break;  
                    case SDLK_LEFT:
                        gauche = true;
                        if (!collision_gauche(world->sprite, tab)) {
                            world->sprite->x -= VITESSE;
                        }
                        break; 
                    case SDLK_UP:
                        haut = true;
                        if (droit && !collision_haut(world->sprite, tab) && !collision_droit(world->sprite, tab, nbCol)) {
                            world->sprite->y -= 10 * VITESSE;
                            world->sprite->x += VITESSE;
                        }
                        if (!collision_haut(world->sprite, tab)) {
                            world->sprite->y -= 10 * VITESSE;
                        }                    
                        break;
                    case SDLK_DOWN:
                        if (!collision_bas(world->sprite, tab, nblig)) {
                            world->sprite->y += VITESSE;
                        }
                        break;
                    default:
                        break;
                }
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        droit = false;
                        break;
                    case SDLK_LEFT:
                        gauche = false;
                        break;
                    case SDLK_UP:
                        haut = false;
                        break;
                }
        }
    }
    if (!collision_bas(world->sprite, tab, nblig)) {
        world->sprite->y += GRAVITE;
    }
}*/
