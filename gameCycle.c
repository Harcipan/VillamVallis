#include "gameCycle.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "szoveg_kiir.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dinTomb.h"
#include "gameManagement.h"

typedef enum Buza
{
    WheatS1, WheatS2, WheatS3, WheatS4, WheatS5, WheatS0
} Buza;
enum { MERET = 60 };


void babu_rajzol(SDL_Renderer *renderer, SDL_Texture *novenyek, Buza melyik, int x, int y)
{
    // a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk.
    SDL_Rect src = { (melyik % 6) * 62 + 10, (melyik / 6) * 60 + 10, MERET, MERET };
    /* a cel kepre, ezekre a koordinatakra masoljuk */
    SDL_Rect dest = { x, y, MERET, MERET };
    // kepreszlet masolasa
    SDL_RenderCopy(renderer, novenyek, &src, &dest);
}

void gameCycle(SDL_Renderer *renderer)
{
    //változók
    int kertSor=0;
    int kertOszlop=0;
    int tileSize=MERET;
    int penz=0;
    int tickSpeed=100;//játék sebessége
    loadGame(&kertSor,&kertOszlop);
    DinTomb kertTartalma;
    dintomb_foglal(&kertTartalma, kertSor,kertOszlop);
    //dintomb_feltolt(&kertTartalma, kertTartalma.meretSor, kertTartalma.meretOszlop,0);
    readTo2DArray(kertTartalma.adat, kertSor, kertOszlop);

    SDL_Texture *novenyek = IMG_LoadTexture(renderer, "Textures/wheat.png");
    if (novenyek == NULL)
    {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }
    enum { ABLAKX=900, ABLAKY=400 };
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.y<kertTartalma.meretSor*tileSize&&event.button.x<kertTartalma.meretOszlop*tileSize)//check, hogy a kerten belul kattintottunk-e
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if(kertTartalma.adat[event.button.y/tileSize][event.button.x/tileSize]>=60000)
                    {
                        kertTartalma.adat[event.button.y/tileSize][event.button.x/tileSize]=0;
                        penz+=1;
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    if(kertTartalma.adat[event.button.y/tileSize][event.button.x/tileSize]==0)
                    {
                        kertTartalma.adat[event.button.y/tileSize][event.button.x/tileSize]=1;
                    }
                }
            }

            break;
        case SDL_KEYDOWN:

            if (event.key.keysym.sym == SDLK_k && kertTartalma.meretSor<6)//mit nyomtam és check, hogy van-e még hely boviteni
            {
                dintomb_atmeretez(&kertTartalma, kertTartalma.meretSor+1, kertTartalma.meretOszlop);
            }
            if (event.key.keysym.sym == SDLK_o && kertTartalma.meretOszlop<10)
            {
                dintomb_atmeretez(&kertTartalma, kertTartalma.meretSor, kertTartalma.meretOszlop+1);
            }
            if (event.key.keysym.sym == SDLK_j&&kertTartalma.meretSor>1)
            {
                dintomb_atmeretez(&kertTartalma, kertTartalma.meretSor-1, kertTartalma.meretOszlop);
            }
            if (event.key.keysym.sym == SDLK_i&&kertTartalma.meretOszlop>1)
            {
                dintomb_atmeretez(&kertTartalma, kertTartalma.meretSor, kertTartalma.meretOszlop-1);
            }
            if(event.key.keysym.sym == SDLK_z)
            {
                saveGame(kertTartalma.meretSor,kertTartalma.meretOszlop,kertTartalma.adat);
            }
        case SDL_USEREVENT:
            //novenynovesztes
            for(int i=0; i<kertTartalma.meretSor; i++)
            {
                for(int j=0; j<kertTartalma.meretOszlop; j++)
                {
                    if(kertTartalma.adat[i][j]>=1&&kertTartalma.adat[i][j]<=60000)
                        kertTartalma.adat[i][j]+=tickSpeed;
                }
            }
            //rajzolas
            for(int i=0; i<kertTartalma.meretSor; i++)
            {
                for(int j=0; j<kertTartalma.meretOszlop; j++)
                {
                    //kert kirajzolása
                    babu_rajzol(renderer, novenyek, WheatS0, tileSize*j,tileSize*i);
                    //buza kirajzolasa
                    if(kertTartalma.adat[i][j]>0&&kertTartalma.adat[i][j]<1000)
                    {
                        babu_rajzol(renderer, novenyek, WheatS1, tileSize*j,tileSize*i);
                    }
                    if(kertTartalma.adat[i][j]>=1000&&kertTartalma.adat[i][j]<4000)
                    {
                        //keret tartalmának üritese
                        babu_rajzol(renderer, novenyek, WheatS2,tileSize*j,tileSize*i);
                    }
                    if(kertTartalma.adat[i][j]>=4000&&kertTartalma.adat[i][j]<40000)
                    {
                        //keret tartalmának üritese
                        babu_rajzol(renderer, novenyek, WheatS3, tileSize*j,tileSize*i);
                    }
                    if(kertTartalma.adat[i][j]>=40000&&kertTartalma.adat[i][j]<60000)
                    {
                        //keret tartalmának üritese
                        babu_rajzol(renderer, novenyek, WheatS4, tileSize*j,tileSize*i);
                    }
                    if(kertTartalma.adat[i][j]>=60000)
                    {
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
    for (int i = 0; i < kertTartalma.meretSor; ++i)
    {
        free(kertTartalma.adat[i]);
    }
    free(kertTartalma.adat);
    SDL_DestroyTexture(novenyek);
}
