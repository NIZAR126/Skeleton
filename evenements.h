#ifndef EVENEMENTS_H
#define EVENEMENTS_H

#include <SDL2/SDL.h>
#include "world.h"

void evenements(SDL_Event event, s_world_t* world, char** tab);

#endif