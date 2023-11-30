#ifndef COLLISIONS_H_INCLUDED
#define COLLISIONS_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>

bool inReach(int x, int y, SDL_Rect rect);
int melyikGomb(int x, int y, SDL_Rect* menuButtons);

#endif // COLLISIONS_H_INCLUDED
