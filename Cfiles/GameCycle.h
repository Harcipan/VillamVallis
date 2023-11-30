#ifndef GAMECYCLE_H_INCLUDED
#define GAMECYCLE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DinTomb.h"

    typedef struct player{
        int playerX,playerY,playerSpeed, currentTool, penz, pOrientation, left,right,up,down;
        SDL_Rect playerReach;
    }player;

    typedef struct gameVariables{
        int tickSpeed, animTimer, settingsOpen, newGame,currentScene;
    }gameVariables;

    enum { MERET = 64 };

    typedef enum Character {//character animation states
        IdleD1,IdleD2,MovD1, MovD2,
        IdleDL1,IdleDL2,MovDL1,MovDL2,
        IdleL1,IdleL2,MovL1, MovL2,
        IdleUL1,IdleUL2,MovUL1,MovUL2,
        IdleU1,IdleU2,MovU1, MovU2,
        IdleUR1,IdleUR2,MovUR1,MovUR2,
        IdleR1,IdleR2,MovR1, MovR2,
        IdleDR1,IdleDR2,MovDR1,MovDR2
    } Character;


void initializeGame(int newGame, char *save_file,player* p1,DinTomb* kertTartalma,SDL_Renderer *renderer,SDL_Window *window);
void gameCycle();//SDL_Renderer *renderer, SDL_Window* window, int isFullscreen

#endif // GAMECYCLE_H_INCLUDED
