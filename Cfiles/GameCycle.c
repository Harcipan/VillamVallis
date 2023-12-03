#include <stdio.h>
#include "gameCycle.h"
#include "Ablak.h"
#include "debugmalloc.h"
#include "ManagementGame.h"
#include "SceneGame.h"
#include "SceneMenu.h"
#include "DinTomb.h"

void initializeGame(int newGame, char *save_file,player* p1,DinTomb* kertTartalma,SDL_Renderer *renderer,SDL_Window *window)
{
    int kertSor=5;
    int kertOszlop=5;
    if(!newGame)
    {
        printf("\n%s\n",save_file);
        if(save_file==NULL)
        {
            printf("Hiba a mentett allas betolteseben.");
            SDL_Delay(60000);//60s wait, debug segítség
        }
        if(!loadGame(&kertSor,&kertOszlop,p1,save_file)){
            newGame=true;
        }
    }

    dintomb_foglal(kertTartalma, kertSor,kertOszlop);
    if(newGame)
    {
        dintomb_feltolt(kertTartalma,0);
    }
    else
    {
        readTo2DArray(kertTartalma->adat, kertSor, kertOszlop, save_file);
    }
}

//Funkció:      meghívja a megfelő scene-t
// Megjegyzés:  miután lefutott ki kell lépni az sdl és a programból
void gameCycle()//SDL_Renderer *renderer, SDL_Window* window, int isFullscreen
{
    //játék indítása
    //ablak meghívása
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(900, 600, &window, &renderer);
    WindowParam ablak= {0,0,0,window,renderer};
    SDL_GetWindowSize(window, &ablak.windX, &ablak.windY);
#ifdef __WIN32__
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
#endif
    // idozito hozzaadasa: 20 ms; 1000 ms / 24 ms -> 60 fps
    SDL_TimerID id = SDL_AddTimer(24, idozit, NULL);
    gameVariables gameVar= {10,0,0,1,1}; //tickSpeed, animTimer,settingsOpen,newGame,currentScene

    char save_file[256]="save_file";
    int playing = true;


    while(playing)
    {
        switch(gameVar.currentScene)//scene selector
        {
        case 1:
            MenuScene(&ablak, &gameVar, save_file);
            break;
        case 2:
            GameScene(&ablak, &gameVar, save_file);
            break;
        }
    }

    SDL_RemoveTimer(id);
}
