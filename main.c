#include <stdio.h>
#include <SDL2/SDL.h>
#include "ablak.h"
#include "gameCycle.h"

int main(int argc, char *argv[])
{
    //ablak meghívása
    enum { ABLAKX=900, ABLAKY=400 };
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(ABLAKX, ABLAKY, &window, &renderer);
    /* idozito hozzaadasa: 20 ms; 1000 ms / 24 ms -> 60 fps */
    SDL_TimerID id = SDL_AddTimer(24, idozit, NULL);

    //esemenyhurok
    gameCycle(renderer);

    // idozito torlese
    SDL_RemoveTimer(id);
    //kilépés
    SDL_Quit();
    return 0;
}
