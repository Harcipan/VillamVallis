#include <SDL2/SDL.h>
#include "gameCycle.h"
#include "debugmalloc.h"

int main(int argc, char *argv[]) {
    gameCycle();
    SDL_Quit();
    return 0;
}
