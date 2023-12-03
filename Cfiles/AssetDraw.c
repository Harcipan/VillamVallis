#include "GameCycle.h"
#include "AssetDraw.h"
#include "SzovegKiir.h"
#include <stdio.h>
//Funkció:
//  -Kirajzolja a megadott növény állapotát
//Paraméterként kapja:
//  -renderer(SDL_Renderer) renderelõ-re mutató ptr
//  -novenyek(SDL_Texture)  textúra amely a kirajzoláshoz szükséges képeket tartalmazza
//  -melyik:(enum Character)noveny texturábol melyik állapot részletet akarjuk kirajzolni
//  -x,y:(int)              hova akarjuk kirajzolni a karaktert
void plantDraw(SDL_Renderer *renderer, SDL_Texture *novenyek, Buza melyik, int x, int y)
{
    // a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk.
    SDL_Rect src = { (melyik % 6) * 64, (melyik / 6) * 64, MERET, MERET };
    /* a cel kepre, ezekre a koordinatakra masoljuk */
    SDL_Rect dest = { x, y, MERET, MERET };
    // kepreszlet masolasa
    SDL_RenderCopy(renderer, novenyek, &src, &dest);
}

typedef enum Button
{
    playB, scoreB, resumeB,
    optionsB,shopB, exitB
}Button;

void buttonDraw(SDL_Renderer *renderer, SDL_Texture *buttons, Buza melyik, SDL_Rect *menuButtons)
{
    SDL_Rect src = { (melyik % 6) * 64, (melyik / 6) * 64, MERET*2, MERET };
    SDL_Rect dest = { menuButtons->x, menuButtons->y, menuButtons->w, menuButtons->h };
    SDL_RenderCopy(renderer, buttons, &src, &dest);
}

//Funkció:
//  -Kirajzolja a játékos karakterét
//Paraméterként kapja:
//  -renderer(SDL_Renderer) renderelõ-re mutató ptr
//  -texture(SDL_Texture)  textúra amely a kirajzoláshoz szükséges képeket tartalmazza
//  -melyik:(enum Character)character texturábol melyik animáció részletet akarjuk kirajzolni
//  -x,y:(int)              hova akarjuk kirajzolni a karaktert
void playerDraw(SDL_Renderer *renderer, SDL_Texture *texture, Character melyik, int x, int y)
{
    // a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk.
    SDL_Rect src = { (melyik % 4) * MERET, (melyik / 4) * MERET, MERET, MERET };
    // a cel kepre, ezekre a koordinatakra masoljuk
    SDL_Rect dest = { x, y, MERET, MERET };
    // kepreszlet masolasa
    SDL_RenderCopy(renderer, texture, &src, &dest);
}

//Funkció:
//  -Betölti a megadott textúrát
//Paraméterként kapja:
//  -renderer(SDL_Renderer) renderelõ-re mutató ptr
//  -textT(char)            melyik texturat toltse be (texture mappából)
// Visszatérési érték:
//      - SDL_Texture* texture: A betöltött textúrára mutató ptr.
// Megjegyzés: A hívónak gondoskodnia kell a textúra álltal foglalt memória felszabadításáról. (texture)
SDL_Texture* loadTexture(SDL_Renderer *renderer, char *textT)
{
    printf("%s\n",textT);
    SDL_Texture *texture = IMG_LoadTexture(renderer, textT);
    if (texture == NULL)
    {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        SDL_Delay(60000);//60s wait, debug segítség
        exit(1);
    }
    return texture;
}

//Funkció:
//  -Kirajzolja a UserInterface-t
//Paraméterként kapja:
//  -renderer(SDL_Renderer) renderelõ-re mutató ptr
//  -window (SDL_Window)    mejelenített ablak adataira mutató ptr
void drawUI(SDL_Renderer *renderer,SDL_Window *window,player* p1,SDL_Texture *novenyek)
{
    int inventorySlot=3;
    int windX, windY;
    SDL_GetWindowSize(window, &windX, &windY);
    int inventoryX=windX/2-256;
    boxRGBA(renderer, inventoryX+64*(8-inventorySlot+1),windY-64,inventoryX+64*inventorySlot,windY,150,150,150,100);
    boxRGBA(renderer, inventoryX+64*(p1->currentTool-1)+64*(8-inventorySlot-1),windY-64,inventoryX+64*p1->currentTool+64*(inventorySlot-1),windY,150,0,200,100);
    for(int tool=1; tool<=inventorySlot; ++tool)
        plantDraw(renderer, novenyek, WateredSoid+tool, inventoryX+64*(tool-1)+64*(inventorySlot),windY-64);
}

//Funkció:
//  -Kirajzolja a kertben lévö növényeket
//Paraméterként kapja:
//  -kertTartalma(DinTomb)  kert adatait tartalmazó struktúra
//  -novenyek(SDL_Texture)  novenyek textúrájára mutató ptr
//  -renderer(SDL_Renderer) renderelõ-re mutató ptr
//  -window (SDL_Window)    mejelenített ablak adataira mutató ptr
//  -tileSize(int)          mekkora egy ültetheto terulet mérete
//  -p1(player)             játékos pos és speed-et tartalmazó struct
void kertRajzolas(DinTomb *kertTartalma, SDL_Texture *novenyek, SDL_Renderer *renderer, int tileSize,player* p1,SDL_Window *window)
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
            if((kertTartalma->adat[i][j]%10)==2)
            {
                plantDraw(renderer, novenyek, WateredSoid, tileSize*j-offSetX,tileSize*i-offSetY);
            }
            else
            {
                plantDraw(renderer, novenyek, NormalSoil, tileSize*j-offSetX,tileSize*i-offSetY);
            }
            //buza kirajzolasa
            if(kertTartalma->adat[i][j]>=10&&kertTartalma->adat[i][j]<1000)
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
    drawUI(renderer,window,p1,novenyek);
}
//Funkció:
//  -Kirajzolja a fomenut
//Paraméterként kapja:
//  -renderer(SDL_Renderer) renderelõ-re mutató ptr
//  -window (SDL_Window)    mejelenített ablak adataira mutató ptr
//  -menuButtons(SDL_Rect)  kirajzolandó gombok
//  -novenyek(SDL_Texture)  novenyek betöltött képébõl textura dísznek
void drawMenu(SDL_Renderer *renderer, SDL_Window *window,SDL_Rect* menuButtons,SDL_Texture *novenyek)
{

    int windX, windY;
    SDL_GetWindowSize(window, &windX, &windY);
    boxRGBA(renderer, 0, 0, windX, windY, 0, 0, 0, 255);
    int gombokSzama=4;
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);

    char settingsSzoveg[][128]= {{"New Game"},{"Load Game"},{"FullScreen"},{"Exit"}};
    for (int i = 0; i < gombokSzama; i++)
    {
        buttonDraw(renderer, novenyek, button, &menuButtons[i]);
        szoveg_kiir(renderer,settingsSzoveg[i],windX/2+(i+1-gombokSzama/2)*200-165, windY-30,0,1);
    }

    SDL_Rect src = { (WheatS5 % 6) * 64, (WheatS5 / 6) * 64, MERET, MERET };
    SDL_Rect dest = { windX/10*3, windY/10, windY/1.5, windY/1.5 };
    SDL_RenderCopy(renderer, novenyek, &src, &dest);
}
//Funkció:
//  -Kirajzolja a beállítások(at/menut) játék közben/fölé
//Paraméterként kapja:
//  -renderer(SDL_Renderer) renderelõ-re mutató ptr
//  -window (SDL_Window)    mejelenített ablak adataira mutató ptr
//  -menuButtons(SDL_Rect)+gombokSzama  megjelenítendo gombok tömbje+mérete
void drawSettings(SDL_Renderer *renderer, SDL_Window *window,SDL_Rect* menuButtons,int gombokSzama,SDL_Texture *novenyek)
{
    int windX, windY;
    SDL_GetWindowSize(window, &windX, &windY);

    boxRGBA(renderer, 0, 0, windX, windY, 100, 100, 100, 255);

    char settingsSzoveg[][128]= {{"Save&Exit"},{"FullScreen"},{"Exit"}};
    for (int i = 0; i < gombokSzama; i++)
    {
        buttonDraw(renderer, novenyek, button, &menuButtons[i]);
        szoveg_kiir(renderer,settingsSzoveg[i],windX/2+(i+1-gombokSzama/2)*200-270, windY/2+20,0,1);
    }
}
