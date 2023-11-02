#ifndef ABLAK_H_INCLUDED
#define ABLAK_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>
enum { ABLAKX=800, ABLAKY=400 };
void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);
Uint32 idozit(Uint32 ms, void *param);
void toggleFullscreen(SDL_Window *window, bool *isFullscreen);

#endif // ABLAK_H_INCLUDED
