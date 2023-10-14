#include "gameCycle.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "szoveg_kiir.h"


typedef enum Buza {
    WheatS1, WheatS2, WheatS3, WheatS4, WheatS5, WheatS0
} Buza;
enum { MERET = 60 };


void babu_rajzol(SDL_Renderer *renderer, SDL_Texture *novenyek, Buza melyik, int x, int y) {
    /* a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk. */
    SDL_Rect src = { (melyik % 6) * 62 + 10, (melyik / 6) * 60 + 10, MERET, MERET };
    /* a cel kepre, ezekre a koordinatakra masoljuk */
    SDL_Rect dest = { x, y, MERET, MERET };
    /* kepreszlet masolasa */
    SDL_RenderCopy(renderer, novenyek, &src, &dest);
}

void tombUjra(int *kertSor, int *kertOszlop, int ***kertTartalma,int ujSor,int ujOszlop){
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
                }


void gameCycle(SDL_Renderer *renderer){
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
    }
        SDL_Texture *novenyek = IMG_LoadTexture(renderer, "Textures/wheat.png");
    if (novenyek == NULL) {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }
enum { ABLAKX=900, ABLAKY=400 };
bool quit = false;
while (!quit) {
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if(kertTartalma[event.button.y/tileSize][event.button.x/tileSize]>=60000){
                            //printf("%d,%d,%d\n",kertTartalma[event.button.y/tileSize][event.button.x/tileSize],event.button.y/tileSize,event.button.x/tileSize);//osszegyujti a buzat és pénzt kap érte
                            kertTartalma[event.button.y/tileSize][event.button.x/tileSize]=0;
                            penz+=1;
                        }
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT) {
                        if(kertTartalma[event.button.y/tileSize][event.button.x/tileSize]==0){
                            //printf("%d,%d,%d\n",kertTartalma[event.button.y/tileSize][event.button.x/tileSize],event.button.y/tileSize,event.button.x/tileSize);//osszegyujti a buzat és pénzt kap érte
                            kertTartalma[event.button.y/tileSize][event.button.x/tileSize]=1;
                        }
                    }
                break;
            case SDL_KEYDOWN:
                                if (event.key.keysym.sym == SDLK_k) {
tombUjra(&kertSor, &kertOszlop, &kertTartalma, 4,11);}

            case SDL_USEREVENT:
                //novenynovesztes
                    for(int i=0;i<kertSor;i++){
                        for(int j=0;j<kertOszlop;j++){
                            if(kertTartalma[i][j]>=1&&kertTartalma[i][j]<=60000)
                            kertTartalma[i][j]+=tickSpeed;
                        }
                    }
                    //rajzolas
                    typedef enum Babu {
                    WheatS1, WheatS2, WheatS3, WheatS4, WheatS5, WheatS0,
                    SKiraly, SVezer, SSastya, SFuto, SHuszar, SGyalog
                } Babu;
                //rajzolas
                for(int i=0;i<kertSor;i++){
                    for(int j=0;j<kertOszlop;j++){
                        //kert kirajzolása
                        //rectangleRGBA(renderer,tileSize*j,tileSize*i,tileSize+tileSize*j,tileSize+tileSize*i,100,100,200,100);
                        //boxRGBA(renderer,tileSize*j,tileSize*i,tileSize+tileSize*j,tileSize+tileSize*i,0,100,0,255);//talaj kirajzolása
                        babu_rajzol(renderer, novenyek, WheatS0, tileSize*j,tileSize*i);
                        //buza kirajzolasa
                        if(kertTartalma[i][j]>0&&kertTartalma[i][j]<1000){
                        babu_rajzol(renderer, novenyek, WheatS1, tileSize*j,tileSize*i);
                        }
                        if(kertTartalma[i][j]>=1000&&kertTartalma[i][j]<4000){
                            //keret tartalmának üritese
                            //boxRGBA(renderer,tileSize*j,tileSize*i,50+tileSize*j,50+tileSize*i,0,0,0,255);
                            babu_rajzol(renderer, novenyek, WheatS2,tileSize*j,tileSize*i);
                            //rectangleRGBA(renderer,tileSize*j,tileSize*i,10+tileSize*j,10+tileSize*i,200,100,200,100);
                        }
                        if(kertTartalma[i][j]>=4000&&kertTartalma[i][j]<40000){
                            //keret tartalmának üritese
                            //boxRGBA(renderer,tileSize*j,tileSize*i,50+tileSize*j,50+tileSize*i,0,0,0,255);
                            babu_rajzol(renderer, novenyek, WheatS3, tileSize*j,tileSize*i);
                            //rectangleRGBA(renderer,tileSize*j,tileSize*i,10+tileSize*j,10+tileSize*i,200,200,100,100);
                        }
                        if(kertTartalma[i][j]>=40000&&kertTartalma[i][j]<60000){
                            //keret tartalmának üritese
                            //boxRGBA(renderer,tileSize*j,tileSize*i,50+tileSize*j,50+tileSize*i,0,0,0,255);
                            babu_rajzol(renderer, novenyek, WheatS4, tileSize*j,tileSize*i);
                            //rectangleRGBA(renderer,tileSize*j,tileSize*i,10+tileSize*j,10+tileSize*i,255,255,255,255);
                        }
                        if(kertTartalma[i][j]>=60000){
                            babu_rajzol(renderer, novenyek, WheatS5, tileSize*j,tileSize*i);
                        }
                    }
                }
                szoveg_kiir(penz, renderer);
                SDL_RenderPresent(renderer);
                boxRGBA(renderer, 0, 0, ABLAKX, ABLAKY, 0, 0, 0, 255);
                break;
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
    //memoria uritese
    for (int i = 0; i < kertSor; i++) {
    free(kertTartalma[i]);
    }
    free(kertTartalma);

}

/*
void mouseButtonDown(SDL_Event event,int *penz,int kertSor, int kertOszlop,int **kertTartalma,int tileSize){
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if(kertTartalma[event.button.y/tileSize][event.button.x/tileSize]>=60000){
                            //printf("%d,%d,%d\n",kertTartalma[event.button.y/tileSize][event.button.x/tileSize],event.button.y/tileSize,event.button.x/tileSize);//osszegyujti a buzat és pénzt kap érte
                            kertTartalma[event.button.y/tileSize][event.button.x/tileSize]=0;
                            *penz+=1;
                        }
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT) {
                        if(kertTartalma[event.button.y/tileSize][event.button.x/tileSize]==0){
                            //printf("%d,%d,%d\n",kertTartalma[event.button.y/tileSize][event.button.x/tileSize],event.button.y/tileSize,event.button.x/tileSize);//osszegyujti a buzat és pénzt kap érte
                            kertTartalma[event.button.y/tileSize][event.button.x/tileSize]=1;
                        }
                    }
}

void novenyNovesztes(int kertSor, int kertOszlop,int **kertTartalma,int tickSpeed){
                for(int i=0;i<kertSor;i++){
                    for(int j=0;j<kertOszlop;j++){
                        if(kertTartalma[i][j]>=1&&kertTartalma[i][j]<=60000)
                        kertTartalma[i][j]+=tickSpeed;
                    }
                }
}

void rajzolas(SDL_Event event,int kertSor, int kertOszlop,int **kertTartalma,SDL_Renderer *renderer,int tileSize,SDL_Texture *babuk){
                    typedef enum Babu {
                    WheatS1, WheatS2, WheatS3, WheatS4, WheatS5, WheatS0,
                    SKiraly, SVezer, SSastya, SFuto, SHuszar, SGyalog
                } Babu;
                //rajzolas
                for(int i=0;i<kertSor;i++){
                    for(int j=0;j<kertOszlop;j++){
                        //kert kirajzolása
                        //rectangleRGBA(renderer,tileSize*j,tileSize*i,tileSize+tileSize*j,tileSize+tileSize*i,100,100,200,100);
                        //boxRGBA(renderer,tileSize*j,tileSize*i,tileSize+tileSize*j,tileSize+tileSize*i,0,100,0,255);//talaj kirajzolása
                        babu_rajzol(renderer, babuk, WheatS0, tileSize*j,tileSize*i);
                        //buza kirajzolasa
                        if(kertTartalma[i][j]>0&&kertTartalma[i][j]<1000){
                        babu_rajzol(renderer, babuk, WheatS1, tileSize*j,tileSize*i);
                        }
                        if(kertTartalma[i][j]>=1000&&kertTartalma[i][j]<4000){
                            //keret tartalmának üritese
                            //boxRGBA(renderer,tileSize*j,tileSize*i,50+tileSize*j,50+tileSize*i,0,0,0,255);
                            babu_rajzol(renderer, babuk, WheatS2,tileSize*j,tileSize*i);
                            //rectangleRGBA(renderer,tileSize*j,tileSize*i,10+tileSize*j,10+tileSize*i,200,100,200,100);
                        }
                        if(kertTartalma[i][j]>=4000&&kertTartalma[i][j]<40000){
                            //keret tartalmának üritese
                            //boxRGBA(renderer,tileSize*j,tileSize*i,50+tileSize*j,50+tileSize*i,0,0,0,255);
                            babu_rajzol(renderer, babuk, WheatS3, tileSize*j,tileSize*i);
                            //rectangleRGBA(renderer,tileSize*j,tileSize*i,10+tileSize*j,10+tileSize*i,200,200,100,100);
                        }
                        if(kertTartalma[i][j]>=40000&&kertTartalma[i][j]<60000){
                            //keret tartalmának üritese
                            //boxRGBA(renderer,tileSize*j,tileSize*i,50+tileSize*j,50+tileSize*i,0,0,0,255);
                            babu_rajzol(renderer, babuk, WheatS4, tileSize*j,tileSize*i);
                            //rectangleRGBA(renderer,tileSize*j,tileSize*i,10+tileSize*j,10+tileSize*i,255,255,255,255);
                        }
                        if(kertTartalma[i][j]>=60000){
                            babu_rajzol(renderer, babuk, WheatS5, tileSize*j,tileSize*i);
                        }
                    }
                }
}

void keyboardDown(SDL_Event event){
    if (event.button.button == SDL_BUTTON_LEFT) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_k) {
                    // The "K" key has been pressed
                    SDL_Log("K key pressed");
                }
            }
}*/
