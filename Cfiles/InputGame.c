#include "GameCycle.h"
#include "ManagementGame.h"

// Funkció:
//  - Kezeli a billentyűzet leütés eseményeit a játék során.
// Paraméterként kapja:
//  - event (SDL_Event): az SDL esemény, ami tartalmazza a billentyűzet állapotát.
//  - kertTartalma (DinTomb*): a játékban lévő kert dinamikus tömbje.
//  - p1 (player*): a játékos állapotát tároló struktúra címe.
//  - isSetting (int*): a jelenlegi beállításokat tárolja.
//  - save_file (char*): a mentési fájl neve
// Visszatérési érték: nincs
// Megjegyzés: Kezeli a játékban történő billentyűzet interakciókat, mint például a kert bővítése, mozgás, mentés.
void gamekeyDown(SDL_Event event, DinTomb *kertTartalma, player* p1, int *isSetting,char* save_file)
{
    //kert minimális és maximális mérete
    int minX=1;
    int minY=1;
    int maxY=6;
    int maxX=10;
    //ha szamot nyomunk meg
    if (event.key.keysym.sym >= SDLK_1 && event.key.keysym.sym <= SDLK_3)
    {
        int pressedNumber = event.key.keysym.sym - SDLK_0;
        p1->currentTool=pressedNumber;
    }
    else
    {
        switch(event.key.keysym.sym)
        {
        //kert bovites eladas
        case SDLK_k:
            if (kertTartalma->meretSor<maxY&&p1->penz>=10)//mit nyomtam és check, hogy van-e még hely boviteni és van-e elég pénz
            {
                p1->penz-=10;
                dintomb_atmeretez(kertTartalma, kertTartalma->meretSor+1, kertTartalma->meretOszlop);
            }
            break;
        case SDLK_o:
            if (kertTartalma->meretOszlop<maxX&&p1->penz>=10)
            {
                p1->penz-=10;
                dintomb_atmeretez(kertTartalma, kertTartalma->meretSor, kertTartalma->meretOszlop+1);
            }
            break;
        case SDLK_j:
            if (kertTartalma->meretSor>minY)
            {
                p1->penz+=10;
                dintomb_atmeretez(kertTartalma, kertTartalma->meretSor-1, kertTartalma->meretOszlop);
            }
            break;
        case SDLK_i:
            if (kertTartalma->meretOszlop>minX)
            {
                p1->penz+=10;
                dintomb_atmeretez(kertTartalma, kertTartalma->meretSor, kertTartalma->meretOszlop-1);
            }
            break;
        //player Movement
        case SDLK_w:
            if(p1->playerY>0)
                p1->up=1;
            break;
        case SDLK_a:
            if(p1->playerX>0)
                p1->left=1;
            break;
        case SDLK_s:
            if(p1->playerY<(60*kertTartalma->meretSor-10))//60:tilesize, 10:playerSize
                p1->down=1;
            break;
        case SDLK_d:
            if(p1->playerX<(60*kertTartalma->meretOszlop-10))
                p1->right=1;
            break;
        case SDLK_z:
            saveGame(kertTartalma->meretSor,kertTartalma->meretOszlop,kertTartalma->adat, p1,save_file);
            break;
        case SDLK_ESCAPE:
            if(*isSetting)
                *isSetting=false;
            else
                *isSetting=true;
            break;
        }
    }
}


// Funkció:
//  - megállítja az animációt és a mozgást ha felengedik a billentyuzet gomját
// Paraméterként kapja:
//  - p1 (player*): a játékos állapotát tároló struktúra címe.
//  - event     mit engedtek fel a billentyuzeten
void gamekeyUp(SDL_Event event, player* p1)
{
    switch(event.key.keysym.sym)
    {
    case SDLK_w:
        p1->up=0;
        break;
    case SDLK_a:
        p1->left=0;
        break;
    case SDLK_s:
        p1->down=0;
        break;
    case SDLK_d:
        p1->right=0;
        break;
    }
}


// Funkció:
//  - Mozgatja a játékost a kijelölt irányban.
// Paraméterként kapja:
//  - p1 (player*): a játékos állapotát tároló struktúra címe.
// Visszatérési érték: nincs
// Megjegyzés: A játékos X és Y koordinátáit módosítja a játékostól függően, figyelembe véve az aktuális sebességet és irányt.
void movePlayer(player* p1)
{
    if(p1->down)
        p1->playerY+=p1->playerSpeed;
    if(p1->up)
        p1->playerY-=p1->playerSpeed;
    if(p1->left)
        p1->playerX-=p1->playerSpeed;
    if(p1->right)
        p1->playerX+=p1->playerSpeed;
}


// Funkció:
//  - Kezeli a billentyűzet input eseményeit.
// Paraméterként kapja:
//  - event (SDL_Event*): az SDL esemény címe, ami tartalmazza a billentyűzet állapotát.
//  - inputText (char*): a felhasználó által beírt szöveg.
// Megjegyzés: Kezeli a szövegbevitelt és a backspace működését az input szövegben. (betöltendo file kiválasztáshoz használlom)
void handle_keyboard_event(SDL_Event *event, char *inputText)
{
    if (event->type == SDL_KEYDOWN)
    {
        if (event->key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0)
        {
            // karakter visszavonás és végjel a végére
            inputText[strlen(inputText) - 1] = '\0';
        }
    }
    else if (event->type == SDL_TEXTINPUT)
    {
        if (strlen(inputText) < 256 - 1)
        {
            strcat(inputText, event->text.text);
        }
    }
}
