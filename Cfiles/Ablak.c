#include <stdbool.h>
#include "AssetDraw.h"
#include "Ablak.h"

//Funkció:
//  -Inicializálja az ablakot amin a megjelenítés folyik
//Paraméterként kapja:
//  -szeles, magas(int)     mekkora képernyõt szeretnénk
//  -prenderer(SDL_Renderer)??INFOC-rol van
//  -pwindow (SDL_Window)   ??INFOC-rol van
// Visszatérési érték: nincs
// Megjegyzés: nincs
void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}
/* ez a fuggveny hivodik meg az idozito altal.
 * betesz a feldolgozando esemenyek koze (push) egy felhasznaloi esemenyt */
Uint32 idozit(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

void calcButtonPos(WindowParam* ablak,SDL_Rect* menuButtons, int gombokSzama)
{

    enum {buttonW=170, buttonH=100};
    if(gombokSzama==3) //align center
    {
        for (int i = 0; i < gombokSzama; i++)
        {
            menuButtons[i] = (SDL_Rect)
            {
                ablak->windX/2+(i-gombokSzama/2)*200-100, ablak->windY/2-50, buttonW, buttonH
            };
        }
    }
    else //align bottom
    {
        for (int i = 0; i < gombokSzama; i++)
        {
            menuButtons[i] = (SDL_Rect)
            {
                ablak->windX/2+(i-gombokSzama/2)*200, ablak->windY-100, buttonW, buttonH
            };
        }
    }
}


//Funkció:
//  -vált a teljesképernyõ és egy beállított méret között
//Paraméterként kapja:
//  -renderer(SDL_Renderer) renderelõ-re mutató ptr
//  -window (SDL_Window)    mejelenített ablak adataira mutató ptr
//  -isFullscreen(bool)     teljesképernyõn van-e
void toggleFullscreen(SDL_Window *window, int *isFullscreen)
{
    if (*isFullscreen)
    {
        SDL_SetWindowFullscreen(window, 0); // Exit fullscreen
        *isFullscreen = false;
    }
    else
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); // Enter fullscreen
        *isFullscreen = true;
    }
}

//Funkció:
//  -ki-be kapcsolja a teljes képernyőt
//Paraméterként kapja:
//  -renderer(SDL_Renderer) renderelő-re mutató ptr
//  -isFullscreen(bool)     teljesképernyőn van-e
//  -window (SDL_Window)    mejelenített ablak adataira mutató ptr
//  -menuButtons(SDL_Rect)  menu gombjait tároló tömbre mutat
// Visszatérési érték: nincs
// Megjegyzés: nincs
void toggleScreen(WindowParam* ablak,SDL_Rect* menuButtons,int gombokSzama)
{
    toggleFullscreen(ablak->window, &ablak->isFullscreen);
    SDL_GetWindowSize(ablak->window, &ablak->windX, &ablak->windY);
    calcButtonPos(ablak,menuButtons,gombokSzama);
}
