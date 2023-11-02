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
#include "ablak.h"
#include "debugmalloc.h"
#include "assetDraw.h"
#include "gameInput.h"
#include "kertErtekad.h"

typedef enum Character
{
    Idle1, Idle2, Idle3, Idle4, Idle5, Idle6
} Character;

void playerDraw(SDL_Renderer *renderer, SDL_Texture *texture, Character melyik, int x, int y)
{
    // a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk.
    SDL_Rect src = { (melyik % 6) * 62 + 10, (melyik / 6) * 60 + 10, MERET, MERET };
    /* a cel kepre, ezekre a koordinatakra masoljuk */
    SDL_Rect dest = { x, y, MERET, MERET };
    // kepreszlet masolasa
    SDL_RenderCopy(renderer, texture, &src, &dest);
}

void toggleScreen(SDL_Renderer *renderer,bool *isFullscreen, SDL_Window *window, int windX,int windY, SDL_Rect* menuButtons){
    SDL_Texture *novenyek=loadTexture(renderer,"Textures/wheat.png");
    enum{buttonW=150, buttonH=100};
    toggleFullscreen(window, isFullscreen);
    SDL_GetWindowSize(window, &windX, &windY);
    for (int i = 0; i < 3; i++)
    {
        menuButtons[i] = (SDL_Rect)
        {
            windX/10*(3+i*2), windY-100, buttonW, buttonH
        };
    }
    drawMenu(renderer, window, menuButtons,novenyek);
}
bool inReach(int x, int y, SDL_Rect rect)
{   if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
        return true; // Point is inside one of the rectangles
    return false; // Point is not inside any of the rectangles
}

void MenuScene(SDL_Renderer *renderer, SDL_Window *window, bool *isFullscreen, int *currentScene, char *save_file)
{
    SDL_Texture *novenyek=loadTexture(renderer,"Textures/wheat.png");
    int windX=ABLAKX, windY=ABLAKY;
    SDL_GetWindowSize(window, &windX, &windY);
    enum{buttonW=150, buttonH=100};
    SDL_Rect menuButtons[4]; // An array to store rectangles
    menuButtons[0] = (SDL_Rect){windX/10*1, windY-100, buttonW, buttonH};
    menuButtons[1] = (SDL_Rect){windX/10*3, windY-100, buttonW, buttonH};
    menuButtons[2] = (SDL_Rect){windX/10*5, windY-100, buttonW, buttonH};
    menuButtons[3] = (SDL_Rect){windX/10*7, windY-100, buttonW, buttonH};

    while (1)
    {
        drawMenu(renderer, window, menuButtons,novenyek);

        int megNyomva=-1;
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            megNyomva=melyikGomb(event.button.x, event.button.y, menuButtons);
            if (megNyomva!=-1)
            {
                switch(megNyomva)
                {
                case 0://new game
                    changeScene(1, currentScene);
                    return;
                case 1://load game
                    strcpy(save_file,"save_file.txt");
                    changeScene(1, currentScene);
                    return;
                    break;
                case 2://fullscrean
                    toggleScreen(renderer,isFullscreen, window, windX, windY,menuButtons);
                    break;
                case 3://exit
                    SDL_Quit();
                    exit(0);
                    break;
                }
            }
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_f)
            {
                toggleScreen(renderer,isFullscreen, window, windX, windY,menuButtons);
            }
            break;
        case SDL_QUIT:
            currentScene = 0;
            break;
        }
        SDL_RenderPresent(renderer);
    }
}

void GameScene(SDL_Renderer *renderer, SDL_Window *window, bool *isFullscreen, int *currentScene, char *save_file)
{
    //változók
    int kertSor=5;
    int kertOszlop=5;
    int tileSize=MERET;
    int penz=0;
    int tickSpeed=10;//játék sebessége
    int currentTool=1;
    player p1={200,200,10};
    int windX, windY;
    SDL_GetWindowSize(window, &windX, &windY);
    int offSetX=(p1.playerX-windX/2);
    int offSetY=(p1.playerY-windY/2);
    printf("\n%s\n",save_file);
    if(save_file[0]!='\0'){
        printf("betoltom");
        loadGame(&kertSor,&kertOszlop,&penz,&p1,save_file);
    }
    DinTomb kertTartalma;
    dintomb_foglal(&kertTartalma, kertSor,kertOszlop);
    if(save_file[0]=='\0'){
        dintomb_feltolt(&kertTartalma, kertTartalma.meretSor, kertTartalma.meretOszlop,0);
    }
    else{
        readTo2DArray(kertTartalma.adat, kertSor, kertOszlop);
    }

    SDL_Texture *novenyek=loadTexture(renderer,"Textures/wheat.png");
    SDL_Texture *playerText=loadTexture(renderer,"Textures/karakter.png");
    int megNyomva=-1;
    bool settingsOpen=false;
    int kertY,kertX;
    SDL_Rect playerReach = {p1.playerX,p1.playerY,tileSize*3,tileSize*3};

    enum{buttonW=150, buttonH=100};
    int gombokSzama=3;
    SDL_Rect menuButtons[gombokSzama]; // An array to store rectangles
    menuButtons[0] = (SDL_Rect){windX/10*3, windY-100, buttonW, buttonH};
    menuButtons[1] = (SDL_Rect){windX/10*5, windY-100, buttonW, buttonH};
    menuButtons[2] = (SDL_Rect){windX/10*7, windY-100, buttonW, buttonH};

    Uint32 startTime = 0;
    Uint32 currentTime = 0;

    while (1)
    {
        currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - startTime;
        if(deltaTime>=10*60*1000){//10 percenkent mentes
            saveGame(kertTartalma.meretSor,kertTartalma.meretOszlop,kertTartalma.adat,penz, p1.playerX, p1.playerY);

            startTime=currentTime;
        }
        //printf("%d\n",deltaTime);
        SDL_GetWindowSize(window, &windX, &windY);
        offSetX=(p1.playerX-windX/2);
        offSetY=(p1.playerY-windY/2);

        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            kertY=(event.button.y+offSetY+tileSize)/tileSize;//which tile did the player press
            kertX=(event.button.x+offSetX+tileSize)/tileSize;
            playerReach.x=p1.playerX-tileSize; playerReach.y=p1.playerY-tileSize;
            if(kertY>0&&kertX>0&&kertY<=kertTartalma.meretSor&&kertX<=kertTartalma.meretOszlop&&inReach(kertX*tileSize,kertY*tileSize,playerReach))//check, hogy a kerten belul kattintottunk-e, és kozel van-e a player
            {
                kertX--;kertY--;
                if (event.button.button == SDL_BUTTON_LEFT&&(kertX>=0&&kertY<kertTartalma.meretSor&&kertX>=0&&kertY<kertTartalma.meretOszlop))
                    if(kertTartalma.adat[kertY][kertX]>=60000)
                    {
                        tileErtek(&kertTartalma,0,kertX, kertY);
                        penz+=1;
                    }
                    else
                    {
                        if(currentTool==2)
                        {
                            int tileErtek = kertTartalma.adat[kertY][kertX];
                            kertTartalma.adat[kertY][kertX]=tileErtek-tileErtek%10+2;
                        }
                    }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    if(kertTartalma.adat[kertY][kertX]==0)
                    {
                        tileErtek(&kertTartalma,1,kertX, kertY);
                    }
                }
            }
            else{
                megNyomva=melyikGomb(event.button.x, event.button.y, menuButtons);
            if (megNyomva!=-1&&settingsOpen)
            {
                switch(megNyomva)
                {
                case 0:
                    //if(elég közel van az ágyhoz)
                    saveGame(kertTartalma.meretSor,kertTartalma.meretOszlop,kertTartalma.adat,penz, p1.playerX, p1.playerY);
                    save_file[0]='\0';
                    changeScene(2, currentScene);
                    memoryCleanup(&kertTartalma, novenyek, playerText);
                    return;
                case 1:
                    toggleScreen(renderer,isFullscreen, window, windX, windY,menuButtons);
                    break;
                case 2:
                    memoryCleanup(&kertTartalma, novenyek, playerText);//, playerText
                    SDL_Quit();
                    exit(0);
                }
            }
            }

            break;
        case SDL_KEYDOWN:
            gamekeyDown(event, &kertTartalma, isFullscreen, window, currentScene,&currentTool,&p1,&settingsOpen,penz);
                        if (event.key.keysym.sym == SDLK_f)
            {
                toggleScreen(renderer,isFullscreen, window, windX, windY,menuButtons);
            }
            break;
        case SDL_USEREVENT:
            SDL_GetWindowSize(window, &windX, &windY);
            novenyNovesztes(&kertTartalma, tickSpeed);
            rajzolas(&kertTartalma, novenyek, renderer,tileSize,&p1,window);
            char szoveg[100];
            snprintf(szoveg, sizeof(szoveg), "Pontok Lacikám, pontok: %d", penz); // Convert the variable to a string
            szoveg_kiir(renderer,szoveg,windX-800,windY-150);
            playerDraw(renderer, playerText, Idle1, windX/2, windY/2);
            //boxRGBA(renderer, windX/2, windY/2, windX/2+10, windY/2+10, 100, 100, 0, 255);//player kirajzolasa
            if(settingsOpen)
            drawSettings(renderer, window, menuButtons,gombokSzama);
            SDL_RenderPresent(renderer);
            boxRGBA(renderer, 0, 0, windX, windY, 100, 50, 0, 255);
            break;
        case SDL_QUIT:
            currentScene=0;
            break;
        }
        if(*currentScene!=2)
        {
            memoryCleanup(&kertTartalma, novenyek, playerText);//,playerText
            return;
        }
    }
}

void gameCycle()//SDL_Renderer *renderer, SDL_Window* window, int isFullscreen
{
    //ablak meghívása
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(ABLAKX, ABLAKY, &window, &renderer);
    // idozito hozzaadasa: 20 ms; 1000 ms / 24 ms -> 60 fps
    SDL_TimerID id = SDL_AddTimer(24, idozit, NULL);
    bool isFullscreen = false;


    int currentScene = 1;
    char save_file[100]="\0";
    bool playing = true;
    while(playing)
    {
        switch(currentScene)//scene selector
        {
        case 1:
            MenuScene(renderer, window, &isFullscreen, &currentScene, save_file);
            break;
        case 2:
            GameScene(renderer, window, &isFullscreen, &currentScene, save_file);
            break;
        }
    }

    SDL_RemoveTimer(id);
}
