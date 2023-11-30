#ifndef ABLAK_H_INCLUDED
#define ABLAK_H_INCLUDED
#include <stdbool.h>
#include "AssetDraw.h"

typedef struct WindowParam{
    int windX, windY, isFullscreen;
    SDL_Window *window;
    SDL_Renderer *renderer;
}WindowParam;


void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);
Uint32 idozit(Uint32 ms, void *param);
void calcButtonPos(WindowParam* ablak,SDL_Rect* menuButtons, int gombokSzama);
void toggleFullscreen(SDL_Window *window, int *isFullscreen);
void toggleScreen(WindowParam* ablak,SDL_Rect* menuButtons,int gombokSzama);

#endif // ABLAK_H_INCLUDED
