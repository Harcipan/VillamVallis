#ifndef ABLAK_H_INCLUDED
#define ABLAK_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);
Uint32 idozit(Uint32 ms, void *param);

#endif // ABLAK_H_INCLUDED
