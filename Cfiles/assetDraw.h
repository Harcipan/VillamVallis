#ifndef ASSETDRAW_H_INCLUDED
#define ASSETDRAW_H_INCLUDED
#include "gameCycle.h"
typedef enum Buza
{
    WheatS1, WheatS2, WheatS3, WheatS4, WheatS5, WheatS0
} Buza;
enum { MERET = 60 };


void plantDraw(SDL_Renderer *renderer, SDL_Texture *novenyek, Buza melyik, int x, int y)
{
    // a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk.
    SDL_Rect src = { (melyik % 6) * 62 + 10, (melyik / 6) * 60 + 10, MERET, MERET };
    /* a cel kepre, ezekre a koordinatakra masoljuk */
    SDL_Rect dest = { x, y, MERET, MERET };
    // kepreszlet masolasa
    SDL_RenderCopy(renderer, novenyek, &src, &dest);
}

SDL_Texture* loadTexture(SDL_Renderer *renderer, char *textT)
{
    printf("%s",textT);
    SDL_Texture *texture = IMG_LoadTexture(renderer, textT);
    if (texture == NULL)
    {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        SDL_Delay(60000);
        exit(1);
    }
    return texture;
}

void rajzolas(DinTomb *kertTartalma, SDL_Texture *novenyek, SDL_Renderer *renderer, int tileSize,player* p1,SDL_Window *window)
{
    int windX, windY;
    SDL_GetWindowSize(window, &windX, &windY);
    int offSetX=(p1->playerX-windX/2);
    int offSetY=(p1->playerY-windY/2);
    for(int i=0; i<kertTartalma->meretSor; i++)
    {
        for(int j=0; j<kertTartalma->meretOszlop; j++)
        {
            //kert kirajzolása
            plantDraw(renderer, novenyek, WheatS0, tileSize*j-offSetX,tileSize*i-offSetY);
            //buza kirajzolasa
            if(kertTartalma->adat[i][j]>0&&kertTartalma->adat[i][j]<1000)
            {
                plantDraw(renderer, novenyek, WheatS1, tileSize*j-offSetX,tileSize*i-offSetY);
            }
            if(kertTartalma->adat[i][j]>=1000&&kertTartalma->adat[i][j]<4000)
            {
                //keret tartalmának üritese
                plantDraw(renderer, novenyek, WheatS2,tileSize*j-offSetX,tileSize*i-offSetY);
            }
            if(kertTartalma->adat[i][j]>=4000&&kertTartalma->adat[i][j]<40000)
            {
                //keret tartalmának üritese
                plantDraw(renderer, novenyek, WheatS3, tileSize*j-offSetX,tileSize*i-offSetY);
            }
            if(kertTartalma->adat[i][j]>=40000&&kertTartalma->adat[i][j]<60000)
            {
                //keret tartalmának üritese
                plantDraw(renderer, novenyek, WheatS4, tileSize*j-offSetX,tileSize*i-offSetY);
            }
            if(kertTartalma->adat[i][j]>=60000)
            {
                plantDraw(renderer, novenyek, WheatS5, tileSize*j-offSetX,tileSize*i-offSetY);
            }
        }
    }
}

void drawMenu(SDL_Renderer *renderer, SDL_Window *window,SDL_Rect* menuButtons,SDL_Texture *novenyek)
{

    int windX, windY;
    SDL_GetWindowSize(window, &windX, &windY);
    boxRGBA(renderer, 0, 0, windX, windY, 0, 0, 0, 255);
    int gombokSzama=4;
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);

    for (int i = 0; i < gombokSzama; i++) {
        SDL_RenderFillRect(renderer, &menuButtons[i]); // Fill the rectangle
    }
    szoveg_kiir(renderer,"New Game",windX/10*1,windY-100);
    szoveg_kiir(renderer,"Load Game",windX/10*3,windY-100);
    szoveg_kiir(renderer,"FullScreen",windX/10*5,windY-100);
    szoveg_kiir(renderer,"Exit",windX/10*7,windY-100);

    SDL_Rect src = { (WheatS5 % 6) * 62 + 10, (WheatS5 / 6) * 60 + 10, MERET, MERET };
    SDL_Rect dest = { windX/10*3, windY/10, windY/1.5, windY/1.5 };
    SDL_RenderCopy(renderer, novenyek, &src, &dest);
}

void drawSettings(SDL_Renderer *renderer, SDL_Window *window,SDL_Rect* menuButtons,int gombokSzama)
{

    int windX, windY;
    SDL_GetWindowSize(window, &windX, &windY);
    //boxRGBA(renderer, 0, 0, windX, windY, 0, 0, 0, 255);
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);

    for (int i = 0; i < gombokSzama; i++) {
        SDL_RenderFillRect(renderer, &menuButtons[i]); // Fill the rectangle
    }
    szoveg_kiir(renderer,"Save&ExitToMain",windX/10*3,windY-100);
    szoveg_kiir(renderer,"FullScreen",windX/10*5,windY-100);
    szoveg_kiir(renderer,"Exit",windX/10*7,windY-100);

    /*SDL_Texture *novenyek=loadTexture(renderer);
    SDL_Rect src = { (WheatS5 % 6) * 62 + 10, (WheatS5 / 6) * 60 + 10, MERET, MERET };
    SDL_Rect dest = { windX/10*3, windY/10, windY/1.5, windY/1.5 };
    SDL_RenderCopy(renderer, novenyek, &src, &dest);*/
}

#endif // ASSETDRAW_H_INCLUDED
