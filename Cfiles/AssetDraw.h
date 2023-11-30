#ifndef ASSETDRAW_H_INCLUDED
#define ASSETDRAW_H_INCLUDED
#include "GameCycle.h"
typedef enum Buza
{
    WheatS1, WheatS2, WheatS3, WheatS4, WheatS5, NormalSoil,
    WateredSoid, seed, shovel, wateringCan
} Buza;

void plantDraw(SDL_Renderer *renderer, SDL_Texture *novenyek, Buza melyik, int x, int y);
void playerDraw(SDL_Renderer *renderer, SDL_Texture *texture, Character melyik, int x, int y);
SDL_Texture* loadTexture(SDL_Renderer *renderer, char *textT);
void drawUI(SDL_Renderer *renderer,SDL_Window *window,player* p1,SDL_Texture *novenyek);
void kertRajzolas(DinTomb *kertTartalma, SDL_Texture *novenyek, SDL_Renderer *renderer, int tileSize,player* p1,SDL_Window *window);
void drawMenu(SDL_Renderer *renderer, SDL_Window *window,SDL_Rect* menuButtons,SDL_Texture *novenyek);
void drawSettings(SDL_Renderer *renderer, SDL_Window *window,SDL_Rect* menuButtons,int gombokSzama);

#endif // ASSETDRAW_H_INCLUDED
