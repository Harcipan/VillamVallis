#ifndef GAMECYCLE_H_INCLUDED
#define GAMECYCLE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
    typedef struct player{
    int playerX,playerY,playerSpeed;
    }player;
void gameCycle();//SDL_Renderer *renderer, SDL_Window* window, int isFullscreen
#endif // GAMECYCLE_H_INCLUDED
