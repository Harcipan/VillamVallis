#include <SDL2/SDL.h>
#include "gameCycle.h"
#include "debugmalloc.h"

//Funkció:
//  -meghívja a játékot, ha az végzett kilép
int main(int argc, char *argv[])
{
    gameCycle();
    TTF_Quit();
    SDL_Quit();
    /*

    */
    return 0;
}
