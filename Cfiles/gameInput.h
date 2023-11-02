#ifndef GAMEINPUT_H_INCLUDED
#define GAMEINPUT_H_INCLUDED
#include "gameCycle.h"
void gamekeyDown(SDL_Event event, DinTomb *kertTartalma, bool *isFullscreen, SDL_Window *window, int *currentScene, int *currentTool, player* p1, bool *isSetting,int penz)
{
    int minX=1;
    int minY=1;
    int maxY=6;
    int maxX=10;
    //ha szamot nyomunk meg
    if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
    {
        int pressedNumber = event.key.keysym.sym - SDLK_0;
        *currentTool=pressedNumber;
    }
    else
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_k:
            if (kertTartalma->meretSor<maxY)//mit nyomtam és check, hogy van-e még hely boviteni
            {
                dintomb_atmeretez(kertTartalma, kertTartalma->meretSor+1, kertTartalma->meretOszlop);
            }
            break;
        case SDLK_o:
            if (kertTartalma->meretOszlop<maxX)
            {
                dintomb_atmeretez(kertTartalma, kertTartalma->meretSor, kertTartalma->meretOszlop+1);
            }
            break;
        case SDLK_j:
            if (kertTartalma->meretSor>minY)
            {
                dintomb_atmeretez(kertTartalma, kertTartalma->meretSor-1, kertTartalma->meretOszlop);
            }
            break;
        case SDLK_i:
            if (kertTartalma->meretOszlop>minX)
            {
                dintomb_atmeretez(kertTartalma, kertTartalma->meretSor, kertTartalma->meretOszlop-1);
            }
            break;
        //player Movement
        case SDLK_w:
            if(p1->playerY>0)
            p1->playerY-=p1->playerSpeed;
            break;
        case SDLK_a:
            if(p1->playerX>0)
            p1->playerX-=p1->playerSpeed;
            break;
        case SDLK_s:
            if(p1->playerY<(60*kertTartalma->meretSor-10))//60:tilesize, 10:playerSize
            p1->playerY+=p1->playerSpeed;
            break;
        case SDLK_d:
            if(p1->playerX<(60*kertTartalma->meretOszlop-10))
            p1->playerX+=p1->playerSpeed;
            break;
        case SDLK_z:
            saveGame(kertTartalma->meretSor,kertTartalma->meretOszlop,kertTartalma->adat,penz, p1->playerX, p1->playerY);
            break;
        /*case SDLK_f:
            toggleFullscreen(window, isFullscreen);
            break;*/
        case SDLK_ESCAPE:
            if(*isSetting)
                *isSetting=false;
            else
                *isSetting=true;
            //changeScene(2, currentScene);
            break;
        }
    }
}

int melyikGomb(int x, int y, SDL_Rect* menuButtons)
{
    int gombokSzama=sizeof(menuButtons);
    for (int i = 0; i < gombokSzama; i++)
    {
        SDL_Rect rect = menuButtons[i];
        if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
        {
            return i; // Point is inside one of the rectangles
        }
    }
    return -1; // Point is not inside any of the rectangles
}
#endif // GAMEINPUT_H_INCLUDED
