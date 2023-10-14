#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#include "szoveg_kiir.h"
#include "ablak.h"
#include "gameCycle.h"
/*
typedef enum Buza {
    WheatS1, WheatS2, WheatS3, WheatS4, WheatS5, WheatS0
} Buza;
enum { MERET = 60 };*/

/*void babu_rajzol(SDL_Renderer *renderer, SDL_Texture *novenyek, Buza melyik, int x, int y) {
    /* a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk. //
    SDL_Rect src = { (melyik % 6) * 62 + 10, (melyik / 6) * 60 + 10, MERET, MERET };
    /* a cel kepre, ezekre a koordinatakra masoljuk //
    SDL_Rect dest = { x, y, MERET, MERET };
    /* kepreszlet masolasa //
    SDL_RenderCopy(renderer, novenyek, &src, &dest);
}*/

/*void tombUjra(int *kertSor, int *kertOszlop, int ***kertTartalma,int ujSor,int ujOszlop) {
    // First, free the memory
    for (int i = 0; i < *kertSor; i++) {
        free((*kertTartalma)[i]);
    }
    free(*kertTartalma);

    // Set new dimensions (kertSorNew and kertOszlopNew) for the array
    *kertSor = ujSor; // New number of rows
    *kertOszlop = ujOszlop; // New number of columns

    // Allocate memory for the new 2D array
    *kertTartalma = (int**)malloc(*kertSor * sizeof(int*));
    for (int i = 0; i < *kertSor; i++) {
        (*kertTartalma)[i] = (int*)malloc(*kertOszlop * sizeof(int));
    }

    // Initialize the new array with 0s if needed
    for (int i = 0; i < *kertSor; i++) {
        for (int j = 0; j < *kertOszlop; j++) {
            (*kertTartalma)[i][j] = 0;
        }
    }
}*/

int main(int argc, char *argv[]) {/*
    //változók
    int kertSor=6;
    int kertOszlop=10;
    int tileSize=MERET;
    int penz=0;
    int tickSpeed=100;//játék sebessége

    int **kertTartalma = NULL;

    // Allocate memory for the 2D array
    kertTartalma = (int**)malloc(kertSor * sizeof(int*));
    for (int i = 0; i < kertSor; i++) {
        kertTartalma[i] = (int*)malloc(kertOszlop * sizeof(int));
    }

    // 2D tömb feltöltése 0-kkal
    for (int i = 0; i < kertSor; i++) {
        for (int j = 0; j < kertOszlop; j++) {
            kertTartalma[i][j] = 0;
        }
    }*/

    //ablak meghívása
    enum { ABLAKX=900, ABLAKY=400 };
    //int AblakX=900; int AblakY=400;
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(ABLAKX, ABLAKY, &window, &renderer);

    /* idozito hozzaadasa: 20 ms; 1000 ms / 24 ms -> 60 fps */
    SDL_TimerID id = SDL_AddTimer(24, idozit, NULL);

    //kep betoltese
    /*SDL_Texture *novenyek = IMG_LoadTexture(renderer, "Textures/wheat.png");
    if (novenyek == NULL) {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }*/

    //esemenyhurok
    gameCycle(renderer);
/*
    bool quit = false;
while (!quit) {
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                mouseButtonDown(event, &penz, kertSor, kertOszlop, kertTartalma, tileSize);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_k) {
                    tombUjra(&kertSor, &kertOszlop, &kertTartalma, 4,11);
                }

            case SDL_USEREVENT:
                novenyNovesztes(kertSor, kertOszlop, kertTartalma, tickSpeed);
                rajzolas(event, kertSor, kertOszlop, kertTartalma, renderer, tileSize, novenyek);
                szoveg_kiir(penz, renderer);
                SDL_RenderPresent(renderer);
                boxRGBA(renderer, 0, 0, ABLAKX, ABLAKY, 0, 0, 0, 255);
                break;
            case SDL_QUIT:
                quit = true;
                break;
        }
    }*/
    /*//memoria uritese
    for (int i = 0; i < kertSor; i++) {
    free(kertTartalma[i]);
    }
    free(kertTartalma);*/
    // idozito torlese
    SDL_RemoveTimer(id);
    //kilépés
    SDL_Quit();
    return 0;
}
