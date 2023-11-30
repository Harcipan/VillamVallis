#include "InputGame.h"
#include "SceneMenu.h"
#include "SzovegKiir.h"
#include "Collisions.h"
#include "ManagementGame.h"


//Funkció:
//  -megjeleníti és kezeli a fõmenüt (gombokat kezeli)
//Paraméterként kapja:
//  -ablak                  megjelenítshez szükséges változókat tartalmazó struct
//  -gameVar                játék állapotával kapcsolatos változók
//                          (melyik sceenben vagyunk, új játékot kezdünk-e?)
//  -save_file(char)        melyik mentett állást töltse be a program
void MenuScene(WindowParam* ablak, gameVariables* gameVar, char* save_file)
{
    SDL_StartTextInput();

    SDL_Event event;

    SDL_Texture *novenyText=loadTexture(ablak->renderer,"Textures/wheat.png");

    enum {buttonW=150, buttonH=100};
    int gombokSzama=4;
    SDL_Rect menuButtons[gombokSzama]; // An array to store rectangles
    calcButtonPos(ablak,menuButtons,gombokSzama);
    while (1)
    {

        while(SDL_PollEvent(&event))
        {
            handle_keyboard_event(&event, save_file);
        }
        SDL_GetWindowSize(ablak->window, &ablak->windX, &ablak->windY);
        drawMenu(ablak->renderer, ablak->window, menuButtons,novenyText);
        szoveg_kiir(ablak->renderer,save_file,0,0,0,0);

        int megNyomva=-1;
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            megNyomva=melyikGomb(event.button.x, event.button.y, menuButtons);
            if (megNyomva!=-1)
            {
                switch(megNyomva)
                {
                case 0://new game
                    SDL_DestroyTexture(novenyText);
                    SDL_StopTextInput();
                    gameVar->newGame=true;
                    changeScene(1, &gameVar->currentScene);
                    return;
                    break;
                case 1://load game
                    //memória tisztítása
                    SDL_DestroyTexture(novenyText);
                    SDL_StopTextInput();
                    //másik scenere át kell lépni, gamecycle switche kezeli majd
                    gameVar->newGame=false;
                    changeScene(1, &gameVar->currentScene);
                    return;
                    break;
                case 2://fullscrean
                    toggleScreen(ablak,menuButtons,gombokSzama);
                    break;
                case 3://exit
                    SDL_Quit();
                    exit(0);
                    break;
                }
            }
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_F11)
            {
                toggleScreen(ablak, menuButtons,gombokSzama);
            }
            break;
        case SDL_QUIT:
            gameVar->currentScene = 0;
            SDL_StopTextInput();
            SDL_DestroyRenderer(ablak->renderer);
            SDL_DestroyWindow(ablak->window);
            break;
        }
        SDL_RenderPresent(ablak->renderer);
    }
}
