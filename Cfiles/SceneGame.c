#include <stdio.h>
#include "SceneGame.h"
#include "DinTomb.h"
#include "GameCycle.h"
#include "Ablak.h"
#include "InputGame.h"
#include "ManagementGame.h"
#include "KertErtekad.h"
#include "SzovegKiir.h"
#include "Collisions.h"
#include "debugmalloc.h"

//Funkció:
//  -megjeleníti és kezeli a gameplayt (kert dinamikus kezelését, inputokat, gombokat kezeli) inicializálja a játékhoz szükséges változókat
//Paraméterként kapja:
//  -ablak                  megjelenítshez szükséges változókat tartalmazó struct
//  -gameVar                játék állapotával kapcsolatos változók
//                          (melyik sceenben vagyunk, új játékot kezdünk-e?)
//  -save_file(char)        melyik mentett állást töltse be a program
void GameScene(WindowParam* ablak, gameVariables* gameVar, char *save_file)
{

    player p1= {200,200,2,1,0,2,0,0,0,0,{p1.playerX,p1.playerY,MERET*4,MERET*4}};

    int offSetX=(p1.playerX-ablak->windX/2);
    int offSetY=(p1.playerY-ablak->windY/2);
    DinTomb kertTartalma;
    int kertY,kertX;
    SDL_Texture *novenyText=loadTexture(ablak->renderer,"Textures/wheat.png");
    SDL_Texture *playerText=loadTexture(ablak->renderer,"Textures/karakter.png");


    //settings variables (todo:into struct)
    int megNyomva=-1;
    enum {buttonW=150, buttonH=100};
    int gombokSzama=3;
    SDL_Rect menuButtons[gombokSzama]; // gombokat pozícióját tároló tömb
    calcButtonPos(ablak,menuButtons,gombokSzama);


    initializeGame(gameVar->newGame, save_file,&p1,&kertTartalma,ablak->renderer,ablak->window);

    Uint32 startTime = 0;
    Uint32 currentTime = 0;

    while (1)
    {
        currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - startTime;
        if(deltaTime>=10*60*1000) //10 percenkent mentes
        {
            saveGame(kertTartalma.meretSor,kertTartalma.meretOszlop,kertTartalma.adat, &p1,save_file);

            startTime=currentTime;
        }
        SDL_GetWindowSize(ablak->window, &ablak->windX, &ablak->windY);
        offSetX=(p1.playerX-ablak->windX/2);
        offSetY=(p1.playerY-ablak->windY/2);

        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            kertY=(event.button.y+offSetY+MERET)/MERET;//hova nyomott a játékos az egérrel
            kertX=(event.button.x+offSetX+MERET)/MERET;
            p1.playerReach.x=p1.playerX-MERET;
            p1.playerReach.y=p1.playerY-MERET;
            if(kertY>0&&kertX>0&&kertY<=kertTartalma.meretSor&&kertX<=kertTartalma.meretOszlop&&inReach(kertX*MERET,kertY*MERET,p1.playerReach))//check, hogy a kerten belul kattintottunk-e, és kozel van-e a player
            {
                kertX--;
                kertY--;//bal klikk, aratás, locsolás (tool 2,3)
                if (event.button.button == SDL_BUTTON_LEFT&&(kertX>=0&&kertY<kertTartalma.meretSor&&kertX>=0&&kertY<kertTartalma.meretOszlop))
                {
                    if(kertTartalma.adat[kertY][kertX]>=60000 && p1.currentTool==2)
                    {
                        kertTartalma.adat[kertY][kertX]=0;
                        p1.penz++;
                    }
                    if(p1.currentTool==3&& kertTartalma.adat[kertY][kertX]%10!=2)//még nincsen meglocsolva
                        kertTartalma.adat[kertY][kertX]+=2;

                    if(kertTartalma.adat[kertY][kertX]<10&&p1.currentTool==1)//üres és 1-es tool
                        kertTartalma.adat[kertY][kertX]+=10;
                }
            }
            if(gameVar->settingsOpen)
            {
                megNyomva=melyikGomb(event.button.x, event.button.y, menuButtons);
                if (megNyomva!=-1&&gameVar->settingsOpen)
                {
                    switch(megNyomva)
                    {
                    case 0:
                        //if(elég közel van az ágyhoz)
                        saveGame(kertTartalma.meretSor,kertTartalma.meretOszlop,kertTartalma.adat, &p1,save_file);
                        changeScene(2, &gameVar->currentScene);
                        gameVar->settingsOpen=0;
                        memoryCleanup(&kertTartalma, novenyText, playerText);
                        return;
                    case 1:
                        printf("2");
                        toggleScreen(ablak, menuButtons,gombokSzama);
                        break;
                    case 2:
                        memoryCleanup(&kertTartalma, novenyText, playerText);
                        SDL_Quit();
                        exit(0);
                    }
                }
            }

            break;
        case SDL_KEYDOWN:
            gamekeyDown(event, &kertTartalma,&p1,&gameVar->settingsOpen,save_file);
            if (event.key.keysym.sym == SDLK_f)
            {
                toggleScreen(ablak, menuButtons,gombokSzama);
            }
            break;
        case SDL_KEYUP:
            gamekeyUp(event,&p1);
            break;
        case SDL_USEREVENT:
            SDL_GetWindowSize(ablak->window, &ablak->windX, &ablak->windY);
            if(gameVar->settingsOpen)
            {
                drawSettings(ablak->renderer, ablak->window, menuButtons,gombokSzama,novenyText);
                SDL_RenderPresent(ablak->renderer);
            }
            else
            {
                boxRGBA(ablak->renderer, 0, 0, ablak->windX, ablak->windY, 100, 50, 0, 255);
                novenyNovesztes(&kertTartalma, gameVar->tickSpeed);
                kertRajzolas(&kertTartalma, novenyText, ablak->renderer,MERET,&p1,ablak->window);
                char szoveg[100];
                snprintf(szoveg, sizeof(szoveg), "Pénz: %d", p1.penz); // Convert the variable to a string
                szoveg_kiir(ablak->renderer,szoveg,ablak->windX,ablak->windY,1,1);

                if(++gameVar->animTimer>=gameVar->tickSpeed/2)
                {
                    playerOrient(&p1);
                    gameVar->animTimer=0;
                }
                playerDraw(ablak->renderer, playerText, p1.pOrientation, ablak->windX/2, ablak->windY/2);
                movePlayer(&p1);
                //stopPlayer(&kertTartalma,&p1);
                SDL_RenderPresent(ablak->renderer);
            }
            break;

        case SDL_QUIT:
            gameVar->currentScene=0;
            break;
        }
        if(gameVar->currentScene!=2)
        {
            memoryCleanup(&kertTartalma, novenyText, playerText);
            SDL_DestroyRenderer(ablak->renderer);
            SDL_DestroyWindow(ablak->window);
            return;
        }
    }
}
